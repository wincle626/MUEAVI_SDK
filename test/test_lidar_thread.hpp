/*
 * test_urg2d_thread.hpp
 *
 *  Created on: 7 Jun 2018
 *      Author: Yun Wu
 */

#ifndef SRC_TEST_TEST_LIDAR_THREAD_HPP_
#define SRC_TEST_TEST_LIDAR_THREAD_HPP_

#include "urg2d.hpp"
#include "urg3d.hpp"

#include "quanergym8.hpp"


void *test_urg2d_thread(void *p);
void *test_urg3d_thread(void *p);

void *test_m8_thread(void *p);


#endif /* SRC_TEST_TEST_LIDAR_THREAD_HPP_ */
