#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <curl/curl.h> //  apt-get install libcurl4-openssl-dev
#include "ipcamclass.h"

using namespace std;

IPCAMClass::IPCAMClass()
{
	this->ipcam_ip = "";
	this->ipcam_port ="";
	this->ipcam_user="";
	this->ipcam_pass="";
}

int IPCAMClass::setparametres(string ip, string port , string user, string pass)
{
	this->ipcam_ip = ip;
	this->ipcam_port = port ;
	this->ipcam_user = user;
	this->ipcam_pass = pass ;
	return 0;
}

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
       size_t written = fwrite(ptr, size, nmemb, stream);
       return written;
}



int IPCAMClass::getimage()
{
	string url = "";
    	CURL *image;
	FILE * fp;
        CURLcode res = CURLE_FAILED_INIT;

	if (this->ipcam_ip == "")
	{
		cout  << "ip non defini" << endl;
		return (-1);
	}
	if (this->ipcam_ip != "")
	{
		url += "http://";
		url += this->ipcam_ip; 
	}
        if (this->ipcam_port != "")
        {
                url += ":";
                url += this->ipcam_port;
        }
	url += "/snapshot.cgi?";
        if (this->ipcam_user != "")
        {
                url += "user=";
      	        url += this->ipcam_user;
        }
        if (this->ipcam_pass != "")
        {
                url += "&pwd=";
                url += this->ipcam_pass;
        }
	cout << "url : " << url << endl;

	image = curl_easy_init(); 
	if (image)
	{
		fp = fopen("/tmp/img.jpg","wb");
		curl_easy_setopt(image, CURLOPT_URL, url.c_str());
		curl_easy_setopt(image, CURLOPT_WRITEFUNCTION, write_data);
		curl_easy_setopt(image, CURLOPT_WRITEDATA, fp);
        	res = curl_easy_perform(image);
        	/* always cleanup */
        	curl_easy_cleanup(image);
		fclose (fp);
	}
        if ( res == CURLE_OK)
        {
		return 0;
	}
	else
	{
		return (-1);
	}
}


