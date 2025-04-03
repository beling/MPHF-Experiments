#pragma once

#include "Contender.h"
#include <ShockHash.h>

template<int l, bool rotationFitting = true>
class ShockHashContender : public Contender {
    public:
        size_t bucketSize;
        shockhash::ShockHash<l, rotationFitting> *shockHash = nullptr;

        ShockHashContender(size_t N, size_t bucketSize)
                : Contender(N, 1.0), bucketSize(bucketSize) {
        }

        ~ShockHashContender() override {
            delete shockHash;
        }

        std::string name() override {
            return std::string("ShockHash")
                  + " rotationFitting=" + std::to_string(rotationFitting)
                  + " l=" + std::to_string(l)
                  + " b=" + std::to_string(bucketSize);
        }

        void construct() override {
            shockHash = new shockhash::ShockHash<l, rotationFitting>(keys, bucketSize);
        }

        size_t sizeBits() override {
            return shockHash->getBits();
        }

        void performQueries() override {
            doPerformQueries(keys, *shockHash);
        }

        size_t keyValue(size_t key_index) override {
            return (*shockHash)(keys[key_index]);
        }
};

void shockHashContenderRunner(size_t N);
