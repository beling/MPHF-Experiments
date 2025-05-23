#pragma once

#include <cmph.h>

#include <utility>
#undef MAX_BUCKET_SIZE
#include "Contender.h"

class ChmContender : public Contender {
    public:
        cmph_t *mphf = nullptr;
        cmph_io_adapter_t *source = nullptr;
        const char **data;
        double c;

        ChmContender(size_t N, double loadFactor, double c, bool minimal)
                : Contender(N, minimal ? 1.0 : loadFactor), c(c) {
            data = static_cast<const char **>(malloc(N * sizeof(char*)));
        }

        ~ChmContender() override {
            if (mphf != nullptr) {
                cmph_destroy(mphf);
            }
            free(source);
            free(data);
        }

        std::string name() override {
            return std::string("cmph-CHM")
                    + " c=" + std::to_string(c);
        }

        void beforeConstruction() override {
            std::cout << "Converting input" << std::endl;
            for (size_t i = 0; i < N; i++) {
                data[i] = keys[i].c_str();
            }
            source = cmph_io_vector_adapter((char **)data, N); // They even do the const cast in their readme file
        }

        void construct() override {
            (void) keys;
            //Create mphf
            cmph_config_t *config = cmph_config_new(source);
            cmph_config_set_algo(config, CMPH_CHM);
            cmph_config_set_verbosity(config, 0);
            cmph_config_set_graphsize(config, c);
            mphf = cmph_new(config);

            cmph_config_destroy(config);
            if (mphf == nullptr) {
                throw std::logic_error("Unable to create minimum perfect hashing function");
            }
        }

        size_t sizeBits() override {
            return 8 * cmph_packed_size(mphf);
        }

        void performQueries() override {
            auto x = [&] (std::string &key) {
                return cmph_search(mphf, key.c_str(), key.length());
            };
            doPerformQueries(keys, x);
        }

        size_t keyValue(size_t key_index) override {
            return cmph_search(mphf, keys[key_index].c_str(), keys[key_index].length());
        }
};

void chmContenderRunner(size_t N, double loadFactor);
