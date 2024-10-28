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
#include <eigen3/Eigen/Eigen>

struct intrinsics {
    double focalLength{0.0};
};

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

        VisualControl(bool sRawStream, bool sProcessedStream): showRawStream(sRawStream),
                                                               showProcessedStream(sProcessedStream) {
        };
    };

    class AcmeVision {
    private:
        /* Camera parameters */
        intrinsics mIntrinsics;
        int mFrameRate{0};
        /*OpenCV video capture*/
        int mCapture{0};

        std::shared_ptr<moodycamel::ReaderWriterQueue<cv::Mat> > mFrameQueue;
        // std::shared_ptr<moodycamel::ReaderWriterQueue<acmebot::DetectedObject>> mDetectedObjectQueue;
        std::shared_ptr<moodycamel::ReaderWriterQueue<acmebot::Pose>> mOutputQueue;
        cv::VideoCapture cap_;
        cv::Mat p_frame_;
        cv::Size p_size_;
        int frame_width_{};
        int frame_height_{};
        int frame_rate_{};
        double mFocalLength{};
        uint8_t mcameraId_{};
        double mcFactor_{};
        double mavgHumanHeight_{};
        int raw_width{};
        int raw_height{};
        bool initCamera();
        bool initTestData();
        acmebot::Pose mrobotPose;
        acmebot::Pose mcamPose;
        int mcalib_{};

        std::unique_ptr<Detector> mDetector;
        std::unique_ptr<Tracker> mTracker;

    public:
        /**
        * @brief Function to set robot pose
        * Used in calculating final transforms
        */
        bool SetRobotPose(const Pose &robo_pose);

        /**
        * @brief Function to set camera pose
        * Used in calculating final transforms
        */
        bool SetCameraPose(const Pose &cam_pose);
        /**
        * @brief Function to set capture frame size
        * @param w width of capture frame
        * @param h height of capture frame
        * @return True if operation is success else False
        */
        bool SetProcessingSize(int w, int h);

        /**
        * @brief
        */
        VisualControl windowControl;
        /**
        * @brief Shared queue containing all the poses.
        */
        std::shared_ptr<moodycamel::ReaderWriterQueue<acmebot::HumanPoses> > mPoseQueue;

        /**
         * @brief Constructs a new Acme Vision object
         * 
         */
        explicit AcmeVision(int8_t camId);

        /**
         * @brief Constructs a new Acme Vision object with specified file path
         * file can be in form of video/ image
         *
         */
        explicit AcmeVision(std::string filePath);

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
        * @brief Calculate the Intrinsics of camera
        * Intrinsics are required to correctly map human from pixels to robot frame
        */
        void setIntrinsics();

        /**
        * @brief Set the Focal Length of the camera
        *
        * @param focal_length
        */
        void SetFocalLength(double focal_length);

        /**
        * @brief Converts points from camera's reference frame to robot frame
        * 
        */
        void transformPoints(const std::vector<cv::Rect> &tracks);
    };
} //namespace

#endif
