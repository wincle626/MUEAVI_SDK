/*
 * test_udp_thread.cpp
 *
 *  Created on: 21 May 2018
 *      Author: Yun Wu
 */

#include "test_udp_thread.hpp"
#include "file.hpp"

void mat2chararray(cv::Mat image, char *rawdata)
{
   int datasize = image.total() * image.elemSize();
   std::memcpy(rawdata, image.data, datasize*sizeof(char));
}

cv::Mat chararray2mat(char *rawdata,int width,int height)
{
    cv::Mat image = cv::Mat(height,width,CV_8UC3,rawdata).clone(); // make a copy
    return image;
}

void cvmatrawdata(cv::Mat cvframe, char *rawdata){
    std::cout << "image size: " << cvframe.rows << "x" << cvframe.cols << std::endl;
    for (int i=0; i<cvframe.rows; i++)
    {
        for (int j=0; j<cvframe.cols; j++)
        {
            cv::Vec3b intensity = cvframe.at<cv::Vec3b>(i, j);
            char b = intensity.val[0]-128;
            char g = intensity.val[1]-128;
            char r = intensity.val[2]-128;
            rawdata[i*cvframe.cols+j*3] = b; // Blue
            rawdata[i*cvframe.cols+j*3+1] = g; // Green
            rawdata[i*cvframe.cols+j*3+2] = r; // Red
            //std::cout << b << g << r << std::endl;
        }
    }
}

void *test_udp_thread(void *p){

    /*ptzcam *dev_ptzcam = new ptzcam();
    dev_ptzcam->capture_cv();
    dev_ptzcam->capture_cvframe();
    cv::Mat cvframe = dev_ptzcam->getcvframe();*/
    cv::Mat cvframe = cv::imread("./test.jpg", cv::IMREAD_COLOR);
    int imgdataarrsize = cvframe.total()*cvframe.elemSize();
    char *tosenddata = NULL;
    tosenddata = (char*) realloc(tosenddata,imgdataarrsize);
    memcpy((char *)tosenddata,(char *)cvframe.data,imgdataarrsize);
    /*cvmatrawdata(cvframe, tosenddata);
    FILE *fp;
    fp = fopen("test.txt","wb");
    fwrite(tosenddata , sizeof(char), imgdataarrsize, fp);
    fclose(fp);
    fp = fopen("test.txt","rb");
    fseek (fp , 0 , SEEK_END);
    long lSize = ftell (fp);
    rewind (fp);
    fread (tosenddata,1,lSize,fp);
    fclose(fp);
    int tosendlen = std::strlen(tosenddata);*/
    int tosendlen = imgdataarrsize;
    //int tosendlen = lSize;
    std::cout << "total element number: " << cvframe.total() << std::endl;
    std::cout << "element number: " << cvframe.elemSize() << std::endl;
    std::cout << "to send data array length: " << tosendlen << std::endl;
    // std::cout << "Tx data: " << tosenddata << std::endl;

    udp *sys_udp_tx = new udp(9527,(char*)"127.0.0.1",(char*)tosenddata,tosendlen);
    udp *sys_udp_rx = new udp(9527,(char*)"127.0.0.1",tosendlen);
    std::cout << "rx port number: " << sys_udp_rx->getRxPort() << std::endl;
    std::cout << "tx port number: " << sys_udp_tx->getTxPort() << std::endl;
    std::cout << "rx data size: " << sys_udp_rx->getRxDataSize() << std::endl;
    std::cout << "tx data size: " << sys_udp_tx->getTxDataSize() << std::endl;

    //sys_udp_rx->setServerOnOff(true);
    int err1 = pthread_create(&sys_udp_rx->udpserver_id, NULL, udp_server_thread, sys_udp_rx);
    if (err1)
    {
        std::cout << "Thread creation failed : " << strerror(err1) << std::endl;
        exit(err1);
    }
    int err2 = pthread_create(&sys_udp_tx->udpclient_id, NULL, udp_client_thread, sys_udp_tx);
    if (err2)
    {
        std::cout << "Thread creation failed : " << strerror(err2) << std::endl;
        exit(err2);
    }

    pthread_join(sys_udp_tx->udpclient_id, NULL);
    pthread_join(sys_udp_rx->udpserver_id, NULL);

    //std::cout << "data received: " << sys_udp_rx->getRxData() << std::endl;

    char *data_tx = sys_udp_tx->getTxData();
    sys_udp_rx->setRxDataR();
    char *data_rx = sys_udp_rx->getRxData();
    for(int i=0;i<tosendlen;i++){
        if(data_tx[i]-data_rx[i]>0.0001){
            std::cout << "data received does not match transmitted !" << std::endl;
            //exit(0);
        }
    }
    std::cout << "data verified !" << std::endl;

    int row = cvframe.rows;
    int col = cvframe.cols;
    cv::Mat cvframe_tx(row,col,CV_8UC3,cv::Scalar(0, 0, 0));
    memcpy((char *)cvframe_tx.data,(char *)tosenddata,imgdataarrsize);
    cv::namedWindow( "Test Image", cv::WINDOW_AUTOSIZE );
    cv::imshow("Test Image",cvframe_tx);
    cv::waitKey(0);

    cv::Mat cvframe_rx(row,col,CV_8UC3,cv::Scalar(0, 0, 0));
    memcpy((char *)cvframe_rx.data,(char *)sys_udp_rx->getRxData(),imgdataarrsize);
    cv::imshow("Test Image",cvframe_rx);
    cv::waitKey(0);

    delete sys_udp_tx;
    delete sys_udp_rx;
    //dev_ptzcam->capture_release();
    std::cout << "udp done !" << std::endl;

    return NULL;
}


/*int main(int argc, char** argv){

    pthread_t udp_thread_id;
    int err3 = pthread_create(&udp_thread_id, NULL, &test_udp_thread, NULL);
    if (err3)
    {
        std::cout << "Thread creation failed : " << strerror(err3) << std::endl;
        exit(err3);
    }
    pthread_join(udp_thread_id, NULL);
    return 0;
}*/
