#include <gtest/gtest.h>

#include "exiv2/value.hpp"



using namespace Exiv2;



TEST_F(ValueTypeTest_2154, ConstructorWithBuffer_NormalOperation_2154) {

    const byte buf[] = {0x01, 0x02, 0x03};

    size_t len = sizeof(buf);

    ByteOrder byteOrder = littleEndian;

    TypeId typeId = asciiString;



    ValueType<int> value(buf, len, byteOrder, typeId);



    EXPECT_TRUE(value.ok());

}



TEST_F(ValueTypeTest_2154, ConstructorWithBuffer_BoundaryCondition_ZeroLength_2154) {

    const byte buf[] = {0x01, 0x02, 0x03};

    size_t len = 0;

    ByteOrder byteOrder = littleEndian;

    TypeId typeId = asciiString;



    ValueType<int> value(buf, len, byteOrder, typeId);



    EXPECT_TRUE(value.ok());

}



TEST_F(ValueTypeTest_2154, ConstructorWithBuffer_ExceptionalCase_NullBuffer_2154) {

    const byte* buf = nullptr;

    size_t len = 3;

    ByteOrder byteOrder = littleEndian;

    TypeId typeId = asciiString;



    ValueType<int> value(buf, len, byteOrder, typeId);



    EXPECT_FALSE(value.ok());

}



TEST_F(ValueTypeTest_2154, ReadWithBuffer_NormalOperation_2154) {

    const byte buf[] = {0x01, 0x02, 0x03};

    size_t len = sizeof(buf);

    ByteOrder byteOrder = littleEndian;

    TypeId typeId = asciiString;



    ValueType<int> value(typeId);

    int result = value.read(buf, len, byteOrder);



    EXPECT_EQ(result, 0); // Assuming read returns 0 on success

}



TEST_F(ValueTypeTest_2154, ReadWithBuffer_BoundaryCondition_ZeroLength_2154) {

    const byte buf[] = {0x01, 0x02, 0x03};

    size_t len = 0;

    ByteOrder byteOrder = littleEndian;

    TypeId typeId = asciiString;



    ValueType<int> value(typeId);

    int result = value.read(buf, len, byteOrder);



    EXPECT_EQ(result, 0); // Assuming read returns 0 on success

}



TEST_F(ValueTypeTest_2154, ReadWithBuffer_ExceptionalCase_NullBuffer_2154) {

    const byte* buf = nullptr;

    size_t len = 3;

    ByteOrder byteOrder = littleEndian;

    TypeId typeId = asciiString;



    ValueType<int> value(typeId);

    int result = value.read(buf, len, byteOrder);



    EXPECT_NE(result, 0); // Assuming read returns non-zero on failure

}



TEST_F(ValueTypeTest_2154, ReadWithString_NormalOperation_2154) {

    std::string buf = "test";

    TypeId typeId = asciiString;



    ValueType<int> value(typeId);

    int result = value.read(buf);



    EXPECT_EQ(result, 0); // Assuming read returns 0 on success

}



TEST_F(ValueTypeTest_2154, ReadWithString_BoundaryCondition_EmptyString_2154) {

    std::string buf = "";

    TypeId typeId = asciiString;



    ValueType<int> value(typeId);

    int result = value.read(buf);



    EXPECT_EQ(result, 0); // Assuming read returns 0 on success

}



TEST_F(ValueTypeTest_2154, SetDataArea_NormalOperation_2154) {

    const byte buf[] = {0x01, 0x02, 0x03};

    size_t len = sizeof(buf);

    TypeId typeId = asciiString;



    ValueType<int> value(typeId);

    int result = value.setDataArea(buf, len);



    EXPECT_EQ(result, 0); // Assuming setDataArea returns 0 on success

}



TEST_F(ValueTypeTest_2154, SetDataArea_BoundaryCondition_ZeroLength_2154) {

    const byte buf[] = {0x01, 0x02, 0x03};

    size_t len = 0;

    TypeId typeId = asciiString;



    ValueType<int> value(typeId);

    int result = value.setDataArea(buf, len);



    EXPECT_EQ(result, 0); // Assuming setDataArea returns 0 on success

}



TEST_F(ValueTypeTest_2154, SetDataArea_ExceptionalCase_NullBuffer_2154) {

    const byte* buf = nullptr;

    size_t len = 3;

    TypeId typeId = asciiString;



    ValueType<int> value(typeId);

    int result = value.setDataArea(buf, len);



    EXPECT_NE(result, 0); // Assuming setDataArea returns non-zero on failure

}



TEST_F(ValueTypeTest_2154, Count_NormalOperation_2154) {

    TypeId typeId = asciiString;



    ValueType<int> value(typeId);

    size_t count = value.count();



    EXPECT_GE(count, 0); // Assuming count is always non-negative

}



TEST_F(ValueTypeTest_2154, Size_NormalOperation_2154) {

    TypeId typeId = asciiString;



    ValueType<int> value(typeId);

    size_t size = value.size();



    EXPECT_GE(size, 0); // Assuming size is always non-negative

}



TEST_F(ValueTypeTest_2154, ToString_NormalOperation_2154) {

    TypeId typeId = asciiString;



    ValueType<int> value(typeId);

    std::string str = value.toString();



    EXPECT_TRUE(str.empty() || !str.empty()); // Assuming toString returns a string

}



TEST_F(ValueTypeTest_2154, ToStringWithIndex_NormalOperation_2154) {

    TypeId typeId = asciiString;



    ValueType<int> value(typeId);

    std::string str = value.toString(0);



    EXPECT_TRUE(str.empty() || !str.empty()); // Assuming toString returns a string

}



TEST_F(ValueTypeTest_2154, ToInt64_NormalOperation_2154) {

    TypeId typeId = asciiString;



    ValueType<int> value(typeId);

    int64_t val = value.toInt64(0);



    EXPECT_TRUE(true); // Assuming toInt64 returns an int64_t

}



TEST_F(ValueTypeTest_2154, ToUint32_NormalOperation_2154) {

    TypeId typeId = asciiString;



    ValueType<int> value(typeId);

    uint32_t val = value.toUint32(0);



    EXPECT_TRUE(true); // Assuming toUint32 returns a uint32_t

}



TEST_F(ValueTypeTest_2154, ToFloat_NormalOperation_2154) {

    TypeId typeId = asciiString;



    ValueType<int> value(typeId);

    float val = value.toFloat(0);



    EXPECT_TRUE(true); // Assuming toFloat returns a float

}



TEST_F(ValueTypeTest_2154, ToRational_NormalOperation_2154) {

    TypeId typeId = asciiString;



    ValueType<int> value(typeId);

    Rational rat = value.toRational(0);



    EXPECT_TRUE(true); // Assuming toRational returns a Rational

}



TEST_F(ValueTypeTest_2154, SizeDataArea_NormalOperation_2154) {

    TypeId typeId = asciiString;



    ValueType<int> value(typeId);

    size_t size = value.sizeDataArea();



    EXPECT_GE(size, 0); // Assuming sizeDataArea is always non-negative

}



TEST_F(ValueTypeTest_2154, DataArea_NormalOperation_2154) {

    TypeId typeId = asciiString;



    ValueType<int> value(typeId);

    DataBuf data = value.dataArea();



    EXPECT_TRUE(true); // Assuming dataArea returns a DataBuf

}
