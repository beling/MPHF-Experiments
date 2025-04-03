#pragma once

#include <sux/function/RecSplit.hpp>
#include "Contender.h"

template<int l>
class RecSplitContender : public Contender {
    public:
        size_t bucketSize;
        sux::function::RecSplit<l> *recSplit = nullptr;

        RecSplitContender(size_t N, size_t bucketSize)
                : Contender(N, 1.0), bucketSize(bucketSize) {
        }

        ~RecSplitContender() override {
            delete recSplit;
        }

        std::string name() override {
            return std::string("RecSplit")
                  + " l=" + std::to_string(l)
                  + " b=" + std::to_string(bucketSize);
        }

        void beforeConstruction() override {
            (void) keys;
        }

        void construct() override {
            recSplit = new sux::function::RecSplit<l>(keys, bucketSize);
        }

        size_t sizeBits() override {
            return recSplit->bitCount();
        }

        void performQueries() override {
            doPerformQueries(keys, *recSplit);
        }

        size_t keyValue(size_t key_index) override {
            return (*recSplit)(keys[key_index]);
        }
};

void recSplitContenderRunner(size_t N);
