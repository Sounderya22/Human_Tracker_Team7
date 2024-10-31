/**
 * @file detector.cpp
 * @author Anirudh
 ^         Amogha Sunil
 *         Sounderya
 * @brief C++ source file for AcmeBot pipeline
 * @version 0.1
 * @date 2024-10-16
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "detector.hpp"
#include <acme_vision.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/dnn/dnn.hpp>
#include <opencv2/imgproc.hpp>
#include <utility>


acmebot::Detector::Detector(){
    spdlog::set_pattern("[%H:%M:%S %z] [%n] [%^---%L---%$] [thread %t] %v");
}

acmebot::Detector::~Detector() {
}

void acmebot::Detector::loadModel(std::string modelPath, std::string configPath) {
    mModelPath = modelPath;
    mConfigPath = configPath;
}

bool acmebot::Detector::Inference() {
}


void acmebot::Detector::Process(cv::Mat &frame, std::vector<cv::Rect> &detectedFaces) {

    loadModel("../models/res10_300x300_ssd_iter_140000_fp16.caffemodel", "../models/deploy.protext");

    cv::dnn::Net faceDetectNet; ///< face detection model from dnn opencv lib
    faceDetectNet = cv::dnn::readNet(mModelPath, mConfigPath);

    //create from for the current frame.
    cv::Mat blob = cv::dnn::blobFromImage(frame, 1.0, cv::Size(850, 850),
                                          cv::Scalar(98, 125, 133));
    faceDetectNet.setInput(blob);

    //forward pass of the network
    cv::Mat detections = faceDetectNet.forward();

    cv::Mat detectionMat(detections.size[2], detections.size[3], CV_32F,
                         detections.ptr<float>());

    for (int rows = 0; rows < detectionMat.rows; rows++) {
        float conf = detectionMat.at<float>(rows, 2);
        if (conf > mConfThres) {
            int x1 = static_cast<int>(detectionMat.at<float>(rows, 3) * frame.cols);
            int y1 = static_cast<int>(detectionMat.at<float>(rows, 4) * frame.rows);
            int x2 = static_cast<int>(detectionMat.at<float>(rows, 5) * frame.cols);
            int y2 = static_cast<int>(detectionMat.at<float>(rows, 6) * frame.rows);

            cv::Rect faces(x1, y1, x2 - x1, y2 - y1);
            cv::rectangle(frame, faces, cv::Scalar(0, 255, 0), 1, 4);
            // output detected face coordinates
            detectedFaces.push_back(faces);
        }
    }
}
