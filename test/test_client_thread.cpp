/*
 * test_client_thread.cpp
 *
 *  Created on: 18 July 2018
 *      Author: Yun Wu
 */

#include "test_client_thread.hpp"

void *acquire_imu_frame_thread(void *p){
ENTER_FUNC
    ((imu *)p)->openPort();
    ((imu *)p)->setEnableimurx(true);
    ((imu *)p)->revIMUFrameData();
    ((imu *)p)->getTIME();
    return NULL;
EXIT_FUNC
}

void *acquire_ptzcam_frame_thread(void *p){
ENTER_FUNC
    ((ptzcam *)p)->capture_cv();
    ((ptzcam *)p)->capture_cvframe();
    ((ptzcam *)p)->capture_cvframe_size();
EXIT_FUNC
    return NULL;
}

void *acquire_lidarm8_frame_thread(void *p){
    char * data = ((quanergym8 *)p)->getm8data();
    return NULL;
}

void data_acquire(imu *dev_imu, ptzcam *dev_ptzcam, quanergym8 *dev_lidarm8){
ENTER_FUNC
    // data acquiring threads
    //pthread_t dev_imu_thread_id;
    pthread_t dev_ptzcam_thread_id;
    pthread_t dev_lidarm8_thread_id;

    // acquiring GPS time
    /*int err1 = pthread_create(&dev_imu_thread_id, NULL, &acquire_imu_frame_thread, dev_imu);
    if(err1){
        std::cout << "failed to create GPS thread" << std::endl;
    }*/

    // acquiring Camera data
    int err2 = pthread_create(&dev_ptzcam_thread_id, NULL, &acquire_ptzcam_frame_thread, dev_ptzcam);
    if(err2){
        std::cout << "failed to create camera thread" << std::endl;
    }

    // acquiring Lidar data
    int err3 = pthread_create(&dev_lidarm8_thread_id, NULL, &acquire_lidarm8_frame_thread, dev_lidarm8);
    if(err3){
        std::cout << "failed to create lidar thread" << std::endl;
    }

    // acquiring Radar data

    // joint the threads
    //pthread_join(dev_imu_thread_id, NULL);
    pthread_join(dev_ptzcam_thread_id, NULL);
    pthread_join(dev_lidarm8_thread_id, NULL);
 EXIT_FUNC
}

void *data_transmit_ptzcam_thread(void *p){
ENTER_FUNC
    // initiate udt
    udp *sys_udp_ptzcam = new udp();
    sys_udp_ptzcam->setTxIP((char*)"127.0.0.1");
    sys_udp_ptzcam->setTxPort(9527);
    //FILE_LINE

    // send Camera data
    ((ptzcam *)p)->cvframe2rawdata();
    //FILE_LINE
    sys_udp_ptzcam->setTxDataSize(((ptzcam *)p)->getrawdatasize());
    //FILE_LINE
    sys_udp_ptzcam->setTxDataW((char*)((ptzcam *)p)->getrawdata());
    //FILE_LINE
    sys_udp_ptzcam->tx2();
    //FILE_LINE
EXIT_FUNC
}

void *data_transmit_m8_thread(void *p){
ENTER_FUNC
    // initiate udp
    udp *sys_udp_m8 = new udp();
    sys_udp_m8->setTxIP((char*)"127.0.0.1");
    sys_udp_m8->setTxPort(9528);

    // send M8 data
    sys_udp_m8->setTxDataSize(((quanergym8 *) p)->getm8datasize());
    
    sys_udp_m8->setTxDataW((char*)((quanergym8 *)p)->getm8data());

    sys_udp_m8->tx2();
    
EXIT_FUNC
}

void data_transmit(imu *dev_imu, ptzcam *dev_ptzcam, quanergym8 *dev_lidarm8){
ENTER_FUNC
    // get time stamp
    // float timestamp = dev_imu->getTIME();
    float timestamp = 0.1;
    unsigned char timestamp_char[4];
    float2byte(timestamp, timestamp_char);

    // time stamp vedio frame
    dev_ptzcam->setrawdatatime(timestamp_char);

    // data transmit threads
    pthread_t sys_udp_ptzcam_id;
    pthread_t sys_udp_lidarm8_id;

    // transmit Camera data
    int err1 = pthread_create(&sys_udp_ptzcam_id, NULL, &data_transmit_ptzcam_thread, dev_ptzcam);
    if(err1){
        std::cout << "failed to create ptz camera data transmit thread" << std::endl;
    }

    // transmit Lidar data
    int err2 = pthread_create(&sys_udp_lidarm8_id, NULL, &data_transmit_m8_thread, dev_lidarm8);
    if(err2){
        std::cout << "failed to create lidar m8 data transmit thread" << std::endl;
    }

    // transmit Radar data

    // joint the threads
    pthread_join(sys_udp_ptzcam_id, NULL);
    pthread_join(sys_udp_lidarm8_id, NULL);
EXIT_FUNC
}

void *test_client_thread(void *p){
ENTER_FUNC

    // initiate device
    imu *dev_imu = new imu();
    ptzcam *dev_ptzcam = new ptzcam();
    dev_ptzcam->setcamip((char*)"192.168.57.61");
    quanergym8 *dev_lidarm8 = new quanergym8(4141, 100, 2, "192.168.57.141");

    // data acquiring
    data_acquire(dev_imu, dev_ptzcam, dev_lidarm8);

    // data transmitting
    data_transmit(dev_imu, dev_ptzcam, dev_lidarm8);

 EXIT_FUNC
    return NULL;
}
