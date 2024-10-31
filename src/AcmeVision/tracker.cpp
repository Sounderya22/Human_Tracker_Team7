#include"tracker.hpp"

acmebot::Tracker::Tracker() {

}

acmebot::Tracker::~Tracker() {

}

void acmebot::Tracker::Process(cv::Mat &frame, std::vector<cv::Rect> &detectedFaces) {
   mDetector.Process(frame,detectedFaces);
}

void acmebot::Tracker::setParameters() {

}