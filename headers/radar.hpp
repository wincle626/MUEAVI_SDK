/*
 * radar.hpp
 *
 *  Created on: 16 May 2018
 *      Author: Yun Wu
 *  Modified on: 7 Aug 2018 by Yun Wu - add data strucuture and functions
 */

#ifndef SRC_HEADERS_RADAR_HPP_
#define SRC_HEADERS_RADAR_HPP_

#include <json-c/json.h>
#include "common.hpp"
#include "curl.hpp"
#include "file.hpp"
#include "system.hpp"

class radar : public curl{
	public:
		radar();
		radar(int dataport, int restport, std::string ipaddr);
		radar(int dataport, int restport,
				std::string usrname, std::string usrpsswd, std::string ipaddr);
		radar(int dataport, int restport, std::string localusrpasswd,
				std::string usrname, std::string usrpsswd, std::string ipaddr);
		~radar();
		void setdeviceonflag(bool flag);
		void setdataportnum(int port);
		void setrestportnum(int port);
		void setipaddress(std::string ipaddr);
		void setusername(std::string usrname);
		void setuserpasswd(std::string usrpasswd);
		void setdatasparsesize(int len);
		void setdatafullsize(int len);
		void setdatasparse(char* data);
		void setdatafull(char* data);
		void switchondevice();
		void switchoffdevice();
        void switchonserverservice();
        void switchoffserverservice();
		void resetserverservice();
		std::string acquiresparsedata();
		std::string acquiresparsedata2();
		void acquirefulldata();
		void stopdataacquire();
		void parse_data_sparse();
		void parse_data_full();
		void getdeviceonstatus();
		bool getdeviceonflag();
		char* getdatasparse();
		char* getdatafull();
		int getdataportnum();
		int getrestportnum();
		int getdatasparsesize();
		int getdatafullsize();
		int getparseddatasize();
		float* getparseddatasparse();
		std::string getipaddress();
		std::string getusername();
		std::string getuserpasswd();


	private:
		bool device_on = false;
		int dataportnum=12345;
		int restportnum=5000;
		std::string localpasswd = std::string("humandrive");
		std::string username = std::string("liber");
		std::string password = std::string("Liber!");
		std::string ipaddress = std::string("10.42.0.82");
		std::string controlurl = std::string("control/capture-in-progress");
		std::string adcresurl = std::string("config/0");
		std::string couplingurl = std::string("config/1");
		std::string dopplerppicolormapurl = std::string("config/2");
		std::string dopplerppiminvalurl = std::string("config/3");
		std::string dopplerppimaxvalurl = std::string("config/4");
		std::string dopplerresurl = std::string("config/5");
		std::string effdownsampleratiourl = std::string("config/6");
		std::string hwdownsamplemodeurl = std::string("config/7");
		std::string whdownsampleratiourl = std::string("config/8");
		std::string ignoredopplerbinurl = std::string("config/9");
		std::string maxsparsepointsurl = std::string("config/10");
		std::string movingthresholdurl = std::string("config/11");
		std::string munstaticbinurl = std::string("config/12");
		std::string numdopplerbinurl = std::string("config/13");
		std::string numpositiverangebinurl = std::string("config/14");
		std::string numrangebinurl = std::string("config/15");
		std::string numspokesurl = std::string("config/16");
		std::string persistenceurl = std::string("config/17");
		std::string persistencedopplerlenurl = std::string("config/18");
		std::string persistenceppilenurl = std::string("config/19");
		std::string ppimaxrangeurl = std::string("config/20");
		std::string ppireversespokesurl = std::string("config/21");
		std::string radaridurl = std::string("config/22");
		std::string rangebinsizeurl = std::string("config/23");
		std::string rawmodeurl = std::string("config/24");
		std::string samplingdurationurl = std::string("config/25");
		std::string sampleingrateurl = std::string("config/26");
		std::string spokeresurl = std::string("config/27");
		std::string staticthresholdurl = std::string("config/28");
		std::string storagechecksumurl = std::string("config/29");
		std::string storagecompressurl = std::string("config/30");
		std::string storageoverwriteurl = std::string("config/31");
		std::string storageshuffleurl = std::string("config/32");
		std::string sumppimaxvalurl = std::string("config/33");
		std::string sumppiminvalurl = std::string("config/34");
		std::string swdownsampleratiourl = std::string("config/35");
		std::string trigdirurl = std::string("config/36");
		std::string trigsourceurl = std::string("config/37");
		std::string trigvurl = std::string("config/38");
		std::string trigvrangeurl = std::string("config/39");
		std::string timeflybackurl = std::string("config/40");
		std::string timepostacquiringrl = std::string("config/41");
		std::string timepriorurl = std::string("config/42");
		std::string timerampdurationurl = std::string("config/43");
		std::string timespokeurl = std::string("config/44");
		std::string timestarturl = std::string("config/45");
		std::string vrangeurl = std::string("config/46");

	protected:
		int data_sparse_size = 0;
		int data_full_size = 0;
        char* data_sparse = NULL;
        char* data_full = NULL;
		int parsed_data_size = 0;
        float* parsed_data_sparse = NULL;
};

void *terminatedataacquire_thread(void *context);
void *dataacquire_thread(void *context);
void *parsedatasparse_thread(void *context);


#endif /* SRC_HEADERS_RADAR_HPP_ */
