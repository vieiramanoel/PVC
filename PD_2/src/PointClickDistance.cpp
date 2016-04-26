#include "PointClickDistance.hpp"

PointClickDistance::PointClickDistance(std::string window_name){
    distance_ = 0.0;
    window_ = window_name;
}

PointClickDistance::~PointClickDistance(){}

bool PointClickDistance::gettingROI(cv::Mat img){
	cv::setMouseCallback(window_, mouseHandler, (void*)&clickedPoint_);
	if(clickedPoint_.size() == 2){
		return true;
	}else return false;
}

void PointClickDistance::mouseHandler(int event, int x, int y, int flags, void* param){
    if  ( event == cv::EVENT_LBUTTONDOWN ){
    	std::vector<cv::Point>* ptPtr = (std::vector<cv::Point>*)param;
        ptPtr->push_back(cv::Point(x,y));
    }
}

void PointClickDistance::draw_points(cv::Mat frame){
	for(std::vector<cv::Point>::iterator it = clickedPoint_.begin(); it != clickedPoint_.end(); ++it)
		cv::circle(frame, *it, 5, cv::Scalar(255, 255, 255));
	cv::line(frame, clickedPoint_.at(0), clickedPoint_.at(1), cv::Scalar(255, 255, 255));

}
void PointClickDistance::calculateDistance(){
	cv::Point diff = clickedPoint_.at(0) - clickedPoint_.at(1);
	distance_ = sqrt(diff.x*diff.x + diff.y*diff.y);
}

float PointClickDistance::getDistance(){
	calculateDistance();
	return distance_;
}

void PointClickDistance::draw_grid(cv::Mat frame){
	for(int i = 0; i <= 640; i +=160){
		cv::line(frame, cv::Point(i, 0), cv::Point(i, 480), cv::Scalar(255, 0, 0));
		for(int j = 0; j < 480; j += 120)
			cv::line(frame, cv::Point(0, j), cv::Point(640, j), cv::Scalar(255, 0, 0));
	}
}

void PointClickDistance::clear(){
    distance_ = 0.0;
    clickedPoint_.clear();
}

