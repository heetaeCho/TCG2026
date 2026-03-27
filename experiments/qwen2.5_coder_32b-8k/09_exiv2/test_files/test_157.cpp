#include <gtest/gtest.h>

#include "exiv2/value.hpp"

#include <cstdint>



using namespace Exiv2;



class ValueTypeDoubleTest_157 : public ::testing::Test {

protected:

    ValueType<double> value_type_double_;



    void SetUp() override {

        // Initialize with a sample double value for testing

        value_type_double_.value_.push_back(3.14);

    }

};



TEST_F(ValueTypeDoubleTest_157, ToInt64_NormalOperation_157) {

    int64_t result = value_type_double_.toInt64(0);

    EXPECT_EQ(result, 3);

}



TEST_F(ValueTypeDoubleTest_157, ToInt64_BoundaryCondition_ZeroIndex_157) {

    value_type_double_.value_.push_back(0.0);

    int64_t result = value_type_double_.toInt64(1);

    EXPECT_EQ(result, 0);

}



TEST_F(ValueTypeDoubleTest_157, ToInt64_BoundaryCondition_MaxIndex_157) {

    size_t index = value_type_double_.count() - 1;

    int64_t result = value_type_double_.toInt64(index);

    EXPECT_EQ(result, static_cast<int64_t>(value_type_double_.value_[index]));

}



TEST_F(ValueTypeDoubleTest_157, ToInt64_ErrorCase_OutOfBoundsIndex_157) {

    size_t out_of_bounds_index = value_type_double_.count();

    int64_t result = value_type_double_.toInt64(out_of_bounds_index);

    EXPECT_EQ(result, 0); // Assuming out-of-bounds returns 0 as a safe default

}



TEST_F(ValueTypeDoubleTest_157, ToInt64_ErrorCase_NegativeIndex_157) {

    int64_t result = value_type_double_.toInt64(-1);

    EXPECT_EQ(result, 0); // Assuming negative index returns 0 as a safe default

}
