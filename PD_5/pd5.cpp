#include <opencv2/opencv.hpp>
#include <iostream>

void initializeGLCM(int* glcmMat);
void normalizeGLCM(cv::Mat glcmMat);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cout << "invalid number of arguments" << std::endl << "please pass only one image as argument, returning" << std::endl;
        return -1;
    }

    cv::Mat inputImg = cv::imread(argv[1]);
    if(!inputImg.data){
        std::cout << "argument not valid" << std::endl;
        return -1;
    }

    std::string filename = argv[1];
    filename.erase(filename.end()-4, filename.end());
    filename += ".xml";
    
    cv::Mat glcmHorizontal(256, 256, CV_32FC1);
    cv::cvtColor(inputImg, inputImg, CV_BGR2GRAY);
    int glcmMat[256][256];

    initializeGLCM((int*)glcmMat);
    
    for (int i = 0; i < inputImg.rows; ++i)
        for (int j = 0; j < inputImg.cols - 1; ++j)
           glcmMat[(int)inputImg.at<uchar>(i,j)][(int)inputImg.at<uchar>(i, j+1)]++;

    for (int i = 0; i < 256; ++i)
        for (int j = 0; j < 256; ++j)
            glcmHorizontal.at<float>(i,j) = (float)glcmMat[i][j];
    
    normalizeGLCM(glcmHorizontal);

    initializeGLCM((int*)glcmMat);
    cv::Mat glcm45(256,256, CV_32FC1);
    for (int i = 1; i < inputImg.rows; ++i)
        for (int j = 0; j < inputImg.cols - 1; ++j)
           glcmMat[(int)inputImg.at<uchar>(i, j)][(int)inputImg.at<uchar>(i-1, j+1)]++;
        
    for (int i = 0; i < 256; ++i)
        for (int j = 0; j < 256; ++j)
            glcm45.at<float>(i,j) = (float)glcmMat[i][j];
    
    normalizeGLCM(glcm45);
    
    cv::FileStorage fs(filename, cv::FileStorage::WRITE);
    fs << "glcmMatHorizontal" << glcmHorizontal;
    fs << "glcmMat45" << glcm45;

    return 0;

}

void initializeGLCM(int* glcmMat){
    for (int i = 0; i < 256 * 256; ++i, glcmMat++)
        *glcmMat = 0;
}

void normalizeGLCM(cv::Mat glcm){
    float* p;
    int sum = 0;
    for (int i = 0; i < 256; ++i)
    {
        p = glcm.ptr<float>(i);
        for (int j = 0; j < 256; ++j)
            sum += p[j];
    }

    for (int i = 0; i < 256; ++i)
    {
        p = glcm.ptr<float>(i);
        for (int j = 0; j < 256; ++j)
            p[j] /= sum;
    }
}
