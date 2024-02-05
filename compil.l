%{
#include "functions.h"
#include "compil.tab.h"
#include<stdio.h>
#include<stdlib.h>
int strtoEntier(const char *s);
%}

%option noyywrap
%%
"+"|"-"|"/"|"*"|"("|")" {return yytext[0];}

[1-9][0-9]*|"0" {yylval.entier=strtoEntier(yytext);return NUM;}

[[:blank:]] {}

"!=" {return DIF;}
"&&" {return AND;}
"==" {return EGAL;}
"||" {return OR;}

"true" {return TRUE;}
"false" {return FALSE;}

. {fprintf(stderr,"caractère non souhaité : %c\n",yytext[0]);}
\n {}
%%


int strtoEntier(const char * s){
    return strtol(s,NULL,10);
}