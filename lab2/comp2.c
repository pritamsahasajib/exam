#include <stdio.h>
#include <string.h>

int main() {
    char str[100];

    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);

    printf("String entered: %s", str);
    printf("Length including newline: %d\n", strlen(str));

    return 0;
}


//Programming
