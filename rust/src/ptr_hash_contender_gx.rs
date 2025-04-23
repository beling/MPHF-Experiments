use mem_dbg::SizeFlags;
use ptr_hash::PtrHashParams;
use rayon::iter::{IntoParallelRefIterator, ParallelIterator};

use std::hint::black_box;

use cacheline_ef::CachelineEfVec;

#[derive(Clone, Copy)]
pub struct GxHashForPtr;

impl<K: std::hash::Hash> ptr_hash::hash::Hasher<K> for GxHashForPtr {
    type H = u64;

    #[inline]
    fn hash(x: &K, seed: u64) -> Self::H {
        let mut state = gxhash::GxHasher::with_seed(seed as i64);
        x.hash(&mut state);
        std::hash::Hasher::finish(&state)
        //state.finish_u128()
    }
}

type PtrHashLinearVec = ptr_hash::PtrHash<&'static [u8], ptr_hash::bucket_fn::Linear,
    Vec<u32>, GxHashForPtr, Vec<u8>>; // Fast
type PtrHashSquareVec = ptr_hash::PtrHash<&'static [u8], ptr_hash::bucket_fn::SquareEps,
    Vec<u32>, GxHashForPtr, Vec<u8>>;
type PtrHashCubicVec = ptr_hash::PtrHash<&'static [u8], ptr_hash::bucket_fn::CubicEps,
    Vec<u32>, GxHashForPtr, Vec<u8>>;
type PtrHashLinearEF = ptr_hash::PtrHash<&'static [u8], ptr_hash::bucket_fn::Linear,
    CachelineEfVec, GxHashForPtr, Vec<u8>>;
type PtrHashSquareEF = ptr_hash::PtrHash<&'static [u8], ptr_hash::bucket_fn::SquareEps,
    CachelineEfVec, GxHashForPtr, Vec<u8>>;
type PtrHashCubicEF = ptr_hash::PtrHash<&'static [u8], ptr_hash::bucket_fn::CubicEps,
    CachelineEfVec, GxHashForPtr, Vec<u8>>; // Compact

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
pub extern "C" fn createPtrHashGxStruct() -> *mut PtrHashVariant {
    Box::into_raw(Box::new(PtrHashVariant::None))
}

#[no_mangle]
pub extern "C" fn constructPtrHashGx(struct_ptr: *mut PtrHashVariant, keys_ptr: *const Box<[Box<[u8]>]>, variant: u64, lambda: f64) {
    let f = unsafe { &mut *struct_ptr };
    let keys = unsafe { &*keys_ptr };
    *f = match variant {
        1 => {
            let mut params = PtrHashParams::default_fast();
            params.lambda = lambda;
            PtrHashVariant::LinearVec( PtrHashLinearVec::new_from_par_iter(keys.len(), keys.par_iter().map(|v| v.as_ref()), params) )
        },
        2 => {
            let mut params = PtrHashParams::default_square();
            params.lambda = lambda;
            PtrHashVariant::SquareVec( PtrHashSquareVec::new_from_par_iter(keys.len(), keys.par_iter().map(|v| v.as_ref()), params) )
        },
        3 => {
            let mut params = PtrHashParams::default_compact();
            params.lambda = lambda;
            PtrHashVariant::CubicVec( PtrHashCubicVec::new_from_par_iter(keys.len(), keys.par_iter().map(|v| v.as_ref()), params) )
        },
        4 => {
            let mut params = PtrHashParams::default_fast();
            params.lambda = lambda;
            PtrHashVariant::LinearEF( PtrHashLinearEF::new_from_par_iter(keys.len(), keys.par_iter().map(|v| v.as_ref()), params) )
        },
        5 => {
            let mut params = PtrHashParams::default_square();
            params.lambda = lambda;
            PtrHashVariant::SquareEF( PtrHashSquareEF::new_from_par_iter(keys.len(), keys.par_iter().map(|v| v.as_ref()), params) )
        },
        6 => {
            let mut params = PtrHashParams::default_compact();
            params.lambda = lambda;
            PtrHashVariant::CubicEF( PtrHashCubicEF::new_from_par_iter(keys.len(), keys.par_iter().map(|v| v.as_ref()), params) )
        },
        _ => panic!("Invalid variant"),
    }
}

#[no_mangle]
pub extern "C" fn queryPtrHashGx(struct_ptr: *const PtrHashVariant, keys_ptr: *const Box<[Box<[u8]>]>, index: usize) -> u64 {
    let keys = &unsafe { &*keys_ptr }[..];
    let key = keys[index].as_ref();
    match unsafe { &*struct_ptr } {
        PtrHashVariant::LinearVec(f) => f.index(&key) as u64,
        PtrHashVariant::SquareVec(f) => f.index(&key) as u64,
        PtrHashVariant::CubicVec(f) => f.index(&key) as u64,
        PtrHashVariant::LinearEF(f) => f.index(&key) as u64,
        PtrHashVariant::SquareEF(f) => f.index(&key) as u64,
        PtrHashVariant::CubicEF(f) => f.index(&key) as u64,
        PtrHashVariant::None => panic!("PtrHashGx not constructed yet"),
    }
}

#[inline(never)]
fn query_all<BF, F, Hx>(f: &ptr_hash::PtrHash<&'static [u8], BF, F, Hx, Vec<u8>>, keys: &'static [Box<[u8]>])
    where BF: ptr_hash::bucket_fn::BucketFn, F: ptr_hash::pack::Packed, Hx: ptr_hash::hash::Hasher<&'static [u8]>
{
    for key in keys {
        black_box(f.index(&key.as_ref()));
    }
    //keys.iter().for_each(|key| { black_box(f.index(&key));});
}

#[no_mangle]
pub extern "C" fn queryPtrHashGxAll(struct_ptr: *const PtrHashVariant, keys_ptr: *const Box<[Box<[u8]>]>) {
    let keys = unsafe { &*keys_ptr }; 
    match unsafe { &*struct_ptr } {
        PtrHashVariant::LinearVec(f) => query_all(f, keys),
            //for key in keys { black_box(key.as_ref()); black_box(f.index(&key.as_ref())); },
            //keys.iter().for_each(|key| { black_box(f.index(&key.as_ref())); }),
        PtrHashVariant::SquareVec(f) => query_all(f, keys),
            //for key in keys { black_box(key.as_ref()); black_box(f.index(&key.as_ref())); },
            //keys.iter().for_each(|key| { black_box(f.index(&key.as_ref())); }),
        PtrHashVariant::CubicVec(f) => query_all(f, keys),
            //for key in keys { black_box(key.as_ref()); black_box(f.index(&key.as_ref())); },
            //keys.iter().for_each(|key| { black_box(f.index(&key.as_ref())); }),
        PtrHashVariant::LinearEF(f) => query_all(f, keys),
            //for key in keys { black_box(key.as_ref()); black_box(f.index(&key.as_ref())); },
            //keys.iter().for_each(|key| { black_box(f.index(&key.as_ref())); }),
        PtrHashVariant::SquareEF(f) => query_all(f, keys),
            //for key in keys { black_box(key.as_ref()); black_box(f.index(&key.as_ref())); },
            //keys.iter().for_each(|key| { black_box(f.index(&key.as_ref())); }),
        PtrHashVariant::CubicEF(f) => query_all(f, keys),
            //for key in keys { black_box(key.as_ref()); black_box(f.index(&key.as_ref())); },
            //keys.iter().for_each(|key| { black_box(f.index(&key.as_ref())); }),
        PtrHashVariant::None => panic!("PtrHashGx not constructed yet"),
    };
}

#[no_mangle]
pub extern "C" fn sizePtrHashGx(struct_ptr: *const PtrHashVariant) -> usize {
    use mem_dbg::MemSize;
    match unsafe { &*struct_ptr } {   
        PtrHashVariant::LinearVec(f) => f.mem_size(SizeFlags::default()),
        PtrHashVariant::SquareVec(f) => f.mem_size(SizeFlags::default()),
        PtrHashVariant::CubicVec(f) => f.mem_size(SizeFlags::default()),
        PtrHashVariant::LinearEF(f) => f.mem_size(SizeFlags::default()),
        PtrHashVariant::SquareEF(f) => f.mem_size(SizeFlags::default()),
        PtrHashVariant::CubicEF(f) => f.mem_size(SizeFlags::default()),
        PtrHashVariant::None => panic!("PtrHashGx not constructed yet"),
    }
}

#[no_mangle]
pub extern "C" fn destroyPtrHashGxStruct(struct_instance: *mut PtrHashVariant) {
    unsafe { let _ = Box::from_raw(struct_instance); }
}