
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char str[100];
    int i, valid = 1;

    char *keywords[] = { "int", "char", "float", "double", "if", "else", "for", "while", "return", "void"};

    printf("Enter an identifier: ");
    scanf("%99s", str);

    if (!isalpha((unsigned char)str[0]) && str[0] != '_')    //2value, @name, #total invalid
        valid = 0;

    for (i = 1; str[i] != '\0'; i++) {                        //total-marks . total@marks
        if (!isalnum((unsigned char)str[i]) && str[i] != '_') {
            valid = 0;
            break;
        }
    }

    for (i = 0; i < 10; i++) {               // int, while, return invalid
        if (strcmp(str, keywords[i]) == 0) {
            valid = 0;
            break;
        }
    }

    if (valid)
        printf("%s is a valid identifier.\n", str);
    else
        printf("%s is an invalid identifier.\n", str);

    return 0;
}

//total_marks    2value
