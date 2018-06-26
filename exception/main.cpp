#include <stdint.h>
#include <cstdio>

extern "C" int bar1();

void foo() {
    try{
        bar1();
    } catch(int64_t x) {
        printf("good %ld", x);
    }
}

int main(int argc, char *argv[]) {
    foo();
    return 0;
}
