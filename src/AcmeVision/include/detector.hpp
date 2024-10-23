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
 #include <iostream>
#include <opencv2/core/mat.hpp>
 #include <opencv2/opencv.hpp>
 #include <opencv2/core.hpp>
 #include <opencv2/highgui.hpp>
#include <spdlog/spdlog.h>
#include <readerwriterqueue.h>

 namespace acmebot {
 class Detector {
    public:
        explicit Detector(std::shared_ptr<moodycamel::ReaderWriterQueue<cv::Mat>> mqueue);
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
         */
        void Process(cv::Mat &frame,std::vector<cv::Rect> &detectedFaces);

    private: 
        /* Prediction confidence*/
        std::shared_ptr<moodycamel::ReaderWriterQueue<cv::Mat>> frames;
        std::string mModelPath;  //path to dnn model 
        std::string mConfigPath; //path to dnn config
        double mConfThres{0.3}; 
        std::future<bool> mVisionToDetector;
};
}  //namespace
#endif