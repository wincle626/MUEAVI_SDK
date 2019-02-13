/*
 * urg.hpp
 *
 *  Created on: 4 Jun 2018
 *      Author: Yun Wu
 */

#ifndef SRC_HEADERS_URG2D_HPP_
#define SRC_HEADERS_URG2D_HPP_

#include "common.hpp"
#include "debug.hpp"
#include <urg_c/urg_sensor.h>
#include <urg_c/urg_utils.h>

class urg2d{
public:
	pthread_t RevEthernetPkgThreadId=0;
	pthread_t RevEthernetPkgEnableThreadId=0;
	pthread_t RevEthernetPkgDisableThreadId=0;
	pthread_mutex_t Urg2dpkgAccessMuxid;
	bool urg2dstartstop=false;
	urg2d();
	urg2d(std::string addr, long int port);
	~urg2d();
	void seturg2dfirstdegree(int degree);
	void seturg2dlastdegree(int degree);
	void seturg2dskipstep(int step);
	void seturg2dskipscan(int scan);
	void seturg2dscantimes(int times);
	void seturg2dipaddress(char *ip);
	void seturg2dport(long int port);
	void urg2dconnect();
	void urg2dconfigscan();
	void urg2dstartscan();
	void urg2dstopscan();
	void urg2dgetdata();
	void urg2dparsedata();
	void *revUrg2dEthernetData();
	void setEnableurg2drx(bool flag);
	void *enableurg2drx();
	void *disableurg2drx();
	int geturg2dfirstdegree();
	int geturg2dlastdegree();
	int geturg2dskipstep();
	int geturg2dskipscan();
	int geturg2dscantimes();
	std::string geturg2dconnectaddress();
	float *geturg2dx();
	float *geturg2dy();
	float *geturg2dt();
	long int geturg2dconnetport();
	long geturg2dtimestamp();
	long geturg2ddatasize();
	long *geturg2dscandata();
private:
	int first_degree_urg2d;
	int last_degree_urg2d;
	int skip_step_urg2d;
	int skip_scan_urg2d;
	int scan_times_urg2d;
    urg_t urg_urg2d;
	std::string connect_address_urg2d = std::string("10.42.0.10");
	long int connect_port_urg2d = 10940;
protected:
	float *x_urg2d;
	float *y_urg2d;
	float *t_urg2d;
	long time_stamp_urg2d;
	long data_size_urg2d;
    long *scan_data_urg2d;
};
void *revUrg2dEthernetData_pthread(void *context);
void *enableurg2drx_pthread(void *context);
void *disableurg2drx_pthread(void *context);

#endif /* SRC_HEADERS_URG2D_HPP_ */
