/*
 * imu.cpp
 *
 *  Created on: 16 May 2018
 *      Author: Yun Wu
 *  log:
 *  2018-05-16 add functions for accessing gps data in multi-threading
 */

#include "imu.hpp"

#include "debug.hpp"
#include "mathformat.hpp"

// #define CUSTOM_BAUD_RATE
#define CUSTOM_BAUD_RATE_ARBITRARY
#ifdef CUSTOM_BAUD_RATE
#include <termios.h>
#endif
#ifdef CUSTOM_BAUD_RATE_ARBITRARY
#include "/usr/include/asm-generic/termbits.h"
#endif

unsigned long leap[18] = {46828800, 78364801, 109900802,
			 173059203, 252028804, 315187205,
			 346723206, 393984007, 425520008,
			 457056009, 504489610, 551750411,
			 599184012, 820108813, 914803214,
			 1025136015, 1119744016, 1167264017};

// constructor
imu::imu(){
	this->port = (char*)"";
	this->baudrate = 256000;
	this->rx_state = 0;
	this->rx_index = 0;
    this->done = 0;
	this->checksum = 0x00;
	this->rx_char = 'D';
	this->imu_pkg[0] = 0x00;
	this->imu_data[0] = 0x00;
	this->crcpass = 0;
	this->port_fd = open(this->port, O_RDONLY | O_NONBLOCK);
	this->accx = 0.0; this->accy = 0.0; this->accz = 0.0;
	this->gyrox = 0.0; this->gyroy = 0.0; this->gyroz = 0.0;
	this->magx = 0.0; this->magy = 0.0; this->magz = 0.0;
	this->press = 0.0; this->temp = 0.0; this->roll = 0.0; this->pitch = 0.0;
	this->yaw = 0.0; this->latti = 0.0; this->longi = 0.0; this->alti = 0.0;
	this->time = 0.0;
	this->RevSeriesPkgThreadId = 0;
	this->RevSeriesPkgEnableThreadId = 0;
	this->RevSeriesPkgDisableThreadId = 0;
	this->startstop = false;
#ifdef PRINT_DEFAUT_SETTING
	std::cout << "Port: " << this->port << std::endl;
	std::cout << "Baudrate: " << this->baudrate << std::endl;
#endif
}
imu::imu(char* p, unsigned int b){
	this->port = p;
	this->baudrate = b;
	this->rx_state = 0;
	this->rx_index = 0;
    this->done = 0;
	this->checksum = 0x00;
	this->rx_char = 'D';
	this->imu_pkg[0] = 0x00;
	this->crcpass = 0;
	this->port_fd = open(this->port, O_RDONLY | O_NONBLOCK);
	this->accx = 0.0; this->accy = 0.0; this->accz = 0.0;
	this->gyrox = 0.0; this->gyroy = 0.0; this->gyroz = 0.0;
	this->magx = 0.0; this->magy = 0.0; this->magz = 0.0;
	this->press = 0.0; this->temp = 0.0; this->roll = 0.0; this->pitch = 0.0;
	this->yaw = 0.0; this->latti = 0.0; this->longi = 0.0; this->alti = 0.0;
	this->time = 0.0;
	this->RevSeriesPkgThreadId = 0;
	this->RevSeriesPkgEnableThreadId = 0;
	this->RevSeriesPkgDisableThreadId = 0;
	this->startstop = false;
#ifdef PRINT_DEFAUT_SETTING
	std::cout << "Port: " << this->port << std::endl;
	std::cout << "Baudrate: " << this->baudrate << std::endl;
#endif
}

// destructor
imu::~imu(){

}


// update and return the gps acceleration X in float
float imu::getACCX(){
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif
    pthread_mutex_lock(&this->IMUpkgAccessMuxid);
	/*unsigned int bytes = ((this->imu_data[3]<<24)
				| (this->imu_data[2]<<16)
				| (this->imu_data[1]<<8)
				| this->imu_data[0]);
	this->accx = *(float *) & bytes;*/
	this->accx = byte2float(&this->imu_data[0]);
    pthread_mutex_unlock(&this->IMUpkgAccessMuxid);
#ifdef PRINT_FUNC
	EXIT_FUNC
#endif
	return this->accx;
}

// update and return the gps acceleration Y
float imu::getACCY(){
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif
    pthread_mutex_lock(&this->IMUpkgAccessMuxid);
	/*unsigned int bytes = ((this->imu_data[7]<<24)
				| (this->imu_data[6]<<16)
				| (this->imu_data[5]<<8)
				| this->imu_data[4]);
	this->accy = *(float *) & bytes;*/
	this->accx = byte2float(&this->imu_data[4]);
    pthread_mutex_unlock(&this->IMUpkgAccessMuxid);
#ifdef PRINT_FUNC
	EXIT_FUNC
#endif
	return this->accy;
}

// update and return the gps acceleration Z
float imu::getACCZ(){
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif
    pthread_mutex_lock(&this->IMUpkgAccessMuxid);
	/*unsigned int bytes = ((this->imu_data[11]<<24)
				| (this->imu_data[10]<<16)
				| (this->imu_data[9]<<8)
				| this->imu_data[8]);
	this->accz = *(float *) & bytes;*/
	this->accx = byte2float(&this->imu_data[8]);
    pthread_mutex_unlock(&this->IMUpkgAccessMuxid);
#ifdef PRINT_FUNC
	EXIT_FUNC
#endif
	return this->accz;
}

// update and return the gps gyro X
float imu::getGYROX(){
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif
    pthread_mutex_lock(&this->IMUpkgAccessMuxid);
	/*unsigned int bytes = ((this->imu_data[15]<<24)
				| (this->imu_data[14]<<16)
				| (this->imu_data[13]<<8)
				| this->imu_data[12]);
	this->gyrox = *(float *) & bytes;*/
	this->accx = byte2float(&this->imu_data[12]);
    pthread_mutex_unlock(&this->IMUpkgAccessMuxid);
#ifdef PRINT_FUNC
	EXIT_FUNC
#endif
	return this->gyrox;
}

// update and return the gps gyro Y
float imu::getGYROY(){
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif
    pthread_mutex_lock(&this->IMUpkgAccessMuxid);
	unsigned int bytes = ((this->imu_data[19]<<24)
				| (this->imu_data[18]<<16)
				| (this->imu_data[17]<<8)
				| this->imu_data[16]);
	this->gyroy = *(float *) & bytes;
    pthread_mutex_unlock(&this->IMUpkgAccessMuxid);
#ifdef PRINT_FUNC
	EXIT_FUNC
#endif
	return this->gyroy;
}

// update and return the gps gyro Z
float imu::getGYROZ(){
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif
    pthread_mutex_lock(&this->IMUpkgAccessMuxid);
	/*unsigned int bytes = ((this->imu_data[23]<<24)
				| (this->imu_data[22]<<16)
				| (this->imu_data[21]<<8)
				| this->imu_data[20]);
	this->gyroz = *(float *) & bytes;*/
	this->accx = byte2float(&this->imu_data[20]);
    pthread_mutex_unlock(&this->IMUpkgAccessMuxid);
#ifdef PRINT_FUNC
	EXIT_FUNC
#endif
	return this->gyroz;
}

// update and return the gps magnitude X
float imu::getMAGX(){
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif
    pthread_mutex_lock(&this->IMUpkgAccessMuxid);
	/*unsigned int bytes = ((this->imu_data[27]<<24)
				| (this->imu_data[26]<<16)
				| (this->imu_data[25]<<8)
				| this->imu_data[24]);
	this->magx = *(float *) & bytes;*/
	this->accx = byte2float(&this->imu_data[24]);
    pthread_mutex_unlock(&this->IMUpkgAccessMuxid);
#ifdef PRINT_FUNC
	EXIT_FUNC
#endif
	return this->magx;
}

// update and return the gps magnitude Y
float imu::getMAGY(){
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif
    pthread_mutex_lock(&this->IMUpkgAccessMuxid);
	/*unsigned int bytes = ((this->imu_data[31]<<24)
				| (this->imu_data[30]<<16)
				| (this->imu_data[29]<<8)
				| this->imu_data[28]);
	this->magy = *(float *) & bytes;*/
	this->accx = byte2float(&this->imu_data[28]);
    pthread_mutex_unlock(&this->IMUpkgAccessMuxid);
#ifdef PRINT_FUNC
	EXIT_FUNC
#endif
	return this->magy;
}

// update and return the gps magnitude Z
float imu::getMAGZ(){
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif
    pthread_mutex_lock(&this->IMUpkgAccessMuxid);
	/*unsigned int bytes = ((this->imu_data[35]<<24)
				| (this->imu_data[34]<<16)
				| (this->imu_data[33]<<8)
				| this->imu_data[32]);
	this->magz = *(float *) & bytes;*/
	this->accx = byte2float(&this->imu_data[32]);
    pthread_mutex_unlock(&this->IMUpkgAccessMuxid);
#ifdef PRINT_FUNC
	EXIT_FUNC
#endif
	return this->magz;
}

// update and return the gps pressure
float imu::getPRESS(){
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif
    pthread_mutex_lock(&this->IMUpkgAccessMuxid);
	/*unsigned int bytes = ((this->imu_data[39]<<24)
				| (this->imu_data[38]<<16)
				| (this->imu_data[37]<<8)
				| this->imu_data[36]);
	this->press = *(float *) & bytes;*/
	this->accx = byte2float(&this->imu_data[36]);
    pthread_mutex_unlock(&this->IMUpkgAccessMuxid);
#ifdef PRINT_FUNC
	EXIT_FUNC
#endif
	return this->press;
}

// update and return the gps temperature
float imu::getTEMP(){
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif
    pthread_mutex_lock(&this->IMUpkgAccessMuxid);
	/*unsigned int bytes = ((this->imu_data[43]<<24)
				| (this->imu_data[42]<<16)
				| (this->imu_data[41]<<8)
				| this->imu_data[40]);
	this->temp = *(float *) & bytes;*/
	this->accx = byte2float(&this->imu_data[40]);
    pthread_mutex_unlock(&this->IMUpkgAccessMuxid);
#ifdef PRINT_FUNC
	EXIT_FUNC
#endif
	return this->temp;
}

// update and return the gps roll
float imu::getROLL(){
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif
    pthread_mutex_lock(&this->IMUpkgAccessMuxid);
	/*unsigned int bytes = ((this->imu_data[47]<<24)
				| (this->imu_data[46]<<16)
				| (this->imu_data[45]<<8)
				| this->imu_data[44]);
	this->roll = *(float *) & bytes;*/
	this->accx = byte2float(&this->imu_data[44]);
    pthread_mutex_unlock(&this->IMUpkgAccessMuxid);
#ifdef PRINT_FUNC
	EXIT_FUNC
#endif
	return this->roll;
}

// update and return the gps pitch
float imu::getPITCH(){
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif
    pthread_mutex_lock(&this->IMUpkgAccessMuxid);
	/*unsigned int bytes = ((this->imu_data[51]<<24)
				| (this->imu_data[50]<<16)
				| (this->imu_data[49]<<8)
				| this->imu_data[48]);
	this->pitch = *(float *) & bytes;*/
	this->accx = byte2float(&this->imu_data[48]);
    pthread_mutex_unlock(&this->IMUpkgAccessMuxid);
#ifdef PRINT_FUNC
	EXIT_FUNC
#endif
	return this->pitch;
}

// update and return the gps yaw
float imu::getYAW(){
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif
    pthread_mutex_lock(&this->IMUpkgAccessMuxid);
	/*unsigned int bytes = ((this->imu_data[55]<<24)
				| (this->imu_data[54]<<16)
				| (this->imu_data[53]<<8)
				| this->imu_data[52]);
	this->yaw = *(float *) & bytes;*/
	this->accx = byte2float(&this->imu_data[52]);
    pthread_mutex_unlock(&this->IMUpkgAccessMuxid);
#ifdef PRINT_FUNC
	EXIT_FUNC
#endif
	return this->yaw;
}

// update and return the gps latitude
float imu::getLATTI(){
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif
    pthread_mutex_lock(&this->IMUpkgAccessMuxid);
	/*unsigned int bytes = ((this->imu_data[59]<<24)
				| (this->imu_data[58]<<16)
				| (this->imu_data[57]<<8)
				| this->imu_data[56]);
	this->latti = *(float *) & bytes;*/
	this->accx = byte2float(&this->imu_data[56]);
    pthread_mutex_unlock(&this->IMUpkgAccessMuxid);
#ifdef PRINT_FUNC
	EXIT_FUNC
#endif
	return this->latti;
}

// update and return the gps longitude
float imu::getLONGI(){
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif
    pthread_mutex_lock(&this->IMUpkgAccessMuxid);
	/*unsigned int bytes = ((this->imu_data[63]<<24)
				| (this->imu_data[62]<<16)
				| (this->imu_data[61]<<8)
				| this->imu_data[60]);
	this->longi = *(float *) & bytes;*/
	this->accx = byte2float(&this->imu_data[60]);
    pthread_mutex_unlock(&this->IMUpkgAccessMuxid);
#ifdef PRINT_FUNC
	EXIT_FUNC
#endif
	return this->longi;
}

// update and return the gps altitude
float imu::getALTI(){
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif
    pthread_mutex_lock(&this->IMUpkgAccessMuxid);
	/*unsigned int bytes = ((this->imu_data[67]<<24)
				| (this->imu_data[66]<<16)
				| (this->imu_data[65]<<8)
				| this->imu_data[64]);
	this->alti = *(float *) & bytes;*/
	this->accx = byte2float(&this->imu_data[64]);
    pthread_mutex_unlock(&this->IMUpkgAccessMuxid);
#ifdef PRINT_FUNC
	EXIT_FUNC
#endif
	return this->alti;
}

// update and return the gps time
float imu::getTIME(){
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif
    pthread_mutex_lock(&this->IMUpkgAccessMuxid);
	/*unsigned int bytes = ((this->imu_data[71]<<24)
				| (this->imu_data[70]<<16)
				| (this->imu_data[69]<<8)
				| this->imu_data[68]);
	this->time = *(float *) & bytes;*/
	this->accx = byte2float(&this->imu_data[68]);
    pthread_mutex_unlock(&this->IMUpkgAccessMuxid);
#ifdef PRINT_FUNC
	EXIT_FUNC
#endif
	return this->time;
}

// open the port
void imu::openPort(){
	this->port_fd  = open(this->getPort(), O_RDONLY | O_NONBLOCK);
}

// close the port
void imu::closePort(){
	close(this->port_fd);
}

// get the port file id
int imu::getPortFd(){
	return this->port_fd;
}

// get the reading state
int imu::getState(){
	return this->rx_state;
}

// set the reading state
void imu::setState(int s){
	this->rx_state = s;
}

// get the port name string
char* imu::getPort(){
	return this->port;
}

// read a char from the port
char imu::readPort(){
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif
	char c = 0x0D;
#ifdef DEBUG
	std::cout << "port is: " << this->getPort() << std::endl;
	std::cout << "port file id is: " << this->getPortFd() << std::endl;
	std::cout << "baud rate is: " << this->getBaudrate() << std::endl;
#endif
    ssize_t num = read(this->getPortFd(),&c,1);
    if(num!=1){
        return this->rx_char;
    }
	this->rx_char = c;
#ifdef DEBUG
		std::cout << "received char is " << c << std::endl;
#endif
#ifdef PRINT_FUNC
	EXIT_FUNC
#endif
	return this->rx_char;
}

// get the baud rate
unsigned int imu::getBaudrate(){
	return this->baudrate;
}

// set the series port
void imu::setPort(char* p){
	this->port = p;
}

// set the series file id
void imu::setPortFd(int fd){
	this->port_fd = fd;
}

// set the baudrate of series port
void imu::setBaudrate(unsigned int b){
	this->baudrate = b;
}

// update the package vector with received char
int imu::updatePKG(unsigned char rx_char){
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif
	int i;
	unsigned char crc;
#ifdef DEBUG
	std::cout << "receive state is: " << this->rx_state << std::endl;
	std::cout << "receive index is: " << this->rx_index << std::endl;
	std::cout << "receive char is: " << rx_char << std::endl;
#endif
	switch(this->rx_state){
		case 0:
			if(rx_char==0xA0){
				this->rx_state = 1;
				break;
			}
		case 1:
			if(rx_char==0xA1){
				this->rx_state = 2;
				this->rx_index = 0;
				break;
			}else if(rx_char==0xA2){
				this->rx_state = 3;
				break;
			}else{
				this->rx_state = 0;
				break;
			}
		case 2:
			if(this->rx_index<73){
				this->imu_pkg[this->rx_index] = rx_char;
				this->rx_index ++;
				break;
			}else{
				this->rx_index = 0;
				this->imu_pkg[73] = rx_char;
				this->rx_state = 0;
				unsigned char header[2] = {0xA0, 0xA1};
				crc = header[0]^header[1];
				for(i=0;i<72;i++){
					crc = crc ^ this->imu_pkg[i];
				}
				if(crc==this->imu_pkg[72]){
					this->crcpass = 1;
					for(int j=0;j<76;j++)
						this->imu_data[j] = this->imu_pkg[j];
					//printf("CRC passed !\n");
                    this->done = 1;
				}else{
					this->crcpass = 0;
					//printf("CRC failed !\n");
				}
				this->checksum = crc;
				break;
			}
		case 3:
			if(this->rx_index<73){
				this->imu_pkg[this->rx_index] = rx_char;
				this->rx_index ++;
				break;
			}else{
				this->rx_index = 0;
				this->imu_pkg[73] = rx_char;
				// rx_state = 0;
				break;
			}
		default:
			this->crcpass = 0;
			printf("Wrong state ! %d\n",this->rx_state);
			exit(0);
			break;
	}
#ifdef PRINT_FUNC
	EXIT_FUNC
#endif
	return this->rx_index;
}


// Test to see if a GPS second is a leap second
bool imu::isleap(unsigned long gpsTime){
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif
	bool isLeap = false;
	int i;
	for(i=0;i<18;i++){
		if(gpsTime == leap[i]){
			isLeap = true;
		}
	}
#ifdef PRINT_FUNC
	EXIT_FUNC
#endif
	return isLeap;
}

// Count number of leap seconds that have passed
unsigned long imu::countleap(unsigned long gpsTime,
						char* dirFlag){
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif
	unsigned long nleap = 0;
	int i;
	for(i=0;i<18;i++){
		if(!strcmp("unix2gps", dirFlag)){
            if (gpsTime >= leap[i] - i) {
               nleap++;
            }
		}else if (!strcmp("gps2unix", dirFlag)) {
            if (gpsTime >= leap[i]) {
               nleap++;
            }
		}
	}
#ifdef PRINT_FUNC
	EXIT_FUNC
#endif
	return nleap;
}


// Convert Unix Time to GPS Time
unsigned long imu::unix2gps(unsigned long unixTime){
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif
    // Add offset in seconds
	unsigned int isLeap = 0;
	unsigned long gpsTime = 0;
	unsigned long nleap = 0;
    if (fmod(unixTime, 1) != 0) {
       unixTime = unixTime - 0.5;
       isLeap = 1;
    } else {
       isLeap = 0;
    }
    gpsTime = unixTime - 315964800;
    nleap = countleap(gpsTime, (char*)"unix2gps");
    gpsTime = gpsTime + nleap + isLeap;
#ifdef PRINT_FUNC
	EXIT_FUNC
#endif
    return gpsTime;
}

// Convert GPS Time to Unix Time
unsigned long imu::gps2unix(unsigned long gpsTime){
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif
    // Add offset in seconds
    unsigned long unixTime = gpsTime + 315964800;
    unsigned long nleap = countleap(gpsTime, (char*)"gps2unix");
    unixTime = unixTime - nleap;
    if (isleap(gpsTime)) {
       unixTime = unixTime + 0.5;
    }
#ifdef PRINT_FUNC
	EXIT_FUNC
#endif
    return unixTime;
}

/*#define  B50	0000001
#define  B75	0000002
#define  B110	0000003
#define  B134	0000004
#define  B150	0000005
#define  B200	0000006
#define  B300	0000007
#define  B600	0000010
#define  B1200	0000011
#define  B1800	0000012
#define  B2400	0000013
#define  B4800	0000014
#define  B9600	0000015
#define  B19200	0000016
#define  B38400	0000017
#define    B57600 0010001
#define   B115200 0010002
#define   B230400 0010003
#define   B460800 0010004
#define   B500000 0010005
#define   B576000 0010006
#define   B921600 0010007
#define  B1000000 0010010
#define  B1152000 0010011
#define  B1500000 0010012
#define  B2000000 0010013
#define  B2500000 0010014
#define  B3000000 0010015
#define  B3500000 0010016
#define  B4000000 0010017*/
// set the baud rate to the port physically
void imu::setSeriesPortBaudrate(){
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif
	// Open serial port
	int fd = open(getPort(), O_RDONLY | O_NONBLOCK);
	if(fd<0){
		printf("Error %d %s! cannot open port %s\n",
				errno, strerror(errno), getPort());
		exit(0);
	}
	setPortFd(fd);
#ifdef CUSTOM_BAUD_RATE
	// Set serial through termios
	struct termios t;
	tcgetattr(fd, &t);
	t.c_cflag |=  CS8 | CREAD | CLOCAL;
	switch(dev.baudrate){
		case 9600:
			cfsetospeed(&t,B9600); // 115200 baud
			cfsetispeed(&t,B9600); // 115200 baud
			break;
		case 19200:
			cfsetospeed(&t,B19200); // 115200 baud
			cfsetispeed(&t,B19200); // 115200 baud
			break;
		case 115200:
			cfsetospeed(&t,B115200); // 115200 baud
			cfsetispeed(&t,B115200); // 115200 baud
			break;
		// add more baud rate if needed
		default:
			std::cout << "non-supported baud rate" << std::endl;
			exit(0);
			break;
	}
    tcsetattr(fd,TCSANOW,&t);
#endif
#ifdef CUSTOM_BAUD_RATE_ARBITRARY
	struct termios2 t;
	ioctl(fd, TCGETS2, &t);
	t.c_cflag &= ~CBAUD;
	t.c_cflag |=  CS8 | CREAD
				 | CLOCAL | CBAUDEX
				 | BOTHER;
	t.c_ispeed = getBaudrate();
	t.c_ospeed = getBaudrate();
	ioctl(fd, TCSETS2, &t);
#endif
	close(fd);
#ifdef PRINT_FUNC
	EXIT_FUNC
#endif
}

// read the data frame from imu
void *imu::revIMUFrameData(){
#ifdef PRINT_FUNC
    ENTER_FUNC
#endif
    pthread_mutex_lock(&this->IMUpkgAccessMuxid);
    while(!this->done){
        char c = readPort();
        this->rx_index = updatePKG(c);
#ifdef DEBUG
    std::cout << "loop flag is: " << this->startstop << std::endl;
#endif
    }
    this->done = 0;
    pthread_mutex_unlock(&this->IMUpkgAccessMuxid);
#ifdef PRINT_FUNC
    EXIT_FUNC
#endif
    return NULL;
}

// continue read the data from imu
void *imu::revIMUSeriesData(){
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif
	pthread_mutex_lock(&this->IMUpkgAccessMuxid);
	while(this->startstop){
		char c = readPort();
		this->rx_index = updatePKG(c);
#ifdef DEBUG
	std::cout << "loop flag is: " << this->startstop << std::endl;
#endif
	}
	pthread_mutex_unlock(&this->IMUpkgAccessMuxid);
#ifdef PRINT_FUNC
	EXIT_FUNC
#endif
	return NULL;
}

void *revIMUFrameData_pthread(void *context){
#ifdef PRINT_FUNC
    ENTER_FUNC
#endif
    ((imu *)context)->revIMUFrameData();
#ifdef PRINT_FUNC
    EXIT_FUNC
#endif
    return NULL;
}

void *revIMUSeriesData_pthread(void *context){
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif
	((imu *)context)->revIMUSeriesData();
#ifdef PRINT_FUNC
	EXIT_FUNC
#endif
	return NULL;
}

// set reading enable flag
void imu::setEnableimurx(bool flag){
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif
	this->startstop = flag;
#ifdef PRINT_FUNC
	EXIT_FUNC
#endif
}

// enable data fetching from gps
void *imu::enableimurx(void){
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif
    pthread_mutex_lock(&this->IMUpkgAccessMuxid);
	this->startstop = true;
    pthread_mutex_unlock(&this->IMUpkgAccessMuxid);
#ifdef PRINT_FUNC
	EXIT_FUNC
#endif
	return NULL;
}

void *enableimurx_pthread(void *context){
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif
	((imu *)context)->enableimurx();
#ifdef PRINT_FUNC
	EXIT_FUNC
#endif
	return NULL;
}

// disable data fetching from gps and stop the data fetching thread
void *imu::disableimurx(void){
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif
    pthread_mutex_lock(&this->IMUpkgAccessMuxid);
	this->startstop =false;
    pthread_mutex_unlock(&this->IMUpkgAccessMuxid);
#ifdef PRINT_FUNC
	EXIT_FUNC
#endif
	return NULL;
}

void *disableimurx_pthread(void *context){
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif
	((imu *)context)->disableimurx();
#ifdef PRINT_FUNC
	EXIT_FUNC
#endif
	return NULL;
}
