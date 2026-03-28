#include <gtest/gtest.h>

#include "exiv2/value.hpp"



using namespace Exiv2;



class ValueTypeTest_137 : public ::testing::Test {

protected:

    ValueType<int> intValueType;

};



TEST_F(ValueTypeTest_137, CloneReturnsNonNullPointer_137) {

    auto clone = intValueType.clone();

    EXPECT_NE(clone.get(), nullptr);

}



TEST_F(ValueTypeTest_137, CountReturnsZeroForDefaultConstructed_137) {

    EXPECT_EQ(intValueType.count(), 0u);

}



TEST_F(ValueTypeTest_137, SizeDataAreaReturnsZeroForDefaultConstructed_137) {

    EXPECT_EQ(intValueType.sizeDataArea(), 0u);

}



TEST_F(ValueTypeTest_137, DataAreaReturnsEmptyBufferForDefaultConstructed_137) {

    auto dataArea = intValueType.dataArea();

    EXPECT_TRUE(dataArea.pData_ == nullptr || dataArea.size_ == 0);

}



TEST_F(ValueTypeTest_137, ToStringReturnsEmptyStringForDefaultConstructed_137) {

    EXPECT_EQ(intValueType.toString(0), "");

}



TEST_F(ValueTypeTest_137, ToInt64ThrowsForInvalidIndex_137) {

    EXPECT_THROW(intValueType.toInt64(0), std::out_of_range);

}



TEST_F(ValueTypeTest_137, ToUint32ThrowsForInvalidIndex_137) {

    EXPECT_THROW(intValueType.toUint32(0), std::out_of_range);

}



TEST_F(ValueTypeTest_137, ToFloatThrowsForInvalidIndex_137) {

    EXPECT_THROW(intValueType.toFloat(0), std::out_of_range);

}



TEST_F(ValueTypeTest_137, ToRationalThrowsForInvalidIndex_137) {

    EXPECT_THROW(intValueType.toRational(0), std::out_of_range);

}
