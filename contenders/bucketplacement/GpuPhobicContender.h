#pragma once

#include <memory> // Otherwise PTHash misses an import
#include <pthash.hpp>
#undef MAX_BUCKET_SIZE
#include <phobic_gpu_mphf.hpp>
#include "Contender.h"

class GpuPhobicContender : public Contender {
    public:
        float averageBucketSize;
        size_t partitionSize;
        float tradeoff;
        phobicgpu::MPHFbuilder builder;
        using PilotEncoder = phobicgpu::interleaved_encoder_dual<phobicgpu::rice, pthash::compact>;
        using PartitionEncoder = phobicgpu::diff_partition_encoder<phobicgpu::compact>;
        phobicgpu::MPHF<PilotEncoder, PartitionEncoder, phobicgpu::xxhash> f;

        GpuPhobicContender(size_t N, float averageBucketSize, size_t partitionSize, float tradeoff)
                : Contender(N, 1.0), averageBucketSize(averageBucketSize), partitionSize(partitionSize),
                  tradeoff(tradeoff),
                  builder(phobicgpu::MPHFconfig(averageBucketSize, partitionSize)) {
            f.getPilotEncoder().setEncoderTradeoff(tradeoff);
            //App::getInstance().printDebugInfo();
        }

        std::string name() override {
            return std::string("GpuPhobic")
                  + " partitionSize=" + std::to_string(partitionSize)
                  + " A=" + std::to_string(averageBucketSize)
                  + " tradeoff=" + std::to_string(tradeoff)
                  + " pilotEncoder=" + typeid(PilotEncoder).name()
                  + " partitionEncoder=" + typeid(PartitionEncoder).name();
        }

        void construct() override {
            builder.build(keys, f);
        }

        size_t sizeBits() override {
            return f.getBitsPerKey() * N;
        }

        void performQueries() override {
            doPerformQueries(keys, f);
        }

        size_t keyValue(size_t key_index) override {
            return f(keys[key_index]);
        }
};

void gpuPhobicContenderRunner(size_t N);
