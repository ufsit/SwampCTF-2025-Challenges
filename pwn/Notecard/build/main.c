#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>

// Function pointer leak from the stack using printf, use write to write to a buffer without an null ptr

// populate pool
// give some way to overwrite the pointers in the pool

typedef int (*Operation)(void*);
char temp;

uintptr_t** generate_pool(){
    uintptr_t pool[5];

    for(int i = 0; i < 5; i++) {
        pool[i] = (uintptr_t) malloc(sizeof(uintptr_t) * 5);
    }

    uintptr_t** heap_pool = (uintptr_t **) malloc(sizeof(uintptr_t) * 5);
    memcpy(heap_pool, pool, sizeof(uintptr_t) * 5);

    return heap_pool;
}

void exit_internal(int arg) {
    exit(arg);
}

void heap_read(uintptr_t** heap_pool) {
    //unsigned char size;
    int index;
    printf("Notecard number (0 - 4): ");
    scanf("%d", &index);
    scanf("%c", &temp);
    //printf("Read Size: ");
    //scanf("%d", &size);
    //scanf("%c", &temp);

    if(index > 4) {
        printf("You are using the free version of Note and only have 5 note cards!\n");
        return;
    }

    puts((char *)(heap_pool[index]));

    /*if((char)size < 40 && index <= 5) {
        write(STDOUT_FILENO, heap_pool[index], (char)size);

    } else {
        puts("Invalid read size");
    }*/
}

void heap_write(uintptr_t** heap_pool) {
    int index;
    printf("Notecard number (0 - 4): ");
    scanf("%d", &index);
    scanf("%c", &temp);

    if(index > 4) {
        printf("You are using the free version of Note and only have 5 note cards!\n");
        return;
    }


    //fgets((char *)(heap_pool[index]), 40, STDIN_FILENO);
    read(STDIN_FILENO,(char *)(heap_pool[index]), 40);
    //gets((char *)(heap_pool[index]));
}

void main_loop(uintptr_t** heap_pool) {
    //Operation funcs[3] = {(Operation) exit, (Operation) heap_read, (Operation) heap_write};
    //char name[24] = {0};

    /*
    Operation *funcs;
    char name[24 + sizeof(Operation) * 3] = {0};
    funcs = (Operation*)(name + 24);
    funcs[0] = (Operation)(exit);
    funcs[1] = (Operation)(heap_read);
    funcs[2] = (Operation)(heap_write);
    */

    char name[24 + sizeof(Operation) * 3] = {0};


    unsigned int choice;

    char name_loop = 'y';

    while(name_loop != 'n') {
        puts("Please enter your name:");
        //read(STDIN_FILENO, name, 33);
        gets(name);

        printf("Your name is ");
        puts(name);
        printf("\nChange it? (y/n)?\n", name);
        scanf("%c", &name_loop);
        scanf("%c", &temp);
    }

    //*(strchr(name, '\n')) = 0;

    ((Operation*)(name + 24))[0] = (Operation)(exit_internal);
    ((Operation*)(name + 24))[1] = (Operation)(heap_read);
    ((Operation*)(name + 24))[2] = (Operation)(heap_write);

    printf("Hello %s!\n", name);

    while(1) {
        printf("0 - exit\n"
             "1 - read\n"
             "2 - write\n"
             "> \n");

        scanf("%d", &choice);
        scanf("%c", &temp);

        choice = 3 & choice;

        switch (choice) {
            case 0:
                printf("Goodbye ");
                puts(name);
                //fptr = funcs[0];
                (*((Operation*)(name + 24))[0])(EXIT_SUCCESS);
                break;
            case 1:
                (*((Operation*)(name + 24))[1])((void*)heap_pool);
                break;
            case 2:
                (*((Operation*)(name + 24))[2])((void*)heap_pool);
                break;
            default:
                break;
        }


    }
}

int main(void) {
    setbuf(stdin, NULL);
    setbuf(stdout, NULL);

    printf("Welcome to Note! Your one stop shop for all notecard needs!\n");

    uintptr_t** heap_pool = generate_pool();

    main_loop(heap_pool);

    return 0;
}
