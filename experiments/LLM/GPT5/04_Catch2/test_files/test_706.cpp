// File: test_approx_toString_706.cpp

#include <gtest/gtest.h>

#include <catch2/catch_approx.hpp>
#include <catch2/catch_tostring.hpp> // for Catch::Detail::stringify

namespace {

using Catch::Approx;

// A tiny helper to build the expected string using the same public stringify.
static std::string expectedString(double v) {
    return std::string("Approx( ") + Catch::Detail::stringify(v) + " )";
}

class ApproxToStringTest_706 : public ::testing::Test {};

} // namespace

// [Normal] Basic positive value formatting via constructor
TEST_F(ApproxToStringTest_706, ToStringBasicPositive_706) {
    Approx a{3.5};
    EXPECT_EQ(a.toString(), expectedString(3.5));
}

// [Normal] Templated constructor from integral type should still stringify the stored double
TEST_F(ApproxToStringTest_706, ToStringFromIntCtor_706) {
    int v = 7;
    Approx a{v}; // uses templated ctor; internally stored as double
    EXPECT_EQ(a.toString(), expectedString(static_cast<double>(v)));
}

// [Boundary] Zero value
TEST_F(ApproxToStringTest_706, ToStringZero_706) {
    Approx a{0.0};
    EXPECT_EQ(a.toString(), expectedString(0.0));
}

// [Boundary] Large magnitude value
TEST_F(ApproxToStringTest_706, ToStringLargeMagnitude_706) {
    double v = 1e100;
    Approx a{v};
    EXPECT_EQ(a.toString(), expectedString(v));
}

// [Normal] Negative value
TEST_F(ApproxToStringTest_706, ToStringNegative_706) {
    double v = -2.25;
    Approx a{v};
    EXPECT_EQ(a.toString(), expectedString(v));
}

// [Observable behavior] operator() creates a new Approx with the provided value;
// original should remain unchanged.
TEST_F(ApproxToStringTest_706, ToStringAfterCallOperator_706) {
    Approx base{0.5};
    std::string baseBefore = base.toString();

    auto other = base(42.0); // returns a new Approx with value 42.0
    EXPECT_EQ(other.toString(), expectedString(42.0));

    // Ensure base is unchanged (observable through its toString)
    EXPECT_EQ(base.toString(), baseBefore);
}

// [Observable behavior] Unary minus should return an Approx whose string shows negated value
TEST_F(ApproxToStringTest_706, ToStringUnaryMinus_706) {
    double v = 3.25;
    Approx a{v};

    auto neg = -a;
    EXPECT_EQ(neg.toString(), expectedString(-v));
}
