#include "fileModule.h"


fileModule::fileModule()
{
	nameofFile="";
}


fileModule::~fileModule()
{}

/*Open the file "name"
@par1:name of file to open 
raise an exception if the file does not exist*/
void fileModule::open(string name )
{
	FILE  *file=NULL;
	file = fopen(name.c_str(),"r+");
	string content="";
	char current_car;
	
	if(file!=NULL)
	{
		
		current_car=fgetc(file);
		while(current_car!=EOF)
		{
			while((current_car!=' ') && (current_car!=EOF) )
			{
				content+=current_car;
				current_car=fgetc(file);
			}
			data.addWord(content);
			content="";

			while(current_car==' ' && (current_car!=EOF))
			{
				content+=current_car;
				current_car=fgetc(file);
			}
			data.addWord(content);
			content="";
		}
		fclose(file);
	}else 
	{
		throw -1 ; 
	}

	//printf("%s",data.getText().c_str() );
	//refresh();
}

/*save the file "name"
@par1:name of file to osave */
void fileModule::save(string name)
{
	ofstream file(name.c_str());
	string stringChaine="";

	stringChaine=data.getText();
	if(file.is_open())
	{
		file<<stringChaine;
		file.close();
	}else 
	{
		cerr<< "ERROR OPENING FILE !";
		exit(1);

	}
}

void  fileModule::copyData(dataModule d)
{
	data=d;
}

string fileModule::getText()
{

	return data.getText();
}

dataModule fileModule::getDataFromfileModule()
{
	return data; 
}







