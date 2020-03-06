# video2opencv-video
This is a C++ program to convert a video to opencv format video


## Requirements
		- OpenCV 4.1.2
		- CMake 3.5.1 minimum		


## Compilation

		- mkdir build
		- cd build/
		- cmake ../
		- make

## Test

		- cd build/
		- ./video2opencv <video_file>
		
## Note
To choose more frames, modify:

		(59) - const int total_output_frames = 5; // Number of output desired frames
