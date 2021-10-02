/* 
	This is the lex.c file for the UCF Fall 2021 Systems Software Project.
	For HW2, you must implement the function lexeme *lexanalyzer(char *input).
	You may add as many constants, global variables, and support functions
	as you desire.
	
	If you choose to alter the printing functions or delete list or lex_index, 
	you MUST make a note of that in you readme file, otherwise you will lose 
	5 points.
*/

//Yosha Riley
//COP3402 Fall 2021


#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "compiler.h"
#define MAX_NUMBER_TOKENS 500
#define MAX_IDENT_LEN 11
#define MAX_NUMBER_LEN 5

lexeme *list;
int lex_index;

void printlexerror(int type);
void printtokens();
int addtoken(char* input);
int isnum(char* input);
int isid(char* input);
int issym(char input);

lexeme *lexanalyzer(char *input)
{
	//allocate memory for the list
	list = malloc(sizeof(lexeme) * MAX_NUMBER_TOKENS);

	//make a temp string to send to the add token funciton
	char tempString[MAX_IDENT_LEN + 1];
	int i = 0;
	lex_index = 0;

	//outer loop to go through the input
	for(i = 0; input[i] != '\0'; i++)	{
		//make sure we dont go over our max input
		if(lex_index <= MAX_NUMBER_TOKENS)	{
			
			//inner loop to construct the strings to pass
			for(int j = 0;;i++)	{

					//skip through comments
					if(input[i] == '/' && input[i + 1] == '/')	{
						while(input[i] != '\n')	{
							i++;
						}
					}

					//skip over spaces unless they are in teh middle of a string
					if(input[i] == ' ')	{
						if(strlen(tempString) == 0)
							continue;
						tempString[j] = '\0';
						break;
					}
					//skips over all control charaacters
					else if(iscntrl(input[i]))	{
						continue;
					}
					//reads numbers and throws the 2 related errors
					else if(isdigit(input[i]) && j == 0)	{
						while(isdigit(input[i]))	{
							if(j <= MAX_NUMBER_LEN)	{
								tempString[j] = input[i];
								i++;
								j++;
							}
							else	{
								printlexerror(3);
								return NULL;
							}
						}
						if(isalpha(input[i]))	{
							printlexerror(2);
							return NULL;
						}
						i--;
						tempString[j] = '\0';
						break;
					}
					//starts reading identifiers and throws related error
					else if(isalpha(input[i]) && j== 0)	{
						//ensures alphanumerics
						while(isalnum(input[i]))	{
							if(j <= MAX_IDENT_LEN)	{
								tempString[j] = input[i];
								i++;
								j++;
							}
							else	{
								printlexerror(4);
								return NULL;
							}
						}
						tempString[j] = '\0';
						i--;
						break;
					}
					//checks for symbols that MUST conjoin with equals
					else if(input[i] == ':' || input[i] == '=' || input[i] == '!')	{
						if(input[i + 1] == '=')	{
							tempString[j] = input[i];
							i++;
							j++;
							tempString[j] = input[i];
							j++;
							tempString[j] = '\0';
							break;
						}
						else	{
							printlexerror(1);
							return NULL;
						}
					}
					//checks for symbols that MAY conjoin with equals
					else if(input[i] == '<' || input[i] == '>')	{
						if(input[i + 1] == '=')	{
							tempString[j] = input[i];
							i++;
							j++;
							tempString[j] = input[i];
							j++;
							tempString[j] = '\0';
							break;
						}

						tempString[j] = input[i];
						j++;
					}
					//checks for symbols that arent related to equals
					else if(issym(input[i]))	{
						tempString[j] = '\0';
						addtoken(tempString);
						tempString[0] = input[i];
						tempString[1] = '\0';
						break;
					}
				}
			}
		//adds whatever is in temp string to the list
		addtoken(tempString);
	}

	printtokens();
	return list;
}

//adds tokens based on a string to the list
int addtoken(char *input)	{

	if(!strcmp("const", input))	{
		list[lex_index].type = 1;
	}
	else if(!strcmp("var", input))	{
		list[lex_index].type = 2;
	}
	else if(!strcmp("procedure", input))	{
		list[lex_index].type = 3;
	}
	else if(!strcmp("begin", input))	{
		list[lex_index].type = 4;
	}
	else if(!strcmp("end", input))	{
		list[lex_index].type = 5;
	}
	else if(!strcmp("while", input))	{
		list[lex_index].type = 6;
	}
	else if(!strcmp("do", input))	{
		list[lex_index].type = 7;
	}
	else if(!strcmp("if", input))	{
		list[lex_index].type = 8;
	}
	else if(!strcmp("then", input))	{
		list[lex_index].type = 9;
	}
	else if(!strcmp("else", input))	{
		list[lex_index].type = 10;
	}
	else if(!strcmp("call", input))	{
		list[lex_index].type = 11;
	}
	else if(!strcmp("write", input))	{
		list[lex_index].type = 12;
	}
	else if(!strcmp("read", input))	{
		list[lex_index].type = 13;
	}
	else if(!strcmp(":=", input))	{
		list[lex_index].type = 16;
	}
	else if(!strcmp("+", input))	{
		list[lex_index].type = 17;
	}
	else if(!strcmp("-", input))	{
		list[lex_index].type = 18;
	}
	else if(!strcmp("*", input))	{
		list[lex_index].type = 19;
	}
	else if(!strcmp("/", input))	{
		list[lex_index].type = 20;
	}
	else if(!strcmp("%", input))	{
		list[lex_index].type = 21;
	}
	else if(!strcmp("==", input))	{
		list[lex_index].type = 22;
	}
	else if(!strcmp("!=", input))	{
		list[lex_index].type = 23;
	}
	else if(!strcmp("<", input))	{
		list[lex_index].type = 24;
	}
	else if(!strcmp("<=", input))	{
		list[lex_index].type = 25;
	}
	else if(!strcmp(">", input))	{
		list[lex_index].type = 26;
	}
	else if(!strcmp(">=", input))	{
		list[lex_index].type = 27;
	}
	else if(!strcmp("odd", input))	{
		list[lex_index].type = 28;
	}
	else if(!strcmp("(", input))	{
		list[lex_index].type = 29;
	}
	else if(!strcmp(")", input))	{
		list[lex_index].type = 30;
	}
	else if(!strcmp(",", input))	{
		list[lex_index].type = 31;
	}
	else if(!strcmp(".", input))	{
		list[lex_index].type = 32;
	}
	else if(!strcmp(";", input))	{
		list[lex_index].type = 33;
	}
	else if(isid(input))	{
		list[lex_index].type = 14;
		strcpy(list[lex_index].name, input);
	}
	else if(isnum(input))	{
		list[lex_index].type = 15;
		list[lex_index].value = atoi(input);
	}
	else	{
		return 0;
	}

	lex_index++;
	return 1;
}

//condenses the if statement in the lexanalyzer function
int issym(char input)	{
	if(input == '(' || input == ')' || input == '.' || input == '+' 
		|| input == '-' || input == '/' || input == '*' || input == ';' || input == ',')	{
		return 1;
	}
	return 0;
}

//checks if a string is a number
int isnum(char* input)	{
	for(int i = 0; input[i] != '\0'; i++)	{
		if(isdigit(input[i]))	{
			return 1;
		}
	}	
	return 0;
}

//checks if a string is an identifier
int isid(char* input)	{
	if(!isdigit(input[0]) && input[0] != ' ' && !iscntrl(input[0]))
		return 1;
	else
		return 0;
}

void printtokens()
{
	int i;
	printf("Lexeme Table:\n");
	printf("lexeme\t\ttoken type\n");
	for (i = 0; i < lex_index; i++)
	{
		switch (list[i].type)
		{
			case oddsym:
				printf("%11s\t%d", "odd", oddsym);
				break;
			case eqlsym:
				printf("%11s\t%d", "==", eqlsym);
				break;
			case neqsym:
				printf("%11s\t%d", "!=", neqsym);
				break;
			case lsssym:
				printf("%11s\t%d", "<", lsssym);
				break;
			case leqsym:
				printf("%11s\t%d", "<=", leqsym);
				break;
			case gtrsym:
				printf("%11s\t%d", ">", gtrsym);
				break;
			case geqsym:
				printf("%11s\t%d", ">=", geqsym);
				break;
			case modsym:
				printf("%11s\t%d", "%", modsym);
				break;
			case multsym:
				printf("%11s\t%d", "*", multsym);
				break;
			case divsym:
				printf("%11s\t%d", "/", divsym);
				break;
			case addsym:
				printf("%11s\t%d", "+", addsym);
				break;
			case subsym:
				printf("%11s\t%d", "-", subsym);
				break;
			case lparensym:
				printf("%11s\t%d", "(", lparensym);
				break;
			case rparensym:
				printf("%11s\t%d", ")", rparensym);
				break;
			case commasym:
				printf("%11s\t%d", ",", commasym);
				break;
			case periodsym:
				printf("%11s\t%d", ".", periodsym);
				break;
			case semicolonsym:
				printf("%11s\t%d", ";", semicolonsym);
				break;
			case assignsym:
				printf("%11s\t%d", ":=", assignsym);
				break;
			case beginsym:
				printf("%11s\t%d", "begin", beginsym);
				break;
			case endsym:
				printf("%11s\t%d", "end", endsym);
				break;
			case ifsym:
				printf("%11s\t%d", "if", ifsym);
				break;
			case thensym:
				printf("%11s\t%d", "then", thensym);
				break;
			case elsesym:
				printf("%11s\t%d", "else", elsesym);
				break;
			case whilesym:
				printf("%11s\t%d", "while", whilesym);
				break;
			case dosym:
				printf("%11s\t%d", "do", dosym);
				break;
			case callsym:
				printf("%11s\t%d", "call", callsym);
				break;
			case writesym:
				printf("%11s\t%d", "write", writesym);
				break;
			case readsym:
				printf("%11s\t%d", "read", readsym);
				break;
			case constsym:
				printf("%11s\t%d", "const", constsym);
				break;
			case varsym:
				printf("%11s\t%d", "var", varsym);
				break;
			case procsym:
				printf("%11s\t%d", "procedure", procsym);
				break;
			case identsym:
				printf("%11s\t%d", list[i].name, identsym);
				break;
			case numbersym:
				printf("%11d\t%d", list[i].value, numbersym);
				break;
		}
		printf("\n");
	}
	printf("\n");
	printf("Token List:\n");
	for (i = 0; i < lex_index; i++)
	{
		if (list[i].type == numbersym)
			printf("%d %d ", numbersym, list[i].value);
		else if (list[i].type == identsym)
			printf("%d %s ", identsym, list[i].name);
		else
			printf("%d ", list[i].type);
	}
	printf("\n");
	list[lex_index++].type = -1;
}

void printlexerror(int type)
{
	if (type == 1)
		printf("Lexical Analyzer Error: Invalid Symbol\n");
	else if (type == 2)
		printf("Lexical Analyzer Error: Invalid Identifier\n");
	else if (type == 3)
		printf("Lexical Analyzer Error: Excessive Number Length\n");
	else if (type == 4)
		printf("Lexical Analyzer Error: Excessive Identifier Length\n");
	else
		printf("Implementation Error: Unrecognized Error Type\n");
	
	free(list);
	return;
}