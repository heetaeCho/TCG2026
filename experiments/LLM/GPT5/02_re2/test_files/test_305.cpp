// File: compile_make_rune_cache_key_test.cc

#include <gtest/gtest.h>
#include <cstdint>
#include <set>
#include <vector>
#include <tuple>

namespace re2 {
// Bring the provided partial code into this TU so the tests can call it.
static uint64_t MakeRuneCacheKey(uint8_t lo, uint8_t hi, bool foldcase, int next) {
    return (uint64_t)next << 17 | (uint64_t)lo << 9 | (uint64_t)hi << 1 | (uint64_t)foldcase;
}
}  // namespace re2

namespace {

// Helpers to interpret the packed fields without relying on any internal state.
static inline bool       ExtractFold(uint64_t key) { return (key & 0x1ull) != 0; }
static inline uint8_t    ExtractHi(uint64_t key)   { return static_cast<uint8_t>((key >> 1) & 0xFFull); }
static inline uint8_t    ExtractLo(uint64_t key)   { return static_cast<uint8_t>((key >> 9) & 0xFFull); }
static inline int        ExtractNext(uint64_t key) { return static_cast<int>(key >> 17); }

}  // namespace

// 1) Zero inputs -> zero output
TEST(MakeRuneCacheKeyTest_305, ZeroValues_305) {
    uint64_t key = re2::MakeRuneCacheKey(/*lo=*/0, /*hi=*/0, /*foldcase=*/false, /*next=*/0);
    EXPECT_EQ(key, 0u);
    EXPECT_FALSE(ExtractFold(key));
    EXPECT_EQ(ExtractHi(key), 0);
    EXPECT_EQ(ExtractLo(key), 0);
    EXPECT_EQ(ExtractNext(key), 0);
}

// 2) Foldcase toggles only the lowest bit
TEST(MakeRuneCacheKeyTest_305, FoldcaseBit_305) {
    uint64_t k0 = re2::MakeRuneCacheKey(0, 0, false, 0);
    uint64_t k1 = re2::MakeRuneCacheKey(0, 0, true,  0);
    EXPECT_EQ(k0 ^ k1, 0x1ull);       // only LSB differs
    EXPECT_FALSE(ExtractFold(k0));
    EXPECT_TRUE(ExtractFold(k1));
    // Other fields unaffected
    EXPECT_EQ(ExtractHi(k0), 0); EXPECT_EQ(ExtractHi(k1), 0);
    EXPECT_EQ(ExtractLo(k0), 0); EXPECT_EQ(ExtractLo(k1), 0);
    EXPECT_EQ(ExtractNext(k0), 0); EXPECT_EQ(ExtractNext(k1), 0);
}

// 3) Boundary: lo max (255) sits only in its 8-bit field
TEST(MakeRuneCacheKeyTest_305, LoMaxBoundary_305) {
    uint64_t key = re2::MakeRuneCacheKey(/*lo=*/0xFF, /*hi=*/0x00, /*foldcase=*/false, /*next=*/0);
    EXPECT_EQ(ExtractLo(key), 0xFF);
    EXPECT_EQ(ExtractHi(key), 0x00);
    EXPECT_FALSE(ExtractFold(key));
    EXPECT_EQ(ExtractNext(key), 0);
    // Ensure expected packed value
    uint64_t expected = (uint64_t)0xFF << 9;
    EXPECT_EQ(key, expected);
}

// 4) Boundary: hi max (255) sits only in its 8-bit field
TEST(MakeRuneCacheKeyTest_305, HiMaxBoundary_305) {
    uint64_t key = re2::MakeRuneCacheKey(/*lo=*/0x00, /*hi=*/0xFF, /*foldcase=*/false, /*next=*/0);
    EXPECT_EQ(ExtractHi(key), 0xFF);
    EXPECT_EQ(ExtractLo(key), 0x00);
    EXPECT_FALSE(ExtractFold(key));
    EXPECT_EQ(ExtractNext(key), 0);
    uint64_t expected = (uint64_t)0xFF << 1;
    EXPECT_EQ(key, expected);
}

// 5) Next positive (including large) occupies upper bits without disturbing lower fields
TEST(MakeRuneCacheKeyTest_305, NextPositiveAndLarge_305) {
    int next = 1 << 30; // large positive int
    uint64_t key = re2::MakeRuneCacheKey(/*lo=*/0x12, /*hi=*/0x34, /*foldcase=*/true, /*next=*/next);
    EXPECT_EQ(ExtractNext(key), next);
    EXPECT_EQ(ExtractLo(key), 0x12);
    EXPECT_EQ(ExtractHi(key), 0x34);
    EXPECT_TRUE(ExtractFold(key));

    uint64_t expected = ((uint64_t)next << 17) | ((uint64_t)0x12 << 9) | ((uint64_t)0x34 << 1) | 1ull;
    EXPECT_EQ(key, expected);
}

// 6) Next negative is preserved via uint64_t cast-and-shift semantics
TEST(MakeRuneCacheKeyTest_305, NextNegative_305) {
    int next = -1;
    uint64_t key = re2::MakeRuneCacheKey(/*lo=*/0, /*hi=*/0, /*foldcase=*/false, /*next=*/next);
    // Extracting should reconstruct the same signed value when shifted back down.
    EXPECT_EQ(ExtractNext(key), next);
    EXPECT_EQ(ExtractLo(key), 0);
    EXPECT_EQ(ExtractHi(key), 0);
    EXPECT_FALSE(ExtractFold(key));

    uint64_t expected = ((uint64_t)-1 << 17);
    EXPECT_EQ(key, expected);
}

// 7) Combined fields pack without overlap and round-trip cleanly
TEST(MakeRuneCacheKeyTest_305, CombinedFieldsNoOverlap_305) {
    uint8_t lo = 0xAA;
    uint8_t hi = 0x55;
    bool fold = true;
    int next = 12345;

    uint64_t key = re2::MakeRuneCacheKey(lo, hi, fold, next);
    // Round-trip extraction
    EXPECT_EQ(ExtractLo(key), lo);
    EXPECT_EQ(ExtractHi(key), hi);
    EXPECT_EQ(ExtractNext(key), next);
    EXPECT_TRUE(ExtractFold(key));

    // Exact packed value as observable result
    uint64_t expected = ((uint64_t)next << 17) | ((uint64_t)lo << 9) | ((uint64_t)hi << 1) | 1ull;
    EXPECT_EQ(key, expected);
}

// 8) Small cross-product shows uniqueness across different parameter tuples
TEST(MakeRuneCacheKeyTest_305, UniquenessAcrossParams_305) {
    std::vector<std::tuple<uint8_t,uint8_t,bool,int>> cases = {
        {0x00, 0x00, false, 0},
        {0x01, 0x00, false, 0},
        {0x00, 0x01, false, 0},
        {0x00, 0x00, true,  0},
        {0xFF, 0x00, false, 0},
        {0x00, 0xFF, false, 0},
        {0x12, 0x34, true,  7},
        {0x12, 0x34, true,  8},
        {0x12, 0x34, false, 7},
    };

    std::set<uint64_t> seen;
    for (const auto& t : cases) {
        uint64_t key = re2::MakeRuneCacheKey(std::get<0>(t), std::get<1>(t), std::get<2>(t), std::get<3>(t));
        // Each generated key should be unique across these distinct inputs.
        EXPECT_TRUE(seen.insert(key).second) << "Duplicate key for tuple encountered";
    }
}
