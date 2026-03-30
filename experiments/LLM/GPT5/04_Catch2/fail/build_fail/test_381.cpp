// File: tests/invokeLambda_tests_381.cpp
#include <gtest/gtest.h>
#include <string>

// Adjust include path as needed for your project layout.
#include "Catch2/src/catch2/internal/catch_clara.hpp"

namespace {
using Catch::Clara::Detail::invokeLambda;

// Suite name includes TEST_ID as requested.
class InvokeLambdaTest_381 : public ::testing::Test {};
} // namespace

// Normal operation: successful conversion calls the lambda with the converted value.
TEST(InvokeLambdaTest_381, CallsLambdaOnSuccessfulIntConversion_381) {
    int received = 0;
    bool called = false;

    auto lambda = [&](int v) { called = true; received = v; /* returns void */ };

    auto result = Catch::Clara::Detail::invokeLambda<int>(lambda, std::string{"42"});

    EXPECT_TRUE(result);          // observable success
    EXPECT_TRUE(called);          // lambda was invoked
    EXPECT_EQ(42, received);      // value was forwarded correctly
}

// Error path: failed conversion should return failure and skip invoking the lambda.
TEST(InvokeLambdaTest_381, ReturnsFailureAndSkipsLambdaOnBadInt_381) {
    bool called = false;

    auto lambda = [&](int) { called = true; };

    auto result = Catch::Clara::Detail::invokeLambda<int>(lambda, std::string{"not_an_int"});

    EXPECT_FALSE(result);         // observable failure from conversion
    EXPECT_FALSE(called);         // lambda must not be called on conversion failure
}

// Boundary-ish / formatting case: floating-point value forwarded exactly when convertible.
TEST(InvokeLambdaTest_381, ForwardsConvertedDoubleValue_381) {
    double got = 0.0;
    bool called = false;

    auto lambda = [&](double d) { called = true; got = d; };

    auto result = Catch::Clara::Detail::invokeLambda<double>(lambda, std::string{"3.5"});

    EXPECT_TRUE(result);
    EXPECT_TRUE(called);
    EXPECT_DOUBLE_EQ(3.5, got);
}

// Verification of external interaction semantics when lambda returns bool: false -> observable failure.
TEST(InvokeLambdaTest_381, PropagatesBoolReturningLambda_FalseMeansFailure_381) {
    auto lambda = [&](int) -> bool { return false; };

    auto result = Catch::Clara::Detail::invokeLambda<int>(lambda, std::string{"0"});

    EXPECT_FALSE(result); // Expect ParserResult reflects lambda's false (via LambdaInvoker)
}

// Verification of external interaction semantics when lambda returns bool: true -> observable success.
TEST(InvokeLambdaTest_381, PropagatesBoolReturningLambda_TrueMeansSuccess_381) {
    auto lambda = [&](int) -> bool { return true; };

    auto result = Catch::Clara::Detail::invokeLambda<int>(lambda, std::string{"123"});

    EXPECT_TRUE(result); // Expect ParserResult reflects lambda's true (via LambdaInvoker)
}

// String passthrough: when ArgType is std::string, value should be forwarded as-is.
TEST(InvokeLambdaTest_381, SupportsStringArgument_PassesThrough_381) {
    std::string got;
    bool called = false;

    auto lambda = [&](const std::string& s) { called = true; got = s; };

    auto result = Catch::Clara::Detail::invokeLambda<std::string>(lambda, std::string{"hello"});

    EXPECT_TRUE(result);
    EXPECT_TRUE(called);
    EXPECT_EQ("hello", got);
}
