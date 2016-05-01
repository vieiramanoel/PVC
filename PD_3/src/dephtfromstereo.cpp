#include "opencv2/opencv.hpp"
#include "iostream"
#include "cstdio"
#include "string"
#include "cmath"

cv::Mat createtemplate(int, cv::Mat, cv::Point);
int comparetemplate(cv::Mat, cv::Mat);

int main(int argc, char const *argv[])
{
    cv::Mat rightImage, leftImage;

    if (argc < 3){
        std::cout << "invalid arguments" << std::endl;
        return -1;
    }

    int template_size;

    std::cout << "Digite o tamanho do template: ";
    std::cin >> template_size;
    while(template_size % 2 == 0){
        std::cout << "O template precisa ser um número impar!" << std::endl;
        std::cout << "Digite o tamanho do template: ";
        std::cin >> template_size;
    }

    leftImage = cv::imread(argv[1]);
    rightImage = cv::imread(argv[2]);
    uchar *p;
    cv::cvtColor(rightImage, rightImage, CV_BGR2GRAY);
    cv::cvtColor(leftImage, leftImage, CV_BGR2GRAY);
    cv::Mat templateLeft, templateRight;
    std::vector<int> sadList;
    for (int i = template_size; i < leftImage.rows - template_size; ++i){
        for (int j = template_size; j < leftImage.cols - template_size; ++j){
        	templateLeft = createtemplate(template_size, leftImage, cv::Point(i, j));
        	for (int k = j; k < leftImage.cols - template_size; ++k){
        		templateRight = createtemplate(template_size, rightImage, cv::Point(i,k));
        		sadList.push_back(comparetemplate(templateLeft, templateRight));
        	}
            //std::cout << *std::min_element(sadList.begin(), sadList.end()) << std::endl;
            sadList.clear();
        }
        printf("i = %d \n", i);
    }

    return 0;
}

cv::Mat createtemplate(int template_size, cv::Mat image, cv::Point position){
    cv::Mat createdtemplate(template_size, template_size, CV_8UC1);
    uchar* p;
    int x,y;
    for (int i = 0; i < template_size; ++i){
        p = createdtemplate.ptr<uchar>(i);
        x = position.x - (template_size - 2) + i;
        for (int j = 0; j < template_size; ++j){
            y = position.y - (template_size - 2) + j;
            p[j] = image.at<uchar>(x, y);
        }
    }

    return createdtemplate;
}

int comparetemplate(cv::Mat templateLeft, cv::Mat templateRight){
    uchar *pR, *pL;
    int sad = 0;

    for (int i = 0; i < templateLeft.rows; ++i)
    {
        pL = templateLeft.ptr<uchar>(i);
        pR = templateRight.ptr<uchar>(i);
        for (int j = 0; j < templateLeft.cols; ++j)
        {
            sad += std::abs(pR[j] - pL[j]);
        }
    }

    return sad;
}
