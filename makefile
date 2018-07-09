FILES	= lex.yy.c parser.tab.c main.c ast.c
CC	= gcc
CFLAGS	= -g 

test:		$(FILES)
		$(CC) $(CFLAGS) $(FILES) -o test

lex.yy.c:	lexer.l parser.tab.c
		flex lexer.l

parser.tab.c:	parser.y 
		bison -d parser.y

clean:
		rm -f *.o *~ lex.yy.c parser.tab.c parser.tab.h test
