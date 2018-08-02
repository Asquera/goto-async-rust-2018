#include <stdio.h>
#include <stdlib.h>
#include "ffi-examples.h"


int main(int argc, char const *argv[])
{
    // wchar_t *greeting = "привет Rustfest 👩🏽‍💻";
    // printf("'%s' reversed: '%s' \n", greeting, reverse(greeting));

    // struct server_t *server;
    // unsigned int ret = initialise(&server, 8080);
    // if(ret) {
    //     printf("Error: %i\n", ret);
    // }

    struct rvalue_t value = myfunction();
    printf("The return code was: %d\n", value.code);

    // printf("Server port number: %i\n", server->port);
    return 0;
}
