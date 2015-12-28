#include "dataModule.h"
//#include <cstring>

 dataModule::dataModule()
{
	position_in_list=-1;
	curseur_position=0;
	number_of_character=0;
}

dataModule::~dataModule()
{}


/*Add a word inside the list 
@par1word to add in the list:*/
void dataModule::addWord(string Word)
{
	list<string>::iterator it=text.begin();
	int cpt =0;
	while (cpt<=position_in_list)
	{
		cpt++; 
		it++;
	}
	text.insert(it,Word) ;
	position_in_list++;
	curseur_position=Word.size();
	number_of_character=number_of_character+Word.size();
}

/*Inser a character before the actual position of the cursor
@par1:char to insert  */
void dataModule::addcharacter(char car,int posCursorScreen)
{
	//printw("+++++++++++++++++++%d\n",posCursorScreen);
	string new_word="" ; 
	if(position_in_list==-1)
	{
		new_word+=car;
		text.push_front(new_word);
		position_in_list++;
		curseur_position++;
		number_of_character++; 
	}else
	{
		
		list<string>::iterator it=text.begin();
		list<string>::iterator replace_word=it;
		int cpt =0; 
		bool find=false;

		while(find==false )
		{
			if (cpt==position_in_list)
			{
				new_word = (*it) ;
				replace_word=it;
				find=true ;
			}
			
			if(find==false)
			{
				posCursorScreen= posCursorScreen- (*it).size() ;
			}	
				cpt++;
				it++;
		}

		string result ="" ;
		//printw("---------------------%d",posCursorScreen);

		if(curseur_position==posCursorScreen)
		{
			 result =  new_word.substr(0,curseur_position)+ car+ new_word.substr(curseur_position) ;
			 curseur_position++;
			number_of_character++;
		}else if (curseur_position+1==posCursorScreen)
		{
			result=new_word+car;
			curseur_position++;
			number_of_character++;
		}else if(curseur_position==0)
		{
			result=car+new_word;
			curseur_position++;
			number_of_character++;
		}
		/*if (curseur_position!=-1)
		{
			 result =  new_word.substr(0,curseur_position)+ car+ new_word.substr(curseur_position) ;
			curseur_position++;
			number_of_character++;
		}else
		{
			result = car+new_word ;
			curseur_position++;
			number_of_character++;
		}*/
		
	
		text.insert((replace_word),result);	
		text.erase(replace_word) ; 
	}
	
}


/*Search if word is present inside the list which represent the text
@par1:word that we need to searh
@return:a array which contain  positions of differents occurences*/
vector<int> dataModule::searchWord(string word)
{
	vector<int> occurences_number;
	int cpt = 0 ;
	for (list<string>::reverse_iterator it=text.rbegin(); it!=text.rend(); ++it)
	{
		if( (*it)==word)
		{
			//cout<<"////////////////////"<<(*it)<<cpt<<endl;

			occurences_number.push_back(cpt);
		}
		cpt++; 
	}

	return occurences_number ;
}

/*@return :Return text*/
string dataModule::getText()
{	
	string stringChaine="";
	for (list<string>::iterator it=text.begin(); it!=text.end(); ++it)
	{
		stringChaine = stringChaine  +(*it);
	}

   return stringChaine ;
}

/*Change the value of position_in_list*/
void dataModule::setPositionInList(int value)
{
	position_in_list=value;
}


/*Change value of cursor*/
void dataModule::setCurseurPostion(int value)
{
	//printw("value : %d************************* ",value );
	//refresh();
	int abdi = value;
	list<string>::iterator it=text.begin();
	int local_num_of_char=0; //new cursor position value 
	position_in_list=-1;
	string mot="";
	while (local_num_of_char<=value &&(it!=text.end()))
	{
		for(int i =0 ; i <(*it).size();i++)
		{
			local_num_of_char++;
		}
		mot =(*it);
		position_in_list++;
		it++;
	}

	if (local_num_of_char>=value)
	{
		local_num_of_char =value+mot.size()-local_num_of_char; 
	}
	curseur_position = local_num_of_char;
	
}


/*@return:return cursor position */
int dataModule::getCurseurPostion()
{
	return curseur_position;
}

/*@return : return position in list*/
int dataModule::getPositionInList()
{
	return position_in_list ; 
}

 /*@return:return list which represent the text */
list<string> dataModule::getList()
{
	return text;
}


void dataModule::setList(list<string> t)
{
	 text=t;
}

/*Copy sentence if buffer */
void dataModule::copy(string sentence)
{
	buffer =sentence; 
}

/*Cut sentence inside the word*/
void dataModule::cut(string sentence)
{
	if(sentence!="")
	{
		buffer= sentence;
		list<string>::iterator it=text.begin();
		string previous ="";
		bool find = false;
		int cpt = 0 ;//find the good occurence of word
		while(find==false )
		{
			if ( ((*it)==sentence ) && (cpt==position_in_list) )
			{
				//previous=(*it)
				text.erase(it);
				find=true;
			}

			it++;
			cpt++;
		}

		position_in_list--;
		curseur_position=0; 
		number_of_character=number_of_character- sentence.size();

	}
	
}


/*Delete  word*/
void dataModule::deleteWord()
{
		//buffer= sentence;
		list<string>::iterator it=text.begin();
		string previous ="";
		bool find = false;
		int cpt = 0 ;//find the good occurence of word
		//printw("*************%d",position_in_list);
		while( (find==false ) && (it != text.end() ) && ( (position_in_list+1)!=text.size() ))
		{
			if (cpt==position_in_list )
			{
				previous=(*it);				
				text.erase(it);				
				find=true;
			}

			it++;
			cpt++;
		}
		//position_in_list++;
		curseur_position=0; 
		number_of_character=number_of_character- previous.size();
}


/*Delete the character before the cursor */
void dataModule::deleteChar(int pos_cursor_screen)
{
	if(position_in_list !=-1)
	{
		string new_word="" ; 
		list<string>::iterator it= text.begin();
		list<string>::iterator replace_word=it;
		string previous_word="";
		int cpt =0; 
		bool find=false;

		while(find==false )
		{
			if (cpt== position_in_list)
			{
				new_word = (*it) ;
				replace_word=it;
				find=true ;
				if(position_in_list!=0)
				{
					it--;
					previous_word=(*it);
					it++;
				}
			}
			if(find==false)
			{
				pos_cursor_screen= pos_cursor_screen-  (*it).size() ;
			}		
				cpt++;
				it++;
		}

		string result="";

		if(curseur_position==pos_cursor_screen)
		{
			if (curseur_position==0)
			{
				position_in_list--;
				if (position_in_list!=-1)
				{
					//clear(); printw("previous word:%s...\n",previous_word.c_str());
					curseur_position=previous_word.size();
					if((number_of_character+1)==pos_cursor_screen)
					{
						result =  previous_word.substr(0,curseur_position-1) ;
					}else
					{
						result =  previous_word.substr(0,curseur_position-1)+previous_word.substr(curseur_position) ;
					}

					curseur_position--;
					it=replace_word;
					replace_word--;
					text.erase(replace_word) ;
					text.insert((it),result);
					number_of_character--;
				}
			}else
			{
				result =  new_word.substr(0,curseur_position-1)+new_word.substr(curseur_position) ;
				//printw("---------------------------%s"result.c_str());
			 	curseur_position--;
				number_of_character--;
				text.insert((replace_word),result);	
				text.erase(replace_word) ; 
			}
			 
		}else if (curseur_position+1==pos_cursor_screen)
		{
			result=new_word.substr(0,new_word.size()-1);
			curseur_position--;
			number_of_character--;
			text.insert((replace_word),result);	
			text.erase(replace_word) ; 
		}		
	}
	//text.remove("");
}



/*Clear the list and reset all the attributes*/
void dataModule::clearData()
{
	text.clear();
	position_in_list=-1;
	curseur_position=0;
	number_of_character=0;
}

/*@return:return List's number of character  */
int dataModule::getNumberOfCharacter()
{
	return number_of_character;
}


/*Select the word where the cursor is located
@return:empty string if any word is selected , otherwise the selected word */
string dataModule::selectWord()
{
	list<string>::iterator it=text.begin();
	int cpt =0;
	string select="";
	while (cpt<=position_in_list)
	{
		cpt++; 
		select=(*it);
		it++;
	}

	return select;	
}


/*@return :return number of character which are present before before the actual position of the cusor */

int dataModule::getNumberOfCharacterBeforeCursor()
{
	list<string>::iterator it=text.begin();
	//list<string>::iterator b=it++;//debug
	//list<string>::iterator a=text.end();//debug
	//printw("%d",(*a).size());//debug
	int cpt =0;
	int result=0 ;
	int local_cpt  ; 
	string select="";
	bool find =false;
	while ( (cpt<=position_in_list) && (find==false) /*&& (it!=text.end())*/)
	{
		local_cpt=0;
		//if(it!=text.end())
		//{
			for(int i =0 ; i<(*it).size();i++)
			{
				if( (local_cpt==curseur_position) && (cpt==position_in_list) )
				{
					find=true ;
					break;
				}
				local_cpt++;
				result++;
			
			}
			cpt++; 
			select=(*it);
			it++;
		//}
		
	}

	return result-1;
}

/*Paste the word which is in the buffer*/
void dataModule::paste()
{
	list<string>::iterator it=text.begin();
	int cpt =0;
	while (cpt<=position_in_list)
	{
		cpt++; 
		it++;
	}
	text.insert(it,buffer) ;
	position_in_list++;
	curseur_position=buffer.size();
	number_of_character=number_of_character+buffer.size();
}

/*@return : true if the curor can move up , otherwise false */
bool dataModule::canMoveUp(int screenCursor,int sizeWindow) 
{
	if(( getNumberOfCharacterBeforeCursor()-(screenCursor+sizeWindow) )>= 0)
	{

		return true ;
	}else 
	{
		//clear();
		//printw("CharacterBeforeCursor() : %d ,screenCursor :%d ,sizeWindow:%d",getNumberOfCharacterBeforeCursor(),screenCursor,sizeWindow);
		return false ;
	}
} 

/*@return : true if the curor can move down , otherwise false */
bool dataModule::canMoveDown(int screenCursor,int sizeWindow) 
{
	if(( getNumberOfCharacterBeforeCursor()+(screenCursor+sizeWindow) )<= number_of_character)
	{
		return true ;
	}else 
	{
		return false ;
	}
} 
