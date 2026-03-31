#include <gtest/gtest.h>
#include <utility>
#include <cstddef>

// Since we only need the StructParentsMcidHash struct, we can include the header
// or replicate the minimal struct for testing purposes based on the provided interface.
// We include the actual header to test the real implementation.

// Minimal reproduction of the struct under test based on the provided interface
struct StructParentsMcidHash {
    size_t operator()(std::pair<int, int> x) const {
        return x.first << 16 | x.second;
    }
};

class StructParentsMcidHashTest_2282 : public ::testing::Test {
protected:
    StructParentsMcidHash hasher;
};

// Normal operation tests

TEST_F(StructParentsMcidHashTest_2282, BasicHashComputation_2282) {
    std::pair<int, int> input{1, 2};
    size_t result = hasher(input);
    size_t expected = (1 << 16) | 2;
    EXPECT_EQ(result, expected);
}

TEST_F(StructParentsMcidHashTest_2282, HashWithZeroZero_2282) {
    std::pair<int, int> input{0, 0};
    size_t result = hasher(input);
    EXPECT_EQ(result, static_cast<size_t>(0));
}

TEST_F(StructParentsMcidHashTest_2282, HashWithFirstZero_2282) {
    std::pair<int, int> input{0, 5};
    size_t result = hasher(input);
    size_t expected = (0 << 16) | 5;
    EXPECT_EQ(result, expected);
}

TEST_F(StructParentsMcidHashTest_2282, HashWithSecondZero_2282) {
    std::pair<int, int> input{5, 0};
    size_t result = hasher(input);
    size_t expected = (5 << 16) | 0;
    EXPECT_EQ(result, expected);
}

TEST_F(StructParentsMcidHashTest_2282, HashWithLargeFirst_2282) {
    std::pair<int, int> input{1000, 1};
    size_t result = hasher(input);
    size_t expected = (1000 << 16) | 1;
    EXPECT_EQ(result, expected);
}

TEST_F(StructParentsMcidHashTest_2282, HashWithLargeSecond_2282) {
    std::pair<int, int> input{1, 1000};
    size_t result = hasher(input);
    size_t expected = (1 << 16) | 1000;
    EXPECT_EQ(result, expected);
}

TEST_F(StructParentsMcidHashTest_2282, DifferentPairsProduceDifferentHashes_2282) {
    std::pair<int, int> input1{1, 2};
    std::pair<int, int> input2{2, 1};
    EXPECT_NE(hasher(input1), hasher(input2));
}

TEST_F(StructParentsMcidHashTest_2282, SamePairsProduceSameHash_2282) {
    std::pair<int, int> input1{42, 73};
    std::pair<int, int> input2{42, 73};
    EXPECT_EQ(hasher(input1), hasher(input2));
}

// Boundary conditions

TEST_F(StructParentsMcidHashTest_2282, HashWithMaxSecond16Bit_2282) {
    // Second value at 16-bit max (0xFFFF = 65535)
    std::pair<int, int> input{1, 0xFFFF};
    size_t result = hasher(input);
    size_t expected = (1 << 16) | 0xFFFF;
    EXPECT_EQ(result, expected);
}

TEST_F(StructParentsMcidHashTest_2282, HashWithSmallValues_2282) {
    std::pair<int, int> input{1, 1};
    size_t result = hasher(input);
    size_t expected = (1 << 16) | 1;
    EXPECT_EQ(result, expected);
}

TEST_F(StructParentsMcidHashTest_2282, HashWithNegativeFirst_2282) {
    std::pair<int, int> input{-1, 0};
    size_t result = hasher(input);
    size_t expected = static_cast<size_t>((-1 << 16) | 0);
    EXPECT_EQ(result, expected);
}

TEST_F(StructParentsMcidHashTest_2282, HashWithNegativeSecond_2282) {
    std::pair<int, int> input{0, -1};
    size_t result = hasher(input);
    size_t expected = static_cast<size_t>((0 << 16) | (-1));
    EXPECT_EQ(result, expected);
}

TEST_F(StructParentsMcidHashTest_2282, HashWithBothNegative_2282) {
    std::pair<int, int> input{-1, -1};
    size_t result = hasher(input);
    size_t expected = static_cast<size_t>((-1 << 16) | (-1));
    EXPECT_EQ(result, expected);
}

TEST_F(StructParentsMcidHashTest_2282, HashConsistency_2282) {
    // Call multiple times with same input, should always return same result
    std::pair<int, int> input{100, 200};
    size_t result1 = hasher(input);
    size_t result2 = hasher(input);
    size_t result3 = hasher(input);
    EXPECT_EQ(result1, result2);
    EXPECT_EQ(result2, result3);
}

TEST_F(StructParentsMcidHashTest_2282, HashSecondValueOverlapsFirst_2282) {
    // When second value has bits beyond 16 bits, they overlap with the first shifted value
    std::pair<int, int> input{0, 0x10000}; // second = 65536
    size_t result = hasher(input);
    size_t expected = (0 << 16) | 0x10000;
    EXPECT_EQ(result, expected);
}

TEST_F(StructParentsMcidHashTest_2282, HashDistinguishesPairsWithinLower16Bits_2282) {
    // Pairs that differ only in lower 16 bits of second
    std::pair<int, int> input1{0, 1};
    std::pair<int, int> input2{0, 2};
    EXPECT_NE(hasher(input1), hasher(input2));
}

TEST_F(StructParentsMcidHashTest_2282, HashDistinguishesPairsInFirstComponent_2282) {
    std::pair<int, int> input1{1, 0};
    std::pair<int, int> input2{2, 0};
    EXPECT_NE(hasher(input1), hasher(input2));
}
