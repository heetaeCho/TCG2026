#include <gtest/gtest.h>

#include "exiv2/value.hpp"



using namespace Exiv2;



class ValueTypeTest_156 : public ::testing::Test {

protected:

    ValueType<int> value_type;

};



TEST_F(ValueTypeTest_156, ToUint32_NormalOperation_156) {

    ValueList values = {42};

    ValueType<int> vt(values, 0, littleEndian, intType);

    EXPECT_EQ(vt.toUint32(0), 42U);

}



TEST_F(ValueTypeTest_156, ToUint32_BoundaryCondition_EmptyValueList_156) {

    ValueType<int> vt;

    EXPECT_THROW(vt.toUint32(0), std::out_of_range);

}



TEST_F(ValueTypeTest_156, ToUint32_BoundaryCondition_OutOfRangeIndex_156) {

    ValueList values = {42};

    ValueType<int> vt(values, 0, littleEndian, intType);

    EXPECT_THROW(vt.toUint32(1), std::out_of_range);

}



TEST_F(ValueTypeTest_156, ToUint32_ExceptionalCase_NegativeValue_156) {

    ValueList values = {-42};

    ValueType<int> vt(values, 0, littleEndian, intType);

    EXPECT_EQ(vt.toUint32(0), static_cast<uint32_t>(-42));

}



TEST_F(ValueTypeTest_156, ToUint32_ExceptionalCase_MaxInt_156) {

    ValueList values = {std::numeric_limits<int>::max()};

    ValueType<int> vt(values, 0, littleEndian, intType);

    EXPECT_EQ(vt.toUint32(0), static_cast<uint32_t>(std::numeric_limits<int>::max()));

}



TEST_F(ValueTypeTest_156, ToUint32_ExceptionalCase_MinInt_156) {

    ValueList values = {std::numeric_limits<int>::min()};

    ValueType<int> vt(values, 0, littleEndian, intType);

    EXPECT_EQ(vt.toUint32(0), static_cast<uint32_t>(std::numeric_limits<int>::min()));

}



TEST_F(ValueTypeTest_156, ToUint32_VerificationOfExternalInteractions_156) {

    ValueList values = {42};

    ValueType<int> vt(values, 0, littleEndian, intType);

    EXPECT_CALL(vt, toUint32(0)).WillOnce(testing::Return(42U));

    EXPECT_EQ(vt.toUint32(0), 42U);

}
