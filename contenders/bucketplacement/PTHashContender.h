#pragma once

#include <memory> // Otherwise PTHash misses an import
#include <pthash.hpp>
#undef MAX_BUCKET_SIZE
#include "Contender.h"

template <bool minimal, typename encoder, typename bucketer = pthash::skew_bucketer>
class PTHashContender : public Contender {
    public:
        double lambda;
        double internalLoadFactor;
        pthash::single_phf<pthash::murmurhash2_64, bucketer, encoder, minimal, pthash::xor_displacement> pthashFunction;

        PTHashContender(size_t N, double loadFactor, double lambda)
                : Contender(N, minimal ? 1.0 : loadFactor), lambda(lambda), internalLoadFactor(loadFactor) {
        }

        std::string name() override {
            return std::string("PTHash")
                    + " minimal=" + std::to_string(minimal)
                    + " lambda=" + std::to_string(lambda)
                    + " encoder=" + encoder::name()
                    + " lf=" + std::to_string(internalLoadFactor);
        }

        void construct() override {
            pthash::build_configuration config;
            config.lambda = lambda;
            config.alpha = internalLoadFactor;
            config.num_threads = numThreads;
            config.minimal = minimal;
            config.verbose = false;
            config.search = pthash::xor_displacement;
            pthashFunction.build_in_internal_memory(keys.begin(), keys.size(), config);
        }

        size_t sizeBits() override {
            return pthashFunction.num_bits();
        }

        void performQueries() override {
            doPerformQueries(keys, pthashFunction);
        }

        size_t keyValue(size_t key_index) override {
            return pthashFunction(keys[key_index]);
        }
};

void ptHashContenderRunner(size_t N, double loadFactor, bool minimalOnly);
