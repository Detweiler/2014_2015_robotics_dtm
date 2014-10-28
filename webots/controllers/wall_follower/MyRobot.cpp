/**
 * @file    MyRobot.cpp
 * @brief   A simple example for maintaining a straight line with the compass.
 *
 * @author  Raul Perula-Martinez <raul.perula@uc3m.es>
 * @date    2014-07
 */

#include "MyRobot.h"

//////////////////////////////////////////////

MyRobot::MyRobot() : DifferentialWheels()
{
    _time_step = 64;

    _left_speed = 0;
    _right_speed = 0;

    _mode = FORWARD;

    // Get and enable the distance sensors
    _distance_sensor[0] = getDistanceSensor("ds0");
    _distance_sensor[0]->enable(_time_step);
    _distance_sensor[1] = getDistanceSensor("ds1");
    _distance_sensor[1]->enable(_time_step);
    _distance_sensor[2] = getDistanceSensor("ds2");
    _distance_sensor[2]->enable(_time_step);
    _distance_sensor[3] = getDistanceSensor("ds3");
    _distance_sensor[3]->enable(_time_step);
    _distance_sensor[4] = getDistanceSensor("ds12");
    _distance_sensor[4]->enable(_time_step);
    _distance_sensor[5] = getDistanceSensor("ds13");
    _distance_sensor[5]->enable(_time_step);
    _distance_sensor[6] = getDistanceSensor("ds14");
    _distance_sensor[6]->enable(_time_step);
    _distance_sensor[7] = getDistanceSensor("ds15");
    _distance_sensor[7]->enable(_time_step);
}


//////////////////////////////////////////////

MyRobot::~MyRobot()
{
    for (int i=0; i<NUM_DISTANCE_SENSOR; i++) {
            _distance_sensor[i]->disable();
        }
}

//////////////////////////////////////////////

void MyRobot::run()
{
    double ir15_val = 0.0, ir14_val = 0.0, ir13_val = 0.0, ir12_val = 0.0, 
		ir0_val = 0.0, ir1_val = 0.0, ir2_val = 0.0, ir3_val = 0.0;

    while (step(_time_step) != -1) {

        // Read the sensors and get the value of then
        ir0_val = _distance_sensor[0]->getValue();
        ir1_val = _distance_sensor[1]->getValue();
        ir2_val = _distance_sensor[2]->getValue();
        ir3_val = _distance_sensor[3]->getValue();
        ir12_val = _distance_sensor[4]->getValue();
        ir13_val = _distance_sensor[5]->getValue();
        ir14_val = _distance_sensor[6]->getValue();
        ir15_val = _distance_sensor[7]->getValue();

        // Control logic of the robot, , depending of the valor of the sensor the robor will do a diferent thing
        if (_mode == FORWARD) {
            // Move forward
            cout<<"Moving forward, no wall detected"<<endl;
            // When sufficiently close to a wall in front of robot,
            // switch mode to wall following
            if ((ir0_val > DISTANCE_LIMIT) || (ir1_val > DISTANCE_LIMIT) ||(ir14_val > DISTANCE_LIMIT) ||(ir15_val > DISTANCE_LIMIT)) {
                _mode = WALL_FOLLOWER;
                cout << "Mode " << WALL_FOLLOWER << ": Following the wall" << endl;
            }
        }
        else {
            // Wall following

            if ((ir0_val > DISTANCE_LIMIT) || (ir1_val > DISTANCE_LIMIT) ||(ir14_val > DISTANCE_LIMIT) ||(ir15_val > DISTANCE_LIMIT)){
                _mode = WALL_FOLLOWER;
                cout << "Backing up and turning left." << endl;
            }
            else {
                if (ir13_val > DISTANCE_LIMIT) {
                    _mode = TURN_LEFT;
                    cout << "Turning left." << endl;
                }
                else {
                    if (ir13_val < DISTANCE_LIMIT + 50) {
                        _mode = TURN_RIGHT;
                        cout << "Turning right." << endl;
                    }
                    else {
                        _mode = FORWARD;
                        cout << "Moving forward." << endl;
                    }
                }
            }
        }

        // Send actuators commands according to the mode
        switch (_mode){
            case STOP:
                _left_speed = 0;
                _right_speed = 0;
                break;
            case FORWARD:
                _left_speed = MAX_SPEED;
                _right_speed = MAX_SPEED;
                break;
            case TURN_LEFT:
                _left_speed = MAX_SPEED / 1.25;
                _right_speed = MAX_SPEED;
                break;
            case TURN_RIGHT:
                _left_speed = MAX_SPEED;
                _right_speed = MAX_SPEED / 1.25;
                break;
            case WALL_FOLLOWER:
                _left_speed = -MAX_SPEED / 3.0;
                _right_speed = -MAX_SPEED / 20.0;
                break;
            default:
                break;
        }



        // Print the value of the sensors of the robot


        cout << endl <<"Left sensors: dist0: " << ir0_val << " dist1:" << ir1_val << " dist2:" << ir2_val<< " dist3:"  << ir3_val << endl << "Right sensors: dist12:" << ir12_val<< " dist13:" << ir13_val<< " dist14:" << ir14_val<< " dist15:" << ir15_val<< endl<< endl << endl;



        // Set the motor speeds
        setSpeed(_left_speed, _right_speed);

    }
}


