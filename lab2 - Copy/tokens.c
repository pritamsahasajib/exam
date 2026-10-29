#include <stdio.h>
#include <ctype.h>
#include <string.h>

const char *keywords[] = {
    "auto", "break", "case", "char", "const", "continue", "default", "do",
    "double", "else", "enum", "extern", "float", "for", "goto", "if",
    "int", "long", "register", "return", "short", "signed", "sizeof", "static",
    "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while"
};

    //char *keywords[] = { "int", "char", "float", "double", "if", "else", "for", "while", "return", "void"};

int isKeyword(char str[]) {
    for (int i = 0; i < 32; i++) {
        if (strcmp(keywords[i], str) == 0) {
            return 1;
        }
    }
    return 0;
}

int main() {
    char input[1000];
    char ch;
    int index = 0;
    int token_count = 0;

    printf("Enter code (End your input with '$'):\n\n");

    while ((ch = getchar()) != '$' && index < 999) {
        input[index++] = ch;
    }
    input[index] = '\0';

    printf("\n--- Output Tokens ---\n");

    int i = 0;

    while (input[i] != '\0') {

        // Skip preprocessor line
        if (input[i] == '#' &&
            (i == 0 || input[i - 1] == '\n')) {
            while (input[i] != '\0' && input[i] != '\n') {
                i++;
            }
            continue;
        }

        // Skip spaces
        if (isspace((unsigned char)input[i])) {
            i++;
            continue;
        }

        // Keyword or Identifier
        if (isalpha((unsigned char)input[i]) || input[i] == '_') {
            char word[100];
            int k = 0;

            while (isalnum((unsigned char)input[i]) ||
                   input[i] == '_') {
                if (k < 99) {
                    word[k++] = input[i];
                }
                i++;
            }
            word[k] = '\0';

            if (isKeyword(word)) {
                printf("Keyword: %s\n", word);
            } else {
                printf("Identifier: %s\n", word);
            }
            token_count++;
        }

        // Number
        else if (isdigit((unsigned char)input[i])) {
            char num[100];
            int k = 0;

            while (isdigit((unsigned char)input[i])) {
                if (k < 99) {
                    num[k++] = input[i];
                }
                i++;
            }
            num[k] = '\0';

            printf("Number: %s\n", num);
            token_count++;
        }

        // String Literal
        else if (input[i] == '"') {
            char str[100];
            int k = 0;

            str[k++] = input[i++];

            while (input[i] != '\0' && input[i] != '"') {
                if (k < 98) {
                    str[k++] = input[i];
                }
                i++;
            }

            if (input[i] == '"') {
                if (k < 99) {
                    str[k++] = input[i];
                }
                i++;
            }

            str[k] = '\0';

            printf("Literal: %s\n", str);
            token_count++;
        }

        // Operator
        else if (strchr("=+-*/<>!%&|^~", input[i])) {
            printf("Operator: %c\n", input[i]);
            token_count++;
            i++;
        }

        // Symbol
        else if (strchr("(){};,#@", input[i])) {
            printf("Symbol: %c\n", input[i]);
            token_count++;
            i++;
        }

        // Other characters
        else {
            i++;
        }
    }

    printf("\nTotal number of tokens = %d\n", token_count);

    return 0;
}

/*
int main()
{
int a = 10;
printf(“Display a”);
return 0;
}
$

#include <stdio.h>
X=#
int main() {
    int a = 10;
    printf("Display a");
    return 0;
}
$

// Skip preprocessor line
if (input[i] == '#') {
    int j = i - 1;

    while (j >= 0 && input[j] != '\n' &&
           isspace((unsigned char)input[j])) {
        j--;
    }

    if (j < 0 || input[j] == '\n') {
        while (input[i] != '\0') {
            while (input[i] != '\0' && input[i] != '\n') {
                i++;
            }

            if (i == 0 || input[i - 1] != '\\') {
                break;
            }

            if (input[i] == '\n') {
                i++;
            }
        }
        continue;
    }
}
*/
