#include "catch2/catch_assertion_result.hpp"
#include "catch2/internal/catch_lazy_expr.hpp"
#include "catch2/internal/catch_reusable_string_stream.hpp"

#include <gtest/gtest.h>
#include <string>

using namespace Catch;

// We need to know about ResultWas - it's typically an enum in Catch2
// Including the necessary header
#include "catch2/interfaces/catch_interfaces_capture.hpp"

class AssertionResultDataTest_290 : public ::testing::Test {
protected:
    // Helper to create a LazyExpression with no transient expression (operator bool returns false)
    LazyExpression createEmptyLazyExpression() {
        return LazyExpression(false);
    }
};

// Test that reconstructExpression returns empty string when both reconstructedExpression 
// is empty and lazyExpression is falsy (no transient expression)
TEST_F(AssertionResultDataTest_290, ReconstructExpressionReturnsEmptyWhenBothEmpty_290) {
    LazyExpression lazy(false);  // m_transientExpression is nullptr, operator bool() is false
    AssertionResultData data(ResultWas::Unknown, lazy);
    
    // reconstructedExpression is empty by default, lazyExpression has no transient expr
    std::string result = data.reconstructExpression();
    EXPECT_TRUE(result.empty());
}

// Test that reconstructExpression returns the pre-set reconstructedExpression if it's not empty
TEST_F(AssertionResultDataTest_290, ReconstructExpressionReturnsPresetExpression_290) {
    LazyExpression lazy(false);
    AssertionResultData data(ResultWas::Unknown, lazy);
    
    // Directly set the reconstructedExpression member (it's public)
    data.reconstructedExpression = "x == 42";
    
    std::string result = data.reconstructExpression();
    EXPECT_EQ(result, "x == 42");
}

// Test that reconstructExpression returns the same value on repeated calls when preset
TEST_F(AssertionResultDataTest_290, ReconstructExpressionIsIdempotentWhenPreset_290) {
    LazyExpression lazy(false);
    AssertionResultData data(ResultWas::Unknown, lazy);
    data.reconstructedExpression = "a != b";
    
    std::string result1 = data.reconstructExpression();
    std::string result2 = data.reconstructExpression();
    EXPECT_EQ(result1, result2);
    EXPECT_EQ(result1, "a != b");
}

// Test that when reconstructedExpression is empty and lazyExpression is falsy,
// calling reconstructExpression multiple times still returns empty
TEST_F(AssertionResultDataTest_290, ReconstructExpressionStaysEmptyWithNoLazy_290) {
    LazyExpression lazy(false);
    AssertionResultData data(ResultWas::Unknown, lazy);
    
    std::string result1 = data.reconstructExpression();
    std::string result2 = data.reconstructExpression();
    EXPECT_TRUE(result1.empty());
    EXPECT_TRUE(result2.empty());
}

// Test with negated LazyExpression that has no transient expression
TEST_F(AssertionResultDataTest_290, ReconstructExpressionWithNegatedEmptyLazy_290) {
    LazyExpression lazy(true);  // negated but still no transient expression
    AssertionResultData data(ResultWas::Ok, lazy);
    
    std::string result = data.reconstructExpression();
    EXPECT_TRUE(result.empty());
}

// Test that message field can be set and doesn't affect reconstructExpression
TEST_F(AssertionResultDataTest_290, MessageDoesNotAffectReconstructExpression_290) {
    LazyExpression lazy(false);
    AssertionResultData data(ResultWas::ExpressionFailed, lazy);
    data.message = "Some failure message";
    
    std::string result = data.reconstructExpression();
    EXPECT_TRUE(result.empty());
    EXPECT_NE(result, data.message);
}

// Test that resultType is properly stored (accessible via public member)
TEST_F(AssertionResultDataTest_290, ResultTypeIsStoredCorrectly_290) {
    LazyExpression lazy(false);
    AssertionResultData data(ResultWas::Ok, lazy);
    
    EXPECT_EQ(data.resultType, ResultWas::Ok);
}

// Test with ExpressionFailed result type
TEST_F(AssertionResultDataTest_290, ResultTypeExpressionFailed_290) {
    LazyExpression lazy(false);
    AssertionResultData data(ResultWas::ExpressionFailed, lazy);
    
    EXPECT_EQ(data.resultType, ResultWas::ExpressionFailed);
}

// Test that setting reconstructedExpression after first call still returns the set value
TEST_F(AssertionResultDataTest_290, ReconstructExpressionAfterSettingValue_290) {
    LazyExpression lazy(false);
    AssertionResultData data(ResultWas::Unknown, lazy);
    
    // First call returns empty
    std::string result1 = data.reconstructExpression();
    EXPECT_TRUE(result1.empty());
    
    // Set value after first call
    data.reconstructedExpression = "new_expression";
    std::string result2 = data.reconstructExpression();
    EXPECT_EQ(result2, "new_expression");
}

// Test with various result types that the constructor properly stores them
TEST_F(AssertionResultDataTest_290, VariousResultTypes_290) {
    LazyExpression lazy(false);
    
    {
        AssertionResultData data(ResultWas::DidntThrowException, lazy);
        EXPECT_EQ(data.resultType, ResultWas::DidntThrowException);
    }
    {
        AssertionResultData data(ResultWas::ThrewException, lazy);
        EXPECT_EQ(data.resultType, ResultWas::ThrewException);
    }
}

// Test that an empty reconstructedExpression string with whitespace is not considered empty
TEST_F(AssertionResultDataTest_290, ReconstructExpressionWithWhitespace_290) {
    LazyExpression lazy(false);
    AssertionResultData data(ResultWas::Unknown, lazy);
    data.reconstructedExpression = " ";
    
    std::string result = data.reconstructExpression();
    EXPECT_EQ(result, " ");
    EXPECT_FALSE(result.empty());
}
