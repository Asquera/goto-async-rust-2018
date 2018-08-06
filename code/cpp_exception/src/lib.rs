//! A wrapper around unsafe code that throws a C++ exception

extern "C" {
    fn throw_native(code: i64);
}

// extern "C" {
    // extern void *__cxa_allocate_exception(size_t thrown_size);
    // extern void __cxa_throw(void *thrown_exception, void **tinfo, void (*dest)(void *));
    // extern void *_ZTIl; // typeinfo of long

    // fn __cxa_allocate_exception(throw_size: usize) -> *mut c_void;
    // fn __cxa_throw(thrown_exception: *mut c_void, tinfo: *mut *mut c_void, dest: *mut c_void);
// }

/// Throw a C++ exception for someone higher up to catch
#[no_mangle]
pub fn totally_safe_rust_code() {
    println!("From Rust: Don't worry, Rust is a memory safe language!");
    unsafe { throw_native(201) };
}
