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
    try {
        cout << "From C++: Running some Rust code in a `try` block – I don't trust Rust!" << endl;
        totally_safe_rust_code();
    } catch (RustException e) {
        cout << "From C++: Rust Exception code: " << e.code << ", message: " << e.message << endl;
    }

    return 0;
}
