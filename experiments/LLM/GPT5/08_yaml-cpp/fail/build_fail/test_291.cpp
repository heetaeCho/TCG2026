// TEST_ID: 291
#include <gtest/gtest.h>

#include <type_traits>

#include "TestProjects/yaml-cpp/src/contrib/dragonbox.h"

namespace {

using YAML::jkj::dragonbox::exponent_int;

// A simple FormatTraits stub with a clearly-defined mapping.
// We only verify that float_bits::binary_exponent forwards to FormatTraits::binary_exponent.
struct TestFormatTraits_291 {
	static constexpr exponent_int binary_exponent(exponent_int exponent_bits) noexcept {
		// Deterministic, non-identity mapping to make forwarding verifiable.
		return static_cast<exponent_int>(exponent_bits + static_cast<exponent_int>(7));
	}
};

using FloatBits_291 = YAML::jkj::dragonbox::float_bits<TestFormatTraits_291>;

class FloatBitsBinaryExponentTest_291 : public ::testing::Test {};

TEST_F(FloatBitsBinaryExponentTest_291, ForwardsZero_291) {
	const exponent_int in = static_cast<exponent_int>(0);
	const exponent_int expected = TestFormatTraits_291::binary_exponent(in);

	EXPECT_EQ(FloatBits_291::binary_exponent(in), expected);
}

TEST_F(FloatBitsBinaryExponentTest_291, ForwardsPositiveValue_291) {
	const exponent_int in = static_cast<exponent_int>(5);
	const exponent_int expected = TestFormatTraits_291::binary_exponent(in);

	EXPECT_EQ(FloatBits_291::binary_exponent(in), expected);
}

TEST_F(FloatBitsBinaryExponentTest_291, ForwardsNegativeValue_291) {
	// Even if exponent_int were unsigned in some builds, this still compiles because of the cast.
	const exponent_int in = static_cast<exponent_int>(-3);
	const exponent_int expected = TestFormatTraits_291::binary_exponent(in);

	EXPECT_EQ(FloatBits_291::binary_exponent(in), expected);
}

TEST_F(FloatBitsBinaryExponentTest_291, ForwardsLargeMagnitudeValue_291) {
	// Use a literal that stays reasonable across typical exponent_int definitions.
	const exponent_int in = static_cast<exponent_int>(12345);
	const exponent_int expected = TestFormatTraits_291::binary_exponent(in);

	EXPECT_EQ(FloatBits_291::binary_exponent(in), expected);
}

TEST_F(FloatBitsBinaryExponentTest_291, IsNoexcept_291) {
	static_assert(noexcept(FloatBits_291::binary_exponent(static_cast<exponent_int>(0))),
	              "binary_exponent(exponent_bits) should be noexcept");
	SUCCEED();
}

TEST_F(FloatBitsBinaryExponentTest_291, IsConstexprEvaluable_291) {
	// If forwarding is constexpr-friendly, these compile-time checks will pass.
	constexpr exponent_int in = static_cast<exponent_int>(11);
	constexpr exponent_int out = FloatBits_291::binary_exponent(in);
	static_assert(out == TestFormatTraits_291::binary_exponent(in),
	              "binary_exponent should match FormatTraits::binary_exponent at compile time");
	SUCCEED();
}

}  // namespace