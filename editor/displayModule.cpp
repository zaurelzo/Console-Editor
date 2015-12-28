#include "displayModule.h"

displayModule::displayModule()
{

	initscr();
	start_color();
    init_pair(1,  COLOR_BLUE,  COLOR_RED); //init window saving and opening color 
}


displayModule::~displayModule()
{}

/*Print the text */
void displayModule::printText(string t)
{
		printw("%s",t.c_str());
       	refresh();
}


/*void displayModule::printSearchingText(string word,list<string> l)
{
	if (word != "")
	{
		clear();
		int counter=0;
		string new_word="";
		
		for (list<string>:: iterator it=l.begin(); it!=l.end(); ++it)
		{
			while(counter<(*it).size())
			{
				if((*it)[counter]==word[0])
				{
					if( (counter+word.size())<=(*it).size())
					{
						if (counter==0)
						{
							new_word = (*it).substr(counter,counter+word.size());
						}else
						{
							new_word = (*it).substr(counter,counter+word.size()-1);
						}
						
						//printw("%d**********%s**********%d\n",counter,new_word.c_str(),word.size());
						if(new_word==word)
						{
							attron(COLOR_PAIR(1));
							printw("%s",new_word.c_str());
							refresh();
							attroff(COLOR_PAIR(1));
							counter=counter+word.size();
						}else
						{
							printw("%c",(*it)[counter]);
							refresh();
							counter++;
						}
					}else //end because word does'nt belong to (*it)
					{
						 new_word=(*it).substr(counter);
						printw("%s",new_word.c_str());
						refresh();
						counter=(*it).size();
					}
					
				}else
				{
					//attron(COLOR_PAIR(1));
					printw("%c",(*it)[counter]);
					refresh();
					//attroff(COLOR_PAIR(1));
					counter++;
				}
			}
			counter=0;
		}
	}	
			
}*/


/*display the sentence and the searching word with an other color
@return : list which contains the exact position of each occurence founded*/
std::vector<int> displayModule::printSearchingWordInSentence(string word,string  sentence )
{

	std::vector<int> result;
	string manipulation = "";//sentence;
	bool finish = false ; 

	int start = 0 ;
	//int end = sentence.size() ;
	clear();
	size_t pos = sentence.find(word);
	//printw("****%s",sentence.c_str());
	while (finish==false )
	{
		if(pos==string::npos)
		{
			//result.push_back(start);
			//attron(COLOR_PAIR(1));
			
				manipulation = sentence.substr(start,sentence.size()-start); 
				printw("%s",manipulation.c_str());
				refresh();
			//attroff(COLOR_PAIR(1));
			finish=true ; 
		}else
		{
			//manipulation = sentence.substr(start,(int)pos); 
			
			if (start != pos)
			{
				printw("%s",(sentence.substr(start, ((int)pos )-start)).c_str()); //display without color
				attron(COLOR_PAIR(1));
				printw("%s",(  sentence.substr(  (int)pos , word.size())).c_str()); //display with color ,means we find an occurence of word in the sentence
				attroff(COLOR_PAIR(1));
				refresh();
			}else
			{
				attron(COLOR_PAIR(1));
				printw("%s",(  sentence.substr(  (int)pos , word.size())).c_str()); //display with color ,means we find an occurence of word in the sentence
				attroff(COLOR_PAIR(1));
				refresh();
			}
			
			result.push_back((int)pos);
			start=(int)pos+word.size();
			pos= sentence.find(word,start);
			/*if (pos!=string::npos)
			{
				result.push_back((int)pos);
			}*/
		}
	}
	
	return result ;
}
