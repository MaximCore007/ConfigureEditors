#include <stdio.h>
#include <malloc.h>

static void afunc(void);
static void bfunc(void);

int bss_var;
int bss_zero = 0;
int data_var = 42;

#define ARR_SIZE 4
int bss_arr[ARR_SIZE];
int bss_init[ARR_SIZE] = {0};
int data_arr[ARR_SIZE] = {1, 2, 3, 4};

#define FUNC_RECURSIVE 4

int main(int argc, char **argv) {
    char *p, *b, *nb;

    printf("Text location:\n");
    printf("\tAddress of main : %p\n", main);
    printf("\tAddress of afunc: %p\n", afunc);
    printf("\tAddress of bfunc: %p\n", bfunc);

    printf("Stack locations:\n");
    afunc();
    p = (char *)alloca(4 * FUNC_RECURSIVE);
    if (p != NULL) {
        printf("\tStart of alloca()'ed array: %p\n", p);
    }
    bfunc();

    printf("Data locations:\n");
    printf("\tAddress of data_var: %p\n", &data_var);
    printf("\tStart address of data_arr: %p\n", data_arr);
    printf("\tEnd address of data_arr: %p\n", data_arr + ARR_SIZE * (sizeof(int)));

    printf("BSS locations:\n");
    printf("\tAddress of bss_var: %p\n", &bss_var);
    printf("\tStart address of bss_arr: %p\n", bss_arr);
    printf("\tEnd address of bss_arr: %p\n", bss_arr + ARR_SIZE * (sizeof(int)));

    printf("BSS init zero locations:\n");
    printf("\tAddress of bss_zero: %p\n", &bss_zero);
    printf("\tStart address of bss_inti: %p\n", bss_init);
    printf("\tEnd address of bss_init: %p\n", bss_init + ARR_SIZE * (sizeof(int)));

    b = (char *)sbrk((ptrdiff_t) 32);
    nb = (char *)sbrk((ptrdiff_t) 0);
    printf("Heap location:\n");
    printf("\tInitial end of heap: %p\n", b);
    printf("\tNew end of heap (+32bytes): %p\n", nb);
    b = (char *)sbrk((ptrdiff_t) -16);
    nb = (char *)sbrk((ptrdiff_t) 0); 
    printf("\tFinal end of heap (-16bytes): %p\n", nb);
}

void afunc(void)
{
    static int level = 0;   // recursion level
    int stack_var;     // automatic variable in stack

    if (++level == FUNC_RECURSIVE) {     // avoid infinite recursion
        return;
    }

    printf("\tStack level %d: adderess of stack_var: %p\n", 
        level, &stack_var);
    afunc();    // call recursive
}

void bfunc(void)
{
    int stack_var;
    printf("\tAddress of stack_var after allocated: %p\n", &stack_var);
}
