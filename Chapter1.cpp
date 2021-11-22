#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

////////////////// Importing Images  ///////////////////////////////
//
//void main() {
//
//	string path = "Resources/test.png";
//	Mat img = imread(path);
//
//	imshow("Image", img);
//	waitKey(0);
//}

////////////////// Importing Videos  ///////////////////////////////

//void main() {
//
//	string path = "Resources/testvideo.mp4";
//	VideoCapture cap(path);
//	Mat img;
//
//	while (true) {
//
//		cap.read(img);
//		imshow("Image", img);
//		waitKey(16);
//	}
//}


////////////////// WebCam  ///////////////////////////////

void main() {

	
	VideoCapture cap(0);
	Mat img;

	while (true) {

		cap.read(img);
		imshow("Image", img);
		waitKey(1);
	}
}