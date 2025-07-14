#pragma once

#include "RustContender.h"
#include <cstdint>

extern "C" {
    void *createPhastStruct();
    void constructPhast(void *rustStruct, void *keysStruct, uint8_t bits_per_seed, uint16_t bucket_size100, size_t threads, bool ef);
    uint64_t queryPhast(void *rustStruct, void *keysStruct, size_t index);
    void queryPhastAll(void *rustStruct, void *keysStruct);
    size_t sizePhast(void *rustStruct);
    void destroyPhastStruct(void *rustStruct);

    void *createPhastPlusStruct();
    void constructPhastPlus(void *rustStruct, void *keysStruct, uint8_t multiplier, uint8_t bits_per_seed, uint16_t bucket_size100, size_t threads, bool ef);
    uint64_t queryPhastPlus(void *rustStruct, void *keysStruct, size_t index);
    void queryPhastPlusAll(void *rustStruct, void *keysStruct);
    size_t sizePhastPlus(void *rustStruct);
    void destroyPhastPlusStruct(void *rustStruct);

    void *createPhastPlusWrappedStruct();
    void constructPhastPlusWrapped(void *rustStruct, void *keysStruct, uint8_t multiplier, uint8_t bits_per_seed, uint16_t bucket_size100, uint16_t preferred_slice_len, size_t threads, bool ef);
    uint64_t queryPhastPlusWrapped(void *rustStruct, void *keysStruct, size_t index);
    void queryPhastPlusWrappedAll(void *rustStruct, void *keysStruct);
    size_t sizePhastPlusWrapped(void *rustStruct);
    void destroyPhastPlusWrappedStruct(void *rustStruct);
}

class RustPhastContender : public RustContender {
    protected:
        void *rustStruct = nullptr;
        uint8_t bits_per_seed;
        uint16_t bucket_size100;
        bool use_ef;
    public:
        RustPhastContender(size_t N, uint8_t bits_per_seed, uint16_t bucket_size100, bool use_ef)
            : RustContender(N), bits_per_seed(bits_per_seed), bucket_size100(bucket_size100), use_ef(use_ef) {
            rustStruct = createPhastStruct();
        }

        ~RustPhastContender() override {
            destroyPhastStruct(rustStruct);
        }

        std::string name() override {
            return std::string("RustPHast")
                + " bits_per_seed=" + std::to_string(bits_per_seed)
                + " bucket_size100=" + std::to_string(bucket_size100)
                + " encoder=" + (use_ef ? "EF" : "C");
        }

        void construct() override {
            constructPhast(rustStruct, keysRustWrapper, bits_per_seed, bucket_size100, numThreads, use_ef);
        }

        size_t sizeBits() override {
            return sizePhast(rustStruct) * 8;
        }

        void performQueries(void *keys) override {
            queryPhastAll(rustStruct, keys);
        }

        size_t keyValue(size_t key_index) override {
            return queryPhast(rustStruct, keysRustWrapper, key_index);
        }
};

void rustPHastContenderRunnerWithEf(size_t N, bool use_ef);

void rustPHastContenderRunner(size_t N);



class RustPhastPlusContender : public RustContender {
    protected:
        void *rustStruct = nullptr;
        uint8_t multiplier;
        uint8_t bits_per_seed;
        uint16_t bucket_size100;
        bool use_ef;
    public:
        RustPhastPlusContender(size_t N, uint8_t multiplier, uint8_t bits_per_seed, uint16_t bucket_size100, bool use_ef)
            : RustContender(N), multiplier(multiplier), bits_per_seed(bits_per_seed), bucket_size100(bucket_size100), use_ef(use_ef) {
            rustStruct = createPhastPlusStruct();
        }

        ~RustPhastPlusContender() override {
            destroyPhastPlusStruct(rustStruct);
        }

        std::string name() override {
            return std::string("RustPHast+")
                + " multiplier=" + std::to_string(multiplier)
                + " bits_per_seed=" + std::to_string(bits_per_seed)
                + " bucket_size100=" + std::to_string(bucket_size100)
                + " encoder=" + (use_ef ? "EF" : "C");
        }

        void construct() override {
            constructPhastPlus(rustStruct, keysRustWrapper, multiplier, bits_per_seed, bucket_size100, numThreads, use_ef);
        }

        size_t sizeBits() override {
            return sizePhastPlus(rustStruct) * 8;
        }

        void performQueries(void *keys) override {
            queryPhastPlusAll(rustStruct, keys);
        }

        size_t keyValue(size_t key_index) override {
            return queryPhastPlus(rustStruct, keysRustWrapper, key_index);
        }
};

void rustPHastPlusContenderRunnerWithEf(size_t N, bool use_ef);

void rustPHastPlusContenderRunner(size_t N);



class RustPhastPlusWrappedContender : public RustContender {
    protected:
        void *rustStruct = nullptr;
        uint8_t multiplier;
        uint8_t bits_per_seed;
        uint16_t bucket_size100;
        uint16_t preferred_slice_len;
        bool use_ef;
    public:
        RustPhastPlusWrappedContender(size_t N, uint8_t multiplier, uint8_t bits_per_seed, uint16_t bucket_size100, uint16_t preferred_slice_len, bool use_ef)
            : RustContender(N), multiplier(multiplier), bits_per_seed(bits_per_seed), bucket_size100(bucket_size100),
                preferred_slice_len(preferred_slice_len), use_ef(use_ef)
        {
            rustStruct = createPhastPlusWrappedStruct();
        }

        ~RustPhastPlusWrappedContender() override {
            destroyPhastPlusWrappedStruct(rustStruct);
        }

        std::string name() override {
            return std::string("RustPHast+wrap")
                + " multiplier=" + std::to_string(multiplier)
                + " bits_per_seed=" + std::to_string(bits_per_seed)
                + " bucket_size100=" + std::to_string(bucket_size100)
                + " preferred_slice_len=" + std::to_string(preferred_slice_len)
                + " encoder=" + (use_ef ? "EF" : "C");
        }

        void construct() override {
            constructPhastPlusWrapped(rustStruct, keysRustWrapper, multiplier, bits_per_seed, bucket_size100, preferred_slice_len, numThreads, use_ef);
        }

        size_t sizeBits() override {
            return sizePhastPlusWrapped(rustStruct) * 8;
        }

        void performQueries(void *keys) override {
            queryPhastPlusWrappedAll(rustStruct, keys);
        }

        size_t keyValue(size_t key_index) override {
            return queryPhastPlusWrapped(rustStruct, keysRustWrapper, key_index);
        }
};

void rustPHastPlusWrappedContenderRunnerWithEf(size_t N, bool use_ef);

void rustPHastPlusWrappedContenderRunner(size_t N);