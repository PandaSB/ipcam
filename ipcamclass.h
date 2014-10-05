#ifndef IPCAM_CLASS_H
#define IPCAM_CLASS_H

#include <string>
using namespace std;
/* IPCAM Class
 */
class IPCAMClass
{
public:
	IPCAMClass();  // create a GPIO object that controls GPIO4 (default
	int setparametres(string ip, string port , string user, string pass);
	int getimage();
private:
	string ipcam_ip ; 
	string ipcam_port ;
	string ipcam_user;
	string ipcam_pass;
};
#endif
