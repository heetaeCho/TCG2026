#include <gtest/gtest.h>

#include "exiv2/value.hpp"

#include <memory>



using namespace Exiv2;



class ValueTest_790 : public ::testing::Test {

protected:

    TypeId dummyTypeId = static_cast<TypeId>(1); // Assuming a valid TypeId for testing

    std::unique_ptr<Value> value;



    void SetUp() override {

        value = Value::create(dummyTypeId);

    }

};



TEST_F(ValueTest_790, SizeDataArea_ReturnsZero_790) {

    EXPECT_EQ(value->sizeDataArea(), 0U);

}



TEST_F(ValueTest_790, Ok_ReturnsTrueByDefault_790) {

    EXPECT_TRUE(value->ok());

}



TEST_F(ValueTest_790, TypeId_ReturnsProvidedTypeId_790) {

    EXPECT_EQ(value->typeId(), dummyTypeId);

}



TEST_F(ValueTest_790, Clone_ReturnsNonNullUniquePtr_790) {

    auto clonedValue = value->clone();

    EXPECT_NE(clonedValue.get(), nullptr);

}



TEST_F(ValueTest_790, SetDataArea_ReturnsZeroForDefaultImplementation_790) {

    byte buffer[] = {0x1, 0x2, 0x3};

    size_t len = sizeof(buffer);

    EXPECT_EQ(value->setDataArea(buffer, len), 0);

}



TEST_F(ValueTest_790, Copy_ReturnsZeroForDefaultImplementation_790) {

    byte buffer[10];

    ByteOrder dummyByteOrder = littleEndian; // Assuming a valid ByteOrder for testing

    EXPECT_EQ(value->copy(buffer, dummyByteOrder), 0U);

}



TEST_F(ValueTest_790, Count_ReturnsZeroForDefaultImplementation_790) {

    EXPECT_EQ(value->count(), 0U);

}



TEST_F(ValueTest_790, Size_ReturnsZeroForDefaultImplementation_790) {

    EXPECT_EQ(value->size(), 0U);

}



TEST_F(ValueTest_790, ToString_ReturnsEmptyStringByDefault_790) {

    EXPECT_EQ(value->toString(), "");

}



TEST_F(ValueTest_790, ToStringWithIndex_ReturnsEmptyStringByDefault_790) {

    EXPECT_EQ(value->toString(0), "");

}



TEST_F(ValueTest_790, ToInt64_ReturnsZeroForDefaultImplementation_790) {

    EXPECT_EQ(value->toInt64(0), 0);

}



TEST_F(ValueTest_790, ToUint32_ReturnsZeroForDefaultImplementation_790) {

    EXPECT_EQ(value->toUint32(0), 0U);

}



TEST_F(ValueTest_790, ToFloat_ReturnsZeroForDefaultImplementation_790) {

    EXPECT_FLOAT_EQ(value->toFloat(0), 0.0f);

}



TEST_F(ValueTest_790, ToRational_ReturnsZeroNumeratorAndDenominatorForDefaultImplementation_790) {

    Rational rational = value->toRational(0);

    EXPECT_EQ(rational.first, 0);

    EXPECT_EQ(rational.second, 0);

}
