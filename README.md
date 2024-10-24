# Human Obstacle detector and tracker
![CICD Workflow status](https://github.com/Sounderya22/Human_Tracker_Team7/actions/workflows/run-unit-test-and-upload-codecov.yml/badge.svg) [![codecov](https://codecov.io/gh/Sounderya22/Human_Tracker_Team7/branch/main/graph/badge.svg)](https://codecov.io/gh/Sounderya22/Human_Tracker_Team7) [![License](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)


A C++17 module for Human Obstacle Detection and Tracking using YOLOv8. The module outputs in the robot's base frame. 

## Project Contributors
[Sounderya Varagur Venugopal](https://github.com/Sounderya22), Driver
<br>[Amogha Thalihalla Sunil](https://github.com/amoghatsunil), 
Navigator
<br>[Anirudh Swarnakar](https://github.com/Arthav24), Design Keeper

## Overview

Human detection and tracking is an essential component of applications where robots interact with humans. This is a challenging task as human beings are dynamic obstacles and it is crucial to avoid collision while the robot is operating. 

We propose a Human Obstacle Detection and Tracking Module using YOLOv8, tailored for a robotic system intended for navigation in human-populated environments at Acme Robotics which will enable the robot to track humans in real-time using a monocular camera. We plan to use YOLOv8 for human detection and OpenCV for video processing. The module will output location in the robot's reference frame.

## Deliverables

- A fully functional Human Obstacle Detection and Tracking Module. 
- Overview of proposed work including timeline, risks and mitigation
- UML and activity diagrams
- Developer-level documentation

## Risks and Mitigation

- There are chances of potential performance issues with real time processing, if the model is not
well optimized. 
  - In phase 1 we decided to use shared queue IPC mechanism. Each unit i.e. Framegrabber, Detector, Tracker will have a shared queue in between. 
  - Shared queue used is a SPSC(Single Producer Single Consumer) lock free.

- False positives for unseen data while using the pretrained yolo model.
  - In phase 2 we plan to use transfer learning and train on larger dataset hence reducing false detections. 

## UML Diagram - Phase 1
Class dependency diagram of the proposed design

![image](https://github.com/Sounderya22/Human_Tracker_Team7/blob/main//UML/Phase1/UML_diagram.jpeg)

## Activity Diagram

![image](https://github.com/Sounderya22/Human_Tracker_Team7/blob/main/UML/Phase0/activity_diagram.jpeg)

## Quad Chart

![image](https://github.com/Sounderya22/Human_Tracker_Team7/blob/main/docs/quad_chart.jpeg)

## Proposal video
[<img src="https://github.com/Sounderya22/Human_Tracker_Team7/blob/main/docs/quad_chart.jpeg" width="50%">](https://drive.google.com/file/d/1x_w5co_9UD8CQUA8fLLDc7qcsHzgK9t5/view?usp=sharing)

## Backlog
Product backlog sheet can be found [here](https://umd0-my.sharepoint.com/:x:/g/personal/aniswa_umd_edu/EestCJ8OoQ5Kma2gOCJLRu0B8-GHkAcc6Mof4minRu5YdA?e=6aKXpD)

## Proposal Documentation
The proposal documentation for Phase 0 can be found [here](https://github.com/Sounderya22/Human_Tracker_Team7/blob/main/docs/Phase0_Proposal.pdf)

## Dependencies with licenses

[OpenCV](https://github.com/opencv/opencv) >= 4.5.0 is licensed under the Apache 2 License.
<br> [Eigen](https://github.com/OPM/eigen3/tree/master) is MPL2-licensed.
<br> [Spdlog](https://github.com/gabime/spdlog) is MIT
<br> [readerwriterqueue](https://github.com/cameron314/readerwriterqueue) is BSD

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
  cmake --build build/ --clean-first --verbose
# Clean
  cmake --build build/ --target clean
```

### Generating Documentation

To generate and view the Doxygen documentation of the project, run the following commands.
```sh
# Build the documentation into the 'docs' directory using CMake:
  cmake --build build/ --target docs
# Open the documentation as a HTML file in your web browser:
  open docs/html/index.html
```
### Running the Program Executables (Project Demo Run)

To run the demo code of the project , the following command is to be executed.
``` bash
# Run a demo of track on your computer system:
  ./build/app/track
```
### Running Unit Tests

To manually run and verify the working of the unit tests for track, execute the commands below.
``` bash
# Manually run the unit tests:
  ctest --test-dir build/
```
### Google Coding Style Verification
To check how the written code conforms to the Google C++ style guide, look at the `results/clangd-format_output.txt` and `results/clangd-format_output.png` files to see the output on using the *clang-format* tool on this project.

```sh
# Install clang-format(ignore if already installed):
  sudo apt install clangd-format
# Self-check Google code style conformity using clang-format:
  clang-format -style=Google -i $( find . -name *.cpp | grep -vE -e "^./build/" )
```

### Static Code Analysis
To check the static code analysis of this project, check the `results/clang-tidy_output.txt` and `results/clang-tidy_output.png` files to see the output on using the *clang-tidy* tool. You should not be able to see any issues or problems, with all the files checked successfully.
```sh
# Install Cppcheck (ignore if already installed):
  sudo apt install clang-tidy
# Self-check the static code analysis using Cppcheck:
  clang-tidy -p ./ $( find . -name *.cpp | grep -v "/build/" )
```
## Phase 1

Phase 1 of the project involved building the directory structure, writing the class headers and stubs, and writing more unit tests. major time was invested in understanding program requirements and flow and hence using a design pattern. Using right design pattern enables code Reusability and Maintainability and efficient communication. Design patterns provide proven solutions to common problems, making it easier to reuse code across different projects. This leads to cleaner, more maintainable code that is easier to understand and modify. As a result Shared queue IPC mechanism is being used.

[<img src="https://github.com/Sounderya22/Human_Tracker_Team7/blob/main/docs/quad_chart.jpeg" width="50%">](https://drive.google.com/drive/folders/1mcVHQ7RUj1PIpepL2NkcWiuVDMI84d2H?usp=sharing)

### References
- [SSD Achitecture](https://towardsdatascience.com/understanding-ssd-multibox-real-time-object-detection-in-deep-learning-495ef744fab)
- [Caffe](https://caffe.berkeleyvision.org/)
- [OpenCV DNN](https://docs.opencv.org/4.x/d2/d58/tutorial_table_of_content_dnn.html)
