/*
 * LaplaceOperator.cpp
 *
 *  Created on: May 7, 2016
 *      Author: vieira
 */

#include "LaplaceOperator.h"

LaplaceOperator::LaplaceOperator(cv::Mat input, std::string window) {
	laplace = input;
	kernel_size = 3;
	scale = 1;
	delta = 0;
	ddepth = CV_16S;
	window_name = window;

}


void LaplaceOperator::calculate(){
	cv::GaussianBlur( laplace, laplace, cv::Size(3,3), 0, 0, cv::BORDER_DEFAULT );
	cv::cvtColor( laplace, src_gray, CV_BGR2GRAY );
	cv::Mat abs_dst;
	cv::Laplacian( src_gray, dst, ddepth, kernel_size, scale, delta, cv::BORDER_DEFAULT );
	cv::convertScaleAbs( dst, abs_dst );
	abs_dst = 255 - abs_dst;
	laplace = abs_dst;

}

void LaplaceOperator::show(){
	cv::imshow(window_name, laplace);
}

void LaplaceOperator::writeImg(std::string name){
	std::string folder = "Results/Laplace/";
	std::string finalpath = folder + name;

	cv::imwrite(finalpath, laplace);
}
