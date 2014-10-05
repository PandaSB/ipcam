#include <iostream>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include "gpioclass.h"
#include "ipcamclass.h"

using namespace std ;


int main ()
{
	string inputstate;
	string laststate = "0";

        GPIOClass* gpio4 = new GPIOClass("4");
	GPIOClass* gpio23 = new GPIOClass("23");

	IPCAMClass* ipcam = new IPCAMClass();

	cout << "Programme de test" << endl;

	gpio23->export_gpio(); //export GPIO4
    	gpio4->export_gpio(); //export GPIO17

	cout << " GPIO pins exported" << endl;

    	gpio4->setdir_gpio("in"); //GPIO4 set to output
	gpio23->setdir_gpio("out"); // GPIO17 set to input

	cout << " Set GPIO pin directions" << endl;

	ipcam->setparametres ("192.168.1.10","80","toto","titi");

	while(1)
	{
        	gpio4->getval_gpio(inputstate);
		if (inputstate == "1")
		{
			if (laststate == "0")
			{
				cout << "get image " << endl;
				ipcam->getimage();
			}
			gpio23->setval_gpio ("1");
		}else
		{
                        gpio23->setval_gpio ("0");
		}
		laststate = inputstate ; 

	}

	return 0;
}
