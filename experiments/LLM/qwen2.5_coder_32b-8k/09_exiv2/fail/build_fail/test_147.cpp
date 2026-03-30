#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/value.hpp"



using namespace Exiv2;



// Mocking external collaborators if needed (none in this case)



class ValueTypeTest : public ::testing::Test {

protected:

    ValueType<int> intValue;

    ValueType<double> doubleValue;

};



TEST_F(ValueTypeTest_147, CopyConstructorCreatesEqualObject_147) {

    ValueType<int> original(42, TypeId::int32);

    ValueType<int> copy = original;

    EXPECT_EQ(original.toInt64(), copy.toInt64());

}



TEST_F(ValueTypeTest_147, AssignmentOperatorAssignsValue_147) {

    ValueType<int> original(42, TypeId::int32);

    ValueType<int> target;

    target = original;

    EXPECT_EQ(original.toInt64(), target.toInt64());

}



TEST_F(ValueTypeTest_147, ReadFromBufferUpdatesValue_147) {

    byte buffer[] = { 0x2A };

    intValue.read(buffer, sizeof(buffer), ByteOrder::big);

    EXPECT_EQ(intValue.toInt64(), 0x2A);

}



TEST_F(ValueTypeTest_147, SetDataAreaSetsCorrectly_147) {

    byte data[] = { 0x1, 0x2, 0x3 };

    doubleValue.setDataArea(data, sizeof(data));

    EXPECT_EQ(doubleValue.sizeDataArea(), sizeof(data));

}



TEST_F(ValueTypeTest_147, CountReturnsNumberOfElements_147) {

    intValue.value_.push_back(1);

    intValue.value_.push_back(2);

    EXPECT_EQ(intValue.count(), 2);

}



TEST_F(ValueTypeTest_147, SizeReturnsSizeInBytes_147) {

    ValueType<Rational> rationalValue(Rational(1, 2), TypeId::rational64);

    EXPECT_EQ(rationalValue.size(), sizeof(Rational));

}



TEST_F(ValueTypeTest_147, ToStringConvertsToCorrectString_147) {

    doubleValue = ValueType<double>(3.14, TypeId::float64);

    EXPECT_EQ(doubleValue.toString(0), "3.14");

}



TEST_F(ValueTypeTest_147, ToInt64ConvertsCorrectly_147) {

    intValue = ValueType<int>(255, TypeId::int32);

    EXPECT_EQ(intValue.toInt64(), 255);

}



TEST_F(ValueTypeTest_147, ToUint32ConvertsCorrectly_147) {

    intValue = ValueType<int>(65535, TypeId::int32);

    EXPECT_EQ(intValue.toUint32(), 65535U);

}



TEST_F(ValueTypeTest_147, ToFloatConvertsCorrectly_147) {

    doubleValue = ValueType<double>(3.14, TypeId::float64);

    EXPECT_FLOAT_EQ(doubleValue.toFloat(0), 3.14f);

}



TEST_F(ValueTypeTest_147, ToRationalConvertsCorrectly_147) {

    Rational testRational(3, 2);

    ValueType<Rational> rationalValue(testRational, TypeId::rational64);

    EXPECT_EQ(rationalValue.toRational(0), testRational);

}



TEST_F(ValueTypeTest_147, DataAreaReturnsCorrectBuffer_147) {

    byte data[] = { 0x1, 0x2, 0x3 };

    doubleValue.setDataArea(data, sizeof(data));

    EXPECT_EQ(memcmp(doubleValue.dataArea().pData_, data, sizeof(data)), 0);

}



TEST_F(ValueTypeTest_147, CopyMethodCopiesDataCorrectly_147) {

    byte originalData[] = { 0x1, 0x2, 0x3 };

    doubleValue.setDataArea(originalData, sizeof(originalData));

    byte copiedData[sizeof(originalData)];

    doubleValue.copy(copiedData, ByteOrder::big);

    EXPECT_EQ(memcmp(copiedData, originalData, sizeof(originalData)), 0);

}



TEST_F(ValueTypeTest_147, WriteMethodOutputsCorrectly_147) {

    std::ostringstream oss;

    intValue = ValueType<int>(42, TypeId::int32);

    intValue.write(oss);

    EXPECT_EQ(oss.str(), "42");

}
