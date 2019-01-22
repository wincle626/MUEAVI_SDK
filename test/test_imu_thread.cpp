/*
 * test_imu_thread.cpp
 *
 *  Created on: 21 May 2018
 *      Author: Yun Wu
 */

#include "test_imu_thread.hpp"

#define IMU_TIMING_TEST imu *dev_imu = new imu((char*)"/dev/ttyUSB0",256000);\
	dev_imu->openPort(); \
	dev_imu->setEnableimurx(true);\
	int err = pthread_create(&dev_imu->RevSeriesPkgThreadId,\
						NULL, revIMUSeriesData_pthread, dev_imu);\
	if (err)\
	{\
		std::cout << "Thread creation failed : " << strerror(err) << std::endl;\
		exit(err);\
	}\
	usleep(1000*1000);\
	err = pthread_create(&dev_imu->RevSeriesPkgDisableThreadId,\
						NULL, disableimurx_pthread, dev_imu);\
	if (err)\
	{\
		std::cout << "Thread creation failed : " << strerror(err) << std::endl;\
		exit(err);\
	}\
	dev_imu->closePort();\
    pthread_join(dev_imu->RevSeriesPkgThreadId, NULL);\
    pthread_join(dev_imu->RevSeriesPkgDisableThreadId, NULL);\
	printf("gps time is: %f\n",dev_imu->getTIME()); \
	delete dev_imu;

void *test_imu_thread(void *p){

	IMU_TIMING_TEST

	std::cout << "imu done !" << std::endl;
	return NULL;
}


/*int main(int argc, char** argv){
    pthread_t imu_thread_id;
    int err1 = pthread_create(&imu_thread_id, NULL, &test_imu_thread, NULL);
    if (err1)
    {
        std::cout << "Thread creation failed : " << strerror(err1) << std::endl;
        exit(err1);
    }
    pthread_join(imu_thread_id, NULL);
    return 0;
}*/
