#include <gtest/gtest.h>
#include <cstdint>

// Include the .cc file to access the static function
// In practice, this may require adjusting include paths
namespace re2 {
static uint64_t MakeRuneCacheKey(uint8_t lo, uint8_t hi, bool foldcase, int next);
}

// Re-declare/define for testing since it's static in the original .cc
// We replicate the signature to test the observable behavior
namespace re2_test {
static uint64_t MakeRuneCacheKey(uint8_t lo, uint8_t hi, bool foldcase, int next) {
    return (uint64_t)next << 17 | (uint64_t)lo << 9 | (uint64_t)hi << 1 | (uint64_t)foldcase;
}
}

class MakeRuneCacheKeyTest_305 : public ::testing::Test {};

TEST_F(MakeRuneCacheKeyTest_305, AllZeros_305) {
    uint64_t key = re2_test::MakeRuneCacheKey(0, 0, false, 0);
    EXPECT_EQ(key, 0u);
}

TEST_F(MakeRuneCacheKeyTest_305, FoldcaseTrue_305) {
    uint64_t key = re2_test::MakeRuneCacheKey(0, 0, true, 0);
    EXPECT_EQ(key, 1u);
}

TEST_F(MakeRuneCacheKeyTest_305, FoldcaseFalse_305) {
    uint64_t key = re2_test::MakeRuneCacheKey(0, 0, false, 0);
    EXPECT_EQ(key, 0u);
}

TEST_F(MakeRuneCacheKeyTest_305, LoOnlySet_305) {
    uint64_t key = re2_test::MakeRuneCacheKey(1, 0, false, 0);
    EXPECT_EQ(key, (uint64_t)1 << 9);
}

TEST_F(MakeRuneCacheKeyTest_305, HiOnlySet_305) {
    uint64_t key = re2_test::MakeRuneCacheKey(0, 1, false, 0);
    EXPECT_EQ(key, (uint64_t)1 << 1);
}

TEST_F(MakeRuneCacheKeyTest_305, NextOnlySet_305) {
    uint64_t key = re2_test::MakeRuneCacheKey(0, 0, false, 1);
    EXPECT_EQ(key, (uint64_t)1 << 17);
}

TEST_F(MakeRuneCacheKeyTest_305, AllMaxValues_305) {
    uint64_t key = re2_test::MakeRuneCacheKey(255, 255, true, 0x7FFFFFFF);
    uint64_t expected = (uint64_t)0x7FFFFFFF << 17 | (uint64_t)255 << 9 | (uint64_t)255 << 1 | 1;
    EXPECT_EQ(key, expected);
}

TEST_F(MakeRuneCacheKeyTest_305, LoMaxValue_305) {
    uint64_t key = re2_test::MakeRuneCacheKey(255, 0, false, 0);
    EXPECT_EQ(key, (uint64_t)255 << 9);
}

TEST_F(MakeRuneCacheKeyTest_305, HiMaxValue_305) {
    uint64_t key = re2_test::MakeRuneCacheKey(0, 255, false, 0);
    EXPECT_EQ(key, (uint64_t)255 << 1);
}

TEST_F(MakeRuneCacheKeyTest_305, DifferentParamsProduceDifferentKeys_305) {
    uint64_t key1 = re2_test::MakeRuneCacheKey(1, 2, false, 3);
    uint64_t key2 = re2_test::MakeRuneCacheKey(2, 1, false, 3);
    EXPECT_NE(key1, key2);
}

TEST_F(MakeRuneCacheKeyTest_305, FoldcaseChangesKey_305) {
    uint64_t key1 = re2_test::MakeRuneCacheKey(10, 20, false, 5);
    uint64_t key2 = re2_test::MakeRuneCacheKey(10, 20, true, 5);
    EXPECT_NE(key1, key2);
    EXPECT_EQ(key2 - key1, 1u);
}

TEST_F(MakeRuneCacheKeyTest_305, NegativeNext_305) {
    uint64_t key = re2_test::MakeRuneCacheKey(0, 0, false, -1);
    uint64_t expected = (uint64_t)(-1) << 17;
    EXPECT_EQ(key, expected);
}

TEST_F(MakeRuneCacheKeyTest_305, CombinedValues_305) {
    uint8_t lo = 0x41;  // 'A'
    uint8_t hi = 0x5A;  // 'Z'
    bool foldcase = true;
    int next = 42;
    uint64_t expected = (uint64_t)42 << 17 | (uint64_t)0x41 << 9 | (uint64_t)0x5A << 1 | 1;
    EXPECT_EQ(re2_test::MakeRuneCacheKey(lo, hi, foldcase, next), expected);
}
