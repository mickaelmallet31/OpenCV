#include <opencv2/opencv.hpp>

int main(void)
{
  cv::Mat img;

  cv::VideoCapture cap(0);
  if(!cap.isOpened())
    return -1;

  do
  {
    cap >> img;
    cv::imshow("Video", img);
  } while(cv::waitKey(20) == -1);

  return 0;
}
