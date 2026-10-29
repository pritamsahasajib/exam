#include <stdio.h>

int main() {
    char str[100];
    int i, count = 0;

    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);

    for (i = 0; str[i] != '\0'; i++) {
        if (str[i] == ' ')
            count++;
    }

    printf("Number of white spaces = %d", count);

    return 0;
}


//Hello World CSE Student

