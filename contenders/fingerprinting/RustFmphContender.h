#pragma once

#include "RustContender.h"

extern "C" {
void *createFmphStruct();
void constructFmph(void *rustStruct, void *keysStruct, uint16_t gamma);
uint64_t queryFmph(void *rustStruct, void *keysStruct, size_t index);
void queryFmphAll(void *rustStruct, void *keysStruct);
size_t sizeFmph(void *rustStruct);
void destroyFmphStruct(void *rustStruct);
}

class RustFmphContender : public RustContender {
    protected:
        void *rustStruct = nullptr;
        double gamma;
    public:

        RustFmphContender(size_t N, double gamma)
            : RustContender(N), gamma(gamma) {
            rustStruct = createFmphStruct();
        }

        ~RustFmphContender() override {
            destroyFmphStruct(rustStruct);
        }

        std::string name() override {
            return std::string("RustFmphContender")
                + " gamma=" + std::to_string(gamma);
        }

        void construct() override {
            constructFmph(rustStruct, keysRustWrapper, 100 * gamma);
        }

        size_t sizeBits() override {
            return sizeFmph(rustStruct) * 8;
        }

        void performQueries(void *keys) override {
            queryFmphAll(rustStruct, keys);
        }

        size_t keyValue(size_t key_index) override {
            return queryFmph(rustStruct, keysRustWrapper, key_index);
        }

};

void rustFmphContenderRunner(size_t N);
