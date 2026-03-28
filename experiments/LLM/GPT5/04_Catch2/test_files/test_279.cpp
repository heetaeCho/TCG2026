// StringMaker_double_convert_tests_279.cpp
#include <gtest/gtest.h>
#include <string>
#include <algorithm>
#include <cctype>
#include <cmath>
#include <limits>

#include "catch2/catch_tostring.hpp"  // Interface under test

namespace {

// Tiny helper: lowercase a string for case-insensitive checks.
std::string ToLower(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(),
                   [](unsigned char c){ return static_cast<char>(std::tolower(c)); });
    return s;
}

} // namespace

// Test fixture kept empty for consistency/extension.
class StringMakerDoubleTest_279 : public ::testing::Test {};

// Normal operation: finite round-trip parse
TEST_F(StringMakerDoubleTest_279, ConvertsFiniteNumber_RoundTripParse_279) {
    const double input = 123.456;
    const std::string out = Catch::StringMaker<double>::convert(input);

    // Observable behaviors only: returns a non-empty, parsable representation of the value.
    ASSERT_FALSE(out.empty());
    // stod should parse a finite number from the produced string
    const double parsed = std::stod(out);
    // Allow reasonable tolerance to avoid depending on exact formatting/precision.
    ASSERT_NEAR(parsed, input, 1e-9);
}

// Boundary: very large finite value remains parsable
TEST_F(StringMakerDoubleTest_279, ConvertsVeryLargeNumber_RoundTripParse_279) {
    // Well within finite range and commonly supported formatting
    const double input = 1e308;
    const std::string out = Catch::StringMaker<double>::convert(input);

    ASSERT_FALSE(out.empty());
    const double parsed = std::stod(out);
    // Relative tolerance because magnitude is large
    const double rel_err = std::abs(parsed - input) / input;
    ASSERT_LT(rel_err, 1e-12);
}

// Boundary: very small (but normal) positive value remains parsable
TEST_F(StringMakerDoubleTest_279, ConvertsVerySmallNumber_RoundTripParse_279) {
    const double input = 1e-308;
    const std::string out = Catch::StringMaker<double>::convert(input);

    ASSERT_FALSE(out.empty());
    const double parsed = std::stod(out);
    // Relative tolerance (avoid division by zero)
    const double rel_err = std::abs(parsed - input) / input;
    ASSERT_LT(rel_err, 1e-12);
}

// Exceptional: NaN formats to a string that clearly indicates NaN
TEST_F(StringMakerDoubleTest_279, ConvertsNaN_ContainsNaN_279) {
    const double input = std::numeric_limits<double>::quiet_NaN();
    const std::string out = Catch::StringMaker<double>::convert(input);

    ASSERT_FALSE(out.empty());
    const std::string low = ToLower(out);
    // Common, observable spellings: "nan"
    ASSERT_NE(low.find("nan"), std::string::npos);
}

// Exceptional: +Inf formats to a string that clearly indicates inf
TEST_F(StringMakerDoubleTest_279, ConvertsPosInfinity_ContainsInf_279) {
    const double input = std::numeric_limits<double>::infinity();
    const std::string out = Catch::StringMaker<double>::convert(input);

    ASSERT_FALSE(out.empty());
    const std::string low = ToLower(out);
    // Common, observable spellings: "inf"
    ASSERT_NE(low.find("inf"), std::string::npos);
}

// Exceptional: -Inf formats to a string that clearly indicates sign and inf
TEST_F(StringMakerDoubleTest_279, ConvertsNegInfinity_ContainsMinusInf_279) {
    const double input = -std::numeric_limits<double>::infinity();
    const std::string out = Catch::StringMaker<double>::convert(input);

    ASSERT_FALSE(out.empty());
    const std::string low = ToLower(out);
    // Expect both a minus sign and "inf" to be present in some order
    ASSERT_NE(low.find("inf"), std::string::npos);
    ASSERT_NE(out.find('-'), std::string::npos);
}

// Boundary: negative zero should parse to (positive) zero; we don't assert exact formatting
TEST_F(StringMakerDoubleTest_279, ConvertsNegativeZero_ParsesToZero_279) {
    const double input = -0.0;
    const std::string out = Catch::StringMaker<double>::convert(input);

    ASSERT_FALSE(out.empty());
    const double parsed = std::stod(out);
    ASSERT_DOUBLE_EQ(parsed, 0.0);
}

// Sanity: produced string should not be only whitespace
TEST_F(StringMakerDoubleTest_279, OutputIsNotWhitespaceOnly_279) {
    const double input = 42.0;
    const std::string out = Catch::StringMaker<double>::convert(input);

    ASSERT_FALSE(out.empty());
    const bool all_ws = std::all_of(out.begin(), out.end(),
        [](unsigned char c){ return std::isspace(c) != 0; });
    ASSERT_FALSE(all_ws);
}
