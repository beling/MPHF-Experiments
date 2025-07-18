use ph::{phast::{self, compressed_array::CompactFast, DefaultCompressedArray, Params, ShiftOnly}, GetSize};
use std::hint::black_box;

pub enum PHastPlusVariant {
    BitsEF(phast::Function2<ph::seeds::BitsFast, ShiftOnly, DefaultCompressedArray>),
    Bits8EF(phast::Function2<ph::seeds::Bits8, ShiftOnly, DefaultCompressedArray>),
    BitsC(phast::Function2<ph::seeds::BitsFast, ShiftOnly, CompactFast>),
    Bits8C(phast::Function2<ph::seeds::Bits8, ShiftOnly, CompactFast>),
    None
}

#[no_mangle]
pub extern "C" fn createPhastPlusStruct() -> *mut PHastPlusVariant {
    Box::into_raw(Box::new(PHastPlusVariant::None))
}

#[no_mangle]
pub extern "C" fn constructPhastPlus(struct_ptr: *mut PHastPlusVariant, keys_ptr: *const Box<[Box<[u8]>]>,
                        bits_per_seed: u8, bucket_size100: u16, threads_num: usize, ef: bool) {
    let f = unsafe { &mut *struct_ptr };
    let keys = unsafe { &*keys_ptr };
    *f = match (bits_per_seed, ef) {
        (8, true) => PHastPlusVariant::Bits8EF(phast::Function2::with_slice_p_threads_hash_sc(
            &keys[..], &Params::new(ph::seeds::Bits8, bucket_size100), threads_num,
            seedable_hash::BuildDefaultSeededHasher::default(), ShiftOnly
        )),
        (_, true) => PHastPlusVariant::BitsEF(phast::Function2::with_slice_p_threads_hash_sc(
            &keys[..], &Params::new(ph::seeds::BitsFast(bits_per_seed), bucket_size100),
            threads_num, seedable_hash::BuildDefaultSeededHasher::default(), ShiftOnly
        )),

        (8, false) => PHastPlusVariant::Bits8C(phast::Function2::with_slice_p_threads_hash_sc(
            &keys[..], &Params::new(ph::seeds::Bits8, bucket_size100), threads_num,
            seedable_hash::BuildDefaultSeededHasher::default(), ShiftOnly
        )),
        (_, false) => PHastPlusVariant::BitsC(phast::Function2::with_slice_p_threads_hash_sc(
            &keys[..], &phast::Params::new(ph::seeds::BitsFast(bits_per_seed), bucket_size100),
            threads_num, seedable_hash::BuildDefaultSeededHasher::default(), ShiftOnly
        ))
    }
}

#[no_mangle]
pub extern "C" fn queryPhastPlus(struct_ptr: *const PHastPlusVariant, keys_ptr: *const Box<[Box<[u8]>]>, index: usize) -> u64 {
    let keys = &unsafe { &*keys_ptr }[..];
    let key = keys[index].as_ref();
    match unsafe { &*struct_ptr } {
        PHastPlusVariant::BitsEF(function2) => function2.get(key) as u64,
        PHastPlusVariant::Bits8EF(function2) => function2.get(key) as u64,
        PHastPlusVariant::BitsC(function2) => function2.get(key) as u64,
        PHastPlusVariant::Bits8C(function2) => function2.get(key) as u64,
        PHastPlusVariant::None => panic!("PHast+ not constructed yet"),
    }
}

/*#[inline(always)] fn query_all<SS, CA, S>(Function2: &phast::Function2<SS, CA, S>, keys: &[Box<[u8]>])
    where SS: ph::fmph::SeedSize, CA: phast::CompressedArray, S: ph::BuildSeededHasher 
{
    for key in keys {
        black_box(Function2.get(key.as_ref()));
    }
}*/

#[no_mangle]
pub extern "C" fn queryPhastPlusAll(struct_ptr: *const PHastPlusVariant, keys_ptr: *const Box<[Box<[u8]>]>) {
    let keys = unsafe { &*keys_ptr };
    match unsafe { &*struct_ptr } {
        PHastPlusVariant::BitsEF(function2) => //query_all(Function2, &keys),
            for key in keys { black_box(function2.get(key.as_ref())); },
        PHastPlusVariant::Bits8EF(function2) =>  //query_all(Function2, &keys),
            for key in keys { black_box(function2.get(key.as_ref())); },
        PHastPlusVariant::BitsC(function2) => //query_all(Function2, &keys),
            for key in keys { black_box(function2.get(key.as_ref())); },
        PHastPlusVariant::Bits8C(function2) => //query_all(Function2, &keys),
            for key in keys { black_box(function2.get(key.as_ref())); },
        PHastPlusVariant::None => panic!("PHast+ not constructed yet"),
    }
}

#[no_mangle]
pub extern "C" fn sizePhastPlus(struct_ptr: *const PHastPlusVariant) -> usize {
    match unsafe { &*struct_ptr } {
        PHastPlusVariant::BitsEF(function2) => function2.size_bytes(),
        PHastPlusVariant::Bits8EF(function2) => function2.size_bytes(),
        PHastPlusVariant::BitsC(function2) => function2.size_bytes(),
        PHastPlusVariant::Bits8C(function2) => function2.size_bytes(),
        PHastPlusVariant::None => panic!("PHast+ not constructed yet"),
    }
}

#[no_mangle]
pub extern "C" fn destroyPhastPlusStruct(struct_instance: *mut PHastPlusVariant) {
    unsafe { let _ = Box::from_raw(struct_instance); }
}