#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OP_END          0
#define OP_INC_DP       1
#define OP_DEC_DP       2
#define OP_INC_VAL      3
#define OP_DEC_VAL      4
#define OP_OUT          5
#define OP_IN           6
#define OP_JMP_FWD      7
#define OP_JMP_BCK      8

struct instruction_t {
    unsigned short item;
    unsigned short reference;
};

#define MAX_CMD  60000
#define MAX_DATA 30000
#define STACK_SIZE 512

static struct instruction_t Cmd[MAX_CMD];
static unsigned short Stack[STACK_SIZE];
static unsigned int SP = 0;

void push(unsigned short cp) { 
  Stack[SP++] = cp;
}
int pop() {    
  return Stack[--SP];
}

void readData() {
    unsigned short pc = 0, jmp_pc;
    unsigned char c;
    while (scanf("%c",&c) != EOF) {
        switch (c) {
            case '>': Cmd[pc].item = OP_INC_DP; break;
            case '<': Cmd[pc].item = OP_DEC_DP; break;
            case '+': Cmd[pc].item = OP_INC_VAL; break;
            case '-': Cmd[pc].item = OP_DEC_VAL; break;
            case '.': Cmd[pc].item = OP_OUT; break;
            case ',': Cmd[pc].item = OP_IN; break;
            case '[': Cmd[pc].item = OP_JMP_FWD;
                      push(pc);
                      break;
            case ']': jmp_pc = pop();
                      Cmd[pc].item =  OP_JMP_BCK;
                      Cmd[pc].reference = jmp_pc;
                      Cmd[jmp_pc].reference = pc;
                      break;
            default: Cmd[pc].item = c; break;
        }
        pc++;
    }
    Cmd[pc].item = OP_END;
}   

void interpretData() {
    unsigned char data[MAX_DATA]; 
    memset(data,0,MAX_DATA);
    unsigned char *data_ptr = data;
    unsigned short pc = 0;
    while (Cmd[pc].item != OP_END) {
        switch (Cmd[pc].item) {
            case OP_INC_DP: ++data_ptr; break;
            case OP_DEC_DP: --data_ptr; break;
            case OP_INC_VAL: ++*data_ptr; break;
            case OP_DEC_VAL: --*data_ptr; break;
            case OP_OUT: putchar(*data_ptr); break;
            case OP_IN: *data_ptr = (unsigned int)getchar(); break;
            case OP_JMP_FWD: if (!(*data_ptr)) { 
                                pc = Cmd[pc].reference; 
                             } 
                             break;
            case OP_JMP_BCK: if (*data_ptr) { 
                                pc = Cmd[pc].reference; 
                             } 
                             break;
        }
        pc++;
    }
}

int main() {
   readData();
   interpretData();

   return 0;
}

