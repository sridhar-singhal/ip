#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
#include <iostream>
using namespace std;
using namespace cv;

int main()
{	Mat i1 = imread("hay.jpg",0);
	Mat i2;
	i2 = i1;
	namedWindow("Origianal",WINDOW_NORMAL);
	namedWindow("Copy",WINDOW_NORMAL);
	for(int i=0;i<100;i++)
	{
		for(int j=0;j<100;j++)
		{
			i1.at<uchar>(i+20,j+20)=255;

			imshow("Origianal",i1);
			imshow("Copy",i2);
			waitKey(15);
			cout<<"KalaHUa?\n"<<i<<" ";
		}
		
	}

	waitKey(0);

	return 0;

}