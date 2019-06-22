#include <iostream>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#define pi 3.14159
#define stepsize1 0.2
using namespace std;
using namespace cv;
int nKernel = 7;
int minThreshold = 12, Kernel = 0,maxThreshold =50;
Mat blurer(Mat orig)
{
	Mat blur2(orig.size(),orig.type()),blured(orig.size(),orig.type());
	GaussianBlur(orig,blur2,Size(7,7),5,5);
	GaussianBlur(blur2,blured,Size(7,7),9,9);
	return blured;
}

Mat sobel(Mat img, char ch)
{	
	float ax[3][3] = {-1,0,1,-2,0,2,-1,0,1},ay[3][3] = {1,2,1,0,0,0,-1,-2,-1},a[3][3];		//Convention is taken according to the maths
	Mat g(img.rows,img.cols,CV_8UC1,Scalar(0));
	if(ch == 'x')
	{	//	cout<<"x chala?";
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
				g.at<uchar>(i,j)= val/8+70;				//127 important hai kyunki -vs phir mod ban jata hais
				val=0;
			}
			
		}
		
	}
	else if(ch == 'y')
	{		//cout<<"\ny chala?\n";
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
				g.at<uchar>(i,j)= val/8+70;
				val=0;
			}
			
		}
	}
	return g;

}

Mat sobel(Mat img)
{
	float ax[3][3] = {-1,0,1,-2,0,2,-1,0,1},ay[3][3] = {1,2,1,0,0,0,-1,-2,-1},a[3][3];		//Convention is taken according to the maths
	Mat g(img.rows,img.cols,CV_8UC1,Scalar(0));
	{	//	cout<<"x chala?";
		int val1=0,val2=0,val;
		for(int i=1;i<img.rows-1;i++)
		{
			for(int j=1;j<img.cols-1;j++)
			{
				for(int k=0;k<3;k++)
				{
					for(int l=0;l<3;l++)
					{													//k is for y(cols), 
						val1+=ax[k][l]*img.at<uchar>(i+k-1,j+l-1);		//i is for y(rows), j is for x(cols)
						val2+=ay[k][l]*img.at<uchar>(i+k-1,j+l-1);
					
					}
				}
				val = sqrt( pow(val1,2)+pow(val2,2));
				g.at<uchar>(i,j)= val/8+70;				//127 important hai kyunki -vs phir mod ban jata hais
				val1=val2=0;
			}
			
		}
		
	}

	return g;
}



// point* maximizer(Mat img)
// {	point *a;
// 	long size = 0,current =0,n =0;
// 	a = (point *)malloc(1000*sizeof(point));	//Let one element be wasted
// 	//cout<<"load?\n";
// 	for(int i=4;i<img.rows-4;i++)
// 	{	//cout<<"load? :"<<i<<endl;
// 		for (int j = 4; j <img.cols-4; ++j)
// 		{	//cout<<"load?: "<<j<<endl;
// 			int max = img.at<uchar>(i-4,j-4);
			
// 			for(int k=-4;k<5;k++)
// 			{	
// 				for(int l=-4;l<5;l++)
// 				{
// 					//if(max < (img.at<uchar>(i+k,j+l)) )
// 					{
// 						//max = img.at<uchar>(i+k,j+l);
						
// 						cout<<i<<" "<<j<<"\n";
// 					}
// 					//else
// 					//	continue;
// 				}
// 			}
// 			//cout<<"Aaya yaha?\n";
// 			if(max==img.at<uchar>(i,j))
// 			{	//cout<<"Aaya bhi?\n";
// 				size++;
// 				current++;
// 				//a = (point*)realloc(a,size*sizeof(point));
// 				(a+current)->row = i;
// 				(a+current)->col = j;
// 				a->len++;
// 			}

// 		}
// 	}
// return a;
// }

struct point
{
	int rows,cols,len;
};

point* maximizer(Mat img)
{	long long int count = 0;
	Mat max(img.size(),img.type());
	for(int i=nKernel;i<img.rows-nKernel;i++)
	{
		for(int j= nKernel;j<img.cols- nKernel;j++)
		{
			int temp = img.at<uchar>(i- nKernel,j-nKernel);

			for(int k=- nKernel;k< nKernel;k++)
			{
				for(int l= - nKernel;l< nKernel;l++)
				{	
					if(temp < (img.at<uchar>(i+k,j+l)))
					{
						temp = img.at<uchar>(i+k,j+l);						
					}									
				}
			}

			if(temp==img.at<uchar>(i,j) && temp > 150)
				{count++;
				
				cout<<(img.rows)/2-i<<" "<<(j-25)*stepsize1<<" "<<count<<endl;}

		}
	}

return NULL;
}




float **houghlines(Mat blured) 		//theta elemnent of 0 to 180 and increments of 0.1 degree 
{	
	Mat edge(blured.size(),blured.type()),vote(2*sqrt( pow(blured.rows,2)+pow(blured.cols,2)),(180/stepsize1)+50,CV_8UC1,Scalar(0));	//y(r) maximum
	Canny(blured,edge,minThreshold,maxThreshold,Kernel*2+3);
	imshow("edge",edge);
	float theta = -10,rad = -10;
	int i,j;
	cout<<vote.rows<<" "<<vote.cols;
	for(theta=-5;(theta-175)<1e-3;theta+=stepsize1)
	{	//cout<<"\ntheta: "<<theta;
		for(i=0;i<edge.rows;i++)		//edge.rows-i is y coordinate
		{	
			for(j=0;j<edge.cols;j++)	//edge.cols -j is x coordinate
			{ 	//cout<<" "<<i<<" "<<j; 
				if(edge.at<uchar>(i,j)>100)
				{
					rad = j*sin(theta*pi/180.0) + (edge.rows-i)*cos(theta*pi/180.0);
					
					int row =(vote.rows)/2-rad ,col = 25+(theta/stepsize1);
					
						if(vote.at<uchar>(row,col)<=252)
						{
							vote.at<uchar>(row,col)+=1;
						}
						
					
					
				}
				
			}
		}
	}
	// Mat gx = sobel(vote,'x');	
	// Mat gy = sobel(vote,'y');
	// Mat g1 = sobel(vote),g2;
	// g2 = sobel(g1);

	// namedWindow("grad2",WINDOW_NORMAL);
	// imshow("grad2",g2);
	// namedWindow("grad",WINDOW_NORMAL);
	// imshow("grad",g1);
	// namedWindow("ygrad",WINDOW_NORMAL);
	// imshow("ygrad",gy);
	// namedWindow("xgrad",WINDOW_NORMAL);
	// imshow("xgrad",gx);
	 namedWindow("votes",WINDOW_NORMAL);
	// Mat maxes(vote.size(),vote.type());
	point* a = maximizer(vote);
	// for(int i=1;i<=a->len;i++)
	// {
	// 	maxes.at<uchar>((a+i)->row,(a+i)->col) = 255;
	// }
	// namedWindow("maxes",WINDOW_NORMAL);
	// imshow("maxes",maxes);
	imshow("votes",vote);
	return NULL;

}

int main()
{	float **a;
	Mat blure;
	Mat orig = imread("lanes3.jpg",0);
	namedWindow("Original",WINDOW_NORMAL);
	imshow("Original",orig);
	blure = blurer(orig);
	namedWindow("edges",WINDOW_NORMAL);
	imshow("edges",blure);
	a = houghlines(blure);
	
	// createTrackbar("Threshold","edges",&Threshold,100,edges);
	// createTrackbar("high","edges",&High,500,edges);
	// createTrackbar("Kernel(2n+3)","edges",&Kernel,2,edges);
	// edges(0,NULL);
	waitKey(0);
	return 0;
}