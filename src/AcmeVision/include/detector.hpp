/**
 * @file detector.hpp
 * @author  Amogha Sunil
 * @brief C++ header file for AcmeBOt Class
 * @version 0.1
 * @date 2024-10-16
 *
 * @copyright Copyright (c) 2024
 *
 */

 #ifndef _H_DETECTER_H_
 #define _H_DETECTER_H_

#include <future>
#include <opencv2/core/mat.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <spdlog/spdlog.h>

 namespace acmebot {
 class Detector {
    public:
        /**
        * @brief Constructor for the Detector class
        * 
        */
         Detector();

        /**
        * @brief Destructor for the Detector class
        * 
        */
        ~Detector();

        /**
         * @brief load dnn model and network
         * 
         */
        void loadModel(std::string modelPath, std::string configPath);

        /**
         * @brief Captures frames from real-time camera feed or series of images
         * 
         */
        bool Inference();
        /**
         * @brief Performs detection and outputs bounding box
         * 
         *@startuml
            :start
            :actor User
            :participant "Detector" as Detector
            :participant "Net" as FaceDetectNet
            :participant "Frame" as Frame
            :participant "Detections" as Detections
            :participant "DetectionMat" as DetectionMat

            :User -> Detector: Process(frame, detectedFaces)
            :Detector -> Detector: loadModel(modelPath, configPath)
            :Detector -> FaceDetectNet: readNet(modelPath, configPath)
            :Detector -> Frame: blobFromImage(frame, size, scalar)
            :Detector -> FaceDetectNet: setInput(blob)
            :Detector -> FaceDetectNet: forward()
            :FaceDetectNet -> Detections: Get detections
            :Detector -> DetectionMat: Create(detections)
            :alt For each detection
                :loop rows in DetectionMat
                    :DetectionMat -> Detector: at(rows, 2) // confidence
                    :alt If conf > mConfThres
                        :DetectionMat -> Detector: at(rows, 3-6) // bounding box
                        :Detector -> Frame: rectangle(faces)
                        :Detector -> detectedFaces: push_back(faces)
                    :end
                :end loop
            :end
         * @enduml
         */
        void Process(cv::Mat &frame,std::vector<cv::Rect> &detectedFaces);

    private: 
        /// path to dnn model 
        std::string mModelPath;  

        /// path to dnn config
        std::string mConfigPath; 

        ///confidence threshold
        double mConfThres{0.3}; 
};
}  //namespace
#endif