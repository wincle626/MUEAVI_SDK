/*
 * test_radar_thread.cpp
 *
 *  Created on: 28 Aug 2018
 *      Author: Yun Wu
 */

#include "test_radar_thread.hpp"

void *test_radar_thread(void *p){

    radar *dev_radar = new radar(12345, 5000, std::string("humandrive"),
                                std::string("Liber"), std::string("Liber!"),
		                        std::string("10.42.0.82"));
	std::cout << "device ip: " << dev_radar->getipaddress() << std::endl;
	std::cout << "device data port: " << dev_radar->getdataportnum() << std::endl;
	std::cout << "device rest port: " << dev_radar->getrestportnum() << std::endl;

	pthread_t id1;
	pthread_t id2;
	pthread_t id3;

	int err1 = pthread_create(&id1, NULL, dataacquire_thread, dev_radar);
	if(err1){
		std::cout << "failed to create thread to netcat data from Plextek Radar" << std::endl;
		exit(0);
	}
	int err2  = pthread_create(&id2, NULL, terminatedataacquire_thread, dev_radar);
	if(err2){
		std::cout << "failed to create thread to teminate netcat data from Plextek Radar" << std::endl;
	}

	pthread_join(id1, NULL);
	pthread_join(id2, NULL);

    writestr2file(std::string(dev_radar->getdatasparse()), std::string("radar_data.txt"));

	int err3 = pthread_create(&id3, NULL, parsedatasparse_thread, dev_radar);
	if(err3){
		std::cout << "failed to create data parsing thread" << std::endl;
	}
	pthread_join(id3, NULL);
	float *parseddata = dev_radar->getparseddatasparse();
	for(int i=0;i<dev_radar->getparseddatasize();i++){
    	std::cout << parseddata[i] << std::endl;
	}
}