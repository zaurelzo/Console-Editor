#chmod 700 compile.sh
g++ -g   main.cpp dataModule.cpp fileModule.cpp keybord.cpp displayModule.cpp  -o exe -lncurses -lpanel -lform 
