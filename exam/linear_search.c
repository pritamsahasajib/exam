#include <stdio.h>

int linearSearch(int array[], int size, int key)
{

    for (int i = 0; i < size; i++)
    {

        if (array[i] == key)
        {
            return i;
        }
    }

    return -1;
}

int main()
{
    int array[] = { 10, 50, 30, 70, 80, 60, 20, 90, 40 };
    int size = sizeof(array) / sizeof(array[0]);
    int key = 70;

    int result = linearSearch(array, size, key);

    if (result == -1)
        printf("Key Not Found");
    else
        printf("Key Found at Index: %d", result);

    return 0;
}
