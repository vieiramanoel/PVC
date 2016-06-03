/*
 * HarrisDetector.h
 *
 *  Created on: May 27, 2016
 *      Author: vieira
 */

#ifndef INCLUDE_HARRISDETECTOR_H_
#define INCLUDE_HARRISDETECTOR_H_
#include <opencv2/opencv.hpp>

class HarrisDetector {
  public:
	HarrisDetector();
	void Detect(cv::Mat&);
	cv::Mat getCornerMap(double);
	void getCorners(std::vector<cv::Point>&, double);
	void getCorners(std::vector<cv::Point>&, const cv::Mat&);
	void drawOnImage(cv::Mat&, const std::vector<cv::Point>&, cv::Scalar, int, int);
  private:
	cv::Mat cornerStrength;
	cv::Mat cornerTh;
	cv::Mat localMax;
	int neighbourhood;
	int aperture;
	double k;
	double maxStrength;
	double threshold;
	int nonMaxSize;
	cv::Mat kernel;
};

#endif /* INCLUDE_HARRISDETECTOR_H_ */
