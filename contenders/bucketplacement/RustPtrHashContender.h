#pragma once

#include "RustContender.h"

extern "C" {
    void *createPtrHashStruct();
    void constructPtrHash(void *rustStruct, void *keysStruct, uint64_t variant, double lambda);
    uint64_t queryPtrHash(void *rustStruct, void *keysStruct, size_t index);
    void queryPtrHashAll(void *rustStruct, void *keysStruct);
    size_t sizePtrHash(void *rustStruct);
    void destroyPtrHashStruct(void *rustStruct);
}

class RustPtrHashContender : public RustContender {
    protected:
        void *rustStruct = nullptr;
        uint64_t variant;
        double lambda;
    public:
        static constexpr int VARIANT_LINEAR_VEC = 1;
        static constexpr int VARIANT_SQUARE_VEC = 2;
        static constexpr int VARIANT_CUBIC_VEC = 3;
        static constexpr int VARIANT_LINEAR_EF = 4;
        static constexpr int VARIANT_SQUARE_EF = 5;
        static constexpr int VARIANT_CUBIC_EF = 6;

        RustPtrHashContender(size_t N, uint64_t variant, double lambda)
            : RustContender(N), variant(variant), lambda(lambda) {
            rustStruct = createPtrHashStruct();
        }

        ~RustPtrHashContender() override {
            destroyPtrHashStruct(rustStruct);
        }

        std::string name() override {
            return std::string("RustPtrHash")
                + " variant=" + std::to_string(variant)
                + " lambda=" + std::to_string(lambda);
        }

        void construct() override {
            constructPtrHash(rustStruct, keysRustWrapper, variant, lambda);
        }

        size_t sizeBits() override {
            return sizePtrHash(rustStruct) * 8;
        }

        void performQueries(void *keys) override {
            queryPtrHashAll(rustStruct, keys);
        }

        size_t keyValue(size_t key_index) override {
            return queryPtrHash(rustStruct, keysRustWrapper, key_index);
        }
};

void rustPtrHashContenderRunner(size_t N);
