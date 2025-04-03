#pragma once

#include "RustContender.h"

extern "C" {
    void *createPhastStruct();
    void constructPhast(void *rustStruct, void *keysStruct, uint8_t bits_per_seed, uint16_t bucket_size100, size_t threads);
    uint64_t queryPhast(void *rustStruct, void *keysStruct, size_t index);
    void queryPhastAll(void *rustStruct, void *keysStruct);
    size_t sizePhast(void *rustStruct);
    void destroyPhastStruct(void *rustStruct);
}

class RustPhastContender : public RustContender {
    protected:
        void *rustStruct = nullptr;
        uint8_t bits_per_seed;
        uint16_t bucket_size100;
    public:
        RustPhastContender(size_t N, uint8_t bits_per_seed, uint16_t bucket_size100)
            : RustContender(N), bits_per_seed(bits_per_seed), bucket_size100(bucket_size100) {
            rustStruct = createPhastStruct();
        }

        ~RustPhastContender() override {
            destroyPhastStruct(rustStruct);
        }

        std::string name() override {
            return std::string("RustPHast")
                + " bits_per_seed=" + std::to_string(bits_per_seed)
                + " bucket_size100=" + std::to_string(bucket_size100);
        }

        void construct() override {
            constructPhast(rustStruct, keysRustWrapper, bits_per_seed, bucket_size100, numThreads);
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

void rustPHastContenderRunner(size_t N);
