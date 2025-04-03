#pragma once

#include "RustContender.h"

extern "C" {
void *createFmphGoStruct();
void constructFmphGo(void *rustStruct, void *keys, uint16_t gamma);
uint64_t queryFmphGo(void *rustStruct, void *keysStruct, size_t index);
void queryFmphGoAll(void *rustStruct, void *keys);
size_t sizeFmphGo(void *rustStruct);
void destroyFmphGoStruct(void *rustStruct);
}

class RustFmphGoContender : public RustContender {
    protected:
        void *rustStruct = nullptr;
        double gamma;
    public:

        RustFmphGoContender(size_t N, double gamma)
            : RustContender(N), gamma(gamma) {
            rustStruct = createFmphGoStruct();
        }

        ~RustFmphGoContender() override {
            destroyFmphGoStruct(rustStruct);
        }

        std::string name() override {
            return std::string("RustFmphGoContender")
                + " gamma=" + std::to_string(gamma);
        }

        void construct() override {
            constructFmphGo(rustStruct, keysRustWrapper, 100 * gamma);
        }

        size_t sizeBits() override {
            return sizeFmphGo(rustStruct) * 8;
        }

        void performQueries(void *keys) override {
            queryFmphGoAll(rustStruct, keys);
        }

        size_t keyValue(size_t key_index) override {
            return queryFmphGo(rustStruct, keysRustWrapper, key_index);
        }

};

void rustFmphGoContenderRunner(size_t N);
