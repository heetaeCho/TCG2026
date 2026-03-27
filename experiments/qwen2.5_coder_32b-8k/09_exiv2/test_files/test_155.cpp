#include <gtest/gtest.h>

#include "exiv2/value.hpp"



using namespace Exiv2;



class ValueTypeTest_155 : public ::testing::Test {

protected:

    ValueType<int> value_type;

};



TEST_F(ValueTypeTest_155, ToInt64_NormalOperation_155) {

    ValueList values = {10, 20, 30};

    value_type.value_ = values;

    EXPECT_EQ(value_type.toInt64(0), 10);

    EXPECT_EQ(value_type.toInt64(1), 20);

    EXPECT_EQ(value_type.toInt64(2), 30);

}



TEST_F(ValueTypeTest_155, ToInt64_BoundaryConditions_155) {

    ValueList values = {std::numeric_limits<int>::min(), std::numeric_limits<int>::max()};

    value_type.value_ = values;

    EXPECT_EQ(value_type.toInt64(0), static_cast<int64_t>(std::numeric_limits<int>::min()));

    EXPECT_EQ(value_type.toInt64(1), static_cast<int64_t>(std::numeric_limits<int>::max()));

}



TEST_F(ValueTypeTest_155, ToInt64_OutOfBounds_155) {

    ValueList values = {10, 20, 30};

    value_type.value_ = values;

    EXPECT_THROW(value_type.toInt64(3), std::out_of_range);

}



TEST_F(ValueTypeTest_155, ToInt64_EmptyValueList_155) {

    ValueList values = {};

    value_type.value_ = values;

    EXPECT_THROW(value_type.toInt64(0), std::out_of_range);

}
