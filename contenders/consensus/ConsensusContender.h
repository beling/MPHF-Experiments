#pragma once

#include "Contender.h"
#include <ConsensusRecSplit.h>

template <size_t k, double overhead>
class ConsensusContender : public Contender {
    public:
        consensus::ConsensusRecSplit<k, overhead> *consensus = nullptr;

        ConsensusContender(size_t N) : Contender(N, 1.0) {
        }

        ~ConsensusContender() override {
            delete consensus;
        }

        std::string name() override {
            return std::string("Consensus")
                + " k=" + std::to_string(k)
                + " overhead=" + std::to_string(overhead);
        }

        void construct() override {
            (void) keys;
            consensus = new consensus::ConsensusRecSplit<k, overhead>(std::span(keys.begin(), keys.end()));
        }

        size_t sizeBits() override {
            return consensus->getBits();
        }

        void performQueries() override {
            doPerformQueries(keys, *consensus);
        }

        size_t keyValue(size_t key_index) override {
            return (*consensus)(keys[key_index]);
        }
};

void consensusContenderRunner(size_t N);
