Name: Yosha Riley

I did not change anything from the given files (besides parser.c of course).

Instructions

To run:
You must first compile with the following command
	gcc -g vm.o lex.o parser.c driver.c

Then run the following to compile a text file

./a.out infile.txt

where infile is the code you want to compile

The compiler supports the following tags for additional information while compiling

-l - prints the lexeme list of tokens
-s - prints the symbol table
-a - prints assembly code
-v - prints the VM execution trace

an example of using them would be -

./a.out infile.txt -a -s