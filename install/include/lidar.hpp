/*
 * lidar.hpp
 *
 *  Created on: 16 May 2018
 *      Author: Yun Wu
 */

#ifndef SRC_HEADERS_LIDAR_HPP_
#define SRC_HEADERS_LIDAR_HPP_

#include "common.hpp"
#include "urg2d.hpp"
#include "urg3d.hpp"
#include "quanergym8.hpp"

class lidar : public urg2d, urg3d, quanergym8{
public:
	lidar();
	~lidar();
private:
protected:
};



#endif /* SRC_HEADERS_LIDAR_HPP_ */
