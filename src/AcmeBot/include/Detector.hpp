/**
 * @file AcmeBot.hpp
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
        double mConfidenceThreshold{0.0}; // Prediction confidence
        
};
}  //namespace
#endif