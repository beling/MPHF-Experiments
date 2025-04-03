#pragma once

#include "Contender.h"
#include <cstddef>

extern "C" {
void initializeRayonThreadPool(uint64_t threads);
void * constructKeys(size_t len);
void pushKey(void *rustStruct, const char *str, size_t len);
void * constructKeysEnd(void *rustStruct);
void destroyKeys(void *rustStruct);
}

class RustContender : public Contender {
    protected:
        void *keysRustWrapper = nullptr;
    public:
        RustContender(size_t N): Contender(N, 1.0) {
            initializeRayonThreadPool(numThreads);
        }

        ~RustContender() override {
            freeKeysWrapper();
        }

        virtual void generateKeys(uint64_t seed) override;

        void performQueries() final {
            performQueries(keysRustWrapper);
        }

        virtual void performQueries(void *keysRustWrapper) = 0;

    private:
        void freeKeysWrapper() {
            if (keysRustWrapper == nullptr) {
                return;
            }
            destroyKeys(keysRustWrapper);
            keysRustWrapper = nullptr;
        }
};
