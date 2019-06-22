#include <iostream>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace std;
using namespace cv;
Mat blure;
int Ratio =0,Threshold = 10, Kernel = 0,High =100;
Mat blurer(Mat orig)
{
	//Mat edge(orig.rows,orig.cols,CV_8UC1,Scalar(0));
	Mat blur2(orig.size(),orig.type()),blured(orig.size(),orig.type());
	GaussianBlur(orig,blur2,Size(5,5),3,3);
	GaussianBlur(blur2,blured,Size(5,5),3,3);
	// namedWindow("Blur",WINDOW_NORMAL);
	// namedWindow("Blur2",WINDOW_NORMAL);
	// imshow("Blur2",blur2);
	// imshow("Blur",blured);
	return blured;
}

void edges(int a, void* ch)
{
	Mat edge(blure.size(),blure.type());
	 namedWindow("blur",WINDOW_NORMAL);
	 imshow("blur",blure);
	Canny(blure,edge,Threshold,High,Kernel*2+3);
	imshow("edges",edge);


} 

int main()
{
	Mat orig = imread("car2.jpg",0);
	namedWindow("Original",WINDOW_NORMAL);
	imshow("Original",orig);
	blure = blurer(orig);
	namedWindow("edges",WINDOW_NORMAL);
	createTrackbar("Threshold","edges",&Threshold,100,edges);
	createTrackbar("high","edges",&High,500,edges);
	createTrackbar("Kernel(2n+3)","edges",&Kernel,2,edges);
	edges(0,NULL);
	waitKey(0);
	return 0;
}