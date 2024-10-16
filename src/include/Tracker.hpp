#pragma once

class Tracker {
    private:
        int detector;

    public:
        Tracker();
        ~Tracker();
        /**
         * @brief Takes frame-wise detections to track humans
         * 
         */
        void Process();
        /**
         * @brief Sets parameters that are private to class
         * 
         */
        void setParameters();
       
};