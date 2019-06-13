/*1. In uchar or Vec3b, if you move above 255 then, the answer becomes ans = val -255.
Similar thing happens if it gets negative, it does not put up an error message.
2.Working with images with many many pixels is very difficult as the edges are not sharp enough. 
So the filter does not produce sharp enough edges.
3. Keep a note of your rows and cols of the image and the filter.Generally, you can get your sign
convention on the filter itself and do a ni=ormal correlation (same cell multiplied with same cell).
In that case, you just have to add row to row and col to col, no buffoonry. 
4. root of sum of squares help in some amount to make a rough edge only image. Now what happens is
that you need set your zero point and you need add or subtract accordingly. 
*/
#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"

using namespace cv;
using namespace std;

Mat sobel(Mat img, char ch)
{	float ax[3][3] = {-1,0,1,-2,0,2,-1,0,1},ay[3][3] = {1,2,1,0,0,0,-1,-2,-1},a[3][3];		//Convention is taken according to the maths
	Mat g(img.rows,img.cols,CV_8UC1,Scalar(0));
	if(ch == 'x')
	{	cout<<"x chala?";
		int val=0;
		for(int i=1;i<img.rows-1;i++)
		{
			for(int j=1;j<img.cols-1;j++)
			{
				for(int k=0;k<3;k++)
				{
					for(int l=0;l<3;l++)
					{													//k is for y(cols), 
						val+=ax[k][l]*img.at<uchar>(i+k-1,j+l-1);		//i is for y(rows), j is for x(cols)
					}
				}
				g.at<uchar>(i,j)= val/8+127;				//127 important hai kyunki -vs phir mod ban jata hais
				val=0;
			}
			
		}
		
	}
	else if(ch == 'y')
	{	cout<<"\ny chala?\n";
		int val=0;
		for(int i=1;i<img.rows-1;i++)
		{
			for(int j=1;j<img.cols-1;j++)
			{
				for(int k=0;k<3;k++)
				{
					for(int l=0;l<3;l++)
					{													//k is for y(rows)(row number = y) 
						val+=ay[k][l]*img.at<uchar>(i+k-1,j+l-1);		//i is for y(rows), j is for x(cols)
					}
				}
				g.at<uchar>(i,j)= val/8+127;
				val=0;
			}
			
		}
	}
	//cout<<a<<"\t"<<ax<<"\t"<<ay<<endl;
for(int i=0;i<3;i++)
{
	for(int j=0;j<3;j++)
	{
			cout<<ax[i][j]<<" ";
	}
	cout<<endl;
}

	return g;




}


Mat magnitude(Mat gx, Mat gy)
{
	Mat mag(gx.rows,gx.cols,CV_8UC1,Scalar(0));
	for (int i = 0; i <gx.rows; ++i)
	{
		for(int j=0;j<gx.cols;j++)
		{
			float grad = pow(gx.at<uchar>(i,j),2) + pow(gy.at<uchar>(i,j),2);
			grad = sqrt(grad);
			mag.at<uchar>(i,j)=int(grad);//-int(127*sqrt(2));
		}
	}
return mag;
}


int main(int argc, char const *argv[])
{
	Mat img = imread("steinway2.jpg",0),gx,gy,gmag;		//The problem with pictures with very high pixel count is that edges are not sharp, don't get no sharp grad
	gx = sobel(img,'x');	
	gy = sobel(img,'y');
	gmag = magnitude(gx,gy);
	cout<<"Image aai?\n";
	namedWindow("grad",0);
	namedWindow("orig",0);
	namedWindow("xgrad",0);
	namedWindow("ygrad",0);

	imshow("grad",gmag);
	imshow("orig",img);
	imshow("xgrad",gx);
	imshow("ygrad",gy);
	waitKey(0);
	return 0;
}