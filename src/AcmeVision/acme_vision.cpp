/**
 * @file acme_vision.cpp
 * @author Amogha Sunil
 * @brief C++ source file for AcmeBot pipeline
 * @version 0.1
 * @date 2024-10-16
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "acme_vision.hpp"
#include <opencv2/core/mat.hpp>

#include<iostream>
using namespace std;
/**
 * @brief Constructs a new Acme Vision object
 * 
 */
acmebot::AcmeVision::AcmeVision(const int8_t camId): mcameraId_(camId), windowControl(false,false) {
    // mFrameQueue = std::make_shared<moodycamel::ReaderWriterQueue<cv::Mat>>(100);
    spdlog::set_pattern("[%H:%M:%S %z] [%n] [%^---%L---%$] [thread %t] %v");
    // initCamera();
     mDetector = std::make_unique<acmebot::Detector>();
    //  mTracker = std::make_unique<acmebot::Tracker>();
}


/**
 * @brief Destructor for the Acme Bot class
 * 
 */
acmebot::AcmeVision::~AcmeVision() {
}

bool acmebot::AcmeVision::initCamera() {

    // auto path = mcameraId_;
    // /// Path for testing on a video; comment this line if using webcam
    // // auto path = "..//data//test.mov";
    // cap_.open(path);
    // cap_.set(cv::CAP_PROP_FRAME_HEIGHT, 850);
    // cap_.set(cv::CAP_PROP_FRAME_WIDTH, 850);
    // /// check if camera is open
    // if ( cap_.isOpened() ) {
    //     /// set srouce frame width
    //     frame_width_ = cap_.get(cv::CAP_PROP_FRAME_WIDTH);

    //     /// set srouce frame height
    //     frame_height_ = cap_.get(cv::CAP_PROP_FRAME_HEIGHT);

    //     // set srouce frame rate
    //     frame_rate_ = cap_.get(cv::CAP_PROP_FPS);

    //     /// if height or width is 0, throw error
    //     if (frame_height_ == 0 || frame_width_ == 0) {
    //         // Display error msg and EXIT
    //         spdlog::error("Frame is empty");
    //         return false;
    //     }
    // } else {
    //     // Display error msg and EXIT
    //     spdlog::error("Cannot open camera");
    //     return false;
    // }
    // return true;
  return false;
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
void acmebot::AcmeVision::ProcessCameraFrame(cv::Mat &p_frame_) {
    /// if calib_factor == default value, calculate calib_factor
    // int calib_factor_ = 1;
    // if (calib_factor_ == -1) {
    //     Calibrate();
    // }
    // const std::string kWindowName = "Raw frame";

    // if (windowControl.showRawStream) {
    //     /// create a display window if show window is true
    //     cv::namedWindow(kWindowName);
    // }

   cv::VideoCapture cap(0);
//    p_size_ = cv::Size(850, 850);
   
    // Check if camera opened successfully
   if(!cap.isOpened()){
        spdlog::error("Cannot read frame");
        return;
    }
   
    cap.read(p_frame_);
    // p_frame_ = acmebot::Utils::ResizeImage(p_frame_,);
   
     // When everything done, release the video capture object  
    // while (true) {
    //     cv::Mat src_frame;
    //     if (cap_.read(src_frame)) {
    //         // mFrameQueue->try_enqueue(p_frame_);
    //         // if (windowControl.showRawStream) {
    //         //     cv::imshow(kWindowName, p_frame_);
    //         //     char k = cv::waitKey(1);
    //         //     if (k == 27 || k == 'q') {
    //         //         return;
    //         //     // }
    //         // }
    //     } 
    //     else {
            
    //     }
    
}

void acmebot::AcmeVision::Process(){
    cv::Mat currFrame;
    std::vector<cv::Rect> detectedFaces;
    ProcessCameraFrame(currFrame);
    mDetector->Process(currFrame,detectedFaces);
    
    // cout<< "currFrame.size() : "<< currFrame.size();
    
    cv::imshow("acmeVision Process", currFrame);
    char k = cv::waitKey(1);
    if (k == 27 || k == 'q') 
        return;
}

/**
 * @brief Sets required intrinsics for transformations
 * 
 */
void acmebot::AcmeVision::setIntrinsics() {
}

/**
 * @brief Converts points from camera's reference frame to robot frame
 * 
 */
void acmebot::AcmeVision::transformPoints() {
}
