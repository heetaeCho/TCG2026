#include <gtest/gtest.h>

#include <exiv2/value.hpp>

#include <sstream>



using namespace Exiv2;



TEST_F(ValueTypeTest_153, Constructor_Default_153) {

    ValueType<int> value;

    EXPECT_EQ(value.count(), 0);

}



TEST_F(ValueTypeTest_153, Constructor_Value_153) {

    ValueType<int> value(42, 0); // Assuming TypeId is irrelevant for count check

    EXPECT_EQ(value.count(), 1);

}



TEST_F(ValueTypeTest_153, Constructor_Copy_153) {

    ValueType<int> original(42, 0);

    ValueType<int> copy(original);

    EXPECT_EQ(copy.count(), 1);

}



TEST_F(ValueTypeTest_153, OperatorAssignment_153) {

    ValueType<int> value1(42, 0);

    ValueType<int> value2;

    value2 = value1;

    EXPECT_EQ(value2.count(), 1);

}



TEST_F(ValueTypeTest_153, Count_Empty_153) {

    ValueType<int> value;

    EXPECT_EQ(value.count(), 0);

}



TEST_F(ValueTypeTest_153, Count_SingleElement_153) {

    ValueType<int> value(42, 0);

    EXPECT_EQ(value.count(), 1);

}



TEST_F(ValueTypeTest_153, Write_Empty_153) {

    ValueType<int> value;

    std::ostringstream os;

    value.write(os);

    EXPECT_EQ(os.str(), "");

}



TEST_F(ValueTypeTest_153, Write_SingleElement_153) {

    ValueType<int> value(42, 0);

    std::ostringstream os;

    value.write(os);

    EXPECT_EQ(os.str(), "42");

}



TEST_F(ValueTypeTest_153, Write_MultipleElements_153) {

    ValueType<double> value;

    value.value_.push_back(1.1);

    value.value_.push_back(2.2);

    std::ostringstream os;

    value.write(os);

    EXPECT_EQ(os.str(), "1.1 2.2");

}



TEST_F(ValueTypeTest_153, ToString_OutOfBounds_153) {

    ValueType<int> value(42, 0);

    EXPECT_THROW(value.toString(1), std::out_of_range);

}



TEST_F(ValueTypeTest_153, ToInt64_OutOfBounds_153) {

    ValueType<int> value(42, 0);

    EXPECT_THROW(value.toInt64(1), std::out_of_range);

}



TEST_F(ValueTypeTest_153, ToUint32_OutOfBounds_153) {

    ValueType<int> value(42, 0);

    EXPECT_THROW(value.toUint32(1), std::out_of_range);

}



TEST_F(ValueTypeTest_153, ToFloat_OutOfBounds_153) {

    ValueType<int> value(42, 0);

    EXPECT_THROW(value.toFloat(1), std::out_of_range);

}



TEST_F(ValueTypeTest_153, ToRational_OutOfBounds_153) {

    ValueType<int> value(42, 0);

    EXPECT_THROW(value.toRational(1), std::out_of_range);

}
