
/**
 * @file tracker.hpp
 * @author  Sounderya
            Amogha Sunil
 * @brief C++ header file for tracker Class
 * @version 0.1
 * @date 2024-10-16
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef _H_TRACKER_H_
#define _H_TRACKER_H_

#include "detector.hpp"

namespace acmebot {
class Tracker {
    public:
        /**
        * @brief Constructor for the Tracker class
        * 
        */
        Tracker();

        /**
        * @brief Destructor for the Tracker class
        * 
        */
        ~Tracker();

        /**
         * @brief Takes frame-wise detections to track humans
         * 
         */
        void Process(cv::Mat &frame, std::vector<cv::Rect> &detectedFaces);
        
        /**
         * @brief Sets parameters that are private to class
         * 
         */
        void setParameters();

    private:
        acmebot::Detector mDetector;
};
} //namespace

#endif