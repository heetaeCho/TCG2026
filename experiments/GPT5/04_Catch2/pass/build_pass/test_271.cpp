// File: test_stringmaker_longlong_271.cpp

#include <gtest/gtest.h>
#include "Catch2/src/catch2/catch_tostring.hpp"

// For brevity
using Catch::StringMaker;

//
// Behavior under test (from given code snippet):
// - Always prints the decimal value.
// - If value > hexThreshold (255), additionally appends " (0x<hex>)" using lowercase hex digits.
// - Otherwise, no hex suffix is appended.
//

// Boundary: exactly at threshold -> no hex suffix.
TEST(StringMakerLongLongTest_271, AtThresholdPrintsDecimalOnly_271) {
    const long long value = 255; // hexThreshold
    const std::string out = StringMaker<long long>::convert(value);
    EXPECT_EQ(out, "255");
}

// Boundary: just above threshold -> decimal + hex suffix.
TEST(StringMakerLongLongTest_271, AboveThresholdAddsLowercaseHexSuffix_271) {
    const long long value = 256; // 0x100
    const std::string out = StringMaker<long long>::convert(value);
    EXPECT_EQ(out, "256 (0x100)");
}

// Normal: zero -> decimal only, no hex.
TEST(StringMakerLongLongTest_271, ZeroPrintedAsDecimalOnly_271) {
    const long long value = 0;
    const std::string out = StringMaker<long long>::convert(value);
    EXPECT_EQ(out, "0");
}

// Edge: negative value -> decimal only, no hex suffix even though absolute value might exceed threshold.
TEST(StringMakerLongLongTest_271, NegativeValuePrintedAsDecimalOnly_271) {
    const long long value = -42;
    const std::string out = StringMaker<long long>::convert(value);
    EXPECT_EQ(out, "-42");
}

// Normal: larger value well above threshold -> ensure lowercase hex and correct formatting.
TEST(StringMakerLongLongTest_271, LargeValueHasCorrectLowercaseHexAndFormat_271) {
    const long long value = 4095; // 0xFFF -> "fff" in lowercase with std::hex
    const std::string out = StringMaker<long long>::convert(value);
    EXPECT_EQ(out, "4095 (0xfff)");
}
