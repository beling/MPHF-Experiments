mod fmph_contender;
mod fmph_go_contender;
mod phast_contender;
mod ptr_hash_contender;

use std::os::raw::c_char;
use std::slice;

static mut THREAD_POOL_INITIALIZED: bool = false;

#[no_mangle]
pub extern "C" fn initializeRayonThreadPool(threads: usize) {
    if unsafe {THREAD_POOL_INITIALIZED} {
        assert!(rayon::current_num_threads() == threads);
        return;
    }
    rayon::ThreadPoolBuilder::new().num_threads(threads).build_global().unwrap();
    unsafe { THREAD_POOL_INITIALIZED = true; }
}

#[no_mangle]
pub extern "C" fn constructKeys(len: usize) -> *mut Vec<Box<[u8]>> {
    Box::into_raw(Box::new(Vec::with_capacity(len)))
}

#[no_mangle]
pub extern "C" fn pushKey(v: *mut Vec<Box<[u8]>>, str: *const c_char, len: usize) {
    let v = unsafe{&mut *v};
    v.push(unsafe { slice::from_raw_parts(str as *const u8, len) }.to_owned().into_boxed_slice())
}

#[no_mangle]
pub extern "C" fn constructKeysEnd(struct_instance: *mut Vec<Box<[u8]>>) -> *mut Box<[Box<[u8]>]> {
    let b = unsafe { Box::from_raw(struct_instance) };
    Box::into_raw(Box::new(b.into_boxed_slice()))
}

/*#[no_mangle]
pub extern "C" fn convertToVecSlice(len: usize, my_strings: *const *const c_char) -> *mut Box<[Box<[u8]>]> {
    let mut keys = Vec::with_capacity(len);
    let sl = unsafe { std::slice::from_raw_parts(my_strings, len) };
    let mut index = 0;
    while index < sl.len() {
        let c_s = sl[index];
        let s = unsafe { slice::from_raw_parts(c_s as *const u8, strlen(c_s)) }.to_owned().into_boxed_slice();
        keys.push(s);
        index += 1;
    }
    let boxx = Box::new(keys.into_boxed_slice());
    Box::into_raw(boxx)
}*/

#[no_mangle]
pub extern "C" fn destroyKeys(struct_instance: *mut Box<[Box<[u8]>]>) {
    unsafe { let _ = Box::from_raw(struct_instance); }
}
