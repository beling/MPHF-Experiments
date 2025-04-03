#pragma once

#include <cstddef>
#include <cstdint>
#include <random>
#include <iostream>
#include <chrono>
#include <bytehamster/util/XorShift64.h>
#include <unistd.h>
#include <thread>
#include <span>

#define DO_NOT_OPTIMIZE(value) asm volatile ("" : : "r,m"(value) : "memory")

template<typename F> inline
std::vector<std::string> generateInputDataTo(size_t N, uint64_t seed, F out) {
    std::vector<std::string> inputData;
    inputData.reserve(N);
    bytehamster::util::XorShift64 prng(seed);
    std::cout<<"Generating input"<<std::flush;
    char string[200];
    for (size_t i = 0; i < N; i++) {
        if ((i % (N/5)) == 0) {
            std::cout<<"\rGenerating input: "<<100l*i/N<<"%"<<std::flush;
        }
        size_t length = 10 + prng((30 - 10) * 2);
        for (std::size_t k = 0; k < (length + sizeof(uint64_t))/sizeof(uint64_t); ++k) {
            ((uint64_t*) string)[k] = prng();
        }
        // Repair null bytes
        for (std::size_t k = 0; k < length; ++k) {
            if (string[k] == 0) {
                string[k] = 1 + prng(254);
            }
        }
        string[length] = 0;
        out(string, length);
    }
    std::cout<<"\rInput generation complete."<<std::endl;
    return inputData;
}

class Contender {
    public:
        static size_t numQueries;
        static size_t numThreads;
        static size_t numQueryThreads;
        static size_t seed;
        static bool skipTests;

        const size_t N;
        const double loadFactor;
        const double mByN;
        const size_t M;
        long constructionTimeMicroseconds = 0;
        long queryTimeMilliseconds = 0;

        std::vector<std::string> keys;

        Contender(size_t N, double loadFactor)
                : N(N), loadFactor(loadFactor), mByN(1.0 / loadFactor), M(N * mByN) {
        }

        virtual ~Contender() = default;

        virtual std::string name() = 0;
        virtual size_t sizeBits() = 0;
        virtual void construct() = 0;

        virtual void generateKeys(uint64_t seed);

        virtual void beforeConstruction() {}
        virtual void beforeQueries() {}

        virtual void performQueries() = 0;
        virtual void performTest() {
            double eps = 1.0001; // Rounding with load factor variables
            std::vector<bool> taken(M * eps);
            for (size_t i = 0; i < N; i++) {
                // Some contenders expect non-const keys but actually use them as const.
                size_t retrieved = keyValue(i);
                if (retrieved > M * eps) {
                    std::cout << "Error: Range wrong. Hash function returned " << retrieved
                            << " but maximum should be " << (M*eps) << " (actually " << M << ")" << std::endl;
                    throw std::logic_error("Range wrong");
                }
                if (taken[retrieved]) {
                    std::cout<<"Error: Collision: Key #"<<i<<"/"<<N<<" resulted in "<<retrieved<<std::endl;
                    std::cout<<"Aborting query"<<std::endl;
                    throw std::logic_error("Collision");
                }
                taken[retrieved] = true;
            }
        }

        void run(bool shouldPrintResult = true); // In cpp file

        void printResult(std::string additional = ""); // In cpp file

        virtual size_t keyValue(size_t key_index) = 0;

    protected:
        template<typename F>
        void doPerformQueries(const std::span<std::string> keys, F &hashFunction) {
            for (const std::string &key : keys) {
                size_t retrieved = hashFunction(const_cast<std::string &>(key));
                // Some contenders expect non-const keys but actually use them as const.
                DO_NOT_OPTIMIZE(retrieved);
            }
        }
};
