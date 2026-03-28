#include <gtest/gtest.h>
#include <sstream>
#include <utility>

// Include the necessary Exiv2 headers
#include "types.hpp"

// Test ID: 1135

// Test normal operation: basic URational output
TEST(URationalOutputTest_1135, BasicOutput_1135) {
    std::ostringstream oss;
    Exiv2::URational r(1, 2);
    oss << r;
    EXPECT_EQ(oss.str(), "1/2");
}

// Test normal operation: another fraction
TEST(URationalOutputTest_1135, AnotherFraction_1135) {
    std::ostringstream oss;
    Exiv2::URational r(3, 4);
    oss << r;
    EXPECT_EQ(oss.str(), "3/4");
}

// Test boundary: zero numerator
TEST(URationalOutputTest_1135, ZeroNumerator_1135) {
    std::ostringstream oss;
    Exiv2::URational r(0, 1);
    oss << r;
    EXPECT_EQ(oss.str(), "0/1");
}

// Test boundary: zero denominator
TEST(URationalOutputTest_1135, ZeroDenominator_1135) {
    std::ostringstream oss;
    Exiv2::URational r(1, 0);
    oss << r;
    EXPECT_EQ(oss.str(), "1/0");
}

// Test boundary: both zero
TEST(URationalOutputTest_1135, BothZero_1135) {
    std::ostringstream oss;
    Exiv2::URational r(0, 0);
    oss << r;
    EXPECT_EQ(oss.str(), "0/0");
}

// Test boundary: large values (max uint32_t)
TEST(URationalOutputTest_1135, LargeValues_1135) {
    std::ostringstream oss;
    Exiv2::URational r(4294967295u, 4294967295u);
    oss << r;
    EXPECT_EQ(oss.str(), "4294967295/4294967295");
}

// Test boundary: max numerator with denominator 1
TEST(URationalOutputTest_1135, MaxNumeratorDenomOne_1135) {
    std::ostringstream oss;
    Exiv2::URational r(4294967295u, 1);
    oss << r;
    EXPECT_EQ(oss.str(), "4294967295/1");
}

// Test normal: whole number representation
TEST(URationalOutputTest_1135, WholeNumber_1135) {
    std::ostringstream oss;
    Exiv2::URational r(5, 1);
    oss << r;
    EXPECT_EQ(oss.str(), "5/1");
}

// Test normal: equal numerator and denominator
TEST(URationalOutputTest_1135, EqualParts_1135) {
    std::ostringstream oss;
    Exiv2::URational r(7, 7);
    oss << r;
    EXPECT_EQ(oss.str(), "7/7");
}

// Test: chaining output operator
TEST(URationalOutputTest_1135, ChainingOutput_1135) {
    std::ostringstream oss;
    Exiv2::URational r1(1, 2);
    Exiv2::URational r2(3, 4);
    oss << r1 << " " << r2;
    EXPECT_EQ(oss.str(), "1/2 3/4");
}

// Test: operator returns the same stream reference
TEST(URationalOutputTest_1135, ReturnsStreamReference_1135) {
    std::ostringstream oss;
    Exiv2::URational r(1, 2);
    std::ostream& ref = (oss << r);
    EXPECT_EQ(&ref, &oss);
}

// Test: numerator 1, denominator large
TEST(URationalOutputTest_1135, SmallNumeratorLargeDenominator_1135) {
    std::ostringstream oss;
    Exiv2::URational r(1, 1000000);
    oss << r;
    EXPECT_EQ(oss.str(), "1/1000000");
}

// Test: typical camera exposure value
TEST(URationalOutputTest_1135, TypicalExposureValue_1135) {
    std::ostringstream oss;
    Exiv2::URational r(1, 250);
    oss << r;
    EXPECT_EQ(oss.str(), "1/250");
}
