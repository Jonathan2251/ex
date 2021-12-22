// turn off slp vectorize
// https://stackoverflow.com/questions/51461924/how-to-disable-vectorization-in-clang

// work for x86_64 but not for riscv64
// ~/llvm/release/build/bin/clang++ -O2 -emit-llvm -S -fno-slp-vectorize Godbolt.cpp -o Godbolt.no-slp-vectorize.ll -target x86_64-unknown-linux-gnu
// ~/llvm/release/build/bin/clang++ -O2 -emit-llvm -S -fslp-vectorize Godbolt.cpp -o Godbolt.slp-vectorize.ll -target x86_64-unknown-linux-gnu

#define N 10

typedef unsigned int uint32_t;

uint32_t countsearch(const uint32_t *base, uint32_t needle) {
    uint32_t count = 0;
    for (const uint32_t *probe = base; probe < base + N; probe++) {
        if (*probe < needle)
            count++;
    }
    return count;
}
