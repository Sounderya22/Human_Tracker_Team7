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

    // bot = std::make_shared<acmebot::AcmeVision>(0);
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

  std::shared_ptr<acmebot::AcmeVision> bot;
  std::shared_ptr<acmebot::Detector> detector;
  std::shared_ptr<acmebot::Tracker> tracker;

};


//==================================
// Unit Tests
//==================================


