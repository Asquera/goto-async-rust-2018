// begin bar.c
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

extern void *__cxa_allocate_exception(size_t thrown_size);
extern void __cxa_throw(void *thrown_exception, void **tinfo, void (*dest)(void *));
extern void *_ZTIl; // typeinfo of long

struct exception_t
{
    int64_t value;
};

int throw_native(int64_t value)
{
    printf("From C: Hello!\n");
    struct exception_t *p = (struct exception_t *)__cxa_allocate_exception(8);
    p->value = value;
    printf("From C: Allocating exception 3:)\n");
    __cxa_throw(p, &_ZTIl, 0);
    return 10;
}

// struct exception_t {
//     int64_t value;
//     // char *message;
// };

// void meh(unsigned int value) {
//     struct exception_t* e = (struct exception_t*) __cxa_allocate_exception(8);

//     // size_t msglen = strlen(message) + 1;
//     // char *msg = (char*) calloc(sizeof(char), msglen);
//     // strcpy(msg, message);

//     /* Assign the exception */
//     e->value = value;
//     // e->message = msg;

//     /* swoosh */
//     __cxa_throw(e, &_ZTIl, 0);
// }
