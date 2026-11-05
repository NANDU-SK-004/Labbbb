#include <stdio.h>
#include <string.h>
#include <ctype.h>

char tempvariables[] = {'z', 'y', 'x', 'w' ,'v'};
int length, top = -1, count = 0, tvar = 0;

char input[20], tempinput[20];
char prearray[20];
char stack[20];
char threeaddress[10][20];
char concatarrray[20];

char *strrev(char *str)
{
    if (!str || !*str)
        return str;

    int i = strlen(str) - 1, j = 0;
    char ch;

    while (i > j)
    {
        ch = str[i];
        str[i] = str[j];
        str[j] = ch;
        j++;
        i--;
    }

    return str;
}

int prec(char op)
{
    switch (op)
    {
        case '+':
        case '-':
            return 1;

        case '*':
        case '/':
            return 2;
    }

    return 0;
}

int isoperator(char sym)
{
    if (sym == '+' || sym == '-' || sym == '*' || sym == '/')
        return 1;
    else
        return 0;
}

void push(char sym)
{
    stack[++top] = sym;
}

char pop()
{
    if (top == -1)
        return '\0';

    return stack[top--];
}

void del(char sym, int pos)
{
    int i, j, k, c = 0;

    for (j = 0; j < pos; j++)
        tempinput[j] = prearray[j];

    tempinput[j++] = tempvariables[tvar - 1];

    k = j;

    for (j = pos + 3; j < length; j++)
        tempinput[k++] = prearray[j];

    tempinput[k] = '\0';

    strcpy(prearray, tempinput);
    length = strlen(prearray);
}

void prefix()
{
    int i, k = 0;
    char popval;

    for (i = 0; i < length; i++)
    {
        if (isalnum(input[i]))
        {
            prearray[k++] = input[i];
        }
        else
        {
            while (top != -1 &&
                   prec(stack[top]) >= prec(input[i]))
            {
                prearray[k++] = pop();
            }

            push(input[i]);
        }
    }

    while (top != -1)
    {
        prearray[k++] = pop();
    }

    prearray[k] = '\0';
}

void generator(char op, char sym1, char sym2)
{
    int len = 0;

    concatarrray[len++] = tempvariables[tvar++];
    concatarrray[len++] = '=';
    concatarrray[len++] = sym1;
    concatarrray[len++] = op;
    concatarrray[len++] = sym2;
    concatarrray[len] = '\0';

    strcpy(threeaddress[count++], concatarrray);
}

int main()
{
    int i;

    printf("Enter the input expression: ");
    scanf("%19s", input);

    length = strlen(input);

    strcpy(input, strrev(input));

    prefix();

    strcpy(prearray, strrev(prearray));

    length = strlen(prearray);

    for (i = 0; i < length; i++)
    {
        if (isoperator(prearray[i]))
        {
            if ((isalnum(prearray[i + 1])) &&
                (isalnum(prearray[i + 2])))
            {
                generator(prearray[i],
                          prearray[i + 1],
                          prearray[i + 2]);

                del(prearray[i], i);

                i = -1;
            }
        }
    }

    printf("\nThree Address Code for the expression:\n");

    for (i = 0; i < count; i++)
        printf("%s\n", threeaddress[i]);

    return 0;
}

// ------------------------------------------------------------------------------------------OUTPUT-------------------------------------------------------------------------------

// Enter the input expression: a+b*c/d-e*f

//Three-address code for the expression:
// z=c/d
// y=b*z
// x=e*f
// w=y-x
// v=a+w
