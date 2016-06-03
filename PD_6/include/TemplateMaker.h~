/*
 * TemplateMaker.h
 *
 *  Created on: May 28, 2016
 *      Author: vieira
 */
#ifndef INCLUDE_TEMPLATEMAKER_H_
#define INCLUDE_TEMPLATEMAKER_H_

#include <opencv2/opencv.hpp>

class TemplateMaker {
  public:
	TemplateMaker();
	bool acquireTemplate(cv::Mat&, std::string);
	cv::Mat getTemplate();
  private:
	cv::Mat _template;
	cv::Point *_clickedPoint;
	cv::Mat _input;
	std::string _window;
	static void mouseHandler(int, int, int, int, void*);
};

#endif /* INCLUDE_TEMPLATEMAKER_H_ */
