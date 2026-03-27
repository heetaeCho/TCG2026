#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/types.hpp"



using namespace Exiv2;



// Test fixture for testing toStringHelper function

class ToStringHelperTest_32 : public ::testing::Test {

protected:

    // You can set up any common state here if needed

};



TEST_F(ToStringHelperTest_32, NormalOperationWithInteger_32) {

    int testValue = 123;

    std::string result = toStringHelper(testValue, std::true_type());

    EXPECT_EQ(result, "123");

}



TEST_F(ToStringHelperTest_32, NormalOperationWithLong_32) {

    long testValue = 4567890L;

    std::string result = toStringHelper(testValue, std::true_type());

    EXPECT_EQ(result, "4567890");

}



TEST_F(ToStringHelperTest_32, NormalOperationWithUnsignedInteger_32) {

    unsigned int testValue = 12345U;

    std::string result = toStringHelper(testValue, std::true_type());

    EXPECT_EQ(result, "12345");

}



TEST_F(ToStringHelperTest_32, BoundaryConditionZero_32) {

    int testValue = 0;

    std::string result = toStringHelper(testValue, std::true_type());

    EXPECT_EQ(result, "0");

}



TEST_F(ToStringHelperTest_32, BoundaryConditionNegativeInteger_32) {

    int testValue = -123;

    std::string result = toStringHelper(testValue, std::true_type());

    EXPECT_EQ(result, "-123");

}
