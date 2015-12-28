#ifndef DEF_DATAMODULE
#define DEF_DATAMODULE

#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <ncurses.h>
using namespace std;


class dataModule
{
public:
 dataModule();
 ~dataModule();
 void addWord(string Word);
 void addcharacter(char car,int posCursorScreen);
 vector<int> searchWord(string word);
 void copy(string sentence);
 void cut(string sentence);
 void paste();
 void deleteWord();
 void deleteChar(int pos_cursor_screen);

 string getText();
 void setPositionInList(int value);//change value posiontion_In_list
 void setCurseurPostion(int value);//Change value cursorPosition
 int getPositionInList();
 int getCurseurPostion();
 list<string> getList();//return list which represent the word of the text
 void setList(list<string> t); //copy the list
 void clearData();// reset the list 
 int getNumberOfCharacter(); //return number of character  of the list
 string selectWord(); //select the current word , (word were curseur position is pointing)
 int getNumberOfCharacterBeforeCursor();//return number of character which are present before before the actual position of the cusor 
 bool canMoveUp(int screenCursor,int sizeWindow) ; //indicates if the cursor can move up
 bool canMoveDown(int screenCursor,int sizeWindow) ;//indicates if the cursor can move down 



private:
  	list<string> text; //link list which contains the text
  	int position_in_list;  //indicate the exact position of the word  in the list that we editing
  	int curseur_position; //indicate the exact position of the cursor for the current editing word
    int number_of_character; //number of characterthe list
    string buffer ; //for copy , paste , cut

  };


#endif 