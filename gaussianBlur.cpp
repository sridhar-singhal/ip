/*Take Home messages:
1. A higher sigma gives high weights to surrounding pixels as well as centre pixel. Low sigma gives 
it only to central pixel. What this means is that if my sigma is too high for the kernal size, then 
I am making nothing but an approximate square filter(equal precedance 111\n111\n111). That is why we
could see see lines in between as seen in the video given 
in course(https://classroom.udacity.com/courses/ud810/lessons/3417359075/concepts/34235689650923).
2. A larger kernal takes data from a larger area and in my view is a better method. A higher sigma 
was making ghost lines. That were not visible in a larger kernal.
Furthur more, you CAN APPLY THE BLUR MULTIPLE TIMES with the same kernal to make it look even better.
What this would is take even lesser contributions from an even larger area (as the pixels would be a 
contribution from many other pixels besides). So applying a gaussian even twice is equivalent to using a
very very large kernel though the distribution in it may not neccessarily be a gaussian.
3. Hot to use a trackbar:
*/

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream> 
using namespace cv;
using namespace std;
int  n =0,sigma =3,nd =3,sigmad = 1;
Mat unprocessed = imread("hay.jpg",1);
Mat processed(unprocessed.rows,unprocessed.cols,CV_8UC3,Scalar(0,0,0));
void kernelCalc(int n,void* a)	//Can only be a void, defined in library for trackbar
{
	nd = 2*n+3;
	
	GaussianBlur(unprocessed,processed,Size(nd,nd),sigmad,sigmad);
	cout<<"\nsigma: "<<sigmad<<"\tn: "<<nd;
	imshow("param",processed);
	imshow("Original Image",unprocessed);

}
 void sigmaCalc(int sigma,void* a)
 {
 	sigmad = sigma;
 	cout<<"\nsigma: "<<sigmad<<"\tn: "<<nd;
 	GaussianBlur(unprocessed,processed,Size(nd,nd),sigmad,sigmad);
 	imshow("param",processed);
 	imshow("Original",unprocessed);
 }
int main()
{	//int n=0;
	// Mat unprocessed;//,processed;
	//unprocessed = imread("hay.jpg",1);
	
	//processed = unprocessed;	
	
	cout<<"Aya?";
	namedWindow("param",1);
	 createTrackbar("Kernel(2*n+3)","param",&n,8,kernelCalc);
	 createTrackbar("Sigma","param",&sigma,20,sigmaCalc);
	  
	 kernelCalc(n,NULL);
	 sigmaCalc(0,NULL);
	//createTrackbar("Kernel(2*n+3)","param",&n,8,0,NULL);			//These are not called all the time, only at the time of exit 
	//createTrackbar("Sigma","param",&sigma,20,0,NULL);				//That is when the callback is done. 
	// GaussianBlur(processed,unprocessed,Size(2*n+3,2*n+3),sigma,sigma);//So if you want to update real time, make function and call
	// imshow("param",processed);									//it in the callback function.
	// imshow("Original Image",unprocessed);						//A null just updates the values if  a callback is not present tested in 
	 																//program callback
	
	
	waitKey(0);
	return 0;
}
