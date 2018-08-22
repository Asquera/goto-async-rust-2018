// Rust defined functions via C interface


#include <stdint.h>

struct CustomRustException {
    int64_t code;
    unsigned char *message;
};

void totally_safe_rust_code();