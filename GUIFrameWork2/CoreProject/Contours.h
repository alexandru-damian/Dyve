#pragma once

#include<cv.h>
#include<highgui.h>

#define MIN_SIZE 10

class Contours
{
public:
	Contours();
	~Contours();

	cv::Mat computeEdges(cv::Mat & original)
	{
		cv::Mat gray;
		cv::cvtColor(original, gray, CV_BGR2GRAY);
		cv::Scalar meanvalue, stdvalue;
		cv::meanStdDev(gray, meanvalue, stdvalue);
		double t1 = meanvalue.val[0] / 3.0;
		double t2 = meanvalue.val[0];
		cv::Canny(gray, gray, t1, t2);
		cv::namedWindow("canny", 0);
		cv::imshow("canny", gray);
		cv::waitKey();
		cv::Mat colored;
		cv::cvtColor(gray, colored, CV_GRAY2BGR);

		return colored;
	}

	cv::Mat computeContours(cv::Mat & original)
	{
		cv::Mat gray;
		cv::cvtColor(original, gray, CV_BGR2GRAY);
		cv::Scalar meanvalue, stdvalue;
		cv::meanStdDev(gray, meanvalue, stdvalue);
		double t1 = meanvalue.val[0] / 3.0;
		double t2 = meanvalue.val[0];
		cv::Canny(gray, gray, t1, t2);
		
		std::vector<std::vector <cv::Point>> contours;
		cv::findContours(gray, contours, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);
		cv::Mat mask(gray.rows, gray.cols, gray.type(), cv::Scalar(0));

		cv::Mat colored = original.clone();
		colored = cv::Scalar(0, 0, 0);

		for (int i = 0; i < contours.size(); i++)
		{
			cv::Rect r = cv::boundingRect(contours[i]);
			if (r.width < MIN_SIZE || r.height < MIN_SIZE)
			{
				continue;
			}

			cv::Scalar color = cv::Scalar(rand() & 255, rand() & 255, rand() & 255);
			/*cv::RotatedRect rr = cv::fitEllipse(contours[i]);
			if (rr.size.width > gray.cols || rr.size.height >gray.rows )
			{
				continue;
			}
			cv::ellipse(colored, rr, color, 1);
			double area = cv::contourArea(contours[i]);
			char text[256];
			sprintf(text, "%3.2lf", area);
			cv::putText(colored, text, rr.center, CV_FONT_HERSHEY_PLAIN, 1, color, 2);*/
			/*mask = cv::Scalar(0);
			cv::drawContours(mask, contours, i, color, -1);
			cv::namedWindow("mask", 0);
			cv::imshow("mask", mask);
			cv::waitKey();*/


			cv::drawContours(colored, contours, i, cv::Scalar(rand() & 255, rand() & 255, rand() & 255),2);
		}
		return colored;
	}

	cv::Mat approximateContours(cv::Mat & original)
	{
		cv::Mat gray;
		cv::Mat colored = original.clone();
		cv::cvtColor(original, gray, CV_BGR2GRAY);
		cv::Scalar meanvalue, stdvalue;
		cv::meanStdDev(gray, meanvalue, stdvalue);
		double t1 = meanvalue.val[0] / 3.0;
		double t2 = meanvalue.val[0];
		cv::Canny(gray, gray, t1, t2);

		std::vector<std::vector <cv::Point>> contours;
		cv::findContours(gray, contours, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);

		for (int i = 0; i < contours.size(); i++)
		{
			if (contours[i].size() <= 4)
				continue;

			cv::approxPolyDP(contours[i], contours[i], contours[i].size() * 0.2, false);
			cv::drawContours(colored, contours, i, cv::Scalar(rand() & 255, rand() & 255, rand() & 255));
		}

		return colored;
	}

};

