#include <gtest/gtest.h>

#include "exiv2/value.hpp"



using namespace Exiv2;



// Test fixture for ValueType tests

template <typename T>

class ValueTypeTest : public ::testing::Test {

protected:

    ValueType<T> value;

};



using TestTypes = ::testing::Types<int, float, double>;

TYPED_TEST_SUITE(ValueTypeTest, TestTypes);



TYPED_TEST(ValueTypeTest, Constructor_Default_174) {

    EXPECT_EQ(this->value.count(), 0);

}



TYPED_TEST(ValueTypeTest, SetDataArea_Successful_174) {

    byte data[] = {0x01, 0x02, 0x03};

    EXPECT_EQ(this->value.setDataArea(data, sizeof(data)), 0);

    EXPECT_EQ(this->value.sizeDataArea(), sizeof(data));

}



TYPED_TEST(ValueTypeTest, SetDataArea_ZeroLength_174) {

    byte data[] = {0x01, 0x02, 0x03};

    EXPECT_EQ(this->value.setDataArea(data, 0), 0);

    EXPECT_EQ(this->value.sizeDataArea(), 0);

}



TYPED_TEST(ValueTypeTest, DataArea_ReturnsCorrectData_174) {

    byte data[] = {0x01, 0x02, 0x03};

    this->value.setDataArea(data, sizeof(data));

    DataBuf buf = this->value.dataArea();

    EXPECT_EQ(buf.pData_, data);

    EXPECT_EQ(buf.size_, sizeof(data));

}



TYPED_TEST(ValueTypeTest, Copy_ReturnsCorrectSize_174) {

    byte data[] = {0x01, 0x02, 0x03};

    this->value.setDataArea(data, sizeof(data));

    byte output[sizeof(data)];

    EXPECT_EQ(this->value.copy(output, littleEndian), sizeof(data));

}



TYPED_TEST(ValueTypeTest, Copy_ZeroLength_174) {

    byte data[] = {0x01, 0x02, 0x03};

    this->value.setDataArea(data, sizeof(data));

    byte output[0];

    EXPECT_EQ(this->value.copy(output, littleEndian), 0);

}



TYPED_TEST(ValueTypeTest, Size_ReturnsCorrectSize_174) {

    byte data[] = {0x01, 0x02, 0x03};

    this->value.setDataArea(data, sizeof(data));

    EXPECT_EQ(this->value.size(), sizeof(data));

}



TYPED_TEST(ValueTypeTest, Count_ReturnsCorrectCount_174) {

    byte data[] = {0x01, 0x02, 0x03};

    this->value.setDataArea(data, sizeof(data));

    EXPECT_EQ(this->value.count(), sizeof(data) / sizeof(TypeParam));

}



TYPED_TEST(ValueTypeTest, ToString_ReturnsNonEmptyString_174) {

    byte data[] = {0x01, 0x02, 0x03};

    this->value.setDataArea(data, sizeof(data));

    EXPECT_FALSE(this->value.toString(0).empty());

}



TYPED_TEST(ValueTypeTest, ToInt64_ReturnsCorrectValue_174) {

    byte data[] = {0x01, 0x02, 0x03};

    this->value.setDataArea(data, sizeof(data));

    EXPECT_EQ(this->value.toInt64(0), *reinterpret_cast<TypeParam*>(data));

}



TYPED_TEST(ValueTypeTest, ToUint32_ReturnsCorrectValue_174) {

    byte data[] = {0x01, 0x02, 0x03};

    this->value.setDataArea(data, sizeof(data));

    EXPECT_EQ(this->value.toUint32(0), *reinterpret_cast<TypeParam*>(data));

}



TYPED_TEST(ValueTypeTest, ToFloat_ReturnsCorrectValue_174) {

    byte data[] = {0x01, 0x02, 0x03};

    this->value.setDataArea(data, sizeof(data));

    EXPECT_EQ(this->value.toFloat(0), *reinterpret_cast<TypeParam*>(data));

}



TYPED_TEST(ValueTypeTest, ToRational_ReturnsCorrectValue_174) {

    byte data[] = {0x01, 0x02, 0x03};

    this->value.setDataArea(data, sizeof(data));

    Rational rational = this->value.toRational(0);

    EXPECT_EQ(rational.first, *reinterpret_cast<TypeParam*>(data));

    EXPECT_EQ(rational.second, 1);

}
