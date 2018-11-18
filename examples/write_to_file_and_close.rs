use std::fs::File;
use std::io::prelude::*;

fn main() {
    let f = File::open("test").unwrap();

    write_to_file_and_close(f);
}

fn write_to_file_and_close(mut f: File) {
    write!(f, "test");
}
