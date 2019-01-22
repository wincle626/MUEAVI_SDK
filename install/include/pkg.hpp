/*
 * pkg.hpp
 *
 *  Created on: 22 May 2018
 *      Author: Yun Wu
 */

#ifndef SRC_HEADERS_PKG_HPP_
#define SRC_HEADERS_PKG_HPP_


#include "common.hpp"
#include "udp.hpp"

class pkg : public udp {
	public:
		pkg();
		~pkg();
		bool done_tx = false;
		bool done_rx = false;
		void pkgTx(char *data, int size);
		void pkgRx(char *data, int size);
	private:
	protected:
		char *data_tx;
		char *data_rx;
};

#endif /* SRC_HEADERS_PKG_HPP_ */
