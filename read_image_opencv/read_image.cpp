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
    Mat img = imread("images/frameIndex_0.png");

    if (img.empty()) {
        cout << "Error: Image cannot be loaded." << endl;
        system("pause");
        return -1;
    }
    namedWindow("Image Window");
    imshow("Image Window", img);
    if (waitKey() == 27) {
        return -1;
    }
    destroyWindow("Image Window");
    return 0;
}