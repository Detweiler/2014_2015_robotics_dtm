/**
 * @file    MyRobot.h
 * @brief   with this controller the robot use odoemtry with the encoders to reach the point
 *
 * @author  Diego Torres Mollejo <100290865@alumnos.uc3m.es>
 * @date    11/11/2014
 */
#include <iostream>
#include <cmath>
#include <webots/DifferentialWheels.hpp>

using namespace std;
using namespace webots;

#define MAX_SPEED           100
#define ENCODER_RESOLUTION  5
#define radio               0.0825
#define AXLELENGTH          0.32

class MyRobot : public DifferentialWheels {
    private:
        int _time_step;
        double _distance;
        double _incremental_distance_right, _incremental_distance_left;
        double _posicion0, _posicion1, _posicion2;
        double _posicion2_grados;

        int _state;
        double _odometry_error;

        Compass * _my_compass;

        double _left_speed, _right_speed;
        double _left_encoder, _right_encoder;
        double _last_left_encoder, _last_right_encoder;
        double _total_left_increment, _total_right_increment;

	 /**
         * @brief a function to introduce the desire point
	 * @param distance we want to reach and angle we want 
	 * @return  
	 * 
         */        
	void go_forward(double distance_desired, double angle_desired);
 	/**
         * @brief a function to reset the encoders
         */ 
       void reset_encoders();

    public:
        /**
         * @brief Empty constructor of the class.
         */
        MyRobot();

        /**
         * @brief Destructor of the class.
         */
        ~MyRobot();

        /**
         * @brief User defined function for initializing and running the template class.
         */
        void run();

        /**
          * @brief An example for converting bearing vector from compass to angle (in degrees).
          */
        double convert_bearing_to_degrees(const double* in_vector, bool option);
};
