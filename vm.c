//Yosha Riley
#include <stdio.h>

#define MAX_PAS_LENGTH 500

typedef struct IRstruct  {
    int OP;
    int L;
    int M;
} IRstruct;

int BP;     //Base pointer
int SP;     //Stack pointer
int PC; //Program counter
int DP;     //Data pointer
int GP;     //Global pointer
int FREE;   //Heap pointer
int IC;     //Instruction counter
int pas[MAX_PAS_LENGTH];

int base(int L) {
    int  arb = BP;      //arb -> activation record base
    while (L > 0)   {   //find base L levels down
        arb = pas[arb];
        L--;
    }

    return arb;
}

void print_execution(int line, char *opname, int *IR, int PC, int BP, int SP, int DP, int *pas, int GP)
{
	int i;
	// print out instruction and registers
	printf("%2d\t%s\t%d\t%d\t%d\t%d\t%d\t%d\t", line, opname, IR[1], IR[2], PC, BP, SP, DP);
	
	// print data section
	for (i = GP; i <= DP; i++)
		printf("%d ", pas[i]);
	printf("\n");
	
	// print stack
	printf("\tstack : ");
	for (i = MAX_PAS_LENGTH - 1; i >= SP; i--)
		printf("%d ", pas[i]);
	printf("\n");
}

void main(int argc, char** argv) {
    FILE* input = fopen(argv[1], "r");

    for(int i = 0; i < MAX_PAS_LENGTH; i++) {
        pas[i] = 0;
    }

    //load input into text 
    int i = 0;
    while(fscanf(input, "%i", &pas[i]) != EOF){
        i++;
    }

    //set initial CPU registers
    IRstruct IR;
    PC = 0;
    SP = MAX_PAS_LENGTH;
    IC = i;
    GP = IC;
    DP = IC - 1;
    FREE = IC + 40;
    BP = IC;

    //instruction cycle
    while(PC < i)  {
        //fetch  cycle

        //load instrction from text into IR
        IR.OP = pas[PC];
        IR.L = pas[PC + 1];
        IR.M = pas[PC + 2];

        //increment PC
        PC = PC + 3;

        //execute cycle

        switch(IR.OP)   {
            //LIT 
            case 1:
                break;
            //OPR
            case 2:
                break;
            //LOD
            case 3:
                break;
            //STO
            case 4:
                break;
            //CAL
            case 5:
                break;
            //INC
            case 6:
                break;
            //JMP
            case 7:
                break;
            //JPC
            case 8:
                break;
            //SYS
            case 9:
                break;
        }

    }
    fclose(input);
}