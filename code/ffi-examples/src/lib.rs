extern crate unicode_reverse as ur;

use std::ffi::{CStr, CString};
use std::os::raw::{c_char, c_uint, c_void};

/// Safely reverse a utf-8 string
#[no_mangle]
pub extern "C" fn reverse(word: *const c_char) -> *const c_char {
    let mut s: String = match unsafe { CStr::from_ptr(word) }.to_str() {
        Ok(s) => s,
        _ => return unsafe { ::std::mem::uninitialized() },
    }.into();
    ur::reverse_grapheme_clusters_in_place(&mut s);
    println!("{}", s);
    CString::new(s).unwrap().into_raw()
}

#[allow(unused, non_camel_case_types)]
pub struct server_t {
    port: u32,
}

#[no_mangle]
pub extern "C" fn initialise(ctx: *mut *mut c_void, port: c_uint) -> c_uint {
    let port: u32 = port;
    if port <= 1024 {
        return 2;
    }

    let server = Box::new(server_t { port });
    unsafe { *ctx = Box::into_raw(server) as *mut c_void };
    return 0;
}

use std::any::Any;

#[allow(unused, non_camel_case_types)]
#[repr(C)]
pub struct rvalue_t {
    thing: Box<Option<Box<Any>>>,
    code: u32,
}

#[no_mangle]
pub extern "C" fn myfunction() -> rvalue_t {
    rvalue_t {
        thing: Box::new(None),
        code: 666,
    }
}