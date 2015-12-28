#ifndef DEF_FILEMODULE
#define DEF_FILEMODULE

#include <iostream>
#include <string>
#include <fstream>
#include "dataModule.h"
#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>


using namespace std ;

class fileModule
{
public:
	fileModule();
	~fileModule();
	void open(string name ); //open  file "name" 
	void save(string name);//save if the file name 
	//void new() ; 
	void copyData(dataModule d); //this function is usefull for copy the text from main the local attribute data befor saving 
	string getText();
	dataModule getDataFromfileModule(); //return the value of attribute data

	private:
	dataModule data;
	string nameofFile;

};

#endif