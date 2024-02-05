#include <stdio.h>
#include <stdbool.h>

typedef enum 
{
    NUM_T, BOOL_T,ERR_T
}t_synth;

int test_expr(int first, int second);


void addition();
void soustraction();
void multiplication();
void division();
void num(int number);
void start_asm();
void end_asm();
void err_div();
void err_mul();