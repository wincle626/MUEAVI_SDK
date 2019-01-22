/*
 * timestampe.hpp
 *
 *  Created on: 16 May 2018
 *      Author: Yun Wu
 */

#ifndef SRC_HEADERS_TIMESTAMP_HPP_
#define SRC_HEADERS_TIMESTAMP_HPP_

#include "common.hpp"
#include "ptzcam.hpp"
#include "imu.hpp"
#include "mathformat.hpp"

void *timestampvideo(ptzcam *dev_ptzcam, imu *dev_imu);
void timestamplidar();
void timestampradar();



#endif /* SRC_HEADERS_TIMESTAMP_HPP_ */
