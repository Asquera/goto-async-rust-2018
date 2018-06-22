// begin bar.c
#include <stdlib.h>
#include <stdint.h>

extern void *__cxa_allocate_exception(size_t thrown_size);
extern void __cxa_throw (void *thrown_exception, void* *tinfo, void (*dest) (void *) );
extern void * _ZTIl; // typeinfo of long

struct exception_t {
  int64_t value;
};

int bar1() {
   struct exception_t* p = (struct exception_t*)__cxa_allocate_exception(8);
   p->value = 1337;
   __cxa_throw(p,&_ZTIl,0);
  return 10;
}
