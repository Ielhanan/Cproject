myprog: bitField.o data.o entry.o extern.o generalFunc.o guidanceCommand.o ICommand.o JCommand.o RCommand.o Labels.o main.o 
	gcc -ansi -Wall -pedantic -g bitField.o data.o  entry.o extern.o generalFunc.o guidanceCommand.o ICommand.o JCommand.o RCommand.o Labels.o main.o -o myprog

bitField.o: bitField.c bitField.h
	gcc -c -ansi -Wall -pedantic -g bitField.c -o bitField.o

data.o: data.c data.h
	gcc -c -ansi -Wall -pedantic -g data.c -o data.o

entry.o: entry.c entry.h
	gcc -c -ansi -Wall -pedantic -g entry.c -o entry.o

extern.o: extern.c extern.h
	gcc -c -ansi -Wall -pedantic -g extern.c -o extern.o

generalFunc.o: generalFunc.c generalFunc.h
	gcc -c -ansi -Wall -pedantic -g generalFunc.c -o generalFunc.o

guidanceCommand.o: guidanceCommand.c guidanceCommand.h
	gcc -c -ansi -Wall -pedantic -g guidanceCommand.c -o guidanceCommand.o

ICommand.o: ICommand.c ICommand.h
	gcc -c -ansi -Wall -pedantic -g ICommand.c -o ICommand.o

JCommand.o: JCommand.c JCommand.h
	gcc -c -ansi -Wall -pedantic -g JCommand.c -o JCommand.o

Labels.o: Labels.c Labels.h
	gcc -c -ansi -Wall -pedantic -g Labels.c -o Labels.o

main.o: main.c main.h
	gcc -c -ansi -Wall -pedantic -g main.c -o main.o

RCommand.o: RCommand.c RCommand.h
	gcc -c -ansi -Wall -pedantic -g RCommand.c -o RCommand.o
