#include <gtest/gtest.h>

#include <exiv2/value.hpp>



using namespace Exiv2;



class ValueTypeTest_154 : public ::testing::Test {

protected:

    ValueType<int> value_type;

};



TEST_F(ValueTypeTest_154, ToString_NormalOperation_154) {

    // Assuming the value_ vector is initialized with some data

    value_type.value_.push_back(42);

    EXPECT_EQ(value_type.toString(0), "42");

}



TEST_F(ValueTypeTest_154, ToString_BoundaryCondition_EmptyVector_154) {

    EXPECT_THROW(value_type.toString(0), std::out_of_range);

}



TEST_F(ValueTypeTest_154, ToString_BoundaryCondition_OutOfRange_154) {

    value_type.value_.push_back(42);

    EXPECT_THROW(value_type.toString(1), std::out_of_range);

}
