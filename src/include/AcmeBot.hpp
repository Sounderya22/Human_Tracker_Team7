#pragma once
// #include 

class AcmeBot {
    private:
        int intrinsics;     // Camera parameters
        int FrameRate;      
        // std::vector<std::vector<<cv::Rect>,10> Tracker;        // Tracker class 
        int capture;        // OpenCV video capture
    public:
        /**
         * @brief Constructs a new Acme Bot object
         * 
         */
        AcmeBot();
        /**
         * @brief Destructor for the Acme Bot class
         * 
         */
        ~AcmeBot();
        /**
        * @brief Calls tracker class to retreive trackpoints of detections and calculates 3D coordinates
        * 
        */
        void Process();
        /**
        * @brief Sets required intrinsics for transformations
        * 
        */
        void setIntrinsics();
        /**
        * @brief Converts points from camera's reference frame to robot frame
        * 
        */
        void transformPoints();
};
