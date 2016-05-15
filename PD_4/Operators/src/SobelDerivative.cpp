/*
 * sobelderivative.cpp
 *
 *  Created on: May 7, 2016
 *      Author: vieira
 */
#include "SobelDerivative.h"

SobelDerivative::SobelDerivative(cv::Mat inputMat, std::string window){
	edge = inputMat;
	scale = 1;
	delta = 0;
	ddepth = CV_16S;
	window_name = window;
}

SobelDerivative::~SobelDerivative(){

}

void SobelDerivative::calculate(){
	cv::Mat grad_x, grad_y;
	cv::Mat abs_grad_x, abs_grad_y;

	cv::GaussianBlur(edge, edge, cv::Size(3,3), 0, 0, cv::BORDER_DEFAULT);
	cv::cvtColor( edge, edge, CV_BGR2GRAY);

	//Calculating gradient x and converting to abs
	cv::Sobel( edge, grad_x, ddepth, 1, 0, 3, scale, delta, cv::BORDER_DEFAULT );
	cv::convertScaleAbs( grad_x, abs_grad_x );

	//Calculating gradient y and converting to abs
	cv::Sobel( edge, grad_y, ddepth, 0, 1, 3, scale, delta, cv::BORDER_DEFAULT );
	cv::convertScaleAbs( grad_y, abs_grad_y );
	cv::addWeighted( abs_grad_x, 0.5, abs_grad_y, 0.5, 0, edge);
	edge = 255 - edge;
}

bool SobelDerivative::isImageOpened(){
	if (!edge.data)
		return false;
	else
		return true;
}

void SobelDerivative::writeImg(std::string name){
	std::string folder = "Results/Sobel/";
	std::string finalpath = folder + name;
	cv::imwrite(finalpath, edge);
}

void SobelDerivative::show(){

	cv::namedWindow( window_name, CV_WINDOW_AUTOSIZE );
	cv::imshow(window_name, edge);
}
