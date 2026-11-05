
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

char ip_sym[15], stack[15];
int ip_ptr=0, st_ptr=0, len, i;
char temp[2], temp2[2];
char act[15];

void check();

int main()
{
    printf("\n\t SHIFT REDUCE PARSER\n");

    printf("\n GRAMMER\n");
    printf("\n E->E+E\n E->E/E");
    printf("\n E->E*E\n E->a|b");

    printf("\n Enter the input symbol:");
    scanf("%14s", ip_sym);

    printf("\n\t Stack Implementation table");
    printf("\n Stack\t\t input symbol\t action");
    printf("\n $\t\t%s$\t\t--", ip_sym);

    strcpy(act, "Shift ");

    temp[0]=ip_sym[ip_ptr];
    temp[1]='\0';
    strcat(act, temp);

    len=strlen(ip_sym);

    for(i=0; i<len; i++)
    {
        stack[st_ptr]=ip_sym[ip_ptr];
        stack[st_ptr+1]='\0';

        ip_sym[ip_ptr]=' ';
        ip_ptr++;

        printf("\n $%s\t\t%s$\t\t%s", stack, ip_sym, act);

        strcpy(act, "Shift ");

        temp[0]=ip_sym[ip_ptr];
        temp[1]='\0';
        strcat(act, temp);

        check();
        st_ptr++;
    }

    st_ptr++;
    check();

    return 0;
}

void check()
{
    int flag=0;
    char temp3[15];

    temp2[0]=stack[st_ptr];
    temp2[1]='\0';

    if((!strcmp(temp2,"a")) || (!strcmp(temp2,"b")))
    {
        stack[st_ptr]='E';

        if(!strcmp(temp2,"a"))
            printf("\n $%s\t\t%s$\t\tREDUCE E->a",stack,ip_sym);
        else
            printf("\n $%s\t\t%s$\t\tREDUCE E->b",stack,ip_sym);

        flag=1;
    }

    if((!strcmp(temp2,"+")) || (!strcmp(temp2,"*")) || (!strcmp(temp2,"/")))
        flag=1;

    if((!strcmp(stack,"E+E")) || (!strcmp(stack,"E/E")) || (!strcmp(stack,"E*E")))
    {
        strcpy(temp3,stack);
        strcpy(stack,"E");
        st_ptr=0;

        if(!strcmp(temp3,"E+E"))
            printf("\n $%s\t\t%s$\t\tREDUCE E->E+E",stack,ip_sym);
        else if(!strcmp(temp3,"E/E"))
            printf("\n $%s\t\t%s$\t\tREDUCE E->E/E",stack,ip_sym);
        else
            printf("\n $%s\t\t%s$\t\tREDUCE E->E*E",stack,ip_sym);

        flag=1;
    }

    if(!strcmp(stack,"E") && ip_ptr==len)
    {
        printf("\n $%s\t\t%s$\t\tACCEPT",stack,ip_sym);
        exit(0);
    }

    if(flag==0)
    {
        printf("\n %s\t\t%s\t\tREJECT",stack,ip_sym);
        exit(0);
    }

    return;
}


// -------------------------------------------------------------------------------------------OUTPUT-----------------------------------------------------------------------------
//            SHIFT REDUCE PARSER

//  GRAMMER

//  E->E+E
//  E->E/E
//  E->E*E
//  E->a|b
//  Enter the input symbol:a+a*b

//          Stack Implementation table
//  Stack           input symbol    action
//  $              a+a*b$          --
//  $a              +a*b$          Shift a
//  $E              +a*b$          REDUCE E->a
//  $E+              a*b$          Shift +
//  $E+a              *b$          Shift a
//  $E+E              *b$          REDUCE E->a
//  $E                *b$          REDUCE E->E+E
//  $E*                b$          Shift *
//  $E*b                $          Shift b
//  $E*E                $          REDUCE E->b
//  $E                  $          REDUCE E->E*E
//  $E                  $          ACCEPT
