#include "email_send.h"

namespace email{

	Email::Email(std::string to_email_address, std::string from_email_address,std::string title,std::string smtpserver,int port, std::string emailPwd){

    this->title = title;
    this->to_email_address = to_email_address;
    this->from_email_address=from_email_address;
    this->port = port;
    this->emailPwd = emailPwd;
    this->smtpserver = smtpserver;
	}

  void Email::quickmailsetup(std::string pathNameJpg, std::string body){

    quickmail_initialize();
    this->mailobj = quickmail_create(from_email_address.c_str(), title.c_str());
    quickmail_add_header(this->mailobj, "Importance: Low");
    quickmail_add_header(this->mailobj, "X-Priority: 5");
    quickmail_add_header(this->mailobj, "X-MSMail-Priority: High");
    quickmail_set_body(this->mailobj, body.c_str());
    quickmail_add_attachment_file(this->mailobj, pathNameJpg.c_str(), NULL);
  }
		
	Email::~Email(){
     quickmail_destroy(this->mailobj);
	}

  void Email::addToEmailaddress(){

      quickmail_add_to(this->mailobj, this->to_email_address.c_str());

  }


  void Email::sendEmail(){
    quickmail_send_secure(this->mailobj, this->smtpserver.c_str(), this->port, this->from_email_address.c_str(), this->emailPwd.c_str());
  }

  }