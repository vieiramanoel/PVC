/*
 * pd6.cpp
 *
 *  Created on: May 27, 2016
 *      Author: vieira
 */

#include <iostream>
#include <opencv2/opencv.hpp>
#include <HarrisDetector.h>
#include <TemplateMaker.h>
#include <cstdio>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/nonfree/nonfree.hpp"


int main(int argc, char** argv){
	HarrisDetector harris;
	TemplateMaker tempmaker;
	cv::VideoCapture cap(1);
	cv::Mat frame;
	std::vector<cv::Point> pts;
	while(true){
		cap >> frame;
		cv::cvtColor(frame, frame, CV_BGR2GRAY);
		harris.Detect(frame);
		harris.getCorners(pts,0.01);
		harris.drawOnImage(frame, pts, cv::Scalar(255,255,255), 3, 2);
		cv::imshow("lala", frame);
		if(cv::waitKey(30) == 27)
			break;
		pts.clear();
	}
	while(1){
		cap >> frame;
		cv::cvtColor(frame, frame, CV_BGR2GRAY);
		cv::namedWindow("lala");
		cv::imshow("lala", frame);
		bool hasclicked = false;
		hasclicked = tempmaker.acquireTemplate(frame, "lala");
		if(hasclicked) break;
		cv::waitKey(30);
	}
	cv::Mat template_;
	template_ = tempmaker.getTemplate();

	cv::FlannBasedMatcher matcher;
	std::vector< cv::DMatch > matches;

	cv::SurfFeatureDetector detector( 2000. );
	std::vector<cv::KeyPoint> keypoints_temp, keypoints_frame;

	cv::SurfDescriptorExtractor extractor;
	cv::Mat descriptorsTemp, descriptorsFrame;
	while(1){
		cap >> frame;
		cv::cvtColor(frame, frame, CV_BGR2GRAY);

		detector.detect( template_, keypoints_temp );
		detector.detect( frame, keypoints_frame );

		extractor.compute(template_, keypoints_temp, descriptorsTemp);
		extractor.compute(frame, keypoints_frame, descriptorsFrame);

		double max_dist = 0, min_dist = 100;

		matcher.match( descriptorsTemp, descriptorsFrame, matches );

		for(int i = 0; i < descriptorsTemp.rows; ++i){
			double dist = matches[i].distance;
			if( dist < min_dist) min_dist = dist;
			if( dist > max_dist) max_dist = dist;
		}

		printf("-- Max dist : %f \n", max_dist );
		printf("-- Min dist : %f \n", min_dist );

		std::vector< cv::DMatch > goodMatches;

		for(int i = 0; i < descriptorsTemp.rows; ++i)
			if(matches[i].distance < 3*min_dist)
				goodMatches.push_back(matches[i]);

		cv::Mat imgMatches;

		cv::drawMatches(template_, keypoints_temp, frame, keypoints_frame, goodMatches, imgMatches,
				cv::Scalar::all(-1), cv::Scalar::all(-1), std::vector<char>(), cv::DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

		std::vector<cv::Point2f> obj;
		std::vector<cv::Point2f> scene;

		for( uint i = 0; i < goodMatches.size(); i++ ){
		//-- Get the keypoints from the good matches
			obj.push_back( keypoints_temp[ goodMatches[i].queryIdx ].pt );
		    scene.push_back( keypoints_frame[ goodMatches[i].trainIdx ].pt );
		}

		cv::Mat H = findHomography( obj, scene, CV_RANSAC );

		std::vector<cv::Point2f> obj_corners(4);
		obj_corners[0] = cv::Point(0,0); obj_corners[1] = cv::Point( template_.cols, 0 );
		obj_corners[2] = cv::Point(template_.cols, template_.rows); obj_corners[3] = cv::Point( 0, template_.rows );
		std::vector<cv::Point2f> scene_corners(4);

		cv::perspectiveTransform(obj_corners, scene_corners, H);

		//-- Draw lines between the corners (the mapped object in the scene - image_2 )
		cv::line( imgMatches, scene_corners[0] + cv::Point2f( template_.cols, 0), scene_corners[1] + cv::Point2f( template_.cols, 0), cv::Scalar(0, 255, 0), 4 );
		cv::line( imgMatches, scene_corners[1] + cv::Point2f( template_.cols, 0), scene_corners[2] + cv::Point2f( template_.cols, 0), cv::Scalar( 0, 255, 0), 4 );
		cv::line( imgMatches, scene_corners[2] + cv::Point2f( template_.cols, 0), scene_corners[3] + cv::Point2f( template_.cols, 0), cv::Scalar( 0, 255, 0), 4 );
		cv::line( imgMatches, scene_corners[3] + cv::Point2f( template_.cols, 0), scene_corners[0] + cv::Point2f( template_.cols, 0), cv::Scalar( 0, 255, 0), 4 );

		cv::imshow( "Good Matches & Object detection", imgMatches );
		if(cv::waitKey(30) == 27) break;
	}


	return 0;
}



