#include <catch2/internal/catch_clara.hpp>
#include <gtest/gtest.h>
#include <string>

using namespace Catch::Clara::Detail;

class BoundLambdaTest_382 : public ::testing::Test {
protected:
};

// Test that setValue with a string lambda successfully processes a normal string
TEST_F(BoundLambdaTest_382, SetValueWithStringLambda_NormalString_382) {
    std::string captured;
    auto lambda = [&captured](std::string const& s) { captured = s; };
    BoundLambda<decltype(lambda)> bound(lambda);

    auto result = bound.setValue("hello");

    EXPECT_EQ(captured, "hello");
    // ParserResult should indicate success for a valid string
    EXPECT_TRUE(static_cast<bool>(result));
}

// Test that setValue with a string lambda processes an empty string
TEST_F(BoundLambdaTest_382, SetValueWithStringLambda_EmptyString_382) {
    std::string captured;
    auto lambda = [&captured](std::string const& s) { captured = s; };
    BoundLambda<decltype(lambda)> bound(lambda);

    auto result = bound.setValue("");

    EXPECT_EQ(captured, "");
    EXPECT_TRUE(static_cast<bool>(result));
}

// Test that setValue with an int lambda parses integer from string
TEST_F(BoundLambdaTest_382, SetValueWithIntLambda_ValidInt_382) {
    int captured = 0;
    auto lambda = [&captured](int v) { captured = v; };
    BoundLambda<decltype(lambda)> bound(lambda);

    auto result = bound.setValue("42");

    EXPECT_EQ(captured, 42);
    EXPECT_TRUE(static_cast<bool>(result));
}

// Test that setValue with an int lambda handles negative integer
TEST_F(BoundLambdaTest_382, SetValueWithIntLambda_NegativeInt_382) {
    int captured = 0;
    auto lambda = [&captured](int v) { captured = v; };
    BoundLambda<decltype(lambda)> bound(lambda);

    auto result = bound.setValue("-100");

    EXPECT_EQ(captured, -100);
    EXPECT_TRUE(static_cast<bool>(result));
}

// Test that setValue with an int lambda handles zero
TEST_F(BoundLambdaTest_382, SetValueWithIntLambda_Zero_382) {
    int captured = -1;
    auto lambda = [&captured](int v) { captured = v; };
    BoundLambda<decltype(lambda)> bound(lambda);

    auto result = bound.setValue("0");

    EXPECT_EQ(captured, 0);
    EXPECT_TRUE(static_cast<bool>(result));
}

// Test that setValue with an int lambda fails on non-numeric string
TEST_F(BoundLambdaTest_382, SetValueWithIntLambda_InvalidString_382) {
    int captured = 0;
    auto lambda = [&captured](int v) { captured = v; };
    BoundLambda<decltype(lambda)> bound(lambda);

    auto result = bound.setValue("not_a_number");

    // Should fail to parse
    EXPECT_FALSE(static_cast<bool>(result));
}

// Test that setValue with a bool lambda handles "true"
TEST_F(BoundLambdaTest_382, SetValueWithBoolLambda_True_382) {
    bool captured = false;
    auto lambda = [&captured](bool v) { captured = v; };
    BoundLambda<decltype(lambda)> bound(lambda);

    auto result = bound.setValue("true");

    EXPECT_TRUE(captured);
    EXPECT_TRUE(static_cast<bool>(result));
}

// Test that setValue with a double lambda parses floating point
TEST_F(BoundLambdaTest_382, SetValueWithDoubleLambda_ValidDouble_382) {
    double captured = 0.0;
    auto lambda = [&captured](double v) { captured = v; };
    BoundLambda<decltype(lambda)> bound(lambda);

    auto result = bound.setValue("3.14");

    EXPECT_NEAR(captured, 3.14, 0.001);
    EXPECT_TRUE(static_cast<bool>(result));
}

// Test that setValue with a string lambda handles string with spaces
TEST_F(BoundLambdaTest_382, SetValueWithStringLambda_StringWithSpaces_382) {
    std::string captured;
    auto lambda = [&captured](std::string const& s) { captured = s; };
    BoundLambda<decltype(lambda)> bound(lambda);

    auto result = bound.setValue("hello world");

    EXPECT_EQ(captured, "hello world");
    EXPECT_TRUE(static_cast<bool>(result));
}

// Test that setValue can be called multiple times
TEST_F(BoundLambdaTest_382, SetValueCalledMultipleTimes_382) {
    std::string captured;
    auto lambda = [&captured](std::string const& s) { captured = s; };
    BoundLambda<decltype(lambda)> bound(lambda);

    bound.setValue("first");
    EXPECT_EQ(captured, "first");

    bound.setValue("second");
    EXPECT_EQ(captured, "second");
}

// Test that setValue with unsigned int lambda parses valid unsigned
TEST_F(BoundLambdaTest_382, SetValueWithUnsignedLambda_ValidUnsigned_382) {
    unsigned int captured = 0;
    auto lambda = [&captured](unsigned int v) { captured = v; };
    BoundLambda<decltype(lambda)> bound(lambda);

    auto result = bound.setValue("255");

    EXPECT_EQ(captured, 255u);
    EXPECT_TRUE(static_cast<bool>(result));
}

// Test that setValue with a very long string
TEST_F(BoundLambdaTest_382, SetValueWithStringLambda_VeryLongString_382) {
    std::string captured;
    auto lambda = [&captured](std::string const& s) { captured = s; };
    BoundLambda<decltype(lambda)> bound(lambda);

    std::string longStr(10000, 'x');
    auto result = bound.setValue(longStr);

    EXPECT_EQ(captured, longStr);
    EXPECT_TRUE(static_cast<bool>(result));
}
