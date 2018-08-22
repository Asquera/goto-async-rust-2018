/**
 * An example of how to catch an exception thrown from Rust code
 */

extern "C" {
    #include "rust.h"
}

#include <iostream>
using std::cout;
using std::endl;

int main(int argc, char *argv[]) {
    cout << "From C++: Running some Rust code – hope it doesn't break anything!" << endl;
    totally_safe_rust_code();
    
    try {
        totally_safe_rust_code();
    } catch (CustomRustException e) {
        cout << "From C++: Rust Exception code: " << e.code << ", message: " << e.message << endl;
    }
    return 0;
}
