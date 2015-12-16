/*
 * SL_USBCamReader.h
 *
 *  Created on: 2012-4-10
 *      Author: elezoud
 */

#ifndef SL_USBCAMREADER_H_
#define SL_USBCAMREADER_H_
#include "SL_VideoReader.h"
#include "SL_Tictoc.h"

class USBCamReader:public VideoReader {
protected:
	cv::VideoCapture videoCap;
	TimeMeasurer _tm;
	uint32_t _timstamp;
public:
	int camid;
public:
	USBCamReader() :
		videoCap(), camid(-1){
			avi = false;
	}
	virtual ~USBCamReader();
	virtual void open();
	virtual void grabFrame();
	virtual void readCurFrameRGB(cv::Mat& img);
	virtual void readCurFrameGray(cv::Mat& grayimg);
	virtual void readCurFrame(cv::Mat& rgbImg, cv::Mat& grayImg);
	virtual uint32_t getTimeStamp();
};
#endif /* SL_USBCAMREADER_H_ */
