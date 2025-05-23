use ph::{fmph, GetSize};
use ph::fmph::GOBuildConf;
use std::hint::black_box;

#[no_mangle]
pub extern "C" fn createFmphGoStruct() -> *mut fmph::GOFunction {
    Box::into_raw(Box::new(fmph::GOFunction::from(&[] as &[Box<[u8]>])))
}

#[no_mangle]
pub extern "C" fn constructFmphGo(struct_ptr: *mut fmph::GOFunction, keys_ptr: *const Box<[Box<[u8]>]>, gamma: u16) {
    let keys = unsafe { &*keys_ptr };
    let f = unsafe { &mut *struct_ptr };
    let mut build_config = GOBuildConf::default();
    build_config.use_multiple_threads = true;
    build_config.relative_level_size = gamma;
    *f = fmph::GOFunction::from_slice_with_conf(&keys[..], build_config);
}

#[no_mangle]
pub extern "C" fn queryFmphGo(struct_ptr: *const fmph::GOFunction, keys_ptr: *const Box<[Box<[u8]>]>, index: usize) -> u64 {
    let f = unsafe { &*struct_ptr };
    let keys = &unsafe { &*keys_ptr }[..];
    f.get_or_panic(&keys[index])
}

#[no_mangle]
pub extern "C" fn queryFmphGoAll(struct_ptr: *const fmph::GOFunction, keys_ptr: *const Box<[Box<[u8]>]>) {
    let f = unsafe { &*struct_ptr };
    let keys = unsafe { &*keys_ptr };
    for key in keys {
        black_box(f.get(key.as_ref()));
    }
}

#[no_mangle]
pub extern "C" fn sizeFmphGo(struct_ptr: *const fmph::GOFunction) -> usize {
    unsafe { &*struct_ptr }.size_bytes()
}

#[no_mangle]
pub extern "C" fn destroyFmphGoStruct(struct_instance: *mut fmph::GOFunction) {
    unsafe { let _ = Box::from_raw(struct_instance); }
}
