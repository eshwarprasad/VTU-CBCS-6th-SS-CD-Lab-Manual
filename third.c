#include <stdio.h>
#include<stdlib.h>
#include<string.h>
char STACK[20]="\0";
int TOP=-1;
int B_ptr = 0;
char BUFFER[20],G_prod[20];
char table [4][3][10] =
{
"NT", "a","b",
"A", "aBa","Error",
"B", "Error","bB",
"B", "Error","ε",
};
char pop()
{
char ch;
ch = STACK[TOP--];
return ch;
}
void push(char ch)
{
STACK[++TOP] = ch;
}
void stack_content()
{
if (TOP != -1)
{
int i = 0;
printf("\nstack content: ");
while(i <= TOP)
{
printf("%c",STACK[i++]);
}
printf("\n");
}
return;
}
int isterm(char c)
{
if (c >= 'a' && c <= 'z')
return 1;
else
return 0;
}
int Parser_table(char stack_top,char buf_value,int flag)
{
int r,c;
switch(stack_top)
{
case 'A' : r = 1; break;
case 'B' : if(flag<=5) r = 2; else r = 3;
}
switch(buf_value)
{
case 'a' : c = 1; break;
case 'b' : c = 2;
}
if (strcmp(table[r][c],"error") == 0)
return 0;
if (strcmp(table[r][c],"ε") != 0)
{
strcpy(G_prod,table[r][c]);
}
return 1;
}
int main()
{
int i,j,stln;
static int flag;
printf("LL(1) PARSER TABLE \n");
for(i=0;i<3;i++)
{
for(j=0;j<3;j++)
{
printf("%s\t",table[i][j]);
}
printf("\n");
}
printf("\n");
printf("ENTER THE STRING into the Buffer and also give a ';' as the terminator: ");
scanf("%s",BUFFER);
printf("\n THE STRING in the Buffer is %s",BUFFER);
if(BUFFER[strlen(BUFFER)-1] != ';')
{
printf("END OF STRING MARKER SHOULD BE ';'");
//getch();
exit(0);
}
push('$');
push('A');
while(STACK[TOP] != '$' && flag<=7) // Stack is not Empty
{
flag++;
if (STACK[TOP] == BUFFER[B_ptr]) // X is a
{
printf("\n1.The poped item is %c",pop());
B_ptr++;
}
else if (isterm(STACK[TOP])) // is X is terminal
{
printf("\n2. $ %c",STACK[TOP]);
printf("\t Error in Parsing \n");
}
else if (!Parser_table(STACK[TOP],BUFFER[B_ptr],flag))
printf("3. Error Entry in Parse Table ");
else if (Parser_table(STACK[TOP],BUFFER[B_ptr],flag))
{
if (flag < 5 && strcmp(G_prod,"?") != 0)
{
stack_content();
printf("\n4. flag = %d * %s*\t",flag,G_prod);
pop();
stln = strlen(G_prod);
for(i=stln-1;i>=0;i--)
push(G_prod[i]);
stack_content();
}
else
{
stack_content();
printf("\n4.1 flag = %d *reduce by %s*",flag,"B->ε"); pop();
B_ptr++;
}
}
}
if (STACK[TOP] == '$')
printf("\n** The string is accepted **");
}
