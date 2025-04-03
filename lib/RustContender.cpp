#include "RustContender.h"

void RustContender::generateKeys(uint64_t seed) {
    auto keys = constructKeys(N);
    generateInputDataTo(N, seed, [=](const char* string, std::size_t length) {
        pushKey(keys, string, length);
    });
    keysRustWrapper = constructKeysEnd(keys);
}