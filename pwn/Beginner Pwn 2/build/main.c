#include <stdio.h>

void win(){
    FILE *fptr;
    char flag[35] = {0};
    printf("win\n");

    fptr = fopen("flag.txt", "r");
    fread(flag, 1, 30, fptr);
    printf("Here is your flag! %s\n", flag);
    fclose(fptr);
}

int main(void) {
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);

    char name[10] = {0};
    gets(name);
    printf("Hello, %s!\n", name);
    return 0;
}
