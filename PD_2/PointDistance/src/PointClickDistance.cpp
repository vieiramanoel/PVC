#include "PointClickDistance.hpp"

PointClickDistance::PointClickDistance(){
    img_ = cv::Mat(480, 680, CV_8U);
    has_clicked = false;
}

PointClickDistance::~PointClickDistance(){}

void PointClickDistance::gettingROI(){
    while(!has_clicked){
        cv::imshow("roi", img_);
        cv::setMouseCallback("roi", mouseHandler, (void*)&clickedPoint_);
        if(clickedPoint_.size() == 2){
            for(std::vector<cv::Point>::iterator it = clickedPoint_.begin(); it != clickedPoint_.end(); ++it)
                cv::circle(img_, *it, 5, cv::Scalar(255, 133, 100));
            cv::line(img_, clickedPoint_.at(0), clickedPoint_.at(1), cv::Scalar(255, 133, 100));
            cv::destroyWindow("roi");
            has_clicked = true;
        }
        cv::waitKey(150);
    }
    draw_points();
}

void PointClickDistance::mouseHandler(int event, int x, int y, int flags, void* param){
    if  ( event == cv::EVENT_LBUTTONDOWN ){
        std::vector<cv::Point>* ptPtr = (std::vector<cv::Point>*)param;
        ptPtr->push_back(cv::Point(x,y));
    }
}

void PointClickDistance::draw_points(){
    cv::imshow("Points", img_);
    calculateDistance();
    cv::waitKey(0);
}

void PointClickDistance::calculateDistance(){
    cv::Point diff = clickedPoint_.at(0) - clickedPoint_.at(1);
    distance_ = sqrt(diff.x*diff.x + diff.y*diff.y);
    printf("%f\n", distance_ );
}

float PointClickDistance::getDistance(){
    return distance_;
}