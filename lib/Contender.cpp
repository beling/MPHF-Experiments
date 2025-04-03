#include "Contender.h"

#include <cstddef>
#include <string>
#include <vector>
#include <iostream>
#include <chrono>
#include <bytehamster/util/XorShift64.h>




std::vector<std::string> generateInputData(size_t N, uint64_t seed) {
    std::vector<std::string> inputData;
    inputData.reserve(N);
    generateInputDataTo(N, seed, [&](const char* string, std::size_t length) {
        inputData.emplace_back(string, length);
    });
    return inputData;
}

void Contender::generateKeys(uint64_t seed) {
    keys = generateInputData(N, seed);
}

void Contender::run(bool shouldPrintResult) {
    std::cout <<  std::endl;
    std::cout << "Contender: " << name().substr(0, name().find(' ')) << std::endl;

    if (seed == 0) {
        auto time = std::chrono::system_clock::now();
        seed = std::chrono::duration_cast<std::chrono::milliseconds>(time.time_since_epoch()).count();
    }
    bytehamster::util::XorShift64 prng(seed);
    for (size_t i = 0; i < 10; i++) {
        prng(); // Ensure that first few generated seeds don't have too many zeroes when users pick small seeds
    }
    std::cout << "Seed: " << seed << std::endl;
    generateKeys(prng());

    std::cout << "Cooldown" << std::endl;
    usleep(1000*1000);
    std::cout << "Constructing" << std::endl;

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    try {
        construct();
    } catch (const std::exception& e) {
        std::cout<<"Error: "<<e.what()<<std::endl;
        return;
    }
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    constructionTimeMicroseconds = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();

    if (!skipTests) {
        std::cout<<"Testing"<<std::endl;
        performTest();
    }

    queryTimeMilliseconds = 0;
    if (numQueries > 0) {
        std::cout << "Cooldown" << std::endl;
        usleep(1000*1000);
        std::cout<<"Querying"<<std::endl;
        begin = std::chrono::steady_clock::now();
        performQueries();
        end = std::chrono::steady_clock::now();
        queryTimeMilliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
    }
    if (shouldPrintResult) {
        printResult();
    }
}

void Contender::printResult(std::string additional) {
    // Some competitors print stuff when determining their space consumption
    double bitsPerElement = (double) sizeBits() / N;
    std::cout << "RESULT"
              << " name=" << name()
              << " bitsPerElement=" << bitsPerElement
              << " constructionTimeMilliseconds=" << (constructionTimeMicroseconds < 10000
                                    ? std::to_string(0.001 * constructionTimeMicroseconds)
                                    : std::to_string(constructionTimeMicroseconds / 1000))
              << " queryTimeMilliseconds=" << queryTimeMilliseconds
              << " numQueries=" << numQueries
              << " numQueriesTotal=" << (numQueries * numQueryThreads)
              << " N=" << N
              << " loadFactor=" << loadFactor
              << " threads=" << numThreads
              << " queryThreads=" << numQueryThreads
              << additional
              << std::endl;
}

size_t Contender::numQueries = 5e7;
size_t Contender::numThreads = 1;
size_t Contender::numQueryThreads = 1;
size_t Contender::seed = 0;
bool Contender::skipTests = false;
