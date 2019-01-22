/*
 * tcp.cpp
 *
 *  Created on: 8 Aug 2018
 *      Author: Yun Wu
 */

#include "tcp.hpp"


tcp::tcp(){

}

tcp::tcp(int port, std::string ipaddr){
	this->port_tx = port;
	this->port_rx = port;
	this->ipaddress_tx = ipaddr;
	this->ipaddress_rx = std::string("127.0.0.1");
	this->datasize_rx = 0;
	this->datasize_tx = 0;
	this->data_rxw = NULL;
	this->data_rxr = NULL;
	this->data_txw = NULL;
	this->data_txr = NULL;
}

tcp::tcp(int port, std::string ipaddr, char* data, int datasize){
	this->port_tx = port;
	this->port_rx = port;
	this->ipaddress_tx = ipaddr;
	this->ipaddress_rx = std::string("127.0.0.1");
	this->datasize_rx = 0;
	this->datasize_tx = datasize;
	this->data_rxw = NULL;
	this->data_rxr = NULL;
	this->data_txw = (char*) realloc(this->data_txw, sizeof(char)*datasize);
	memcpy(this->data_txw, data, sizeof(char)*datasize);
	this->data_txr = NULL;
}
tcp::tcp(int port, std::string ipaddr, int datasize){
	this->port_tx = port;
	this->port_rx = port;
	this->ipaddress_tx = std::string("127.0.0.1");
	this->ipaddress_rx = ipaddr;
	this->datasize_rx = datasize;
	this->datasize_tx = 0;
	this->data_rxw = (char*) realloc(this->data_rxw, sizeof(char)*datasize);
	this->data_rxr = NULL;
	this->data_txw = NULL;
	this->data_txr = NULL;
}

tcp::~tcp(){

}

int tcp::getrxport(){
	return this->port_rx;
}

int tcp::gettxport(){
	return this->port_tx;
}

int tcp::getrxdatasize(){
	return this->datasize_rx;
}

int tcp::gettxdatasize(){
	return this->datasize_tx;
}

char* tcp::getrxip(){
	return (char*)this->ipaddress_rx.c_str();
}

char* tcp::gettxip(){
	return (char*)this->ipaddress_tx.c_str();
}

char* tcp::getrxdata(){
	return this->data_rxr;
}

char* tcp::gettxdata(){
	return this->data_txr;
}

void tcp::setrxport(int p){
	this->port_rx = p;
}

void tcp::settxport(int p){
	this->port_tx = p;
}

void tcp::setrxip(char* ip){
	this->ipaddress_rx = std::string(ip);
}

void tcp::settxip(char* ip){
	this->ipaddress_tx = std::string(ip);
}

void tcp::setrxdatasize(int len){
	this->datasize_rx = len;
}

void tcp::settxdatasize(int len){
	this->datasize_tx = len;
}

void tcp::setrxdataw(char* d){
	this->data_rxw = (char*) realloc(this->data_rxw, sizeof(char)*this->datasize_rx);
	memcpy(this->data_rxw, d, sizeof(char)*this->datasize_rx);
}

void tcp::settxdataw(char* d){
	this->data_txw = (char*) realloc(this->data_txw, sizeof(char)*this->datasize_tx);
	memcpy(this->data_txw, d, sizeof(char)*this->datasize_tx);
}

void tcp::setrxdatar(){
	this->data_rxr = (char*) realloc(this->data_rxr, sizeof(char)*this->datasize_rx);
	memcpy(this->data_rxr, this->data_rxw, sizeof(char)*this->datasize_rx);
}

void tcp::settxdatar(){
	this->data_txr = (char*) realloc(this->data_txr, sizeof(char)*this->datasize_tx);
	memcpy(this->data_txr, this->data_txw, sizeof(char)*this->datasize_tx);
}

#define BUF_LEN 65540 // Larger than maximum TCP packet size

void *tcp::rx(){

	int server_fd, new_socket, valread;
	struct sockaddr_in address;
	int opt = 1;
	int addrlen = sizeof(address);
	char buffer[BUF_LEN];

	// Creating socket file descriptor
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		perror("socket failed");
		exit(EXIT_FAILURE);
	}

	// Forcefully attaching socket to the port 8080
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
												  &opt, sizeof(opt)))
	{
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(this->port_rx);

	// Forcefully attaching socket to the port 8080
	if (bind(server_fd, (struct sockaddr *)&address,
								 sizeof(address))<0)
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	if (listen(server_fd, 3) < 0)
	{
		perror("listen");
		exit(EXIT_FAILURE);
	}

	if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
					   (socklen_t*)&addrlen))<0)
	{
		perror("accept");
		exit(EXIT_FAILURE);
	}

    int total_pack = 1 + (this->datasize_rx - 1) / TCP_BUFFER_SIZE;
    char *longbuf = new char[TCP_BUFFER_SIZE * total_pack];
    for (int i = 0; i < total_pack; i++) {
    	valread = read( new_socket , buffer, TCP_BUFFER_SIZE);
        if (valread==-1) {
    		perror("read");
    		exit(EXIT_FAILURE);
        }
        memcpy( & longbuf[i * TCP_BUFFER_SIZE], buffer, TCP_BUFFER_SIZE);
    }
    this->setrxdataw(longbuf);
    free(longbuf);

	return NULL;
}

void *tcp::tx(){

	int sock = 0;
	struct sockaddr_in serv_addr;
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("\n Socket creation error \n");
		exit(EXIT_FAILURE);
	}

	memset(&serv_addr, '0', sizeof(serv_addr));

    /*struct hostent *h;
    h = gethostbyname(this->ipaddress_tx.c_str());
    if(h==NULL)//check assigment of TCP server host
    {
        perror("Unknown host ");
		exit(EXIT_FAILURE);
    }
    serv_addr.sin_family = h->h_addrtype;
    memcpy((char *) &serv_addr.sin_addr.s_addr, h->h_addr_list[0], h->h_length);*/
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(this->port_tx);

	// Convert IPv4 and IPv6 addresses from text to binary form
	if(inet_pton(AF_INET, this->ipaddress_tx.c_str(), &serv_addr.sin_addr)<=0)
	{
		printf("\nInvalid address/ Address not supported \n");
		exit(EXIT_FAILURE);
	}

	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	{
		printf("\nConnection Failed \n");
		exit(EXIT_FAILURE);
	}

	int i = 0;
	int ss = 0;
    this->settxdatar();
    int tosendlen = this->gettxdatasize();
    char *tosenddata = this->gettxdata();
    int total_pack = 1 + (this->gettxdatasize() - 1) / TCP_BUFFER_SIZE;
	char tosendpkg[TCP_BUFFER_SIZE];
    if(total_pack>1){
		for (i = 0; i < total_pack-1; i++){
			memcpy(tosendpkg, &tosenddata[i * TCP_BUFFER_SIZE], TCP_BUFFER_SIZE);
			ss += write(sock, &tosenddata[i * TCP_BUFFER_SIZE], TCP_BUFFER_SIZE);
			tosendlen -= TCP_BUFFER_SIZE;
		}
		memcpy(tosendpkg, &tosenddata[i * TCP_BUFFER_SIZE], tosendlen);
		ss += write(sock, &tosenddata[i * TCP_BUFFER_SIZE], TCP_BUFFER_SIZE);
    }else{
		memcpy(tosendpkg, &tosenddata[i * TCP_BUFFER_SIZE], tosendlen);
		ss += write(sock, &tosenddata[i * TCP_BUFFER_SIZE], TCP_BUFFER_SIZE);
    }
#ifdef DEBUG
	printf("Hello message sent\n");
#endif

	return NULL;
}

void *tcp::rx2(boost::asio::io_service &io_service,
				boost::asio::ip::tcp::socket &socket,
				boost::asio::ip::tcp::endpoint &endpoint,
				boost::asio::ip::tcp::acceptor &acceptor){

	int total_pack = 1 + (this->datasize_rx - 1) / TCP_BUFFER_SIZE;
    char *data = new char[TCP_BUFFER_SIZE * total_pack];
	char toreceivepkg[TCP_BUFFER_SIZE];
	for (int i = 0; i < total_pack; i++){
		boost::asio::read(socket, boost::asio::buffer(toreceivepkg, TCP_BUFFER_SIZE));
        memcpy( & data[i * TCP_BUFFER_SIZE], toreceivepkg, TCP_BUFFER_SIZE);
    }
    this->setrxdataw(data);

	return NULL;
}

void *tcp::tx2(boost::asio::io_service &io_service,
				boost::asio::ip::tcp::socket &socket,
				boost::asio::ip::tcp::resolver &resolver){

    this->settxdatar();
    char *tosenddata = this->gettxdata();
    int tosendlen = this->gettxdatasize();
    int total_pack = 1 + (tosendlen - 1) / TCP_BUFFER_SIZE;
    int i = 0;
    char *tosendpkg = new char[TCP_BUFFER_SIZE+1];
    if(total_pack>1){
		for (i = 0; i < total_pack-1; i++){
			memcpy(tosendpkg, &tosenddata[i * TCP_BUFFER_SIZE], TCP_BUFFER_SIZE);
			boost::asio::write(socket, boost::asio::buffer(tosendpkg, TCP_BUFFER_SIZE));
			tosendlen -= TCP_BUFFER_SIZE;
		}
		memcpy(tosendpkg, &tosenddata[i * TCP_BUFFER_SIZE], tosendlen);
		boost::asio::write(socket, boost::asio::buffer(tosendpkg, TCP_BUFFER_SIZE));
    }else{
		memcpy(tosendpkg, &tosenddata[i * TCP_BUFFER_SIZE], tosendlen);
		boost::asio::write(socket, boost::asio::buffer(tosendpkg, TCP_BUFFER_SIZE));
    }

	return NULL;
}

void *tcp_server_thread(void *context){
#ifdef PRINT_FUNC
    std::cout << "enter function: " << __func__ << std::endl;
#endif
    ((tcp *)context)->rx();
#ifdef DEBUG
    std::cout << "the received data is: " << ((tcp *)context)->getRxData() << std::endl;
#endif
#ifdef PRINT_FUNC
    std::cout << "exit function: " << __func__ << std::endl;
#endif
    return NULL;
}

void *tcp_client_thread(void *context){
#ifdef PRINT_FUNC
    std::cout << "enter function: " << __func__ << std::endl;
#endif
#ifdef DEBUG
    std::cout << "the transmitting data will be: " << ((tcp *)context)->getTxData() << std::endl;
#endif
#ifdef DEBUG
    ((tcp *)context)->setServerOnOff(false);
#endif
    ((tcp *)context)->tx();
#ifdef PRINT_FUNC
    std::cout << "exit function: " << __func__ << std::endl;
#endif
    return NULL;
}


