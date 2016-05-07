/*
 * CannyEdge.h
 *
 *  Created on: May 7, 2016
 *      Author: vieira
 */

#ifndef CANNYEDGE_H_
#define CANNYEDGE_H_
#include <opencv2/opencv.hpp>

class CannyEdge{
  public:
	CannyEdge(cv::Mat, std::string);
	~CannyEdge();
	void calculate();
  private:
	static void CannyThreshold(int, void*);
	cv::Mat cannyMat;
	cv::Mat grayCannyMat;
	int edgeThresh;
	int lowThreshold;
	int const max_lowThreshold;
	int ratio;
	int kernel_size;
	std::string window_name;
};



#endif /* CANNYEDGE_H_ */
