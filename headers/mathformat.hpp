/*
 * mathformat.hpp
 *
 *  Created on: 29 May 2018
 *      Author: Yun Wu
 */

#ifndef SRC_HEADERS_MATHFORMAT_HPP_
#define SRC_HEADERS_MATHFORMAT_HPP_

#include "common.hpp"

float byte2float(unsigned char *bytes);
int byte2int(unsigned char *bytes);
void float2byte(float bytesfloat, unsigned char bytes[4]);
void int2byte(int bytesint, unsigned char bytes[4]);


#endif /* SRC_HEADERS_MATHFORMAT_HPP_ */
