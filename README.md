# Human Obstacle detector and tracker
![CICD Workflow status](https://github.com/Sounderya22/Human_Tracker_Team7/actions/workflows/run-unit-test-and-upload-codecov.yml/badge.svg) [![codecov](https://codecov.io/gh/Sounderya22/Human_Tracker_Team7/branch/main/graph/badge.svg)](https://codecov.io/gh/Sounderya22/Human_Tracker_Team7) [![License](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)


A C++ module for Human Obstacle Detection and Tracking using YOLOv8.

## Project Contributors
[Sounderya Varagur Venugopal](https://github.com/Sounderya22), Driver
<br>[Amogha Thalihalla Sunil](https://github.com/amoghatsunil), 
Navigator
<br>[Anirudh Swarnakar](https://github.com/Arthav24), Design Keeper

## Overview

Human detection and tracking is an essential component of applications where robots interact with humans. This is a challenging task as human beings are dynamic obstacles and it is crucial to avoid collision while the robot is operating. 

We propose a Human Obstacle Detection and Tracking Module using YOLOv8, tailored for a robotic system intended for navigation in human-populated environments at Acme Robotics which will enable the robot to track humans in real-time using a monocular camera. We plan to use YOLOv8 for human detection and OpenCV for video processing. The module will output location in the robot's reference frame.

## Deliverables

- A fully functional Humand Obstacle Detection and Tracking Module. 
- Overview of proposed work including timeline, risks and mitigation
- UML and activity diagrams
- Developer-level documentation

## Risks and Mitigation

- There are chances of potential performance issues with real time processing, if the model is not
well optimized. 

- False positives for unseen data while using the pretrained yolo model.

## UML Diagram
Class dependency diagram of the proposed design

![image](https://github.com/Sounderya22/Human_Tracker_Team7/blob/main//UML/Phase0/UML_diagram.jpeg)

## Activity Diagram

![image](https://github.com/Sounderya22/Human_Tracker_Team7/blob/main/UML/Phase0/activity_diagram.jpeg)

## Quad Chart

![image](https://github.com/Sounderya22/Human_Tracker_Team7/blob/main/docs/quad_chart.jpeg)

## Proposal Documentation

The proposal documentation for Phase 0 can be found [here](https://github.com/Sounderya22/Human_Tracker_Team7/blob/main/docs/Phase0_Proposal.pdf)

## Dependencies with licenses

OpenCV >= 4.5.0 is licensed under the Apache 2 License.
<br> Eigen is MPL2-licensed.
<br> Spdlog is MIT

## Build Instructions

```bash
# Install OpenCV
  # Install minimal prerequisites (Ubuntu 18.04 as reference)
  sudo apt update && sudo apt install -y cmake g++ wget unzip
  # Download and unpack sources
  cd 
  wget -O opencv.zip https://github.com/opencv/opencv/archive/4.x.zip
  unzip opencv.zip
  # Create build directory
  mkdir -p build && cd build 
  # Configure
  cmake  ../opencv-4.x
  # Build
  cmake --build .
# Download the source code:
  git clone https://github.com/Sounderya22/Human_Tracker_Team7
  cd Human_Tracker_Team7
# Configure the project and generate a native build system:
  # Must re-run this command whenever any CMakeLists.txt file has been changed.
  cmake -S ./ -B build/
# Compile and build the project:
  # rebuild only files that are modified since the last build
  cmake --build build/
  # or rebuild everything from scracth
  cmake --build build/ --clean-first
  # to see verbose output, do:
  cmake --build build/ --verbose
# Run program:
  ./build/app/Human_Tracker
# Run tests:
  cd build/; ctest; cd -
  # or if you have newer cmake
  ctest --test-dir build/
# Clean
  cmake --build build/ --target clean
# Clean and start over:
  rm -rf build/
```



