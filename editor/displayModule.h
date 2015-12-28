#ifndef DEF_DISPLAYMODULE
#define DEF_DISPLAYMODULE

#include <string>
#include <ncurses.h>
#include <iostream>
#include <list>
#include <vector>

using namespace std;

class displayModule
{
public:
	displayModule();
	~displayModule();
	void printText(string text);//print normal text
	//void printSearchingText(string  word, list<string> l);
	std::vector<int> printSearchingWordInSentence(string word,string  sentence );//display the sentence and the searching word with an other color


	/* data */
};


#endif