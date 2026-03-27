// File: stringmaker_float_convert_test_278.cpp
#include <gtest/gtest.h>
#include <string>
#include <cmath>
#include <limits>
#include "catch2/catch_tostring.hpp"

// Test fixture (not strictly necessary, but keeps naming consistent)
class StringMakerFloatTest_278 : public ::testing::Test {
protected:
    // Helper that asserts the output format contract and parses back the number.
    static float ParseNumberPart(const std::string& s) {
        ASSERT_FALSE(s.empty()) << "Converted string must not be empty";
        ASSERT_EQ('f', s.back()) << "Converted string must end with 'f'";
        const std::string number = s.substr(0, s.size() - 1);
        // std::stof should be able to parse what convert() produced
        // (black-box assumption: it is a valid float textual representation)
        return std::stof(number);
    }

    // Approx compare with a relative tolerance; avoids overfitting to formatting.
    static void ExpectAlmostEqual(float a, float b) {
        // Use a mixed tolerance: absolute for tiny values, relative otherwise.
        const float abs_a = std::fabs(a);
        const float eps = std::max(1e-6f, abs_a * 1e-6f);
        ASSERT_NEAR(a, b, eps);
    }
};

// --- Normal operation: returns a string that ends in 'f' for various values
TEST_F(StringMakerFloatTest_278, EndsWithF_ForTypicalValues_278) {
    EXPECT_EQ('f', Catch::StringMaker<float>::convert(3.14f).back());
    EXPECT_EQ('f', Catch::StringMaker<float>::convert(-2.5f).back());
    EXPECT_EQ('f', Catch::StringMaker<float>::convert(0.0f).back());
}

// --- Normal operation: string is parseable back to approximately the same value
TEST_F(StringMakerFloatTest_278, RoundTripParsing_PreservesValueWithinTolerance_278) {
    const float inputs[] = {
        0.0f,
        1.0f,
        -1.0f,
        3.1415926f,
        -123456.0f,
        1e-7f,     // very small (but normal) magnitude
        1e+7f      // large magnitude
    };

    for (float v : inputs) {
        const std::string out = Catch::StringMaker<float>::convert(v);
        float parsed = ParseNumberPart(out);
        ExpectAlmostEqual(v, parsed);
    }
}

// --- Boundary-ish values (finite extremes): still ends with 'f' and parses
TEST_F(StringMakerFloatTest_278, FiniteExtremeValues_AreFormattedAndParseable_278) {
    // Use slightly-reduced extremes to avoid any platform-dependent overflow on parse
    const float near_max = std::numeric_limits<float>::max() / 2.0f;
    const float near_min_pos = std::numeric_limits<float>::min() * 2.0f; // min() is smallest positive normal

    {
        const std::string out = Catch::StringMaker<float>::convert(near_max);
        float parsed = ParseNumberPart(out);
        // The formatter may choose scientific notation; only require numeric equivalence
        ExpectAlmostEqual(near_max, parsed);
    }
    {
        const std::string out = Catch::StringMaker<float>::convert(near_min_pos);
        float parsed = ParseNumberPart(out);
        ExpectAlmostEqual(near_min_pos, parsed);
    }
}

// --- Exceptional/error cases (observable): convert should not throw for finite inputs
TEST_F(StringMakerFloatTest_278, DoesNotThrow_ForFiniteInputs_278) {
    EXPECT_NO_THROW((void)Catch::StringMaker<float>::convert(42.0f));
    EXPECT_NO_THROW((void)Catch::StringMaker<float>::convert(-0.125f));
    EXPECT_NO_THROW((void)Catch::StringMaker<float>::convert(1e5f));
}

// --- Formatting contract: output is non-empty and contains at least one digit or sign before 'f'
TEST_F(StringMakerFloatTest_278, NonEmptyAndHasNumberPartBeforeSuffix_278) {
    const std::string out = Catch::StringMaker<float>::convert(12.5f);
    ASSERT_FALSE(out.empty());
    ASSERT_EQ('f', out.back());
    ASSERT_FALSE(out.substr(0, out.size() - 1).empty()) << "There must be a numeric portion before the 'f' suffix";
}
