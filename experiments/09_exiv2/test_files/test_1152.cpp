#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Assuming Exiv2 namespace and f2Data function are available

namespace Exiv2 {

    size_t f2Data(byte* buf, float f, ByteOrder byteOrder);

}



using ::testing::Test;

using ::testing::Eq;



class F2DataTest_1152 : public Test {

protected:

    static constexpr size_t bufferSize = sizeof(uint32_t);

    byte buffer[bufferSize];

};



TEST_F(F2DataTest_1152, PositiveFloatConversion_1152) {

    float testValue = 42.0f;

    Exiv2::ByteOrder byteOrder = Exiv2::littleEndian; // Example byte order

    size_t result = Exiv2::f2Data(buffer, testValue, byteOrder);

    EXPECT_EQ(result, bufferSize);

}



TEST_F(F2DataTest_1152, NegativeFloatConversion_1152) {

    float testValue = -42.0f;

    Exiv2::ByteOrder byteOrder = Exiv2::bigEndian; // Example byte order

    size_t result = Exiv2::f2Data(buffer, testValue, byteOrder);

    EXPECT_EQ(result, bufferSize);

}



TEST_F(F2DataTest_1152, ZeroFloatConversion_1152) {

    float testValue = 0.0f;

    Exiv2::ByteOrder byteOrder = Exiv2::littleEndian; // Example byte order

    size_t result = Exiv2::f2Data(buffer, testValue, byteOrder);

    EXPECT_EQ(result, bufferSize);

}



TEST_F(F2DataTest_1152, MaxFloatConversion_1152) {

    float testValue = std::numeric_limits<float>::max();

    Exiv2::ByteOrder byteOrder = Exiv2::bigEndian; // Example byte order

    size_t result = Exiv2::f2Data(buffer, testValue, byteOrder);

    EXPECT_EQ(result, bufferSize);

}



TEST_F(F2DataTest_1152, MinFloatConversion_1152) {

    float testValue = std::numeric_limits<float>::min();

    Exiv2::ByteOrder byteOrder = Exiv2::littleEndian; // Example byte order

    size_t result = Exiv2::f2Data(buffer, testValue, byteOrder);

    EXPECT_EQ(result, bufferSize);

}



TEST_F(F2DataTest_1152, SubnormalFloatConversion_1152) {

    float testValue = std::numeric_limits<float>::denorm_min();

    Exiv2::ByteOrder byteOrder = Exiv2::bigEndian; // Example byte order

    size_t result = Exiv2::f2Data(buffer, testValue, byteOrder);

    EXPECT_EQ(result, bufferSize);

}



TEST_F(F2DataTest_1152, NaNFloatConversion_1152) {

    float testValue = std::numeric_limits<float>::quiet_NaN();

    Exiv2::ByteOrder byteOrder = Exiv2::littleEndian; // Example byte order

    size_t result = Exiv2::f2Data(buffer, testValue, byteOrder);

    EXPECT_EQ(result, bufferSize);

}



TEST_F(F2DataTest_1152, InfinityFloatConversion_1152) {

    float testValue = std::numeric_limits<float>::infinity();

    Exiv2::ByteOrder byteOrder = Exiv2::bigEndian; // Example byte order

    size_t result = Exiv2::f2Data(buffer, testValue, byteOrder);

    EXPECT_EQ(result, bufferSize);

}



TEST_F(F2DataTest_1152, NegativeInfinityFloatConversion_1152) {

    float testValue = -std::numeric_limits<float>::infinity();

    Exiv2::ByteOrder byteOrder = Exiv2::littleEndian; // Example byte order

    size_t result = Exiv2::f2Data(buffer, testValue, byteOrder);

    EXPECT_EQ(result, bufferSize);

}
