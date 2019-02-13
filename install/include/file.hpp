/*
 * file.cpp
 *
 *  Created on: 28 Aug 2018
 *      Author: Yun Wu
 */

#ifndef SRC_HEADERS_FILE_HPP_
#define SRC_HEADERS_FILE_HPP_


#include "common.hpp"

void writestr2file(std::string data, std::string filename);

std::string readstr4file(std::string filename);

#endif /* SRC_HEADERS_FILE_HPP_ */