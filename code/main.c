#include <stdio.h>
#include <stdlib.h>
#include "ffi-examples.h"


int main(int argc, char const *argv[])
{
    wchar_t *greeting = "привет Rustfest 👩🏽‍💻";
    printf("'%s' reversed: '%s' \n", greeting, reverse(greeting));
    return 0;
}
