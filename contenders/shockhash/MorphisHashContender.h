#pragma once

#include "Contender.h"
#include <MorphisHash.h>

template<int l, int ws>
class MorphisHashContender : public Contender {
    public:
        size_t bucketSize;
        morphishash::MorphisHash<l, ws> *morphisHash = nullptr;

        MorphisHashContender(size_t N, size_t bucketSize)
                : Contender(N, 1.0), bucketSize(bucketSize) {
        }

        ~MorphisHashContender() override {
            delete morphisHash;
        }

        std::string name() override {
            return std::string("MorphisHash")
                  + " l=" + std::to_string(l)
                  + " ws=" + std::to_string(ws)
                  + " b=" + std::to_string(bucketSize);
        }

        void construct() override {
            morphisHash = new morphishash::MorphisHash<l, ws>(keys, bucketSize, numThreads);
        }

        size_t sizeBits() override {
            return morphisHash->getBits();
        }

        void performQueries() override {
            doPerformQueries(keys, *morphisHash);
        }

        size_t keyValue(size_t key_index) override {
            return (*morphisHash)(keys[key_index]);
        }
};

void morphisHashContenderRunner(size_t N);
