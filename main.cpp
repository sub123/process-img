#include <iostream>
#include <string>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
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
	imshow("original",img);
	Mat gray;
	cvtColor(img,gray,CV_BGR2GRAY);
	imshow("grayscale",gray);
	//imwrite("result.jpg",img);
	waitKey(0);
	return 0;
}