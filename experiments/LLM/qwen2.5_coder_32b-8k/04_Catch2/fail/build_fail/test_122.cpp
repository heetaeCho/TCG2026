#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_decomposer.hpp"



using namespace Catch;



class BinaryExprTest_122 : public ::testing::Test {

protected:

    BinaryExpr binary_expr;

};



// Normal operation tests are not applicable here as the operator> is templated and will always static_assert.

// However, we can test boundary conditions by attempting to use different types.



TEST_F(BinaryExprTest_122, StaticAssertOnChainedComparisonInt_122) {

    EXPECT_DEATH({

        auto result = (binary_expr > 5) > 3;

    }, "chained comparisons are not supported inside assertions");

}



TEST_F(BinaryExprTest_122, StaticAssertOnChainedComparisonDouble_122) {

    EXPECT_DEATH({

        auto result = (binary_expr > 5.0) > 3.0;

    }, "chained comparisons are not supported inside assertions");

}



TEST_F(BinaryExprTest_122, StaticAssertOnChainedComparisonString_122) {

    EXPECT_DEATH({

        auto result = (binary_expr > std::string("test")) > std::string("example");

    }, "chained comparisons are not supported inside assertions");

}



// Boundary conditions and exceptional cases are tested by the above tests.

// No further external interactions need to be verified as there are no mocks involved.


