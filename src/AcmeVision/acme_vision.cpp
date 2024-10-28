/**
 * @file acme_vision.cpp
 * @author Amogha Sunil
 * @brief C++ source file for AcmeBot pipeline
 * @version 0.1
 * @date 2024-10-16
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "acme_vision.hpp"

acmebot::AcmeVision::AcmeVision(const int8_t camId): mcalib_(1), mcameraId_(camId),
                                                     windowControl(false, false) {
    SetProcessingSize(640, 480);
    SetCameraPose(Pose(0, 0, 1));
    SetRobotPose(Pose(1, 1, 1));
    mFrameQueue = std::make_shared<moodycamel::ReaderWriterQueue<cv::Mat> >(100);
    mOutputQueue = std::make_shared<moodycamel::ReaderWriterQueue<acmebot::Pose> >(100);
    spdlog::set_pattern("[%H:%M:%S %z] [%n] [%^---%L---%$] [thread %t] %v");
    if (camId != -1) {
        initCamera();

        mDetector = std::make_unique<acmebot::Detector>(mFrameQueue);
        mTracker = std::make_unique<acmebot::Tracker>();
    } else {
        initTestData();
    }
}

acmebot::AcmeVision::AcmeVision(const std::string filePath): windowControl(false, false) {
    AcmeVision(-1);
}

acmebot::AcmeVision::~AcmeVision() = default;

bool acmebot::AcmeVision::SetProcessingSize(const int w, const int h) {
    if (!cap_.isOpened()) {
        raw_height = h;
        raw_width = w;
        return true;
    }
    return false;
}


bool acmebot::AcmeVision::initTestData() {
    cap_.release();
    cv::Mat img1 = cv::imread("../data/test/1.png");
    cv::Mat img2 = cv::imread("../data/test/2.png");
    cv::Mat img3 = cv::imread("../data/test/3.png");
    cv::Mat img4 = cv::imread("../data/test/4.png");
    cv::Mat img5 = cv::imread("../data/test/5.jpeg");

    std::array<cv::Rect, 1> ground_truth_2 = {cv::Rect(330, 107, 160, 294)};
    std::array<cv::Rect, 1> ground_truth_3 = {cv::Rect(298, 126, 98, 228)};
    std::array<cv::Rect, 1> ground_truth_1 = {cv::Rect(300, 21, 197, 310)};
    std::array<cv::Rect, 1> ground_truth_4 = {cv::Rect(297, 84, 147, 265)};
    std::array<cv::Rect, 1> ground_truth_5 = {cv::Rect(320, 55, 110, 400)};
    std::array<std::array<cv::Rect, 1>, 5> gts = {
        ground_truth_1, ground_truth_2,
        ground_truth_3, ground_truth_4, ground_truth_5
    };

    std::array<cv::Mat, 5> testimg_ = {img1, img2, img3, img4, img5};
    int x = 0, y = 0;
    for (const auto &img: testimg_) {
        p_size_ = cv::Size(raw_height, raw_height);
        p_frame_ = acmebot::Utils::ResizeImage(img, p_size_);
        mFrameQueue->enqueue(p_frame_);
    }
    return true;
}

bool acmebot::AcmeVision::initCamera() {
    try {
        auto path = mcameraId_;
        p_size_ = cv::Size(raw_height, raw_height);
        cap_.open(path);
        cap_.set(cv::CAP_PROP_FRAME_HEIGHT, raw_height);
        cap_.set(cv::CAP_PROP_FRAME_WIDTH, raw_width);
        if (cap_.isOpened()) {
            frame_width_ = cap_.get(cv::CAP_PROP_FRAME_WIDTH);
            frame_height_ = cap_.get(cv::CAP_PROP_FRAME_HEIGHT);
            frame_rate_ = cap_.get(cv::CAP_PROP_FPS);
            if (frame_height_ == 0 || frame_width_ == 0) {
                spdlog::error("Frame is empty");
                return false;
            }
        } else {
            spdlog::error("Cannot open camera");
            return false;
        }
    } catch (cv::Exception e) {
        spdlog::error("Exception caught: {}", e.what());
        return false;
    }
    return true;
}


void acmebot::AcmeVision::ProcessCameraFrame() {
    if (mcalib_ == -1) {
        setIntrinsics();
    }
    const std::string kWindowName = "Raw frame";

    if (windowControl.showRawStream) {
        cv::namedWindow(kWindowName);
    }

    while (true) {
        cv::Mat src_frame;
        if (cap_.read(src_frame)) {
            p_frame_ = acmebot::Utils::ResizeImage(src_frame, p_size_);
            mFrameQueue->enqueue(p_frame_);
            if (windowControl.showRawStream) {
                cv::imshow(kWindowName, p_frame_);
                char k = cv::waitKey(1);
                if (k == 27 || k == 'q') {
                    return;
                }
            }
        } else {
            spdlog::error("Cannot read frame");
            return;
        }
    }
}

void acmebot::AcmeVision::setIntrinsics() {
    /// calculate calib factor and focal length here
    cv::Mat image = cv::imread("../data/calibrate.jpg", 0);
    cv::Mat thr;
    /// original distance between object and camera
    double original_distance = 20;
    /// original width of the object
    double original_width = 10;
    /// thresholding the image
    cv::threshold(image, thr, 150, 255, cv::THRESH_BINARY);
    /// variable tostore contours
    std::vector<std::vector<cv::Point> > contours;
    std::vector<cv::Vec4i> hierarchy;
    /// search for the contour
    cv::findContours(thr, contours, hierarchy,
                     cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE);
    double maxArea = 0;
    int maxAreaContourId = -1;
    /// get ID for contour of maximum area
    for (int j = 0; j < static_cast<int>(contours.size()); j++) {
        double newArea = cv::contourArea(contours.at(j));
        if (newArea > maxArea) {
            maxArea = newArea;
            maxAreaContourId = j;
        }
    }
    /// make bounding box
    cv::Rect box = cv::boundingRect(contours[maxAreaContourId]);
    /// calculate focal length
    double focalLength = (box.width * original_distance) / original_width;
    /// set focal length
    SetFocalLength(focalLength);
    mcalib_ = focalLength * mavgHumanHeight_;
}

void acmebot::AcmeVision::SetFocalLength(double focal_length) {
    mFocalLength = focal_length;
}

bool acmebot::AcmeVision::SetRobotPose(const Pose &robo_pose) {
    mrobotPose = robo_pose;
    return true;
}

bool acmebot::AcmeVision::SetCameraPose(const Pose &cam_pose) {
    mcamPose = cam_pose;
    return true;
}


void acmebot::AcmeVision::transformPoints(const std::vector<cv::Rect> &tracks) {
    Eigen::Matrix4d transform_mat;
    Eigen::Vector4d obj_in_cam;
    Eigen::Vector4d obj_in_robot;
    /// transformation matrix considering
    transform_mat << 1, 0, 0, mrobotPose.x - mcamPose.x,
            0, 1, 0, mrobotPose.y - mcamPose.y,
            0, 0, 1, mrobotPose.theta - mcamPose.theta,
            0, 0, 0, 1;

    if (tracks.size()) {
        /// create a variable to store Pose of the detected object
        acmebot::Pose obj_pose;
        int bbox_id = 0;
        for (cv::Rect box: tracks) {
            bbox_id++;
            double factor = mavgHumanHeight_ / box.height;
            /// convert from img plane to Pose(x, y, z) using calib_factor
            obj_pose = acmebot::Utils::PixelsToPose(box, mcalib_);
            obj_pose.y = obj_pose.y * factor;
            obj_pose.theta = obj_pose.theta * factor;

            // from world coordinates to camera coordinates using homogeneous
            // CHECK UTILS GET TRANSFORMED POSE METHOD
            obj_in_cam << obj_pose.x, obj_pose.y, obj_pose.theta, 1;
            /// convert from camera Pose to Robot Pose
            obj_in_robot = transform_mat * obj_in_cam;

            /// store detected obj Pose in a vector
            mOutputQueue->try_enqueue(acmebot::Pose(obj_in_robot[0],
                                                    obj_in_robot[1], obj_in_robot[2]));

            std::string label = std::to_string(bbox_id) + " (" +
                                std::to_string(static_cast<int>(obj_in_robot[0]))
                                + "," +
                                std::to_string(static_cast<int>(obj_in_robot[1]))
                                + "," +
                                std::to_string(static_cast<int>(obj_in_robot[2]))
                                + ")";

            p_frame_ = acmebot::Utils::DrawBbox(p_frame_, box, label);
        }
    }
}
