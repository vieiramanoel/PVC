#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "cstdio"

#ifndef CLICK_CLASS_H_SRC
#define CLICK_CLASS_H_SRC

class PointClickDistance{
  public:
    PointClickDistance();
    ~PointClickDistance();
    static void mouseHandler(int event,int x,int y, int flags,void*);
    void gettingROI();
    float getDistance();
  private:
    bool has_clicked;
    float distance_;
    cv::Mat img_;
    static int click_;
    std::vector<cv::Point> clickedPoint_;
    void draw_points();
    void calculateDistance();
};

#endif
