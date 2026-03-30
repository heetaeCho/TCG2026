#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <Catch2/internal/catch_decomposer.hpp>

#include <sstream>



using namespace Catch;

using ::testing::HasSubstr;



TEST(formatReconstructedExpressionTest_540, NormalOperationShortStrings_540) {

    std::ostringstream os;

    formatReconstructedExpression(os, "a", "+", "b");

    EXPECT_EQ(os.str(), "a + b");

}



TEST(formatReconstructedExpressionTest_540, NormalOperationLongStrings_540) {

    std::ostringstream os;

    formatReconstructedExpression(os, "this_is_a_long_string_that_exceeds_the_limit", "+", "another_long_string");

    EXPECT_EQ(os.str(), "this_is_a_long_string_that_exceeds_the_limit\n+\nanother_long_string");

}



TEST(formatReconstructedExpressionTest_540, StringsContainNewline_540) {

    std::ostringstream os;

    formatReconstructedExpression(os, "a\nb", "+", "c");

    EXPECT_EQ(os.str(), "a\nb\n+\nc");

}



TEST(formatReconstructedExpressionTest_540, EmptyLeftString_540) {

    std::ostringstream os;

    formatReconstructedExpression(os, "", "+", "rhs");

    EXPECT_EQ(os.str(), "\n+\nrhs");

}



TEST(formatReconstructedExpressionTest_540, EmptyRightString_540) {

    std::ostringstream os;

    formatReconstructedExpression(os, "lhs", "+", "");

    EXPECT_EQ(os.str(), "lhs\n+\n");

}



TEST(formatReconstructedExpressionTest_540, BothStringsEmpty_540) {

    std::ostringstream os;

    formatReconstructedExpression(os, "", "+", "");

    EXPECT_EQ(os.str(), "\n+\n");

}
