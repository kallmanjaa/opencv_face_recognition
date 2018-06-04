
#include "face_detect.h"

namespace opencv{

		opencvFaceDetect::opencvFaceDetect(int device_id , std::string path , std::string csv_file){

			this->deviceID = device_id;
			this->xml_haarcascade_path = path;
			this->csv_file = csv_file;
			this->flag = false ;
			this->width =0 ;
			this->height =0 ;
		}

		opencvFaceDetect::~opencvFaceDetect(){

		}

		int opencvFaceDetect::camOpen(){
			this->cam.open(this->deviceID);
			if(this->cam.isOpened() ==0){
				std::cout<<"cam open error"<<std::endl;
				return -1;
			}
			return 0;
		}

		void opencvFaceDetect::read_csv(std::string filename) {
    		std::ifstream file(filename.c_str(), std::ifstream::in);
    		
    		if (!file) {
    			std::cerr<<"file read error"<<std::endl;
				return ;
    		}

    		std::string line, path, classlabel;
    		while (!file.eof()) {

    			getline(file,line);

    			 std::size_t pos = line.find(";");
    			 if (pos!=std::string::npos){
    				classlabel = line.substr(pos+1);
    			 	path= line.substr(0,pos);
            		this->labels.push_back(atoi(classlabel.c_str()));
            		cv::Mat m = cv::imread(path, 0);
					if ( m.empty() )
					{
     				std::cerr << path << " could not be read!" << std::endl;
     				return;
					}

					this->stored_images.push_back(m);
    			 }
    		}
		}
		
		void  opencvFaceDetect::loadXmlAndCsvFile(){
			this->face_cascade.load(this->xml_haarcascade_path);
			read_csv(this->csv_file);
			this->height = this->stored_images[0].rows;
			this->width = this->stored_images[0].cols;
    		this->stored_images.pop_back();
    		this->labels.pop_back();
		}

		cv::Mat opencvFaceDetect::getImage(){
			if(flag == true){
				flag = false;
				return this->actual_face;
			}	
			cv::Mat empty;
			return empty;
		}
		
		void opencvFaceDetect::detectFace(){

			this->model = cv::face::LBPHFaceRecognizer::create();
    		model->train(this->stored_images, this->labels);

			this->cam.read(this->img);
		 	std::vector<cv::Rect> faces;
 		 	cv::Mat frame_gray;
 		 	cv::Mat face_resized;
  		 	cv::cvtColor(this->img, frame_gray, cv::COLOR_BGR2GRAY);  // Convert to gray scale
  		 	equalizeHist(frame_gray, frame_gray);   	// Equalize histogram
  		 	int predictedLabel;
    		double confidence;

  			this->face_cascade.detectMultiScale(frame_gray, faces, 1.1, 3,0|cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30));

  			// Iterate over all of the faces
  				for( size_t i = 0; i < faces.size(); i++ ) {
    				cv::Point center(faces[i].x + faces[i].width/2, faces[i].y + faces[i].height/2);
    				cv::resize(frame_gray, face_resized, cv::Size(this->width, this->height));
    				model->predict(face_resized, predictedLabel, confidence);
    				cv::ellipse(this->img, center, cv::Size(faces[i].width/2, faces[i].height/2),0, 0, 360, cv::Scalar( 255, 0, 255 ), 4, 8, 0 );
    				std::cout<<confidence<<std::endl;
    				if(confidence < 80){  //adjust to confifence value to whatever you like
    					std::cout<<confidence<<std::endl;
    					this->actual_face = this->img;
    					this->flag = true;
    				}
  				}

  				cv::imshow("FaceDetect", this->img);  // Display frame
  				cv::waitKey(30);   // Pause key
		}

		void opencvFaceDetect::closeCam(){
			this->cam.release();
		}

}