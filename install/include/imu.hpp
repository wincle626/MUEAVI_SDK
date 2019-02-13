/*
 * imu.hpp
 *
 *  Created on: 16 May 2018
 *      Author: Yun Wu
 *  log:
 *  2018-05-16 create imu class
 */

#ifndef SRC_HEADERS_IMU_HPP_
#define SRC_HEADERS_IMU_HPP_

#include "common.hpp"

class imu{
	public:
		pthread_t RevSeriesPkgThreadId=0;
		pthread_t RevSeriesPkgEnableThreadId=0;
		pthread_t RevSeriesPkgDisableThreadId=0;
		pthread_mutex_t IMUpkgAccessMuxid;
		bool startstop=false;
        int done = 0;
		imu();
		imu(char* p, unsigned int b);
		~imu();
		unsigned long unix2gps(unsigned long unixTime);
		unsigned long gps2unix(unsigned long gpsTime);
		float getACCX();
		float getACCY();
		float getACCZ();
		float getGYROX();
		float getGYROY();
		float getGYROZ();
		float getMAGX();
		float getMAGY();
		float getMAGZ();
		float getPRESS();
		float getTEMP();
		float getROLL();
		float getPITCH();
		float getYAW();
		float getLATTI();
		float getLONGI();
		float getALTI();
		float getTIME();
		int getPortFd();
		int updatePKG(unsigned char rx_char);
		int getState();
		unsigned int getBaudrate();
		void setState(int s);
		void openPort();
		void closePort();
		char* getPort();
		char readPort();
		void setPort(char* p);
		void setPortFd(int fd);
		void setBaudrate(unsigned int b);
		void setSeriesPortBaudrate();
		void *revIMUSeriesData();
        void *revIMUFrameData();
		void setEnableimurx(bool flag);
		void *enableimurx();
		void *disableimurx();
	private:
		char* port=(char*)"/dev/ttyUSB0";
		int port_fd=0;
		unsigned int baudrate=256000;
		float accx=0, accy=0, accz=0;
		float gyrox=0, gyroy=0, gyroz=0;
		float magx=0, magy=0, magz=0;
		float press=0, temp=0, roll=0, pitch=0;
		float yaw=0, latti=0, longi=0, alti=0;
		float time=0;
		bool isleap(unsigned long gpsTime);
		unsigned long countleap(unsigned long gpsTime,
								char* dirFlag);
	protected:
		int rx_state=0;
		int crcpass=0;
		int rx_index=0;
		unsigned char checksum=0;
		unsigned char rx_char=0;
		unsigned char imu_pkg[76]={};
		unsigned char imu_data[76]={};
};
void *revIMUSeriesData_pthread(void *context);
void *enableimurx_pthread(void *context);
void *disableimurx_pthread(void *context);

#endif /* SRC_HEADERS_IMU_HPP_ */
