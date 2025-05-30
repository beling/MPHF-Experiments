#pragma once

#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
#endif
#include <BooPHF.h>
#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif

#include <bytehamster/util/MurmurHash64.h>
#include "Contender.h"

class BBHashContender : public Contender {
    public:
        typedef boomphf::SingleHashFunctor<u_int64_t> hasher_t;
        typedef boomphf::mphf<u_int64_t, hasher_t> boophf_t;
        boophf_t * bbhash = nullptr;
        std::vector<u_int64_t> mhcs;
        double gamma;
        double perc_elem_loaded;

        BBHashContender(size_t N, double gamma, double perc_elem_loaded = 0.03)
                : Contender(N, 1.0), gamma(gamma), perc_elem_loaded(perc_elem_loaded) {
        }

        ~BBHashContender() override {
            delete bbhash;
        }

        std::string name() override {
            return std::string("BBHash")
                + " gamma=" + std::to_string(gamma)
                + " perc_elem_loaded=" + std::to_string(perc_elem_loaded);
        }

        void beforeConstruction() override {
            for (const std::string &s : keys) {
                mhcs.emplace_back(bytehamster::util::MurmurHash64(s));
            }
        }

        void construct() override {
            (void) keys;
            bbhash = new boomphf::mphf<u_int64_t,hasher_t>(mhcs.size(), mhcs,
                    /* num_thread */ numThreads, /* gamma */ gamma, /* writeEach */ true,
                    /* progress */ false, perc_elem_loaded);
        }

        size_t sizeBits() override {
            return bbhash->totalBitSize();
        }

        void performQueries() override {
            auto x = [&] (std::string &key) {
                return bbhash->lookup(bytehamster::util::MurmurHash64(key));
            };
            doPerformQueries(keys, x);
        }

        size_t keyValue(size_t key_index) override {
            return bbhash->lookup(bytehamster::util::MurmurHash64(keys[key_index]));
        }
};

void bbHashContenderRunner(size_t N);