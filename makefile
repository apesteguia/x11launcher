all: rm list cmenu main clean run

install: rm list cmenu main clean 
			sudo cp mlauncher /bin/
			
uninstall: 
			sudo rm /bin/mlauncher

run: 
			./mlauncher
rm: 
			rm -f mlauncher 

clean: 
			rm -f *.o

main: mlauncher.c
			gcc mlauncher.c -o mlauncher Cmenu.o list.o -Wall -lGL -lm -lpthread -ldl -lrt -lX11 -lXinerama
cmenu: Cmenu.c Cmenu.h
			gcc -c Cmenu.c -Wall -lGL -lm -lpthread -ldl -lrt -lX11 list.o
list: list.c list.h
			gcc -c list.c -Wall
