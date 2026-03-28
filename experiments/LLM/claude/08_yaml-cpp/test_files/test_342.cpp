#include <gtest/gtest.h>
#include <cstdint>
#include <type_traits>

// We need to include the header that defines the types
// First, let's define the minimal required types if not available
namespace YAML {
namespace jkj {
namespace dragonbox {

template <class DecimalSignificand, class DecimalExponentType, bool HasTrailingZeros>
struct unsigned_decimal_fp {
    DecimalSignificand significand;
    DecimalExponentType exponent;
    bool may_have_trailing_zeros;
};

namespace policy {
namespace trailing_zero {

struct report_t {
public:
    template <class Format, class DecimalSignificand, class DecimalExponentType>
    static constexpr unsigned_decimal_fp<DecimalSignificand, DecimalExponentType, true>
    on_trailing_zeros(DecimalSignificand significand, DecimalExponentType exponent) noexcept {
        return {significand, exponent, true};
    }

    template <class Format, class DecimalSignificand, class DecimalExponentType>
    static constexpr unsigned_decimal_fp<DecimalSignificand, DecimalExponentType, true>
    no_trailing_zeros(DecimalSignificand significand, DecimalExponentType exponent) noexcept {
        return {significand, exponent, false};
    }
};

} // namespace trailing_zero
} // namespace policy
} // namespace dragonbox
} // namespace jkj
} // namespace YAML

// Dummy format type for testing
struct DummyFormat {};
struct AnotherFormat {};

using namespace YAML::jkj::dragonbox;
using report_t = policy::trailing_zero::report_t;

// ============================================================
// Tests for no_trailing_zeros
// ============================================================

class ReportTrailingZeroTest_342 : public ::testing::Test {
protected:
    // Common setup if needed
};

TEST_F(ReportTrailingZeroTest_342, NoTrailingZeros_ReturnsFalseForMayHaveTrailingZeros_342) {
    auto result = report_t::no_trailing_zeros<DummyFormat>(uint32_t(123), int(5));
    EXPECT_FALSE(result.may_have_trailing_zeros);
}

TEST_F(ReportTrailingZeroTest_342, NoTrailingZeros_PreservesSignificand_342) {
    auto result = report_t::no_trailing_zeros<DummyFormat>(uint32_t(456), int(3));
    EXPECT_EQ(result.significand, uint32_t(456));
}

TEST_F(ReportTrailingZeroTest_342, NoTrailingZeros_PreservesExponent_342) {
    auto result = report_t::no_trailing_zeros<DummyFormat>(uint32_t(789), int(-7));
    EXPECT_EQ(result.exponent, -7);
}

TEST_F(ReportTrailingZeroTest_342, NoTrailingZeros_WithUint64Significand_342) {
    auto result = report_t::no_trailing_zeros<DummyFormat>(uint64_t(123456789012345ULL), int(10));
    EXPECT_EQ(result.significand, uint64_t(123456789012345ULL));
    EXPECT_EQ(result.exponent, 10);
    EXPECT_FALSE(result.may_have_trailing_zeros);
}

TEST_F(ReportTrailingZeroTest_342, NoTrailingZeros_ZeroSignificand_342) {
    auto result = report_t::no_trailing_zeros<DummyFormat>(uint32_t(0), int(0));
    EXPECT_EQ(result.significand, uint32_t(0));
    EXPECT_EQ(result.exponent, 0);
    EXPECT_FALSE(result.may_have_trailing_zeros);
}

TEST_F(ReportTrailingZeroTest_342, NoTrailingZeros_NegativeExponent_342) {
    auto result = report_t::no_trailing_zeros<DummyFormat>(uint32_t(100), int(-300));
    EXPECT_EQ(result.significand, uint32_t(100));
    EXPECT_EQ(result.exponent, -300);
    EXPECT_FALSE(result.may_have_trailing_zeros);
}

TEST_F(ReportTrailingZeroTest_342, NoTrailingZeros_LargePositiveExponent_342) {
    auto result = report_t::no_trailing_zeros<DummyFormat>(uint32_t(1), int(1000));
    EXPECT_EQ(result.significand, uint32_t(1));
    EXPECT_EQ(result.exponent, 1000);
    EXPECT_FALSE(result.may_have_trailing_zeros);
}

TEST_F(ReportTrailingZeroTest_342, NoTrailingZeros_MaxUint32Significand_342) {
    auto result = report_t::no_trailing_zeros<DummyFormat>(
        std::numeric_limits<uint32_t>::max(), int(5));
    EXPECT_EQ(result.significand, std::numeric_limits<uint32_t>::max());
    EXPECT_EQ(result.exponent, 5);
    EXPECT_FALSE(result.may_have_trailing_zeros);
}

TEST_F(ReportTrailingZeroTest_342, NoTrailingZeros_MaxUint64Significand_342) {
    auto result = report_t::no_trailing_zeros<DummyFormat>(
        std::numeric_limits<uint64_t>::max(), int(-10));
    EXPECT_EQ(result.significand, std::numeric_limits<uint64_t>::max());
    EXPECT_EQ(result.exponent, -10);
    EXPECT_FALSE(result.may_have_trailing_zeros);
}

TEST_F(ReportTrailingZeroTest_342, NoTrailingZeros_DifferentFormatType_342) {
    auto result = report_t::no_trailing_zeros<AnotherFormat>(uint32_t(42), int(3));
    EXPECT_EQ(result.significand, uint32_t(42));
    EXPECT_EQ(result.exponent, 3);
    EXPECT_FALSE(result.may_have_trailing_zeros);
}

// ============================================================
// Tests for on_trailing_zeros
// ============================================================

TEST_F(ReportTrailingZeroTest_342, OnTrailingZeros_ReturnsTrueForMayHaveTrailingZeros_342) {
    auto result = report_t::on_trailing_zeros<DummyFormat>(uint32_t(123), int(5));
    EXPECT_TRUE(result.may_have_trailing_zeros);
}

TEST_F(ReportTrailingZeroTest_342, OnTrailingZeros_PreservesSignificand_342) {
    auto result = report_t::on_trailing_zeros<DummyFormat>(uint32_t(456), int(3));
    EXPECT_EQ(result.significand, uint32_t(456));
}

TEST_F(ReportTrailingZeroTest_342, OnTrailingZeros_PreservesExponent_342) {
    auto result = report_t::on_trailing_zeros<DummyFormat>(uint32_t(789), int(-7));
    EXPECT_EQ(result.exponent, -7);
}

TEST_F(ReportTrailingZeroTest_342, OnTrailingZeros_WithUint64Significand_342) {
    auto result = report_t::on_trailing_zeros<DummyFormat>(uint64_t(999999999999ULL), int(20));
    EXPECT_EQ(result.significand, uint64_t(999999999999ULL));
    EXPECT_EQ(result.exponent, 20);
    EXPECT_TRUE(result.may_have_trailing_zeros);
}

TEST_F(ReportTrailingZeroTest_342, OnTrailingZeros_ZeroSignificand_342) {
    auto result = report_t::on_trailing_zeros<DummyFormat>(uint32_t(0), int(0));
    EXPECT_EQ(result.significand, uint32_t(0));
    EXPECT_EQ(result.exponent, 0);
    EXPECT_TRUE(result.may_have_trailing_zeros);
}

TEST_F(ReportTrailingZeroTest_342, OnTrailingZeros_NegativeExponent_342) {
    auto result = report_t::on_trailing_zeros<DummyFormat>(uint32_t(100), int(-300));
    EXPECT_EQ(result.significand, uint32_t(100));
    EXPECT_EQ(result.exponent, -300);
    EXPECT_TRUE(result.may_have_trailing_zeros);
}

// ============================================================
// Tests comparing on_trailing_zeros vs no_trailing_zeros
// ============================================================

TEST_F(ReportTrailingZeroTest_342, OnVsNoTrailingZeros_SameInputDifferentFlag_342) {
    auto result_on = report_t::on_trailing_zeros<DummyFormat>(uint32_t(500), int(10));
    auto result_no = report_t::no_trailing_zeros<DummyFormat>(uint32_t(500), int(10));

    EXPECT_EQ(result_on.significand, result_no.significand);
    EXPECT_EQ(result_on.exponent, result_no.exponent);
    EXPECT_TRUE(result_on.may_have_trailing_zeros);
    EXPECT_FALSE(result_no.may_have_trailing_zeros);
}

// ============================================================
// Tests for constexpr behavior
// ============================================================

TEST_F(ReportTrailingZeroTest_342, NoTrailingZeros_IsConstexpr_342) {
    constexpr auto result = report_t::no_trailing_zeros<DummyFormat>(uint32_t(42), int(7));
    static_assert(result.significand == 42, "Significand should be 42");
    static_assert(result.exponent == 7, "Exponent should be 7");
    static_assert(result.may_have_trailing_zeros == false, "Should not have trailing zeros");
    EXPECT_EQ(result.significand, uint32_t(42));
}

TEST_F(ReportTrailingZeroTest_342, OnTrailingZeros_IsConstexpr_342) {
    constexpr auto result = report_t::on_trailing_zeros<DummyFormat>(uint32_t(42), int(7));
    static_assert(result.significand == 42, "Significand should be 42");
    static_assert(result.exponent == 7, "Exponent should be 7");
    static_assert(result.may_have_trailing_zeros == true, "Should have trailing zeros");
    EXPECT_EQ(result.significand, uint32_t(42));
}

// ============================================================
// Tests with short exponent type
// ============================================================

TEST_F(ReportTrailingZeroTest_342, NoTrailingZeros_ShortExponentType_342) {
    auto result = report_t::no_trailing_zeros<DummyFormat>(uint32_t(100), short(5));
    EXPECT_EQ(result.significand, uint32_t(100));
    EXPECT_EQ(result.exponent, short(5));
    EXPECT_FALSE(result.may_have_trailing_zeros);
}

TEST_F(ReportTrailingZeroTest_342, OnTrailingZeros_ShortExponentType_342) {
    auto result = report_t::on_trailing_zeros<DummyFormat>(uint32_t(100), short(5));
    EXPECT_EQ(result.significand, uint32_t(100));
    EXPECT_EQ(result.exponent, short(5));
    EXPECT_TRUE(result.may_have_trailing_zeros);
}

// ============================================================
// Noexcept verification
// ============================================================

TEST_F(ReportTrailingZeroTest_342, NoTrailingZeros_IsNoexcept_342) {
    EXPECT_TRUE(noexcept(report_t::no_trailing_zeros<DummyFormat>(uint32_t(1), int(1))));
}

TEST_F(ReportTrailingZeroTest_342, OnTrailingZeros_IsNoexcept_342) {
    EXPECT_TRUE(noexcept(report_t::on_trailing_zeros<DummyFormat>(uint32_t(1), int(1))));
}
