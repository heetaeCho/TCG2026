#include <gtest/gtest.h>



// Assuming Function class is included via header file as mentioned.

#include "Function.h"



class FunctionTest_354 : public ::testing::Test {

protected:

    // Setup and teardown can be added here if needed.

    Function* func1;

    Function* func2;



    virtual void SetUp() {

        func1 = new Function();

        func2 = new Function();

    }



    virtual void TearDown() {

        delete func1;

        delete func2;

    }

};



// Test to verify normal operation where both functions are the same.

TEST_F(FunctionTest_354, HasDifferentResultSet_SameFunction_354) {

    EXPECT_FALSE(func1->hasDifferentResultSet(func1));

}



// Test to verify normal operation where different functions are compared.

TEST_F(FunctionTest_354, HasDifferentResultSet_DifferentFunctions_354) {

    EXPECT_FALSE(func1->hasDifferentResultSet(func2));

}



// Boundary condition test with nullptr as argument.

TEST_F(FunctionTest_354, HasDifferentResultSet_NullptrArgument_354) {

    EXPECT_FALSE(func1->hasDifferentResultSet(nullptr));

}
