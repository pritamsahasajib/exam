#include <stdio.h>
#include <string.h>

int main() {
    char str[100];
    int i, j = 0, count = 0;

    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);

    str[strcspn(str, "\n")] = '\0';

    for (i = 0; str[i] != '\0'; i++) {
        if (str[i] == ' ') {
            count++;
        } else {
            str[j] = str[i];
            j++;
        }
    }

    str[j] = '\0';

    printf("Number of white spaces: %d\n", count);
    printf("String without white spaces: %s\n", str);

    return 0;
}
//Hello World CSE Student
