/*
 * CannyEdge.cpp
 *
 *  Created on: May 7, 2016
 *      Author: vieira
 */

#include "CannyEdge.h"

CannyEdge::CannyEdge(cv::Mat inputMat, std::string window) : max_lowThreshold(100){
	cannyMat = inputMat;
	grayCannyMat = cannyMat;
	edgeThresh = 1;
	lowThreshold = 0;
	ratio = 3;
	kernel_size = 3;
	window_name = window;
}

CannyEdge::~CannyEdge(){

}

void CannyEdge::calculate(){
	cv::namedWindow(window_name, CV_WINDOW_AUTOSIZE);
	cv::imshow(window_name, cannyMat);
	cv::cvtColor(cannyMat, grayCannyMat, CV_BGR2GRAY);
	cv::createTrackbar("Min Threshold:", window_name, &lowThreshold, max_lowThreshold, CannyEdge::CannyThreshold, (void*)this);
}

void CannyEdge::CannyThreshold(int, void* param){
	/// Reduce noise with a kernel 3x3
	std::cout << "to aqui" << std::endl;
	CannyEdge* pointer = (CannyEdge*) param;
	cv::Mat detectedEdges, dst;
	cv::blur(pointer->grayCannyMat, detectedEdges, cv::Size(3,3) );
	cv::Canny( detectedEdges, detectedEdges, pointer->lowThreshold, pointer->lowThreshold*pointer->ratio, pointer->kernel_size );
	dst = cv::Scalar::all(0);
	pointer->cannyMat.copyTo(dst, detectedEdges);
	cv::imshow(pointer->window_name, dst);
}




