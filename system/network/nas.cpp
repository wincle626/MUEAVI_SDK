/*
 * nas.cpp
 *
 *  Created on: 31 Aug 2018
 *      Author: Yun Wu
 */

#include "nas.hpp"


nas::nas(){
	this->nasipaddress = std::string("192.168.57.171");
	this->nasusername = std::string("MUEAVI");
	this->naspasswd = std::string("HumanDrive2018");
	this->filename2upload = std::string("test.hdm");
	this->datauploadsize = 0;
	this->datadownloadsize = 0;
	this->data2upload = NULL;
	this->datadownload = NULL;
}

nas::nas(std::string ip, std::string usrname, std::string passwd,
	std::string filename){
	this->nasipaddress = ip;
	this->nasusername = usrname;
	this->naspasswd = passwd;
	this->filename2upload = filename;
	this->datauploadsize = 0;
	this->datadownloadsize = 0;
	this->data2upload = NULL;
	this->datadownload = NULL;
}
nas::nas(std::string ip, std::string usrname, std::string passwd,
	std::string filename, char* data, int datasize){
	this->nasipaddress = ip;
	this->nasusername = usrname;
	this->naspasswd = passwd;
	this->filename2upload = filename;
	this->datauploadsize = datasize;
	this->datadownloadsize = 0;
	this->data2upload = NULL;
	this->data2upload = (char*) realloc(this->data2upload,datasize*sizeof(char));
	memcpy(this->data2upload, data, datasize*sizeof(char));
	this->datadownload = NULL;
}
nas::~nas(){

}
void nas::setip(std::string ip){
	this->nasipaddress = ip;
}

void nas::setusrname(std::string usrname){
	this->nasusername = usrname;
}
void nas::setpasswd(std::string passwd){
	this->naspasswd = passwd;
}

void nas::setuploadfilename(std::string filename){
	this->filename2upload = filename;
}

void nas::setdownloadfilename(std::string filename){
	this->filename2download = filename;
}

void nas::setuploaddatasize(int datasize){
	this->datauploadsize = datasize;
}

void nas::setdownloaddatasize(int datasize){
	this->datadownloadsize = datasize;
}

void nas::setuploaddata(char *data, int datasize){
	this->datauploadsize = datasize;
	this->data2upload = (char*) realloc(this->data2upload,datasize*sizeof(char));
	memcpy(this->data2upload, data, datasize*sizeof(char));
}
void nas::setdownloaddata(char *data, int datasize){
	this->datadownloadsize = datasize;
	this->datadownload = (char*) realloc(this->datadownload,datasize*sizeof(char));
	memcpy(this->datadownload, data, datasize*sizeof(char));
}

std::string nas::getip(){
	return this->nasipaddress;
}

std::string nas::getusrname(){
	return this->nasusername;
}

std::string nas::getpasswd(){
	return this->naspasswd;
}

std::string nas::getfilename(){
	return this->filename2upload;
}

char* nas::getuploaddata(){
	return this->data2upload;
}

char* nas::getdownloaddata(){
	return this->datadownload;
}

struct readmem {
	const char *readptr;
	size_t sizeleft;
};

struct writemem {
	char *writeptr;
	size_t size;
};

struct ftpfile {
	const char *filename;
	FILE *stream;
};

static size_t readmem_callback(void *ptr,
		size_t size, size_t nmemb, void *userp)
{

	struct readmem *upload = (struct readmem *)userp;
	size_t max = size*nmemb;

	if(max < 1)
		return 0;

	if(upload->sizeleft) {
		size_t copylen = max;
		if(copylen > upload->sizeleft)
		  copylen = upload->sizeleft;
		memcpy(ptr, upload->readptr, copylen);
		upload->readptr += copylen;
		upload->sizeleft -= copylen;
		return copylen;
	}

	return 0;                          /* no more data left to deliver */

}

static size_t writemem_callback(void *contents,
		size_t size, size_t nmemb, void *userp)
{
  size_t realsize = size * nmemb;
  struct writemem *mem = (struct writemem *)userp;

  mem->writeptr = (char*)realloc(mem->writeptr, mem->size + realsize + 1);
  if(mem->writeptr == NULL) {
    /* out of memory! */
    printf("not enough memory (realloc returned NULL)\n");
    return 0;
  }

  memcpy(&(mem->writeptr[mem->size]), contents, realsize);
  mem->size += realsize;
  mem->writeptr[mem->size] = 0;

  return realsize;
}


static size_t ftpfwrite(void *buffer, size_t size, size_t nmemb,
                        void *stream)
{
  struct ftpfile *out = (struct ftpfile *)stream;
  if(out && !out->stream) {
    /* open file for writing */
    out->stream = fopen(out->filename, "wb");
    if(!out->stream)
      return -1; /* failure, can't open file to write */
  }
  return fwrite(buffer, size, nmemb, out->stream);
}

void nas::newdataupload(){

	CURL *curl_handle;
	CURLcode res;

	struct readmem upload;

	upload.readptr = this->data2upload;
	upload.sizeleft = this->datauploadsize;

	/* In windows, this will init the winsock stuff */
	res = curl_global_init(CURL_GLOBAL_DEFAULT);
	/* Check for errors */
	if(res != CURLE_OK) {
		fprintf(stderr, "curl_global_init() failed: %s\n",
				curl_easy_strerror(res));
	}

	/* get a curl handle */
	curl_handle = curl_easy_init();
	if(curl_handle) {
		/* First set the URL, the target file */
		std::string linkaddr = std::string("ftp://")
							   + this->nasipaddress
							   + std::string("/")
							   + this->filename2upload;
		curl_easy_setopt(curl_handle, CURLOPT_URL, linkaddr.c_str());

		/* User and password for the FTP login */
		std::string authen = this->nasusername
							 + std::string(":")
							 + this->naspasswd;
		curl_easy_setopt(curl_handle, CURLOPT_USERPWD, authen.c_str());

		/* Now specify we want to UPLOAD data */
		curl_easy_setopt(curl_handle, CURLOPT_UPLOAD, 1L);

		/* we want to use our own read function */
		curl_easy_setopt(curl_handle, CURLOPT_READFUNCTION, readmem_callback);

		/* pointer to pass to our read function */
		curl_easy_setopt(curl_handle, CURLOPT_READDATA, &upload);

		/* get verbose debug output please */
		curl_easy_setopt(curl_handle, CURLOPT_VERBOSE, 1L);

		/* Set the expected upload size. */
		curl_easy_setopt(curl_handle, CURLOPT_INFILESIZE_LARGE,
				 (curl_off_t)upload.sizeleft);

		/* Perform the request, res will get the return code */
		res = curl_easy_perform(curl_handle);
		/* Check for errors */
		if(res != CURLE_OK)
			fprintf(stderr, "curl_easy_perform() failed: %s\n",
					curl_easy_strerror(res));

		/* always cleanup */
		curl_easy_cleanup(curl_handle);
	}
	curl_global_cleanup();

}

void nas::appenddataupload(){
	CURL *curl_handle;
	CURLcode curlcode = CURLE_GOT_NOTHING;
    //long uploaded_len = 0;

	struct readmem uploadstruct;
	uploadstruct.readptr = this->data2upload;
	uploadstruct.sizeleft = this->datauploadsize;

	/* get a curl handle */
	curl_handle = curl_easy_init();
	if(curl_handle) {
		/* First set the URL, the target file */
		std::string linkaddr = std::string("ftp://")
							   + this->nasipaddress
							   + std::string("/")
							   + this->filename2upload;
		curl_easy_setopt(curl_handle, CURLOPT_URL, linkaddr.c_str());

		/* User and password for the FTP login */
		std::string authen = this->nasusername
							 + std::string(":")
							 + this->naspasswd;
		curl_easy_setopt(curl_handle, CURLOPT_USERPWD, authen.c_str());

		/* Now specify we want to UPLOAD data */
		curl_easy_setopt(curl_handle, CURLOPT_UPLOAD, 1L);

		/* Set the timeout times */
		curl_easy_setopt(curl_handle, CURLOPT_FTP_RESPONSE_TIMEOUT, 3);

		/* we want to use our own read function */
		curl_easy_setopt(curl_handle, CURLOPT_READFUNCTION, readmem_callback);

		/* pointer to pass to our read function */
		curl_easy_setopt(curl_handle, CURLOPT_READDATA, &uploadstruct);

		/* get verbose debug output please */
		curl_easy_setopt(curl_handle, CURLOPT_VERBOSE, 1L);

		/* Set the expected upload size. */
		curl_easy_setopt(curl_handle, CURLOPT_INFILESIZE_LARGE,
						 (curl_off_t)uploadstruct.sizeleft);

		/* Set the upload mode to appending */
		curl_easy_setopt(curl_handle, CURLOPT_APPEND, 1L);

		/* Perform the request, curlcode will get the return code */
		curlcode = curl_easy_perform(curl_handle);
		/* Check for errors */
		if(curlcode != CURLE_OK)
		  fprintf(stderr, "curl_easy_perform() failed: %s\n",
				  curl_easy_strerror(curlcode));

		/* always cleanup */
		curl_easy_cleanup(curl_handle);
	}

	curl_global_cleanup();
}

void nas::filedatadownload(){
	CURL *curl_handle;
	CURLcode res;

	struct writemem chunk;

	chunk.writeptr = (char*) malloc(1);  /* will be grown as needed by the realloc above */
	chunk.size = 0;    /* no data at this point */

	curl_global_init(CURL_GLOBAL_ALL);

	/* init the curl session */
	curl_handle = curl_easy_init();

	/* specify URL to get */
	std::string linkaddr = std::string("ftp://")
						   + this->nasipaddress
						   + std::string("/")
						   + this->filename2upload;
	curl_easy_setopt(curl_handle, CURLOPT_URL, linkaddr.c_str());

	/* User and password for the FTP login */
	std::string authen = this->nasusername
						 + std::string(":")
						 + this->naspasswd;
	curl_easy_setopt(curl_handle, CURLOPT_USERPWD, authen.c_str());

	/* send all data to this function  */
	curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, writemem_callback);

	/* we pass our 'chunk' struct to the callback function */
	curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&chunk);

	/* some servers don't like requests that are made without a user-agent
	 field, so we provide one */
	curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");

	/* get it! */
	res = curl_easy_perform(curl_handle);

	/* check for errors */
	if(res != CURLE_OK) {
		fprintf(stderr, "curl_easy_perform() failed: %s\n",
				curl_easy_strerror(res));
	}else {
		/*
		 * Now, our chunk.memory points to a memory block that is chunk.size
		 * bytes big and contains the remote file.
		 *
		 * Do something nice with it!
		 */

		printf("%lu bytes retrieved\n", (unsigned long)chunk.size);
	}

	/* cleanup curl stuff */
	curl_easy_cleanup(curl_handle);

	this->setdownloaddata(chunk.writeptr, chunk.size);

	free(chunk.writeptr);

	/* we're done with libcurl, so clean it up */
	curl_global_cleanup();
}

void nas::fileupload(){
	CURL *curl_handle;
	CURLcode res;
	struct stat file_info;
	//curl_off_t speed_upload;
	//curl_off_t total_time;
	FILE *fd;

	fd = fopen(this->getfilename().c_str(), "rb"); /* open file to upload */
	if(!fd)
		exit(1); /* can't continue */

	/* to get the file size */
	if(fstat(fileno(fd), &file_info) != 0)
		exit(1); /* can't continue */

	curl_handle = curl_easy_init();
	if(curl_handle) {
	/* upload to this place */
	std::string linkaddr = std::string("ftp://")
						   + this->nasipaddress
						   + std::string("/");
	curl_easy_setopt(curl_handle, CURLOPT_URL, linkaddr.c_str());

	/* User and password for the FTP login */
	std::string authen = this->nasusername
						 + std::string(":")
						 + this->naspasswd;
	curl_easy_setopt(curl_handle, CURLOPT_USERPWD, authen.c_str());

	/* tell it to "upload" to the URL */
	curl_easy_setopt(curl_handle, CURLOPT_UPLOAD, 1L);

	/* set where to read from (on Windows you need to use READFUNCTION too) */
	curl_easy_setopt(curl_handle, CURLOPT_READDATA, fd);

	/* and give the size of the upload (optional) */
	curl_easy_setopt(curl_handle, CURLOPT_INFILESIZE_LARGE,
					 (curl_off_t)file_info.st_size);

	/* enable verbose for easier tracing */
	curl_easy_setopt(curl_handle, CURLOPT_VERBOSE, 1L);

	res = curl_easy_perform(curl_handle);
	/* Check for errors */
	if(res != CURLE_OK) {
		fprintf(stderr, "curl_easy_perform() failed: %s\n",
			  curl_easy_strerror(res));

	}
	/*else {
		// now extract transfer info
		curl_easy_getinfo(curl_handle, CURLINFO_SPEED_UPLOAD_T, &speed_upload);
		curl_easy_getinfo(curl_handle, CURLINFO_TOTAL_TIME_T, &total_time);

		fprintf(stderr, "Speed: %" CURL_FORMAT_CURL_OFF_T " bytes/sec during %"
			  CURL_FORMAT_CURL_OFF_T ".%06ld seconds\n",
			  speed_upload,
			  (total_time / 1000000), (long)(total_time % 1000000));

	}*/
	/* always cleanup */
	curl_easy_cleanup(curl_handle);
	}
	fclose(fd);
}


void nas::filedownload(){
	CURL *curl_handle;
	CURLcode res;
	struct ftpfile ffile = {
		"yourfile.bin", /* name to store the file as if successful */
		NULL
	};

	curl_global_init(CURL_GLOBAL_DEFAULT);

	curl_handle = curl_easy_init();
	if(curl_handle) {
		/*
		 * You better replace the URL with one that works! Note that we use an
		 * FTP:// URL with standard explicit FTPS. You can also do FTPS:// URLs if
		 * you want to do the rarer kind of transfers: implicit.
		 */
		std::string linkaddr = std::string("ftp://")
							   + this->nasipaddress
							   + std::string("/")
							   + this->filename2download;
		curl_easy_setopt(curl_handle, CURLOPT_URL, linkaddr.c_str());

		/* User and password for the FTP login */
		std::string authen = this->nasusername
							 + std::string(":")
							 + this->naspasswd;
		curl_easy_setopt(curl_handle, CURLOPT_USERPWD, authen.c_str());

		/* Define our callback to get called when there's data to be written */
		curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, ftpfwrite);

		/* Set a pointer to our struct to pass to the callback */
		curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, &ftpfwrite);

		/* We activate SSL and we require it for both control and data */
		curl_easy_setopt(curl_handle, CURLOPT_USE_SSL, CURLUSESSL_ALL);

		/* Switch on full protocol/debug output */
		curl_easy_setopt(curl_handle, CURLOPT_VERBOSE, 1L);

		res = curl_easy_perform(curl_handle);

		/* always cleanup */
		curl_easy_cleanup(curl_handle);

		if(CURLE_OK != res) {
			/* we failed */
			fprintf(stderr, "curl told us %d\n", res);
		}
	}

	if(ffile.stream)
	fclose(ffile.stream); /* close the local file */

	curl_global_cleanup();
}
