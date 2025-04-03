#pragma once

#include "Contender.h"
#include <ShockHash2.h>

template<int l>
class BipartiteShockHashContender : public Contender {
    public:
        size_t bucketSize;
        shockhash::ShockHash2<l> *shockHash = nullptr;

        BipartiteShockHashContender(size_t N, size_t bucketSize)
                : Contender(N, 1.0), bucketSize(bucketSize) {
        }

        ~BipartiteShockHashContender() override {
            delete shockHash;
        }

        std::string name() override {
            return std::string("BipartiteShockHash")
                  + " l=" + std::to_string(l)
                  + " b=" + std::to_string(bucketSize);
        }

        void construct() override {
            shockHash = new shockhash::ShockHash2<l>(keys, bucketSize, numThreads);
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

void bipartiteShockHashContenderRunner(size_t N);
