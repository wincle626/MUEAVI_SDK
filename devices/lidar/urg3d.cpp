/*
 * urg3d.cpp
 *
 *  Created on: 7 Jun 2018
 *      Author: Yun Wu
 */

#include "urg3d.hpp"


urg3d::urg3d(){
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif
	this->RevEthernetPkgThreadId=0;
	this->RevEthernetPkgEnableThreadId=0;
	this->RevEthernetPkgDisableThreadId=0;
	this->connect_address_urg3d = std::string("10.42.0.10");
	this->connect_port_urg3d = 10940;
	this->blockfunctimeout = 2000; // ms
	this->frameinterval = 10000; // ms
    this->interlacecount  =4;
	this->rangeswith = false;
	this->intensityswith = false;
	this->auxilaryswith = false;
	this->meas_data_size_urg3d = 0;
	this->auxi_data_size_urg3d = 0;
	this->urg_urg3d = (urg3d_t*) malloc(sizeof(urg3d_t));
	this->meas_header = (urg3d_vssp_header_t*) malloc(sizeof(urg3d_vssp_header_t));
	this->meas_data_urg3d = (urg3d_measurement_data_t*) malloc(sizeof(urg3d_measurement_data_t));
	this->auxi_header = (urg3d_vssp_header_t*) malloc(sizeof(urg3d_vssp_header_t));
	this->auxi_data_urg3d = (urg3d_auxilary_data_t*) malloc(sizeof(urg3d_auxilary_data_t));
#ifdef PRINT_FUNC
	EXIT_FUNC
#endif
}
urg3d::urg3d(std::string addr, long int port){
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif
	this->RevEthernetPkgThreadId=0;
	this->RevEthernetPkgEnableThreadId=0;
	this->RevEthernetPkgDisableThreadId=0;
	this->connect_address_urg3d = addr;
	this->connect_port_urg3d = port;
	this->blockfunctimeout = 2000; // ms
	this->frameinterval = 10000; // ms
    this->interlacecount  =4;
	this->rangeswith = false;
	this->intensityswith = false;
	this->auxilaryswith = false;
	this->meas_data_size_urg3d = 0;
	this->auxi_data_size_urg3d = 0;
	this->urg_urg3d = (urg3d_t*) malloc(sizeof(urg3d_t));
	this->meas_header = (urg3d_vssp_header_t*) malloc(sizeof(urg3d_vssp_header_t));
	this->meas_data_urg3d = (urg3d_measurement_data_t*) malloc(sizeof(urg3d_measurement_data_t));
	this->auxi_header = (urg3d_vssp_header_t*) malloc(sizeof(urg3d_vssp_header_t));
	this->auxi_data_urg3d = (urg3d_auxilary_data_t*) malloc(sizeof(urg3d_auxilary_data_t));
#ifdef PRINT_FUNC
	EXIT_FUNC
#endif
}
urg3d::~urg3d(){
}


std::string urg3d::get_connect_address_urg3d(){
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif
#ifdef PRINT_FUNC
	EXIT_FUNC
#endif
	return this->connect_address_urg3d;
}
int urg3d::get_connect_port_urg3d(){
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif
#ifdef PRINT_FUNC
	EXIT_FUNC
#endif
	return this->connect_port_urg3d;
}

int urg3d::getmeasdatasizeurg3d(){
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif
#ifdef PRINT_FUNC
	EXIT_FUNC
#endif
	return this->meas_data_size_urg3d;
}
int urg3d::getauxidatasizeurg3d(){
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif
#ifdef PRINT_FUNC
	EXIT_FUNC
#endif
	return this->auxi_data_size_urg3d;
}

void urg3d::connectsensor(){
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif
	/*
	* open the connection to the sensor
	*/
	int ret;
#ifdef DEBUG
	std::cout << "connect sensor at " << this->connect_address_urg3d.c_str() << std::endl;
	std::cout << "connect port at " << this->connect_port_urg3d << std::endl;
	std::cout << "sensor active status: " << this->urg_urg3d->is_active << std::endl;
#endif
	if((ret = urg3d_open(this->urg_urg3d,  this->connect_address_urg3d.c_str(), this->connect_port_urg3d)) < 0) {
		printf("error urg3d_open %d\n", ret);
		#if defined(URG_MSC)
			getchar();
		#endif
		std::cout << "cannot open urg3d sensor !!!" << std::endl;
		exit(-1);
	}
#ifdef PRINT_FUNC
	EXIT_FUNC
#endif
}
void urg3d::disconnectsensor(){
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif
    /*
     * close the connection to the sensor
     */
	int ret;
    if((ret = urg3d_close(this->urg_urg3d)) < 0) {
        printf("error urg3d_close %d\n", ret);
        #if defined(URG_MSC)
            getchar();
        #endif
		std::cout << "cannot close urg3d sensor !!!" << std::endl;
		exit(-1);
    }
#ifdef PRINT_FUNC
	EXIT_FUNC
#endif
}
void urg3d::setblockfunctimeout(int timeout){
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif
	this->blockfunctimeout = timeout;
#ifdef PRINT_FUNC
	EXIT_FUNC
#endif
}
void urg3d::setframeinterval(int interval){
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif
	this->frameinterval = interval;
#ifdef PRINT_FUNC
	EXIT_FUNC
#endif
}
void urg3d::setrangeswitch(bool flag){
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif
	this->rangeswith = flag;
#ifdef PRINT_FUNC
	EXIT_FUNC
#endif
}
void urg3d::setintensityswith(bool flag){
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif
	this->intensityswith = flag;
}
void urg3d::setauxilaryswith(bool flag){
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif
	this->auxilaryswith = flag;
}

void urg3d::setconnectipaddress(std::string ip){
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif
    this->connect_address_urg3d  = ip;
#ifdef PRINT_FUNC
	EXIT_FUNC
#endif
}

void urg3d::setconnectport(int p){
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif
    this->connect_port_urg3d = p;
#ifdef PRINT_FUNC
	EXIT_FUNC
#endif
}

void urg3d::initsensor(){
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif
    /*
     * set blocking function timeout = 2000[ms]
     */
    urg3d_high_set_blocking_timeout_ms(this->urg_urg3d, this->blockfunctimeout);
    /*
	 * initialize the urg3d session (get transform tables)
	 */
	int ret;
	if((ret = urg3d_high_blocking_init(this->urg_urg3d)) < 0) {
		printf("error urg3d_high_blocking_init %d\n", ret);
		ret = urg3d_close(this->urg_urg3d);
		#if defined(URG_MSC)
			getchar();
		#endif
		exit(-1);
	}
	/*
	 * wait to finish initialize of mesurement
	 */
	printf("wait initialize... (about 30-60 seconds after power-on)\n");
	if((ret = urg3d_high_blocking_wait_finished_initialize(this->urg_urg3d)) < 0) {
		printf("error urg3d_high_blocking_wait_finished_initialize %d\n", ret);
		ret = urg3d_close(this->urg_urg3d);
		#if defined(URG_MSC)
			getchar();
		#endif
		exit(-1);
	}
    /*
     * send interlace count for device (4 field/frame)
     */
    if((ret = urg3d_high_blocking_set_interlace_count(this->urg_urg3d, this->interlacecount)) < 0) {
        printf("error urg3d_high_blocking_set_interlace_count %d\n", ret);
        ret = urg3d_close(this->urg_urg3d);
        #if defined(URG_MSC)
            getchar();
        #endif
		exit(-1);
    }
#ifdef PRINT_FUNC
	EXIT_FUNC
#endif
}
void urg3d::startdatastream(){
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif
	/*
	 * start the acquisition mode. possible value are:
	 *     URG3D_DISTANCE
	 *     URG3D_DISTANCE_INTENSITY
	 *     URG3D_AUXILIARY
	 */
	int ret;
	if(this->rangeswith==true){
		if((ret = urg3d_high_start_data(this->urg_urg3d, URG3D_DISTANCE)) < 0) {
			printf("error urg3d_high_start_data %d\n", ret);
			ret = urg3d_close(this->urg_urg3d);
			#if defined(URG_MSC)
				getchar();
			#endif
			exit(-1);
		}
	}
	if(this->intensityswith==true){
		if((ret = urg3d_high_start_data(this->urg_urg3d, URG3D_DISTANCE_INTENSITY)) < 0) {
			printf("error urg3d_high_start_data %d\n", ret);
			ret = urg3d_close(this->urg_urg3d);
			#if defined(URG_MSC)
				getchar();
			#endif
			exit(-1);
		}
	}
	if(this->auxilaryswith==true){
		if((ret = urg3d_high_start_data(this->urg_urg3d, URG3D_AUXILIARY)) < 0) {
			printf("error urg3d_high_start_data %d\n", ret);
			ret = urg3d_close(this->urg_urg3d);
			#if defined(URG_MSC)
				getchar();
			#endif
			exit(-1);
		}
	}
#ifdef PRINT_FUNC
	EXIT_FUNC
#endif

}
void urg3d::stopdatastream(){
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif
	/*
	 * stop the acquisition flow started earlier using the start acquisition mode.
	 */
	int ret;
	if(this->rangeswith==true){
		if((ret = urg3d_high_stop_data(this->urg_urg3d, URG3D_DISTANCE)) < 0) {
			printf("error urg3d_high_stop_data %d\n", ret);
			ret = urg3d_close(this->urg_urg3d);
			#if defined(URG_MSC)
				getchar();
			#endif
			exit(-1);
		}
	}

	if(this->intensityswith==true){
		if((ret = urg3d_high_stop_data(this->urg_urg3d, URG3D_DISTANCE_INTENSITY)) < 0) {
			printf("error urg3d_high_stop_data %d\n", ret);
			ret = urg3d_close(this->urg_urg3d);
			#if defined(URG_MSC)
				getchar();
			#endif
			exit(-1);
		}
	}

	if(this->auxilaryswith==true){
		if((ret = urg3d_high_stop_data(this->urg_urg3d, URG3D_AUXILIARY)) < 0) {
			printf("error urg3d_high_stop_data %d\n", ret);
			ret = urg3d_close(this->urg_urg3d);
			#if defined(URG_MSC)
				getchar();
			#endif
			exit(-1);
		}
	}
#ifdef PRINT_FUNC
	EXIT_FUNC
#endif
}

void urg3d::measuresingledataframe(){
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif
	int prev_frame = -1;
	char data[URG3D_MAX_RX_LENGTH];
	while(1) {
		/*
		 * check received data
		 */
		if(urg3d_next_receive_ready(this->urg_urg3d)) {
			/*
			 * pick up the data (non-blocking)
			 */
			if(urg3d_high_get_measurement_data(this->urg_urg3d, this->meas_data_urg3d) > 0) {
				/*
				 * wait for first data
				 */
				if(prev_frame == -1) {
					/*
					 * check line and field number
					 */
					if(this->meas_data_urg3d->line_number == 0 && this->meas_data_urg3d->field_number == 0) {
						prev_frame = this->meas_data_urg3d->frame_number;
					}
				}
				/*
				 * start frame data
				 */
				if(prev_frame != -1) {
					/*
					 * if frame number is difficult, break the loop
					 */
					if(prev_frame != this->meas_data_urg3d->frame_number) {
						break;
					}
				}
			} else if(urg3d_low_get_binary(this->urg_urg3d, this->meas_header, data, &this->meas_data_size_urg3d) > 0) {
				/*
				 * check error data
				 */
				if(strncmp(this->meas_header->type, "ERR", 3) == 0 || strncmp(this->meas_header->type, "_er", 3) == 0) {
					printf("error %c%c%c %s", this->meas_header->status[0], this->meas_header->status[1], this->meas_header->status[2], data);
					if(this->meas_header->status[0] != '0'){
						break;
					}
				}
			 }
		} else {
			#ifdef URG_WINDOWS_OS
				Sleep(10);
			#else
				usleep(this->frameinterval);
			#endif
		}
	}
#ifdef PRINT_FUNC
	EXIT_FUNC
#endif
}


enum YVT_X002_AUXILARY_DATA_INDEX {
    ROTATION_ANGULAR_VELOCITY_ABOUT_X_AXIS = 0,
    ROTATION_ANGULAR_VELOCITY_ABOUT_Y_AXIS,
    ROTATION_ANGULAR_VELOCITY_ABOUT_Z_AXIS,

    ACCELERATION_IN_X_DIRECTION,
    ACCELERATION_IN_Y_DIRECTION,
    ACCELERATION_IN_Z_DIRECTION,

    TEMPERATURE,

    NUMBER_OF_YVT_X002_AUXILARY_DATA,
};


#define MAXIMUM_RECORD_TIMES 10
#define MAXIMUM_CAPTURING_COUNT 300

double yvt_sensor_ax_data_timestamps[MAXIMUM_CAPTURING_COUNT * MAXIMUM_RECORD_TIMES];
double yvt_sensor_scaled_ax_data[MAXIMUM_CAPTURING_COUNT * MAXIMUM_RECORD_TIMES][NUMBER_OF_YVT_X002_AUXILARY_DATA];

//! following YVT-X002 scaling factors are defined in MPU-9250 product specification

//! scaling factor for angular velocity (500.0 * 0.001 / 32767) [deg/msec]
#define YVT_X002_ANGULAR_VELOCITY_SCALING_FACTOR 0.00001525925

//! scaling factor for acceleration (1 / 8192) [G]
#define YVT_X002_ACCELERATION_SCALING_FACTOR 0.00012207031

//! scaling factor for temperature (1.0 / 333.87) [degree]
#define YVT_X002_TEMPERATURE_SCALING_FACTOR 0.0029951776

//! shift value for temperature [degree]
#define YVT_X002_TEMPERATURE_SHIFT_VALUE 21.0

//! invalid time stamp
#define INVALID_TIMESTAMP -1.0

static int is_yvt_x002_valid_auxilary_data(const urg3d_auxilary_data_t *raw_data);

static void set_value_unit_of_yvt_x002(const urg3d_auxilary_record_t *raw_data,
                                       double *timestamp_msec,
                                       double yvt_scaled_data[NUMBER_OF_YVT_X002_AUXILARY_DATA]);

static int is_yvt_x002_valid_auxilary_data(const urg3d_auxilary_data_t *raw_data)
{
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif
    if ((raw_data->type & URG3D_GYRO_DATA) &&
        (raw_data->type & URG3D_ACCEL_DATA) &&
        (raw_data->type & URG3D_TEMPERATURE_DATA)) {

        return 1;
    }
#ifdef PRINT_FUNC
	EXIT_FUNC
#endif

    return 0;
}

static void set_value_unit_of_yvt_x002(const urg3d_auxilary_record_t *raw_data,
                                       double *timestamp_msec,
                                       double yvt_scaled_data[NUMBER_OF_YVT_X002_AUXILARY_DATA])
{
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif
    *timestamp_msec = (double)raw_data->timestamp_ms;

    yvt_scaled_data[ROTATION_ANGULAR_VELOCITY_ABOUT_X_AXIS] =
        YVT_X002_ANGULAR_VELOCITY_SCALING_FACTOR * (double)raw_data->gyro_x;
    yvt_scaled_data[ROTATION_ANGULAR_VELOCITY_ABOUT_Y_AXIS] =
        YVT_X002_ANGULAR_VELOCITY_SCALING_FACTOR * (double)raw_data->gyro_y;
    yvt_scaled_data[ROTATION_ANGULAR_VELOCITY_ABOUT_Z_AXIS] =
        YVT_X002_ANGULAR_VELOCITY_SCALING_FACTOR * (double)raw_data->gyro_z;

    yvt_scaled_data[ACCELERATION_IN_X_DIRECTION] =
        YVT_X002_ACCELERATION_SCALING_FACTOR * (double)raw_data->accel_x;
    yvt_scaled_data[ACCELERATION_IN_Y_DIRECTION] =
        YVT_X002_ACCELERATION_SCALING_FACTOR * (double)raw_data->accel_y;
    yvt_scaled_data[ACCELERATION_IN_Z_DIRECTION] =
        YVT_X002_ACCELERATION_SCALING_FACTOR * (double)raw_data->accel_z;

    yvt_scaled_data[TEMPERATURE] =
        YVT_X002_TEMPERATURE_SCALING_FACTOR * (double)raw_data->temperature + YVT_X002_TEMPERATURE_SHIFT_VALUE;

#ifdef PRINT_FUNC
	EXIT_FUNC
#endif
    return;
}

void urg3d::auxilarysingledataframe(){
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif

    int record_index = 0;
    int capturing_record_count = 0;

    int capturing_count = 0;
    int capturing_data_index = 0;

	char data[URG3D_MAX_RX_LENGTH];

    while(1) {

        if (capturing_count == MAXIMUM_CAPTURING_COUNT / 2) {
            printf("%d capturing end\n", capturing_count);
        }

        if (capturing_count > MAXIMUM_CAPTURING_COUNT) {
            break;
        }

        // check receiving data7
        if(urg3d_next_receive_ready(this->urg_urg3d)) {

            // parse ax data7 from receiving data7
            if(urg3d_high_get_auxilary_data(this->urg_urg3d, this->auxi_data_urg3d) > 0) {

                if (is_yvt_x002_valid_auxilary_data(this->auxi_data_urg3d) > 0) {
                    ++capturing_count;

                    if (capturing_count > MAXIMUM_CAPTURING_COUNT) {
                        break;
                    }

                    capturing_record_count = this->auxi_data_urg3d->record_count;
                    if (capturing_record_count > MAXIMUM_RECORD_TIMES) {
                        capturing_record_count = MAXIMUM_RECORD_TIMES;
                    }

                    for (record_index = 0; record_index < capturing_record_count; ++record_index) {
                        set_value_unit_of_yvt_x002(&this->auxi_data_urg3d->records[record_index],
                                                   &yvt_sensor_ax_data_timestamps[capturing_data_index],
                                                   yvt_sensor_scaled_ax_data[capturing_data_index]);
                        ++capturing_data_index;
                    }

                }

            } else if(urg3d_low_get_binary(this->urg_urg3d, this->auxi_header, data, &this->auxi_data_size_urg3d) > 0) {

                // error check
                if(strncmp(this->auxi_header->type, "ERR", 3) == 0 || strncmp(this->auxi_header->type, "_er", 3) == 0) {
                    printf("error %c%c%c %s", this->auxi_header->status[0], this->auxi_header->status[1], this->auxi_header->status[2], data);
                    if(this->auxi_header->status[0] != '0'){
                        break;
                    }
                }

            }


        } else {
            #ifdef URG_WINDOWS_OS
                Sleep(10);
            #else
                usleep(this->frameinterval);
            #endif
        }
    }
#ifdef PRINT_FUNC
	EXIT_FUNC
#endif
}



void convert_urg3d_point_to_xyzi(const urg3d_point_t *urg3d_point,
                                 double length_scale_coefficient,
                                 double intensity_scale_coefficient,
                                 pcl::PointXYZI &xyzi)
{
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif

    xyzi.data[0] =
        static_cast<float>(length_scale_coefficient * urg3d_point->x_m);
    xyzi.data[1] =
        static_cast<float>(length_scale_coefficient * urg3d_point->y_m);
    xyzi.data[2] =
        static_cast<float>(length_scale_coefficient * urg3d_point->z_m);

    xyzi.data[3] =
        static_cast<float>(intensity_scale_coefficient * urg3d_point->intensity);

#ifdef PRINT_FUNC
	EXIT_FUNC
#endif
    return;
}

void convert_urg3d_point_to_xyzi(const urg3d_point_t *urg3d_point,
                                 pcl::PointXYZI &xyzi)
{
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif

    xyzi.data[0] =
        static_cast<float>(urg3d_point->x_m);
    xyzi.data[1] =
        static_cast<float>(urg3d_point->y_m);
    xyzi.data[2] =
        static_cast<float>(urg3d_point->z_m);

    xyzi.data[3] =
        static_cast<float>(urg3d_point->intensity);

#ifdef PRINT_FUNC
	EXIT_FUNC
#endif
    return;
}

unsigned int add_urg3d_spot_to_point_cloud(const urg3d_spot_t *urg3d_spot,
                                           double length_scale_coefficient,
                                           double intensity_scale_coefficient,
                                           pcl::PointCloud<pcl::PointXYZI>::Ptr &point_cloud_pointer)
{
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif

    const unsigned int number_of_points =
        static_cast<unsigned int>(urg3d_spot->echo_count);

    pcl::PointXYZI temp_point;
    for (unsigned int echo_index = 0; echo_index < number_of_points; ++echo_index) {

        const urg3d_point_t * point =
            &urg3d_spot->point[echo_index];

		convert_urg3d_point_to_xyzi(point,
									length_scale_coefficient,
									intensity_scale_coefficient,
									temp_point);

        point_cloud_pointer->points.push_back(temp_point);

    }
#ifdef PRINT_FUNC
	EXIT_FUNC
#endif

    return number_of_points;
}

unsigned int add_urg3d_spot_to_point_cloud(const urg3d_spot_t *urg3d_spot,
                                           pcl::PointCloud<pcl::PointXYZI>::Ptr &point_cloud_pointer)
{
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif

    const unsigned int number_of_points =
        static_cast<unsigned int>(urg3d_spot->echo_count);

    pcl::PointXYZI temp_point;
    for (unsigned int echo_index = 0; echo_index < number_of_points; ++echo_index) {

        const urg3d_point_t * point =
            &urg3d_spot->point[echo_index];

		convert_urg3d_point_to_xyzi(point, temp_point);
        point_cloud_pointer->points.push_back(temp_point);

    }
#ifdef PRINT_FUNC
	EXIT_FUNC
#endif

    return number_of_points;
}

unsigned int add_urg3d_measurement_data_to_point_cloud(const urg3d_measurement_data_t *urg3d_measurement_data,
                                                       double length_scale_coefficient,
                                                       double intensity_scale_coefficient,
                                                       pcl::PointCloud<pcl::PointXYZI>::Ptr &point_cloud_pointer)
{
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif
    const urg3d_spot_t *spot = NULL;

    unsigned int number_of_added_points = 0;
    for (int spot_index = 0; spot_index < urg3d_measurement_data->spot_count; ++spot_index) {

        spot = &urg3d_measurement_data->spots[spot_index];
        number_of_added_points +=
            add_urg3d_spot_to_point_cloud(spot, length_scale_coefficient,
                                          intensity_scale_coefficient,
                                          point_cloud_pointer);

    }
#ifdef PRINT_FUNC
	EXIT_FUNC
#endif

    return number_of_added_points;
}


unsigned int add_urg3d_measurement_data_to_point_cloud(const urg3d_measurement_data_t *urg3d_measurement_data,
                                                       pcl::PointCloud<pcl::PointXYZI>::Ptr &point_cloud_pointer)
{
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif
    const urg3d_spot_t *spot = NULL;

    unsigned int number_of_added_points = 0;
    for (int spot_index = 0; spot_index < urg3d_measurement_data->spot_count; ++spot_index) {

        spot = &urg3d_measurement_data->spots[spot_index];
        number_of_added_points +=
            add_urg3d_spot_to_point_cloud(spot, point_cloud_pointer);

    }
#ifdef PRINT_FUNC
	EXIT_FUNC
#endif

    return number_of_added_points;
}

//! constants of color for urg3d library with pcl
enum COLOR_CONSTANT_FOR_URG3D_WITH_PCL {
    //! maximum value of hue
    MAXIMUM_VALUE_OF_HUE_IN_HEAT_MAP = 240,

};

static float calculate_rgb_color(float maximum_value, float minimum_value, int hue)
{
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif
    const float inverse_of_60 = 0.01666666666;

    const int recalculate_hue = (hue + 180) % 360;

    if (recalculate_hue < 60.0) {

        return maximum_value + (minimum_value - maximum_value) * static_cast<double>(recalculate_hue) * inverse_of_60;

    } else if (recalculate_hue < 180.0) {

        return minimum_value;

    } else if (recalculate_hue < 240.0) {

        return maximum_value + (minimum_value - maximum_value) * (240.0 - static_cast<double>(recalculate_hue)) * inverse_of_60;

    }
#ifdef PRINT_FUNC
	EXIT_FUNC
#endif

    return maximum_value;
}

static void convert_hls_to_8bit_rgb(const float *hls, float *rgb)
{
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif

    if (hls[2] == 0.0) {

        rgb[0] = hls[1];
        rgb[1] = hls[1];
        rgb[2] = hls[1];

    } else {

        float maximum_value = 0.0;
        if (hls[1] < 0.5) {
            maximum_value = hls[1] * (1 + hls[2]);
        } else {
            maximum_value = hls[1] + hls[2] - hls[1] * hls[2];
        }

        const float minimum_value = 2.0 * hls[1] - maximum_value;

        rgb[0] = calculate_rgb_color(maximum_value, minimum_value, hls[0] + 120.0);
        rgb[1] = calculate_rgb_color(maximum_value, minimum_value, hls[0]);
        rgb[2] = calculate_rgb_color(maximum_value, minimum_value, hls[0] - 120.0);

    }

    const float maximum_8bit_value = 255.0;
    for (unsigned int i = 0; i < 3; ++i) {
        rgb[i] = maximum_8bit_value * rgb[i];
    }
#ifdef PRINT_FUNC
	EXIT_FUNC
#endif

    return;
}

static void calculate_8bit_color_in_heat_map(float saturation, float luminance,
                                             float minimum_value, float maximum_value,
                                             float value, float *rgb_heat_color)
{
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif
    if (minimum_value == maximum_value) {

        for (unsigned int i = 0; i < 3; ++i) {
            rgb_heat_color[i] = 0.0;
        }

        return;
    }

    const float  coefficience_of_hue = static_cast<float>(MAXIMUM_VALUE_OF_HUE_IN_HEAT_MAP) / (maximum_value - minimum_value);

    float restricted_value = value;

    if (value < minimum_value) {
        restricted_value = minimum_value;
    } else if (value > maximum_value) {
        restricted_value = maximum_value;
    }

    float hls[3];
    hls[0] = static_cast<float>(MAXIMUM_VALUE_OF_HUE_IN_HEAT_MAP) - (restricted_value - minimum_value) * coefficience_of_hue;
    hls[1] = luminance;
    hls[2] = saturation;

    convert_hls_to_8bit_rgb(hls, rgb_heat_color);

#ifdef PRINT_FUNC
	EXIT_FUNC
#endif
    return;
}

void calculate_8bit_rgb_heat_color(float saturation, float luminance,
                                   float minimum_value, float maximum_value,
                                   float value, pcl::PointXYZRGB &colored_point)
{
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif
    float rgb[3];

    calculate_8bit_color_in_heat_map(saturation, luminance,
                                     minimum_value, maximum_value,
                                     value, rgb);

    colored_point.r = static_cast<unsigned char>(rgb[0]);
    colored_point.g = static_cast<unsigned char>(rgb[1]);
    colored_point.b = static_cast<unsigned char>(rgb[2]);

#ifdef PRINT_FUNC
	EXIT_FUNC
#endif
    return;
}

void calculate_component_heat_colored_point(float saturation, float luminance,
								            float minimum_value, float maximum_value,
                                            unsigned int value_component_index, const pcl::PointXYZI &point,
                                            pcl::PointXYZRGB &colored_point)
{
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif
    colored_point.x = point.x;
    colored_point.y = point.y;
    colored_point.z = point.z;

    if (value_component_index < 4) {

        calculate_8bit_rgb_heat_color(saturation, luminance,
                                      minimum_value, maximum_value,
                                      point.data[value_component_index],
                                      colored_point);

    } else {

        calculate_8bit_rgb_heat_color(saturation, luminance,
                                      minimum_value, maximum_value,
                                      minimum_value,
                                      colored_point);

    }

#ifdef PRINT_FUNC
	EXIT_FUNC
#endif
    return;
}

void calculate_component_heat_colored_point_cloud(float saturation, float luminance,
                                                  float minimum_value, float maximum_value,
                                                  unsigned int value_component_index,
                                                  const pcl::PointCloud<pcl::PointXYZI>::Ptr &point_cloud_ptr,
                                                  pcl::PointCloud<pcl::PointXYZRGB>::Ptr &colored_point_cloud_ptr)
{
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif

    if (colored_point_cloud_ptr->points.size() != point_cloud_ptr->points.size()) {
        colored_point_cloud_ptr->points.clear();
        colored_point_cloud_ptr->points.resize(point_cloud_ptr->points.size());
    }

    for (unsigned int i = 0; i < point_cloud_ptr->points.size(); ++i) {

        calculate_component_heat_colored_point(saturation, luminance,
                                               minimum_value, maximum_value,
                                               value_component_index,
                                               point_cloud_ptr->points.at(i),
                                               colored_point_cloud_ptr->points.at(i));

    }

#ifdef PRINT_FUNC
	EXIT_FUNC
#endif
    return;
}

bool wait_to_initialize_yvt(urg3d_t *urg,
                                   const std::string &ip_address, long port,
                                   int blocking_timeout)
{
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif
    // connect to device
    std::cout << "Connect to YVT-X002 [" << ip_address << ":" << port << "] ";
    if (urg3d_open(urg, ip_address.c_str(), port) < 0) {

        std::cout << "fails." << std::endl;
        return false;

    }
    std::cout << "success." << std::endl;

    // set timeout for blocking function [msec]
    urg3d_high_set_blocking_timeout_ms(urg, blocking_timeout);

    // initialize urg3d session
    std::cout << "Initialize YVT-X002 session ";
    if (urg3d_high_blocking_init(urg) < 0) {

        urg3d_close(urg);

        std::cout << "fails." << std::endl;
        return false;

    }
    std::cout << "success." << std::endl;

    // wait to initialize
    std::cout << "Wait to initialize... ";
    if (urg3d_high_blocking_wait_finished_initialize(urg) < 0) {

        urg3d_close(urg);

        std::cout << "fails." << std::endl;
        return -1;

    }
    std::cout << "success." << std::endl;
#ifdef PRINT_FUNC
	EXIT_FUNC
#endif
	return true;
}

static bool is_error_vssp_packet(urg3d_t *urg)
{
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif

    // structure for error message
    urg3d_vssp_header_t vssp_header;
    char vssp_data[URG3D_MAX_RX_LENGTH];
    int length_data = 0;

    if (urg3d_low_get_binary(urg, &vssp_header, vssp_data, &length_data) == 1) {

        if (strncmp(vssp_header.type, "ERR", 3) == 0) {

            std::cout << "Error " << vssp_header.status << " " << vssp_data << "\n";
            return true;

        } else if (strncmp(vssp_header.type, "_er", 3) == 0) {

            std::cout << "Error " << vssp_header.status << " " << vssp_data << "\n";
            return true;
        }

    }
#ifdef PRINT_FUNC
	EXIT_FUNC
#endif

    return false;
}

static void sleep_milisecond(unsigned int wait_time_msec)
{
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif

#ifdef URG_WINDOWS_OS
    Sleep(wait_time_msec);
#else
    usleep(wait_time_msec * 1000);
#endif

#ifdef PRINT_FUNC
	EXIT_FUNC
#endif
    return;
}

static pcl::PointCloud<pcl::PointXYZI>::Ptr *drawing_point_cloud = NULL;
static pcl::PointCloud<pcl::PointXYZI>::Ptr *setting_point_cloud = NULL;

static bool drawing = false;

static bool wait_flag_down(const bool *flag,
						   unsigned int timeout_usec, unsigned int sleep_msec)
{
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif
#ifdef URG_WINDOWS_OS
    LARGE_INTEGER past_count;
    QueryPerformanceCounter(&past_count);

    LARGE_INTEGER frequency;
    double frequency_inverse;
    QueryPerformanceFrequency(&frequency);

    const double time_scale_microsecond = 1000.0 * 1000.0;
    if (frequency.QuadPart != 0) {
        frequency_inverse = time_scale_microsecond / static_cast<double>(frequency.QuadPart);
    } else {
        frequency_inverse = 0.0;
    }

    LONGLONG count_difference = 0;

    LARGE_INTEGER current_count;
	while (*flag == true) {

        QueryPerformanceCounter(&current_count);

        if (current_count.QuadPart > past_count.QuadPart) {
            count_difference = current_count.QuadPart - past_count.QuadPart;
        } else {
            const LONGLONG maximum = LLONG_MAX;
            count_difference = current_count.QuadPart + (maximum - past_count.QuadPart);
        }

		if (count_difference * frequency_inverse > timeout_usec) {
			break;
		}

		sleep_milisecond(sleep_msec);

	}
#else

    struct rusage resource;
    struct timeval time_val;
    getrusage(RUSAGE_SELF, &resource);

    time_val = resource.ru_stime;

    const size_t start_time_usec = time_val.tv_sec * 1000000 + time_val.tv_usec;

    size_t current_time_usec = start_time_usec;

    size_t interval_time_usec = 0;

    while (*flag == true) {

        getrusage(RUSAGE_SELF, &resource);

        time_val = resource.ru_stime;

        current_time_usec = time_val.tv_sec * 1000000 + time_val.tv_usec;

        if (current_time_usec > start_time_usec) {
            interval_time_usec = current_time_usec - start_time_usec;
        } else {
            interval_time_usec = current_time_usec + (std::numeric_limits<size_t>::max() - start_time_usec);
        }

        if (interval_time_usec > timeout_usec) {
            break;
        }

		sleep_milisecond(sleep_msec);
	}

#endif

	if (*flag == false) {
		return true;
	}
#ifdef PRINT_FUNC
	EXIT_FUNC
#endif
	return false;
}

static void switch_data_buffer(void)
{
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif
	const unsigned int flag_down_wait_timeout_usec = 100000;
	const unsigned int sleep_msec = 10;

	if (wait_flag_down(&drawing, flag_down_wait_timeout_usec,
					   sleep_msec) == true) {

		drawing = true;
		pcl::PointCloud<pcl::PointXYZI>::Ptr *temp = drawing_point_cloud;

		drawing_point_cloud = setting_point_cloud;
		setting_point_cloud = temp;
		drawing = false;

	}
	drawing = true;
	(*setting_point_cloud)->clear();
	drawing = false;

#ifdef PRINT_FUNC
	EXIT_FUNC
#endif
	return;
}

static void view_initialize(pcl::visualization::PCLVisualizer &view)
{
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif
	view.setBackgroundColor(0.0, 0.0, 0.0);

	std::vector<pcl::visualization::Camera> camera_array;

	view.initCameraParameters();
	view.getCameras(camera_array);

	std::cout << "Number of cameras is " << camera_array.size() << std::endl;

	if (camera_array.size() > 0) {
		pcl::visualization::Camera *initial_camera_position = &camera_array.at(0);

		const double rotation_angle_degree_around_x_axis = 15.0;
		const double rotation_angle_around_x_axis = rotation_angle_degree_around_x_axis * 3.1415926535 / 180.0;

		initial_camera_position->view[0] = sin(rotation_angle_around_x_axis);
		initial_camera_position->view[1] = 0.0;
		initial_camera_position->view[2] = cos(rotation_angle_around_x_axis);

		initial_camera_position->focal[0] = 0.0;
		initial_camera_position->focal[1] = 0.0;
		initial_camera_position->focal[2] = 1.0;

		const double camera_distance = 2.0;

		initial_camera_position->pos[0] = initial_camera_position->focal[0] - camera_distance * cos(rotation_angle_around_x_axis);
		initial_camera_position->pos[1] = initial_camera_position->focal[1];
		initial_camera_position->pos[2] = initial_camera_position->focal[2] + camera_distance * sin(rotation_angle_around_x_axis);

		view.setCameraParameters(*initial_camera_position);
		view.updateCamera();
	}
	const double point_size = 2.0;
	view.setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, point_size);

#ifdef PRINT_FUNC
	EXIT_FUNC
#endif
	return;
}

static bool is_window_closed = false;

static float minimum_value_array[4];
static float maximum_value_array[4];

static unsigned int index_of_component_for_color_gradation = 3;

#define MINIMUM_X_VALUE_FOR_HEAT_COLOR -0.5
#define MAXIMUM_X_VALUE_FOR_HEAT_COLOR 2.5

#define MINIMUM_Y_VALUE_FOR_HEAT_COLOR -5.0
#define MAXIMUM_Y_VALUE_FOR_HEAT_COLOR 5.0

#define MINIMUM_Z_VALUE_FOR_HEAT_COLOR -0.5
#define MAXIMUM_Z_VALUE_FOR_HEAT_COLOR 2.0

#define MINIMUM_INTENSITY_VALUE_FOR_HEAT_COLOR 200.0
#define MAXIMUM_INTENSITY_VALUE_FOR_HEAT_COLOR 1000.0

void keyboard_event(const pcl::visualization::KeyboardEvent &event, void *cookie)
{
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif
	unsigned int changed_index_of_component_for_color_gradation =
		index_of_component_for_color_gradation;

	bool draw_parameter_change = false;

	const unsigned char input_key = event.getKeyCode();

	if (event.keyUp() == true) {
		switch (input_key) {
			case '0':
				++changed_index_of_component_for_color_gradation;
				draw_parameter_change = true;
				break;
			default:
				break;
		}
	}

	if (draw_parameter_change == true) {
		const unsigned int flag_down_wait_timeout_usec = 100000;
	    const unsigned int sleep_msec = 10;

	    if (wait_flag_down(&drawing, flag_down_wait_timeout_usec,
					       sleep_msec) == true) {

			if (changed_index_of_component_for_color_gradation >= 4) {
				changed_index_of_component_for_color_gradation = 0;
			}
			index_of_component_for_color_gradation = changed_index_of_component_for_color_gradation;
			std::cout << "Change draw component " << index_of_component_for_color_gradation << std::endl;

		}

	}
#ifdef PRINT_FUNC
	EXIT_FUNC
#endif

	return;
}

static void draw(void)
{
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif
	const unsigned int draw_interval = 50;
	pcl::visualization::CloudViewer view("vssp pcl test");
	view.runOnVisualizationThreadOnce(view_initialize);

	pcl::PointCloud<pcl::PointXYZRGB>::Ptr colored_point_cloud_ptr(new pcl::PointCloud<pcl::PointXYZRGB>);

	const float saturation = 1.0;
	const float luminance = 0.5;

	minimum_value_array[0] = static_cast<float>(MINIMUM_X_VALUE_FOR_HEAT_COLOR);
	maximum_value_array[0] = static_cast<float>(MAXIMUM_X_VALUE_FOR_HEAT_COLOR);

	minimum_value_array[1] = static_cast<float>(MINIMUM_Y_VALUE_FOR_HEAT_COLOR);
	maximum_value_array[1] = static_cast<float>(MAXIMUM_Y_VALUE_FOR_HEAT_COLOR);

	minimum_value_array[2] = static_cast<float>(MINIMUM_Z_VALUE_FOR_HEAT_COLOR);
	maximum_value_array[2] = static_cast<float>(MAXIMUM_Z_VALUE_FOR_HEAT_COLOR);

	minimum_value_array[3] = static_cast<float>(MINIMUM_INTENSITY_VALUE_FOR_HEAT_COLOR);
	maximum_value_array[3] = static_cast<float>(MAXIMUM_INTENSITY_VALUE_FOR_HEAT_COLOR);

	view.registerKeyboardCallback(keyboard_event);

	while (1) {
		if (view.wasStopped() == true) {
			std::cout << "View window is closed." << std::endl;
			break;
		}

		drawing = true;
		calculate_component_heat_colored_point_cloud(saturation, luminance,
													 minimum_value_array[index_of_component_for_color_gradation],
													 maximum_value_array[index_of_component_for_color_gradation],
													 index_of_component_for_color_gradation, *drawing_point_cloud,
													 colored_point_cloud_ptr);
		drawing = false;
		view.showCloud(colored_point_cloud_ptr);

        sleep_milisecond(draw_interval);
	}

	is_window_closed = true;
#ifdef PRINT_FUNC
	EXIT_FUNC
#endif

	return;
}

void urg3d::urg3d_pcl_display()
{
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif
    std::cout << "Start display program." << std::endl;

    // default ip address
    //const std::string ip_address = this->connect_address_urg3d;
    // deault port
    //const int port = this->connect_port_urg3d;
    // timeout for blocking process [msec]
   // const int blocking_timeout = this->blockfunctimeout;

    urg3d_t *urg = this->urg_urg3d;
    /*if (wait_to_initialize_yvt(&urg, ip_address, port,
                               blocking_timeout) == false) {
        return -1;
    }*/

    // set interlace
    /*const int interlace_count = this->interlacecount;
    std::cout << "Set interlace count " << interlace_count << " ";
    if (urg3d_high_blocking_set_interlace_count(&urg, interlace_count) < 0) {

        urg3d_close(&urg);

        std::cout << "fails." << std::endl;
        return -1;

    }
    std::cout << "success." << std::endl;*/

    // start data stream (distance and intensity)
    /*std::cout << "Start data stream ";
    if (urg3d_high_start_data(&urg, URG3D_DISTANCE_INTENSITY) < 0) {

        urg3d_close(&urg);

        std::cout << "fails." << std::endl;
        return -1;

    }
    std::cout << "success." << std::endl;*/

    // interval of checking receive [msec]
    unsigned int receive_check_interval = 5;

    // structure for measurement data
    urg3d_measurement_data_t measurement_data;

    //const double point_coefficient = 1000.0;

    int past_frame_index = -1;

	pcl::PointCloud<pcl::PointXYZI>::Ptr point_cloud1(new pcl::PointCloud<pcl::PointXYZI>);
	pcl::PointCloud<pcl::PointXYZI>::Ptr point_cloud2(new pcl::PointCloud<pcl::PointXYZI>);

	drawing_point_cloud = &point_cloud1;
	setting_point_cloud = &point_cloud2;

	boost::thread draw_thread(&draw);

    while (1) {
		if (is_window_closed == true) {
			std::cout << "Stop data communication." << std::endl;
			draw_thread.join();
			break;
		}

        // if event does not occur, sleep to wait receive event
        if (urg3d_next_receive_ready(urg) == 0) {

            sleep_milisecond(receive_check_interval);

            continue;
        }

        // handle measurement data
        if (urg3d_high_get_measurement_data(urg, &measurement_data) == 1) {

            if ((past_frame_index == - 1) &&
                (measurement_data.line_number == 0) &&
                (measurement_data.field_number == 0)) {
                past_frame_index = measurement_data.frame_number;

            }

            if (past_frame_index == -1) {
                continue;
            }
			add_urg3d_measurement_data_to_point_cloud(&measurement_data, *setting_point_cloud);

            // renew frame
            if ((past_frame_index != -1) &&
                (past_frame_index != measurement_data.frame_number)) {

				switch_data_buffer();
				past_frame_index = measurement_data.frame_number;

            }

        // handle error packet
        } else if (is_error_vssp_packet(urg) == true) {

            std::cout << "Error packet." << std::endl;

        }


    }
    /*std::cout << "Stop data stream ";
    if (urg3d_high_stop_data(&urg, URG3D_DISTANCE_INTENSITY) < 0) {

        urg3d_close(&urg);

        std::cout << "fails." << std::endl;
        return -1;

    }
    std::cout << "success." << std::endl;*/

	// interval of checking receive [msec]
    /*unsigned int end_waiting_interval = 100;
    sleep_milisecond(end_waiting_interval);
    // disconnect
    std::cout << "Disconnect ot YVT-X002 ";

    if (urg3d_close(&urg) < 0) {

        std::cout << "fails." << std::endl;
        return -1;

    }

    std::cout << "success." << std::endl;
    std::cout << "Main loop is ended." << std::endl;*/

#ifdef PRINT_FUNC
	EXIT_FUNC
#endif
    return;
}
