#include "keybord.h"

//renommer la classe keyboard

keybord::keybord()
{
	//selecting_word="";
}

keybord::~keybord()
{}

void keybord::init()
{
	initscr();
    clear();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    //panelVisible= false;
    scrollok(stdscr,true);
    idlok(stdscr,true);
   start_color();
    init_pair(2,  COLOR_BLUE,  COLOR_GREEN); //init window saving and opening color 


}



/*@par 1 : indication message of the action that need be print (exemple : enter name open file , enter name save file )
@par 2 : value 0 or 1 , 0 means that we wait user input | other number (different of 0) means we don't wait for user input ,we just display a window to notify the user
(with a message) that he did bad action 
@return : - if par 2 is 0 , return emtpty string if the user does not enter anything (means he cancel this opening ,saving operation) otherwise return user input
		- if par2 is an other number different of 0 , return always empty string 		*/
string keybord::init_panel_window(string label)
{   
	//prepare the window     
	int x, y, i;
	bool show_it=true;
    //char label[1000];
    y = 2;
    x = 10;
    my_wins = newwin(10, 60, y, x);

    //char user_input[1000];

    //attach panel to window and put this panel on top
    my_panels = new_panel(my_wins); 
    set_panel_userptr(my_panels, &show_it);
    update_panels();
    doupdate();

    //sprintf(label, " enter your message ");
    //show the window by printing box arround window 
    int startx, starty, height, width;
    getbegyx(my_wins, starty, startx);
    getmaxyx(my_wins, height, width);
    box(my_wins, 0, 0);
    mvwaddch(my_wins, 2, 0, ACS_LTEE); 
    mvwhline(my_wins, 2, 1, ACS_HLINE, width - 2); 
    mvwaddch(my_wins, 2, width - 1, ACS_RTEE); 
   string result =  print_in_middle(my_wins, 1, 0, width, label, COLOR_PAIR(2) );  
    return result ;      
}


/*move cursor horizontal to next position*/
void keybord::move_cursor_next()
{
	int x , y;
	getyx(stdscr, y, x);
	move(y,x+1);
	//return return x+1;
}

/*return:screen cursont position*/
int keybord::getPostionCursorScreen()
{
	int x , y;
	getyx(stdscr, y, x);
	return x; 
}

/*move cursor horizontal to previous position*/
void keybord::move_cursor_back()
{
	int x , y;
	getyx(stdscr, y, x); 
	move(y,x-1);
	//return x-1;
}

/*move cursor horizontal to some position 
@par1:pos that we need to move*/
void keybord::move_cursor_to_position_horizontal(int pos)
{
	//printw("pos :%d",pos);refresh();
	int x , y;
	getyx(stdscr, y, x);
	move(y,pos+1);
	refresh();
} 

/*Move cursor up*/
void keybord::move_cursor_to_position_vertical_up()
{
	int x , y;
	getyx(stdscr, y, x);
	move(y-1,x);
	refresh();
}

/*move cursor down */
void keybord::move_cursor_to_position_vertical_down()
{
	int x , y;
	getyx(stdscr, y, x);
	move(y+1,x);
	refresh();
}

/*return: width of actual window*/
int keybord::getwidth()
{
	int height,width;
	getmaxyx(stdscr, height, width);

	return width ; 
}


string keybord::print_in_middle(WINDOW *win, int starty, int startx, int width, string strin, chtype color)
{   
	echo();   
	 int length, x, y;
     float temp;
     char user_input[100]="";

 	show_panel(my_panels); //show the panel 

        if(win == NULL)
                win = stdscr;
        getyx(win, y, x);
        if(startx != 0)
                x = startx;
        if(starty != 0)
                y = starty;
        if(width == 0)
                width = 80;

        length = strin.size();
        temp = (width - length)/ 2;
        x = startx + (int)temp;
      
      	wattron(win, color);
      	mvwprintw(win, y, x, " %s", strin.c_str());    
        wattroff(win, color);

      
        	mvwscanw(win,y+2,x-15,"%[^\n]s",user_input); //USER INPUT , IT'S WORKINK BUT THE INPUT IS NOT DISPLAYING WHILE THE USER IS TYPING 
        	//printw("%s",user_input);
       		refresh();
       		noecho();
       		hide_panel(my_panels);
       return user_input;
}




