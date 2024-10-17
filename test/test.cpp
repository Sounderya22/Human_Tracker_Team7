#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <string>
#include <spdlog/spdlog.h>
#include <memory>

#include "AcmeBot.hpp"

using testing::_;
using testing::Return;


class GMockTests : public testing::Test {
public:
  GMockTests (
    ) {
    spdlog::set_pattern("[%H:%M:%S %z] [%n] [%^---%L---%$] [thread %t] %v");
    bot = std::make_shared<acmebot::AcmeBot>();
    detector = std::make_shared<acmebot::Detector>();
    tracker = std::make_shared<acmebot::Tracker>();

  };

protected:
  void SetUp() override {
    spdlog::info("Calling Fixture SetUp");
  };

  void TearDown () override {
    spdlog::info("Calling Fixture TearDown");
  };

  std::shared_ptr<acmebot::AcmeBot> bot;
  std::shared_ptr<acmebot::Detector> detector;
  std::shared_ptr<acmebot::Tracker> tracker;

};


//==================================
// Unit Tests
//==================================

TEST_F (GMockTests, setIntrinsics) {
  spdlog::info("Calling SetIntrinsics function");
  double fl = 0.35;
  ASSERT_NO_THROW(bot->setIntrinsics());
}

TEST_F(GMockTests,GettransformPoints) {
  spdlog::info("Calling GettransformPoints function");
  std::array<float,3> points = {1,1,1};
  ASSERT_NO_THROW(bot->transformPoints());
}

TEST_F(GMockTests, TestTracking) {
  // cv::Mat img = cv::imread("./test.jpg");
  // auto output = tracker.Process();
  ASSERT_NO_THROW(tracker->Process());
  // ASSERT_EQ(static_cast<int>(output.size()), 1);
}


