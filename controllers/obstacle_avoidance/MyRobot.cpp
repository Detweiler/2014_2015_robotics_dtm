#include "MyRobot.h"

//////////////////////////////////////////////

MyRobot::MyRobot() : DifferentialWheels()
{
    _time_step = 64;

    _left_speed = 0;
    _right_speed = 0;

    _mode = FORWARD;

    _distance_sensor[0] = getDistanceSensor("ds0");
    _distance_sensor[0]->enable(_time_step);
    _distance_sensor[1] = getDistanceSensor("ds1");
    _distance_sensor[1]->enable(_time_step);
    _distance_sensor[2] = getDistanceSensor("ds2");
    _distance_sensor[2]->enable(_time_step);
    _distance_sensor[3] = getDistanceSensor("ds3");
    _distance_sensor[3]->enable(_time_step);
    _distance_sensor[4] = getDistanceSensor("ds4");
    _distance_sensor[4]->enable(_time_step);
    _distance_sensor[5] = getDistanceSensor("ds5");
    _distance_sensor[5]->enable(_time_step);
    _distance_sensor[6] = getDistanceSensor("ds6");
    _distance_sensor[6]->enable(_time_step);
    _distance_sensor[7] = getDistanceSensor("ds7");
    _distance_sensor[7]->enable(_time_step);
    _distance_sensor[8] = getDistanceSensor("ds8");
    _distance_sensor[8]->enable(_time_step);
    _distance_sensor[9] = getDistanceSensor("ds9");
    _distance_sensor[9]->enable(_time_step);
    _distance_sensor[10] = getDistanceSensor("ds10");
    _distance_sensor[10]->enable(_time_step);
    _distance_sensor[11] = getDistanceSensor("ds11");
    _distance_sensor[11]->enable(_time_step);
    _distance_sensor[12] = getDistanceSensor("ds12");
    _distance_sensor[12]->enable(_time_step);
    _distance_sensor[13] = getDistanceSensor("ds13");
    _distance_sensor[13]->enable(_time_step);
    _distance_sensor[14] = getDistanceSensor("ds14");
    _distance_sensor[14]->enable(_time_step);
    _distance_sensor[15] = getDistanceSensor("ds15");
    _distance_sensor[15]->enable(_time_step);

   _my_compass = getCompass("compass");
   _my_compass->enable(_time_step);
}

//////////////////////////////////////////////

MyRobot::~MyRobot()
{
    for (int i=0; i<NUM_DISTANCE_SENSOR; i++) {
        _distance_sensor[i]->disable();
    }
    _my_compass->disable();
}

//////////////////////////////////////////////

void MyRobot::run()
{
    double ir0_val = 0.0, ir1_val = 0.0, ir2_val = 0.0, ir3_val = 0.0, ir4_val = 0.0, ir5_val = 0.0, ir6_val = 0.0, ir7_val= 0.0, ir8_val = 0.0, ir9_val = 0.0, ir10_val = 0.0, ir11_val = 0.0, ir12_val = 0.0, ir13_val = 0.0, ir14_val = 0.0, ir15_val = 0.0;
    int turn_right_First=0;
    int turn_left_First=0;

    double compass_angle;

    while (step(_time_step) != -1) {
       
        
        const double *compass_val = _my_compass->getValues();

        //  the robot get the values of all the sensors using the fuctions below
        compass_angle = convert_bearing_to_degrees(compass_val);

        ir0_val = _distance_sensor[0]->getValue();
        ir1_val = _distance_sensor[1]->getValue();
        ir2_val = _distance_sensor[2]->getValue();
        ir3_val = _distance_sensor[3]->getValue();
        ir4_val = _distance_sensor[4]->getValue();
        ir5_val = _distance_sensor[5]->getValue();
        ir6_val = _distance_sensor[6]->getValue();
        ir7_val = _distance_sensor[7]->getValue();
        ir8_val = _distance_sensor[8]->getValue();
        ir9_val = _distance_sensor[9]->getValue();
        ir10_val = _distance_sensor[10]->getValue();
        ir11_val = _distance_sensor[11]->getValue();
        ir12_val = _distance_sensor[12]->getValue();
        ir13_val = _distance_sensor[13]->getValue();
        ir14_val = _distance_sensor[14]->getValue();
        ir15_val = _distance_sensor[15]->getValue();

        cout << endl;
        

        // we add all the distances of the sensors to prove there is not obstacle near the robot
        if((ir0_val + ir1_val + ir2_val + ir3_val + ir4_val + ir5_val + ir6_val + ir7_val + ir8_val + ir9_val + ir10_val + ir11_val + ir12_val + ir13_val + ir14_val + ir15_val) <= 300)
        {
           cout<<"robot is following: COMPASS"<<endl;

            // this if control the movement of the robot if it is following the compass ant there is not a obstacle
            if (compass_angle > (DESIRED_ANGLE + 2))
            {
                // Turn left
                _left_speed = MAX_SPEED - 15;
                _right_speed = MAX_SPEED;
               
            }
            else
            {
                if (compass_angle < (DESIRED_ANGLE - 2))
                { 
                    // Turn right
                    _left_speed = MAX_SPEED;
                    _right_speed = MAX_SPEED - 15;
                }
                else
                {    
                    // Move straight forward
                    _left_speed = MAX_SPEED;
                    _right_speed = MAX_SPEED;
                }
            }
        }
        else 
        {
            if ((ir12_val == 0)&&(ir11_val != 0)&&(turn_right_First>=1)&&(ir14_val == 0))
            {
               _mode = FAST_TURNRIGHT;
                cout << "turn right faster" << endl;
            }
            else
            {
                if ((ir3_val == 0)&&(ir4_val != 0)&&(turn_left_First>=1)&&(ir1_val == 0))
                {
               _mode = FAST_TURNLEFT;
                cout << "turn left faster" << endl;
                }
		    
               else
                  {  turn_right_First= turn_right_First+1;
                     if((ir3_val + ir12_val <= 200)&&((ir1_val+ir2_val) <= (ir14_val+ir15_val)))
                      {
                        _mode = TURN_RIGHT;
                      }
                      else
                       {
                        if ((ir1_val > DISTANCE_LIMIT+500) || (ir2_val > DISTANCE_LIMIT+500) || (ir14_val > DISTANCE_LIMIT)) {
                            _mode = OBSTACLE_AVOIDLEFT;
                            cout << "Backing up and turning left." << endl;
                          }
                        else {
                            if ((ir14_val > DISTANCE_LIMIT+500) || (ir13_val > DISTANCE_LIMIT+500) || (ir1_val > DISTANCE_LIMIT)){
                                _mode = OBSTACLE_AVOIDRIGHT;
                                cout << "Backing up and turning right." << endl;}

                            else {
                                _mode = FORWARD;
                                cout << "Moving forward." << endl;}
                             }
                     }
                   }
            }
          }


            // Set the speed of the wheels of the robot depending of the mode
            switch (_mode)
            {
                case STOP:
                    _left_speed = 0;
                    _right_speed = 0;
                    break;
                case FORWARD:
                    _left_speed = MAX_SPEED;
                    _right_speed = MAX_SPEED;
                    break;
                case TURN_LEFT:
                    _left_speed = MAX_SPEED / 1.5;
                    _right_speed = MAX_SPEED;
                    break;
                case TURN_RIGHT:
                    _left_speed = MAX_SPEED;
                    _right_speed = MAX_SPEED / 1.5;
                    break;
                case FAST_TURNLEFT:
                    _left_speed = MAX_SPEED /20;
                    _right_speed = MAX_SPEED;
                    break;
                case FAST_TURNRIGHT:
                    _left_speed = MAX_SPEED;
                    _right_speed = MAX_SPEED / 20;
                    break;
                case OBSTACLE_AVOIDLEFT:
                    _left_speed = -MAX_SPEED / 3.0;
                    _right_speed = -MAX_SPEED / 20.0;
                    break;
                case OBSTACLE_AVOIDRIGHT:
                    _left_speed = -MAX_SPEED / 20.0;
                    _right_speed = -MAX_SPEED / 3.0;
                    break;
                default:
                    break;
            }
            // Set the motor speeds
            setSpeed(_left_speed, _right_speed);
        }


}



//////////////////////////////////////////////
double MyRobot::convert_bearing_to_degrees(const double* in_vector)
{
    double rad = atan2(in_vector[0], in_vector[2]);
    double deg = rad * (180.0 / M_PI);

    return deg;
}
