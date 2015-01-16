#pragma once
#include <cv.h>
#include <highgui.h>
class Histograms
{
public:
	Histograms(void);
	~Histograms(void);

	std::vector<float> ComputeHistogram(cv::Mat & original)
	{
		cv::Mat gray;
		cv::cvtColor(original,gray,CV_BGR2GRAY);
		std::vector<float> hist;
		hist.resize(256);
		for(int i=0;i<gray.cols;i++)
			for(int j=0;j<gray.rows;j++)
			{
				uchar val = gray.at<uchar>(cv::Point(i,j));
				hist[val]++;
			}
		double minval,maxval;
		cv::minMaxLoc(hist,&minval, &maxval);
		for(int i=0;i<hist.size();i++)
			hist[i]=hist[i]/(float)maxval;
		return hist;
		
	}
	cv::Mat ImageSegmentation(cv::Mat & original)
	{
		cv::Mat segementedimage = original.clone();
		cv::Mat gray;
		cv::cvtColor(original, gray,CV_BGR2GRAY);

		std::vector<float> hist = ComputeHistogram(original);
		std::vector<cv::Point2f> contour;
		contour.resize(hist.size());

		for(int i=0;i<hist.size();i++)
		{
			contour[i].x = i;
			contour[i].y = hist[i]*255;
		}
		cv::approxPolyDP(contour,contour,contour.size()*0.05,false);

		for(int t = 1; t<contour.size()-1;t++)
		{
			if (contour[t].y > contour[t-1].y && contour[t].y > contour[t+1].y)
			{
				GetRegions(gray,segementedimage,contour[t-1].x,contour[t+1].x);
			}
		}
		return segementedimage;
	}
	void GetRegions(cv::Mat & gray, cv::Mat & segmentedimage, int minX, int maxX)
	{
		cv::Scalar color = cv::Scalar(rand()&255,rand()&255,rand()&255);
		for (int i = 0; i < gray.cols; i++)
		{
			for (int j = 0; j < gray.rows; j++)
			{
				uchar val = gray.at<uchar>(cv::Point(i,j));
				if (val <= maxX && val>=minX)
				{
					segmentedimage.at<cv::Vec<uchar,3>>(cv::Point(i,j)).val[0] = color.val[0]; 
					segmentedimage.at<cv::Vec<uchar,3>>(cv::Point(i,j)).val[1] = color.val[1]; 
					segmentedimage.at<cv::Vec<uchar,3>>(cv::Point(i,j)).val[2] = color.val[2]; 
				}
			}
		}
	}

	cv::Mat DisplayHistogram(std::vector<float> & hist)
	{
		cv::Mat histogram(500,256,CV_8UC1);
		histogram = cv::Scalar(255);

		for(int i=0;i<hist.size();i++)
		{
			cv::line(histogram,cv::Point(i,500),cv::Point(i,500 - 500*hist[i]),cv::Scalar(0)); 
		}
		return histogram;

		
	}

};

