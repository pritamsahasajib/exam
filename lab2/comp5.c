#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char word[100];
    int i, length, isPalindrome = 1;

    printf("Enter a word: ");
    scanf("%99s", word);

    length = strlen(word);

    for (i = 0; i < length / 2; i++) {
        if (tolower((unsigned char)word[i]) != tolower((unsigned char)word[length - 1 - i]))
            {
            isPalindrome = 0;
            break;
            }
    }

    if (isPalindrome)
        printf("%s is a palindrome.\n", word);
    else
        printf("%s is not a palindrome.\n", word);

    return 0;
}

//Level is a palindrome.
