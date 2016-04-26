#include "PointClickDistance.hpp"
#include <cstdlib>
#include <iostream>
#include <string>
#include <cstdio>

int main(int argc, char** argv){

	if (argc != 2){
		std::cout << "invalid arguments" << std::endl;
		return -1;
	}else if (strlen(argv[1]) != 1){
		std::cout << "invalid arguments" << std::endl;
		return -1;
	}

	int camera = (int)argv[1][0] - '0';

    cv::Mat distortionMat, intrinsicsMat;
    cv::Mat mapx, mapy, frame;
    std::string distortion = "Distortion.xml";
    std::string intrinsics = "Intrinsics.xml";
    bool hasclickedRaw = false, hasclickedUndistort = false, hasFinished = false;

    cv::VideoCapture cap(camera);

    if (not cap.isOpened())
        return -1;

    cap >> frame;
    cv::flip(frame, frame, 1);
    
    cv::FileStorage dstfs(distortion, cv::FileStorage::READ);
    dstfs["Distortion"] >> distortionMat;
    dstfs.release();

    cv::FileStorage intrfs(intrinsics, cv::FileStorage::READ);
    intrfs["Intrinsics"] >> intrinsicsMat;
    intrfs.release();

    cv::Mat emptyR;
    mapx.create(frame.size(), CV_32FC1);
    mapy.create(frame.size(), CV_32FC1);
    cv::initUndistortRectifyMap(intrinsicsMat, distortionMat, emptyR, intrinsicsMat, frame.size(), CV_32FC1, mapx, mapy);
    do{
        PointClickDistance clickRaw("Raw Image"), clickUndistort("Undistort Image");
        hasclickedRaw = false;
        hasclickedUndistort = false;
        while(not (hasclickedRaw and hasclickedUndistort)){
        	cv::Mat img = frame.clone();
        	cv::remap(frame, img, mapx, mapy, CV_INTER_LINEAR, cv::BORDER_CONSTANT, cv::Scalar(0,0, 0));
        	clickRaw.draw_grid(img);
    		clickUndistort.draw_grid(frame);
        	cv::imshow("Raw Image", frame);
        	cv::imshow("Undistort Image", img);
        	hasclickedRaw = clickRaw.gettingROI(frame);
        	hasclickedUndistort = clickUndistort.gettingROI(img);
        	cap >> frame;
            cv::flip(frame, frame, 1);
        	if (cv::waitKey(60) >= 30) break;
        }
        if(not (hasclickedRaw or hasclickedUndistort))
        	return -1;
        printf("Raw Distance = %f\n", clickRaw.getDistance());
    	printf("Undistort Distance = %f\n", clickUndistort.getDistance());
        while(true){
        	cv::Mat img = frame.clone();
    		cv::remap(frame, img, mapx, mapy, CV_INTER_LINEAR, cv::BORDER_CONSTANT, cv::Scalar(0,0, 0));
    		clickRaw.draw_points(frame);
    		clickUndistort.draw_points(img);
    		clickRaw.draw_grid(img);
    		clickUndistort.draw_grid(frame);
    		cv::imshow("Raw Image", frame);
    		cv::imshow("Undistort Image", img);
    		cap >> frame;
            cv::flip(frame, frame, 1);
    		if(cv::waitKey(30) >= 30) break;
        }
        clickRaw.clear();
        clickUndistort.clear();
    }while(not hasFinished);

    return 0;
}
