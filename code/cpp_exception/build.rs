extern crate gcc;

fn main() {
    gcc::compile_library("libthrow.a", &["native/handle.c"]);
}