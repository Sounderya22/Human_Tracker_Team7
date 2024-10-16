/**
 * @file AcmeBot.cpp
 * @author Amogha Sunil
 * @brief C++ source file for AcmeBot pipeline
 * @version 0.1
 * @date 2024-10-16
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "AcmeBot.hpp"

/**
 * @brief Constructs a new Acme Bot object
 * 
 */
acmebot::AcmeBot::AcmeBot() {

}

/**
 * @brief Destructor for the Acme Bot class
 * 
 */
acmebot::AcmeBot::~AcmeBot() {

}

/**
 * @brief Calls tracker class to retreive trackpoints of detections and calculates 3D coordinates
 * @startuml
 * @startuml
    : start
    : Initialize Camera;
    : Capture Frame;
        repeat
            : Process Frame;
            : Detect Humans;
            if (Humans Detected?) then (yes)
                : Track Humans;
                : Transform Coordinates;
            else (no)
                : No Action;
            endif
        repeat while (More Frames?)
    : stop
 * @enduml
 */
void acmebot::AcmeBot::Process() {
   /*implementation of acmebot process*/
}

/**
 * @brief Sets required intrinsics for transformations
 * 
 */
void acmebot::AcmeBot::setIntrinsics() {

}

/**
 * @brief Converts points from camera's reference frame to robot frame
 * 
 */
void acmebot::AcmeBot::transformPoints() {

}
