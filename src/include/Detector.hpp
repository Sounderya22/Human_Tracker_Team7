#pragma once

class Detector {
    private: 
        double confidenceThreshold; // Prediction confidence
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
};

