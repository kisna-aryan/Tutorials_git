#include<iostream>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
 
using namespace std;
using namespace cv;

#define NoOfBins 65536
 
int main()
{ 
    Mat image = imread("images/frameIndex_0.png", -1);
    //Before changing
    imshow("Before",image);
    //change some pixel value
    for(int j=0;j<image.rows;j++) 
    {
        for (int i=0;i<image.cols;i++)
        {
            if( i== j)   
                image.at<uchar>(j,i) = 255; //white
        }
    }
    //After changing
    imshow("After",image);
    waitKey(0);

return 0;
}