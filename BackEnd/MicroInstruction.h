#ifndef MICROINSTRUCTION_H_
#define MICROINSTRUCTION_H_

#include "MicroProcessor.h"


#define MAX_TOK_LEN 20 //MAX TOKEN LENGHT
#define MAX_LABEL_LEN 20
#define MAX_OP_LEN 500


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
Memory Op[MAX_OP_LEN];


//define functions used
int to_opcode();
int is_instruction();
void micro_main();
void Init_labels();
void Increase_O_pos(char*);
void get_token();
void To_Start();
void Append(int );
int Op_val(char );
int Find_label(char*);
void print(Memory* , int);

#endif
