#include <iostream>
#include <string>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>
using namespace std;
using namespace cv;
int main()
{
	string path;
	cout<<"Image path:";
	cin>>path;
	Mat img=imread(path,CV_LOAD_IMAGE_COLOR);
	if(!img.data)
	{
		cout<<"Could not load image.";
		return -1;
	}
	//namedWindow("window",CV_WINDOW_AUTOSIZE);
	imshow("Original",img);
	Mat gray;
	cvtColor(img,gray,CV_BGR2GRAY);
	imshow("Grayscale",gray);
	//imwrite("result.jpg",img);
	CascadeClassifier face_cascade;
	face_cascade.load("data/haarcascades/haarcascade_frontalface_default.xml");
	vector <Rect> faces;
	face_cascade.detectMultiScale(img,faces,1.1,2,0|CV_HAAR_SCALE_IMAGE,Size(30,30));
	for(int i=0;i<=faces.size();i++)
	{
		Point center( faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5 );
		ellipse( img, center, Size( faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar( 255, 0, 255 ), 4, 8, 0 );
	}
	imshow("Detected Faces",img);
	waitKey(0);
	return 0;
}