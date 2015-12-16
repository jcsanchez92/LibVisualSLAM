/*
 * SL_AVIReader.cpp
 *
 *  Created on: 2012-4-10
 *      Author: elezoud
 */
#include "SL_AVIReader.h"
#include "SL_error.h"
void AVIReader::open() {
	if (!videoCap.open(filePath.c_str()))
		repErr("Cannot open %s\n", filePath.c_str());
	_w = (int) videoCap.get(CV_CAP_PROP_FRAME_WIDTH);
	_h = (int) videoCap.get(CV_CAP_PROP_FRAME_HEIGHT);

	assert(_w > 0 && _h > 0);
	_timestamp = 0;
}

void AVIReader::grabFrame() {
	assert(videoCap.isOpened());
	videoCap.grab();
}
//skip: setting skip frame numbers can only be used with video
void AVIReader::skip(int nSkippedFrame) {
	videoCap.set(CV_CAP_PROP_POS_FRAMES, nSkippedFrame);
}
void AVIReader::grabReadFrame(int Frame, cv::Mat& img) {
	skip(Frame);
	grabFrame();
	readCurFrameRGB(img);
}
void AVIReader::readCurFrameRGB(cv::Mat& img) {
	assert(videoCap.isOpened());
	videoCap.retrieve(img);
}
void AVIReader::readCurFrameGray(cv::Mat& grayImg) {
	assert(videoCap.isOpened());
    cv::Mat rawFrame;
	videoCap.retrieve(rawFrame);
	if(rawFrame.type() == CV_8UC1)
		rawFrame.copyTo(grayImg);
	else
		cv::cvtColor(rawFrame, grayImg, CV_RGB2GRAY);
}
void AVIReader::readCurFrame(cv::Mat& rgbImg,
		cv::Mat& grayImg) {
	assert(videoCap.isOpened());
	cv::Mat rawFrame;
	videoCap.retrieve(rawFrame);

	cv::cvtColor(rawFrame, rgbImg, CV_BGR2RGB);

	cv::cvtColor(rawFrame, grayImg, CV_RGB2GRAY);
}
int AVIReader::getTotalFrame() {
	return (int)videoCap.get(CV_CAP_PROP_FRAME_COUNT);
}

void AVIReader::releaseCamera(){
	videoCap.release();
}

uint32_t AVIReader::getTimeStamp(){
	return _timestamp++;
}
