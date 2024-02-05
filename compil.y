%{
#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
int yylex();    
void yyerror(const char* s){
    fprintf(stderr,"%s\n",s);
}
%}

%union{
    int entier;
    t_synth synth;
}

%type<synth> EXPR

%token<entier> NUM
%token AND EGAL DIF TRUE FALSE

%left EGAL DIF
%left '+' '-'
%left '*' '/'

%start EXPR

%%
EXPR: EXPR '+' EXPR {addition();}
    | EXPR '-' EXPR {soustraction();}
    | EXPR '*' EXPR {multiplication();}
    | EXPR '/' EXPR {division();}
    | EXPR AND EXPR
    | '(' EXPR ')'  
    | NUM           {num($1);$$=NUM_T;}
    ;
%%
int main(void){
    start_asm();    
    yyparse();
    end_asm();
    return EXIT_SUCCESS;
}