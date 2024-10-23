/**
 * @file acme_vision.hpp
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
#include <future>
#include "Utils.hpp"
#include "tracker.hpp"
#include "detector.hpp"
#include <readerwriterqueue.h>
#include <utility>
#include <vector>
#include <spdlog/spdlog.h>

struct intrinsics {
    double focalLength{0.0};
};

namespace acmebot {
    /**
    * @brief Pose of human in Robot frame
    */
    struct HumanPose {
        /**
        * @brief X coordinate of the pose
        */
        double x;
        /**
        * @brief Y coordinate of the pose
        */
        double y;
        /**
        * @brief Z coordinate of the pose
        */
        double z;
    };

    /**
    * @brief Collection of all human poses and additional information.
    */
    struct HumanPoses {
        std::vector<HumanPose> poses;
    };

    /**
    * @brief Collection of all data passed to tracker from detection class
    * Structure passed to process via shared queue ( single producer single consumer )
*/
    struct DetectedObject {
        // to be filled
        int id;
    };

    struct VisualControl {
        bool showRawStream;
        bool showProcessedStream;
        VisualControl(bool sRawStream, bool sProcessedStream): showRawStream(sRawStream), showProcessedStream(sProcessedStream) {};
    };

    class AcmeVision {
    private:
        /* Camera parameters */
        intrinsics mIntrinsics;
        int mFrameRate{0};
        /*OpenCV video capture*/
        int mCapture{0};

        std::shared_ptr<moodycamel::ReaderWriterQueue<cv::Mat>> mFrameQueue;
        // std::shared_ptr<moodycamel::ReaderWriterQueue<acmebot::DetectedObject>> mDetectedObjectQueue;
        // std::future<bool> mDetectorToTracker;
        cv::VideoCapture cap_;
        cv::Mat p_frame_;
        cv::Size p_size_;
        int frame_width_;
        int frame_height_;
        int frame_rate_;
        uint8_t mcameraId_;
        bool initCamera();

        std::unique_ptr<Detector> mDetector;
        std::unique_ptr<Tracker> mTracker;

    public:
        /**
        * @brief
        */
        VisualControl windowControl;
        /**
        * @brief Shared queue containing all the poses.
        */
        std::shared_ptr<moodycamel::ReaderWriterQueue<acmebot::HumanPoses>> mPoseQueue;

        /**
         * @brief Constructs a new Acme Vision object
         * 
         */
        AcmeVision(const int8_t camId);

        /**
         * @brief Destructor for the Acme Bot class
         * 
         */
        ~AcmeVision();

        /**
        * @brief Calls tracker class to retreive trackpoints of detections and calculates 3D coordinates
        * 
        * 
        */
        void ProcessCameraFrame();

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
