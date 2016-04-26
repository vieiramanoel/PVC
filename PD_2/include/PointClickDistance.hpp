#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <cstdio>

#ifndef CLICK_CLASS_H_SRC
#define CLICK_CLASS_H_SRC

class PointClickDistance{
  public:
    PointClickDistance(std::string window_name);
    ~PointClickDistance();
    bool gettingROI(cv::Mat);
    void draw_points(cv::Mat);
    void draw_grid(cv::Mat);
    float getDistance();
    static void mouseHandler(int, int, int, int, void*);
    void clear();
  private:
    void calculateDistance();
    float distance_;
    std::vector<cv::Point> clickedPoint_;
    std::string window_;
};

#endif
