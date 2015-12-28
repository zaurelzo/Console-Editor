#ifndef DEF_KEYBORD
#define DEF_KEYBORD

#include <string.h>
#include <ncurses.h>
#include <form.h>
#include <iostream>
#include <panel.h>
#include <string>
#include <list>
#include <ctime>


using namespace std;

class keybord
{
public:
	keybord();
	~keybord();
	void init(); //allocate ressources to use ncurses libray
	void move_cursor_next(); //move cursor to next 
	void move_cursor_back(); //move cursor to back
	//void selectCurrentWord();
	int getPostionCursorScreen();
	void move_cursor_to_position_horizontal(int pos);//move cursor horizontal to some position
	void move_cursor_to_position_vertical_up();//move cursor  up
	void move_cursor_to_position_vertical_down(); //move cursor down
	string init_panel_window(string label );//open a new window
	string print_in_middle(WINDOW *win, int starty, int startx, int width, string strin, chtype color  ) ;
	int getwidth();

private:
	//string selecting_word;
	WINDOW *my_wins;
	PANEL  *my_panels;
};


#endif 