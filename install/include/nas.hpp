/*
 * nas.hpp
 *
 *  Created on: 31 Aug 2018
 *      Author: Yun Wu
 */

#ifndef SRC_NAS_HPP_
#define SRC_NAS_HPP_

#include "common.hpp"
#include <curl/curl.h>

class nas{

public:
	nas();
	nas(std::string ip, std::string usrname, std::string passwd,
		std::string filename);
	nas(std::string ip, std::string usrname, std::string passwd,
		std::string filename, char* data, int datasize);
	~nas();
	void setip(std::string ip);
	void setusrname(std::string usrname);
	void setpasswd(std::string passwd);
	void setuploadfilename(std::string filename);
	void setdownloadfilename(std::string filename);
	void setuploaddatasize(int datasize);
	void setdownloaddatasize(int datasize);
	void setuploaddata(char *data, int datasize);
	void setdownloaddata(char *data, int datasize);
	std::string getip();
	std::string getusrname();
	std::string getpasswd();
	std::string getfilename();
	char* getuploaddata();
	char* getdownloaddata();
	void newdataupload();
	void appenddataupload();
	void filedatadownload();
	void fileupload();
	void filedownload();

private:
	std::string nasipaddress;
	std::string nasusername;
	std::string naspasswd;
	std::string filename2upload;
	std::string filename2download;

protected:
	int datauploadsize;
	int datadownloadsize;
	char* data2upload;
	char* datadownload;

};



#endif /* SRC_NAS_HPP_ */
