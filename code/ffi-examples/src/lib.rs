extern crate unicode_reverse as ur;

use std::ffi::{CStr, CString};
use std::os::raw::c_char;

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
