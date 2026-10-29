#include <stdio.h>
#include <ctype.h>

int main() {
    char str[100];
    int i, j = 0;

    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);

    for (i = 0; str[i] != '\0'; i++) {
        if (!isspace((unsigned char)str[i])) {
            str[j] = str[i];
            j++;
        }
    }

    str[j] = '\0';

    printf("String without white spaces: %s", str);

    return 0;
}

//Hello World CSE Student
