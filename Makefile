scheme: main.o lexer.o conscell.o parser.o eval.o
	gcc -o scheme main.o lexer.o conscell.o parser.o eval.o

main.o: main.c
	gcc -c main.c

lexer.o: lexer.c
	gcc -c lexer.c

conscell.o: conscell.c
	gcc -c conscell.c

parser.o: parser.c
	gcc -c parser.c

eval.o: eval.c
	gcc -c eval.c

clean:
	rm -f *~ *.o *.a