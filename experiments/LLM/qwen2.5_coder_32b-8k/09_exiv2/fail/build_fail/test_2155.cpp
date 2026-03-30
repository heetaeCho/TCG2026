#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/value.hpp"



using namespace Exiv2;

using namespace testing;



// Test fixture for ValueType<int>

class ValueTypeIntTest_2155 : public ::testing::Test {

protected:

    ValueType<int> valueInt;



    ValueTypeIntTest_2155() : valueInt(42, TypeId::int32) {}

};



TEST_F(ValueTypeIntTest_2155, ConstructorInitialization_2155) {

    EXPECT_EQ(valueInt.typeId(), TypeId::int32);

    EXPECT_EQ(valueInt.count(), 1u);

}



TEST_F(ValueTypeIntTest_2155, ToStringNormalOperation_2155) {

    EXPECT_EQ(valueInt.toString(0), "42");

}



TEST_F(ValueTypeIntTest_2155, ToInt64NormalOperation_2155) {

    EXPECT_EQ(valueInt.toInt64(0), 42);

}



TEST_F(ValueTypeIntTest_2155, ToUint32NormalOperation_2155) {

    EXPECT_EQ(valueInt.toUint32(0), 42u);

}



TEST_F(ValueTypeIntTest_2155, FloatToIntegerHelperBoundary_2155) {

    ValueType<float> valueFloat(42.5f, TypeId::float_);

    EXPECT_EQ(valueFloat.toInt64(0), 42);

}



TEST_F(ValueTypeIntTest_2155, RationalToIntegerHelperBoundary_2155) {

    ValueType<Rational> valueRational(Rational(85, 2), TypeId::rational);

    EXPECT_EQ(valueRational.toInt64(0), 42);

}



TEST_F(ValueTypeIntTest_2155, ToFloatNormalOperation_2155) {

    ValueType<float> valueFloat(42.5f, TypeId::float_);

    EXPECT_FLOAT_EQ(valueFloat.toFloat(0), 42.5f);

}



TEST_F(ValueTypeIntTest_2155, ToRationalNormalOperation_2155) {

    ValueType<Rational> valueRational(Rational(85, 2), TypeId::rational);

    EXPECT_EQ(valueRational.toRational(0).first, 85);

    EXPECT_EQ(valueRational.toRational(0).second, 2);

}



TEST_F(ValueTypeIntTest_2155, SizeDataAreaNormalOperation_2155) {

    EXPECT_EQ(valueInt.sizeDataArea(), sizeof(int));

}



TEST_F(ValueTypeIntTest_2155, DataAreaNormalOperation_2155) {

    auto data = valueInt.dataArea();

    EXPECT_EQ(data.pData_[0], 42);

}



TEST_F(ValueTypeIntTest_2155, SetDataAreaBoundaryCondition_2155) {

    byte buf[] = {0x2A, 0x00, 0x00, 0x00}; // little-endian representation of 42

    EXPECT_EQ(valueInt.setDataArea(buf, sizeof(int)), 0);

    EXPECT_EQ(valueInt.toInt64(0), 42);

}



TEST_F(ValueTypeIntTest_2155, ReadBufferNormalOperation_2155) {

    byte buf[] = {0x2A, 0x00, 0x00, 0x00}; // little-endian representation of 42

    EXPECT_EQ(valueInt.read(buf, sizeof(int), littleEndian), 0);

    EXPECT_EQ(valueInt.toInt64(0), 42);

}



TEST_F(ValueTypeIntTest_2155, ReadStringNormalOperation_2155) {

    std::string buf = "\x2A\x00\x00\x00"; // little-endian representation of 42

    EXPECT_EQ(valueInt.read(buf), 0);

    EXPECT_EQ(valueInt.toInt64(0), 42);

}



TEST_F(ValueTypeIntTest_2155, CopyNormalOperation_2155) {

    byte buf[4];

    valueInt.copy(buf, littleEndian);

    EXPECT_EQ(*reinterpret_cast<int*>(buf), 42);

}



TEST_F(ValueTypeIntTest_2155, WriteNormalOperation_2155) {

    testing::internal::CaptureStdout();

    valueInt.write(std::cout);

    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "42");

}



TEST_F(ValueTypeIntTest_2155, CloneNormalOperation_2155) {

    auto clonedValue = valueInt.clone();

    EXPECT_NE(&valueInt, clonedValue.get());

    EXPECT_EQ(clonedValue->toInt64(0), 42);

}
