#include "face_detect.h"
#include "email_send.h"
#include <signal.h>
#include <unistd.h>

volatile sig_atomic_t flag = 0;

void sig_handler(int sig){ // can be called asynchronously
  flag = 1; // set flag
}

void * myfunc(void * arg){

	pthread_setcancelstate(PTHREAD_CANCEL_ENABLE,NULL); 

	while(1) {
		((opencv::opencvFaceDetect *) arg)->detectFace();
	}
	return NULL;
}

int main(){

	std::string filename_to_send = "Name of the file";
	std::string to_mailAddress = "second_person_emailaadress";
	std::string from_mailAddress = "yourmailaddress";
	std::string Subject = "test_mail";
	std::string smptp_server = "smtp.gmail.com";
	int port = 465;
	std::string email_pwd = "pwd";

	std::string Body = "Please see the face info in the attachment \n";


	email::Email *objemail = new  email::Email(to_mailAddress,from_mailAddress,Subject,smptp_server,port,email_pwd);
	objemail->quickmailsetup(filename_to_send,Body);
	objemail->addToEmailaddress();
	
	signal(SIGINT, sig_handler); 
	int deviceId=0;
	std::string path = "/home/bentur/project/opencv_camera/haarcascade_frontalcatface_alt.xml";
	std::string csv_file = "manjoo.csv";
	pthread_t thread;


	opencv::opencvFaceDetect * camera = new opencv::opencvFaceDetect(deviceId,path,csv_file);

	if(camera->camOpen() == -1){
		return -1;
	}

	camera->loadXmlAndCsvFile();

	pthread_create(&thread,NULL, myfunc, camera);

	struct timespec sleep_time = {1, 40000000000L};

	int count=0;

	while(1){

		cv::Mat img = camera->getImage();
		if(img.empty() == false){
			imwrite( filename_to_send, img );
			objemail->sendEmail();
		}

		if(flag){
			std::cout<<"key CTRL-C pressed -- terminating"<<std::endl;
			 pthread_cancel(thread);
			 pthread_join(thread, NULL);
			break;
		}
 		nanosleep(&sleep_time, NULL);	
 	}

 	camera->closeCam();

 	delete objemail;
	delete camera;

}