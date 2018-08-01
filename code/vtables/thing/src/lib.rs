#[repr(C)]
pub struct MyThing {
    stuff: Vec<i32>,
}

pub trait DoAThing {
    fn add(&mut self, item: i32);
    fn remove(&mut self) -> i32;
}

impl DoAThing for MyThing {
    fn add(&mut self, item: i32) {
        self.stuff.push(item);
    }

    fn remove(&mut self) -> i32 {
        match self.stuff.pop() {
            Some(value) => value,
            None => 0,
        }
    }
}

#[no_mangle]
pub extern "C" fn new_thing() -> Box<DoAThing> {
    Box::new(MyThing { stuff: vec![] })
}

#[no_mangle]
pub extern "C" fn free_thing(_: Box<DoAThing>) {
    /*
        Taking ownership and dropping it is kinda like letting your 
        younger sibling play with your toys but then they break them
        because they primarily don't want _you_ to have them either.

        Rust is your mean younger sibling.
    */
}