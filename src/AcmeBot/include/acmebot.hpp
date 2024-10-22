/**
 * @file acmebot.hpp
 * @author  Sounderya
            Amogha Sunil
            Anirudh Swarankar
 * @brief C++ header file for AcmeBOt Class
 * @version 0.1
 * @date 2024-10-16
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef _H_ACMEBOT_H_
#define _H_ACMEBOT_H_

#include "tracker.hpp"

struct intrinsics{
    double focalLength{0.0};
};

namespace acmebot {
class AcmeBot {
    private:
        /* Camera parameters */
        intrinsics mIntrinsics;    
        int mFrameRate{0};      
        /*OpenCV video capture*/
        int mCapture{0};              
        /*tracker object*/
        acmebot::Tracker mTracker;  
    public:
        /**
         * @brief Constructs a new Acme Bot object
         * 
         */
        AcmeBot();

        /**
         * @brief Destructor for the Acme Bot class
         * 
         */
        ~AcmeBot();

        /**
        * @brief Calls tracker class to retreive trackpoints of detections and calculates 3D coordinates
        * 
        * 
        */
        void Process();

        /**
        * @brief Sets required intrinsics for transformations
        * 
        */
        void setIntrinsics();

        /**
        * @brief Converts points from camera's reference frame to robot frame
        * 
        */
        void transformPoints();
};
} //namespace

#endif