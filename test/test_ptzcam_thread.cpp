/*
 * test_ptzcam_thread.cpp
 *
 *  Created on: 21 May 2018
 *      Author: Yun Wu
 */

#include "test_ptzcam_thread.hpp"

/*#define PTZ_DISPLAY_TEST ptzcam *dev_ptzcam = new ptzcam();\
	int err = pthread_create(&dev_ptzcam->PTZDisplayThreadID,\
			NULL, display_pthread, dev_ptzcam);\
	if (err)\
	{\
		std::cout << "Thread creation failed : " << strerror(err) << std::endl;\
		exit(err);\
	}\
	err = pthread_create(&dev_ptzcam->PTZControlThreadID,\
			NULL, ptz_pthread, dev_ptzcam);\
	if (err)\
	{\
		std::cout << "Thread creation failed : " << strerror(err) << std::endl;\
		exit(err);\
	}\
    pthread_join(dev_ptzcam->PTZControlThreadID, NULL);\
    pthread_join(dev_ptzcam->PTZDisplayThreadID, NULL);\
	delete dev_ptzcam;\*/

void *test_ptzcam_thread(void *p){

	//PTZ_DISPLAY_TEST
	ptzcam *dev_ptzcam = new ptzcam(std::string("ADMIN"),
									std::string("Qwer1234"),
									std::string("192.168.57.100"));
    int err1 = pthread_create(&dev_ptzcam->PTZTestDisplayThreadID,
            NULL, testdisplay_pthread, dev_ptzcam);
	if (err1)
	{
		std::cout << "Thread creation failed : " << strerror(err1) << std::endl;
		exit(err1);
	}
	int err2 = pthread_create(&dev_ptzcam->PTZControlThreadID,
			NULL, ptz_pthread, dev_ptzcam);
	if (err2)
	{
		std::cout << "Thread creation failed : " << strerror(err2) << std::endl;
		exit(err2);
	}
	pthread_join(dev_ptzcam->PTZControlThreadID, NULL);
    pthread_join(dev_ptzcam->PTZTestDisplayThreadID, NULL);
	delete dev_ptzcam;

	std::cout << "ptz done !" << std::endl;
	return NULL;
}


/*int main(int argc, char** argv){
    pthread_t ptz_thread_id;
    int err2 = pthread_create(&ptz_thread_id, NULL, &test_ptzcam_thread, NULL);
    if (err2)
    {
        std::cout << "Thread creation failed : " << strerror(err2) << std::endl;
        exit(err2);
    }
    pthread_join(ptz_thread_id, NULL);
    return 0;
}*/
