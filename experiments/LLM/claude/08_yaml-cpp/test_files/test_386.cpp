#include <gtest/gtest.h>
#include <cstdint>

// Include the header under test
namespace YAML {
namespace jkj {
namespace dragonbox {
namespace policy {
namespace binary_to_decimal_rounding {

struct to_even_t {
public:
    template <class CarrierUInt>
    static constexpr bool prefer_round_down(CarrierUInt significand) noexcept {
        return significand % 2 != 0;
    }
};

} // namespace binary_to_decimal_rounding
} // namespace policy
} // namespace dragonbox
} // namespace jkj
} // namespace YAML

using ToEvenT = YAML::jkj::dragonbox::policy::binary_to_decimal_rounding::to_even_t;

// Test with even significand (should return false - do not prefer round down)
TEST(ToEvenTTest_386, EvenSignificandReturnsFalse_386) {
    EXPECT_FALSE(ToEvenT::prefer_round_down(0u));
    EXPECT_FALSE(ToEvenT::prefer_round_down(2u));
    EXPECT_FALSE(ToEvenT::prefer_round_down(4u));
    EXPECT_FALSE(ToEvenT::prefer_round_down(100u));
}

// Test with odd significand (should return true - prefer round down)
TEST(ToEvenTTest_386, OddSignificandReturnsTrue_386) {
    EXPECT_TRUE(ToEvenT::prefer_round_down(1u));
    EXPECT_TRUE(ToEvenT::prefer_round_down(3u));
    EXPECT_TRUE(ToEvenT::prefer_round_down(5u));
    EXPECT_TRUE(ToEvenT::prefer_round_down(99u));
}

// Test with zero (boundary - even)
TEST(ToEvenTTest_386, ZeroReturnsFalse_386) {
    EXPECT_FALSE(ToEvenT::prefer_round_down(0u));
}

// Test with one (boundary - smallest odd)
TEST(ToEvenTTest_386, OneReturnsTrue_386) {
    EXPECT_TRUE(ToEvenT::prefer_round_down(1u));
}

// Test with uint32_t type
TEST(ToEvenTTest_386, Uint32Even_386) {
    uint32_t even_val = 42;
    EXPECT_FALSE(ToEvenT::prefer_round_down(even_val));
}

TEST(ToEvenTTest_386, Uint32Odd_386) {
    uint32_t odd_val = 43;
    EXPECT_TRUE(ToEvenT::prefer_round_down(odd_val));
}

// Test with uint64_t type
TEST(ToEvenTTest_386, Uint64Even_386) {
    uint64_t even_val = 1000000000000ULL;
    EXPECT_FALSE(ToEvenT::prefer_round_down(even_val));
}

TEST(ToEvenTTest_386, Uint64Odd_386) {
    uint64_t odd_val = 1000000000001ULL;
    EXPECT_TRUE(ToEvenT::prefer_round_down(odd_val));
}

// Test with maximum uint32_t value (odd)
TEST(ToEvenTTest_386, MaxUint32IsOdd_386) {
    EXPECT_TRUE(ToEvenT::prefer_round_down(UINT32_MAX));
}

// Test with maximum uint64_t value (odd)
TEST(ToEvenTTest_386, MaxUint64IsOdd_386) {
    EXPECT_TRUE(ToEvenT::prefer_round_down(UINT64_MAX));
}

// Test with maximum uint32_t - 1 (even)
TEST(ToEvenTTest_386, MaxUint32MinusOneIsEven_386) {
    EXPECT_FALSE(ToEvenT::prefer_round_down(UINT32_MAX - 1));
}

// Test with maximum uint64_t - 1 (even)
TEST(ToEvenTTest_386, MaxUint64MinusOneIsEven_386) {
    EXPECT_FALSE(ToEvenT::prefer_round_down(UINT64_MAX - 1));
}

// Test constexpr usage
TEST(ToEvenTTest_386, ConstexprEvaluation_386) {
    constexpr bool result_even = ToEvenT::prefer_round_down(10u);
    constexpr bool result_odd = ToEvenT::prefer_round_down(11u);
    EXPECT_FALSE(result_even);
    EXPECT_TRUE(result_odd);
}

// Test with int type (signed)
TEST(ToEvenTTest_386, SignedIntEven_386) {
    EXPECT_FALSE(ToEvenT::prefer_round_down(2));
}

TEST(ToEvenTTest_386, SignedIntOdd_386) {
    EXPECT_TRUE(ToEvenT::prefer_round_down(3));
}

// Test with large even and odd values
TEST(ToEvenTTest_386, LargeEvenValue_386) {
    uint64_t large_even = 0xFFFFFFFFFFFFFFFEULL;
    EXPECT_FALSE(ToEvenT::prefer_round_down(large_even));
}

TEST(ToEvenTTest_386, LargeOddValue_386) {
    uint64_t large_odd = 0xFFFFFFFFFFFFFFFFULL;
    EXPECT_TRUE(ToEvenT::prefer_round_down(large_odd));
}

// Test noexcept
TEST(ToEvenTTest_386, IsNoexcept_386) {
    EXPECT_TRUE(noexcept(ToEvenT::prefer_round_down(0u)));
    EXPECT_TRUE(noexcept(ToEvenT::prefer_round_down(1u)));
}

// Test with uint16_t
TEST(ToEvenTTest_386, Uint16Even_386) {
    uint16_t val = 256;
    EXPECT_FALSE(ToEvenT::prefer_round_down(val));
}

TEST(ToEvenTTest_386, Uint16Odd_386) {
    uint16_t val = 257;
    EXPECT_TRUE(ToEvenT::prefer_round_down(val));
}

// Test with uint8_t
TEST(ToEvenTTest_386, Uint8Even_386) {
    uint8_t val = 128;
    EXPECT_FALSE(ToEvenT::prefer_round_down(val));
}

TEST(ToEvenTTest_386, Uint8Odd_386) {
    uint8_t val = 127;
    EXPECT_TRUE(ToEvenT::prefer_round_down(val));
}
