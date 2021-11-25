#include<iostream>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
 
using namespace std;
using namespace cv;

#define NoOfBins 65536
#define maxThresold 50
#define minThersold 50
#define TotalNoOfPixels 76800
#define ClipLimit   0.0001
#define NoOfclipPixels  76800*ClipLimit
 
int main()
{
    
    int histogram[NoOfBins];
    unsigned char histogram_LUT[NoOfBins];
    unsigned char HE_LUT[NoOfBins];
    float CDF[NoOfBins];
    float CDF_norm[NoOfBins];

    // Mat image = imread("nature.jpg", 0);
    Mat image = imread("images/frameIndex_0.png", -1);
    Mat image_1 = imread("images/frameIndex_1.png", -1);


    if( image.empty() )
    {
        cout << "Image not Found" << endl;
        return EXIT_FAILURE;
    }
    Mat proc_image = Mat::zeros(Size(image.cols,image.rows),CV_8UC1);
    // allcoate memory for no of pixels for each intensity value
    /*     The maximum number of pixels can be total number of pixels in image.

    Total number of pixels in image resolution 640x512 is = 327680 

    The number of bins in 16 bit image is => 2^16 = 65536
    */
 
    // initialize all intensity values to 0
    for(int i = 0; i < NoOfBins; i++)
    {
        histogram[i] = 0;
        CDF[i] = 0;
    }
    
    // cout << sizeof(unsigned short)<< endl;
    cout << "pixel value:" << image.at<u_int16_t>(100,100)<< endl;
    cout <<" Channels:" << image.channels()<< endl;

    // calculate the no of pixels for each intensity values
    for(int y = 0; y < image.rows; y++)
    {
        for(int x = 0; x < image.cols; x++)
        {
            histogram[image.at<u_int16_t>(y,x)]++;
        }
    }

    // int clipedPixels,perBindistribution;
    for(int i = 0; i < NoOfBins; i++){
        if(NoOfclipPixels < histogram[i]){
            // clipedPixels += histogram[i] - NoOfclipPixels;
            histogram[i] = NoOfclipPixels;
        }
    }
    // perBindistribution = clipedPixels/NoOfBins;
    
    int TotalPixelsAfterDistr = 0;
    for(int i = 0; i < NoOfBins; i++)
    {
        // histogram[i] += perBindistribution; 
        TotalPixelsAfterDistr += histogram[i];     
    }
  
    // draw the histograms
    int hist_w = 512; int hist_h = 400;
    // int bin_w = cvRound((double) hist_w/NoOfBins);
    double bin_w = (double) hist_w/NoOfBins;

 
    Mat histImage(hist_h, hist_w, CV_8UC1, Scalar(255, 255, 255));
 
     // find the maximum intensity element from histogram
    int hist_max = histogram[0];
    for(int i = 1; i < NoOfBins; i++){
        if(hist_max < histogram[i]){
            hist_max = histogram[i];
        }
    }

    //Calculate the CDF LUT
    float new_pixel, min_max_diff;
    
    CDF[0] = histogram[0];
    for(int i = 1; i < NoOfBins; i++)
    {
        CDF[i] = CDF[i-1] + histogram[i];
        CDF_norm[i] = CDF[i]/TotalPixelsAfterDistr;
    }

    for(int i = 0; i < NoOfBins; i++)
    {
        new_pixel = CDF_norm[i];
        histogram_LUT[i] = (unsigned char)(new_pixel*255);
    } 
    
    // convert image into 8 bit
    // calculate the no of pixels for each intensity values

    for(int y = 0; y < image.rows; y++)
    {
        for(int x = 0; x < image.cols; x++)
        {
            proc_image.at<uchar>(y,x) = histogram_LUT[image.at<u_int16_t>(y,x)];
        }
    }
 
    // normalize the histogram between 0 and histImage.rows
 
    for(int i = 0; i < NoOfBins; i++){
        histogram[i] = ((double)histogram[i]/hist_max)*histImage.rows;
    }
 
 
    // draw the intensity line for histogram
    for(int i = 0; i < NoOfBins; i++)
    {
        line(histImage, Point(cvRound(bin_w*(i)), hist_h),
                              Point(cvRound(bin_w*(i)), hist_h - histogram[i]),
             Scalar(0,0,0), 1, 8, 0);
    }
 
    hconcat(image,image_1,image_1);//Syntax-> hconcat(source1,source2,destination);

    // display histogram
    namedWindow("Intensity Histogram");
    imshow("Intensity Histogram", histImage);
 
    namedWindow("Image");
    imshow("Image", proc_image);
    waitKey();
    return 0;
}