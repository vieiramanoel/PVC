/*
 * sobelderivative.h
 *
 *  Created on: May 7, 2016
 *      Author: vieira
 */
#include <opencv2/opencv.hpp>


#ifndef SOBELDERIVATIVE_H_
#define SOBELDERIVATIVE_H_

class SobelDerivative{
  public:
	SobelDerivative(cv::Mat, std::string);
	~SobelDerivative();
	void calculate();
	bool isImageOpened();
	void writeImg(std::string);
	void show();
  private:
  	cv::Mat edge;
  	int scale;
  	int delta;
  	int ddepth;
  	std::string window_name;

};



#endif /* SOBELDERIVATIVE_H_ */
