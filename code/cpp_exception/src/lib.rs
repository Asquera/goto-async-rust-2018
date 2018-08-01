//! A wrapper around unsafe code that throws a C++ exception

mod native {
    use std::os::raw::{c_char, c_uint};
    extern "C" {
        pub fn throw(code: c_uint, msg: *const c_char);
    }
}

/// Throw a C++ exception for someone higher up to catch
pub fn throw(code: u32, message: &str) {
    unsafe {
        use std::ffi::CString;
        let c_str = CString::new(message).unwrap();
        native::throw(code, c_str.as_ptr());
    }
}
