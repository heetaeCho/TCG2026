#include <gtest/gtest.h>

#include "exiv2/value.hpp"



using namespace Exiv2;



// Define a fixture for ValueType tests

class ValueTypeTest_2156 : public ::testing::Test {

protected:

    ValueType<int> valueInt;

    ValueType<double> valueDouble;



    ValueTypeTest_2156() 

        : valueInt(42, TypeId::int32),

          valueDouble(3.14, TypeId::xmpText) {}

};



// Test normal operation of read with byte buffer

TEST_F(ValueTypeTest_2156, ReadByteBufferNormalOperation_2156) {

    const byte buf[] = {0x2A}; // 42 in little-endian

    EXPECT_EQ(valueInt.read(buf, sizeof(buf), littleEndian), 0);

}



// Test normal operation of read with string buffer

TEST_F(ValueTypeTest_2156, ReadStringBufferNormalOperation_2156) {

    EXPECT_EQ(valueDouble.read("3.14"), 0);

}



// Test boundary condition for setDataArea with empty buffer

TEST_F(ValueTypeTest_2156, SetDataAreaEmptyBuffer_2156) {

    const byte* buf = nullptr;

    size_t len = 0;

    EXPECT_EQ(valueInt.setDataArea(buf, len), 0);

}



// Test boundary condition for setDataArea with non-empty buffer

TEST_F(ValueTypeTest_2156, SetDataAreaNonEmptyBuffer_2156) {

    const byte buf[] = {0x2A}; // Example data

    EXPECT_EQ(valueInt.setDataArea(buf, sizeof(buf)), 0);

}



// Test normal operation of copy method

TEST_F(ValueTypeTest_2156, CopyNormalOperation_2156) {

    byte buffer[4];

    EXPECT_GT(valueInt.copy(buffer, littleEndian), 0);

}



// Test boundary condition for count method with no values

TEST_F(ValueTypeTest_2156, CountNoValues_2156) {

    ValueType<int> emptyValue(TypeId::int32);

    EXPECT_EQ(emptyValue.count(), 0);

}



// Test normal operation of size method

TEST_F(ValueTypeTest_2156, SizeNormalOperation_2156) {

    EXPECT_GT(valueDouble.size(), 0);

}



// Test normal operation of write method

TEST_F(ValueTypeTest_2156, WriteNormalOperation_2156) {

    std::ostringstream oss;

    valueInt.write(oss);

    EXPECT_FALSE(oss.str().empty());

}



// Test normal operation of toString method with index 0

TEST_F(ValueTypeTest_2156, ToStringIndexZero_2156) {

    EXPECT_EQ(valueDouble.toString(0), "3.14");

}



// Test boundary condition for toInt64 method with invalid index

TEST_F(ValueTypeTest_2156, ToInt64InvalidIndex_2156) {

    EXPECT_THROW(valueInt.toInt64(1), Error);

}



// Test normal operation of toUint32 method

TEST_F(ValueTypeTest_2156, ToUint32NormalOperation_2156) {

    EXPECT_EQ(valueInt.toUint32(0), 42u);

}



// Test normal operation of toFloat method

TEST_F(ValueTypeTest_2156, ToFloatNormalOperation_2156) {

    EXPECT_FLOAT_EQ(valueDouble.toFloat(0), 3.14f);

}



// Test normal operation of toRational method

TEST_F(ValueTypeTest_2156, ToRationalNormalOperation_2156) {

    Rational r = valueDouble.toRational(0);

    EXPECT_EQ(r.first, 3);

    EXPECT_NEAR(r.second, 1.0 / 0.14, 0.01); // Approximation due to floating point precision

}



// Test normal operation of sizeDataArea method

TEST_F(ValueTypeTest_2156, SizeDataAreaNormalOperation_2156) {

    EXPECT_EQ(valueInt.sizeDataArea(), 0);

}



// Test normal operation of dataArea method

TEST_F(ValueTypeTest_2156, DataAreaNormalOperation_2156) {

    DataBuf db = valueDouble.dataArea();

    EXPECT_TRUE(db.pData_ != nullptr || db.size_ == 0);

}
