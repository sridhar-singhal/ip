/*Take home messages:
1.medianBlur(source,destination,kernal size(only odd)) is a great way to 
remove noise that is non mathematical. It works on the assumption that 
there are no abrupt changes in values of pixels. It takes the meadian 
value of all values present in the kernel and assigns to the central pixel. 
2. Check it: why on the copy images, CV_8UC3 did not work and the image got shrunk. 
3. First program where we have directly accesed pixel intensities. 
*/

#include <iostream>
#include <stdlib.h>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace std;
using namespace cv;
#define perton 5
Mat saltAndPepper(Mat a)
{
	Mat badimg(a.rows,a.cols,CV_8UC1,Scalar(0));	//This being cv_8uc3 compressed the image, don't know why Did not allow even to copy coloured images
	for(int i=0 ; i<a.rows;i++)
	{
		for(int j=0;j<a.cols;j++)
		{
			// badimg.at<Vec3b>(i,j)[0]=a.at<Vec3b>(i,j)[0];			//Accessing each and every element to make a copy
			// badimg.at<Vec3b>(i,j)[1]=a.at<Vec3b>(i,j)[1];			//Equating is not a good idea as it kill the original image too.
			// badimg.at<Vec3b>(i,j)[2]=a.at<Vec3b>(i,j)[2];
			badimg.at<uchar>(i,j)=a.at<uchar>(i,j);

		}
	}

	for(int i=0;i<(a.rows*a.cols)*perton/1000;i++)
	{
		int row = rand()%(a.rows-4)+2, col = rand()%(a.cols-4)+2;
		int val = (rand()%2)*255;
		// badimg.at<Vec3b>(row,col)[0]=val;
		// badimg.at<Vec3b>(row,col)[1]=val;
		// badimg.at<Vec3b>(row,col)[2]=val;
		// for(int j=-1;j<2;j++)
		// {
		// 	for(int k=-1;k<2;k++)
		// 	{
		// 		badimg.at<uchar>(row+j,col+k)=val;	
		// 	}
		// }
		badimg.at<uchar>(row,col)=val;	
		cout<<"row: "<<row<<" col: "<<col<<" val: "<<val<<endl;
	}
	return badimg;

}

int main(int argc, char const *argv[])
{
	Mat iIn = imread("steinway2.jpg",0);
	Mat badimg = saltAndPepper(iIn);
	Mat corrected(iIn.rows,iIn.cols,CV_8UC1,Scalar(0));
	medianBlur(badimg,corrected,3);		//You can put in here a one but it is of no use as one value shall be the median itself
	//Even Numbers don't work on this kernal size, the third parameter above
	
	namedWindow("corrected Image",WINDOW_NORMAL);
	namedWindow("Damaged Image",WINDOW_NORMAL);
	namedWindow("Original Image",WINDOW_NORMAL);

	imshow("corrected Image",corrected);
	imshow("Damaged Image",badimg);
	imshow("Original Image",iIn);
	waitKey(0);
	return 0;
}