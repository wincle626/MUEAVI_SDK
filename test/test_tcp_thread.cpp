/*
 * main.cpp
 *
 *  Created on: 8 Aug 2018
 *      Author: Yun Wu
 */

#include "test_tcp_thread.hpp"

void *test_tcp_thread(void *p){

    cv::Mat cvframe = cv::imread("./test.jpg", cv::IMREAD_COLOR);
    int imgdataarrsize = cvframe.total()*cvframe.elemSize();
    char *tosenddata = NULL;
    tosenddata = (char*) realloc(tosenddata,imgdataarrsize);
    memcpy((char *)tosenddata,(char *)cvframe.data,imgdataarrsize);
    /*char *tosenddata = NULL;
    tosenddata = (char*) realloc(tosenddata,imgdataarrsize);
    int imgdataarrsize = 1920*1080*3;
    FILE *fp;
    fp = fopen("test.txt","wb");
    fwrite(tosenddata , sizeof(char), imgdataarrsize, fp);
    fclose(fp);
    fp = fopen("test.txt","rb");
    fseek (fp , 0 , SEEK_END);
    long lSize = ftell (fp);
    rewind (fp);
    fread (tosenddata,1,lSize,fp);
    fclose(fp);*/
    int tosendlen = imgdataarrsize;

    tcp *sys_tcp_tx = new tcp(9527,(char*)"127.0.0.1",(char*)tosenddata,tosendlen);
    tcp *sys_tcp_rx = new tcp(9527,(char*)"127.0.0.1",tosendlen);
    std::cout << "rx port number: " << sys_tcp_rx->getrxport() << std::endl;
    std::cout << "tx port number: " << sys_tcp_tx->gettxport() << std::endl;
    std::cout << "rx data size: " << sys_tcp_rx->getrxdatasize() << std::endl;
    std::cout << "tx data size: " << sys_tcp_tx->gettxdatasize() << std::endl;

    int err1 = pthread_create(&sys_tcp_rx->tcpserver_id, NULL, tcp_server_thread, sys_tcp_rx);
    if (err1)
    {
        std::cout << "Thread creation failed : " << strerror(err1) << std::endl;
        exit(err1);
    }
    int err2 = pthread_create(&sys_tcp_tx->tcpclient_id, NULL, tcp_client_thread, sys_tcp_tx);
    if (err2)
    {
        std::cout << "Thread creation failed : " << strerror(err2) << std::endl;
        exit(err2);
    }

    pthread_join(sys_tcp_tx->tcpclient_id, NULL);
    pthread_join(sys_tcp_rx->tcpserver_id, NULL);


    sys_tcp_rx->setrxdatar();
    /*char *data_tx = sys_tcp_tx->gettxdata();
    char *data_rx = sys_tcp_rx->getrxdata();
    for(int i=0;i<tosendlen;i++){
        if(data_tx[i]-data_rx[i]>0.0001){
            std::cout << "data received does not match transmitted !" << std::endl;
            //exit(0);
        }
    }
    std::cout << "data verified !" << std::endl;*/

    int row = cvframe.rows;
    int col = cvframe.cols;
    /*cv::Mat cvframe_tx(row,col,CV_8UC3,cv::Scalar(0, 0, 0));
    memcpy((char *)cvframe_tx.data,(char *)tosenddata,imgdataarrsize);
    cv::namedWindow( "Test Image", cv::WINDOW_AUTOSIZE );
    cv::imshow("Test Image",cvframe_tx);
    cv::waitKey(0);*/

    cv::Mat cvframe_rx(row,col,CV_8UC3,cv::Scalar(0, 0, 0));
    memcpy((char *)cvframe_rx.data,(char *)sys_tcp_rx->getrxdata(),imgdataarrsize);
    cv::imshow("Test Image",cvframe_rx);
    cv::waitKey(0);

    delete sys_tcp_tx;
    delete sys_tcp_rx;
    //dev_ptzcam->capture_release();
    std::cout << "tcp done !" << std::endl;

	return NULL;
}


