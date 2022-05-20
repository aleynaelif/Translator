hepsi: derle 
derle:
	gcc -I ./include/ -o ./lib/dllist.o -c ./src/dllist.c
	gcc -I ./include/ -o ./lib/fields.o -c ./src/fields.c
	gcc -I ./include/ -o ./lib/jval.o -c ./src/jval.c
	gcc -I ./include/ -o ./bin/ceviri ./lib/dllist.o ./lib/jval.o ./lib/fields.o ./src/main.c
	