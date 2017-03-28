#include <opencv2/opencv.hpp>

int main(int argc, char **argv)
{
    // Rectangle vert 300 par 200
    cv::Mat img(200,300,CV_8UC3,cv::Scalar(0,255,0));
    cv::imshow("Essai", img);
    // Attente appui sur une touche
    cv::waitKey(0);
    return 0;
}
