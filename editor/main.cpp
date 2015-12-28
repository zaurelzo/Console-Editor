#include <iostream>
#include "dataModule.h"
#include "fileModule.h"
#include "keybord.h"
#include "displayModule.h"
#include <string>
#include <ncurses.h>
#include <vector>
using namespace std ; 


//save editing word before doing any other operation(search, keyup,keydown,delete etc...)
void save_editiong_word(bool * editing_buffer_string,int *does , dataModule * data, string * local_buffer_string,string * local_buffer_space);

//analyse next character after some special operation(search, delete,keyup,keydow etc..) and do an approrite operation(if we ask to add new character , this function will do that,otherwise the main function will execute the appropriate operation)
void analyse_next_character_after_special_operation(bool *manipulate_string_after_backspace,int * additional_char,dataModule* data ,displayModule * pr, keybord* kbord ,int position);
void analyse_next_character_after_special_operation_delete(bool *manipulate_string_after_backspace,int * additional_char,dataModule* data ,displayModule * pr, keybord* kbord );

int main(int argc, char** argv)
{


 dataModule data ; 
 fileModule file;
 keybord kbord;
 displayModule pr;
 int input_char ; //get input from user
 string local_buffer_string=""; //the local string that we are editing
 string local_buffer_space="";//current string space that we are editinf
 string select="";//word that we are selected
 bool editing_buffer_string =true ;//bool to indicates if we are editing a string different of space string
 int does = 0; 
  //int current_position_currsor 
 char c ; // for analysis char that user typed
 int additional_char;// for analysis char that user typed
 string previous_char =""; //make a distinction between string space and a string differenct of string space
 bool manipulate_string_after_backspace=false; //allowed to do particualar treatment after keyup,keydown,keyleft ,keyright,backspace
int lsdgs=0;//debug 
string saving_opening_searching ="";
std::vector<int> position_occurences_after_search;


kbord.init();
while(1)
{

    //usefull to delete the approriate letter after backspace
  if(manipulate_string_after_backspace==true)
  {
    input_char=additional_char;
    manipulate_string_after_backspace=false;
  } else 
  {
      input_char = wgetch(stdscr); //get char from keybord 
    }

    switch(input_char)
    {


    //ctrl d : remove current word 
      case 4 :  save_editiong_word(&editing_buffer_string,&does ,&data, &local_buffer_string,&local_buffer_space);
                data.deleteWord();
                clear(); 
                pr.printText(data.getText());
                kbord.move_cursor_to_position_horizontal(data.getNumberOfCharacterBeforeCursor());
               break;  

  //ctrl-w : cut 
      case 23 : save_editiong_word(&editing_buffer_string,&does ,&data, &local_buffer_string,&local_buffer_space);
               data.cut(select);
              clear(); 
              pr.printText(data.getText());
              kbord.move_cursor_to_position_horizontal(data.getNumberOfCharacterBeforeCursor());
              break;

  //ctr -f for searching 
      case 6 : save_editiong_word(&editing_buffer_string,&does ,&data, &local_buffer_string,&local_buffer_space);
                saving_opening_searching=kbord.init_panel_window("SEARCH WORD,ENTER FOR CANCEL");
                if ( saving_opening_searching!="")
                {
                  position_occurences_after_search = pr.printSearchingWordInSentence(saving_opening_searching,data.getText());
                  saving_opening_searching="";
                  //MOVE CURSOR TO THE GOOD POSITION
                  //clear();
                  //printw("************%d" , position_occurences_after_search.size());
                  /*int mouvment =0 ;
                  char somethint[100];
                  if (position_occurences_after_search.empty()==false)
                  {
                    getstr(somethint);
                    //while we press enter , move cursor to the next occurences 
                    while("somethint"==10)
                    {
                      if (mouvment=position_occurences_after_search.size())
                      {
                        mouvment=0;
                      }
                      kbord.move_cursor_to_position_horizontal(position_occurences_after_search[mouvment]);
                      mouvment++;
                    }
                  }*/
                }

                break;

  //ctrl-u copy   
  case 21 :save_editiong_word(&editing_buffer_string,&does ,&data, &local_buffer_string,&local_buffer_space);
          data.copy(select);
           break;

     //ctrl -t :( select  ) for the moment , it's debug     
  case 20: select = data.selectWord();
            //pr.printText(select);
             //lsdgs= kbord.getPostionCursorScreen(); //debug
            //clear();
            //printw("position in list :%d , position curseur : %d \n ",data.getPositionInList(), data.getCurseurPostion());
            //printw("number of character before cursor :%d ",data.getNumberOfCharacterBeforeCursor());
            //printw("position cursor screen  : %d \n",lsdgs);
            //printw("number element in list : %d,contents:%s.", data.getList().size(),data.getText().c_str());
            //printw("%s",data.getText().c_str());
            //kbord.move_cursor_to_position_horizontal(55);
            //saving_opening_searching= kbord.init_panel_window("enter something");
              break;


//press enter


case 10 : //data.addWord("\n");
          kbord.move_cursor_to_position_vertical_down();
          kbord.move_cursor_to_position_horizontal(-1);
          break;


  //ctrl -v : paste
  case 22 : save_editiong_word(&editing_buffer_string,&does ,&data, &local_buffer_string,&local_buffer_space);
            data.paste();
            clear();
            // printw("%s",select.c_str());refresh();
            pr.printText(data.getText());
            break;


  //ctrl-a : save (for the moment ,the name of save file is fixed)
  case 1:   saving_opening_searching=kbord.init_panel_window("SAVE TEXT,ENTER FOR CANCEL");
            if ( saving_opening_searching!="")
            {
              file.copyData(data);
              file.save(saving_opening_searching);
              saving_opening_searching="";
            }  
            break ;



  //crtl-e : open : (for the moment , the name of open file is fixed )
  case 5 :try 
          {
            save_editiong_word(&editing_buffer_string,&does ,&data, &local_buffer_string,&local_buffer_space);
            saving_opening_searching=kbord.init_panel_window("OPEN TEXT,ENTER FOR CANCEL");
            if ( saving_opening_searching!="")
            {
                //file.copyData(data);
                //file.save("filetest.txt");
              clear();
             data.clearData();
             file.open(saving_opening_searching);
             data=file.getDataFromfileModule();
             clear();
             pr.printText(file.getText());
             saving_opening_searching="";
           } 
                    //move cursor at the end  
         }catch (int f )
         {
            //do something if error 
            //printw("*************************\n");
            //saving_opening_searching=kbord.init_panel_window("WARNING, FILE DOES NOT EXIST \n ");

         }                    
         break;


    //KEYUP: move cursor up
  case KEY_UP :  save_editiong_word(&editing_buffer_string,&does ,&data, &local_buffer_string,&local_buffer_space);
              if (data.canMoveUp(kbord.getPostionCursorScreen(),kbord.getwidth())==true)
              {
                kbord.move_cursor_to_position_vertical_up();
                //debug this line 
                 data.setCurseurPostion( data.getNumberOfCharacterBeforeCursor()-(kbord.getPostionCursorScreen()+kbord.getwidth() ));

                   analyse_next_character_after_special_operation( &manipulate_string_after_backspace,&additional_char,&data ,&pr, &kbord ,data.getNumberOfCharacterBeforeCursor()-1);
                }else
                {
                  //clear(); //debug
                }
           break;



    //KEYDOWN: move cursor down
  case KEY_DOWN :  save_editiong_word(&editing_buffer_string,&does ,&data, &local_buffer_string,&local_buffer_space);
                  if (data.canMoveDown(kbord.getPostionCursorScreen(),kbord.getwidth())==true)
                  {
                    kbord.move_cursor_to_position_vertical_down();
                    data.setCurseurPostion( data.getNumberOfCharacterBeforeCursor()+(kbord.getPostionCursorScreen()+kbord.getwidth() ));

                  analyse_next_character_after_special_operation( &manipulate_string_after_backspace,&additional_char,&data ,&pr, &kbord ,data.getNumberOfCharacterBeforeCursor()-1);
                  }
             break;     




   //move cursor left        
	 	case KEY_LEFT: save_editiong_word(&editing_buffer_string,&does ,&data, &local_buffer_string,&local_buffer_space);
                  kbord.move_cursor_back();
                  data.setCurseurPostion(kbord.getPostionCursorScreen());
                  //data.setCurseurPostion(kbord.getPostionCursorScreen());
                 analyse_next_character_after_special_operation( &manipulate_string_after_backspace,&additional_char,&data ,&pr, &kbord ,data.getNumberOfCharacterBeforeCursor()+1);
               break;



   //move cursor right        
	 	case KEY_RIGHT: save_editiong_word(&editing_buffer_string,&does ,&data, &local_buffer_string,&local_buffer_space);
                  if(kbord.getPostionCursorScreen()<data.getNumberOfCharacter()) //if cursor can be move 
                  {
                    data.setCurseurPostion(kbord.getPostionCursorScreen()+1);
                    kbord.move_cursor_next();
                    analyse_next_character_after_special_operation( &manipulate_string_after_backspace,&additional_char,&data ,&pr, &kbord ,data.getNumberOfCharacterBeforeCursor()+1);
                  }
                  break; 



   //remove letter       
	 	case KEY_BACKSPACE ://printw("////////////////////////%d",input_char);refresh(); 
                        save_editiong_word(&editing_buffer_string,&does ,&data, &local_buffer_string,&local_buffer_space); 
                        
                        data.deleteChar(kbord.getPostionCursorScreen());
                        clear();
                        pr.printText(data.getText());
                        kbord.move_cursor_to_position_horizontal(data.getNumberOfCharacterBeforeCursor());

                        //kbord.move_cursor_to_position_horizontal(data.getNumberOfCharacterBeforeCursor()-1);
                        analyse_next_character_after_special_operation_delete( &manipulate_string_after_backspace,&additional_char,&data ,&pr, &kbord );
                        break;


default:
          c =input_char;   
          if (c!=' ')
          {
  	 			 	 local_buffer_string+=c; //build word
  	 			   	printw("%c",c);
          if(previous_char==" " )
          {
              data.addWord(local_buffer_space);
              local_buffer_space="";
          }
            editing_buffer_string=true ;
            does=1;
            previous_char="";previous_char+=c;
  	 			}else if (c==' ' ) //9 for tab
          {
            local_buffer_space+=c;
            printw("%c",c);
            if(previous_char!=" ")
            {
                data.addWord(local_buffer_string);
                local_buffer_string="";
            }
            editing_buffer_string=false;
            does=1;
            previous_char="";previous_char+=c;
          }
        break;

    }
  }
  return 0 ;
}


void save_editiong_word(bool * editing_buffer_string, int *does , dataModule * data, string * local_buffer_string,string * local_buffer_space)
{
  if (((*editing_buffer_string)==true) && ((*does) ==1)) //variable does is usefull to don't save 2times the same word
  {
     data->addWord(*local_buffer_string);
     *local_buffer_string="";
     *does=0;
  } else if(((*editing_buffer_string)==false) && ((*does) ==1))
  {
    data->addWord(*local_buffer_space);
    *does=0;
    *local_buffer_space="";
  } 
}

void analyse_next_character_after_special_operation(bool *manipulate_string_after_backspace,int * additional_char,dataModule* data ,displayModule * pr, keybord* kbord ,int position)
{
   while((*manipulate_string_after_backspace)==false)
    {
      int input_char =wgetch(stdscr);
      //request for remove_next_word, cut ,search, paste ,select save, open , bakspace ,' ',KEYUP, we leave the loop , the switch will do the appriate treatment 
        if( (input_char==4) ||  (input_char==23) || (input_char==6) || (input_char== 22)|| (input_char==20)|| (input_char==1) || (input_char==5) || (input_char==21) || (input_char==KEY_LEFT) || (input_char==KEY_RIGHT) || (input_char==KEY_BACKSPACE) || (input_char==KEY_UP) || (input_char==KEY_DOWN) )//request to save
        {
          (*manipulate_string_after_backspace)=true;
          (*additional_char) = input_char;
        }
        else
        {
          
            data->addcharacter(input_char,kbord->getPostionCursorScreen());
            clear(); 
            pr->printText(data->getText());
            kbord->move_cursor_to_position_horizontal(position);
            position++;
        }
      }
}

void analyse_next_character_after_special_operation_delete(bool *manipulate_string_after_backspace,int * additional_char,dataModule* data ,displayModule * pr, keybord* kbord )
{
   while((*manipulate_string_after_backspace)==false)
    {
      int input_char =wgetch(stdscr);
      
        if(  (input_char==KEY_BACKSPACE))//request to save
        {
            data->deleteChar(kbord->getPostionCursorScreen());
            clear();
            pr->printText(data->getText());
            kbord->move_cursor_to_position_horizontal(data->getNumberOfCharacterBeforeCursor());
            
          //request for remove_next_word, cut ,search, paste ,select save, open ,' ',KEYUP, we leave the loop , the switch will do the appriate treatment 
        }else if ( (input_char==4) ||  (input_char==23) || (input_char==6) || (input_char== 22)|| (input_char==20)|| (input_char==1) || (input_char==5) || (input_char==21) || (input_char==KEY_LEFT) || (input_char==KEY_RIGHT)  || (input_char==KEY_UP) || (input_char==KEY_DOWN) )
        {
          (*manipulate_string_after_backspace)=true;
          (*additional_char) = input_char;  
        }else
        {
            data->addcharacter(input_char,kbord->getPostionCursorScreen());
            clear(); 
            pr->printText(data->getText());
            kbord->move_cursor_to_position_horizontal(data->getNumberOfCharacterBeforeCursor());
        }
      }
}