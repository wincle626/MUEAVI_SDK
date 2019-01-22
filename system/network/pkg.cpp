/*
 * pkg.cpp
 *
 *  Created on: 22 May 2018
 *      Author: Yun Wu
 */

#include "pkg.hpp"

pkg::pkg(){
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif
	this->done_tx = false;
	this->done_rx = false;
	this->ipaddress_tx = std::string("127.0.0.1");
	this->ipaddress_rx = std::string("127.0.0.1");
	this->port_rx = 9527;
	this->port_tx = 9527;
	this->datasize_tx = 0;
	this->datasize_rx = 0;
	this->data_tx_w = NULL;
	this->data_rx_w = NULL;
	this->data_tx_r = NULL;
	this->data_rx_r = NULL;
#ifdef PRINT_FUNC
	EXIT_FUNC
#endif
}
pkg::pkg(char *ipaddr_tx){
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif
	this->done_tx = false;
	this->done_rx = false;
	this->ipaddress_tx = std::string(ipaddr_tx);
	this->ipaddress_rx = std::string(ipaddr_tx);
	this->port_rx = 9527;
	this->port_tx = 9527;
	this->datasize_tx = 0;
	this->datasize_rx = 0;
	this->data_tx_w = NULL;
	this->data_rx_w = NULL;
	this->data_tx_r = NULL;
	this->data_rx_r = NULL;
#ifdef PRINT_FUNC
	EXIT_FUNC
#endif
}
pkg::pkg(int pn_tx){
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif
	this->done_tx = false;
	this->done_rx = false;
	this->ipaddress_tx = std::string("127.0.0.1");
	this->ipaddress_rx = std::string("127.0.0.1");
	this->port_rx = pn_tx;
	this->port_tx = pn_tx;
	this->datasize_tx = 0;
	this->datasize_rx = 0;
	this->data_tx_w = NULL;
	this->data_rx_w = NULL;
	this->data_tx_r = NULL;
	this->data_rx_r = NULL;
#ifdef PRINT_FUNC
	EXIT_FUNC
#endif
}
pkg::pkg(int pn_tx, char *ipaddr_tx){
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif
	this->done_tx = false;
	this->done_rx = false;
	this->ipaddress_tx = std::string(ipaddr_tx);
	this->ipaddress_rx = std::string(ipaddr_tx);
	this->port_rx = pn_tx;
	this->port_tx = pn_tx;
	this->datasize_tx = 0;
	this->datasize_rx = 0;
	this->data_tx_w = NULL;
	this->data_rx_w = NULL;
	this->data_tx_r = NULL;
	this->data_rx_r = NULL;
#ifdef PRINT_FUNC
	EXIT_FUNC
#endif
}
pkg::pkg(int pn_tx, char *ipaddr_tx, unsigned char *d_tx, int s_tx){
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif
	this->done_tx = false;
	this->done_rx = false;
	this->ipaddress_tx = std::string(ipaddr_tx);
	this->ipaddress_rx = std::string(ipaddr_tx);
	this->port_rx = pn_tx;
	this->port_tx = pn_tx;
	this->datasize_tx = s_tx;
	this->datasize_rx = 0;
	this->data_tx_w = NULL;
	this->setdatasizetx(s_tx+1);
	this->setdatatxw(d_tx);
	//free(d_tx);
	this->data_rx_w = NULL;
	this->data_tx_r = NULL;
	this->data_rx_r = NULL;
#ifdef PRINT_FUNC
	EXIT_FUNC
#endif
}
pkg::pkg(int pn_rx, char *ipaddr_rx, int s_rx){
#ifdef PRINT_FUNC
    ENTER_FUNC
#endif
    this->done_tx = false;
    this->done_rx = false;
    this->ipaddress_tx = std::string(ipaddr_rx);
    this->ipaddress_rx = std::string(ipaddr_rx);
    this->port_rx = pn_rx;
    this->port_tx = pn_rx;
    this->datasize_tx = s_rx;
    this->datasize_rx = s_rx;
    this->data_tx_w = NULL;
    this->setdatasizerx(s_rx+1);
    //free(d_tx);
    this->data_rx_w = NULL;
    this->data_tx_r = NULL;
    this->data_rx_r = NULL;
    this->data_rx_w = (unsigned char*) realloc(this->data_rx_r,s_rx*sizeof(unsigned char));
    this->data_rx_r = (unsigned char*) realloc(this->data_rx_r,s_rx*sizeof(unsigned char));
#ifdef PRINT_FUNC
    EXIT_FUNC
#endif
}
pkg::~pkg(){
}

void pkg::setdatasizetx(int size){
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif
	this->datasize_tx = size;
#ifdef PRINT_FUNC
	EXIT_FUNC
#endif
}
void pkg::setdatasizerx(int size){
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif
	this->datasize_rx = size;
#ifdef PRINT_FUNC
	EXIT_FUNC
#endif
}
void pkg::setdatatxw(unsigned char* data){
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif
    pthread_mutex_lock(&this->udt4txmuxid);
    this->data_tx_w = (unsigned char*) realloc(this->data_tx_w, this->datasize_tx);
    memcpy((char*)this->data_tx_w, (char*)data, this->datasize_tx*sizeof(unsigned char));
    pthread_mutex_unlock(&this->udt4txmuxid);
	//free(data);
#ifdef PRINT_FUNC
	EXIT_FUNC
#endif
}
void pkg::setdatarxw(unsigned char* data){
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif
    pthread_mutex_lock(&this->udt4rxmuxid);
    this->data_rx_w = (unsigned char*) realloc(this->data_rx_w, this->datasize_rx);
    memcpy((char*)this->data_rx_w, (char*)data, this->datasize_rx*sizeof(unsigned char));
    pthread_mutex_unlock(&this->udt4rxmuxid);
	//free(data);
#ifdef PRINT_FUNC
	EXIT_FUNC
#endif
}
void pkg::setdatatxr(){
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif
    pthread_mutex_lock(&this->udt4txmuxid);
    this->data_tx_r = (unsigned char*) realloc(this->data_tx_r, this->datasize_tx);
    memcpy((char*)this->data_tx_r, (char*)this->data_tx_w, this->datasize_tx*sizeof(unsigned char));
    pthread_mutex_unlock(&this->udt4txmuxid);
#ifdef PRINT_FUNC
	EXIT_FUNC
#endif
}
void pkg::setdatarxr(){
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif
    pthread_mutex_lock(&this->udt4rxmuxid);
    this->data_rx_r = (unsigned char*) realloc(this->data_rx_r, this->datasize_rx);
    memcpy((char*)this->data_rx_r, (char*)this->data_rx_w, this->datasize_rx*sizeof(unsigned char));
    pthread_mutex_unlock(&this->udt4rxmuxid);
#ifdef PRINT_FUNC
	EXIT_FUNC
#endif
}

void pkg::setiptx(std::string ip){
#ifdef PRINT_FUNC
    ENTER_FUNC
#endif
    this->ipaddress_tx = ip;
#ifdef PRINT_FUNC
    EXIT_FUNC
#endif
}

void pkg::setiprx(std::string ip){
#ifdef PRINT_FUNC
    ENTER_FUNC
#endif
    this->ipaddress_rx = ip;
#ifdef PRINT_FUNC
    EXIT_FUNC
#endif
}

void pkg::setporttx(int p){
#ifdef PRINT_FUNC
    ENTER_FUNC
#endif
    this->port_tx = p;
#ifdef PRINT_FUNC
    EXIT_FUNC
#endif
}

void pkg::setportrx(int p){
#ifdef PRINT_FUNC
    ENTER_FUNC
#endif
    this->port_rx = p;
#ifdef PRINT_FUNC
    EXIT_FUNC
#endif
}

void pkg::pkgTx(){
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif

	struct sockaddr_in si_other;
	int so, slen=sizeof(si_other);

	if ( (so=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
	{
		perror("socket");
		exit(1);
	}

	memset((char *) &si_other, 0, sizeof(si_other));
	si_other.sin_family = AF_INET;
	int pn = this->getporttx();
	si_other.sin_port = htons(pn);

	const char *ip = this->getiptx().c_str();
	if (inet_aton(ip , &si_other.sin_addr) == 0)
	{
		fprintf(stderr, "inet_aton() failed\n");
		exit(1);
	}

	int dataleft = this->datasize_tx;
	this->setdatatxr();
    unsigned char *data = this->getdatatx();
	int packstartind = 0;
    unsigned char message[UDP_BUFFER_SIZE];
	while(dataleft>0){
#ifdef DEBUG
		printf("Send message ? (Enter) \n");
#endif
		memset( message, '\0', sizeof(unsigned char)*UDP_BUFFER_SIZE );
#ifdef DEBUG
		getchar();
#endif

        if(dataleft>=UDP_BUFFER_SIZE){
            strncpy((char*)message, (char*)&data[packstartind], UDP_BUFFER_SIZE);
        }
        else{
            strncpy((char*)message, (char*)&data[packstartind], dataleft);
        }
        dataleft = dataleft - UDP_BUFFER_SIZE;

		//send the message
        if (sendto(so, message, strlen((char*)message) , 0 , (struct sockaddr *) &si_other, slen)==-1)
		{
			perror("sendto()");
			exit(1);
        }
		packstartind = packstartind + UDP_BUFFER_SIZE;
	}

	close(so);
#ifdef PRINT_FUNC
	EXIT_FUNC
#endif
}

void pkg::pkgRx(){
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif

#ifdef PRINT_FUNC
    std::cout << "enter function: " << __func__ << std::endl;
#endif
    struct sockaddr_in si_me, si_other;
    int s, slen = sizeof(si_other) , recv_len;
    //create a UDP socket
    if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        perror("socket");
        exit(1);
    }
    // zero out the structure
    memset((char *) &si_me, 0, sizeof(si_me));
    si_me.sin_family = AF_INET;
    int pn = this->getportrx();
#ifdef DEBUG
    std::cout << "get the rx port: " << pn << std::endl;
#endif
    si_me.sin_port = htons(pn);
    si_me.sin_addr.s_addr = htonl(INADDR_ANY);
    //bind socket to port
    if( bind(s , (struct sockaddr*)&si_me, sizeof(si_me) ) == -1)
    {
        perror("bind");
        exit(1);
    }

    //keep listening for data until the flag is off
    int dataleft = this->datasize_rx;
    unsigned char* data = (unsigned char*)malloc(sizeof(char)*dataleft);
    int packstartind = 0;
    bool flag = true;
    while(dataleft>0){
#ifdef DEBUG
        std::cout << "Waiting for data..." << std::endl;
#endif
        char buf[UDP_BUFFER_SIZE];
        memset( buf, '\0', sizeof(unsigned char)*UDP_BUFFER_SIZE );
        fflush(stdout);
        //try to receive some data, this is a blocking call
        if ((recv_len = recvfrom(s, buf, UDP_BUFFER_SIZE, 0,
            (struct sockaddr *) &si_other, (socklen_t *)&slen)) == -1)
        {
            perror("recvfrom()");
            exit(1);
        }

        if(dataleft>=UDP_BUFFER_SIZE){
            strncpy((char*)&data[packstartind], buf, UDP_BUFFER_SIZE);
        }
        else{
            strncpy((char*)&data[packstartind], buf, dataleft);
        }
        dataleft = dataleft - UDP_BUFFER_SIZE;
        packstartind = packstartind + UDP_BUFFER_SIZE;
#ifdef DEBUG
        //print details of the client/peer and the data received
        std::cout << "Received packet from " << this->getiprx()
             << ":" << this->getportrx() << std::endl;
        std::cout << "Data: " << buf << std::endl;
#endif
    }
    this->setdatarxw(data);
    free(data);
#ifdef PRINT_FUNC
    std::cout << "exit function: " << __func__ << std::endl;
#endif
    close(s);
#ifdef PRINT_FUNC
	EXIT_FUNC
#endif
    return;
}


int pkg::getporttx(){
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif
#ifdef PRINT_FUNC
	EXIT_FUNC
#endif
	return this->port_tx;
}
int pkg::getportrx(){
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif
#ifdef PRINT_FUNC
	EXIT_FUNC
#endif
	return this->port_rx;
}
int pkg::getdatasizetx(){
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif
#ifdef PRINT_FUNC
	EXIT_FUNC
#endif
	return this->datasize_tx;
}
int pkg::getdatasizerx(){
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif
#ifdef PRINT_FUNC
	EXIT_FUNC
#endif
	return this->datasize_rx;
}
std::string pkg::getiptx(){
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif
	return this->ipaddress_tx;
}
std::string pkg::getiprx(){
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif
#ifdef PRINT_FUNC
	EXIT_FUNC
#endif
	return this->ipaddress_rx;
}
unsigned char* pkg::getdatatx(){
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif
#ifdef PRINT_FUNC
	EXIT_FUNC
#endif
	return this->data_tx_r;
}
unsigned char* pkg::getdatarx(){
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif
#ifdef PRINT_FUNC
	EXIT_FUNC
#endif
	return this->data_rx_r;
}

//int createUDTSocket(UDTSOCKET& usock, int port = 0, bool rendezvous = false);
int connectusock(UDTSOCKET& usock, const char* ip, int port);

int createUDTSocket(UDTSOCKET& usock, int port = 0, bool rendezvous = false)
{
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif

   addrinfo hints;
   addrinfo* res;
   memset(&hints, 0, sizeof(struct addrinfo));
   hints.ai_flags = AI_PASSIVE;
   hints.ai_family = AF_INET;
   hints.ai_socktype = SOCK_STREAM;

   char service[16];
   sprintf(service, "%d", port);

   if (0 != getaddrinfo(NULL, service, &hints, &res))
   {
      std::cout << "illegal port number or port is busy.\n" << std::endl;
      return -1;
   }

   usock = UDT::socket(res->ai_family, res->ai_socktype, res->ai_protocol);

   // since we will start a lot of connections, we set the buffer size to smaller value.
   int snd_buf = 16000;
   int rcv_buf = 16000;
   UDT::setsockopt(usock, 0, UDT_SNDBUF, &snd_buf, sizeof(int));
   UDT::setsockopt(usock, 0, UDT_RCVBUF, &rcv_buf, sizeof(int));
   snd_buf = 8192;
   rcv_buf = 8192;
   UDT::setsockopt(usock, 0, UDP_SNDBUF, &snd_buf, sizeof(int));
   UDT::setsockopt(usock, 0, UDP_RCVBUF, &rcv_buf, sizeof(int));
   int fc = 16;
   UDT::setsockopt(usock, 0, UDT_FC, &fc, sizeof(int));
   bool reuse = true;
   UDT::setsockopt(usock, 0, UDT_REUSEADDR, &reuse, sizeof(bool));
   UDT::setsockopt(usock, 0, UDT_RENDEZVOUS, &rendezvous, sizeof(bool));

   if (UDT::ERROR == UDT::bind(usock, res->ai_addr, res->ai_addrlen))
   {
	   std::cout << "bind: " << UDT::getlasterror().getErrorMessage() << std::endl;
      return -1;
   }

   freeaddrinfo(res);
#ifdef PRINT_FUNC
	EXIT_FUNC
#endif
   return 0;

}

int connectusock(UDTSOCKET& usock, const char* ip, int port)
{
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif

   addrinfo hints, *peer;
   memset(&hints, 0, sizeof(struct addrinfo));
   hints.ai_flags = AI_PASSIVE;
   hints.ai_family =  AF_INET;
   hints.ai_socktype = SOCK_STREAM;

   char buffer[16];
   sprintf(buffer, "%d", port);

   if (0 != getaddrinfo(ip, buffer, &hints, &peer))
   {
      return -1;
   }

   UDT::connect(usock, peer->ai_addr, peer->ai_addrlen);

   freeaddrinfo(peer);
#ifdef PRINT_FUNC
	EXIT_FUNC
#endif
   return 0;

}

void *pkg::pkgUdtTx(){
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif

	UDTSOCKET client;
	if (createUDTSocket(client, this->port_tx) < 0)
		return NULL;

	connectusock(client, this->getiptx().c_str(), this->port_tx);

    int tosend = this->datasize_tx * sizeof(char);
    pthread_mutex_lock(&this->udt4txmuxid);
    unsigned char *data = this->getdatatx();
    pthread_mutex_unlock(&this->udt4txmuxid);
#ifdef DEBUG
    std::cout << tosend << " bytes to sent" << std::endl;
#endif
	while (tosend > 0)
    {
        int sent = UDT::send(client, (char*)data + this->datasize_tx * sizeof(char) - tosend, tosend, 0);
		if (sent < 0)
		{
			std::cout << "send: " << UDT::getlasterror().getErrorMessage() << std::endl;
			return NULL;
		}
		tosend -= sent;
	}
	free(data);

	UDT::close(client);
#ifdef PRINT_FUNC
	EXIT_FUNC
#endif
	return NULL;

}

void *pkg::pkgUdtRx(){
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif

	UDTSOCKET serv;
	if (createUDTSocket(serv, this->port_rx) < 0)
		return NULL;

	UDT::listen(serv, 1024);
	sockaddr_storage clientaddr;
	int addrlen = sizeof(clientaddr);
	UDTSOCKET new_sock = UDT::accept(serv, (sockaddr*)&clientaddr, &addrlen);
	UDT::close(serv);

	if (new_sock == UDT::INVALID_SOCK)
	{
		return NULL;
	}

	int torecv = this->datasize_rx * sizeof(char);
    unsigned char *data = (unsigned char*) malloc(sizeof(char)*this->datasize_rx);
	while (torecv > 0)
	{
        int rcvd = UDT::recv(new_sock, (char*)data + this->datasize_rx * sizeof(char) - torecv, torecv, 0);
		if (rcvd < 0)
		{
			std::cout << "recv: " << UDT::getlasterror().getErrorMessage() << std::endl;
			return NULL;
		}
		torecv -= rcvd;
	    pthread_mutex_lock(&this->udt4rxmuxid);
		if(this->rx_thread_halt){
			break;
		}
	    pthread_mutex_unlock(&this->udt4rxmuxid);
	}
    this->setdatarxw(data);
	free(data);

	int eid = UDT::epoll_create();
	UDT::epoll_add_usock(eid, new_sock);
	/*
	set<UDTSOCKET> readfds;
	if (UDT::epoll_wait(eid, &readfds, NULL, -1) > 0)
	{
	UDT::close(new_sock);
	}
	*/

	UDTSOCKET readfds[1];
	int num = 1;
	if (UDT::epoll_wait2(eid, readfds, &num, NULL, NULL, -1) > 0)
	{
		UDT::close(new_sock);
	}

#ifdef PRINT_FUNC
	EXIT_FUNC
#endif
	return NULL;

}

void pkg::setudtrxhalt(bool flag){
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif
    pthread_mutex_lock(&this->udt4rxmuxid);
	this->rx_thread_halt = flag;
    pthread_mutex_unlock(&this->udt4rxmuxid);
#ifdef PRINT_FUNC
	EXIT_FUNC
#endif
}

void *udt_server_thread(void *context){
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif
	((pkg *)context)->setudtrxhalt(false);
	((pkg *)context)->pkgUdtRx();
	((pkg *)context)->setdatarxr();
#ifdef DEBUG
	std::cout << "Received data: " << ((pkg *)context)->getdatarx() << std::endl;
#endif
#ifdef PRINT_FUNC
	EXIT_FUNC
#endif
	return NULL;
}
void *udt_client_thread(void *context){
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif
	((pkg *)context)->setdatatxr();
#ifdef DEBUG
	std::cout << "the transmitting data will be: " << ((pkg *)context)->getdatatx()
			<< " size: " << ((pkg *)context)->getdatasizetx() << std::endl;
#endif
	((pkg *)context)->pkgUdtTx();
#ifdef PRINT_FUNC
	EXIT_FUNC
#endif
	return NULL;
}
