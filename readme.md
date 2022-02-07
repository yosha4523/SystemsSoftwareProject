# Simple PL/0 Compiler in C
This is a simple compiler for the PL/0 language implemented in C, written for the Fall 2021 Systems Software class at UCF.

My implentation is pretty messy so I would advise against using my code as more than a template in the future, I don't claim to have done  this project well or it be super optomized code that is bug free. So you were warned.
## To Compile
### Only complile the VM

`gcc vm.c | ./a.out test.txt`

where test.txt his a text file of instructions listed in the order of

OPcode,  Lexicalgraphical Level, and M which changes based on OPcode

All fields must be separated

### Only compile the lex analyzer

`gcc driver.c lex.c -lm | ./a.out test.txt`

where test.txt is a text file of the code you wish to analyze

This will output a tokenized list of the operations to a text file

### Full Compilation
**To run:**
You must first compile with the following command
	`gcc -g vm.o lex.o parser.c driver.c`

Then run the following to compile a text file

`./a.out infile.txt`

Where infile is the code you want to compile

The compiler supports the following flags for additional information while compiling

-l - prints the lexeme list of tokens
-s - prints the symbol table
-a - prints assembly code
-v - prints the VM execution trace

an example of using them would be -

./a.out infile.txt -a -s
