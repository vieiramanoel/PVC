/*
 * LaplaceOperator.h
 *
 *  Created on: May 7, 2016
 *      Author: vieira
 */

#ifndef LAPLACEOPERATOR_H_
#define LAPLACEOPERATOR_H_
#include <opencv2/opencv.hpp>
#include <string>

class LaplaceOperator {
  public:
	LaplaceOperator(cv::Mat, std::string);
	void writeImg(std::string);
	void calculate();
	void show();
  private:
	cv::Mat laplace, src_gray, dst;
	int kernel_size;
	int scale;
	int delta;
	int ddepth;
	std::string window_name;
};

#endif /* LAPLACEOPERATOR_H_ */
