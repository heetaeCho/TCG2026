#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/exiv2/src/safe_op.hpp"

#include <stdexcept>



using namespace Safe;



class SafeOpTest_66 : public ::testing::Test {

protected:

    // Additional setup can be done here if needed

};



TEST_F(SafeOpTest_66, AddNormalOperation_66) {

    EXPECT_EQ(add(1, 2), 3);

    EXPECT_EQ(add(-1, -2), -3);

    EXPECT_EQ(add(-1, 1), 0);

}



TEST_F(SafeOpTest_66, AddBoundaryConditions_66) {

    // Test with maximum and minimum values for int

    EXPECT_EQ(add(std::numeric_limits<int>::max(), 0), std::numeric_limits<int>::max());

    EXPECT_EQ(add(0, std::numeric_limits<int>::min()), std::numeric_limits<int>::min());



    // Edge case: adding zero to any number should not cause overflow

    EXPECT_NO_THROW(add(std::numeric_limits<int>::max(), 0));

    EXPECT_NO_THROW(add(std::numeric_limits<int>::min(), 0));

}



TEST_F(SafeOpTest_66, AddOverflowIntMax_66) {

    // Test for int overflow

    EXPECT_THROW(add(std::numeric_limits<int>::max(), 1), std::overflow_error);

}



TEST_F(SafeOpTest_66, AddOverflowIntMin_66) {

    // Test for int underflow

    EXPECT_THROW(add(std::numeric_limits<int>::min(), -1), std::overflow_error);

}



TEST_F(SafeOpTest_66, AddUnsignedNormalOperation_66) {

    unsigned int a = 1;

    unsigned int b = 2;

    EXPECT_EQ(add(a, b), 3u);



    a = 0;

    b = 0;

    EXPECT_EQ(add(a, b), 0u);

}



TEST_F(SafeOpTest_66, AddUnsignedBoundaryConditions_66) {

    // Test with maximum value for unsigned int

    EXPECT_EQ(add(std::numeric_limits<unsigned int>::max(), 0u), std::numeric_limits<unsigned int>::max());

}



TEST_F(SafeOpTest_66, AddUnsignedOverflow_66) {

    // Test for unsigned int overflow

    EXPECT_THROW(add(std::numeric_limits<unsigned int>::max(), 1u), std::overflow_error);

}
