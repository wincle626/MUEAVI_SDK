/*
 * test_nas_thread.cpp
 *
 *  Created on: 17 Sep 2018
 *      Author: Yun Wu
 */

#include "test_nas_thread.hpp"

std::string newdata = std::string("This is a test message from host.\n \
			  We use this message to test our NAS. \n \
			  If you see this in the NAS, it means our test succeeds.\n");
std::string  appenddata = std::string("This is a test message from host.\n \
			  We use this message to test our NAS. \n \
			  If you see this in the NAS, it means our test succeeds again.\n");

void *test_nas_thread(void *context){
	nas *dev_nas1 = new nas(std::string("192.168.57.171"),
						std::string("MUEAVI"),
						std::string("HumanDrive2018"),
						std::string("test.hdm"),
						(char*)newdata.c_str(),
						 newdata.size());
						 
	nas *dev_nas2 = new nas(std::string("192.168.57.171"),
						std::string("MUEAVI"),
						std::string("HumanDrive2018"),
						std::string("test.hdm"),
						(char*)appenddata.c_str(), 
						appenddata.size());

	nas *dev_nas3 = new nas(std::string("192.168.57.171"),
						std::string("MUEAVI"),
						std::string("HumanDrive2018"),
						std::string("test.hdm"));

	dev_nas1->newdataupload();
	dev_nas2->appenddataupload();

	dev_nas3->filedatadownload();
	std::cout << dev_nas3->getdownloaddata() << std::endl;

	dev_nas3->filedownload();
	return NULL;
}