/*
 * pcl_pointxyzir.hpp
 *
 *  Created on: 16 Oct 2018
 *      Author: Yun Wu
 */

#ifndef PCL_POINTXYZIR_HPP_
#define PCL_POINTXYZIR_HPP_

#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/console/parse.h>

namespace mueavi
{

	struct PointXYZIR
	{

		PCL_ADD_POINT4D;                    // quad-word XYZ
		float    intensity;
		uint16_t ring;
		EIGEN_MAKE_ALIGNED_OPERATOR_NEW     // ensure proper alignment

	} EIGEN_ALIGN16;

} // namespace velodyne_pointcloud


POINT_CLOUD_REGISTER_POINT_STRUCT(mueavi::PointXYZIR,
								(float, x, x)
								(float, y, y)
								(float, z, z)
								(float, intensity, intensity)
								(uint16_t, ring, ring))


#endif /* PCL_POINTXYZIR_HPP_ */
