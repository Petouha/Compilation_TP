#include"functions.h"

void err_div(){
    printf(":msgErrDiv0\n");
    printf("@string \"Erreur division par 0\\n\"\n");
    printf(":errDiv0\n");
    printf("\tconst ax,msgErrDiv0\n");
    printf("\tcallprintfs ax\n");
    printf("\tend\n");
}

void err_overflow(){
    printf(":msgErrOverflow\n");
    printf("@string \"Erreur dépassement de capacité\\n\"\n");
    printf(":errOverflow\n");
    printf("\tconst ax,msgErrOverflow\n");
    printf("\tcallprintfs ax\n");
    printf("\tend\n");
}

void start_asm(){
printf("\tconst ax,debut\n");
printf("\tjmp ax\n");
printf(":nl\n");
printf("@string \"\\n\"\n");
err_div();
err_overflow();
printf(":debut\n");
printf("\tconst bp,pile\n");
printf("\tconst sp,pile\n");
printf("\tconst ax,2\n");
printf("\tsub sp,ax\n");
printf(";Début du code effectué par yyparse()\n");
}

void end_asm(){
printf(";Fin du code effectué par yyparse()\n");
printf("\tcp ax,sp\n");
printf("\tcallprintfd ax\n");
printf("\tconst ax,nl\n");
printf("\tcallprintfs ax\n");
printf("\tpop ax\n");
printf("\tend\n");
printf(":pile\n");
printf("@int 0\n");
}


void addition(){
    printf("\tpop ax\n");
    printf("\tpop bx\n");
    printf("\tconst cx,errOverflow\n");
    printf("\tadd ax,bx\n");
    printf("\tjmpe cx\n");
    printf("\tpush ax\n");
}


void division(){
    printf("\tpop bx\n");
    printf("\tpop ax\n");
    printf("\tconst cx,errDiv0\n");
    printf("\tdiv ax,bx\n");
    printf("\tjmpe cx\n");
    printf("\tpush ax\n");
}

void multiplication(){
    printf("\tpop ax\n");
    printf("\tpop bx\n");
    printf("\tconst cx,errOverflow\n");
    printf("\tmul ax,bx\n");
    printf("\tjmpe cx\n");
    printf("\tpush ax\n");
}

void soustraction()
{
    printf("\tpop bx\n");
    printf("\tpop ax\n");
    printf("\tconst cx,errOverflow\n");
    printf("\tsub ax,bx\n");
    printf("\tjmpe cx\n");
    printf("\tpush ax\n");
}

void num(int number){
    printf("\tconst ax,%d\n",number);
    printf("\tpush ax\n");
}

int test_expr_int(int first, int second){
    if(first != NUM_T || second != NUM_T)
        return ERR_T;
    return NUM_T;
}

int test_expr_bool(int first, int second){
    if(first != BOOL_T || second != BOOL_T)
        return ERR_T;
    return BOOL_T;
}

void or(int label_num){
    char *jump = create_label("jump",label_num);
    char *end = create_label("end",label_num);
    printf("\tpop ax\n");
    printf("\tpop bx\n");
    printf("\tadd ax,bx\n");
    printf("\tconst cx,%s\n",jump);
    printf("\tconst bx,0\n");
    printf("\tcmp ax,bx\n");
    printf("\tjmpc cx\n");
    printf("\tconst ax,1\n");
    printf("\tpush ax\n");
    printf("\tconst ax,%s\n",end);
    printf("\tjmp ax\n");
    printf(":%s\n",jump);    
    printf("\tpush ax\n");
    printf(":%s\n",end);
}

void egal(int label_num){
    char *jump = create_label("jump",label_num);
    char *end = create_label("end",label_num);
    printf("\tpop ax\n");
    printf("\tpop bx\n");
    printf("\tcmp ax,bx\n");
    printf("\tconst cx,%s\n",jump);
    printf("\tjmpc cx\n");
    printf("\tconst ax,0\n");
    printf("\tpush ax\n");
    printf("\tconst ax,%s\n",end);
    printf("\tjmp ax\n");
    printf(":%s\n",jump);
    printf("\tconst ax,1\n");   
    printf("\tpush ax\n");
    printf(":%s\n",end);

}

char* create_label(char* label_name, int number){
    char* buffer = (char*)malloc(128 * sizeof(char));
    if(buffer == NULL){
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    if(snprintf(buffer,128,"%s:%d",label_name,number) == -1){
        perror("snprintf");
        exit(EXIT_FAILURE);
    }
    return buffer;
}

/*le not
pop bx
const ax,1
sub ax,bx
push ax
*/
