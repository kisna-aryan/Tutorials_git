#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui.hpp"
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main(int argc, const char** argv) {
    // Mat img = imread("/media/darthvader/data/CUDA/CUDA_git/Tutorials_git/read_image_opencv/images/frameIndex_0.png");
    // Mat img = imread("/home/delta/CUDA_git/git_jetson/tutorial_jetson/Tutorials_git/read_image_opencv/images/frameIndex_0.png");
    Mat img = imread("images/frame_04001.png");

    if (img.empty()) {
        cout << "Error: Image cannot be loaded." << endl;
        system("pause");
        return -1;
    }
    cout << "image height:" << img.rows << endl << "Image width:" << img.cols << endl;
    cout << "Number of channels:" << img.channels() << endl << "Bytes per line:" << img.step << endl;
    namedWindow("Image Window");
    imshow("Image Window", img);
    if (waitKey() == 27) {
        return -1;
    }
    destroyWindow("Image Window");
    return 0;
}