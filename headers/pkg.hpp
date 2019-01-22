/*
 * pkg.hpp
 *
 *  Created on: 22 May 2018
 *      Author: Yun Wu
 */

#ifndef SRC_HEADERS_PKG_HPP_
#define SRC_HEADERS_PKG_HPP_


#include "common.hpp"
#include "debug.hpp"
#include "udp.hpp"
#include <udt4/udt.h>

class pkg{
	public:
		pkg();
		pkg(char *ipaddr_tx);
		pkg(int pn_tx);
		pkg(int pn_tx, char *ipaddr_tx);
        pkg(int pn_tx, char *ipaddr_tx, unsigned char *d_tx, int s_tx);
        pkg(int pn_rx, char *ipaddr_rx, int s_rx);
		~pkg();
		pthread_t rx_thread_id=0;
		pthread_t tx_thread_id=0;
		pthread_mutex_t udt4txmuxid;
		pthread_mutex_t udt4rxmuxid;
		bool rx_thread_halt=false;
		bool done_tx=false;
		bool done_rx=false;
        void setdatasizetx(int size);
        void setdatasizerx(int size);
        void setdatatxw(unsigned char* data);
        void setdatarxw(unsigned char* data);
        void setdatatxr();
        void setdatarxr();
        void setiptx(std::string ip);
        void setiprx(std::string ip);
        void setporttx(int p);
        void setportrx(int p);
		void pkgTx();
		void pkgRx();
        void *pkgUdtTx();
        void *pkgUdtRx();
        void setudtrxhalt(bool flag);
        int getporttx();
        int getportrx();
        int getdatasizetx();
        int getdatasizerx();
        std::string getiptx();
        std::string getiprx();
        unsigned char* getdatatx();
        unsigned char* getdatarx();
	private:
        std::string ipaddress_tx=std::string("127.0.0.1");
        std::string ipaddress_rx=std::string("127.0.0.1");
    	int port_rx=9527;
    	int port_tx=9527;
        int datasize_tx;
        int datasize_rx;
	protected:
        unsigned char *data_tx_w=NULL;
        unsigned char *data_rx_w=NULL;
        unsigned char *data_tx_r=NULL;
        unsigned char *data_rx_r=NULL;

};
void *udt_server_thread(void *context);
void *udt_client_thread(void *context);


#endif /* SRC_HEADERS_PKG_HPP_ */
