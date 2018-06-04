#ifndef EMAIL_SEND_H
#define EMAIL_SEND_H

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include "quickmail.h"

namespace email{
	class Email{

		private:
 			std::string to_email_address;
  			std::string from_email_address;
  			std::string title;
  			quickmail mailobj;
  			int port;
  			std::string emailPwd;
  			std::string smtpserver;

		public : 
			Email(std::string to_email_address, std::string from_email_address,std::string title,std::string smtpserver,int port, std::string emailPwd);
			~Email();
			void quickmailsetup(std::string pathNameJpg, std::string body);
			void addToEmailaddress();
			void sendEmail();
	};
}

#endif