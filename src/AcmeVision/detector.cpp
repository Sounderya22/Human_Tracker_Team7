#include "detector.hpp"

#include <acme_vision.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/dnn/dnn.hpp>
#include <opencv2/imgproc.hpp>
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
void acmebot::Detector::loadModel(std::string modelPath, std::string configPath) {
    mModelPath = modelPath;
    mConfigPath = configPath;
}

/**
 * @brief Captures frames from real-time camera feed or series of images
 * 
 */
bool acmebot::Detector::Inference() {
    // pop one from mFrameQueue and inference
    // push result to mDetectedObjectqueue
    std::vector<cv::Rect> detectedFaces;
    cv::Mat frame;

    loadModel("../../models/res10_300x300_ssd_iter_140000_fp16.caffemodel", "../../models/deploy.protext");

    cv::namedWindow("test", cv::WINDOW_NORMAL);
    while (true) {
        spdlog::info(frames->size_approx());
        if (!frames->try_dequeue(frame)) {
            spdlog::info("Empty frame");
            continue;
        };
        Process(frame, detectedFaces);
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
void acmebot::Detector::Process(cv::Mat &frame, std::vector<cv::Rect> &detectedFaces) {
    cv::dnn::Net faceDetectNet; ///< face detection model from dnn opencv lib
    faceDetectNet = cv::dnn::readNet(mModelPath, mConfigPath);

    //create from for the current frame.
    cv::Mat blob = cv::dnn::blobFromImage(frame, 1.0, cv::Size(640, 480),
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
