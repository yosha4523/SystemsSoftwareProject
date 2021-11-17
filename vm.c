//Yosha Riley
//PM/0 VM
#include <stdio.h>
#include <string.h>
#include "compiler-1.h"

#define MAX_PAS_LENGTH 500

/*typedef struct IRstruct  {
    int OP;
    int L;
    int M;
} IRstruct;*/

int BP;     //Base pointer
int SP;     //Stack pointer
int PC;     //Program counter
int DP;     //Data pointer
int GP;     //Global pointer
int FREE;   //Heap pointer
int IC;     //Instruction counter
int pas[MAX_PAS_LENGTH];

int base(int L) {
    int  arb = BP;      //arb -> activation record base
    while (L > 0)   {   //find base L levels down
        arb = pas[arb - 1];
        L--;
    }

    return arb;
}

void print_execution(int line, char *opname, instruction *IR, int PC, int BP, int SP, int DP, int *pas, int GP)
{
	int i;
	// print out instruction and registers
	printf("%2d\t%s\t%d\t%d\t%d\t%d\t%d\t%d\t", line, opname, IR->l, IR->m, PC, BP, SP, DP);
	
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

void execute_program(instruction *code, int printFlag) {
    int lineNo;

    for(int i = 0; i < MAX_PAS_LENGTH; i++) {
        pas[i] = 0;
    }

    //load input into text 
    IC = 0;
    int i =0;
    while(code[i].opcode != -1){
        pas[IC] = code[i].opcode;
        IC++;
        pas[IC] = code[i].l;
        IC++;
        pas[IC] = code[i].m;
        IC++;
        i++;
    }

    //set initial CPU registers
    instruction IR;
    PC = 0;
    SP = MAX_PAS_LENGTH;
    GP = IC;
    DP = IC - 1;
    FREE = IC + 40;
    BP = IC;

    //set up output
    if(printFlag)
    {
        printf("\t\t\t\tPC\tBP\tSP\tDP\tdata\n");
        printf("Initial values:\t\t\t%d\t%d\t%d\t%d",PC, BP, SP, DP);
        for (int i = GP; i <= DP; i++)  {
            printf("%d ", pas[i]);
        }
        printf("\n");
    }

    //instruction cycle
    while(PC < IC)  {
        //fetch  cycle

        //load instrction from text into IR
        IR.opcode = pas[PC];
        IR.l = pas[PC + 1];
        IR.m = pas[PC + 2];

        //store line number to print later
        lineNo = PC / 3;
        //increment PC
        PC = PC + 3;
        
        //execute cycle
        switch(IR.opcode)   {
            //LIT 
            case 1:
                if(BP == GP) {
                    DP++;
                    pas[DP] = IR.m;
                }
                else    {
                    SP--;
                    pas[SP] = IR.m;
                }

                if(printFlag)   {
                    print_execution( lineNo, "LIT", &IR, PC, BP, SP, DP, pas, GP);
                }

                break;
            //OPR
            case 2:
                switch(IR.m)    {
                    //RTN
                    case 0:
                        SP = BP + 1;
                        BP = pas[SP - 3];
                        PC = pas[SP - 4];
                        
                        if(printFlag)   {
                            print_execution( lineNo, "RTN", &IR, PC, BP, SP, DP, pas, GP);
                        }

                        break;
                    //NEG
                    case 1:
                        if(BP == GP)    {
                            pas[DP] = pas[DP] * -1;
                        }
                        else    {
                            pas[SP] = pas[SP] * -1;
                        }

                        if(printFlag)   {
                            print_execution( lineNo, "NEG", &IR, PC, BP, SP, DP, pas, GP);
                        }

                        break;
                    //ADD
                    case 2:
                        if(BP == GP)    {
                            DP--;
                            pas[DP] = pas[DP] + pas[DP + 1];
                        }
                        else    {
                            SP++;
                            pas[SP] = pas[SP] + pas[SP - 1];
                        }

                        if(printFlag)   {
                            print_execution( lineNo, "ADD", &IR, PC, BP, SP, DP, pas, GP);
                        }

                        break;
                    //SUB
                    case 3:
                        if(BP == GP)    {
                            DP--;
                            pas[DP] = pas[DP] - pas[DP + 1];
                        }
                        else    {
                            SP++;
                            pas[SP] = pas[SP] - pas[SP - 1];
                        }

                        if(printFlag)   {
                            print_execution( lineNo, "SUB", &IR, PC, BP, SP, DP, pas, GP);
                        }

                        break;
                    //MUL
                    case 4:
                        if(BP == GP)    {
                            DP--;
                            pas[DP] = pas[DP] * pas[DP + 1];
                        }
                        else    {
                            SP++;
                            pas[SP] = pas[SP] * pas[SP - 1];
                        }

                        if(printFlag)   {
                            print_execution( lineNo, "MUL", &IR, PC, BP, SP, DP, pas, GP);
                        }

                        break;
                    //DIV
                    case 5:
                        if(BP == GP)    {
                            DP--;
                            pas[DP] = pas[DP] / pas[DP + 1];
                        }
                        else    {
                            SP++;
                            pas[SP] = pas[SP] / pas[SP - 1];
                        }

                        if(printFlag)   {
                            print_execution( lineNo, "DIV", &IR, PC, BP, SP, DP, pas, GP);
                        }

                        break;
                    //ODD
                    case 6:
                        if(BP == GP)    {
                            pas[DP] = pas[DP] % 2;
                        }
                        else    {
                           pas[SP] = pas[SP] % 2;
                        }

                        if(printFlag)   {
                            print_execution( lineNo, "ODD", &IR, PC, BP, SP, DP, pas, GP);
                        }

                        break;
                    //MOD
                    case 7:
                        if(BP == GP)    {
                            DP--;
                            pas[DP] = pas[DP] % pas[DP + 1];
                        }
                        else    {
                           SP++;
                           pas[SP] = pas[SP] % pas[SP - 1];
                        }

                        if(printFlag)   {
                            print_execution( lineNo, "MOD", &IR, PC, BP, SP, DP, pas, GP);
                        }

                        break;
                    //EQL
                    case 8:
                        if(BP == GP)    {
                            DP--;
                            pas[DP] = pas[DP] == pas[DP + 1];
                        }
                        else    {
                           SP++;
                           pas[SP] = pas[SP] == pas[SP - 1];
                        }

                        if(printFlag)   {
                            print_execution( lineNo, "EQL", &IR, PC, BP, SP, DP, pas, GP);
                        }

                        break;
                    //NEQ
                    case 9:
                        if(BP == GP)    {
                            DP--;
                            pas[DP] = pas[DP] != pas[DP + 1];
                        }
                        else    {
                           SP++;
                           pas[SP] = pas[SP] != pas[SP - 1];
                        }

                        if(printFlag)   {
                            print_execution( lineNo, "NEQ", &IR, PC, BP, SP, DP, pas, GP);
                        }

                        break;
                    //LSS
                    case 10:
                        if(BP == GP)    {
                            DP--;
                            pas[DP] = pas[DP] < pas[DP + 1];
                        }
                        else    {
                           SP++;
                           pas[SP] = pas[SP] < pas[SP - 1];
                        }

                        if(printFlag)   {
                            print_execution( lineNo, "LSS", &IR, PC, BP, SP, DP, pas, GP);
                        }

                        break;
                    //LEQ
                    case 11:
                        if(BP == GP)    {
                            DP--;
                            pas[DP] = pas[DP] <= pas[DP + 1];
                        }
                        else    {
                           SP++;
                           pas[SP] = pas[SP] <= pas[SP - 1];
                        }

                        if(printFlag)   {
                            print_execution( lineNo, "LEQ", &IR, PC, BP, SP, DP, pas, GP);
                        }

                        break;
                    //GTR
                    case 12:
                        if(BP == GP)    {
                            DP--;
                            pas[DP] = pas[DP] > pas[DP + 1];
                        }
                        else    {
                           SP++;
                           pas[SP] = pas[SP] > pas[SP - 1];
                        }

                        if(printFlag)   {
                            print_execution( lineNo, "GTR", &IR, PC, BP, SP, DP, pas, GP);
                        }

                        break;
                    //GEQ
                    case 13:
                        if(BP == GP)    {
                            DP--;
                            pas[DP] = pas[DP] >= pas[DP + 1];
                        }
                        else    {
                           SP++;
                           pas[SP] = pas[SP] >= pas[SP - 1];
                        }

                        if(printFlag)   {
                            print_execution( lineNo, "GEQ", &IR, PC, BP, SP, DP, pas, GP);
                        }
                        break;
                }
                break;
            //LOD
            case 3:
                if(BP == GP) {
                    DP++;
                    pas[DP] = pas[GP + IR.m];
                }
                else    {
                    if(base(IR.l) == GP) {
                        SP--;
                        pas[SP] = pas[GP + IR.m];
                    }
                    else    {
                        SP--;
                        pas[SP] = pas[base(IR.l) - IR.m];
                    }
                }

                if(printFlag)   {
                print_execution( lineNo, "LOD", &IR, PC, BP, SP, DP, pas, GP);
                }

                break;
            //STO
            case 4:
                if(BP == GP)    {
                    pas[GP + IR.m] = pas[DP];
                    DP--;
                }
                else    {
                    if(base(IR.l) == GP)    {
                        pas[GP + IR.m] = pas[SP];
                        SP++;
                    }
                    else    {
                        pas[base(IR.l) - IR.m] = pas[SP];
                        SP++;
                    }
                }

                if(printFlag)   {
                print_execution( lineNo, "STO", &IR, PC, BP, SP, DP, pas, GP);
                }

                break;
            //CAL
            case 5:
                pas[SP - 1] = 0;
                pas[SP - 2] = base(IR.l);
                pas[SP - 3] = BP;
                pas[SP - 4] = PC;
                BP = SP - 1;
                PC = IR.m;

                if(printFlag)   {
                print_execution( lineNo, "CAL", &IR, PC, BP, SP, DP, pas, GP);
                }

                break;
            //INC
            case 6:
                if(BP == GP)    {
                    DP = DP + IR.m;
                }
                else    {
                    SP = SP - IR.m;
                }

                if(printFlag)   {
                print_execution( lineNo, "INC", &IR, PC, BP, SP, DP, pas, GP);
                }

                break;
            //JMP
            case 7:
                PC = IR.m;

                if(printFlag)   {
                print_execution( lineNo, "JMP", &IR, PC, BP, SP, DP, pas, GP);
                }

                break;
            //JPC
            case 8:
                if(BP == GP)    {
                    if(pas[DP] == 0)    {
                        PC = IR.m;
                    }
                    DP--;
                }
                else    {
                    if(pas[SP] == 0)    {
                        PC = IR.m;
                    }
                    SP++;
                }

                if(printFlag)   {
                print_execution( lineNo, "JPC", &IR, PC, BP, SP, DP, pas, GP);
                }

                break;
            //SYS
            case 9:
                switch(IR.m)    {
                    case 1:
                        if(BP == GP)    {
                            printf("Top of Stack Value: %d\n", pas[DP]);
                            DP--;
                        }
                        else    {
                            printf("Top of Stack Value: %d\n", pas[SP]);
                            SP++;
                        }

                        if(printFlag)   {
                            print_execution( lineNo, "SYS", &IR, PC, BP, SP, DP, pas, GP);
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

                        if(printFlag)   {
                            print_execution( lineNo, "SYS", &IR, PC, BP, SP, DP, pas, GP);
                        }

                        break;
                    case 3:
                        if(printFlag)   {
                            print_execution( lineNo, "SYS", &IR, PC, BP, SP, DP, pas, GP);
                        }
                        break;
                }
                break;
        }
    }

    return;
}