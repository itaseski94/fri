#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LENGTH 9001
#define STACK_SIZE 2048

#define OPS_STACK_PUSH(A)    (OPS_STACK[OPS_N++] = A)
#define OPS_STACK_POP()      (OPS_STACK[--OPS_N])
#define OPS_STACK_EMPTY()    (OPS_N == 0)

#define VALS_STACK_PUSH(A)   (VALS_STACK[VALS_N++] = A)
#define VALS_STACK_POP()     (VALS_STACK[--VALS_N])
#define VALS_STACK_EMPTY()   (VALS_N == 0)


#define IS_EMPTY()           (EXPRESSION[N] == '\0')

static unsigned char EXPRESSION[MAX_LENGTH];
static unsigned char OPS_STACK[STACK_SIZE];
static long VALS_STACK[MAX_LENGTH];
static unsigned int  OPS_N = 0;
static unsigned int  VALS_N = 0;
static unsigned int  N = 0;

static void postfixNotation() {
  char digits[12];
  while (!IS_EMPTY()) {
        if (EXPRESSION[N] == '(') OPS_STACK_PUSH(EXPRESSION[N]);
        else if (EXPRESSION[N] == ')') { 
            while (!OPS_STACK_EMPTY() && OPS_STACK[OPS_N-1] != '(') {
                  VALS_STACK_PUSH(OPS_STACK_POP());
            }
            OPS_STACK_POP();
        }
        else if (EXPRESSION[N] == '+') { 
            while (!OPS_STACK_EMPTY() && OPS_STACK[OPS_N-1] != '(') {
                   VALS_STACK_PUSH(OPS_STACK_POP());
            }
            OPS_STACK_PUSH(EXPRESSION[N]);
        }
        else if (EXPRESSION[N] == '-') { 
            while (!OPS_STACK_EMPTY() && OPS_STACK[OPS_N-1] != '(') {
                   VALS_STACK_PUSH(OPS_STACK_POP());
            }
            OPS_STACK_PUSH(EXPRESSION[N]);
        }
        else if (EXPRESSION[N] == '*') {
            while (!OPS_STACK_EMPTY() && OPS_STACK[OPS_N-1] != '(' && 
                   (OPS_STACK[OPS_N-1] == '/' || OPS_STACK[OPS_N-1] == '*')) {
                   VALS_STACK_PUSH(OPS_STACK_POP());
            }
            OPS_STACK_PUSH(EXPRESSION[N]);
        }
        else if (EXPRESSION[N] == '/') {
            while (!OPS_STACK_EMPTY() && OPS_STACK[OPS_N-1] != '(' && 
                   (OPS_STACK[OPS_N-1] == '/' || OPS_STACK[OPS_N-1] == '*')) {
                   VALS_STACK_PUSH(OPS_STACK_POP());
            }
            OPS_STACK_PUSH(EXPRESSION[N]);
        }
        else if (EXPRESSION[N] >= '0' && EXPRESSION[N] <= '9') { 
            int i = 0;
            while (isdigit(EXPRESSION[N])) {
                digits[i++] = EXPRESSION[N++];
            }
            --N;
            digits[i] = '\0';
            long number;
            sscanf(digits,"%ld",&number);
            VALS_STACK_PUSH(number);
        }
        N++;  
  }
  while (!OPS_STACK_EMPTY()) {
        VALS_STACK_PUSH(OPS_STACK_POP());
  }
}

static long evaluateExpression() {
  long Stack[4096];
  int i = 0;
  long v;
  for (int in = 0; in < VALS_N; ++in) {
      switch (VALS_STACK[in]) {
          case '+': v = Stack[--i];
                    v = Stack[--i] + v;
                    Stack[i++] = v;
                    break;
          case '-': v = Stack[--i];
                    v = Stack[--i] - v;
                    Stack[i++] = v;
                    break;
          case '*': v = Stack[--i];
                    v = Stack[--i] * v;
                    Stack[i++] = v;
                    break;
          case '/': v = Stack[--i];
                    v = Stack[--i] / v;
                    Stack[i++] = v;
                    break;
          default : Stack[i++] = VALS_STACK[in];
      }
  }
  return Stack[--i];
}

int main() {

  fgets(EXPRESSION,MAX_LENGTH,stdin);
  postfixNotation();
  printf("%ld\n",evaluateExpression());

  return 0; 
}