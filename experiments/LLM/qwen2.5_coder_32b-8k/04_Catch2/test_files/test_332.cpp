#include <gtest/gtest.h>

#include "catch2/internal/catch_random_integer_helpers.hpp"



using namespace Catch::Detail;



// Test Fixture for ExtendedMult function

class ExtendedMultTest_332 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code, if needed

    }



    void TearDown() override {

        // Teardown code, if needed

    }

};



// Normal operation test cases

TEST_F(ExtendedMultTest_332, MultiplySmallNumbers_332) {

    auto result = extendedMult(10, 5);

    EXPECT_EQ(result.high, 0);

    EXPECT_EQ(result.low, 50);

}



TEST_F(ExtendedMultTest_332, MultiplyLargeNumbers_332) {

    auto result = extendedMult(UINT64_MAX, 2);

    EXPECT_EQ(result.high, 1);

    EXPECT_EQ(result.low, 0);

}



// Boundary conditions test cases

TEST_F(ExtendedMultTest_332, MultiplyByZero_332) {

    auto result = extendedMult(UINT64_MAX, 0);

    EXPECT_EQ(result.high, 0);

    EXPECT_EQ(result.low, 0);

}



TEST_F(ExtendedMultTest_332, MultiplyMaxWithOne_332) {

    auto result = extendedMult(UINT64_MAX, 1);

    EXPECT_EQ(result.high, 0);

    EXPECT_EQ(result.low, UINT64_MAX);

}



// Exceptional or error cases test cases

// Since the function does not throw exceptions and handles overflow internally,

// there are no exceptional or error cases to test for this specific function.



// Verification of external interactions (not applicable for this function as it has no dependencies)

```


