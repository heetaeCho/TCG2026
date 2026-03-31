#include "catch2/internal/catch_clara.hpp"
#include "catch2/catch_all.hpp"
#include <gtest/gtest.h>
#include <string>

using namespace Catch::Clara::Detail;

class InvokeLambdaTest_381 : public ::testing::Test {
protected:
};

// Test that invokeLambda successfully converts and invokes with an int argument
TEST_F(InvokeLambdaTest_381, InvokeWithValidInt_381) {
    bool lambdaCalled = false;
    int receivedValue = 0;
    auto lambda = [&](int value) {
        lambdaCalled = true;
        receivedValue = value;
    };

    auto result = invokeLambda<int>(lambda, "42");

    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_TRUE(lambdaCalled);
    EXPECT_EQ(receivedValue, 42);
}

// Test that invokeLambda fails gracefully with invalid int input
TEST_F(InvokeLambdaTest_381, InvokeWithInvalidInt_381) {
    bool lambdaCalled = false;
    auto lambda = [&](int value) {
        lambdaCalled = true;
        (void)value;
    };

    auto result = invokeLambda<int>(lambda, "not_a_number");

    EXPECT_FALSE(static_cast<bool>(result));
    EXPECT_FALSE(lambdaCalled);
}

// Test with a double argument and valid string
TEST_F(InvokeLambdaTest_381, InvokeWithValidDouble_381) {
    bool lambdaCalled = false;
    double receivedValue = 0.0;
    auto lambda = [&](double value) {
        lambdaCalled = true;
        receivedValue = value;
    };

    auto result = invokeLambda<double>(lambda, "3.14");

    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_TRUE(lambdaCalled);
    EXPECT_NEAR(receivedValue, 3.14, 0.001);
}

// Test with a string argument - should always succeed in conversion
TEST_F(InvokeLambdaTest_381, InvokeWithString_381) {
    bool lambdaCalled = false;
    std::string receivedValue;
    auto lambda = [&](std::string const& value) {
        lambdaCalled = true;
        receivedValue = value;
    };

    auto result = invokeLambda<std::string>(lambda, "hello_world");

    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_TRUE(lambdaCalled);
    EXPECT_EQ(receivedValue, "hello_world");
}

// Test with empty string argument for string type
TEST_F(InvokeLambdaTest_381, InvokeWithEmptyString_381) {
    bool lambdaCalled = false;
    std::string receivedValue = "initial";
    auto lambda = [&](std::string const& value) {
        lambdaCalled = true;
        receivedValue = value;
    };

    auto result = invokeLambda<std::string>(lambda, "");

    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_TRUE(lambdaCalled);
    EXPECT_EQ(receivedValue, "");
}

// Test with bool argument - "true"
TEST_F(InvokeLambdaTest_381, InvokeWithBoolTrue_381) {
    bool lambdaCalled = false;
    bool receivedValue = false;
    auto lambda = [&](bool value) {
        lambdaCalled = true;
        receivedValue = value;
    };

    auto result = invokeLambda<bool>(lambda, "true");

    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_TRUE(lambdaCalled);
    EXPECT_TRUE(receivedValue);
}

// Test with negative int
TEST_F(InvokeLambdaTest_381, InvokeWithNegativeInt_381) {
    int receivedValue = 0;
    auto lambda = [&](int value) {
        receivedValue = value;
    };

    auto result = invokeLambda<int>(lambda, "-100");

    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_EQ(receivedValue, -100);
}

// Test with zero int
TEST_F(InvokeLambdaTest_381, InvokeWithZeroInt_381) {
    int receivedValue = -1;
    auto lambda = [&](int value) {
        receivedValue = value;
    };

    auto result = invokeLambda<int>(lambda, "0");

    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_EQ(receivedValue, 0);
}

// Test with unsigned int and valid value
TEST_F(InvokeLambdaTest_381, InvokeWithUnsignedInt_381) {
    unsigned int receivedValue = 0;
    auto lambda = [&](unsigned int value) {
        receivedValue = value;
    };

    auto result = invokeLambda<unsigned int>(lambda, "255");

    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_EQ(receivedValue, 255u);
}

// Test with empty string for int type - should fail conversion
TEST_F(InvokeLambdaTest_381, InvokeWithEmptyStringForInt_381) {
    bool lambdaCalled = false;
    auto lambda = [&](int value) {
        lambdaCalled = true;
        (void)value;
    };

    auto result = invokeLambda<int>(lambda, "");

    EXPECT_FALSE(static_cast<bool>(result));
    EXPECT_FALSE(lambdaCalled);
}

// Test with double that has invalid format
TEST_F(InvokeLambdaTest_381, InvokeWithInvalidDouble_381) {
    bool lambdaCalled = false;
    auto lambda = [&](double value) {
        lambdaCalled = true;
        (void)value;
    };

    auto result = invokeLambda<double>(lambda, "abc.def");

    EXPECT_FALSE(static_cast<bool>(result));
    EXPECT_FALSE(lambdaCalled);
}

// Test with a lambda that returns ParserResult (non-void return type)
TEST_F(InvokeLambdaTest_381, InvokeWithStringAndLambdaReturningVoid_381) {
    std::string captured;
    auto lambda = [&](std::string const& s) {
        captured = s;
    };

    auto result = invokeLambda<std::string>(lambda, "test_string");

    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_EQ(captured, "test_string");
}
