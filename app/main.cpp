// #include <readerwriterqueue.h>
//
// int main()
// {
//   moodycamel::ReaderWriterQueue<int> q(100);
// }
/**
 * @file  main.cpp
 * @authors Anirudh Swarankar, Amogha Sunil
 * @brief C++ source file for main pipeline to run AcmeVision instance
 * @version 0.1
 * @date 2024-10-16
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "acme_vision.hpp"

int main(){
    std::unique_ptr<acmebot::AcmeVision> acmevision = std::make_unique<acmebot::AcmeVision>(0);
    acmevision->windowControl.showRawStream = false;


  acmevision->ProcessCameraFrame();

  return 0;
}

