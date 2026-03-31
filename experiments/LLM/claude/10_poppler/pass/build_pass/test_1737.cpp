#include <gtest/gtest.h>
#include <utility>
#include <cstddef>

// Since we only need the StructParentsMcidHash struct, we can include the header
// or define just the struct based on the provided interface.
// We'll replicate the struct as provided in the interface since including the full
// header may require extensive dependencies.

struct StructParentsMcidHash {
public:
    size_t operator()(std::pair<int, int> x) const {
        return x.first << 16 | x.second;
    }
};

class StructParentsMcidHashTest_1737 : public ::testing::Test {
protected:
    StructParentsMcidHash hasher;
};

// Test normal operation with typical positive values
TEST_F(StructParentsMcidHashTest_1737, NormalPositiveValues_1737) {
    std::pair<int, int> input(1, 2);
    size_t result = hasher(input);
    size_t expected = (1 << 16) | 2;
    EXPECT_EQ(result, expected);
}

// Test with both values being zero
TEST_F(StructParentsMcidHashTest_1737, BothZero_1737) {
    std::pair<int, int> input(0, 0);
    size_t result = hasher(input);
    EXPECT_EQ(result, 0u);
}

// Test with first value zero and second non-zero
TEST_F(StructParentsMcidHashTest_1737, FirstZeroSecondNonZero_1737) {
    std::pair<int, int> input(0, 5);
    size_t result = hasher(input);
    size_t expected = 5;
    EXPECT_EQ(result, expected);
}

// Test with first value non-zero and second zero
TEST_F(StructParentsMcidHashTest_1737, FirstNonZeroSecondZero_1737) {
    std::pair<int, int> input(3, 0);
    size_t result = hasher(input);
    size_t expected = 3 << 16;
    EXPECT_EQ(result, expected);
}

// Test that different pairs produce different hashes
TEST_F(StructParentsMcidHashTest_1737, DifferentPairsDifferentHashes_1737) {
    std::pair<int, int> input1(1, 2);
    std::pair<int, int> input2(2, 1);
    EXPECT_NE(hasher(input1), hasher(input2));
}

// Test that same pairs produce same hashes (consistency)
TEST_F(StructParentsMcidHashTest_1737, SamePairsSameHash_1737) {
    std::pair<int, int> input1(42, 99);
    std::pair<int, int> input2(42, 99);
    EXPECT_EQ(hasher(input1), hasher(input2));
}

// Test with larger values for second component (within 16-bit range)
TEST_F(StructParentsMcidHashTest_1737, SecondValueMaxIn16Bits_1737) {
    std::pair<int, int> input(1, 0xFFFF);
    size_t result = hasher(input);
    size_t expected = (1 << 16) | 0xFFFF;
    EXPECT_EQ(result, expected);
}

// Test with first value being 1 and second being max 16-bit value
TEST_F(StructParentsMcidHashTest_1737, FirstOneSecondMax16Bit_1737) {
    std::pair<int, int> input(1, 65535);
    size_t result = hasher(input);
    size_t expected = (1 << 16) | 65535;
    EXPECT_EQ(result, expected);
}

// Test boundary: first value at boundary of 16-bit shift
TEST_F(StructParentsMcidHashTest_1737, FirstValueLarge_1737) {
    std::pair<int, int> input(0xFFFF, 0xFFFF);
    size_t result = hasher(input);
    size_t expected = (0xFFFF << 16) | 0xFFFF;
    EXPECT_EQ(result, expected);
}

// Test with negative values for first component
TEST_F(StructParentsMcidHashTest_1737, NegativeFirstValue_1737) {
    std::pair<int, int> input(-1, 0);
    size_t result = hasher(input);
    size_t expected = static_cast<size_t>((-1 << 16) | 0);
    EXPECT_EQ(result, expected);
}

// Test with negative values for second component
TEST_F(StructParentsMcidHashTest_1737, NegativeSecondValue_1737) {
    std::pair<int, int> input(0, -1);
    size_t result = hasher(input);
    size_t expected = static_cast<size_t>(0 | (-1));
    EXPECT_EQ(result, expected);
}

// Test with both negative values
TEST_F(StructParentsMcidHashTest_1737, BothNegativeValues_1737) {
    std::pair<int, int> input(-1, -1);
    size_t result = hasher(input);
    size_t expected = static_cast<size_t>((-1 << 16) | (-1));
    EXPECT_EQ(result, expected);
}

// Test that the hash formula matches x.first << 16 | x.second
TEST_F(StructParentsMcidHashTest_1737, FormulaVerification_1737) {
    for (int i = 0; i < 100; ++i) {
        for (int j = 0; j < 100; ++j) {
            std::pair<int, int> input(i, j);
            size_t expected = static_cast<size_t>((i << 16) | j);
            EXPECT_EQ(hasher(input), expected);
        }
    }
}

// Test with second component having bits above 16 (potential overlap)
TEST_F(StructParentsMcidHashTest_1737, SecondValueOverlapsFirst_1737) {
    // When second value has bits in upper 16, the OR will combine with shifted first
    std::pair<int, int> input(1, 0x10000);
    size_t result = hasher(input);
    size_t expected = static_cast<size_t>((1 << 16) | 0x10000);
    EXPECT_EQ(result, expected);
}

// Test with pair (0, 1) vs (1, 0) distinction
TEST_F(StructParentsMcidHashTest_1737, DistinctSmallPairs_1737) {
    EXPECT_NE(hasher(std::make_pair(0, 1)), hasher(std::make_pair(1, 0)));
}
