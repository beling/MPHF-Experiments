use ph::{phast::{self, compressed_array::CompactFast, DefaultCompressedArray, Params, ShiftOnly}, GetSize};
use std::hint::black_box;

pub enum PHastPlusVariant {
    BitsEF(phast::Function2<ph::seeds::BitsFast, ShiftOnly<1>, DefaultCompressedArray>),
    Bits8EF(phast::Function2<ph::seeds::Bits8, ShiftOnly<1>, DefaultCompressedArray>),
    Bits4EF(phast::Function2<ph::seeds::TwoToPowerBitsStatic::<2>, ShiftOnly<1>, DefaultCompressedArray>),
    BitsC(phast::Function2<ph::seeds::BitsFast, ShiftOnly<1>, CompactFast>),
    Bits8C(phast::Function2<ph::seeds::Bits8, ShiftOnly<1>, CompactFast>),
    Bits4C(phast::Function2<ph::seeds::TwoToPowerBitsStatic::<2>, ShiftOnly<1>, CompactFast>),

    BitsEF2(phast::Function2<ph::seeds::BitsFast, ShiftOnly<2>, DefaultCompressedArray>),
    Bits8EF2(phast::Function2<ph::seeds::Bits8, ShiftOnly<2>, DefaultCompressedArray>),
    Bits4EF2(phast::Function2<ph::seeds::TwoToPowerBitsStatic::<2>, ShiftOnly<2>, DefaultCompressedArray>),
    BitsC2(phast::Function2<ph::seeds::BitsFast, ShiftOnly<2>, CompactFast>),
    Bits8C2(phast::Function2<ph::seeds::Bits8, ShiftOnly<2>, CompactFast>),
    Bits4C2(phast::Function2<ph::seeds::TwoToPowerBitsStatic::<2>, ShiftOnly<2>, CompactFast>),

    BitsEF3(phast::Function2<ph::seeds::BitsFast, ShiftOnly<3>, DefaultCompressedArray>),
    Bits8EF3(phast::Function2<ph::seeds::Bits8, ShiftOnly<3>, DefaultCompressedArray>),
    Bits4EF3(phast::Function2<ph::seeds::TwoToPowerBitsStatic::<2>, ShiftOnly<3>, DefaultCompressedArray>),
    BitsC3(phast::Function2<ph::seeds::BitsFast, ShiftOnly<3>, CompactFast>),
    Bits8C3(phast::Function2<ph::seeds::Bits8, ShiftOnly<3>, CompactFast>),
    Bits4C3(phast::Function2<ph::seeds::TwoToPowerBitsStatic::<2>, ShiftOnly<3>, CompactFast>),
    None
}

#[no_mangle]
pub extern "C" fn createPhastPlusStruct() -> *mut PHastPlusVariant {
    Box::into_raw(Box::new(PHastPlusVariant::None))
}

#[no_mangle]
pub extern "C" fn constructPhastPlus(struct_ptr: *mut PHastPlusVariant, keys_ptr: *const Box<[Box<[u8]>]>,
                        multiplier: u8, bits_per_seed: u8, bucket_size100: u16, threads_num: usize, ef: bool) {
    let f = unsafe { &mut *struct_ptr };
    let keys = unsafe { &*keys_ptr };
    *f = match (multiplier, bits_per_seed, ef) {
        (1, 8, true) => PHastPlusVariant::Bits8EF(phast::Function2::with_slice_p_threads_hash_sc(
            &keys[..], &Params::new(ph::seeds::Bits8, bucket_size100), threads_num,
            seedable_hash::BuildDefaultSeededHasher::default(), ShiftOnly::<1>
        )),
        (1, 4, true) => PHastPlusVariant::Bits4EF(phast::Function2::with_slice_p_threads_hash_sc(
            &keys[..], &Params::new(ph::seeds::TwoToPowerBitsStatic::<2>, bucket_size100),
            threads_num, seedable_hash::BuildDefaultSeededHasher::default(), ShiftOnly::<1>
        )),
        (1, _, true) => PHastPlusVariant::BitsEF(phast::Function2::with_slice_p_threads_hash_sc(
            &keys[..], &Params::new(ph::seeds::BitsFast(bits_per_seed), bucket_size100),
            threads_num, seedable_hash::BuildDefaultSeededHasher::default(), ShiftOnly::<1>
        )),

        (1, 8, false) => PHastPlusVariant::Bits8C(phast::Function2::with_slice_p_threads_hash_sc(
            &keys[..], &Params::new(ph::seeds::Bits8, bucket_size100), threads_num,
            seedable_hash::BuildDefaultSeededHasher::default(), ShiftOnly::<1>
        )),
        (1, 4, false) => PHastPlusVariant::Bits4C(phast::Function2::with_slice_p_threads_hash_sc(
            &keys[..], &phast::Params::new(ph::seeds::TwoToPowerBitsStatic::<2>, bucket_size100),
            threads_num, seedable_hash::BuildDefaultSeededHasher::default(), ShiftOnly::<1>
        )),
        (1, _, false) => PHastPlusVariant::BitsC(phast::Function2::with_slice_p_threads_hash_sc(
            &keys[..], &phast::Params::new(ph::seeds::BitsFast(bits_per_seed), bucket_size100),
            threads_num, seedable_hash::BuildDefaultSeededHasher::default(), ShiftOnly::<1>
        )),

        (2, 8, true) => PHastPlusVariant::Bits8EF2(phast::Function2::with_slice_p_threads_hash_sc(
            &keys[..], &Params::new(ph::seeds::Bits8, bucket_size100), threads_num,
            seedable_hash::BuildDefaultSeededHasher::default(), ShiftOnly::<2>
        )),
        (2, 4, true) => PHastPlusVariant::Bits4EF2(phast::Function2::with_slice_p_threads_hash_sc(
            &keys[..], &Params::new(ph::seeds::TwoToPowerBitsStatic::<2>, bucket_size100),
            threads_num, seedable_hash::BuildDefaultSeededHasher::default(), ShiftOnly::<2>
        )),
        (2, _, true) => PHastPlusVariant::BitsEF2(phast::Function2::with_slice_p_threads_hash_sc(
            &keys[..], &Params::new(ph::seeds::BitsFast(bits_per_seed), bucket_size100),
            threads_num, seedable_hash::BuildDefaultSeededHasher::default(), ShiftOnly::<2>
        )),

        (2, 8, false) => PHastPlusVariant::Bits8C2(phast::Function2::with_slice_p_threads_hash_sc(
            &keys[..], &Params::new(ph::seeds::Bits8, bucket_size100), threads_num,
            seedable_hash::BuildDefaultSeededHasher::default(), ShiftOnly::<2>
        )),
        (2, 4, false) => PHastPlusVariant::Bits4C2(phast::Function2::with_slice_p_threads_hash_sc(
            &keys[..], &phast::Params::new(ph::seeds::TwoToPowerBitsStatic::<2>, bucket_size100),
            threads_num, seedable_hash::BuildDefaultSeededHasher::default(), ShiftOnly::<2>
        )),
        (2, _, false) => PHastPlusVariant::BitsC2(phast::Function2::with_slice_p_threads_hash_sc(
            &keys[..], &phast::Params::new(ph::seeds::BitsFast(bits_per_seed), bucket_size100),
            threads_num, seedable_hash::BuildDefaultSeededHasher::default(), ShiftOnly::<2>
        )),

        (3, 8, true) => PHastPlusVariant::Bits8EF3(phast::Function2::with_slice_p_threads_hash_sc(
            &keys[..], &Params::new(ph::seeds::Bits8, bucket_size100), threads_num,
            seedable_hash::BuildDefaultSeededHasher::default(), ShiftOnly::<3>
        )),
        (3, 4, true) => PHastPlusVariant::Bits4EF3(phast::Function2::with_slice_p_threads_hash_sc(
            &keys[..], &Params::new(ph::seeds::TwoToPowerBitsStatic::<2>, bucket_size100),
            threads_num, seedable_hash::BuildDefaultSeededHasher::default(), ShiftOnly::<3>
        )),
        (3, _, true) => PHastPlusVariant::BitsEF3(phast::Function2::with_slice_p_threads_hash_sc(
            &keys[..], &Params::new(ph::seeds::BitsFast(bits_per_seed), bucket_size100),
            threads_num, seedable_hash::BuildDefaultSeededHasher::default(), ShiftOnly::<3>
        )),

        (3, 8, false) => PHastPlusVariant::Bits8C3(phast::Function2::with_slice_p_threads_hash_sc(
            &keys[..], &Params::new(ph::seeds::Bits8, bucket_size100), threads_num,
            seedable_hash::BuildDefaultSeededHasher::default(), ShiftOnly::<3>
        )),
        (3, 4, false) => PHastPlusVariant::Bits4C3(phast::Function2::with_slice_p_threads_hash_sc(
            &keys[..], &phast::Params::new(ph::seeds::TwoToPowerBitsStatic::<2>, bucket_size100),
            threads_num, seedable_hash::BuildDefaultSeededHasher::default(), ShiftOnly::<3>
        )),
        (3, _, false) => PHastPlusVariant::BitsC3(phast::Function2::with_slice_p_threads_hash_sc(
            &keys[..], &phast::Params::new(ph::seeds::BitsFast(bits_per_seed), bucket_size100),
            threads_num, seedable_hash::BuildDefaultSeededHasher::default(), ShiftOnly::<3>
        )),

        _ => panic!("Wrong multiplier!")
    }
}

#[no_mangle]
pub extern "C" fn queryPhastPlus(struct_ptr: *const PHastPlusVariant, keys_ptr: *const Box<[Box<[u8]>]>, index: usize) -> u64 {
    let keys = &unsafe { &*keys_ptr }[..];
    let key = keys[index].as_ref();
    match unsafe { &*struct_ptr } {
        PHastPlusVariant::BitsEF(function2) => function2.get(key) as u64,
        PHastPlusVariant::Bits8EF(function2) => function2.get(key) as u64,
        PHastPlusVariant::Bits4EF(function2) => function2.get(key) as u64,
        PHastPlusVariant::BitsC(function2) => function2.get(key) as u64,
        PHastPlusVariant::Bits8C(function2) => function2.get(key) as u64,
        PHastPlusVariant::Bits4C(function2) => function2.get(key) as u64,
        
        PHastPlusVariant::BitsEF2(function2) => function2.get(key) as u64,
        PHastPlusVariant::Bits8EF2(function2) => function2.get(key) as u64,
        PHastPlusVariant::Bits4EF2(function2) => function2.get(key) as u64,
        PHastPlusVariant::BitsC2(function2) => function2.get(key) as u64,
        PHastPlusVariant::Bits8C2(function2) => function2.get(key) as u64,
        PHastPlusVariant::Bits4C2(function2) => function2.get(key) as u64,
        
        PHastPlusVariant::BitsEF3(function2) => function2.get(key) as u64,
        PHastPlusVariant::Bits8EF3(function2) => function2.get(key) as u64,
        PHastPlusVariant::Bits4EF3(function2) => function2.get(key) as u64,
        PHastPlusVariant::BitsC3(function2) => function2.get(key) as u64,
        PHastPlusVariant::Bits8C3(function2) => function2.get(key) as u64,
        PHastPlusVariant::Bits4C3(function2) => function2.get(key) as u64,
        
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
        PHastPlusVariant::Bits4EF(function2) =>  //query_all(Function2, &keys),
            for key in keys { black_box(function2.get(key.as_ref())); },
        PHastPlusVariant::BitsC(function2) => //query_all(Function2, &keys),
            for key in keys { black_box(function2.get(key.as_ref())); },
        PHastPlusVariant::Bits8C(function2) => //query_all(Function2, &keys),
            for key in keys { black_box(function2.get(key.as_ref())); },
        PHastPlusVariant::Bits4C(function2) => //query_all(Function2, &keys),
            for key in keys { black_box(function2.get(key.as_ref())); },

        PHastPlusVariant::BitsEF2(function2) => //query_all(Function2, &keys),
            for key in keys { black_box(function2.get(key.as_ref())); },
        PHastPlusVariant::Bits8EF2(function2) =>  //query_all(Function2, &keys),
            for key in keys { black_box(function2.get(key.as_ref())); },
        PHastPlusVariant::Bits4EF2(function2) =>  //query_all(Function2, &keys),
            for key in keys { black_box(function2.get(key.as_ref())); },
        PHastPlusVariant::BitsC2(function2) => //query_all(Function2, &keys),
            for key in keys { black_box(function2.get(key.as_ref())); },
        PHastPlusVariant::Bits8C2(function2) => //query_all(Function2, &keys),
            for key in keys { black_box(function2.get(key.as_ref())); },
        PHastPlusVariant::Bits4C2(function2) => //query_all(Function2, &keys),
            for key in keys { black_box(function2.get(key.as_ref())); },

        PHastPlusVariant::BitsEF3(function2) => //query_all(Function2, &keys),
            for key in keys { black_box(function2.get(key.as_ref())); },
        PHastPlusVariant::Bits8EF3(function2) =>  //query_all(Function2, &keys),
            for key in keys { black_box(function2.get(key.as_ref())); },
        PHastPlusVariant::Bits4EF3(function2) =>  //query_all(Function2, &keys),
            for key in keys { black_box(function2.get(key.as_ref())); },
        PHastPlusVariant::BitsC3(function2) => //query_all(Function2, &keys),
            for key in keys { black_box(function2.get(key.as_ref())); },
        PHastPlusVariant::Bits8C3(function2) => //query_all(Function2, &keys),
            for key in keys { black_box(function2.get(key.as_ref())); },
        PHastPlusVariant::Bits4C3(function2) => //query_all(Function2, &keys),
            for key in keys { black_box(function2.get(key.as_ref())); },
        PHastPlusVariant::None => panic!("PHast+ not constructed yet"),
    }
}

#[no_mangle]
pub extern "C" fn sizePhastPlus(struct_ptr: *const PHastPlusVariant) -> usize {
    match unsafe { &*struct_ptr } {
        PHastPlusVariant::BitsEF(function2) => function2.size_bytes(),
        PHastPlusVariant::Bits8EF(function2) => function2.size_bytes(),
        PHastPlusVariant::Bits4EF(function2) => function2.size_bytes(),
        PHastPlusVariant::BitsC(function2) => function2.size_bytes(),
        PHastPlusVariant::Bits8C(function2) => function2.size_bytes(),
        PHastPlusVariant::Bits4C(function2) => function2.size_bytes(),
        
        PHastPlusVariant::BitsEF2(function2) => function2.size_bytes(),
        PHastPlusVariant::Bits8EF2(function2) => function2.size_bytes(),
        PHastPlusVariant::Bits4EF2(function2) => function2.size_bytes(),
        PHastPlusVariant::BitsC2(function2) => function2.size_bytes(),
        PHastPlusVariant::Bits8C2(function2) => function2.size_bytes(),
        PHastPlusVariant::Bits4C2(function2) => function2.size_bytes(),
        
        PHastPlusVariant::BitsEF3(function2) => function2.size_bytes(),
        PHastPlusVariant::Bits8EF3(function2) => function2.size_bytes(),
        PHastPlusVariant::Bits4EF3(function2) => function2.size_bytes(),
        PHastPlusVariant::BitsC3(function2) => function2.size_bytes(),
        PHastPlusVariant::Bits8C3(function2) => function2.size_bytes(),
        PHastPlusVariant::Bits4C3(function2) => function2.size_bytes(),

        PHastPlusVariant::None => panic!("PHast+ not constructed yet"),
    }
}

#[no_mangle]
pub extern "C" fn destroyPhastPlusStruct(struct_instance: *mut PHastPlusVariant) {
    unsafe { let _ = Box::from_raw(struct_instance); }
}
