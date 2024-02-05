#include <stdio.h>

typedef enum 
{
    NUM_T, BOOL_T,ERR_T
}t_synth;

void addition();
void soustraction();
void multiplication();
void division();
void num(int number);
void start_asm();
void end_asm();
void err_div();
void err_mul();