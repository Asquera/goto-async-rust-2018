extern crate gcc;

fn main() {
    #![allow(deprecated)]
    gcc::compile_library("libthrow.a", &["native/handle.c"]);
}