#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

////////////////// Importing Images  ///////////////////////////////

Mat imgOriginal, imgGray, imgBlur, imgCanny, imgThre, imgDil, imgErode;

Mat PreProcessing(Mat img)
{
	cvtColor(img, imgGray, COLOR_BGR2GRAY);         // Function 1 : GRAY IMAGE   
	GaussianBlur(imgGray, imgBlur, Size(7, 7), 5, 0);  // Function 2 : BLUR IMAGE
	Canny(imgBlur, imgCanny, 10, 75);              // Function 3 : Edge Detector

	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));  // Need to use Odd numbers only
	dilate(imgCanny, imgDil, kernel);   // Function 3.1 : Dilute the edges from Canny
	//erode(imgDil, imgErode, kernel);    // Function 3.2 :Erode the edges from Canny
	
	return imgDil;
}

void main() {

	string path = "Resources/scanimage.jpeg";
	 imgOriginal = imread(path);
	 resize(imgOriginal, imgOriginal, Size(), 0.5, 0.5);


	 //Preprocessing

	imgThre = PreProcessing(imgOriginal);

	 //Get Contours - Biggest

	getContours(imgThre);
	 //Warp


	imshow("Image", imgOriginal);
	imshow("Image Dilation", imgThre);


	waitKey(0);
}
