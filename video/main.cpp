#include <iostream>
#include <chrono>
#include <thread>
#include <string>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
using namespace cv;
using namespace std;
using namespace std::chrono;

static double getCurrTimeSec() {
	return (double)(system_clock::now().time_since_epoch().count()) * system_clock::period::num / system_clock::period::den;
}

int main()
{

	VideoCapture cap[7];
	//cap[0] = VideoCapture(6);
	//cap[1] = VideoCapture(3);
	//cap[2] = VideoCapture(4);
	//cap[3] = VideoCapture(1);
	//cap[4] = VideoCapture(5);
	//cap[5] = VideoCapture(0);
	//cap[6] = VideoCapture(2);
	for (int i = 0; i < 6; i++)
		cap[i] = VideoCapture(i);

	bool stop(false);
	Mat frame0;
	Mat frame1;
	Mat frame2;
	Mat frame3;
	Mat frame4;
	Mat frame5;
	Mat frame6;

	namedWindow("cam0", CV_WINDOW_AUTOSIZE);
	namedWindow("cam1", CV_WINDOW_AUTOSIZE);
	namedWindow("cam2", CV_WINDOW_AUTOSIZE);
	namedWindow("cam3", CV_WINDOW_AUTOSIZE);
	namedWindow("cam4", CV_WINDOW_AUTOSIZE);
	namedWindow("cam5", CV_WINDOW_AUTOSIZE);
//	namedWindow("cam6", CV_WINDOW_AUTOSIZE);
	for (int i = 0; i < 6; i++) {
		if(!cap[i].isOpened()){
			cout << "cam" << i << " error"<< endl;
			exit(-1);
		}
		cap[i].set(CV_CAP_PROP_FOURCC, CV_FOURCC('M', 'J', 'P', 'G'));
		cap[i].set(CV_CAP_PROP_FRAME_WIDTH, 1280);//宽度 
		cap[i].set(CV_CAP_PROP_FRAME_HEIGHT, 720);//高度
		cap[i].set(CV_CAP_PROP_BRIGHTNESS, 0);//亮度 1
		cap[i].set(CV_CAP_PROP_CONTRAST, 32);//对比度 40p
		cap[i].set(CV_CAP_PROP_SATURATION, 65);//饱和度 50
		cap[i].set(CV_CAP_PROP_HUE, 0);//色调 50
		cap[i].set(CV_CAP_PROP_EXPOSURE, -5);//曝光 50
	}
	int count = 0;
	if (cap[0].read(frame0) && cap[1].read(frame1) && cap[2].read(frame2) && cap[3].read(frame3) && cap[4].read(frame4) && cap[5].read(frame5))// && cap[6].read(frame6))
		;
	while (!stop)
	{
		double start = getCurrTimeSec();
		if (cap[0].read(frame0) && cap[1].read(frame1) && cap[2].read(frame2)&& cap[3].read(frame3)&& cap[4].read(frame4)&& cap[5].read(frame5))//&& cap[6].read(frame6))
		{
			imshow("cam0", frame0);
			imshow("cam1", frame1);
			imshow("cam2", frame2);
			imshow("cam3", frame3);
			imshow("cam4", frame4);
			imshow("cam5", frame5);
//			imshow("cam6", frame6);
			count++;	
			if (waitKey(1) == 27)//按ESC键
			{
				imwrite("cam0/000000.png", frame0);
				imwrite("cam1/000000.png", frame4);
				imwrite("cam2/000000.png", frame5);
				imwrite("cam3/000000.png", frame3);
				imwrite("cam4/000000.png", frame2);
				imwrite("cam5/000000.png", frame1);

				stop = true;
				std::cout << "程序结束！" << endl;
				std::cout << "*** ***" << endl;
				count++;
			}

		}
		double end = getCurrTimeSec();
		std::cout << "fps: " << 1.0f/(end - start) << endl;
	}
	return 0;
}
