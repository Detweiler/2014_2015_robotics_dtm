/**
 * @file    lines_detector.cpp
 * @brief  controller that make the robot detect a yellow line
 *
 * @author  Diego Torres Mollejo <100290865@alumnos.uc3m.es>
 * @date    2014-07
 */

#include "MyRobot.h"

//////////////////////////////////////////////

MyRobot::MyRobot() : DifferentialWheels()
{
    _time_step = 64;

    _left_speed = 0;
    _right_speed = 0;


    _spherical_camera = getCamera("camera_s");
    _spherical_camera->enable(_time_step);
}

//////////////////////////////////////////////

MyRobot::~MyRobot()
{

    _spherical_camera->disable();
}

//////////////////////////////////////////////

void MyRobot::run()
{
    int sum = 0;
    unsigned char green = 0, red = 0, blue = 0;
    double percentage_yellow = 0.0;


    // Get size of images for spherical camera
    int image_width_s = _spherical_camera->getWidth();
    int image_height_s = _spherical_camera->getHeight();
    cout << "Size of spherical camera image: " << image_width_s << ", " << image_height_s << endl;

    while (step(_time_step) != -1) {
        sum = 0;

        // Get current image from forward camera
        const unsigned char *image_s = _spherical_camera->getImage();

        // Count number of pixels that are white
        // (here assumed to have pixel value > 245 out of 255 for all color components)
        for (int x = 0; x < image_width_s; x++) {
            for (int y = 0; y < image_height_s; y++) {
                green = _spherical_camera->imageGetGreen(image_s, image_width_s, x, y);
                red = _spherical_camera->imageGetRed(image_s, image_width_s, x, y);
                blue = _spherical_camera->imageGetBlue(image_s, image_width_s, x, y);

                if ((green > 245) && (red > 245) && (blue > 0)) {
                    sum = sum + 1;
                }
            }
        }

        percentage_yellow = (sum / (float) (image_width_s * image_height_s)) * 100;
        cout << "Percentage of yellow in spherical camera image: " << percentage_yellow << endl;

        // Turn around slowly
        _left_speed = 5;
        _right_speed = -5;

        // Set the motor speeds
        setSpeed(_left_speed, _right_speed);

        if (percentage_yellow > 8 ){
            cout << "yellow line aproaching" << endl;

            if (percentage_yellow > 10 ){
                cout << "yellow line APROACHING" << endl;

                if (percentage_yellow > 14 ){
                    cout << "yellow line reach." << endl << endl;
                    setSpeed (0, 0);
                }
            }
        }

    }
}

//////////////////////////////////////////////
