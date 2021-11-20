
// Include Libraries
#include<opencv2/opencv.hpp>
#include<iostream>

// Namespace nullifies the use of cv::function();
using namespace std;
using namespace cv;

int main()
{
	// Read image
    Mat img_color, img_grayscale, img_unchanged;
    vector<string> fn; // std::string in opencv2.4, but cv::String in 3.0
    string path = "/home/delta/CUDA_git/dataset_thermal/Germany/Berlin/2019-11-16_23.08.04_done/16BitFrames/*.png";
    cv::glob(path,fn,false);
    // Now you got a list of filenames in fn.
    printf("%d\n",fn.size());

    for (string filename:fn)
    {
        std::cout << filename << std::endl;
        img_grayscale = imread(filename,0);
        imshow("grayscale image", img_grayscale);
        int key = waitKey(40);
        if (key == 'q')
        {
           cout << "q key is pressed by the user. Stopping the video" << endl;
           break;
        }

    }

	return 0;
}