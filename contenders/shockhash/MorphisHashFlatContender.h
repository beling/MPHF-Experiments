#pragma once

#include "Contender.h"
#include <MorphisHashFlat.h>

template<int l, int eb, int ws>
class MorphisHashFlatContender : public Contender {
    public:
        morphishash::MorphisHashFlat<l, ws, eb> *morphisHashFlat = nullptr;

        MorphisHashFlatContender(size_t N)
                : Contender(N, 1.0) {
        }

        ~MorphisHashFlatContender() override {
            delete morphisHashFlat;
        }

        std::string name() override {
            return std::string("MorphisHashFlat")
                + " eb=" + std::to_string(eb)
                + " ws=" + std::to_string(ws)
                + " l=" + std::to_string(l);
        }

        void construct() override {
            morphisHashFlat = new morphishash::MorphisHashFlat<l, ws, eb>(keys);
        }

        size_t sizeBits() override {
            return morphisHashFlat->getBits();
        }

        void performQueries() override {
            doPerformQueries(keys, *morphisHashFlat);
        }

        size_t keyValue(size_t key_index) override {
            return (*morphisHashFlat)(keys[key_index]);
        }
};

void morphisHashFlatContenderRunner(size_t N);
