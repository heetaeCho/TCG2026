#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <string>

// Include the header under test
#include "catch2/matchers/internal/catch_matchers_impl.hpp"
#include "catch2/matchers/catch_matchers.hpp"
#include "catch2/catch_tostring.hpp"

// We need a concrete matcher to use with MatchExpr
// Using a simple custom matcher that implements the Catch matcher interface
namespace {

template <typename T>
struct TestMatcher : Catch::Matchers::MatcherBase<T> {
    std::string m_description;
    bool m_result;

    TestMatcher(std::string description, bool result)
        : m_description(std::move(description)), m_result(result) {}

    bool match(T const& val) const override {
        return m_result;
    }

    std::string describe() const override {
        return m_description;
    }
};

} // anonymous namespace

class MatchExprTest_133 : public ::testing::Test {
protected:
    std::ostringstream oss;
};

TEST_F(MatchExprTest_133, StreamReconstructedExpressionWithInt_133) {
    int value = 42;
    TestMatcher<int> matcher("is equal to 42", true);
    auto expr = Catch::MatchExpr<int, TestMatcher<int>>(std::move(value), matcher);

    expr.streamReconstructedExpression(oss);

    std::string result = oss.str();
    // Should contain the stringified value and the matcher description
    EXPECT_NE(result.find("42"), std::string::npos);
    EXPECT_NE(result.find("is equal to 42"), std::string::npos);
}

TEST_F(MatchExprTest_133, StreamReconstructedExpressionWithString_133) {
    std::string value = "hello";
    TestMatcher<std::string> matcher("contains 'hello'", true);
    auto expr = Catch::MatchExpr<std::string, TestMatcher<std::string>>(std::move(value), matcher);

    expr.streamReconstructedExpression(oss);

    std::string result = oss.str();
    EXPECT_NE(result.find("hello"), std::string::npos);
    EXPECT_NE(result.find("contains 'hello'"), std::string::npos);
}

TEST_F(MatchExprTest_133, StreamReconstructedExpressionFormatHasSpace_133) {
    int value = 10;
    TestMatcher<int> matcher("is greater than 5", true);
    auto expr = Catch::MatchExpr<int, TestMatcher<int>>(std::move(value), matcher);

    expr.streamReconstructedExpression(oss);

    std::string result = oss.str();
    // The format should be: stringify(arg) + ' ' + matcher.toString()
    // There should be a space separating them
    EXPECT_NE(result.find(" "), std::string::npos);
}

TEST_F(MatchExprTest_133, StreamReconstructedExpressionWithZero_133) {
    int value = 0;
    TestMatcher<int> matcher("is zero", true);
    auto expr = Catch::MatchExpr<int, TestMatcher<int>>(std::move(value), matcher);

    expr.streamReconstructedExpression(oss);

    std::string result = oss.str();
    EXPECT_NE(result.find("0"), std::string::npos);
    EXPECT_NE(result.find("is zero"), std::string::npos);
}

TEST_F(MatchExprTest_133, StreamReconstructedExpressionWithNegativeValue_133) {
    int value = -99;
    TestMatcher<int> matcher("is negative", false);
    auto expr = Catch::MatchExpr<int, TestMatcher<int>>(std::move(value), matcher);

    expr.streamReconstructedExpression(oss);

    std::string result = oss.str();
    EXPECT_NE(result.find("-99"), std::string::npos);
    EXPECT_NE(result.find("is negative"), std::string::npos);
}

TEST_F(MatchExprTest_133, StreamReconstructedExpressionWithEmptyMatcherDescription_133) {
    int value = 5;
    TestMatcher<int> matcher("", true);
    auto expr = Catch::MatchExpr<int, TestMatcher<int>>(std::move(value), matcher);

    expr.streamReconstructedExpression(oss);

    std::string result = oss.str();
    EXPECT_NE(result.find("5"), std::string::npos);
}

TEST_F(MatchExprTest_133, StreamReconstructedExpressionWithDouble_133) {
    double value = 3.14;
    TestMatcher<double> matcher("is approximately pi", true);
    auto expr = Catch::MatchExpr<double, TestMatcher<double>>(std::move(value), matcher);

    expr.streamReconstructedExpression(oss);

    std::string result = oss.str();
    EXPECT_NE(result.find("3.14"), std::string::npos);
    EXPECT_NE(result.find("is approximately pi"), std::string::npos);
}

TEST_F(MatchExprTest_133, StreamReconstructedExpressionWithBool_133) {
    bool value = true;
    TestMatcher<bool> matcher("is true", true);
    auto expr = Catch::MatchExpr<bool, TestMatcher<bool>>(std::move(value), matcher);

    expr.streamReconstructedExpression(oss);

    std::string result = oss.str();
    EXPECT_NE(result.find("true"), std::string::npos);
    EXPECT_NE(result.find("is true"), std::string::npos);
}
