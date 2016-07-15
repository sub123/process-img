#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>
using namespace std;
using namespace cv;
void save(Mat img)
{
	cout<<"Path to save:";
	string dest;
	cin>>dest;
	imwrite(dest,img);
	waitKey(0);
}
void greyscale(Mat img)
{
	imshow("Original",img);
	Mat gray;
	cvtColor(img,gray,CV_BGR2GRAY);
	imshow("Grayscale",gray);
	cout<<"Save image?(0/1):";
	int schoice;
	cin>>schoice;
	if(schoice==1)
	{
		save(gray);
	}
	waitKey(0);
}
Mat greyscale_video(Mat img)
{
	Mat grey;
	cvtColor(img,grey,CV_BGR2GRAY);
	return grey;
}
void face_detect(Mat img)
{
	imshow("Original",img);
	Mat mod=img;
	CascadeClassifier face_cascade;
	face_cascade.load("data/haarcascades/haarcascade_frontalface_default.xml");
	vector <Rect> faces;
	face_cascade.detectMultiScale(mod,faces,1.1,2,0|CV_HAAR_SCALE_IMAGE,Size(30,30));
	for(int i=0;i<=faces.size();i++)
	{
		Point center( faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5 );
		ellipse( mod, center, Size( faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar( 255, 0, 255 ), 4, 8, 0 );
	}
	imshow("Detected Faces",mod);
	cout<<"Save image?(0/1):";
	int schoice;
	cin>>schoice;
	if(schoice==1)
	{
		save(mod);
	}
	waitKey(0);
}
Mat face_detect_video(Mat img)
{
	Mat mod=img;
	CascadeClassifier face_cascade;
	face_cascade.load("data/haarcascades/haarcascade_frontalface_default.xml");
	vector <Rect> faces;
	face_cascade.detectMultiScale(mod,faces,1.1,2,0|CV_HAAR_SCALE_IMAGE,Size(30,30));
	for(int i=0;i<=faces.size();i++)
	{
		Point center( faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5 );
		ellipse( mod, center, Size( faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar( 255, 0, 255 ), 4, 8, 0 );
	}
	return mod;
}
void cam()
{
	cout<<"1.Normal view"<<endl<<"2.Greyscale view"<<endl<<"3.Detect faces"<<endl<<"Enter choice:";
	int choice;
	cin>>choice;
	if(choice !=1 && choice !=2 && choice !=3)
	{
		cout<<"Invalid choice, switching to normal view."<<endl;
		choice=1;
	}
	VideoCapture cap(0);
	if(!cap.isOpened())
	{
		cout<<"Could not open camera."<<endl;
		return;
	}
	while(1)
	{
		Mat frame;
		cap>>frame;
		if(choice==2)
		{
			frame=greyscale_video(frame);
		}
		else if(choice==3)
		{
			frame=face_detect_video(frame);
		}
		imshow("video",frame);
		if(waitKey(30)=='c')
		{
			break;
		}
	}
}
int main()
{
	cout<<"1.Image"<<endl<<"2.Video"<<endl<<"Enter choice:";
	int schoice;
	cin>>schoice;
	if(schoice==2)
	{
		cam();
	}
	else if(schoice ==1)
	{
		cout<<"1.Convert to greyscale"<<endl<<"2.Detect faces"<<endl<<"Enter choice:";
		int choice;
		cin>>choice;
		if(choice==1 || choice==2)
		{
			string path;
			cout<<"Image path:";
			cin>>path;
			Mat img=imread(path,CV_LOAD_IMAGE_COLOR);
			if(!img.data)
			{
				cout<<"Could not load image."<<endl;
				return -1;
			}
			if(choice==1)
			{
				greyscale(img);
			}
			else if(choice==2)
			{
				face_detect(img);
			}
		}
		else
		{
			cout<<"Invalid choice."<<endl;
			return -1;
		}
	}
	else
	{
		cout<<"Invalid choice"<<endl;
		return -1;
	}
	return 0;
}