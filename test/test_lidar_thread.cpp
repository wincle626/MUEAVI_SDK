/*
 * test_urg2d_thread.cpp
 *
 *  Created on: 7 Jun 2018
 *      Author: Yun Wu
 */

#include "test_lidar_thread.hpp"


void *test_urg2d_thread(void *p){
	urg2d *sys_urg2d = new urg2d(std::string("10.42.0.11"), 10940);
	std::cout << "sensor ip address: " << sys_urg2d->geturg2dconnectaddress() << std::endl;
	std::cout << "sensor port number: " << sys_urg2d->geturg2dconnetport() << std::endl;
	return NULL;
}

void *test_urg3d_thread(void *p){
	urg3d *sys_urg3d = new urg3d(std::string("10.42.0.10"), 10940);
	std::cout << "connect sensor at " << sys_urg3d->get_connect_address_urg3d() << std::endl;
	std::cout << "connect port at " << sys_urg3d->get_connect_port_urg3d() << std::endl;
    sys_urg3d->connectsensor();
    sys_urg3d->initsensor();
    sys_urg3d->setrangeswitch(true);
    sys_urg3d->setintensityswith(false);
    sys_urg3d->setauxilaryswith(false);
    sys_urg3d->startdatastream();
    //sys_urg3d->measuresingledataframe();
    sys_urg3d->urg3d_pcl_display();
    sys_urg3d->stopdatastream();
    sys_urg3d->disconnectsensor();
	return NULL;
}


int datasize;
pcl::PointCloud<quanergy::PointXYZIR> rawdatacpy;
float *fdatacpy = NULL;

void *data_print_thread(void *p){

    std::string input;
    std::getline(std::cin, input);

    {
    	quanergym8 *context = (quanergym8*) p;
		std::cout << "get data" << std::endl;
		pcl::PointCloud<quanergy::PointXYZIR> rawdata = context->getm8pointcloud();
		char *fdata = context->getm8data();
		std::cout << "get data size: " << context->getm8datasize() << std::endl;
		datasize = context->getm8datasize();
		for(uint i=0;i<(uint)rawdata.size();i++){
			rawdatacpy.push_back(rawdata.at(i));
		}
		fdatacpy = (float*) realloc(fdatacpy, datasize);
		memcpy(fdatacpy,fdata,datasize);
    }

	return NULL;

}

void *data_update_thread(void *p){
	quanergym8 *context = (quanergym8*) p;
    std::cout << "start data receiver" << std::endl;
    context->setm8visonffflag(1);
    context->m8datareveiver();
	return NULL;
}

void *control_thread(void *p){

	quanergym8 *context = (quanergym8*) p;

    std::cout << "wait for 10s" << std::endl;
	usleep(1000*1000*10);

    std::cout << "turn on the sensor" << std::endl;
    context->setm8onoffflag(2);

    std::cout << "wait for 120s" << std::endl;
	usleep(1000*1000*120);

    std::cout << "turn off the sensor" << std::endl;
    context->setm8onoffflag(1);

    std::cout << "exit the thread" << std::endl;
    context->setm8onoffflag(0);
	return NULL;
}

void *test_m8_thread(void *p){

	// port number; queue number, return number, ip address
	quanergym8 dev_m8(4141, 100, 2, "192.168.57.162");

	pthread_t tid1;
	pthread_t tid2;
	pthread_t tid3;

	int err1 = pthread_create(&tid1, NULL, data_update_thread, &dev_m8);
	if(err1){
		std::cout << "failed to create thread to test the M8 data acquiring" << std::endl;
	}
	int err2 = pthread_create(&tid2, NULL, control_thread, &dev_m8);
	if(err2){
		std::cout << "failed to create thread to test the M8 control" << std::endl;
	}
	int err3 = pthread_create(&tid3, NULL, data_print_thread, &dev_m8);
	if(err3){
		std::cout << "failed to create thread to test the M8 control" << std::endl;
	}
	pthread_join(tid3, NULL);
	pthread_join(tid2, NULL);
	pthread_join(tid1, NULL);

	std::cout << "raw data size: " << rawdatacpy.size() << std::endl;
	std::cout << "char data size: " << datasize << std::endl;

    std::cout << "save data" << std::endl;
	FILE *fp1;
	FILE *fp2;
	fp1 = fopen("rawdata.txt", "w+");
	fp2 = fopen("chardata.txt", "w+");
	uint i=0;
	for(i=0;i<rawdatacpy.size();i++)
		fprintf(fp1, "%f\t%f\t%f\t%f\t%f\n", rawdatacpy.at(i).x,
				rawdatacpy.at(i).y, rawdatacpy.at(i).z, rawdatacpy.at(i).intensity,
				(float)rawdatacpy.at(i).ring );
	for(i=0;i<(uint)datasize/20;i++)
		fprintf(fp2, "%f\t%f\t%f\t%f\t%f\n", fdatacpy[5*i],fdatacpy[5*i+1],fdatacpy[5*i+2],fdatacpy[5*i+3],fdatacpy[5*i+4]);
	fclose(fp1);
	fclose(fp2);

	return NULL;
}
