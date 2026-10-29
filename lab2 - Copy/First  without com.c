#include <stdio.h>
#include <string.h>
#include <ctype.h>

char production[10][20];
char non_terminal[10][5];
int n, nt_count = 0;

int findNT(char *s)
{
    int i;
    for (i = 0; i < nt_count; i++)
        if (strcmp(non_terminal[i], s) == 0)
            return i;
    return -1;
}

void add(char *s, char c)
{
    if (strchr(s, c) == NULL) {
        int len = strlen(s);
        s[len] = c;
        s[len + 1] = '\0';
    }
}

void first(char *nt, char *result)
{
    int i, j;
    char lhs[5], rhs[20], symbol[5];
    int pos, nullable;

    for (i = 0; i < n; i++) {
        strcpy(lhs, production[i]);
        pos = 0;

        while (lhs[pos] != '=' && lhs[pos] != '\0')
            pos++;

        if (lhs[pos] == '\0')
            continue;

        lhs[pos] = '\0';

        if (strcmp(lhs, nt) != 0)
            continue;

        strcpy(rhs, production[i] + pos + 1);

        if (rhs[0] == '$') {
            add(result, '$');
            continue;
        }

        j = 0;
        while (rhs[j] != '\0') {
            int k = 0;

            symbol[k++] = rhs[j++];

            if (rhs[j] == '\'')
                symbol[k++] = rhs[j++];

            symbol[k] = '\0';

            if (!isupper(symbol[0])) {
                add(result, symbol[0]);
                break;
            }

            {
                char temp[20] = "";
                int index = findNT(symbol);

                if (index == -1)
                    break;

                first(symbol, temp);

                nullable = strchr(temp, '$') != NULL;

                for (k = 0; temp[k] != '\0'; k++)
                    if (temp[k] != '$')
                        add(result, temp[k]);

                if (!nullable)
                    break;

                if (rhs[j] == '\0')
                    add(result, '$');
            }
        }
    }
}

int main()
{
    int i, pos;
    char nt[5], result[20];

    printf("Enter number of productions: ");
    scanf("%d", &n);

    printf("Enter productions (use $ for epsilon):\n");

    for (i = 0; i < n; i++) {
        scanf("%s", production[i]);

        pos = 0;
        while (production[i][pos] != '=' &&
               production[i][pos] != '\0')
            pos++;

        if (production[i][pos] == '\0')
            continue;

        production[i][pos] = '\0';

        if (findNT(production[i]) == -1)
            strcpy(non_terminal[nt_count++],
                   production[i]);

        production[i][pos] = '=';
    }

    printf("Find FIRST of: ");
    scanf("%4s", nt);

    strcpy(result, "");
    first(nt, result);

    printf("FIRST(%s) = { ", nt);
    for (i = 0; result[i] != '\0'; i++)
        printf("%c ", result[i]);
    printf("}\n");

    printf("Tokenized Output Style:\n");

    for (i = 0; result[i] != '\0'; i++)
        if (result[i] != '$')
            printf("Terminal: %c\n", result[i]);

    i = 0;
    for (pos = 0; result[pos] != '\0'; pos++)
        if (result[pos] != '$')
            i++;

    printf("Total number of tokens = %d\n", i);

    return 0;
}


/*
A=aB
B=b

S=AB
A=a
A=#
B=b

S=Aa
A=#
B=b

S=Aa
S=Bb
A=c
A=#
B=d

E=T
E=(F)
F=*a
F=#
T=*a
T=#

E=TE'
T=+
T=#
E'=*a
E'=#
*/
