#ifndef _MY_ROBOT_H_
#define _MY_ROBOT_H_
/**
  @file obstacle_avoidance.cpp
  @brief controller that make the robot reach a point avoiding obstacles
  @author Diego Torres Mollejo
  @date 4/11/2014

*/

#include <iostream>
#include <cmath>
#include <webots/DifferentialWheels.hpp>

using namespace std;
using namespace webots;

#define NUM_DISTANCE_SENSOR 16
#define DISTANCE_LIMIT      200
#define MAX_SPEED           70
#define DESIRED_ANGLE   45.0

class MyRobot : public DifferentialWheels {
    private:
        int _time_step;

        Compass * _my_compass;
        DistanceSensor * _distance_sensor[NUM_DISTANCE_SENSOR];
        double _left_speed, _right_speed;

        enum Mode {
            STOP,
            FORWARD,
            TURN_LEFT,
            TURN_RIGHT,
            FAST_TURNRIGHT,
	    FAST_TURNLEFT,
            OBSTACLE_AVOIDLEFT,
	    OBSTACLE_AVOIDRIGHT
        };

        Mode _mode;

    public:
        // You may need to define your private methods or variables, like
        //  Constructors, helper functions, etc.

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
	 * @param value of the compass
	 * @return return degrees in double 
         */
        void run();

        double convert_bearing_to_degrees(const double* in_vector);
};

#endif

