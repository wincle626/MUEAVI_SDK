/*
 * udp.hpp
 *
 *  Created on: 17 May 2018
 *      Author: Yun Wu
 *  log:
 *  	2018-05-17 create the udp class
 */

#ifndef SRC_HEADERS_UDP_HPP_
#define SRC_HEADERS_UDP_HPP_

#include "common.hpp"

#define UDP_BUFFER_SIZE 32768

class udp{
public:
	pthread_t server_id=0;
	pthread_t client_id=0;
	pthread_mutex_t udpAccessMuxid;
	bool server_onoff=false;
	udp();
	udp(char *ipaddr_tx);
	udp(int pn_tx);
	udp(int pn_tx, char *ipaddr_tx);
	udp(int pn_tx, char *ipaddr_tx, char *d_tx);
	~udp();
	int getRxPort();
	int getTxPort();
	char *getRxIP();
	char *getTxIP();
	char *getRxData();
	char *getTxData();
	void setServerOnOff(bool flag);
	void setRxPort(int p);
	void setTxPort(int p);
	void setRxIP(char *ip);
	void setTxIP(char *ip);
	void setRxData(char *d);
	void setTxData(char *d);
	void *rx();
	void *tx();
private:
	int port_num_rx=9527;
	int port_num_tx=9527;
	char ip_addr_tx[128]={};
	char ip_addr_rx[128]={};
protected:
	char data_rx[UDP_BUFFER_SIZE]={};
	char data_tx[UDP_BUFFER_SIZE]={};
};
void *udp_server_thread(void *p);
void *udp_client_thread(void *p);


#endif /* SRC_HEADERS_UDP_HPP_ */
