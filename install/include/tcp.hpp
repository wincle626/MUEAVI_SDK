/*
 * tcp.hpp
 *
 *  Created on: 8 Aug 2018
 *      Author: Yun Wu
 */

#ifndef SRC_TCP_HPP_
#define SRC_TCP_HPP_

#include "common.hpp"
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/thread/thread.hpp>
#include <boost/algorithm/string.hpp>

#define TCP_BUFFER_SIZE 4096

class tcp{
	public:
		pthread_t tcpserver_id=0;
		pthread_t tcpclient_id=0;
		pthread_mutex_t tcpAccessMuxid;
		tcp();
		tcp(int port, std::string ipaddr);
		tcp(int port, std::string ipaddr, char* data, int datasize);
		tcp(int port, std::string ipaddr, int datasize);
		~tcp();
		int getrxport();
		int gettxport();
		int getrxdatasize();
		int gettxdatasize();
		char* getrxip();
		char* gettxip();
		char* getrxdata();
		char* gettxdata();
		void setrxport(int p);
		void settxport(int p);
		void setrxip(char* ip);
		void settxip(char* ip);
		void setrxdatasize(int len);
		void settxdatasize(int len);
		void setrxdataw(char* d);
		void settxdataw(char* d);
		void setrxdatar();
		void settxdatar();
		void *rx();
		void *tx();
		void *rx2(boost::asio::io_service &io_service,
				boost::asio::ip::tcp::socket &socket,
				boost::asio::ip::tcp::endpoint &endpoint,
				boost::asio::ip::tcp::acceptor &acceptor);
		void *tx2(boost::asio::io_service &io_service,
				boost::asio::ip::tcp::socket &socket,
				boost::asio::ip::tcp::resolver &resolver);
	private:
		int port_tx=3921;
		int port_rx=3921;
		std::string ipaddress_tx = std::string("127.0.0.1");
		std::string ipaddress_rx = std::string("127.0.0.1");

	protected:
		int datasize_rx = 0;
		int datasize_tx = 0;
		char* data_rxw = NULL;
		char* data_txw = NULL;
		char* data_rxr = NULL;
		char* data_txr = NULL;
};
void *tcp_server_thread(void *p);
void *tcp_client_thread(void *p);


#endif /* SRC_TCP_HPP_ */
