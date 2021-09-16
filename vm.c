//Yosha Riley
#include <stdio.h>
#include <string.h>

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

void print_execution(int line, char *opname, IRstruct *IR, int PC, int BP, int SP, int DP, int *pas, int GP)
{
	int i;
	// print out instruction and registers
	printf("%2d\t%s\t%d\t%d\t%d\t%d\t%d\t%d\t", line, opname, IR->L, IR->M, PC, BP, SP, DP);
	
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
    char *opname[3];
    int lineNo;

    for(int i = 0; i < MAX_PAS_LENGTH; i++) {
        pas[i] = 0;
    }

    //load input into text 
    IC = 0;
    while(fscanf(input, "%i", &pas[IC]) != EOF){
        IC++;
    }

    fclose(input);

    //set initial CPU registers
    IRstruct IR;
    PC = 0;
    SP = MAX_PAS_LENGTH;
    GP = IC;
    DP = IC - 1;
    FREE = IC + 40;
    BP = IC;

    //set up output
    printf("\t\t\t\tPC\tBP\tSP\tDP\tdata\n");
    printf("Initial values:\t\t\t%d\t%d\t%d\t%d",PC, BP, SP, DP);
    for (int i = GP; i <= DP; i++)  {
        printf("%d ", pas[i]);
    }
    printf("\n");

    //instruction cycle
    while(PC < IC)  {
        //fetch  cycle

        //load instrction from text into IR
        IR.OP = pas[PC];
        IR.L = pas[PC + 1];
        IR.M = pas[PC + 2];

        //increment PC
        lineNo = PC / 3;
        PC = PC + 3;

        //execute cycle
        switch(IR.OP)   {
            //LIT 
            case 1:
                strncpy(*opname, "LIT", 3);
                if(BP == GP) {
                    DP++;
                    pas[DP] = IR.M;
                }
                else    {
                    SP--;
                    pas[SP] = IR.M;
                }
                break;
            //OPR
            case 2:
                switch(IR.M)    {
                    //RTN
                    case 0:
                        strncpy(*opname, "RTN", 3);
                        SP = BP + 1;
                        BP = pas[SP - 2];
                        PC = pas[SP - 3];
                        break;
                    //NEG
                    case 1:
                        strncpy(*opname, "NEG", 3);
                        if(BP == GP)    {
                            pas[DP] = pas[DP] * -1;
                        }
                        else    {
                            pas[SP] = pas[SP] * -1;
                        }
                        break;
                    //ADD
                    case 2:
                        strncpy(*opname, "ADD", 3);
                        if(BP == GP)    {
                            DP--;
                            pas[DP] = pas[DP] + pas[DP + 1];
                        }
                        else    {
                            SP++;
                            pas[SP] = pas[SP] + pas[SP - 1];
                        }
                        break;
                    //SUB
                    case 3:
                        strncpy(*opname, "SUB", 3);
                        if(BP == GP)    {
                            DP--;
                            pas[DP] = pas[DP] - pas[DP + 1];
                        }
                        else    {
                            SP++;
                            pas[SP] = pas[SP] - pas[SP - 1];
                        }
                        break;
                    //MUL
                    case 4:
                        strncpy(*opname, "MUL", 3);
                        if(BP == GP)    {
                            DP--;
                            pas[DP] = pas[DP] * pas[DP + 1];
                        }
                        else    {
                            SP++;
                            pas[SP] = pas[SP] * pas[SP - 1];
                        }
                        break;
                    //DIV
                    case 5:
                        strncpy(*opname, "DIV", 3);
                        if(BP == GP)    {
                            DP--;
                            pas[DP] = pas[DP] / pas[DP + 1];
                        }
                        else    {
                            SP++;
                            pas[SP] = pas[SP] / pas[SP - 1];
                        }
                        break;
                    //ODD
                    case 6:
                        strncpy(*opname, "ODD", 3);
                        if(BP == GP)    {
                            pas[DP] = pas[DP] % 2;
                        }
                        else    {
                           pas[SP] = pas[SP] % 2;
                        }
                        break;
                    //MOD
                    case 7:
                        strncpy(*opname, "MOD", 3);
                        if(BP == GP)    {
                            DP--;
                            pas[DP] = pas[DP] % pas[DP + 1];
                        }
                        else    {
                           SP++;
                           pas[SP] = pas[SP] % pas[SP - 1];
                        }
                        break;
                    //EQL
                    case 8:
                        strncpy(*opname, "EQL", 3);
                        if(BP == GP)    {
                            DP--;
                            pas[DP] = pas[DP] == pas[DP + 1];
                        }
                        else    {
                           SP++;
                           pas[SP] = pas[SP] == pas[SP - 1];
                        }
                        break;
                    //NEQ
                    case 9:
                        strncpy(*opname, "NEQ", 3);
                        if(BP == GP)    {
                            DP--;
                            pas[DP] = pas[DP] != pas[DP + 1];
                        }
                        else    {
                           SP++;
                           pas[SP] = pas[SP] != pas[SP - 1];
                        }
                        break;
                    //LSS
                    case 10:
                        strncpy(*opname, "LSS", 3);
                        if(BP == GP)    {
                            DP--;
                            pas[DP] = pas[DP] < pas[DP + 1];
                        }
                        else    {
                           SP++;
                           pas[SP] = pas[SP] < pas[SP - 1];
                        }
                        break;
                    //LEQ
                    case 11:
                        strncpy(*opname, "LEQ", 3);
                        if(BP == GP)    {
                            DP--;
                            pas[DP] = pas[DP] <= pas[DP + 1];
                        }
                        else    {
                           SP++;
                           pas[SP] = pas[SP] <= pas[SP - 1];
                        }
                        break;
                    //GTR
                    case 12:
                        strncpy(*opname, "GTR", 3);
                        if(BP == GP)    {
                            DP--;
                            pas[DP] = pas[DP] > pas[DP + 1];
                        }
                        else    {
                           SP++;
                           pas[SP] = pas[SP] > pas[SP - 1];
                        }
                        break;
                    //GEQ
                    case 13:
                        strncpy(*opname, "GEQ", 3);
                        if(BP == GP)    {
                            DP--;
                            pas[DP] = pas[DP] >= pas[DP + 1];
                        }
                        else    {
                           SP++;
                           pas[SP] = pas[SP] >= pas[SP - 1];
                        }
                        break;
                }
                break;
            //LOD
            case 3:
                strncpy(*opname, "LOD", 3);
                if(BP == GP) {
                    DP++;
                    pas[DP] = pas[GP + IR.M];
                }
                else    {
                    if(base(IR.L) == GP) {
                        SP--;
                        pas[SP] = pas[GP + IR.M];
                    }
                    else    {
                        SP--;
                        pas[SP] = pas[base(IR.L) - IR.M];
                    }
                }
                break;
            //STO
            case 4:
                strncpy(*opname, "STO", 3);
                if(BP == GP)    {
                    pas[GP + IR.M] = pas[DP];
                    DP--;
                }
                else    {
                    if(base(IR.L) == GP)    {
                        pas[GP + IR.M] = pas[SP];
                        SP++;
                    }
                    else    {
                        pas[base(IR.L) - IR.M] = pas[SP];
                        SP++;
                    }
                }
                break;
            //CAL
            case 5:
                strncpy(*opname, "CAL", 3);
                pas[SP - 1] = base(IR.L);
                pas[SP - 2] = BP;
                pas[SP - 3] = PC;
                BP = SP - 1;
                PC = IR.M;
                break;
            //INC
            case 6:
                strncpy(*opname, "INC", 3);
                if(BP == GP)    {
                    DP = DP + IR.M;
                }
                else    {
                    SP = SP - IR.M;
                }
                break;
            //JMP
            case 7:
                strncpy(*opname, "JMP", 3);
                PC = IR.M;
                break;
            //JPC
            case 8:
                strncpy(*opname, "JPC", 3);
                if(BP == GP)    {
                    if(pas[DP] == 0)    {
                        PC = IR.M;
                    }
                    DP--;
                }
                else    {
                    if(pas[SP] == 0)    {
                        PC = IR.M;
                    }
                    SP++;
                }
                break;
            //SYS
            case 9:
                strncpy(*opname, "SYS", 3);
                switch(IR.M)    {
                    case 1:
                        if(BP == GP)    {
                            printf("Top of Stack Value: %d\n", pas[DP]);
                            DP--;
                        }
                        else    {
                            printf("Top of Stack Value: %d\n", pas[SP]);
                            SP++;
                        }
                        break;
                    case 2:
                        if(BP == GP)    {
                            DP++;
                            printf("Please Enter an Integer: ");
                            scanf("%d", &pas[DP]);
                        }
                        else    {
                            SP--;
                            printf("Please Enter an Integer: ");
                            scanf("%d", &pas[SP]);
                        }
                        break;
                    case 3:
                        break;
                }
                break;
        }

        print_execution( lineNo, *opname, &IR, PC, BP, SP, DP, pas, GP);
    }

    return;
}