// begin bar.c
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

extern void *__cxa_allocate_exception(size_t thrown_size);
extern void __cxa_throw(void *thrown_exception, void **tinfo, void (*dest)(void *));
extern void *_ZTI19CustomRustException; // typeinfo of long

struct CustomRustException {
    int64_t value;
    unsigned char *message;
};

int throw_native(int64_t value)
{
    printf("From C: Hello!\n");
    struct CustomRustException *p = (struct CustomRustException *) __cxa_allocate_exception(16);
    p->value = value;
    p->message = calloc(sizeof(char), 4);
    strcpy((char*) p->message, "lol\n");

    printf("From C: Allocating exception 3:)\n");
    __cxa_throw(p, &_ZTI19CustomRustException, 0);
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
