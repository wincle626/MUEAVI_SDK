/*
 * timestamp.cpp
 *
 *  Created on: 16 May 2018
 *      Author: Yun Wu
 */

#include "timestamp.hpp"

struct timestampvideodatastruct{
	float videodelay_codec;
	float videodelay_network;
	ptzcam *dev_ptzcam;
	imu *dev_imu;
};

void *timestampvideo(timestampvideodatastruct *p){

	unsigned char timebytes[4];
	ptzcam *dev_ptzcam = (ptzcam*) p->dev_ptzcam;
	imu *dev_imu = (imu*) p->dev_imu;
	dev_ptzcam->capture_cv();
	for(;;){
		dev_ptzcam->capture_cvframe();
		float imutime = dev_imu->getTIME();
		float2byte(imutime, timebytes);
		dev_ptzcam->cvframe2rawdata();
		dev_ptzcam->setrawdatatime(timebytes);
		unsigned char *ptzrawdata = dev_ptzcam->getrawdata();
	}
	return NULL;
}

void timestamplidar(){

}

void timestampradar(){

}
