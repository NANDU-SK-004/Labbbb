#include <stdio.h>
#include <ctype.h>
#include <string.h>

int k_count = 0, i_count = 0;

void keyword(char str[10])
{
    if(strcmp("for",str)==0 || strcmp("while",str)==0 ||
       strcmp("do",str)==0 || strcmp("int",str)==0 ||
       strcmp("float",str)==0 || strcmp("char",str)==0 ||
       strcmp("double",str)==0 || strcmp("static",str)==0 ||
       strcmp("switch",str)==0 || strcmp("case",str)==0 ||
       strcmp("if",str)==0 || strcmp("else",str)==0 ||
       strcmp("break",str)==0 || strcmp("continue",str)==0||
       strcmp("return",str)==0 || strcmp("void",str)==0)
    {
        printf("\n%s is a keyword\n",str);
        k_count++;
    }
    else
    {
        printf("\n%s is an identifier\n",str);
        i_count++;
    }
}

int main()
{
    FILE *f1, *f2, *f3;
    char c, str[10];
    int num[100], lineno=0, tokenvalue=0;
    int i=0, k=0, count=0, s_count=0;

    f1 = fopen("input.txt","r");
    f2 = fopen("identifier","w");
    f3 = fopen("special char","w");

    if(f1==NULL || f2==NULL || f3==NULL)
    {
        printf("Error opening file!");
        return 1;
    }

    while((c=getc(f1))!=EOF)
    {
        if(isdigit(c))
        {
            tokenvalue=c-'0';
            c=getc(f1);

            while(isdigit(c))
            {
                tokenvalue=tokenvalue*10+c-'0';
                c=getc(f1);
            }

            num[i++]=tokenvalue;
            ungetc(c,f1);
            count=i;
        }
        else if(isalpha(c))
        {
            putc(c,f2);
            c=getc(f1);

            while(isdigit(c)||isalpha(c)||c=='_'||c=='$')
            {
                putc(c,f2);
                c=getc(f1);
            }

            putc(' ',f2);
            ungetc(c,f1);
        }
        else if(c==' '||c=='\t')
            printf(" ");
        else if(c=='\n')
            lineno++;
        else
            putc(c,f3);
    }
    if(lineno > 0)
        lineno++;
    fclose(f1);
    fclose(f2);
    fclose(f3);

    printf("\nThe no's in the program are:");

    for(i=0;i<count;i++)
        printf("%d\t",num[i]);

    f2=fopen("identifier","r");
    k=0;

    printf("\nThe keywords and identifiers are:");

    while((c=getc(f2))!=EOF)
    {
        if(c!=' ')
            str[k++]=c;
        else
        {
            str[k]='\0';
            keyword(str);
            k=0;
        }
    }

    fclose(f2);

    s_count=0;
    f3=fopen("special char","r");

    printf("\nThe special characters are:");

    while((c=getc(f3))!=EOF)
    {
        if(c!='\n' && c!='\r')
        {
            printf("%c",c);
            s_count++;
        }
    }

    fclose(f3);

    printf("\n");
    printf("\nTotal no. of lines are:%6d\n",lineno);
    printf("\nCount of numbers are:%6d\n",count);
    printf("\nTotal no. of keywords are:%6d\n",k_count);
    printf("\nTotal no. of identifiers are:%6d\n",i_count);
    printf("\nTotal no. of special characters are:%6d\n",s_count);

    return 0;
}




// input.txt

// int main()
// {
//     int a = 5;
//     int b = 3;
//     float sum = 8;
//     printf(a);
//     return 0;
// }


// --------------------------------------------------------------------------------------------OUTPUT-------------------------------------------------------------------------------------------------
// identifier.txt
// int main int a int b float sum printf a return 

// specialcharacter.txt
// ()
// {
// =;
// =;
// =;
// ();
// ;
// }

// output                               
// The no's in the program are:5   3       8       0
// The keywords and identifiers are:
// int is a keyword

// main is an identifier

// int is a keyword

// a is an identifier

// int is a keyword

// b is an identifier

// float is a keyword

// sum is an identifier

// printf is an identifier

// a is an identifier

// return is a keyword

// The special characters are:(){=;=;=;();;}

// Total no. of lines are:     8

// Count of numbers are:     4

// Total no. of keywords are:     5

// Total no. of identifiers are:     6

// Total no. of special characters are:    14

