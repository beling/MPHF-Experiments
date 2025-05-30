#pragma once

extern "C" {
#include <mphf.h>
}
#include "Contender.h"

class MphfWbpmContender : public Contender {
    public:
        MPHFQuerier *mphfq = nullptr;
        MPHFParameters sParams;

        MphfWbpmContender(size_t N, MPHFParameters sParams)
                : Contender(N, 1.0), sParams(sParams) {
        }

        ~MphfWbpmContender() override {
            MPHFQuerierFree(mphfq);
        }

        std::string name() override {
            return std::string("MphfWbpm")
                + " blockSize=" + std::to_string(sParams.nEltsPerBlock)
                + " litsPerRow=" + std::to_string(sParams.xsfp.nLitsPerRow)
                + " efficiency=" + std::to_string(sParams.xsfp.fEfficiency);
        }

        void construct() override {
            MPHFBuilder *mphfb = MPHFBuilderAlloc(N);
            for (const std::string &key : keys) {
                if(MPHFBuilderAddElement(mphfb, key.data(), key.length()) != 0) {
                    fprintf(stderr, "Element insertion failed...exiting\n");
                    return;
                }
            }
            mphfq = MPHFBuilderFinalize(mphfb,sParams, numThreads);
            MPHFBuilderFree(mphfb);
        }

        size_t sizeBits() override {
            return MPHFSize(mphfq);
        }

        void performQueries() override {
            auto x = [&] (std::string &key) {
                return MPHFQuery(mphfq, key.data(), key.length());
            };
            doPerformQueries(keys, x);
        }

        size_t keyValue(size_t key_index) override {
            return MPHFQuery(mphfq, keys[key_index].data(), keys[key_index].length());
        }
};

void mphfWbpmContenderRunner(size_t N);