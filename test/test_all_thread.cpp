/*
 * test.cpp
 *
 *  Created on: 16 May 2018
 *      Author: Yun Wu
 */

#include "../headers/common.hpp"

#include "test_imu_thread.hpp"
#include "test_lidar_thread.hpp"
#include "test_ptzcam_thread.hpp"
#include "test_radar_thread.hpp"
#include "test_tcp_thread.hpp"
#include "test_udp_thread.hpp"
#include "test_udt_thread.hpp"
#include "test_nas_thread.hpp"
#include "test_client_thread.hpp"
#include "test_server_thread.hpp"

/*  0:imu, 
    1:ptz, 
    2:udp, 
    3:tcp, 
    4:udt, 
    5:urg2d, 
    6:urg3d, 
    7:radar, 
    8:nas, 
    9:m8, 
    10:client, 
    11:server, 
    12:client-server
*/

#define TEST_CASE 9

int main(int argc, char** argv){

#if TEST_CASE==0
    pthread_t imu_thread_id;
#elif TEST_CASE==1
    pthread_t ptz_thread_id;
#elif TEST_CASE==2
    pthread_t udp_thread_id;
#elif TEST_CASE==3
    pthread_t tcp_thread_id;
#elif TEST_CASE==4
    pthread_t udt_thread_id;
#elif TEST_CASE==5
    pthread_t urg2d_thread_id;
#elif TEST_CASE==6
    pthread_t urg3d_thread_id;
#elif TEST_CASE==7
    pthread_t radar_thread_id;
#elif TEST_CASE==8
    pthread_t nas_thread_id;
#elif TEST_CASE==9
    pthread_t m8_thread_id;
#elif TEST_CASE==10
    pthread_t client_thread_id;
#elif TEST_CASE==11
    pthread_t server_thread_id;
#elif TEST_CASE==12
    pthread_t client_thread_id;
    pthread_t server_thread_id;
#endif


#if TEST_CASE==0
    int err0 = pthread_create(&imu_thread_id, NULL, &test_imu_thread, NULL);
    if (err0)
	{
        std::cout << "Thread creation failed : " << strerror(err0) << std::endl;
        exit(err0);
    }
#elif TEST_CASE==1
    int err1 = pthread_create(&ptz_thread_id, NULL, &test_ptzcam_thread, NULL);
    if (err1)
	{
        std::cout << "Thread creation failed : " << strerror(err1) << std::endl;
        exit(err1);
    }
#elif TEST_CASE==2
    int err2 = pthread_create(&udp_thread_id, NULL, &test_udp_thread, NULL);
    if (err2)
	{
        std::cout << "Thread creation failed : " << strerror(err2) << std::endl;
        exit(err2);
    }
#elif TEST_CASE==3
    int err3 = pthread_create(&tcp_thread_id, NULL, &test_tcp_thread, NULL);
    if (err3)
    {
        std::cout << "Thread creation failed : " << strerror(err3) << std::endl;
        exit(err3);
    }
#elif TEST_CASE==4
    int err4 = pthread_create(&udt_thread_id, NULL, &test_udt_thread, NULL);
    if (err4)
    {
        std::cout << "Thread creation failed : " << strerror(err4) << std::endl;
        exit(err4);
    }
#elif TEST_CASE==5
    int err5 = pthread_create(&urg2d_thread_id, NULL, &test_urg2d_thread, NULL);
    if (err5)
	{
        std::cout << "Thread creation failed : " << strerror(err5) << std::endl;
        exit(err5);
    }
#elif TEST_CASE==6
    int err6 = pthread_create(&urg3d_thread_id, NULL, &test_urg3d_thread, NULL);
    if (err6)
    {
        std::cout << "Thread creation failed : " << strerror(err6) << std::endl;
        exit(err6);
    }
#elif TEST_CASE==7
    int err7 = pthread_create(&radar_thread_id, NULL, &test_radar_thread, NULL);
    if (err7)
    {
        std::cout << "Thread creation failed : " << strerror(err7) << std::endl;
        exit(err7);
    }
#elif TEST_CASE==8
	int err8 = pthread_create(&nas_thread_id, NULL, test_nas_thread, NULL);
	if(err8){
		std::cout << "failed to create thread to test the radar data acquiring" << std::endl;
	}
	pthread_join(nas_thread_id, NULL);
#elif TEST_CASE==9
	int err9 = pthread_create(&m8_thread_id, NULL, test_m8_thread, NULL);
	if(err9){
		std::cout << "failed to create thread to test the M8 data acquiring" << std::endl;
	}
	pthread_join(m8_thread_id, NULL);
#elif TEST_CASE==10
    int err10 = pthread_create(&client_thread_id, NULL, &test_client_thread, NULL);
    if (err10)
    {
        std::cout << "Thread creation failed : " << strerror(err10) << std::endl;
        exit(err10);
    }
#elif TEST_CASE==11
    int err11 = pthread_create(&server_thread_id, NULL, &test_server_thread, NULL);
    if (err11)
    {
        std::cout << "Thread creation failed : " << strerror(err11) << std::endl;
        exit(err11);
    }
#elif TEST_CASE==12
    int err12 = pthread_create(&client_thread_id, NULL, &test_client_thread, NULL);
    if (err12)
    {
        std::cout << "Thread creation failed : " << strerror(err12) << std::endl;
        exit(err12);
    }
    err12 = pthread_create(&server_thread_id, NULL, &test_server_thread, NULL);
    if (err12)
    {
        std::cout << "Thread creation failed : " << strerror(err12) << std::endl;
        exit(err12);
    }
#endif

#if TEST_CASE==0
    pthread_join(imu_thread_id, NULL);
#elif TEST_CASE==1
    pthread_join(ptz_thread_id, NULL);
#elif TEST_CASE==2
    pthread_join(udp_thread_id, NULL);
#elif TEST_CASE==3
    pthread_join(tcp_thread_id, NULL);
#elif TEST_CASE==4
    pthread_join(udt_thread_id, NULL);
#elif TEST_CASE==5
    pthread_join(urg2d_thread_id, NULL);
#elif TEST_CASE==6
    pthread_join(urg3d_thread_id, NULL);
#elif TEST_CASE==7
    pthread_join(radar_thread_id, NULL);
#elif TEST_CASE==8
    pthread_join(nas_thread_id, NULL);
#elif TEST_CASE==9
    pthread_join(m8_thread_id, NULL);
#elif TEST_CASE==10
    pthread_join(client_thread_id, NULL);
#elif TEST_CASE==11
    pthread_join(server_thread_id, NULL);
#elif TEST_CASE==12
    pthread_join(client_thread_id, NULL);
    pthread_join(server_thread_id, NULL);
#endif

	return 0;
}

