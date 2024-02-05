#include <stdio.h>
#include <stdbool.h>

typedef enum 
{
    NUM_T, BOOL_T,ERR_T
}t_synth;

int test_expr_int(int first, int second);
int test_expr_bool(int first, int second);

void addition();
void soustraction();
void multiplication();
void division();

void or();

void num(int number);

void start_asm();
void end_asm();

void err_div();
void err_mul();