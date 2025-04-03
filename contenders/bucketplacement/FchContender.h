#pragma once

#include "Contender.h"

#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
#endif
#include <hasher/hasher.hpp>
#include <fch.hpp>
#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif

class FchContender : public Contender {
    public:
        double c;
        mphf::FCH<mphf::hasher::Hasher<>> fchFunction;
        mphf::FCH<mphf::hasher::Hasher<>>::Builder builder;

        FchContender(size_t N, double c)
                : Contender(N, 1.0), c(c), builder(c) {
        }

        std::string name() override {
            return std::string("Fch")
                    + " c=" + std::to_string(c);
        }

        void construct() override {
            builder.build(fchFunction, keys);
        }

        size_t sizeBits() override {
            return fchFunction.num_bits();
        }

        void performQueries() override {
            doPerformQueries(keys, fchFunction);
        }

        size_t keyValue(size_t key_index) override {
            return fchFunction(keys[key_index]);
        }
};

void fchPtHashContenderRunner(size_t N);
