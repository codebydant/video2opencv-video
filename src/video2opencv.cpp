/*********************************
           HEADERS
**********************************/
//----------------------------------------------
#include <iostream>
#include <iterator>
#include <opencv2/opencv.hpp>
#include <string>
#include <vector>
//----------------------------------------------

int fast_mod(const int input, const int ceil) {
  // apply the modulo operator only when needed
  // (i.e. when the input is greater than the ceiling)
  return input >= ceil ? input % ceil : input;
  // NB: the assumption here is that the numbers are positive
}

int main(int argc, const char *argv[]) {

  if (argc < 2 or argc > 2) {
    std::cout << "Usage: <executable> <video file>" << std::endl;
    std::exit(-1);
  } else {

    ///////////////////////////////////////////////////////////////////////////////
    /////////////  WELCOME MESSAGE ////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////
    std::cout << "\n*********************" << std::endl;
    std::cout << "*** VIDEO TO OPENCV VIDEO *** " << std::endl;
    std::cout << "*********************" << std::endl;

    std::cout << "-> Creating opencv video...please wait" << std::endl;

    ///////////////////////////////////////////////////////////////////////////////
    /////////////  VIDEO READING //////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////

    cv::VideoCapture capture(argv[1]);

    if (!capture.isOpened()) {
      std::cout << "-> Error opening video stream or file" << std::endl;
      std::exit(-1);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /////////////  VIDEO FEATURES /////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////

    const int total_number_frames = capture.get(cv::CAP_PROP_FRAME_COUNT);
    const float frames_per_second = capture.get(cv::CAP_PROP_FPS);
    const int multiplier = frames_per_second * 2; // Change (2)

    ///////////////////////////////////////////////////////////////////////////////
    /////////////  LOOP FRAME by FRAME  ///////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////

    std::cout << "-------------------------------------" << std::endl;
    std::vector<cv::Mat> images_list_rgb;

    // int cont = 1;
    for (int frame_i = 0; frame_i < total_number_frames; frame_i++) {
      // for (int frame_i : total_number_frames) {

      capture.set(cv::CAP_PROP_POS_FRAMES, frame_i);
      cv::Mat currentFrame;

      if (fast_mod(frame_i, multiplier) == 0 or frame_i == 0) {
        // if ((frame_i % multiplier) == 0) {
        capture >> currentFrame;

        if (currentFrame.empty()) {
          std::cout << "-> frame empty: " << std::endl;
          break;
        }

        cv::Mat image_rotated;
        cv::rotate(currentFrame, image_rotated, cv::ROTATE_90_CLOCKWISE);
        images_list_rgb.push_back(image_rotated);

        // std::string filename = "Image_" + std::to_string(cont) + ".png";
        // cv::imwrite(filename.c_str(), image_rotated.clone());
        // cv::namedWindow("inputVideo", cv::WINDOW_NORMAL);
        // cv::resizeWindow("inputVideo", 640, 480);
        // cv::imshow("inputVideo", currentFrame);
        // std::cout << "-> Video_frame: " << cont << std::endl;
        // cont += 1;

        // cv::waitKey(400);
        // cv::destroyAllWindows();

      } else {
        continue;
      }
    }

    capture.release();
    std::cout << "-> Number of frames for new video: " << images_list_rgb.size() << std::endl;
    cv::Size s = images_list_rgb[0].size();

    ///////////////////////////////////////////////////////////////////////////////
    /////////////  OPENCV VIDEO FORMAT  ///////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////

    std::string filename = "outcpp.avi";
    cv::VideoWriter video(filename, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), 1, cv::Size(s.width, s.height));

    // for (int frame_i = 0; frame_i < images_list_rgb.size(); frame_i++) {
    for (std::vector<cv::Mat>::iterator it = images_list_rgb.begin(); it != images_list_rgb.end(); ++it) {
      // cv::Mat frame = images_list_rgb[frame_i];
      cv::Mat frame = *it;

      if (frame.empty()) {
        std::cout << "-> Frame empty" << std::endl;
        break;
      }

      video.write(frame);
    }
    video.release();

    std::cout << "-> Video saved: " << filename << std::endl;
    std::cout << "-------------------------------------" << std::endl;
    cv::destroyAllWindows();
  }

  return 0;
}
