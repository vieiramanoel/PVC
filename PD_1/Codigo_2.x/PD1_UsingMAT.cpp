#include <opencv2/opencv.hpp>

#define ROW 480
#define COLS 640

int main(int argc, char const *argv[])
{
    cv::Mat Image(ROW, COLS, CV_8U);
    uchar* p; 
    
    for (int i = 0; i < Image.rows; ++i)
    {
        p = Image.ptr<uchar>(i);
        for (int j = 0; j < Image.cols; ++j)
            p[j] = ((i*j) % 256);
    }
    
    cv::imshow("Created Image", Image);
    cv::waitKey(0);

    return 0;
}