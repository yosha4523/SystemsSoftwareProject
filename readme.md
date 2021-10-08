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

### Code Generation
Todo

### Full Compilation
Todo