# Console-Editor


I tried to design a console editor, something like nano editor in unix . <br/>
I implemented it in c++, ncurses libray is used to handle keyboard events and  graphical interface.
The project is not yet achieved. But basic functionalities are working.

## To compile the project

```bash
 sudo apt-get install libncurses-dev #install ncurses library 
 cd editor
./compile.sh
```

## To  run 

```bash
 ./run.sh
```

##EDITOR COMMANDS 

```bash
 ctrl-u : copy 
 ctrl -t : select 
 ctrl -r : paste
 ctrl-a : save 
 crtl-e : open 
 ctrl-f : search 
 ctrld -d : remove current word
 KEY LEFT : move cursor left 
 KEY RIGHT : move cursor left 
 KEY UP : move cursor up
 KEY RIGHT : move cursor down 
 BACKSPACE : Delete
```
