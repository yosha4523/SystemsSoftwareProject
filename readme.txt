Name: Yosha Riley

I altered the lex_index but only in functions that I wrote, 
otherwise I didn't change any of the provided code.

To Compile:
gcc driver.c lex.c -lm | ./a.out test.txt
	where test.txt is a text file of the code you wish to analyze


The text file must be formated as code such as the example in test1.txt: 

// this program multiplies two numbers given by the user
const one := 1;
var x, y, result;
procedure mult;
	begin
	if x > one then	// x number of recursive calls
		begin
			x := x - one;
			call mult;
		end;
	result := result + y; // after we make x recursive calls we can start adding y
	end;
begin
	// initialize values
	read x;
	read y;
	result := 0;
	call mult;
	write result;
end.