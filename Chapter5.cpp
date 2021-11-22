#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

////////////////// Warp Images  ///////////////////////////////
float w = 250, h = 350;
Mat matrix, imgWarp;

int main() {

	string path = "Resources/card.jpg";
	Mat img = imread(path);

	// Gather pixels from location of the object using the Paint app .  Location 1) Top left 2) Top right 3) Bottom Left 4) Bottom Right
	//Point2f src[4] = { {244,183},{396, 180},{251,357},{414,347} };  // CARD 6 Number pixel 
	Point2f src[4] = { {435,371},{602,367},{448,568},{623,564} };  // CARD 2 Number pixel
	//Point2f src[4] = { {86,18},{230,20},{65,172},{222,169} };  // CARD J Number pixel
	Point2f dst[4] = { {0.0f,0.0f},{w, 0.0f},{0.0f,h},{w,h} };
	

	matrix = getPerspectiveTransform(src, dst);
	warpPerspective(img, imgWarp, matrix, Point(w, h));

	for (int i = 0; i < 4; i++)
	{
		circle(img, src[i], 10, Scalar(0, 69, 255), FILLED);
	}


	imshow("Image", img);
	imshow("Image Warp", imgWarp);

	waitKey(0);
}


