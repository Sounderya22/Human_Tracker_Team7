/**
 * @file acmebot.hpp
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

 #include <iostream>
 #include <opencv2/opencv.hpp>
 #include <opencv2/core.hpp>
 #include <opencv2/highgui.hpp>

 namespace acmebot {
 class Detector {
    public:
        Detector();
        ~Detector();
        /**
         * @brief Captures frames from real-time camera feed or series of images
         * 
         */
        void cameraCapture();   
        /**
         * @brief Performs detection and outputs bounding box
         * 
         */
        void Process();

    private: 
        /* Prediction confidence*/
        double mConfidenceThreshold{0.0}; 
        
};
}  //namespace
#endif