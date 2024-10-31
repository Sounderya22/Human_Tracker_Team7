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
#include <utility>
#include <vector>
#include <spdlog/spdlog.h>

namespace acmebot {

class AcmeVision {
    private:
        int mFrameRate{0};
        /*OpenCV video capture*/
        int mCapture{0};

        cv::Mat p_frame_;
        int calib_factor = 1;

        ///output from tracker method
        std::vector<cv::Rect> mdetectedFaces;

        ///robot reference frame poses
        std::vector<acmebot::Pose> robotFPoses;
        
        ///tracker instance
        std::unique_ptr<Tracker> mTracker;

        ///utils instance
        std::unique_ptr<Utils> mUtils;

    public:
        /**
         * @brief Constructs a new Acme Vision object
         * 
         */
        AcmeVision();

        /**
         * @brief Destructor for the Acme Bot class
         * 
         */
        ~AcmeVision();

        /**
        * @brief grabs the current frame data from live camera stream
        *@startuml
           :start
           : actor User
           : participant "VideoCapture" as Cap
           : participant "Frame" as Frame
           : User -> Cap: Create instance (cap(0))
           : Cap -> Cap: set(CAP_PROP_FRAME_HEIGHT, 480)
           : Cap -> Cap: set(CAP_PROP_FRAME_WIDTH, 640)
           : Cap -> Cap: isOpened()
             alt If Camera Opened
               : Cap -> Cap: read(p_frame_)
               : User -> Frame: Frame Captured
            else If Camera Not Opened
               : User -> User: Log Error("Cannot read frame")
            end
        * @enduml
        */
        void ProcessCameraFrame();

        /**
        * @brief Calls tracker class to retreive trackpoints of detections and calculates 3D coordinates
        * @startuml
            : start
            :actor User
            :participant "AcmeVision" as Vision
            :participant "Camera" as Camera
            :participant "Tracker" as Tracker
            :participant "DetectedFaces" as DetectedFaces
            :participant "RobotFPoses" as RobotFPoses
            :participant "OpenCV" as OpenCV

            :User -> Vision: Process()
            :Vision -> Camera: ProcessCameraFrame()
            :Vision -> Tracker: Process(p_frame_, mDetectedFaces)
            :Tracker -> DetectedFaces: Update detected faces
            :Vision -> Vision: transformPoints(robotFPoses)
            :Vision -> OpenCV: imshow("acmeVision Process", p_frame_)
            :OpenCV -> Vision: Display frame
            :Vision -> OpenCV: waitKey(1)
            :alt If key is ESC or 'q'
                :Vision -> User: return
            :end
        * @enduml
        */
        void Process();

        /**
        * @brief Converts points from camera's reference frame to robot frame
        * @startuml
            :actor User
            :participant "AcmeVision" as Vision
            :participant "Utils" as Utils
            :participant "Pose" as Pose
            :participant "CameraFPoses" as CameraFPoses
            :participant "RobotFPoses" as RobotFPoses
            :participant "Matrix4d" as TransformMatrix

            :User -> Vision: transformPoints(robotFPoses)

            :Vision -> CameraFPoses: Initialize()
            :alt For each detected face
                :loop mdetectedFaces
                    :Vision -> Utils: PixelsToPose(face, calib_factor)
                    :Utils -> Pose: Create pose
                    :Vision -> Vision: Calculate human_scaling_factor
                    :Vision -> Pose: Scale pose.y and pose.z
                    :Vision -> CameraFPoses: emplace_back(scaled_pose)
                :end loop
            :end

            :Vision -> TransformMatrix: Initialize camera_to_robot_tmatrix
            :TransformMatrix -> Vision: Set matrix values

            :alt For each camera pose
                :loop cameraFPoses
                    :Vision -> Pose: Create cam_pose_homogeneous
                    :Vision -> TransformMatrix: Multiply with camera_to_robot_tmatrix
                    :TransformMatrix -> Pose: Create robot_pose_homogeneous
                    :Vision -> RobotFPoses: emplace_back(robot_pose)
                :end loop
            :end
        *@enduml
        */
        void transformPoints(std::vector<acmebot::Pose> &robotFPoses);
    };
} //namespace

#endif
