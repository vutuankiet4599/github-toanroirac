all:	main
main:	main.o graphlib.o
		gcc -g -o main main.o graphlib.o libfdr.a -lm
main.o:	main.c 
	gcc -g -I/ -c main.c -lm
graphlib.o:	graphlib.c
	gcc -g -I/ -c graphlib.c -lm
clean:	
	rm -f *.o *~
