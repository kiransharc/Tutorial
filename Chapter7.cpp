0#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

////////////////// Shapes and Contour Detection  ///////////////////////////////


void getContours(Mat imgDil, Mat img) {

	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;

	findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	//drawContours(img, contours, -1, Scalar(255, 0, 255), 2);

	vector<vector<Point>> conPoly(contours.size());
	vector<Rect> boundRect(contours.size());

	for (int i = 0; i < contours.size(); i++)
	{
		int area = contourArea(contours[i]);
		cout << area << endl;

	
		string objectType;

		if (area > 1000)
		{
			
			float peri = arcLength(contours[i], true);
			approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);
			
			cout << conPoly[i].size() << endl;

			/////BOUNDING RECTANGEL ON THE OBJECT
			boundRect[i] = boundingRect(conPoly[i]);
			

			int objCor = (int)conPoly[i].size();

			if (objCor == 3) { objectType = "Tri"; }
			if (objCor == 4) { 
				
				float aspRatio = (float)boundRect[i].width / (float)boundRect[i].height;
				cout << "AspRatio :" << aspRatio << endl;
				if (aspRatio > 0.80 && aspRatio < 1.05)
				{
					objectType = "Square";
				}
				else
				{
					objectType = "Rect";
				}
			}


			if (objCor == 5) { objectType = "Poly"; }
			if (objCor > 5) { objectType = "Circle"; }

			drawContours(img, conPoly, i, Scalar(255, 0, 255), 2);
			rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 5);
			putText(img, objectType, { boundRect[i].x,boundRect[i].y - 5 }, FONT_HERSHEY_DUPLEX, 0.75, Scalar(0.69, 255), 2);

		}
	}

}


Mat imgGray, imgBlur, imgCanny, imgDil;

int main() {

	string path = "Resources/shapes.jpg";
	Mat img = imread(path);

	// Preprocessing
	cvtColor(img, imgGray, COLOR_BGR2GRAY);         // Function 1 : GRAY IMAGE   
	GaussianBlur(imgGray, imgBlur, Size(7, 7), 5, 0);  // Function 2 : BLUR IMAGE
	Canny(imgBlur, imgCanny, 10, 60);              // Function 3 : Edge Detector
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));  // Need to use Odd numbers only
	dilate(imgCanny, imgDil, kernel);   // Function 3.1 : Dilute the edges from Canny

	getContours(imgDil, img);

	// OUTPUT
	imshow("Image", img);
	//imshow("Image Gray", imgGray);
	//imshow("Image Blur", imgBlur);
	imshow("Image Canny", imgCanny);
	imshow("Image Dialation", imgDil);
	waitKey(0);
}