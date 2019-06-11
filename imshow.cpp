/*
Follow the link Below for image read and write.
https://docs.opencv.org/3.1.0/d4/da8/group__imgcodecs.html#gga61d9b0126a3e57d9277ac48327799c80a64063c4e6a917237bd2daef7aa23dc01
For Imread, various enums are defined, 
0 for opening in 8 bit greyscale
1 for opening in 3 channel color image
-1 for opening as it is defined. 
Others are quite useless (seems to be) and work in powers of 2
like 2, 4, 8, 16 ,17 ,32, 33 ,64 ,65
In the given program a 16 bit image was tried but it did not open its bitmap image so was useless.
*/

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
int main()
{
	Mat a;
	
	a = imread("DeltaE_16bit_gamma1.0.tif",2);	
	namedWindow("2",WINDOW_NORMAL);
	imshow("2",a);

	waitKey(0);
	return 0;
}