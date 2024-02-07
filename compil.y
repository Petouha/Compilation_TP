%{
#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
int yylex();    
void yyerror(const char* s){
    fprintf(stderr,"%s\n",s);
}

int label_number = 0;

%}

%union{
    int entier;
    t_synth synth;
}

%type<synth> EXPR

%token<entier> NUM
%token AND EGAL DIF TRUE FALSE OR


%left EGAL DIF
%left OR
%left AND
%left '+' '-'
%left '*' '/'

%start E

%%
E: EXPR{
    switch($1){
        case ERR_T: fprintf(stderr,"Erreur de types, résultat peut être incorrect\n");
    }
};

EXPR: EXPR '+' EXPR {
    if(test_expr_int($1,$3) == ERR_T){
            $$=ERR_T;
        } else {
            $$=NUM_T;
            addition();
        }
    }
    | EXPR '-' EXPR {
        if(test_expr_int($1,$3) == ERR_T){
            $$=ERR_T;
        } else {
            $$=NUM_T;
            soustraction();
        }
    }
    | EXPR '*' EXPR {
        if(test_expr_int($1,$3) == ERR_T){
            $$=ERR_T;
        } else {
            $$=NUM_T;
            multiplication();
        }
    }
    | EXPR '/' EXPR {
        if(test_expr_int($1,$3) == ERR_T){
            $$=ERR_T;
        } else {
            $$=NUM_T;
            division();
        }
    }
    | EXPR AND EXPR {
        if(test_expr_bool($1,$3) == ERR_T){
            $$=ERR_T;
        } else {
            $$=BOOL_T;
            multiplication();
        }
    }
    | EXPR OR EXPR  {
        if(test_expr_bool($1,$3) == ERR_T){
            $$=ERR_T;
        } else {
            $$=BOOL_T;
            or();
        }
    }
    | EXPR EGAL EXPR {}
    | EXPR DIF EXPR {}
    
    | '(' EXPR ')'  {}
    | NUM           {num($1);$$=NUM_T;}
    | TRUE          {$$=BOOL_T;num(1);}
    | FALSE         {$$=BOOL_T;num(0);}
    ;
%%
int main(void){
    start_asm();    
    yyparse();
    end_asm();
    return EXIT_SUCCESS;
}