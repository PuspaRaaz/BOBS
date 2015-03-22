#ifndef MICROINSTRUCTION_H_
#define MICROINSTRUCTION_H_

#include "MicroProcessor.h"


#define MAX_TOK_LEN 20 //MAX TOKEN LENGHT
#define MAX_LABEL_LEN 20



typedef enum {
    INSTRUCTION,REGMEM,NUMBER,LABEL,
    INVALID,DELIMETER,
    ALPHANUM,ALPHA,
    EOS
}TYPES;
TYPES token_t;

typedef struct {
    char name[20];
    int addr;
}label;

//the list of labels in the code
label* Label_list;
//counter for label count
int Label_count;

//define the actual input and token read
char* input;
char* token;
char* start;

//opcode position
int Op_count;

//define functions used
int to_opcode();                                        //Covert to opcode
void Init_labels();                                     //initialize labels at the start
void Increase_O_pos(char* instruction);                 //Increase opcode pos used for label initialization
void get_token();                                       //get the current token
void To_Start();                                        //goto the start of the instruction
void Append(int opcode);                                //Append the opcode
int Op_val(char in);                                    //return opcode value for different registers
int Find_label(char* name);                             //find the label of the given name

void micro_main(char* instructions, FILE* outfile);     //main function of MicroInstruction
void print(Memory* in ,int c,FILE* outfile);            //print the opcode in a file outfile

#endif
