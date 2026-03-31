#include <gtest/gtest.h>
#include "./TestProjects/Catch2/src/catch2/internal/catch_random_integer_helpers.hpp"

using namespace Catch::Detail;

// Test equality operator with same values
TEST(ExtendedMultResultTest_330, EqualityWithSameValues_330) {
    ExtendedMultResult<uint32_t> a{10, 20};
    ExtendedMultResult<uint32_t> b{10, 20};
    EXPECT_TRUE(a == b);
}

// Test equality operator with different upper values
TEST(ExtendedMultResultTest_330, InequalityWithDifferentUpper_330) {
    ExtendedMultResult<uint32_t> a{10, 20};
    ExtendedMultResult<uint32_t> b{11, 20};
    EXPECT_FALSE(a == b);
}

// Test equality operator with different lower values
TEST(ExtendedMultResultTest_330, InequalityWithDifferentLower_330) {
    ExtendedMultResult<uint32_t> a{10, 20};
    ExtendedMultResult<uint32_t> b{10, 21};
    EXPECT_FALSE(a == b);
}

// Test equality operator with both values different
TEST(ExtendedMultResultTest_330, InequalityWithBothDifferent_330) {
    ExtendedMultResult<uint32_t> a{10, 20};
    ExtendedMultResult<uint32_t> b{11, 21};
    EXPECT_FALSE(a == b);
}

// Test equality with zero values
TEST(ExtendedMultResultTest_330, EqualityWithZeros_330) {
    ExtendedMultResult<uint32_t> a{0, 0};
    ExtendedMultResult<uint32_t> b{0, 0};
    EXPECT_TRUE(a == b);
}

// Test equality with max values for uint32_t
TEST(ExtendedMultResultTest_330, EqualityWithMaxUint32_330) {
    ExtendedMultResult<uint32_t> a{UINT32_MAX, UINT32_MAX};
    ExtendedMultResult<uint32_t> b{UINT32_MAX, UINT32_MAX};
    EXPECT_TRUE(a == b);
}

// Test inequality when upper is zero and lower differs
TEST(ExtendedMultResultTest_330, InequalityUpperZeroLowerDiffers_330) {
    ExtendedMultResult<uint32_t> a{0, 0};
    ExtendedMultResult<uint32_t> b{0, 1};
    EXPECT_FALSE(a == b);
}

// Test inequality when lower is zero and upper differs
TEST(ExtendedMultResultTest_330, InequalityLowerZeroUpperDiffers_330) {
    ExtendedMultResult<uint32_t> a{0, 0};
    ExtendedMultResult<uint32_t> b{1, 0};
    EXPECT_FALSE(a == b);
}

// Test with uint64_t type
TEST(ExtendedMultResultTest_330, EqualityWithUint64_330) {
    ExtendedMultResult<uint64_t> a{100ULL, 200ULL};
    ExtendedMultResult<uint64_t> b{100ULL, 200ULL};
    EXPECT_TRUE(a == b);
}

// Test inequality with uint64_t type
TEST(ExtendedMultResultTest_330, InequalityWithUint64_330) {
    ExtendedMultResult<uint64_t> a{100ULL, 200ULL};
    ExtendedMultResult<uint64_t> b{100ULL, 201ULL};
    EXPECT_FALSE(a == b);
}

// Test with uint8_t type
TEST(ExtendedMultResultTest_330, EqualityWithUint8_330) {
    ExtendedMultResult<uint8_t> a{255, 0};
    ExtendedMultResult<uint8_t> b{255, 0};
    EXPECT_TRUE(a == b);
}

// Test with uint16_t type
TEST(ExtendedMultResultTest_330, EqualityWithUint16_330) {
    ExtendedMultResult<uint16_t> a{1000, 2000};
    ExtendedMultResult<uint16_t> b{1000, 2000};
    EXPECT_TRUE(a == b);
}

// Test reflexivity (a == a)
TEST(ExtendedMultResultTest_330, Reflexivity_330) {
    ExtendedMultResult<uint32_t> a{42, 84};
    EXPECT_TRUE(a == a);
}

// Test symmetry (a == b implies b == a)
TEST(ExtendedMultResultTest_330, Symmetry_330) {
    ExtendedMultResult<uint32_t> a{42, 84};
    ExtendedMultResult<uint32_t> b{42, 84};
    EXPECT_TRUE(a == b);
    EXPECT_TRUE(b == a);
}

// Test symmetry for inequality
TEST(ExtendedMultResultTest_330, SymmetryInequality_330) {
    ExtendedMultResult<uint32_t> a{42, 84};
    ExtendedMultResult<uint32_t> b{42, 85};
    EXPECT_FALSE(a == b);
    EXPECT_FALSE(b == a);
}

// Test constexpr equality
TEST(ExtendedMultResultTest_330, ConstexprEquality_330) {
    constexpr ExtendedMultResult<uint32_t> a{10, 20};
    constexpr ExtendedMultResult<uint32_t> b{10, 20};
    constexpr bool result = (a == b);
    EXPECT_TRUE(result);
}

// Test constexpr inequality
TEST(ExtendedMultResultTest_330, ConstexprInequality_330) {
    constexpr ExtendedMultResult<uint32_t> a{10, 20};
    constexpr ExtendedMultResult<uint32_t> b{10, 21};
    constexpr bool result = (a == b);
    EXPECT_FALSE(result);
}

// Test member access
TEST(ExtendedMultResultTest_330, MemberAccess_330) {
    ExtendedMultResult<uint32_t> a{42, 84};
    EXPECT_EQ(a.upper, 42u);
    EXPECT_EQ(a.lower, 84u);
}

// Test with boundary values where upper is max and lower is min
TEST(ExtendedMultResultTest_330, BoundaryUpperMaxLowerMin_330) {
    ExtendedMultResult<uint32_t> a{UINT32_MAX, 0};
    ExtendedMultResult<uint32_t> b{UINT32_MAX, 0};
    EXPECT_TRUE(a == b);
}

// Test with boundary values where upper is min and lower is max
TEST(ExtendedMultResultTest_330, BoundaryUpperMinLowerMax_330) {
    ExtendedMultResult<uint32_t> a{0, UINT32_MAX};
    ExtendedMultResult<uint32_t> b{0, UINT32_MAX};
    EXPECT_TRUE(a == b);
}
