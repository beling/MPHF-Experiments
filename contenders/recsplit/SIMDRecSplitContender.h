#pragma once

#include <function/SIMDRecSplit.hpp>
#include "Contender.h"

template<int l>
class SIMDRecSplitContender : public Contender {
    public:
        size_t bucketSize;
        bez::function::SIMDRecSplit<l> *recSplit = nullptr;

        SIMDRecSplitContender(size_t N, size_t bucketSize)
                : Contender(N, 1.0), bucketSize(bucketSize) {
        }

        ~SIMDRecSplitContender() override {
            delete recSplit;
        }

        std::string name() override {
            return std::string("SIMDRecSplit")
                  + " l=" + std::to_string(l)
                  + " b=" + std::to_string(bucketSize);
        }

        void beforeConstruction() override {
            (void) keys;
        }

        void construct() override {
            recSplit = new bez::function::SIMDRecSplit<l>(keys, bucketSize, numThreads);
        }

        size_t sizeBits() override {
            return recSplit->getBits();
        }

        void performQueries() override {
            doPerformQueries(keys, *recSplit);
        }

        size_t keyValue(size_t key_index) override {
            return (*recSplit)(keys[key_index]);
        }
};

void simdRecSplitContenderRunner(size_t N);
