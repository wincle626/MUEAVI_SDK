/*
 * urg3d.hpp
 *
 *  Created on: 7 Jun 2018
 *      Author: Yun Wu
 */

#ifndef SRC_HEADERS_URG3D_HPP_
#define SRC_HEADERS_URG3D_HPP_

#include "common.hpp"
#include "debug.hpp"
#include <urg3d_sensor.h>
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
#include <pcl/visualization/cloud_viewer.h>

class urg3d{
public:
	pthread_t RevEthernetPkgThreadId=0;
	pthread_t RevEthernetPkgEnableThreadId=0;
	pthread_t RevEthernetPkgDisableThreadId=0;
	pthread_mutex_t Urg3dpkgAccessMuxid;
	int blockfunctimeout = 2000; // ms
	int frameinterval = 10000; // ms
    int interlacecount = 4; // 1 -> 20 Hz, 4 -> 5 Hz
	bool rangeswith = false;
	bool intensityswith = false;
	bool auxilaryswith = false;
	urg3d();
	urg3d(std::string addr, long int port);
	~urg3d();
    std::string get_connect_address_urg3d();
    urg3d_t *geturg3dstruct();
    int get_connect_port_urg3d();
    int getmeasdatasizeurg3d();
    int getauxidatasizeurg3d();
	void connectsensor();
	void disconnectsensor();
	void setblockfunctimeout(int timeout);
	void setframeinterval(int interval);
	void setrangeswitch(bool flag);
	void setintensityswith(bool flag);
	void setauxilaryswith(bool flag);
    void setconnectipaddress(std::string ip);
    void setconnectport(int p);
	void initsensor();
	void startdatastream();
	void stopdatastream();
	void measuresingledataframe();
	void auxilarysingledataframe();
    void urg3d_pcl_display();
private:
	urg3d_t *urg_urg3d;
	std::string connect_address_urg3d = std::string("10.42.0.10");
	int connect_port_urg3d = 10940;
protected:
	int meas_data_size_urg3d;
	int auxi_data_size_urg3d;
	urg3d_vssp_header_t *meas_header;
	urg3d_vssp_header_t *auxi_header;
	urg3d_measurement_data_t *meas_data_urg3d;
	urg3d_auxilary_data_t* auxi_data_urg3d;
};


#endif /* SRC_HEADERS_URG3D_HPP_ */
