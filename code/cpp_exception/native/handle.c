#include <stdlib.h>
#include <stdint.h>
#include <string.h>

extern void *__cxa_allocate_exception(size_t thrown_size);
extern void __cxa_throw (void *thrown_exception, void **tinfo, void (*dest) (void *) );
extern void *_ZTIl;

struct exception_t {
    int64_t value;
    // char *message;
};

void meh(unsigned int value) {
    struct exception_t* e = (struct exception_t*) __cxa_allocate_exception(8);
    
    // size_t msglen = strlen(message) + 1;
    // char *msg = (char*) calloc(sizeof(char), msglen);
    // strcpy(msg, message);

    /* Assign the exception */
    e->value = value;
    // e->message = msg;

    /* swoosh */
    __cxa_throw(e, &_ZTIl, 0);
}
