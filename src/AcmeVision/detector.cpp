#include "detector.hpp"

#include <acme_vision.hpp>
#include <utility>


/**
 * @brief Constructor for Detector class
 * 
 */
acmebot::Detector::Detector(
    std::shared_ptr<moodycamel::ReaderWriterQueue<cv::Mat> > mqueue): frames(std::move(mqueue)) {
    spdlog::set_pattern("[%H:%M:%S %z] [%n] [%^---%L---%$] [thread %t] %v");
    mVisionToDetector = std::async(std::launch::async, &acmebot::Detector::Inference, this);
}

/**
 * @brief Destructor for Detector class
 * 
 */
acmebot::Detector::~Detector() {
}

/**
 * @brief Captures frames from real-time camera feed or series of images
 * 
 */
bool acmebot::Detector::Inference() {
    // pop one from mFrameQueue and inference
    // push result to mDetectedObjectqueue

    cv::Mat frame;
    cv::namedWindow("test", cv::WINDOW_NORMAL);
    while (true) {
        spdlog::info(frames->size_approx());
        if (!frames->try_dequeue(frame)) {
            spdlog::info("Empty frame");
            continue;
        };

        cv::imshow("test", frame);
        char k = cv::waitKey(1);
        if (k == 27 || k == 'q') {
            return false;
        }
    }
}

/**
 * @brief Performs detection and outputs bounding box
 *
 */
void acmebot::Detector::Process() {
}
