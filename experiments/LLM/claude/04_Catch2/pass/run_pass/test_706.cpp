#include <gtest/gtest.h>
#include "catch2/catch_approx.hpp"
#include <limits>
#include <string>
#include <cmath>

class ApproxTest_706 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test construction with double value
TEST_F(ApproxTest_706, ConstructWithDouble_706) {
    Catch::Approx approx(1.0);
    std::string str = approx.toString();
    EXPECT_NE(str.find("Approx("), std::string::npos);
    EXPECT_NE(str.find("1.0"), std::string::npos);
}

// Test construction with integer value (template constructor)
TEST_F(ApproxTest_706, ConstructWithInt_706) {
    Catch::Approx approx(5);
    std::string str = approx.toString();
    EXPECT_NE(str.find("Approx("), std::string::npos);
    EXPECT_NE(str.find("5"), std::string::npos);
}

// Test construction with zero
TEST_F(ApproxTest_706, ConstructWithZero_706) {
    Catch::Approx approx(0.0);
    std::string str = approx.toString();
    EXPECT_NE(str.find("Approx("), std::string::npos);
    EXPECT_NE(str.find("0"), std::string::npos);
}

// Test construction with negative value
TEST_F(ApproxTest_706, ConstructWithNegativeValue_706) {
    Catch::Approx approx(-3.14);
    std::string str = approx.toString();
    EXPECT_NE(str.find("Approx("), std::string::npos);
    EXPECT_NE(str.find("-3.14"), std::string::npos);
}

// Test toString format
TEST_F(ApproxTest_706, ToStringFormat_706) {
    Catch::Approx approx(42.0);
    std::string str = approx.toString();
    // Should start with "Approx( " and end with " )"
    EXPECT_EQ(str.substr(0, 8), "Approx( ");
    EXPECT_EQ(str.substr(str.size() - 2), " )");
}

// Test unary negation operator
TEST_F(ApproxTest_706, UnaryNegation_706) {
    Catch::Approx approx(5.0);
    Catch::Approx negated = -approx;
    std::string str = negated.toString();
    EXPECT_NE(str.find("-5"), std::string::npos);
}

// Test unary negation of negative value results in positive
TEST_F(ApproxTest_706, UnaryNegationOfNegative_706) {
    Catch::Approx approx(-7.0);
    Catch::Approx negated = -approx;
    std::string str = negated.toString();
    EXPECT_NE(str.find("7"), std::string::npos);
    // Should not contain "--7" or similar
}

// Test unary negation of zero
TEST_F(ApproxTest_706, UnaryNegationOfZero_706) {
    Catch::Approx approx(0.0);
    Catch::Approx negated = -approx;
    std::string str = negated.toString();
    EXPECT_NE(str.find("0"), std::string::npos);
}

// Test custom() static factory method
TEST_F(ApproxTest_706, CustomFactory_706) {
    Catch::Approx approx = Catch::Approx::custom();
    std::string str = approx.toString();
    EXPECT_NE(str.find("Approx("), std::string::npos);
    EXPECT_NE(str.find("0"), std::string::npos);
}

// Test operator() creates new Approx with different value
TEST_F(ApproxTest_706, CallOperator_706) {
    Catch::Approx approx(1.0);
    Catch::Approx newApprox = approx(2.0);
    std::string str = newApprox.toString();
    EXPECT_NE(str.find("2"), std::string::npos);
}

// Test epsilon setter (chaining)
TEST_F(ApproxTest_706, EpsilonSetter_706) {
    Catch::Approx approx(1.0);
    Catch::Approx& ref = approx.epsilon(0.01);
    // Chaining should return reference to same object
    EXPECT_EQ(&ref, &approx);
}

// Test margin setter (chaining)
TEST_F(ApproxTest_706, MarginSetter_706) {
    Catch::Approx approx(1.0);
    Catch::Approx& ref = approx.margin(0.5);
    EXPECT_EQ(&ref, &approx);
}

// Test scale setter (chaining)
TEST_F(ApproxTest_706, ScaleSetter_706) {
    Catch::Approx approx(1.0);
    Catch::Approx& ref = approx.scale(2.0);
    EXPECT_EQ(&ref, &approx);
}

// Test chaining multiple setters
TEST_F(ApproxTest_706, ChainingSetters_706) {
    Catch::Approx approx(1.0);
    Catch::Approx& ref = approx.epsilon(0.01).margin(0.5).scale(1.0);
    EXPECT_EQ(&ref, &approx);
}

// Test with very large value
TEST_F(ApproxTest_706, LargeValue_706) {
    Catch::Approx approx(1e308);
    std::string str = approx.toString();
    EXPECT_NE(str.find("Approx("), std::string::npos);
}

// Test with very small value
TEST_F(ApproxTest_706, SmallValue_706) {
    Catch::Approx approx(1e-308);
    std::string str = approx.toString();
    EXPECT_NE(str.find("Approx("), std::string::npos);
}

// Test with float type (template constructor)
TEST_F(ApproxTest_706, ConstructWithFloat_706) {
    Catch::Approx approx(3.14f);
    std::string str = approx.toString();
    EXPECT_NE(str.find("Approx("), std::string::npos);
}

// Test operator() with int argument
TEST_F(ApproxTest_706, CallOperatorWithInt_706) {
    Catch::Approx approx(1.0);
    Catch::Approx newApprox = approx(42);
    std::string str = newApprox.toString();
    EXPECT_NE(str.find("42"), std::string::npos);
}

// Test epsilon with integer type
TEST_F(ApproxTest_706, EpsilonWithInt_706) {
    Catch::Approx approx(1.0);
    // Should not throw, epsilon of 0 is a valid edge
    Catch::Approx& ref = approx.epsilon(0.0);
    EXPECT_EQ(&ref, &approx);
}

// Test margin with zero
TEST_F(ApproxTest_706, MarginWithZero_706) {
    Catch::Approx approx(1.0);
    Catch::Approx& ref = approx.margin(0.0);
    EXPECT_EQ(&ref, &approx);
}

// Test that operator() preserves epsilon/margin settings
TEST_F(ApproxTest_706, CallOperatorPreservesSettings_706) {
    Catch::Approx approx(1.0);
    approx.epsilon(0.01).margin(0.5).scale(2.0);
    Catch::Approx newApprox = approx(10.0);
    // The new approx should have the value 10.0
    std::string str = newApprox.toString();
    EXPECT_NE(str.find("10"), std::string::npos);
}

// Test negation doesn't affect original
TEST_F(ApproxTest_706, NegationDoesNotAffectOriginal_706) {
    Catch::Approx approx(5.0);
    Catch::Approx negated = -approx;
    // Original should still be 5.0
    std::string originalStr = approx.toString();
    EXPECT_NE(originalStr.find("5"), std::string::npos);
    // Check it's not negative
    // The string should be "Approx( 5.0 )" not "Approx( -5.0 )"
    std::string negStr = negated.toString();
    EXPECT_NE(negStr.find("-5"), std::string::npos);
}

// Test with infinity
TEST_F(ApproxTest_706, InfinityValue_706) {
    double inf = std::numeric_limits<double>::infinity();
    Catch::Approx approx(inf);
    std::string str = approx.toString();
    EXPECT_NE(str.find("Approx("), std::string::npos);
}

// Test with NaN
TEST_F(ApproxTest_706, NaNValue_706) {
    double nan = std::numeric_limits<double>::quiet_NaN();
    Catch::Approx approx(nan);
    std::string str = approx.toString();
    EXPECT_NE(str.find("Approx("), std::string::npos);
}

// Test negative epsilon should throw or be rejected
TEST_F(ApproxTest_706, NegativeEpsilonThrows_706) {
    Catch::Approx approx(1.0);
    EXPECT_ANY_THROW(approx.epsilon(-0.01));
}

// Test epsilon greater than 1 should throw or be rejected  
TEST_F(ApproxTest_706, EpsilonGreaterThanOneThrows_706) {
    Catch::Approx approx(1.0);
    EXPECT_ANY_THROW(approx.epsilon(1.5));
}

// Test negative margin should throw or be rejected
TEST_F(ApproxTest_706, NegativeMarginThrows_706) {
    Catch::Approx approx(1.0);
    EXPECT_ANY_THROW(approx.margin(-1.0));
}

// Test multiple toString calls return consistent results
TEST_F(ApproxTest_706, ToStringConsistency_706) {
    Catch::Approx approx(3.14);
    std::string str1 = approx.toString();
    std::string str2 = approx.toString();
    EXPECT_EQ(str1, str2);
}

// Test equality comparison through operator== (if available via friend)
TEST_F(ApproxTest_706, EqualityWithExactValue_706) {
    Catch::Approx approx(1.0);
    EXPECT_TRUE(approx == 1.0);
}

// Test equality with value within default epsilon
TEST_F(ApproxTest_706, EqualityWithinDefaultEpsilon_706) {
    Catch::Approx approx(1.0);
    // Default epsilon is float::epsilon * 100 ≈ 0.0119209...
    // For value 1.0, the tolerance should be approximately 1.0 * epsilon
    double withinEps = 1.0 + 0.001;
    EXPECT_TRUE(approx == withinEps);
}

// Test inequality with value far from approx
TEST_F(ApproxTest_706, InequalityWithDistantValue_706) {
    Catch::Approx approx(1.0);
    EXPECT_FALSE(approx == 2.0);
}

// Test custom margin affects comparison
TEST_F(ApproxTest_706, CustomMarginComparison_706) {
    Catch::Approx approx(1.0);
    approx.margin(0.5);
    EXPECT_TRUE(approx == 1.4);
    EXPECT_FALSE(approx == 2.0);
}

// Test custom epsilon affects comparison
TEST_F(ApproxTest_706, CustomEpsilonComparison_706) {
    Catch::Approx approx(100.0);
    approx.epsilon(0.1);  // 10% tolerance
    EXPECT_TRUE(approx == 105.0);
    EXPECT_FALSE(approx == 200.0);
}
