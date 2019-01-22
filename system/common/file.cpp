/*
 * file.cpp
 *
 *  Created on: 28 Aug 2018
 *      Author: Yun Wu
 */

#include "file.hpp"

void writestr2file(std::string data, std::string filename){
    std::ofstream out(filename.c_str());
    out << data;
    out.close();
}

std::string readstr4file(std::string filename){
	std::string data;
	std::ifstream f(filename.c_str());
	std::stringstream buf;
	buf << f.rdbuf();
	data = buf.str();
	return data;
}