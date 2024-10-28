#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <string>
#include <spdlog/spdlog.h>
#include <memory>

#include "acme_vision.hpp"

using testing::_;
using testing::Return;


class GMockTests : public testing::Test {
public:
  GMockTests (
    ) {
    spdlog::set_pattern("[%H:%M:%S %z] [%n] [%^---%L---%$] [thread %t] %v");
    mbot = std::make_shared<acmebot::AcmeVision>(-1);
    // detector = std::make_shared<acmebot::Detector>();
    // tracker = std::make_shared<acmebot::Tracker>();
  };

protected:
  void SetUp() override {
    spdlog::info("Calling Fixture SetUp");
  };

  void TearDown () override {
    spdlog::info("Calling Fixture TearDown");
  };

  std::shared_ptr<acmebot::AcmeVision> mbot;
  std::shared_ptr<acmebot::Detector> mdetector;
  std::shared_ptr<acmebot::Tracker> mtracker;


};


//==================================
// Unit Tests
//==================================

TEST_F (GMockTests, setIntrinsics) {
  spdlog::info("Calling SetIntrinsics function");
  double fl = 0.35;
  ASSERT_NO_THROW(mbot->setIntrinsics());
}

TEST_F(GMockTests,GettransformPoints) {
  spdlog::info("Calling GettransformPoints function");
  std::vector<cv::Rect> points = {cv::Rect(0, 0, 100, 100)};
  ASSERT_NO_THROW(mbot->transformPoints(points));
}

TEST_F(GMockTests, TestTracking) {
  // cv::Mat img = cv::imread("./test.jpg");
  // auto output = tracker.Process();
  ASSERT_NO_THROW(mtracker->Process());
  // ASSERT_EQ(static_cast<int>(output.size()), 1);
}

TEST_F(GMockTests, DrawBbox) {
  cv::Mat img = cv::Mat::zeros(cv::Size(100, 100), CV_8UC3);
  cv::Rect box(2, 2, 2, 2);
  std::string label;
  auto output  = acmebot::Utils::DrawBbox(img, box, label);
  ASSERT_EQ(static_cast<int>(output.cols), 100);
  ASSERT_EQ(static_cast<int>(output.rows), 100);
}
TEST_F(GMockTests, GetBboxCenter) {
  cv::Rect r = cv::Rect(0, 0, 10, 10);
  auto output = acmebot::Utils::GetBboxCenter(r);
  ASSERT_EQ(output.x, 5);
  ASSERT_EQ(output.y, 5);
}
TEST_F(GMockTests, GetBboxArea) {
  cv::Rect r = cv::Rect(0, 0, 10, 10);
  auto output = acmebot::Utils::GetBboxArea(r);
  ASSERT_EQ(output, 100.0);
}
TEST_F(GMockTests, ResizeImage) {
  cv::Mat img = cv::Mat::zeros(cv::Size(10, 10), CV_8UC3);
  cv::Size s = cv::Size(20, 20);
  auto output  = acmebot::Utils::ResizeImage(img, s);
  ASSERT_EQ(static_cast<int>(output.cols), 20);
  ASSERT_EQ(static_cast<int>(output.rows), 20);
}
TEST_F(GMockTests, CalculateIOU) {
  cv::Rect r1 = cv::Rect(0, 0, 10, 10);
  cv::Rect r2 = cv::Rect(5, 5, 10, 10);
  auto output = acmebot::Utils::CalculateIOU(r1, r2);
  ASSERT_NEAR(output, 0.166, 1);
}
TEST_F(GMockTests, PixelsToPose) {
  cv::Rect r = cv::Rect(0, 0, 10, 10);
  double calib_factor = 0.2;
  auto output = acmebot::Utils::PixelsToPose(r, calib_factor);
  ASSERT_NEAR(output.x, 0.02, 0.1);
  ASSERT_NEAR(output.y, 5.0, 0.1);
  ASSERT_NEAR(output.theta, 5.0, 0.1);
}
