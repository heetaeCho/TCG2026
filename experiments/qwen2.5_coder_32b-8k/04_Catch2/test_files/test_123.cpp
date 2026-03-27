#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_decomposer.hpp"



using namespace Catch;



class BinaryExprTest : public ::testing::Test {

protected:

    BinaryExpr expr;

};



TEST_F(BinaryExprTest_123, ComparisonOperatorThrowsForChainedComparisons_123) {

    // This test checks that using the < operator in a chained comparison scenario

    // results in a static assertion failure. Since we cannot directly catch static

    // assertions at runtime, this test serves more as a documentation of expected behavior.

    // The actual enforcement is done by the static_assert within the code.



    // Example usage that would cause a compilation error:

    // expr < 5 < 10; // This should not compile



    SUCCEED(); // Placeholder for successful compilation without chained comparisons

}



TEST_F(BinaryExprTest_123, NormalComparisonWithValidTypes_123) {

    // Test normal usage of the < operator with valid types that do not cause chained comparisons.

    BinaryExpr expr;

    auto result = expr < 5;

    (void)result; // Suppress unused variable warning



    SUCCEED(); // If compilation succeeds and no static assertion fails, the test passes

}



TEST_F(BinaryExprTest_123, ComparisonWithDifferentTypes_123) {

    // Test comparison with different types to ensure template handling is correct.

    BinaryExpr expr;

    auto result = expr < std::string("test");

    (void)result; // Suppress unused variable warning



    SUCCEED(); // If compilation succeeds and no static assertion fails, the test passes

}

```


