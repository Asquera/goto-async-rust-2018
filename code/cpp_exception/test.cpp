namespace Rust {
    extern "C" {
       #include "rust.h"
    }
}

#include <iostream>

extern "C" {
    #include <stdint.h>
}

using std::cout;
using std::endl;

void foo() {
    // try
    // {
    cout << "From C++: I hope Rust doesn't do anything bad..." << endl;
    Rust::totally_safe_rust_code();
    // }
    // catch (int64_t x)
    // {
    //     cout << "From C++: I TOLD YOU I DIDN'T TRUST RUST! Caught an exception with code: " << x << endl;
    // }
}

int main(int argc, char *argv[]) {
    cout << "From C++: Running some code" << endl;
    foo();
    return 0;
}
