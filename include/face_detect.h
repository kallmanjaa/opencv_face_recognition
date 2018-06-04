#ifndef FACE_DETECT_H
#define FACE_DETECT_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/face.hpp>
#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <sstream>


namespace opencv{
	class opencvFaceDetect{
		public :
			opencvFaceDetect(int device_id , std::string path ,std::string csv_file);
			~opencvFaceDetect();
			int camOpen();
			void loadXmlAndCsvFile();
			void detectFace();
			void closeCam();

			cv::Mat getImage();
			void read_csv(std::string filename);
		private:
			cv::VideoCapture cam;
			int deviceID;
			std::string xml_haarcascade_path;
			cv::Mat img;
			cv::CascadeClassifier face_cascade;

			bool flag ;
			cv::Mat actual_face;
			cv::Ptr<cv::face::FaceRecognizer> model;
			std::vector<cv::Mat> stored_images;
			std::vector<int> labels;

			int width;
			int height;
			std::string csv_file;
	};

}


#endif