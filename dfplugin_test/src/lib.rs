
use std::ffi::CString;
use std::os::raw::c_char;

#[no_mangle]
pub extern "C" fn add(a: i32, b: i32) -> i32 {
    a + b
}

#[no_mangle]
pub extern "C" fn hello_world_in_rust() -> *mut c_char {
    let c_to_print = CString::new("Hello World, Rust here!!").expect("CString::new failed");

    let ptr = c_to_print.into_raw();
    return ptr;
}

#[no_mangle]
pub extern "C" fn free_rust_cstring(ptr: *mut c_char) {
    unsafe{
        let _ = CString::from_raw(ptr);
    }
}
