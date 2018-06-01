%{
#include<stdio.h>
int id=0,op=0,b=0;
%}
%option noyywrap
%%
[a-zA-Z0-9]*[a-zA-Z]* {id++;printf("\t");ECHO;}
[+|-|*|/] {op++;printf("\t");ECHO;}
"(" b++;
")" b--;
%%
main()
{
printf("enter arthimetic expression \n");
yylex();
if((op+1==id) && b==0)
{
printf("valid expression\n");
printf("No of Identifers=%d\n",id);
printf("No of operators=%d\n",op);
}
else
printf("invalid expression\n");
}
