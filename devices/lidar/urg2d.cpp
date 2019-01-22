/*
 * urg.cpp
 *
 *  Created on: 4 Jun 2018
 *      Author: Yun Wu
 */


#include "urg2d.hpp"


urg2d::urg2d(){
	this->first_degree_urg2d = -45;
	this->last_degree_urg2d = 45;
	this->skip_step_urg2d = 0;
	this->skip_scan_urg2d = 0;
	this->scan_times_urg2d = 123;
	this->connect_address_urg2d = std::string("10.42.0.10");
	this->connect_port_urg2d = 10940;
	this->x_urg2d = NULL;
	this->y_urg2d = NULL;
	this->t_urg2d = NULL;
	this->time_stamp_urg2d = 0;
	this->data_size_urg2d = 0;
	this->scan_data_urg2d = NULL;
}

urg2d::urg2d(std::string addr, long int port){
	this->first_degree_urg2d = -45;
	this->last_degree_urg2d = 45;
	this->skip_step_urg2d = 0;
	this->skip_scan_urg2d = 0;
	this->scan_times_urg2d = 123;
	this->connect_address_urg2d = addr;
	this->connect_port_urg2d = port;
	this->x_urg2d = NULL;
	this->y_urg2d = NULL;
	this->t_urg2d = NULL;
	this->time_stamp_urg2d = 0;
	this->data_size_urg2d = 0;
	this->scan_data_urg2d = NULL;
}

urg2d::~urg2d(){

}

void urg2d::seturg2dfirstdegree(int degree){
	this->first_degree_urg2d = degree;
}

void urg2d::seturg2dlastdegree(int degree){
	this->last_degree_urg2d = degree;
}

void urg2d::seturg2dskipstep(int step){
	this->skip_step_urg2d = step;
}
void urg2d::seturg2dskipscan(int scan){
	this->skip_scan_urg2d = scan;
}

void urg2d::seturg2dscantimes(int times){
	this->scan_times_urg2d = times;
}

void urg2d::seturg2dipaddress(char *ip){
	this->connect_address_urg2d = std::string(ip);
}

void urg2d::seturg2dport(long int port){
	this->connect_port_urg2d = port;
}

void urg2d::urg2dconnect(){
    int ret = urg_open(&this->urg_urg2d, URG_ETHERNET, this->connect_address_urg2d.c_str(), this->connect_port_urg2d);
#ifdef DEBUG
    printf("error code is %d\n", ret);
#endif
}

void urg2d::urg2dconfigscan(){
    int first_step = urg_deg2step(&this->urg_urg2d, this->first_degree_urg2d);
    int last_step = urg_deg2step(&this->urg_urg2d, this->last_degree_urg2d);
    int ret = urg_set_scanning_parameter(&this->urg_urg2d, first_step, last_step, this->skip_step_urg2d);
#ifdef DEBUG
    printf("error code is %d\n", ret);
#endif
}

void urg2d::urg2dstartscan(){
    int ret = urg_start_measurement(&this->urg_urg2d, URG_DISTANCE, this->scan_times_urg2d, this->skip_scan_urg2d);
#ifdef DEBUG
    printf("error code is %d\n", ret);
#endif
}

void urg2d::urg2dstopscan(){
    urg_close(&this->urg_urg2d);
}

void urg2d::urg2dgetdata(){
    this->data_size_urg2d = urg_get_distance(&this->urg_urg2d, this->scan_data_urg2d, &this->time_stamp_urg2d);
}

void urg2d::urg2dparsedata(){
	int i;
    for (i = 0; i < this->data_size_urg2d; ++i) {
        float radian;
        radian = (float)urg_index2rad(&this->urg_urg2d, i);
        this->x_urg2d[i] = this->scan_data_urg2d[i] * cos(radian);
        this->y_urg2d[i] = this->scan_data_urg2d[i] * sin(radian);
    }
}

void *urg2d::revUrg2dEthernetData(){
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif
	pthread_mutex_lock(&this->Urg2dpkgAccessMuxid);
	while(this->urg2dstartstop){
		this->urg2dstartscan();
		this->urg2dgetdata();
#ifdef DEBUG
	std::cout << "loop flag is: " << this->urg2dstartstop << std::endl;
#endif
	}
	pthread_mutex_unlock(&this->Urg2dpkgAccessMuxid);
#ifdef PRINT_FUNC
	EXIT_FUNC
#endif
	return NULL;

}

void urg2d::setEnableurg2drx(bool flag){
	this->urg2dstartstop = flag;
}
void *urg2d::enableurg2drx(){
	pthread_mutex_lock(&this->Urg2dpkgAccessMuxid);
	this->urg2dstartstop = true;
	pthread_mutex_unlock(&this->Urg2dpkgAccessMuxid);
	return NULL;
}
void *urg2d::disableurg2drx(){
	pthread_mutex_lock(&this->Urg2dpkgAccessMuxid);
	this->urg2dstartstop = false;
	pthread_mutex_unlock(&this->Urg2dpkgAccessMuxid);
	return NULL;
}

int urg2d::geturg2dfirstdegree(){
	return this->first_degree_urg2d;
}
int urg2d::geturg2dlastdegree(){
	return this->last_degree_urg2d;
}
int urg2d::geturg2dskipstep(){
	return this->skip_step_urg2d;
}
int urg2d::geturg2dskipscan(){
	return this->skip_scan_urg2d;
}
int urg2d::geturg2dscantimes(){
	return this->scan_times_urg2d;
}

std::string urg2d::geturg2dconnectaddress(){
	return this->connect_address_urg2d;
}

float *urg2d::geturg2dx(){
	return this->x_urg2d;
}

float *urg2d::geturg2dy(){
	return this->y_urg2d;
}

float *urg2d::geturg2dt(){
	return this->t_urg2d;
}

long int urg2d::geturg2dconnetport(){
	return this->connect_port_urg2d;
}

long urg2d::geturg2dtimestamp(){
	return this->time_stamp_urg2d;
}

long urg2d::geturg2ddatasize(){
	return this->data_size_urg2d;
}

long *urg2d::geturg2dscandata(){
	return this->scan_data_urg2d;
}

void *revUrg2dEthernetData_pthread(void *context){
	((urg2d *)context)->revUrg2dEthernetData();
	return NULL;
}
void *enableurg2drx_pthread(void *context){
	((urg2d *)context)->enableurg2drx();
	return NULL;
}
void *disableurg2drx_pthread(void *context){
	((urg2d *)context)->disableurg2drx();
	return NULL;
}
