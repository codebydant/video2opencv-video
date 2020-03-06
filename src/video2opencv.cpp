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

// int fast_mod(const int input, const int ceil) {
//   // apply the modulo operator only when needed
//   // (i.e. when the input is greater than the ceiling)
//   return input >= ceil ? input % ceil : input;
//   // NB: the assumption here is that the numbers are positive
// }

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
    std::cout << "-----------------------------------------------------" << std::endl;

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
    const int frames_rate = cvRound(capture.get(cv::CAP_PROP_FPS));
    // capture.set(cv::CAP_PROP_POS_AVI_RATIO, 1);
    // const int next_frame_id = capture.get(cv::CAP_PROP_POS_FRAMES);
    // const float current_video_position = capture.get(cv::CAP_PROP_POS_MSEC);
    const int frames_width = capture.get(cv::CAP_PROP_FRAME_WIDTH);
    const int frames_height = capture.get(cv::CAP_PROP_FRAME_HEIGHT);
    const float relative_video_position = capture.get(cv::CAP_PROP_POS_AVI_RATIO);
    const int video_duration_msec = cvRound(total_number_frames / (float)frames_rate);
    // const int total_output_frames = cvRound(total_number_frames / (float)multiplier);
    const int total_output_frames = 5; // Number of output desired frames
    const int multiplier_factor = cvRound((float)(total_number_frames / total_output_frames));
    // const int multiplier = frames_rate * 2; // Increase number for more output frames
    const int multiplier = multiplier_factor; // Increase number for more output frames
    // const float brightness_camera = capture.get(cv::CAP_PROP_BRIGHTNESS);
    // const float contrast_camera = capture.get(cv::CAP_PROP_CONTRAST);
    // const float saturation_camera = capture.get(cv::CAP_PROP_SATURATION);
    // const float exposure_camera = capture.get(cv::CAP_PROP_EXPOSURE);

    std::cout << "--> Input video:                  " << argv[1] << std::endl;
    std::cout << "-> Total number of frames:        " << total_number_frames << std::endl;
    std::cout << "-> Frame rate:                    " << frames_rate << std::endl;
    std::cout << "-> Duration (sec):                " << video_duration_msec << std::endl;
    // std::cout << "-> Current video pos(msec):       " << current_video_position << std::endl;
    std::cout << "-> Relative video pos:            " << relative_video_position << std::endl;
    // std::cout << "-> Next frame index:              " << next_frame_id << std::endl;
    std::cout << "-> Frames width:                  " << frames_width << std::endl;
    std::cout << "-> Frames height:                 " << frames_height << std::endl;
    std::cout << "-> Multiplier for output frames:  " << multiplier << std::endl;
    std::cout << "-> Total output frames:           " << total_output_frames << std::endl;
    // std::cout << "-> Brightness:                    " << brightness_camera << std::endl;
    // std::cout << "-> Contrast:                      " << contrast_camera << std::endl;
    // std::cout << "-> Saturation:                    " << saturation_camera << std::endl;
    // std::cout << "-> Exposure:                      " << exposure_camera << std::endl;

    // 11 seq

    ///////////////////////////////////////////////////////////////////////////////
    /////////////  LOOP FRAME by FRAME  ///////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////

    std::cout << "-----------------------------------------------------" << std::endl;
    std::cout << "-> Creating opencv video...please wait - " << std::flush;
    std::vector<cv::Mat> images_list_rgb;

    int next_pos;

    for (int frame_id = 0; frame_id < total_output_frames; frame_id++) {

      cv::Mat currentFrame;
      cv::Mat image_rotated;

      if (frame_id == 0) {
        capture.set(cv::CAP_PROP_POS_FRAMES, frame_id);
        // std::cout << "\nInitial position: " << capture.get(cv::CAP_PROP_POS_FRAMES) << std::endl;
        capture >> currentFrame;
        if (currentFrame.empty()) {
          std::cout << "-> frame empty: " << std::endl;
          break;
        }

        cv::rotate(currentFrame, image_rotated, cv::ROTATE_90_CLOCKWISE);
        images_list_rgb.push_back(image_rotated);
        next_pos += multiplier;
        capture.set(cv::CAP_PROP_POS_FRAMES, next_pos);
      } else {

        // std::cout << "Current position: " << capture.get(cv::CAP_PROP_POS_FRAMES) << std::endl;
        capture >> currentFrame;
        if (currentFrame.empty()) {
          std::cout << "-> frame empty: " << std::endl;
          break;
        }

        cv::rotate(currentFrame, image_rotated, cv::ROTATE_90_CLOCKWISE);
        images_list_rgb.push_back(image_rotated);
        next_pos += multiplier;
        capture.set(cv::CAP_PROP_POS_FRAMES, next_pos);
      }
    }

    // // int cont = 1;
    // // for (int frame_i = 0; frame_i < total_number_frames; frame_i++) {
    // for (int frame_i = 0; frame_i < total_output_frames; frame_i++) {
    //   // for (int frame_i : total_number_frames) {

    //   capture.set(cv::CAP_PROP_POS_FRAMES, frame_i * 2);
    //   std::cout << "Current position: " << capture.get(cv::CAP_PROP_POS_FRAMES) << std::endl;
    //   cv::Mat currentFrame;

    //   if (fast_mod(frame_i, multiplier) == 0 or frame_i == 0) {
    //     // if ((frame_i % multiplier) == 0) {
    //     capture >> currentFrame;

    //     if (currentFrame.empty()) {
    //       std::cout << "-> frame empty: " << std::endl;
    //       break;
    //     }

    //     cv::Mat image_rotated;
    //     cv::rotate(currentFrame, image_rotated, cv::ROTATE_90_CLOCKWISE);
    //     images_list_rgb.push_back(image_rotated);

    //     // std::string filename = "Image_" + std::to_string(cont) + ".png";
    //     // cv::imwrite(filename.c_str(), image_rotated.clone());
    //     // cv::namedWindow("inputVideo", cv::WINDOW_NORMAL);
    //     // cv::resizeWindow("inputVideo", 640, 480);
    //     // cv::imshow("inputVideo", currentFrame);
    //     // std::cout << "-> Video_frame: " << cont << std::endl;
    //     // cont += 1;

    //     // cv::waitKey(400);
    //     // cv::destroyAllWindows();

    //   } else {
    //     continue;
    //   }
    // }

    capture.release();
    std::cout << "[OK]" << std::endl;
    // std::cout << "-> Number of frames for new video: " << images_list_rgb.size() << std::endl;
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
    // cv::destroyAllWindows();
  }

  return 0;
}
