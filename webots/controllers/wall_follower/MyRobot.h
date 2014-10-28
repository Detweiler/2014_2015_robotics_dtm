/**
 * @file    MyRobot.h
 * @brief   A simple example for maintaining a straight line with the compass.
 *
 * @author  Raul Perula-Martinez <raul.perula@uc3m.es>
 * @date    2014-07
 */

#include <iostream>
#include <cmath>
#include <webots/DifferentialWheels.hpp>

using namespace std;
using namespace webots;

#define MAX_SPEED       100
#define NUM_DISTANCE_SENSOR 8
#define DISTANCE_LIMIT      100

class MyRobot : public DifferentialWheels {
    private:
        int _time_step;
        DistanceSensor * _distance_sensor[NUM_DISTANCE_SENSOR];
        double _left_speed, _right_speed;
        enum Mode {
                    STOP,
                    FORWARD,
                    TURN_LEFT,
                    TURN_RIGHT,
                    WALL_FOLLOWER
                  };

        Mode _mode;

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
};
