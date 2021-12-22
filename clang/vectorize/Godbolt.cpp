// turn off slp vectorize
// https://stackoverflow.com/questions/51461924/how-to-disable-vectorization-in-clang

// ~/llvm/release/build/bin/clang++ -O2 -emit-llvm -S -fno-slp-vectorize Godbolt.cpp -o Godbolt.no-slp-vectorize.ll
// ~/llvm/release/build/bin/clang++ -O2 -emit-llvm -S -fslp-vectorize Godbolt.cpp -o Godbolt.slp-vectorize.ll

#include <cstdint>

using std::uint32_t;

template <uint32_t N>
int32_t countsearch(const uint32_t *base, uint32_t needle) {
    uint32_t count = 0;
    for (const uint32_t *probe = base; probe < base + N; probe++) {
        if (*probe < needle)
            count++;
    }
    return count;
}

template
int32_t countsearch<10>(const uint32_t *base, uint32_t needle);
