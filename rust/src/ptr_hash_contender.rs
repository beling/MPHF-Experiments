use mem_dbg::SizeFlags;
use ptr_hash::PtrHashParams;

use std::os::raw::c_char;
use std::slice;
use std::hint::black_box;

type PtrHashLinearVec = ptr_hash::PtrHash<&'static [u8], ptr_hash::bucket_fn::Linear,
    Vec<u32>, ptr_hash::hash::Xx64, Vec<u8>>; // Fast
type PtrHashSquareVec = ptr_hash::PtrHash<&'static [u8], ptr_hash::bucket_fn::SquareEps,
    Vec<u32>, ptr_hash::hash::Xx64, Vec<u8>>;
type PtrHashCubicVec = ptr_hash::PtrHash<&'static [u8], ptr_hash::bucket_fn::CubicEps,
    Vec<u32>, ptr_hash::hash::Xx64, Vec<u8>>;
type PtrHashLinearEF = ptr_hash::PtrHash<&'static [u8], ptr_hash::bucket_fn::Linear,
    ptr_hash::CachelineEfVec, ptr_hash::hash::Xx64, Vec<u8>>;
type PtrHashSquareEF = ptr_hash::PtrHash<&'static [u8], ptr_hash::bucket_fn::SquareEps,
    ptr_hash::CachelineEfVec, ptr_hash::hash::Xx64, Vec<u8>>;
type PtrHashCubicEF = ptr_hash::PtrHash<&'static [u8], ptr_hash::bucket_fn::CubicEps,
    ptr_hash::CachelineEfVec, ptr_hash::hash::Xx64, Vec<u8>>; // Compact

pub enum PtrHashVariant {
    None,
    LinearVec(PtrHashLinearVec),
    SquareVec(PtrHashSquareVec),
    CubicVec(PtrHashCubicVec),
    LinearEF(PtrHashLinearEF),
    SquareEF(PtrHashSquareEF),
    CubicEF(PtrHashCubicEF),
}

#[no_mangle]
pub extern "C" fn createPtrHashStruct() -> *mut PtrHashVariant {
    Box::into_raw(Box::new(PtrHashVariant::None))
}

#[no_mangle]
pub extern "C" fn constructPtrHash(struct_ptr: *mut PtrHashVariant, keys_ptr: *const Box<[&'static [u8]]>, variant: u64, lambda: f64) {
    let f = unsafe { &mut *struct_ptr };
    let keys = unsafe { &*keys_ptr };
    *f = match variant {
        1 => {
            let mut params = PtrHashParams::default_fast();
            params.lambda = lambda;
            PtrHashVariant::LinearVec( PtrHashLinearVec::new(&keys[..], params) )
        },
        2 => {
            let mut params = PtrHashParams::default_square();
            params.lambda = lambda;
            PtrHashVariant::SquareVec( PtrHashSquareVec::new(&keys[..], params) )
        },
        3 => {
            let mut params = PtrHashParams::default_compact();
            params.lambda = lambda;
            PtrHashVariant::CubicVec( PtrHashCubicVec::new(&keys[..], params) )
        },
        4 => {
            let mut params = PtrHashParams::default_fast();
            params.lambda = lambda;
            PtrHashVariant::LinearEF( PtrHashLinearEF::new(&keys[..], params) )
        },
        5 => {
            let mut params = PtrHashParams::default_square();
            params.lambda = lambda;
            PtrHashVariant::SquareEF( PtrHashSquareEF::new(&keys[..], params) )
        },
        6 => {
            let mut params = PtrHashParams::default_compact();
            params.lambda = lambda;
            PtrHashVariant::CubicEF( PtrHashCubicEF::new(&keys[..], params) )
        },
        _ => panic!("Invalid variant"),
    }
}

#[no_mangle]
pub extern "C" fn queryPtrHash(struct_ptr: *const PtrHashVariant, key_c_s: *const c_char, length: usize) -> u64 {
    let f = unsafe { &*struct_ptr };
    let key = unsafe { slice::from_raw_parts(key_c_s as *const u8, length + 1) };
    match f {
        PtrHashVariant::LinearVec(ref f) => f.index_minimal(&key) as u64,
        PtrHashVariant::SquareVec(ref f) => f.index_minimal(&key) as u64,
        PtrHashVariant::CubicVec(ref f) => f.index_minimal(&key) as u64,
        PtrHashVariant::LinearEF(ref f) => f.index_minimal(&key) as u64,
        PtrHashVariant::SquareEF(ref f) => f.index_minimal(&key) as u64,
        PtrHashVariant::CubicEF(ref f) => f.index_minimal(&key) as u64,
        PtrHashVariant::None => panic!("PtrHash not constructed yet"),
    }
}

#[no_mangle]
pub extern "C" fn queryPtrHashAll(struct_ptr: *const PtrHashVariant, keys_ptr: *const Box<[&'static [u8]]>) {
    let f = unsafe { &*struct_ptr };
    let keys = unsafe { &*keys_ptr }; 
    match f {
        PtrHashVariant::LinearVec(ref f) =>
            for key in keys { black_box(f.index_minimal(key)); },
        PtrHashVariant::SquareVec(ref f) =>
            for key in keys { black_box(f.index_minimal(key)); },
        PtrHashVariant::CubicVec(ref f) =>
            for key in keys { black_box(f.index_minimal(key)); },
        PtrHashVariant::LinearEF(ref f) =>
            for key in keys { black_box(f.index_minimal(key)); },
        PtrHashVariant::SquareEF(ref f) =>
            for key in keys { black_box(f.index_minimal(key)); },
        PtrHashVariant::CubicEF(ref f) =>
            for key in keys { black_box(f.index_minimal(key)); },
        PtrHashVariant::None => panic!("PtrHash not constructed yet"),
    };
}

#[no_mangle]
pub extern "C" fn sizePtrHash(struct_ptr: *const PtrHashVariant) -> usize {
    let f = unsafe { &*struct_ptr };
    use mem_dbg::MemSize;
    match f {   
        PtrHashVariant::LinearVec(f) => f.mem_size(SizeFlags::default()),
        PtrHashVariant::SquareVec(f) => f.mem_size(SizeFlags::default()),
        PtrHashVariant::CubicVec(f) => f.mem_size(SizeFlags::default()),
        PtrHashVariant::LinearEF(f) => f.mem_size(SizeFlags::default()),
        PtrHashVariant::SquareEF(f) => f.mem_size(SizeFlags::default()),
        PtrHashVariant::CubicEF(f) => f.mem_size(SizeFlags::default()),
        PtrHashVariant::None => panic!("PtrHash not constructed yet"),
    }
}

#[no_mangle]
pub extern "C" fn destroyPtrHashStruct(struct_instance: *mut PtrHashVariant) {
    unsafe { let _ = Box::from_raw(struct_instance); }
}
