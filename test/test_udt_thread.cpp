/*
 * test_udt_thread.cpp
 *
 *  Created on: 27 Jun 2018
 *      Author: humandrive
 */

#include "test_udt_thread.hpp"


void *test_udt_thread(void *p){

    cv::Mat cvframe = cv::imread("./test.jpg", cv::IMREAD_COLOR);
    int msgsize = cvframe.total()*cvframe.elemSize();
    char *message = NULL;
    message = (char*) realloc(message,msgsize*sizeof(char));
    memcpy(message,(char*)cvframe.data,msgsize);
    //msgsize = std::strlen(message);
    std::cout << "Initial data size: " << msgsize << std::endl;

    pkg *sys_udt_tx = new pkg(9527, (char*)"127.0.0.1", (unsigned char*)message, msgsize);
    pkg *sys_udt_rx = new pkg(9527, (char*)"127.0.0.1", msgsize);

    std::cout << "rx port number: " << sys_udt_rx->getportrx() << std::endl;
    std::cout << "tx port number: " << sys_udt_tx->getporttx() << std::endl;
    int err = pthread_create(&sys_udt_rx->rx_thread_id, NULL, udt_server_thread, sys_udt_rx);
	if (err)
	{
		std::cout << "Thread creation failed : " << strerror(err) << std::endl;
		exit(err);
	}
    err = pthread_create(&sys_udt_tx->tx_thread_id, NULL, udt_client_thread, sys_udt_tx);
	if (err)
	{
		std::cout << "Thread creation failed : " << strerror(err) << std::endl;
		exit(err);
	}
    pthread_join(sys_udt_tx->tx_thread_id, NULL);
    pthread_join(sys_udt_rx->rx_thread_id, NULL);

    std::cout << "pkg done !" << std::endl;

    unsigned char *data_tx = sys_udt_tx->getdatatx();
    unsigned char *data_rx = sys_udt_rx->getdatarx();
    /*for(int i=0;i<msgsize;i++){
        if((data_tx[i]-data_rx[i])>0.01){
            std::cout << "data received does not match transmitted !" << std::endl;
            exit(0);
        }
    }
    std::cout << "data verified !" << std::endl;*/

    cv::Mat cvframe_tx(1080,1920,CV_8UC3,cv::Scalar(0, 0, 0));
    memcpy((char *)cvframe_tx.data,(char *)message,msgsize);
    cv::namedWindow( "Test Image", cv::WINDOW_AUTOSIZE );
    cv::imshow("Test Image",cvframe_tx);
    cv::waitKey(0);
    cv::Mat cvframe_rx(1080,1920,CV_8UC3,cv::Scalar(0, 0, 0));
    memcpy((char *)cvframe_rx.data,(char *)sys_udt_rx->getdatarx(),msgsize);
    cv::imshow("Test Image",cvframe_rx);
    cv::waitKey(0);
    return NULL;

    std::cout << "data displayed !" << std::endl;

    delete sys_udt_rx;
    delete sys_udt_tx;

}


