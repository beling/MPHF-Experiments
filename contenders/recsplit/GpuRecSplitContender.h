#pragma once

#include <function/GPURecSplit.cuh>
#include "Contender.h"

template<int l>
class GpuRecSplitContender : public Contender {
    public:
        size_t bucketSize;
        bez::function::GPURecSplit<l> *recSplit = nullptr;

        GpuRecSplitContender(size_t N, size_t bucketSize)
                : Contender(N, 1.0), bucketSize(bucketSize) {
        }

        ~GpuRecSplitContender() override {
            delete recSplit;
        }

        std::string name() override {
            return std::string("GpuRecSplitContender")
                  + " l=" + std::to_string(l)
                  + " b=" + std::to_string(bucketSize);
        }

        void beforeConstruction() override {
            (void) keys;
        }

        void construct() override {
            recSplit = new bez::function::GPURecSplit<l>(keys, bucketSize, numThreads);
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

template <int l>
void gpuRecSplitTestMulti(size_t N) {
    {GpuRecSplitContender<l>(N, l).run();}
    {GpuRecSplitContender<l>(N, 100).run();}
    {GpuRecSplitContender<l>(N, 500).run();}
    {GpuRecSplitContender<l>(N, 2000).run();}
}

void gpuRecSplitContenderRunner(size_t N) {
    gpuRecSplitTestMulti<4>(N);
    gpuRecSplitTestMulti<6>(N);
    gpuRecSplitTestMulti<8>(N);
    gpuRecSplitTestMulti<10>(N);
    gpuRecSplitTestMulti<12>(N);
    gpuRecSplitTestMulti<16>(N);
    gpuRecSplitTestMulti<18>(N);
    gpuRecSplitTestMulti<20>(N);
}
