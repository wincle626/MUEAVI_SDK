/*
 * imgdet.hpp
 *
 *  Created on: 24 January 2019
 *      Author: Yun Wu
 *  log:
 *  This file contains the class for object detection
 *  through the image from PTZ camera. 
 *
 *  The imgdet class is a wrapper of darknet calling all
 *  the necessary function calls for MUEAVI object detection. 
 *  The major steps of imgdet includes:
 *  1. extract ROI
 *     (we need to define the ROI)
 *  2. detect the object
 *     (we need to define the object)
 *  3. output object information 
 *     (we need to define the information format)
 */

#ifndef SRC_HEADERS_IMGDET_HPP_
#define SRC_HEADERS_IMGDET_HPP_

#include "common.hpp"
#include "darknet.h"

// the object classificaiton on MUEAVI ( temperal reference)
enum objectclass{ 
    vehicle,
    peopel,
    obstacle    
};

class imgdet{
    public:
        // The public variables and functions:
        // non-sensitive data and functions
        int imgwidth; // the width of image
        int imgdepth; // the depth of image
        int numofroi; // the number of ROI
        int *roiwidth; // the array of ROI width 
        int *roidepth; // the array of ROI depth
    private:
        // The private variables and functions:
        // internal temperal data and functions
    protected:
        // The protected variables and functions: 
        // sensitive data and functions
        int numofobj; // the number of detected object
        int *classofobj; // the array of detected object class
        int *boxwidth; // the array of object box width
        int *boxdepth; // the array of object box depth
}

#endif
