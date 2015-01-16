#pragma once

#include <cv.h>
#include <highgui.h>
class Contours
{
public:
	Contours(void);
	~Contours(void);
	cv::Mat extractContours(cv::Mat & original)
	{
		cv::Mat gray;
		cv::cvtColor(original, gray, CV_BGR2GRAY);
		cv::Scalar meanvalue, stdvalue;
		cv::meanStdDev(gray,meanvalue, stdvalue); 

		double t1 = meanvalue.val[0]/3.0;
		double t2 = meanvalue.val[0];

		cv::Canny(gray,gray,t1,t2);

		cv::Mat colored;
		cv::cvtColor(gray, colored, CV_GRAY2BGR);
		cv::Mat cloneofgray = gray.clone();
		std::vector<std::vector<cv::Point>> contours;

		cv::findContours(gray, contours, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);
		cv::Mat mask = gray.clone();
		for(int i=0;i<contours.size();i++)
		{
			cv::Rect r = cv::boundingRect(contours[i]);
			if (r.width < 10 || r.height < 10)
				continue;
			cv::RotatedRect rr = cv::fitEllipse(contours[i]);
			//mask = cv::Scalar(0);
			cv::Scalar color = cv::Scalar(rand()&255,rand()&255,rand()&255);
			cv::ellipse(colored,rr,color,1);
			double area = cv::contourArea(contours[i]);
			char str[256];
			sprintf(str,"%3.2lf",area);
			cv::putText(colored,str,rr.center,CV_FONT_HERSHEY_PLAIN,1,color,2);
			/*mask = cv::Scalar(0);
			cv::drawContours(mask,contours,i,
				cv::Scalar(255),-1);
			cv::namedWindow("mask",0);
			cv::imshow("mask",mask);
			cv::waitKey(40);*/
		}
		return colored;
	};

	cv::Mat flood(cv::Mat &original)
	{
		cv::Mat gray,mask;
		cv::cvtColor(original,gray,CV_BGR2GRAY);
		cv::floodFill(gray,cv::Point(154,190),cv::Scalar(128),0,cv::Scalar(140), cv::Scalar(140));

		cv::Mat colored;
		cv::cvtColor(gray,colored,CV_GRAY2BGR);
		return colored;
	}

	cv::Mat approximateContours(cv::Mat & original)
	{
		cv::Mat gray;
		cv::cvtColor(original, gray, CV_BGR2GRAY);
		cv::Scalar meanvalue, stdvalue;
		cv::meanStdDev(gray,meanvalue, stdvalue); 

		double t1 = meanvalue.val[0]/3.0;
		double t2 = meanvalue.val[0];

		cv::Canny(gray,gray,t1,t2);

		cv::Mat colored;
		cv::cvtColor(gray, colored, CV_GRAY2BGR);
		//cv::Mat cloneofgray = gray.clone();
		std::vector<std::vector<cv::Point>> contours;

		cv::findContours(gray, contours, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);

		for(int i=0;i<contours.size();i++)
		{
			if (contours[i].size()<=4)
				continue;
			cv::approxPolyDP(contours[i],contours[i],contours[i].size()*0.1,false);
			cv::drawContours(colored,contours,i,cv::Scalar(rand()&255,rand()&255,rand()&255));
		}
		return colored;
	}

};

