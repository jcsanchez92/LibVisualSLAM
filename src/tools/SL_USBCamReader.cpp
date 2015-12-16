/*
 * SL_USBCamReader.cpp
 *
 *  Created on: 2012-4-10
 *      Author: elezoud
 */

#include "SL_USBCamReader.h"
#include "SL_error.h"

void USBCamReader::open() {
	videoCap.open(camid);
	videoCap.set(CV_CAP_PROP_FRAME_WIDTH, 640);
	videoCap.set(CV_CAP_PROP_FRAME_HEIGHT, 480);
	videoCap.set(CV_CAP_PROP_FPS, 30);
	if (!videoCap.isOpened()) {
		repErr("ERROR: Fail to detect the USB camera \n");
	}
	_w = (int)videoCap.get(CV_CAP_PROP_FRAME_WIDTH);
	_h = (int)videoCap.get(CV_CAP_PROP_FRAME_HEIGHT);
	if (_w <=0 || _h <= 0)
		repErr("ERROR: Fail to open the USB camera \n");

	_tm.tic();
}
USBCamReader::~USBCamReader(){
	if(videoCap.isOpened())
		videoCap.release();
}

void USBCamReader::grabFrame() {
	assert(videoCap.isOpened());
	videoCap.grab();
}
void USBCamReader::readCurFrameRGB(cv::Mat& img) {
	assert(videoCap.isOpened());
	videoCap.read(img);
}
void USBCamReader::readCurFrameGray(cv::Mat& grayimg) {
	assert(videoCap.isOpened());
	cv::Mat rawFrame;
	videoCap.retrieve(rawFrame);
	cv::cvtColor(rawFrame, grayimg, CV_RGB2GRAY);
}
void USBCamReader::readCurFrame(cv::Mat& rgbImg,
		cv::Mat& grayImg) {
	assert(videoCap.isOpened());
	cv::Mat rawFrame;
	cv::cvtColor(rawFrame, rgbImg, CV_BGR2RGB);
	cv::cvtColor(rawFrame, grayImg, CV_RGB2GRAY);
}
uint32_t USBCamReader::getTimeStamp(){
	double ts = _tm.get_pass_time();
	return (uint32_t)(ts+0.5);
}
