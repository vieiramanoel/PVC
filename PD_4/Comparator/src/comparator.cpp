/*
 * comparator.cpp
 *
 *  Created on: May 7, 2016
 *      Author: vieira
 */
#include <opencv2/opencv.hpp>
#include <fstream>


float compare(cv::Mat, cv::Mat);

int main(int argc, char** argv){
	std::ofstream myfile;
	cv::Mat groundTruth = cv::imread(argv[1]);

	myfile.open("resusts.txt", std::fstream::in | std::fstream::out | std::fstream::app);
	for (int i = 2; i < argc; i++){
		cv::Mat testMethod = cv::imread(argv[i]);
		myfile << compare(groundTruth, testMethod);
		myfile << " ";
	}
	myfile << std::endl;

	return 0;
}

float compare(cv::Mat gd, cv::Mat tM){
	uchar *gdPointer, *tmPointer;
	float match = 0, miss = 0;
	for (int i = 0; i < gd.rows; ++i){
		gdPointer = gd.ptr<uchar>(i);
		tmPointer = tM.ptr<uchar>(i);
		for(int j = 0; j < gd.cols; ++j){
			if(gdPointer[j] == tmPointer[j])
				match++;
			else
				miss++;
		}
	}
	return (match/(float)(match+miss));
}
