use std::fs::File;
use std::io::prelude::*;

fn main() {
    let f = File::open("test").unwrap();

    for i in 1..3 {
        std::thread::spawn(move || {
            write!(f, "thread {}", i);
        });
    }
}
