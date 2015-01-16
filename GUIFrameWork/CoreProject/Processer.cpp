#include "Processer.h"


Processer::Processer(void)
{
	vc = new cv::VideoCapture(0);
}


Processer::~Processer(void)
{
	if (vc != NULL)
	{
		vc->release();
		delete vc;
	}
}
