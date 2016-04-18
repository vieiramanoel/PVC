#include "PointClickDistance.hpp"

PointClickDistance::PointClickDistance(std::string window_name){
    img_ = cv::Mat();
	has_clicked = false;
    distance_ = 0.0;
    window_ = window_name;
}

PointClickDistance::~PointClickDistance(){}

void PointClickDistance::gettingROI(){

        cv::setMouseCallback(window_, mouseHandler, (void*)&clickedPoint_);
        if(clickedPoint_.size() == 2){
            for(std::vector<cv::Point>::iterator it = clickedPoint_.begin(); it != clickedPoint_.end(); ++it)
                cv::circle(*img_, *it, 5, cv::Scalar(255, 133, 100));
            cv::line(*img_, clickedPoint_.at(0), clickedPoint_.at(1), cv::Scalar(255, 133, 100));
            has_clicked = true;
        }
    //draw_points();
}

void PointClickDistance::mouseHandler(int event, int x, int y, int flags, void* param){
    if  ( event == cv::EVENT_LBUTTONDOWN ){
        std::vector<cv::Point>* ptPtr = (std::vector<cv::Point>*)param;
        ptPtr->push_back(cv::Point(x,y));
    }
}

void PointClickDistance::draw_points(){
    calculateDistance();
}
void PointClickDistance::calculateDistance(){
    cv::Point diff = clickedPoint_.at(0) - clickedPoint_.at(1);
    distance_ = sqrt(diff.x*diff.x + diff.y*diff.y);
    printf("%f\n", distance_ );
}

float PointClickDistance::getDistance(){
    return distance_;
}

void PointClickDistance::setframe(cv::Mat frame){
	img_ = frame;
}