/**
 * @file acme_vision.cpp
 * @author Amogha Sunil
 *         Sounderya
 * @brief C++ source file for AcmeBot pipeline
 * @version 0.1
 * @date 2024-10-16
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "acme_vision.hpp"
#include "Utils.hpp"
#include <opencv2/core/mat.hpp>
#include <Eigen/Dense>


acmebot::AcmeVision::AcmeVision(){
    spdlog::set_pattern("[%H:%M:%S %z] [%n] [%^---%L---%$] [thread %t] %v");
    mTracker = std::make_unique<acmebot::Tracker>();
}

acmebot::AcmeVision::~AcmeVision() {
}

void acmebot::AcmeVision::ProcessCameraFrame() {
    cv::VideoCapture cap(0);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);
    cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);

   /// Check if camera opened successfully
   if(!cap.isOpened()){
        spdlog::error("Cannot read frame");
        return;
    }
    cap.read(p_frame_);
}

void acmebot::AcmeVision::Process(){

    ///grabs the current frame data from livestream
    ProcessCameraFrame();
    
    ///tracker process method to get detected faces list
    mTracker->Process(p_frame_,mdetectedFaces);
    
    transformPoints(robotFPoses);
    cv::imshow("acmeVision Process", p_frame_);
    char k = cv::waitKey(1);
    if (k == 27 || k == 'q') 
        return;
}

void acmebot::AcmeVision::transformPoints(std::vector<acmebot::Pose> &robotFPoses) {

    std::vector<acmebot::Pose> cameraFPoses;

    for(const auto &i : mdetectedFaces) {
        auto pose = mUtils->PixelsToPose(i, calib_factor);
        auto scaled_pose = pose;

        /// 1.6m is considered as the average human height
        double human_scaling_factor = 1.6 / i.height;   
        scaled_pose.y *= human_scaling_factor;  
        scaled_pose.z *= human_scaling_factor;  
        cameraFPoses.emplace_back(scaled_pose);
    }

    Eigen::Matrix4d camera_to_robot_tmatrix;
    camera_to_robot_tmatrix << 
        1, 0, 0, 0.5,  
        0, 1, 0, 0.2,  
        0, 0, 1, 1.0,
        0, 0, 0, 1;

    for(const auto &pose : cameraFPoses) {
        Eigen::Vector4d cam_pose_homogeneous(pose.x, pose.y, pose.z, 1.0);
        Eigen::Vector4d robot_pose_homogeneous = camera_to_robot_tmatrix * cam_pose_homogeneous;
        robotFPoses.emplace_back(robot_pose_homogeneous[0], robot_pose_homogeneous[1], robot_pose_homogeneous[2]);
    }
}
