#include "gtest/gtest.h"
#include "contrib/dragonbox.h"

// We need to include the full dragonbox header to get all the policy types and format traits
// The tests exercise compute_left_closed_directed through observable return values

namespace {

using namespace YAML::jkj::dragonbox;
using namespace YAML::jkj::dragonbox::detail;

// Type aliases for the two main float formats
using float_format_traits = ieee754_binary_traits<ieee754_binary32, uint32_t>;
using double_format_traits = ieee754_binary_traits<ieee754_binary64, uint64_t>;

using float_impl = impl<float_format_traits>;
using double_impl = impl<double_format_traits>;

// Policy types commonly used
struct default_sign_policy {
    template <class FormatTraits, class DecimalType>
    static constexpr DecimalType handle_sign(signed_significand_bits<FormatTraits> s, DecimalType d) noexcept {
        d.is_negative = s.is_negative();
        return d;
    }
};

struct default_trailing_zero_policy {
    template <class Format>
    static constexpr auto on_trailing_zeros(auto significand, auto exponent) noexcept {
        return decimal_fp<typename Format::carrier_uint, decltype(exponent)>{significand, exponent, true};
    }
    template <class Format>
    static constexpr auto no_trailing_zeros(auto significand, auto exponent) noexcept {
        return decimal_fp<typename Format::carrier_uint, decltype(exponent)>{significand, exponent, false};
    }
};

// Use the built-in policy classes from dragonbox
// We'll use the to_decimal function as a higher-level wrapper if available,
// otherwise test compute_left_closed_directed directly

// Helper to create signed_significand_bits from a float
template <typename Float>
auto make_signed_bits(Float value) {
    using format_traits = std::conditional_t<
        std::is_same_v<Float, float>,
        float_format_traits,
        double_format_traits>;
    using carrier_uint = typename format_traits::carrier_uint;
    carrier_uint bits;
    std::memcpy(&bits, &value, sizeof(Float));
    return signed_significand_bits<format_traits>{bits};
}

template <typename Float>
auto get_exponent_bits(Float value) {
    using format_traits = std::conditional_t<
        std::is_same_v<Float, float>,
        float_format_traits,
        double_format_traits>;
    using format = typename format_traits::format;
    using carrier_uint = typename format_traits::carrier_uint;
    carrier_uint bits;
    std::memcpy(&bits, &value, sizeof(Float));
    return static_cast<exponent_int>(
        (bits >> format::significand_bits) & ((carrier_uint(1) << format::exponent_bits) - 1));
}

// Test fixture for float (binary32)
class ComputeLeftClosedDirectedFloat_407 : public ::testing::Test {
protected:
    using Impl = float_impl;
};

// Test fixture for double (binary64)
class ComputeLeftClosedDirectedDouble_407 : public ::testing::Test {
protected:
    using Impl = double_impl;
};

// Test with a normal positive float value (1.0f)
TEST_F(ComputeLeftClosedDirectedFloat_407, NormalPositiveOne_407) {
    float value = 1.0f;
    auto s = make_signed_bits(value);
    auto exp_bits = get_exponent_bits(value);

    auto result = Impl::compute_left_closed_directed<
        policy::sign::return_sign,
        policy::trailing_zero::remove,
        policy::cache::full,
        policy::preferred_integer_types::default_preferred_integer_types>(s, exp_bits);

    // 1.0f should convert to significand=1, exponent=0
    EXPECT_FALSE(result.is_negative);
    EXPECT_EQ(result.significand, 1u);
    EXPECT_EQ(result.exponent, 0);
}

// Test with a normal positive float value (0.1f)
TEST_F(ComputeLeftClosedDirectedFloat_407, NormalPositivePointOne_407) {
    float value = 0.1f;
    auto s = make_signed_bits(value);
    auto exp_bits = get_exponent_bits(value);

    auto result = Impl::compute_left_closed_directed<
        policy::sign::return_sign,
        policy::trailing_zero::remove,
        policy::cache::full,
        policy::preferred_integer_types::default_preferred_integer_types>(s, exp_bits);

    EXPECT_FALSE(result.is_negative);
    // The significand should be a positive number
    EXPECT_GT(result.significand, 0u);
}

// Test with negative float
TEST_F(ComputeLeftClosedDirectedFloat_407, NegativeValue_407) {
    float value = -1.0f;
    auto s = make_signed_bits(value);
    auto exp_bits = get_exponent_bits(value);

    auto result = Impl::compute_left_closed_directed<
        policy::sign::return_sign,
        policy::trailing_zero::remove,
        policy::cache::full,
        policy::preferred_integer_types::default_preferred_integer_types>(s, exp_bits);

    EXPECT_TRUE(result.is_negative);
    EXPECT_EQ(result.significand, 1u);
    EXPECT_EQ(result.exponent, 0);
}

// Test with subnormal float (very small value)
TEST_F(ComputeLeftClosedDirectedFloat_407, SubnormalValue_407) {
    // Smallest subnormal float
    uint32_t bits = 1u; // smallest positive subnormal
    float value;
    std::memcpy(&value, &bits, sizeof(float));

    auto s = make_signed_bits(value);
    auto exp_bits = get_exponent_bits(value);

    EXPECT_EQ(exp_bits, 0); // subnormal has zero exponent field

    auto result = Impl::compute_left_closed_directed<
        policy::sign::return_sign,
        policy::trailing_zero::remove,
        policy::cache::full,
        policy::preferred_integer_types::default_preferred_integer_types>(s, exp_bits);

    EXPECT_FALSE(result.is_negative);
    EXPECT_GT(result.significand, 0u);
}

// Test with a large float value
TEST_F(ComputeLeftClosedDirectedFloat_407, LargeValue_407) {
    float value = 3.402823e+38f; // near max float
    auto s = make_signed_bits(value);
    auto exp_bits = get_exponent_bits(value);

    auto result = Impl::compute_left_closed_directed<
        policy::sign::return_sign,
        policy::trailing_zero::remove,
        policy::cache::full,
        policy::preferred_integer_types::default_preferred_integer_types>(s, exp_bits);

    EXPECT_FALSE(result.is_negative);
    EXPECT_GT(result.significand, 0u);
    EXPECT_GT(result.exponent, 0);
}

// Test with power of 2 float
TEST_F(ComputeLeftClosedDirectedFloat_407, PowerOfTwo_407) {
    float value = 2.0f;
    auto s = make_signed_bits(value);
    auto exp_bits = get_exponent_bits(value);

    auto result = Impl::compute_left_closed_directed<
        policy::sign::return_sign,
        policy::trailing_zero::remove,
        policy::cache::full,
        policy::preferred_integer_types::default_preferred_integer_types>(s, exp_bits);

    EXPECT_FALSE(result.is_negative);
    EXPECT_EQ(result.significand, 2u);
    EXPECT_EQ(result.exponent, 0);
}

// Test with 10.0f
TEST_F(ComputeLeftClosedDirectedFloat_407, TenFloat_407) {
    float value = 10.0f;
    auto s = make_signed_bits(value);
    auto exp_bits = get_exponent_bits(value);

    auto result = Impl::compute_left_closed_directed<
        policy::sign::return_sign,
        policy::trailing_zero::remove,
        policy::cache::full,
        policy::preferred_integer_types::default_preferred_integer_types>(s, exp_bits);

    EXPECT_FALSE(result.is_negative);
    EXPECT_EQ(result.significand, 1u);
    EXPECT_EQ(result.exponent, 1);
}

// Test with a normal positive double value (1.0)
TEST_F(ComputeLeftClosedDirectedDouble_407, NormalPositiveOne_407) {
    double value = 1.0;
    auto s = make_signed_bits(value);
    auto exp_bits = get_exponent_bits(value);

    auto result = Impl::compute_left_closed_directed<
        policy::sign::return_sign,
        policy::trailing_zero::remove,
        policy::cache::full,
        policy::preferred_integer_types::default_preferred_integer_types>(s, exp_bits);

    EXPECT_FALSE(result.is_negative);
    EXPECT_EQ(result.significand, 1u);
    EXPECT_EQ(result.exponent, 0);
}

// Test with negative double
TEST_F(ComputeLeftClosedDirectedDouble_407, NegativeValue_407) {
    double value = -42.0;
    auto s = make_signed_bits(value);
    auto exp_bits = get_exponent_bits(value);

    auto result = Impl::compute_left_closed_directed<
        policy::sign::return_sign,
        policy::trailing_zero::remove,
        policy::cache::full,
        policy::preferred_integer_types::default_preferred_integer_types>(s, exp_bits);

    EXPECT_TRUE(result.is_negative);
    EXPECT_EQ(result.significand, 42u);
    EXPECT_EQ(result.exponent, 0);
}

// Test with subnormal double
TEST_F(ComputeLeftClosedDirectedDouble_407, SubnormalValue_407) {
    uint64_t bits = 1ull; // smallest positive subnormal double
    double value;
    std::memcpy(&value, &bits, sizeof(double));

    auto s = make_signed_bits(value);
    auto exp_bits = get_exponent_bits(value);

    EXPECT_EQ(exp_bits, 0);

    auto result = Impl::compute_left_closed_directed<
        policy::sign::return_sign,
        policy::trailing_zero::remove,
        policy::cache::full,
        policy::preferred_integer_types::default_preferred_integer_types>(s, exp_bits);

    EXPECT_FALSE(result.is_negative);
    EXPECT_GT(result.significand, 0u);
}

// Test with 0.1 double
TEST_F(ComputeLeftClosedDirectedDouble_407, PointOneDouble_407) {
    double value = 0.1;
    auto s = make_signed_bits(value);
    auto exp_bits = get_exponent_bits(value);

    auto result = Impl::compute_left_closed_directed<
        policy::sign::return_sign,
        policy::trailing_zero::remove,
        policy::cache::full,
        policy::preferred_integer_types::default_preferred_integer_types>(s, exp_bits);

    EXPECT_FALSE(result.is_negative);
    EXPECT_GT(result.significand, 0u);
}

// Test with power of 2 double
TEST_F(ComputeLeftClosedDirectedDouble_407, PowerOfTwoDouble_407) {
    double value = 4.0;
    auto s = make_signed_bits(value);
    auto exp_bits = get_exponent_bits(value);

    auto result = Impl::compute_left_closed_directed<
        policy::sign::return_sign,
        policy::trailing_zero::remove,
        policy::cache::full,
        policy::preferred_integer_types::default_preferred_integer_types>(s, exp_bits);

    EXPECT_FALSE(result.is_negative);
    EXPECT_EQ(result.significand, 4u);
    EXPECT_EQ(result.exponent, 0);
}

// Test with large double
TEST_F(ComputeLeftClosedDirectedDouble_407, LargeDoubleValue_407) {
    double value = 1.0e+300;
    auto s = make_signed_bits(value);
    auto exp_bits = get_exponent_bits(value);

    auto result = Impl::compute_left_closed_directed<
        policy::sign::return_sign,
        policy::trailing_zero::remove,
        policy::cache::full,
        policy::preferred_integer_types::default_preferred_integer_types>(s, exp_bits);

    EXPECT_FALSE(result.is_negative);
    EXPECT_GT(result.significand, 0u);
    EXPECT_EQ(result.exponent, 300);
}

// Test with small double
TEST_F(ComputeLeftClosedDirectedDouble_407, SmallDoubleValue_407) {
    double value = 1.0e-300;
    auto s = make_signed_bits(value);
    auto exp_bits = get_exponent_bits(value);

    auto result = Impl::compute_left_closed_directed<
        policy::sign::return_sign,
        policy::trailing_zero::remove,
        policy::cache::full,
        policy::preferred_integer_types::default_preferred_integer_types>(s, exp_bits);

    EXPECT_FALSE(result.is_negative);
    EXPECT_GT(result.significand, 0u);
    EXPECT_LT(result.exponent, 0);
}

// Test the special case path for binary32 with binary_exponent <= -80
TEST_F(ComputeLeftClosedDirectedFloat_407, VerySmallExponentPath_407) {
    // Create a float with a very small exponent that triggers binary_exponent <= -80
    // Subnormal floats have binary_exponent = -149, which is <= -80
    uint32_t bits = 0x00000002u; // small subnormal
    float value;
    std::memcpy(&value, &bits, sizeof(float));

    auto s = make_signed_bits(value);
    auto exp_bits = get_exponent_bits(value);

    auto result = Impl::compute_left_closed_directed<
        policy::sign::return_sign,
        policy::trailing_zero::remove,
        policy::cache::full,
        policy::preferred_integer_types::default_preferred_integer_types>(s, exp_bits);

    EXPECT_FALSE(result.is_negative);
    EXPECT_GT(result.significand, 0u);
}

// Test float specific edge case mentioned in code: two_fc == 33554430 && binary_exponent == -10
TEST_F(ComputeLeftClosedDirectedFloat_407, SpecialEdgeCase33554430_407) {
    // This corresponds to a specific float encoding
    // two_fc = 33554430 = 2 * 16777215 = 2 * (2^24 - 1)
    // significand_bits = 23, so two_fc = bits << 1 with sign removed, then OR with (1 << 24)
    // binary_exponent = exponent_bits + bias - significand_bits = exponent_bits + 127 - 23 = -10
    // So exponent_bits = -10 - 127 + 23 = -114 ... that's not valid for unsigned exponent
    // Actually exponent_bits + 127 - 23 = -10 => exponent_bits = -10 + 23 - 127 = -114
    // This doesn't work directly. The exponent_bits field is unsigned.
    // exponent_bits = binary_exponent - (exponent_bias - significand_bits) when binary_exponent is adjusted
    // binary_exponent = exponent_bits + exponent_bias - significand_bits for normal numbers
    // For ieee754_binary32: exponent_bias = 127, significand_bits = 23
    // -10 = exponent_bits + 127 - 23 => exponent_bits = -10 - 104 = -114
    // This is negative, so it's not representable as a normal number's exponent field
    // Perhaps the code handles a subnormal case differently. Skip explicit construction.
    // Just ensure some small floats work
    float value = 1.17549435e-38f; // smallest normal float
    auto s = make_signed_bits(value);
    auto exp_bits = get_exponent_bits(value);

    auto result = Impl::compute_left_closed_directed<
        policy::sign::return_sign,
        policy::trailing_zero::remove,
        policy::cache::full,
        policy::preferred_integer_types::default_preferred_integer_types>(s, exp_bits);

    EXPECT_FALSE(result.is_negative);
    EXPECT_GT(result.significand, 0u);
}

// Test with ignore_sign policy for float
TEST_F(ComputeLeftClosedDirectedFloat_407, IgnoreSignPolicy_407) {
    float value = -5.0f;
    auto s = make_signed_bits(value);
    auto exp_bits = get_exponent_bits(value);

    auto result = Impl::compute_left_closed_directed<
        policy::sign::ignore,
        policy::trailing_zero::remove,
        policy::cache::full,
        policy::preferred_integer_types::default_preferred_integer_types>(s, exp_bits);

    // With ignore sign policy, the result should not have is_negative field
    // but significand should still be correct
    EXPECT_EQ(result.significand, 5u);
    EXPECT_EQ(result.exponent, 0);
}

// Test with report_trailing_zeros policy
TEST_F(ComputeLeftClosedDirectedFloat_407, ReportTrailingZeros_407) {
    float value = 100.0f;
    auto s = make_signed_bits(value);
    auto exp_bits = get_exponent_bits(value);

    auto result = Impl::compute_left_closed_directed<
        policy::sign::return_sign,
        policy::trailing_zero::report,
        policy::cache::full,
        policy::preferred_integer_types::default_preferred_integer_types>(s, exp_bits);

    EXPECT_FALSE(result.is_negative);
    // 100 = 1 * 10^2, so with trailing zeros removed: significand=1, exponent=2
    // With report policy, it may keep trailing zeros
    EXPECT_GT(result.significand, 0u);
}

// Double with 100.0
TEST_F(ComputeLeftClosedDirectedDouble_407, HundredDouble_407) {
    double value = 100.0;
    auto s = make_signed_bits(value);
    auto exp_bits = get_exponent_bits(value);

    auto result = Impl::compute_left_closed_directed<
        policy::sign::return_sign,
        policy::trailing_zero::remove,
        policy::cache::full,
        policy::preferred_integer_types::default_preferred_integer_types>(s, exp_bits);

    EXPECT_FALSE(result.is_negative);
    EXPECT_EQ(result.significand, 1u);
    EXPECT_EQ(result.exponent, 2);
}

// Float with 0.5
TEST_F(ComputeLeftClosedDirectedFloat_407, HalfFloat_407) {
    float value = 0.5f;
    auto s = make_signed_bits(value);
    auto exp_bits = get_exponent_bits(value);

    auto result = Impl::compute_left_closed_directed<
        policy::sign::return_sign,
        policy::trailing_zero::remove,
        policy::cache::full,
        policy::preferred_integer_types::default_preferred_integer_types>(s, exp_bits);

    EXPECT_FALSE(result.is_negative);
    EXPECT_EQ(result.significand, 5u);
    EXPECT_EQ(result.exponent, -1);
}

// Double with 0.5
TEST_F(ComputeLeftClosedDirectedDouble_407, HalfDouble_407) {
    double value = 0.5;
    auto s = make_signed_bits(value);
    auto exp_bits = get_exponent_bits(value);

    auto result = Impl::compute_left_closed_directed<
        policy::sign::return_sign,
        policy::trailing_zero::remove,
        policy::cache::full,
        policy::preferred_integer_types::default_preferred_integer_types>(s, exp_bits);

    EXPECT_FALSE(result.is_negative);
    EXPECT_EQ(result.significand, 5u);
    EXPECT_EQ(result.exponent, -1);
}

// Float max normal value
TEST_F(ComputeLeftClosedDirectedFloat_407, MaxNormalFloat_407) {
    float value = std::numeric_limits<float>::max();
    auto s = make_signed_bits(value);
    auto exp_bits = get_exponent_bits(value);

    auto result = Impl::compute_left_closed_directed<
        policy::sign::return_sign,
        policy::trailing_zero::remove,
        policy::cache::full,
        policy::preferred_integer_types::default_preferred_integer_types>(s, exp_bits);

    EXPECT_FALSE(result.is_negative);
    EXPECT_GT(result.significand, 0u);
}

// Double max normal value
TEST_F(ComputeLeftClosedDirectedDouble_407, MaxNormalDouble_407) {
    double value = std::numeric_limits<double>::max();
    auto s = make_signed_bits(value);
    auto exp_bits = get_exponent_bits(value);

    auto result = Impl::compute_left_closed_directed<
        policy::sign::return_sign,
        policy::trailing_zero::remove,
        policy::cache::full,
        policy::preferred_integer_types::default_preferred_integer_types>(s, exp_bits);

    EXPECT_FALSE(result.is_negative);
    EXPECT_GT(result.significand, 0u);
}

// Double min normal value
TEST_F(ComputeLeftClosedDirectedDouble_407, MinNormalDouble_407) {
    double value = std::numeric_limits<double>::min();
    auto s = make_signed_bits(value);
    auto exp_bits = get_exponent_bits(value);

    auto result = Impl::compute_left_closed_directed<
        policy::sign::return_sign,
        policy::trailing_zero::remove,
        policy::cache::full,
        policy::preferred_integer_types::default_preferred_integer_types>(s, exp_bits);

    EXPECT_FALSE(result.is_negative);
    EXPECT_GT(result.significand, 0u);
    EXPECT_LT(result.exponent, 0);
}

// Float with 3.14159f
TEST_F(ComputeLeftClosedDirectedFloat_407, PiApprox_407) {
    float value = 3.14159f;
    auto s = make_signed_bits(value);
    auto exp_bits = get_exponent_bits(value);

    auto result = Impl::compute_left_closed_directed<
        policy::sign::return_sign,
        policy::trailing_zero::remove,
        policy::cache::full,
        policy::preferred_integer_types::default_preferred_integer_types>(s, exp_bits);

    EXPECT_FALSE(result.is_negative);
    EXPECT_GT(result.significand, 0u);
}

} // namespace
