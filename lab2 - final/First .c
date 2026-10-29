
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Global variables
char production[10][20];
char non_terminal[10][5];
int n, nt_count = 0;


// Find non-terminal
int findNT(char *s)
{
    int i;

    for (i = 0; i < nt_count; i++) {
        if (strcmp(non_terminal[i], s) == 0) {
            return i;
        }
    }

    return -1;
}


// Add character without duplication
void add(char *s, char c)
{
    if (strchr(s, c) == NULL) {
        int len = strlen(s);
        s[len] = c;
        s[len + 1] = '\0';
    }
}


// Calculate FIRST set
void first(char *nt, char *result)
{
    int i, j;
    char lhs[5], rhs[20], symbol[5];
    int pos, nullable;

    // Check all productions
    for (i = 0; i < n; i++) {

        // Copy production to lhs
        strcpy(lhs, production[i]);
        pos = 0;

        // Find equal sign
        while (lhs[pos] != '=' && lhs[pos] != '\0') {
            pos++;
        }
        //Skip invalid productions
        if (lhs[pos] == '\0') {
            continue;
        }

        // Separate left-hand side
        lhs[pos] = '\0';

        // Match requested non-terminal
        if (strcmp(lhs, nt) != 0) {
            continue;
        }

        // Copy right-hand side
        strcpy(rhs, production[i] + pos + 1);

        // Check epsilon
        if (rhs[0] == '$') {
            add(result, '$');
            continue;
        }

        j = 0;

        // Read symbols from right-hand side
        while (rhs[j] != '\0') {
            int k = 0;

            symbol[k++] = rhs[j++];

            if (rhs[j] == '\'') {
                symbol[k++] = rhs[j++];
            }

            symbol[k] = '\0';

            // Check terminal
            if (!isupper((unsigned char)symbol[0])) {
                add(result, symbol[0]);
                break;
            }

            // Calculate FIRST of non-terminal
            {
                char temp[20] = "";
                int index = findNT(symbol);

                if (index == -1) {
                    break;
                }

                first(symbol, temp);

                // Check epsilon in FIRST set
                nullable = strchr(temp, '$') != NULL;

                // Add terminals from FIRST set
                for (k = 0; temp[k] != '\0'; k++) {
                    if (temp[k] != '$') {
                        add(result, temp[k]);
                    }
                }

                if (!nullable) {
                    break;
                }

                if (rhs[j] == '\0') {
                    add(result, '$');
                }
            }
        }
    }
}


// Main
int main()
{
    int i, pos;
    char nt[5], result[20];

    // Input number of productions
    printf("Enter number of productions: ");
    scanf("%d", &n);

    // Input grammar productions
    printf("Enter productions (use $ for epsilon):\n");

    for (i = 0; i < n; i++) {
        scanf("%19s", production[i]);

        // Find equal sign
        pos = 0;

        while (production[i][pos] != '=' &&
               production[i][pos] != '\0') {
            pos++;
        }

        // Skip invalid production
        if (production[i][pos] == '\0') {
            continue;
        }

        // Separate left-hand side
        production[i][pos] = '\0';

        // Store unique non-terminals
        if (findNT(production[i]) == -1) {
            strcpy(non_terminal[nt_count++],
                   production[i]);
        }

        // Restore equal sign
        production[i][pos] = '=';
    }

    // Input non-terminal
    printf("Find FIRST of: ");
    scanf("%4s", nt);

    // Initialize result
    strcpy(result, "");

    // Calculate FIRST set
    first(nt, result);

    // Display FIRST set
    printf("FIRST(%s) = { ", nt);

    for (i = 0; result[i] != '\0'; i++) {
        printf("%c ", result[i]);
    }

    printf("}\n");

    // Display terminal tokens
    printf("Tokenized Output Style:\n");

    for (i = 0; result[i] != '\0'; i++) {
        if (result[i] != '$') {
            printf("Terminal: %c\n", result[i]);
        }
    }

    // Count terminal tokens
    i = 0;

    for (pos = 0; result[pos] != '\0'; pos++) {
        if (result[pos] != '$') {
            i++;
        }
    }

    // Display total tokens
    printf("Total number of tokens = %d\n", i);

    return 0;
}

/*

S=AB
A=a
A=$
B=b

E=TE'
T=+
T=#
E'=*a
E'=#
*/
