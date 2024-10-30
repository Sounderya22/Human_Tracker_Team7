
/**
 * @file tracker.hpp
 * @author  Sounderya
            Amogha Sunil
 * @brief C++ header file for AcmeBOt Class
 * @version 0.1
 * @date 2024-10-16
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef _H_TRACKER_H_
#define _H_TRACKER_H_

// #include "acme_vision.hpp"
#include "detector.hpp"

namespace acmebot {
  struct Obstacle {
        int id;
        double depth;
    };

class Tracker {
    public:
        Tracker();
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
    std::vector<Obstacle> obstacles;
    std::map<int, cv::Rect> objects; // Map of object IDs to bounding boxes
    int nextId{0};
};
} //namespace

#endif