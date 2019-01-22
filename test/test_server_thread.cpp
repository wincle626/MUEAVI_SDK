/*
 * test_server_thread.cpp
 *
 *  Created on: 18 July 2018
 *      Author: Yun Wu
 */

#include "test_server_thread.hpp"

void *data_receive_ptzcam_thread(void *p){

    // initiate udt
    pkg *sys_udt_ptzcam = new pkg();
    sys_udt_ptzcam->setportrx(9527);

    // receive Camera data
    sys_udt_ptzcam->setdatasizetx(1280*720*3+4);
    sys_udt_ptzcam->setudtrxhalt(false);
    sys_udt_ptzcam->pkgRx();
    sys_udt_ptzcam->setdatatxr();
    ((ptzcam *)p)->setframewidth(1280);
    ((ptzcam *)p)->setframeheight(720);
    ((ptzcam *)p)->setrawdata(sys_udt_ptzcam->getdatarx());
    ((ptzcam *)p)->rawdata2cvframe();
    ((ptzcam *)p)->test_rawdisplay();
}

void *data_receive_lidarm8_thread(void *p){
    // initiate udt
    pkg *sys_udt_lidarm8 = new pkg();
    sys_udt_lidarm8->setportrx(9528);

    // receive Camera data
    sys_udt_lidarm8->setdatasizetx(3*8*+4);
    sys_udt_lidarm8->setudtrxhalt(false);
    sys_udt_lidarm8->pkgRx();
    sys_udt_lidarm8->setdatatxr();
}

void data_receive(ptzcam *dev_ptzcam){

    // data receive threads
    pthread_t sys_udt_ptzcam_id;
    pthread_t sys_udt_lidarm8_id;

    // receive Camera data
    int err1 = pthread_create(&sys_udt_ptzcam_id, NULL, &data_receive_ptzcam_thread, dev_ptzcam);
    if(err1){
        std::cout << "failed to create camera thread" << std::endl;
    }

    // receive Lidar data
    int err2 = pthread_create(&sys_udt_lidarm8_id, NULL, &data_receive_ptzcam_thread, dev_ptzcam);
    if(err2){
        std::cout << "failed to create camera thread" << std::endl;
    }

    // receive Radar data

    // joint the threads
    pthread_join(sys_udt_ptzcam_id, NULL);

}

void *test_server_thread(void *p){

    // initiate devices
    ptzcam *dev_ptzcam = new ptzcam();

    // data receiving
    data_receive(dev_ptzcam);

    return NULL;
}
