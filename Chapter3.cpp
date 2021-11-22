#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

////////////////// Resize and Crop Images  ///////////////////////////////

int main() {

	string path = "Resources/test2.jpg";
	Mat img = imread(path);
	Mat imgResize, imgCrop;

	//cout << img.size() << endl;  // above image size[1200 x 1800]

	//resize(img, imgResize, Size(600,900));
	resize(img, imgResize, Size(), 0.5, 0.5);     // Image Resize. Resize using the percentage 0.5, 0.5  50% resize

	Rect roi(300, 300, 400, 300);   //Crop the Image
	imgCrop = img(roi);             //Crop the Image       

	imshow("Image", img);
	imshow("Image Resize", imgResize);
	imshow("Image Crop", imgCrop);

	waitKey(0);
}
