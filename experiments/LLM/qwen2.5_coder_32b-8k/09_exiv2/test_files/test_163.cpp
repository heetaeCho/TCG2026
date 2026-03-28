#include <gtest/gtest.h>

#include "exiv2/value.hpp"



using namespace Exiv2;



class ValueTypeURationalTest_163 : public ::testing::Test {

protected:

    ValueType<URational> value_type;

};



TEST_F(ValueTypeURationalTest_163, ToInt64NormalOperation_163) {

    URational urational(1000000, 1);

    value_type.value_.push_back(urational);

    EXPECT_EQ(value_type.toInt64(0), 1000000);

}



TEST_F(ValueTypeURationalTest_163, ToInt64BoundaryConditionZeroNumerator_163) {

    URational urational(0, 1);

    value_type.value_.push_back(urational);

    EXPECT_EQ(value_type.toInt64(0), 0);

}



TEST_F(ValueTypeURationalTest_163, ToInt64BoundaryConditionLargeNumerator_163) {

    URational urational(std::numeric_limits<int64_t>::max(), 1);

    value_type.value_.push_back(urational);

    EXPECT_EQ(value_type.toInt64(0), std::numeric_limits<int64_t>::max());

}



TEST_F(ValueTypeURationalTest_163, ToInt64BoundaryConditionLargeDenominator_163) {

    URational urational(std::numeric_limits<int64_t>::max(), 2);

    value_type.value_.push_back(urational);

    EXPECT_EQ(value_type.toInt64(0), std::numeric_limits<int64_t>::max() / 2);

}



TEST_F(ValueTypeURationalTest_163, ToInt64BoundaryConditionZeroDenominator_163) {

    URational urational(1, 0);

    value_type.value_.push_back(urational);

    EXPECT_THROW(value_type.toInt64(0), std::overflow_error); // Assuming division by zero throws an exception

}



TEST_F(ValueTypeURationalTest_163, ToInt64IndexOutOfBounds_163) {

    URational urational(1000000, 1);

    value_type.value_.push_back(urational);

    EXPECT_THROW(value_type.toInt64(1), std::out_of_range); // Assuming out of bounds access throws an exception

}



TEST_F(ValueTypeURationalTest_163, ToInt64NegativeNumerator_163) {

    URational urational(-1000000, 1);

    value_type.value_.push_back(urational);

    EXPECT_EQ(value_type.toInt64(0), -1000000);

}



TEST_F(ValueTypeURationalTest_163, ToInt64NegativeDenominator_163) {

    URational urational(1000000, -1);

    value_type.value_.push_back(urational);

    EXPECT_EQ(value_type.toInt64(0), -1000000);

}



TEST_F(ValueTypeURationalTest_163, ToInt64NegativeBoth_163) {

    URational urational(-1000000, -1);

    value_type.value_.push_back(urational);

    EXPECT_EQ(value_type.toInt64(0), 1000000);

}
