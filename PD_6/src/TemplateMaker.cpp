/*
 * TemplateMaker.cpp
 *
 *  Created on: May 28, 2016
 *      Author: vieira
 */

#include <TemplateMaker.h>

TemplateMaker::TemplateMaker() {
    // TODO Auto-generated constructor stub
    _clickedPoint = NULL;
}

cv::Mat TemplateMaker::getTemplate(){
    return _template;
}

bool TemplateMaker::acquireTemplate(cv::Mat& image, std::string window){
    _input = image;
    _window = window;
    //if(_clickedPoint->x >= 0 && _clickedPoint->y >= 0){
    if(_clickedPoint != NULL){
    	_template = _input;
    	cv::destroyAllWindows();
    	return true;
    }
    else
    	cv::setMouseCallback(window, mouseHandler, (void*)this);
    return false;
}

void TemplateMaker::mouseHandler(int event, int x, int y, int flags, void* param){
    TemplateMaker* thisptr = (TemplateMaker*) param;
    if  ( event == cv::EVENT_LBUTTONDOWN ){
            thisptr->_clickedPoint = new cv::Point(x, y);
            thisptr->acquireTemplate(thisptr->_input, thisptr->_window);
            cv::imwrite("ashudh.png", thisptr->_input);
        return;
    }
}

