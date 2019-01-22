/*
 * radar.cpp
 *
 *  Created on: 16 May 2018
 *      Author: Yun Wu
 *  Modified on: 7 Aug 2018 by Yun Wu - add data strucuture and functions
 */

#include "radar.hpp"

radar::radar(){
	this->device_on = false;
	this->dataportnum = 12345;
	this->restportnum = 5000;
    this->username = std::string("liber");
    this->password = std::string("Liber!");;
    this->ipaddress = std::string("10.42.0.82");
    this->localpasswd = std::string("humandrive");
    this->controlurl = std::string("control/capture-in-progress");
    this->adcresurl = std::string("config/0");
    this->couplingurl = std::string("config/1");
    this->dopplerppicolormapurl = std::string("config/2");
    this->dopplerppiminvalurl = std::string("config/3");
    this->dopplerppimaxvalurl = std::string("config/4");
    this->dopplerresurl = std::string("config/5");
    this->effdownsampleratiourl = std::string("config/6");
    this->hwdownsamplemodeurl = std::string("config/7");
    this->whdownsampleratiourl = std::string("config/8");
    this->ignoredopplerbinurl = std::string("config/9");
    this->maxsparsepointsurl = std::string("config/10");
    this->movingthresholdurl = std::string("config/11");
    this->munstaticbinurl = std::string("config/12");
    this->numdopplerbinurl = std::string("config/13");
    this->numpositiverangebinurl = std::string("config/14");
    this->numrangebinurl = std::string("config/15");
    this->numspokesurl = std::string("config/16");
    this->persistenceurl = std::string("config/17");
    this->persistencedopplerlenurl = std::string("config/18");
    this->persistenceppilenurl = std::string("config/19");
    this->ppimaxrangeurl = std::string("config/20");
    this->ppireversespokesurl = std::string("config/21");
    this->radaridurl = std::string("config/22");
    this->rangebinsizeurl = std::string("config/23");
    this->rawmodeurl = std::string("config/24");
    this->samplingdurationurl = std::string("config/25");
    this->sampleingrateurl = std::string("config/26");
    this->spokeresurl = std::string("config/27");
    this->staticthresholdurl = std::string("config/28");
    this->storagechecksumurl = std::string("config/29");
    this->storagecompressurl = std::string("config/30");
    this->storageoverwriteurl = std::string("config/31");
    this->storageshuffleurl = std::string("config/32");
    this->sumppimaxvalurl = std::string("config/33");
    this->sumppiminvalurl = std::string("config/34");
    this->swdownsampleratiourl = std::string("config/35");
    this->trigdirurl = std::string("config/36");
    this->trigsourceurl = std::string("config/37");
    this->trigvurl = std::string("config/38");
    this->trigvrangeurl = std::string("config/39");
    this->timeflybackurl = std::string("config/40");
    this->timepostacquiringrl = std::string("config/41");
    this->timepriorurl = std::string("config/42");
    this->timerampdurationurl = std::string("config/43");
    this->timespokeurl = std::string("config/44");
    this->timestarturl = std::string("config/45");
    this->vrangeurl = std::string("config/46");
    this->data_sparse_size = 0;
    this->data_full_size = 0;
    this->data_sparse = NULL;
    this->data_full = NULL;
}

radar::radar(int dataport, int restport, std::string ipaddr){
	this->device_on = false;
    this->dataportnum = dataport;
    this->restportnum = restport;
    this->username = std::string("liber");
    this->password = std::string("Liber!");
    this->ipaddress = ipaddr;
    this->localpasswd = std::string("humandrive");
    this->controlurl = std::string("control/capture-in-progress");
    this->adcresurl = std::string("config/0");
    this->couplingurl = std::string("config/1");
    this->dopplerppicolormapurl = std::string("config/2");
    this->dopplerppiminvalurl = std::string("config/3");
    this->dopplerppimaxvalurl = std::string("config/4");
    this->dopplerresurl = std::string("config/5");
    this->effdownsampleratiourl = std::string("config/6");
    this->hwdownsamplemodeurl = std::string("config/7");
    this->whdownsampleratiourl = std::string("config/8");
    this->ignoredopplerbinurl = std::string("config/9");
    this->maxsparsepointsurl = std::string("config/10");
    this->movingthresholdurl = std::string("config/11");
    this->munstaticbinurl = std::string("config/12");
    this->numdopplerbinurl = std::string("config/13");
    this->numpositiverangebinurl = std::string("config/14");
    this->numrangebinurl = std::string("config/15");
    this->numspokesurl = std::string("config/16");
    this->persistenceurl = std::string("config/17");
    this->persistencedopplerlenurl = std::string("config/18");
    this->persistenceppilenurl = std::string("config/19");
    this->ppimaxrangeurl = std::string("config/20");
    this->ppireversespokesurl = std::string("config/21");
    this->radaridurl = std::string("config/22");
    this->rangebinsizeurl = std::string("config/23");
    this->rawmodeurl = std::string("config/24");
    this->samplingdurationurl = std::string("config/25");
    this->sampleingrateurl = std::string("config/26");
    this->spokeresurl = std::string("config/27");
    this->staticthresholdurl = std::string("config/28");
    this->storagechecksumurl = std::string("config/29");
    this->storagecompressurl = std::string("config/30");
    this->storageoverwriteurl = std::string("config/31");
    this->storageshuffleurl = std::string("config/32");
    this->sumppimaxvalurl = std::string("config/33");
    this->sumppiminvalurl = std::string("config/34");
    this->swdownsampleratiourl = std::string("config/35");
    this->trigdirurl = std::string("config/36");
    this->trigsourceurl = std::string("config/37");
    this->trigvurl = std::string("config/38");
    this->trigvrangeurl = std::string("config/39");
    this->timeflybackurl = std::string("config/40");
    this->timepostacquiringrl = std::string("config/41");
    this->timepriorurl = std::string("config/42");
    this->timerampdurationurl = std::string("config/43");
    this->timespokeurl = std::string("config/44");
    this->timestarturl = std::string("config/45");
    this->vrangeurl = std::string("config/46");
    this->data_sparse_size = 0;
    this->data_full_size = 0;
    this->data_sparse = NULL;
    this->data_full = NULL;
}

radar::radar(int dataport, int restport,
		std::string usrname, std::string usrpsswd, std::string ipaddr){
	this->device_on = false;
    this->dataportnum = dataport;
    this->restportnum = restport;
    this->username = usrname;
    this->password = usrpsswd;
    this->ipaddress = ipaddr;
    this->localpasswd = std::string("humandrive");
    this->controlurl = std::string("control/capture-in-progress");
    this->adcresurl = std::string("config/0");
    this->couplingurl = std::string("config/1");
    this->dopplerppicolormapurl = std::string("config/2");
    this->dopplerppiminvalurl = std::string("config/3");
    this->dopplerppimaxvalurl = std::string("config/4");
    this->dopplerresurl = std::string("config/5");
    this->effdownsampleratiourl = std::string("config/6");
    this->hwdownsamplemodeurl = std::string("config/7");
    this->whdownsampleratiourl = std::string("config/8");
    this->ignoredopplerbinurl = std::string("config/9");
    this->maxsparsepointsurl = std::string("config/10");
    this->movingthresholdurl = std::string("config/11");
    this->munstaticbinurl = std::string("config/12");
    this->numdopplerbinurl = std::string("config/13");
    this->numpositiverangebinurl = std::string("config/14");
    this->numrangebinurl = std::string("config/15");
    this->numspokesurl = std::string("config/16");
    this->persistenceurl = std::string("config/17");
    this->persistencedopplerlenurl = std::string("config/18");
    this->persistenceppilenurl = std::string("config/19");
    this->ppimaxrangeurl = std::string("config/20");
    this->ppireversespokesurl = std::string("config/21");
    this->radaridurl = std::string("config/22");
    this->rangebinsizeurl = std::string("config/23");
    this->rawmodeurl = std::string("config/24");
    this->samplingdurationurl = std::string("config/25");
    this->sampleingrateurl = std::string("config/26");
    this->spokeresurl = std::string("config/27");
    this->staticthresholdurl = std::string("config/28");
    this->storagechecksumurl = std::string("config/29");
    this->storagecompressurl = std::string("config/30");
    this->storageoverwriteurl = std::string("config/31");
    this->storageshuffleurl = std::string("config/32");
    this->sumppimaxvalurl = std::string("config/33");
    this->sumppiminvalurl = std::string("config/34");
    this->swdownsampleratiourl = std::string("config/35");
    this->trigdirurl = std::string("config/36");
    this->trigsourceurl = std::string("config/37");
    this->trigvurl = std::string("config/38");
    this->trigvrangeurl = std::string("config/39");
    this->timeflybackurl = std::string("config/40");
    this->timepostacquiringrl = std::string("config/41");
    this->timepriorurl = std::string("config/42");
    this->timerampdurationurl = std::string("config/43");
    this->timespokeurl = std::string("config/44");
    this->timestarturl = std::string("config/45");
    this->vrangeurl = std::string("config/46");
    this->data_sparse_size = 0;
    this->data_full_size = 0;
    this->data_sparse = NULL;
    this->data_full = NULL;
}

radar::radar(int dataport, int restport, std::string localusrpasswd,
		std::string usrname, std::string usrpsswd, std::string ipaddr){
	this->device_on = false;
    this->dataportnum = dataport;
    this->restportnum = restport;
    this->username = usrname;
    this->password = usrpsswd;
    this->ipaddress = ipaddr;
    this->localpasswd = std::string("humandrive");
    this->controlurl = std::string("control/capture-in-progress");
    this->adcresurl = std::string("config/0");
    this->couplingurl = std::string("config/1");
    this->dopplerppicolormapurl = std::string("config/2");
    this->dopplerppiminvalurl = std::string("config/3");
    this->dopplerppimaxvalurl = std::string("config/4");
    this->dopplerresurl = std::string("config/5");
    this->effdownsampleratiourl = std::string("config/6");
    this->hwdownsamplemodeurl = std::string("config/7");
    this->whdownsampleratiourl = std::string("config/8");
    this->ignoredopplerbinurl = std::string("config/9");
    this->maxsparsepointsurl = std::string("config/10");
    this->movingthresholdurl = std::string("config/11");
    this->munstaticbinurl = std::string("config/12");
    this->numdopplerbinurl = std::string("config/13");
    this->numpositiverangebinurl = std::string("config/14");
    this->numrangebinurl = std::string("config/15");
    this->numspokesurl = std::string("config/16");
    this->persistenceurl = std::string("config/17");
    this->persistencedopplerlenurl = std::string("config/18");
    this->persistenceppilenurl = std::string("config/19");
    this->ppimaxrangeurl = std::string("config/20");
    this->ppireversespokesurl = std::string("config/21");
    this->radaridurl = std::string("config/22");
    this->rangebinsizeurl = std::string("config/23");
    this->rawmodeurl = std::string("config/24");
    this->samplingdurationurl = std::string("config/25");
    this->sampleingrateurl = std::string("config/26");
    this->spokeresurl = std::string("config/27");
    this->staticthresholdurl = std::string("config/28");
    this->storagechecksumurl = std::string("config/29");
    this->storagecompressurl = std::string("config/30");
    this->storageoverwriteurl = std::string("config/31");
    this->storageshuffleurl = std::string("config/32");
    this->sumppimaxvalurl = std::string("config/33");
    this->sumppiminvalurl = std::string("config/34");
    this->swdownsampleratiourl = std::string("config/35");
    this->trigdirurl = std::string("config/36");
    this->trigsourceurl = std::string("config/37");
    this->trigvurl = std::string("config/38");
    this->trigvrangeurl = std::string("config/39");
    this->timeflybackurl = std::string("config/40");
    this->timepostacquiringrl = std::string("config/41");
    this->timepriorurl = std::string("config/42");
    this->timerampdurationurl = std::string("config/43");
    this->timespokeurl = std::string("config/44");
    this->timestarturl = std::string("config/45");
    this->vrangeurl = std::string("config/46");
    this->data_sparse_size = 0;
    this->data_full_size = 0;
    this->data_sparse = NULL;
    this->data_full = NULL;
}

radar::~radar(){

}

void radar::setdeviceonflag(bool flag){
	this->device_on = flag;
}

void radar::setdataportnum(int port){
	this->dataportnum = port;
}

void radar::setrestportnum(int port){
	this->restportnum = port;
}

void radar::setipaddress(std::string ipaddr){
	this->ipaddress = ipaddr;
}
void radar::setusername(std::string usrname){
	this->username = usrname;
}
void radar::setuserpasswd(std::string usrpasswd){
	this->password = usrpasswd;
}

void radar::setdatasparsesize(int len){
	this->data_sparse_size = len;
}
void radar::setdatafullsize(int len){
	this->data_full_size = len;
}

void radar::setdatasparse(char* data){
    this->data_sparse = (char*) realloc(this->data_sparse, this->data_sparse_size*sizeof(char));
	memcpy(this->data_sparse, data, this->data_sparse_size);
}
void radar::setdatafull(char* data){
    this->data_full = (char*) realloc(this->data_full, this->data_full_size*sizeof(char));
	memcpy(this->data_full, data, this->data_full_size);
}

bool radar::getdeviceonflag(){
	return this->device_on;
}

int radar::getdataportnum(){
	return this->dataportnum;
}

int radar::getrestportnum(){
	return this->restportnum;
}

int radar::getdatasparsesize(){
	return this->data_sparse_size;
}

int radar::getdatafullsize(){
	return this->data_full_size;
}

int radar::getparseddatasize(){
    return this->parsed_data_size;
}

std::string radar::getipaddress(){
	return this->ipaddress;
}

std::string radar::getusername(){
	return this->username;
}

std::string radar::getuserpasswd(){
	return this->password;
}

char* radar::getdatasparse(){
	return this->data_sparse;
}

char* radar::getdatafull(){
	return this->data_full;
}

void radar::switchondevice(){
	std::string cmd = std::string(this->ipaddress)
					+ std::string(":")
					+ std::to_string(this->restportnum)
					+ std::string("/")
					+ this->controlurl
                    + std::string("?value=True");
	this->seturl(cmd);
	this->curlput();
	this->setdeviceonflag(true);
}

void radar::switchoffdevice(){
	std::string cmd = std::string(this->ipaddress)
					+ std::string(":")
					+ std::to_string(this->restportnum)
					+ std::string("/")
					+ this->controlurl
                    + std::string("?value=False");
    std::cout << cmd << std::endl;
	this->seturl(cmd);
	this->curlput();
	this->setdeviceonflag(false);
}

void radar::getdeviceonstatus(){
	std::string cmd = std::string(this->ipaddress)
					+ std::string(":")
					+ std::to_string(this->restportnum)
					+ std::string("/")
					+ this->controlurl;
	this->seturl(cmd);
	this->curlget();

}

void radar::switchonserverservice(){
    std::string startcmd = std::string("sshpass -p \"root\" ssh -o StrictHostKeyChecking=no root@")
                            + std::string(this->ipaddress)
                            + std::string(" 'systemctl start liber.service'");
    int err = std::system(startcmd.c_str());
	if(err){
		std::cout << "error when executing command" << std::endl;
	}
    usleep(100);
}

void radar::switchoffserverservice(){
    std::string stopcmd = std::string("sshpass -p \"root\" ssh -o StrictHostKeyChecking=no root@")
                            + std::string(this->ipaddress)
                            + std::string(" 'systemctl stop liber.service'");
    int err = std::system(stopcmd.c_str());
	if(err){
		std::cout << "error when executing command" << std::endl;
	}
    usleep(100);

}

void radar::resetserverservice(){
    std::string stopcmd = std::string("sshpass -p \"root\" ssh -o StrictHostKeyChecking=no root@")
                            + this->ipaddress
                            + std::string(" 'systemctl stop liber.service'");
    std::string startcmd = std::string("sshpass -p \"root\" ssh -o StrictHostKeyChecking=no root@")
                            + this->ipaddress
                            + std::string(" 'systemctl start liber.service'");
    int err = std::system(stopcmd.c_str());
	usleep(100);
	err |= std::system(startcmd.c_str());
	usleep(100);
	if(err){
		std::cout << "error when executing command" << std::endl;
	}
    std::cout << stopcmd << std::endl;
    std::cout << startcmd << std::endl;
}

std::string radar::acquiresparsedata(){
	std::string cmd = std::string("nc ")
					+ this->ipaddress
					+ std::string(" ")
					+ std::to_string(this->dataportnum);    
    std::string data = getcmdstdout1(cmd);
    return data;
}

std::string radar::acquiresparsedata2(){
	std::string cmd = std::string("nc ")
					+ this->ipaddress
					+ std::string(" ")
					+ std::to_string(this->dataportnum);
    std::string data = getcmdstdout2(cmd.c_str());
    return data;
}

void radar::acquirefulldata(){

}
void radar::stopdataacquire(){
    std::string cmd = std::string("echo ")
                        + std::string("'")
                        + this->localpasswd
                        + std::string("'")
                        + std::string(" | sudo -kS pkill -fx 'nc ")
                        + this->ipaddress
                        + std::string(" ")
                        + std::to_string(this->dataportnum)
                        + std::string("' > /dev/null");
    int err = std::system(cmd.c_str());
	if(err){
		std::cout << "error when executing command" << std::endl;
	}
	usleep(100);
}

void radar::parse_data_sparse(){

    int data_len = 0;

    char *pd = this->getdatasparse();
	json_object *jobj = json_tokener_parse(pd);

	json_object *value1 = NULL;
	json_object_object_get_ex(jobj, "id", &value1);
    //float id = std::stof(json_object_get_string(value1));
    float id = (float) json_object_get_double(value1);
    data_len += 1;

	json_object *value2 = NULL;
	json_object_object_get_ex(jobj, "ts", &value2);
    //float ts = std::stof(json_object_get_string(value2));
    float ts = (float) json_object_get_double(value2);
    data_len += 1;

	json_object *value3 = NULL;
	json_object_object_get_ex(jobj, "ov", &value3);
    //float ov = std::stof(json_object_get_string(value3));
    float ov = (float) json_object_get_double(value3);
    data_len += 1;

	json_object *value4 = NULL;
	json_object_object_get_ex(jobj, "data", &value4);
	struct array_list *arr = json_object_get_array(value4);
    struct json_object *value5 = json_object_array_get_idx(value4, 0);
    struct array_list *subarr = json_object_get_array(value5);
    data_len += arr->length * subarr->length;
    /*std::cout << "data length = "
              << arr->length 
              << " x " 
              << subarr->length  
              << " + "
              << 3
              << " = "
              << data_len
              << std::endl;*/
    this->parsed_data_size = data_len;
    this->parsed_data_sparse = (float*) realloc(this->parsed_data_sparse, data_len * sizeof(float));
    this->parsed_data_sparse[0] = id;
    this->parsed_data_sparse[1] = ts;
    this->parsed_data_sparse[2] = ov;
    //std::cout << id << ":" << ts << ":" << ov << std::endl;

	for(int i=0;i<arr->length;i++){
		value5 = json_object_array_get_idx(value4, i);
		subarr = json_object_get_array(value5);
		for(int j=0;j<subarr->length;j++){
			struct json_object *value6 = json_object_array_get_idx(value5, j);
            float dataf;
            std::string datastr = json_object_get_string(value6);
            dataf = (float)std::atof(datastr.c_str());
            //std::cout << "i:" << i << "j:" << j << std::endl;
            //std::cout << datastr << std::endl;
            this->parsed_data_sparse[i*subarr->length+j+3] = dataf;
		}
	}

}

float* radar::getparseddatasparse(){
    return this->parsed_data_sparse;
}

void radar::parse_data_full(){

}

void *terminatedataacquire_thread(void *context){
	usleep(10);
	((radar *) context) ->stopdataacquire(); 
	//((radar *) context) ->switchoffdevice();
	return NULL;
}

void *dataacquire_thread(void *context){
	// std::system("curl -X PUT 10.42.0.82:5000/control/capture-in-progress?value=true");
	//((radar *) context) ->switchondevice();
    //((radar *) context) -> resetserverservice();
	std::string data = std::string("");
	std::string cmd = std::string("nc ")
					+ ((radar *) context)->getipaddress()
					+ std::string(" ")
					+ std::to_string(((radar *) context)->getdataportnum());    
    std::cout << cmd << std::endl;  
    data = ((radar *) context) -> acquiresparsedata(); 
    std::cout << std::endl;
    std::cout << "data size: " << data.size() << std::endl;
    //std::cout << data << std::endl;
    ((radar *) context) -> setdatasparsesize(data.size());
    std::cout << "set data size: " << ((radar *) context) -> getdatasparsesize() << std::endl;
    ((radar *) context) -> setdatasparse((char*)data.c_str());
    //std::cout << "set data: " << ((radar *) context) -> getdatasparse() << std::endl;
    return NULL;
}

void *parsedatasparse_thread(void *context){
	((radar *) context) ->parse_data_sparse(); 
    return NULL;
}