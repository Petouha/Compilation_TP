#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

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

void or(int label_num);
void egal(int label_num);
void dif(int label_num);

void num(int number);

void start_asm();
void end_asm();

void err_div();
void err_mul();

char* create_label(char* label_name, int number);

#endif