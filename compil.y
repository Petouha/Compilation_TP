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
EXPR: EXPR '+' EXPR {
        if( ( $$=test_expr($1,$3) ) != ERR_T)
            addition();
    }
    | EXPR '-' EXPR {
        if( ( $$=test_expr($1,$3) ) != ERR_T)
            soustraction();
    }
    | EXPR '*' EXPR {
        if( ( $$=test_expr($1,$3) ) != ERR_T)
            multiplication();
    }
    | EXPR '/' EXPR {
        if( ( $$=test_expr($1,$3) ) != ERR_T)
            division();
    }
    | EXPR AND EXPR
    | '(' EXPR ')'  
    | NUM           {num($1);$$=NUM_T;}
    | TRUE          {$$=BOOL_T;num(1);}
    | FALSE         {$$=BOOL_T;num(2);}
    ;
%%
int main(void){
    start_asm();    
    yyparse();
    end_asm();
    return EXIT_SUCCESS;
}