/*
 * HarrisDetector.cpp
 *
 *  Created on: May 27, 2016
 *      Author: vieira
 */

#include <HarrisDetector.h>

HarrisDetector::HarrisDetector() : neighbourhood(3), aperture(3),
								   k(0.01), maxStrength(0.0),
								   threshold(0.01), nonMaxSize(3){

}

void HarrisDetector::Detect(cv::Mat& image) {
	cv::cornerHarris(image, cornerStrength, neighbourhood, aperture, k);
	double minStrength;
	cv::minMaxLoc(cornerStrength, &minStrength, &maxStrength);
	cv::Mat dilated;
	cv::dilate(cornerStrength,dilated,cv::Mat());
	cv::compare(cornerStrength,dilated,
	localMax,cv::CMP_EQ);
}

cv::Mat HarrisDetector::getCornerMap(double qualityLevel) {
	cv::Mat cornerMap;
	threshold= qualityLevel*maxStrength;
	cv::threshold(cornerStrength,cornerTh,
	threshold,255,cv::THRESH_BINARY);
	cornerTh.convertTo(cornerMap, CV_8UC1);
	cv::bitwise_and(cornerMap,localMax,cornerMap);
	return cornerMap;
}

void HarrisDetector::getCorners(std::vector<cv::Point> &points,
								double qualityLevel) {
	cv::Mat cornerMap= getCornerMap(qualityLevel);
	this->getCorners(points, cornerMap);
}
void HarrisDetector::getCorners(std::vector<cv::Point> &points,
				const cv::Mat& cornerMap) {
	for( int y = 0; y < cornerMap.rows; y++ ) {
		const uchar* rowPtr = cornerMap.ptr<uchar>(y);
		for( int x = 0; x < cornerMap.cols; x++ ) {
			if (rowPtr[x]) {
				points.push_back(cv::Point(x,y));
			}
		}
	}
}

void HarrisDetector::drawOnImage(cv::Mat &image,
				const std::vector<cv::Point> &points,
				cv::Scalar color= cv::Scalar(255,255,255),
				int radius=3, int thickness=2) {
	std::vector<cv::Point>::const_iterator it=points.begin();
	while (it!=points.end()) {
		cv::circle(image,*it,radius,color,thickness);
		++it;
	}
}
