//============================================================================
// Name        : PD4.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <cstdio>
#include "SobelDerivative.h"
#include "CannyEdge.h"

int main(int argc,char** argv) {
	cv::Mat src = cv::imread(argv[1]);

	if (not src.data)
		return -1;

	std::string grad_window = "Gradient", canny_window = "Canny";
	SobelDerivative grad(src, grad_window);
	CannyEdge canny(src, canny_window);

	std::cout << "Calculating Sobel Derivative" << std::endl;
	grad.calculate();
	grad.showGradient();

	std::cout << "Calculatin Canny" << std::endl;
	canny.calculate();

	cv::waitKey(0);

	return 0;
}
