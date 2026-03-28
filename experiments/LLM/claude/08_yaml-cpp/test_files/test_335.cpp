#include <gtest/gtest.h>
#include <cstdint>
#include <type_traits>

// We need to include the header that defines the types
// First, let's define or include the necessary types from dragonbox

namespace YAML {
namespace jkj {
namespace dragonbox {

template <class DecimalSignificand, class DecimalExponentType, bool TrailingZeroFlag>
struct unsigned_decimal_fp {
    DecimalSignificand significand;
    DecimalExponentType exponent;
    
    bool operator==(const unsigned_decimal_fp& other) const {
        return significand == other.significand && exponent == other.exponent;
    }
};

namespace policy {
namespace trailing_zero {

struct ignore_t {
public:
    template <class Format, class DecimalSignificand, class DecimalExponentType>
    static constexpr unsigned_decimal_fp<DecimalSignificand, DecimalExponentType, false>
    on_trailing_zeros(DecimalSignificand significand, DecimalExponentType exponent) noexcept {
        return {significand, exponent};
    }

    template <class Format, class DecimalSignificand, class DecimalExponentType>
    static constexpr unsigned_decimal_fp<DecimalSignificand, DecimalExponentType, false>
    no_trailing_zeros(DecimalSignificand significand, DecimalExponentType exponent) noexcept {
        return {significand, exponent};
    }
};

} // namespace trailing_zero
} // namespace policy
} // namespace dragonbox
} // namespace jkj
} // namespace YAML

// Dummy format type for template parameter
struct DummyFormat {};

using namespace YAML::jkj::dragonbox;
using namespace YAML::jkj::dragonbox::policy::trailing_zero;

class IgnoreTrailingZeroTest_335 : public ::testing::Test {
protected:
    ignore_t policy;
};

// Test on_trailing_zeros with uint32_t significand and int exponent
TEST_F(IgnoreTrailingZeroTest_335, OnTrailingZerosUint32Int_335) {
    auto result = ignore_t::on_trailing_zeros<DummyFormat>(uint32_t(12345), int(10));
    EXPECT_EQ(result.significand, uint32_t(12345));
    EXPECT_EQ(result.exponent, int(10));
}

// Test on_trailing_zeros with uint64_t significand and int exponent
TEST_F(IgnoreTrailingZeroTest_335, OnTrailingZerosUint64Int_335) {
    auto result = ignore_t::on_trailing_zeros<DummyFormat>(uint64_t(9876543210ULL), int(-5));
    EXPECT_EQ(result.significand, uint64_t(9876543210ULL));
    EXPECT_EQ(result.exponent, int(-5));
}

// Test no_trailing_zeros with uint32_t significand and int exponent
TEST_F(IgnoreTrailingZeroTest_335, NoTrailingZerosUint32Int_335) {
    auto result = ignore_t::no_trailing_zeros<DummyFormat>(uint32_t(42), int(3));
    EXPECT_EQ(result.significand, uint32_t(42));
    EXPECT_EQ(result.exponent, int(3));
}

// Test no_trailing_zeros with uint64_t significand and int exponent
TEST_F(IgnoreTrailingZeroTest_335, NoTrailingZerosUint64Int_335) {
    auto result = ignore_t::no_trailing_zeros<DummyFormat>(uint64_t(100000ULL), int(-10));
    EXPECT_EQ(result.significand, uint64_t(100000ULL));
    EXPECT_EQ(result.exponent, int(-10));
}

// Test return type has TrailingZeroFlag == false for on_trailing_zeros
TEST_F(IgnoreTrailingZeroTest_335, OnTrailingZerosReturnTypeFlagIsFalse_335) {
    auto result = ignore_t::on_trailing_zeros<DummyFormat>(uint32_t(1), int(0));
    using ResultType = decltype(result);
    bool isSameType = std::is_same<ResultType, unsigned_decimal_fp<uint32_t, int, false>>::value;
    EXPECT_TRUE(isSameType);
}

// Test return type has TrailingZeroFlag == false for no_trailing_zeros
TEST_F(IgnoreTrailingZeroTest_335, NoTrailingZerosReturnTypeFlagIsFalse_335) {
    auto result = ignore_t::no_trailing_zeros<DummyFormat>(uint64_t(1), int(0));
    using ResultType = decltype(result);
    bool isSameType = std::is_same<ResultType, unsigned_decimal_fp<uint64_t, int, false>>::value;
    EXPECT_TRUE(isSameType);
}

// Test on_trailing_zeros with zero significand
TEST_F(IgnoreTrailingZeroTest_335, OnTrailingZerosZeroSignificand_335) {
    auto result = ignore_t::on_trailing_zeros<DummyFormat>(uint32_t(0), int(0));
    EXPECT_EQ(result.significand, uint32_t(0));
    EXPECT_EQ(result.exponent, int(0));
}

// Test no_trailing_zeros with zero significand
TEST_F(IgnoreTrailingZeroTest_335, NoTrailingZerosZeroSignificand_335) {
    auto result = ignore_t::no_trailing_zeros<DummyFormat>(uint32_t(0), int(0));
    EXPECT_EQ(result.significand, uint32_t(0));
    EXPECT_EQ(result.exponent, int(0));
}

// Test on_trailing_zeros with max uint32 significand
TEST_F(IgnoreTrailingZeroTest_335, OnTrailingZerosMaxUint32_335) {
    auto result = ignore_t::on_trailing_zeros<DummyFormat>(
        std::numeric_limits<uint32_t>::max(), int(100));
    EXPECT_EQ(result.significand, std::numeric_limits<uint32_t>::max());
    EXPECT_EQ(result.exponent, int(100));
}

// Test on_trailing_zeros with max uint64 significand
TEST_F(IgnoreTrailingZeroTest_335, OnTrailingZerosMaxUint64_335) {
    auto result = ignore_t::on_trailing_zeros<DummyFormat>(
        std::numeric_limits<uint64_t>::max(), int(-300));
    EXPECT_EQ(result.significand, std::numeric_limits<uint64_t>::max());
    EXPECT_EQ(result.exponent, int(-300));
}

// Test on_trailing_zeros with negative exponent boundary
TEST_F(IgnoreTrailingZeroTest_335, OnTrailingZerosNegativeExponent_335) {
    auto result = ignore_t::on_trailing_zeros<DummyFormat>(
        uint32_t(1), std::numeric_limits<int>::min());
    EXPECT_EQ(result.significand, uint32_t(1));
    EXPECT_EQ(result.exponent, std::numeric_limits<int>::min());
}

// Test no_trailing_zeros with max exponent boundary
TEST_F(IgnoreTrailingZeroTest_335, NoTrailingZerosMaxExponent_335) {
    auto result = ignore_t::no_trailing_zeros<DummyFormat>(
        uint32_t(1), std::numeric_limits<int>::max());
    EXPECT_EQ(result.significand, uint32_t(1));
    EXPECT_EQ(result.exponent, std::numeric_limits<int>::max());
}

// Test that on_trailing_zeros and no_trailing_zeros produce same result (both ignore trailing zeros)
TEST_F(IgnoreTrailingZeroTest_335, OnAndNoTrailingZerosProduceSameResult_335) {
    auto result1 = ignore_t::on_trailing_zeros<DummyFormat>(uint32_t(12300), int(5));
    auto result2 = ignore_t::no_trailing_zeros<DummyFormat>(uint32_t(12300), int(5));
    EXPECT_EQ(result1.significand, result2.significand);
    EXPECT_EQ(result1.exponent, result2.exponent);
}

// Test noexcept specification for on_trailing_zeros
TEST_F(IgnoreTrailingZeroTest_335, OnTrailingZerosIsNoexcept_335) {
    EXPECT_TRUE(noexcept(ignore_t::on_trailing_zeros<DummyFormat>(uint32_t(1), int(1))));
}

// Test noexcept specification for no_trailing_zeros
TEST_F(IgnoreTrailingZeroTest_335, NoTrailingZerosIsNoexcept_335) {
    EXPECT_TRUE(noexcept(ignore_t::no_trailing_zeros<DummyFormat>(uint32_t(1), int(1))));
}

// Test with significand that has trailing zeros (value ending in zeros)
TEST_F(IgnoreTrailingZeroTest_335, OnTrailingZerosWithTrailingZeroValue_335) {
    // The ignore policy should just pass through the value unchanged
    auto result = ignore_t::on_trailing_zeros<DummyFormat>(uint64_t(1000000), int(2));
    EXPECT_EQ(result.significand, uint64_t(1000000));
    EXPECT_EQ(result.exponent, int(2));
}

// Test constexpr behavior
TEST_F(IgnoreTrailingZeroTest_335, OnTrailingZerosConstexpr_335) {
    constexpr auto result = ignore_t::on_trailing_zeros<DummyFormat>(uint32_t(42), int(7));
    static_assert(result.significand == 42, "significand should be 42");
    static_assert(result.exponent == 7, "exponent should be 7");
    EXPECT_EQ(result.significand, uint32_t(42));
    EXPECT_EQ(result.exponent, int(7));
}

// Test constexpr behavior for no_trailing_zeros
TEST_F(IgnoreTrailingZeroTest_335, NoTrailingZerosConstexpr_335) {
    constexpr auto result = ignore_t::no_trailing_zeros<DummyFormat>(uint32_t(99), int(-3));
    static_assert(result.significand == 99, "significand should be 99");
    static_assert(result.exponent == -3, "exponent should be -3");
    EXPECT_EQ(result.significand, uint32_t(99));
    EXPECT_EQ(result.exponent, int(-3));
}

// Test with short exponent type
TEST_F(IgnoreTrailingZeroTest_335, OnTrailingZerosShortExponent_335) {
    auto result = ignore_t::on_trailing_zeros<DummyFormat>(uint32_t(555), short(12));
    EXPECT_EQ(result.significand, uint32_t(555));
    EXPECT_EQ(result.exponent, short(12));
}
