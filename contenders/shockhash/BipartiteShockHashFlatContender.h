#pragma once

#include "Contender.h"
#include <ShockHash2Flat.h>

template<int l>
class BipartiteShockHashFlatContender : public Contender {
    public:
        shockhash::ShockHash2Flat<l> *shockHash = nullptr;

        BipartiteShockHashFlatContender(size_t N)
                : Contender(N, 1.0) {
        }

        ~BipartiteShockHashFlatContender() override {
            delete shockHash;
        }

        std::string name() override {
            return std::string("BipartiteShockHashFlat")
                  + " l=" + std::to_string(l);
        }

        void construct() override {
            shockHash = new shockhash::ShockHash2Flat<l>(keys);
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

void bipartiteShockHashFlatContenderRunner(size_t N);