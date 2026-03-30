#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/internal/catch_decomposer.hpp"



using namespace Catch;

using namespace ::testing;



// Since BinaryExpr does not have any public member variables and the operator== is templated,

// we will focus on testing the behavior related to static assertions.



class BinaryExprTest_120 : public ::testing::Test {

protected:

    BinaryExpr expr;

};



TEST_F(BinaryExprTest_120, ChainedComparison_StaticAssertionFailure_120) {

    // This test checks that chained comparisons inside assertions are not supported.

    EXPECT_DEATH(

        {

            int a = 5, b = 3, c = 8;

            BinaryExpr expr;

            (void)(expr == a == b);

        },

        "chained comparisons are not supported inside assertions"

    );

}



TEST_F(BinaryExprTest_120, ValidComparison_NoStaticAssertionFailure_120) {

    // This test checks that valid single comparison does not trigger static assertion failure.

    int a = 5;

    BinaryExpr expr;

    (void)(expr == a);

    SUCCEED();

}
