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
#include "LaplaceOperator.h"

int main(int argc,char** argv) {

	std::string grad_window = "Gradient", canny_window = "Canny", lapace_window = "Laplace";
	cv::Mat src = cv::imread(argv[1]);
	if (not src.data)
		return -1;
	std::string argument = (std::string)argv[1];
	std::string nametowrite;
	nametowrite.append(argument.begin(), argument.end()-4);
	std::string::iterator it;
	for(it = nametowrite.end(); *it != '/'; it--);
	it++;
	nametowrite.erase(nametowrite.begin(), it);
	nametowrite += "binarized.png";
	SobelDerivative grad(src, grad_window);
	CannyEdge canny(src, canny_window, nametowrite);
	LaplaceOperator laplace(src, lapace_window);

	std::cout << "Calculating Sobel Derivative" << std::endl;
	grad.calculate();
	grad.show();
	grad.writeImg(nametowrite);


	std::cout << "Calculating Canny" << std::endl;
	canny.show();
	canny.writeImg();

	std::cout << "Calculatin w/ Lapace Operator" << std::endl;
	laplace.calculate();
	laplace.show();
	laplace.writeImg(nametowrite);

	cv::waitKey(0);
	return 0;
}
