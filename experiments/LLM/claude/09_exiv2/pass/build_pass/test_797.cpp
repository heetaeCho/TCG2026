#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include "exiv2/value.hpp"

using namespace Exiv2;

class DataValueTest_797 : public ::testing::Test {
protected:
    void SetUp() override {
    }
    void TearDown() override {
    }
};

// Test default construction with undefined type
TEST_F(DataValueTest_797, ConstructWithUndefinedType_797) {
    DataValue dv(TypeId::undefined);
    EXPECT_EQ(dv.count(), 0u);
    EXPECT_EQ(dv.size(), 0u);
}

// Test construction with byte type
TEST_F(DataValueTest_797, ConstructWithUnsignedByteType_797) {
    DataValue dv(TypeId::unsignedByte);
    EXPECT_EQ(dv.count(), 0u);
    EXPECT_EQ(dv.size(), 0u);
}

// Test read from byte buffer
TEST_F(DataValueTest_797, ReadFromByteBuffer_797) {
    DataValue dv(TypeId::undefined);
    byte buf[] = {0x01, 0x02, 0x03, 0x04};
    int result = dv.read(buf, sizeof(buf), littleEndian);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(dv.count(), 4u);
    EXPECT_EQ(dv.size(), 4u);
}

// Test read from empty byte buffer
TEST_F(DataValueTest_797, ReadFromEmptyByteBuffer_797) {
    DataValue dv(TypeId::undefined);
    int result = dv.read(nullptr, 0, littleEndian);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(dv.count(), 0u);
    EXPECT_EQ(dv.size(), 0u);
}

// Test read from string
TEST_F(DataValueTest_797, ReadFromString_797) {
    DataValue dv(TypeId::undefined);
    int result = dv.read("1 2 3 4");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(dv.count(), 4u);
    EXPECT_EQ(dv.size(), 4u);
}

// Test read from empty string
TEST_F(DataValueTest_797, ReadFromEmptyString_797) {
    DataValue dv(TypeId::undefined);
    int result = dv.read("");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(dv.count(), 0u);
}

// Test write with empty value
TEST_F(DataValueTest_797, WriteEmptyValue_797) {
    DataValue dv(TypeId::undefined);
    std::ostringstream os;
    dv.write(os);
    EXPECT_EQ(os.str(), "");
}

// Test write with single byte
TEST_F(DataValueTest_797, WriteSingleByte_797) {
    DataValue dv(TypeId::undefined);
    byte buf[] = {42};
    dv.read(buf, 1, littleEndian);
    std::ostringstream os;
    dv.write(os);
    EXPECT_EQ(os.str(), "42");
}

// Test write with multiple bytes
TEST_F(DataValueTest_797, WriteMultipleBytes_797) {
    DataValue dv(TypeId::undefined);
    byte buf[] = {1, 2, 3};
    dv.read(buf, 3, littleEndian);
    std::ostringstream os;
    dv.write(os);
    EXPECT_EQ(os.str(), "1 2 3");
}

// Test write with max byte values
TEST_F(DataValueTest_797, WriteMaxByteValue_797) {
    DataValue dv(TypeId::undefined);
    byte buf[] = {255, 0, 128};
    dv.read(buf, 3, littleEndian);
    std::ostringstream os;
    dv.write(os);
    EXPECT_EQ(os.str(), "255 0 128");
}

// Test copy to buffer
TEST_F(DataValueTest_797, CopyToBuffer_797) {
    DataValue dv(TypeId::undefined);
    byte input[] = {10, 20, 30};
    dv.read(input, 3, littleEndian);
    
    byte output[3] = {0};
    size_t copied = dv.copy(output, littleEndian);
    EXPECT_EQ(copied, 3u);
    EXPECT_EQ(output[0], 10);
    EXPECT_EQ(output[1], 20);
    EXPECT_EQ(output[2], 30);
}

// Test copy from empty DataValue
TEST_F(DataValueTest_797, CopyEmptyToBuffer_797) {
    DataValue dv(TypeId::undefined);
    byte output[1] = {0xFF};
    size_t copied = dv.copy(output, littleEndian);
    EXPECT_EQ(copied, 0u);
}

// Test toString for valid index
TEST_F(DataValueTest_797, ToStringValidIndex_797) {
    DataValue dv(TypeId::undefined);
    byte buf[] = {65, 66, 67};
    dv.read(buf, 3, littleEndian);
    
    std::string s0 = dv.toString(0);
    std::string s1 = dv.toString(1);
    std::string s2 = dv.toString(2);
    
    EXPECT_EQ(s0, "65");
    EXPECT_EQ(s1, "66");
    EXPECT_EQ(s2, "67");
}

// Test toInt64 for valid index
TEST_F(DataValueTest_797, ToInt64ValidIndex_797) {
    DataValue dv(TypeId::undefined);
    byte buf[] = {100, 200};
    dv.read(buf, 2, littleEndian);
    
    EXPECT_EQ(dv.toInt64(0), 100);
    EXPECT_EQ(dv.toInt64(1), 200);
}

// Test toUint32 for valid index
TEST_F(DataValueTest_797, ToUint32ValidIndex_797) {
    DataValue dv(TypeId::undefined);
    byte buf[] = {50, 150};
    dv.read(buf, 2, littleEndian);
    
    EXPECT_EQ(dv.toUint32(0), 50u);
    EXPECT_EQ(dv.toUint32(1), 150u);
}

// Test toFloat for valid index
TEST_F(DataValueTest_797, ToFloatValidIndex_797) {
    DataValue dv(TypeId::undefined);
    byte buf[] = {77};
    dv.read(buf, 1, littleEndian);
    
    EXPECT_FLOAT_EQ(dv.toFloat(0), 77.0f);
}

// Test toRational for valid index
TEST_F(DataValueTest_797, ToRationalValidIndex_797) {
    DataValue dv(TypeId::undefined);
    byte buf[] = {10};
    dv.read(buf, 1, littleEndian);
    
    Rational r = dv.toRational(0);
    EXPECT_EQ(r.first, 10);
    EXPECT_EQ(r.second, 1);
}

// Test clone
TEST_F(DataValueTest_797, ClonePreservesData_797) {
    DataValue dv(TypeId::undefined);
    byte buf[] = {5, 10, 15};
    dv.read(buf, 3, littleEndian);
    
    auto cloned = dv.clone();
    ASSERT_NE(cloned, nullptr);
    
    EXPECT_EQ(cloned->count(), 3u);
    EXPECT_EQ(cloned->size(), 3u);
    
    std::ostringstream os;
    cloned->write(os);
    EXPECT_EQ(os.str(), "5 10 15");
}

// Test read string with single value
TEST_F(DataValueTest_797, ReadStringSingleValue_797) {
    DataValue dv(TypeId::undefined);
    int result = dv.read("255");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(dv.count(), 1u);
    EXPECT_EQ(dv.toInt64(0), 255);
}

// Test constructor from buffer
TEST_F(DataValueTest_797, ConstructFromBuffer_797) {
    byte buf[] = {7, 14, 21};
    DataValue dv(buf, sizeof(buf), littleEndian, TypeId::undefined);
    
    EXPECT_EQ(dv.count(), 3u);
    EXPECT_EQ(dv.size(), 3u);
    EXPECT_EQ(dv.toInt64(0), 7);
    EXPECT_EQ(dv.toInt64(1), 14);
    EXPECT_EQ(dv.toInt64(2), 21);
}

// Test read overwrites previous data
TEST_F(DataValueTest_797, ReadOverwritesPreviousData_797) {
    DataValue dv(TypeId::undefined);
    byte buf1[] = {1, 2, 3};
    dv.read(buf1, 3, littleEndian);
    EXPECT_EQ(dv.count(), 3u);
    
    byte buf2[] = {4, 5};
    dv.read(buf2, 2, littleEndian);
    EXPECT_EQ(dv.count(), 2u);
    EXPECT_EQ(dv.toInt64(0), 4);
    EXPECT_EQ(dv.toInt64(1), 5);
}

// Test write with two bytes
TEST_F(DataValueTest_797, WriteTwoBytes_797) {
    DataValue dv(TypeId::undefined);
    byte buf[] = {0, 255};
    dv.read(buf, 2, littleEndian);
    std::ostringstream os;
    dv.write(os);
    EXPECT_EQ(os.str(), "0 255");
}

// Test boundary: out of range index for toInt64
TEST_F(DataValueTest_797, ToInt64OutOfRange_797) {
    DataValue dv(TypeId::undefined);
    byte buf[] = {42};
    dv.read(buf, 1, littleEndian);
    
    // Accessing out of range should throw or return error
    EXPECT_THROW(dv.toInt64(1), std::exception);
}

// Test boundary: out of range index for toString
TEST_F(DataValueTest_797, ToStringOutOfRange_797) {
    DataValue dv(TypeId::undefined);
    byte buf[] = {42};
    dv.read(buf, 1, littleEndian);
    
    EXPECT_THROW(dv.toString(5), std::exception);
}

// Test boundary: out of range index for toFloat
TEST_F(DataValueTest_797, ToFloatOutOfRange_797) {
    DataValue dv(TypeId::undefined);
    byte buf[] = {42};
    dv.read(buf, 1, littleEndian);
    
    EXPECT_THROW(dv.toFloat(10), std::exception);
}

// Test boundary: out of range for toRational
TEST_F(DataValueTest_797, ToRationalOutOfRange_797) {
    DataValue dv(TypeId::undefined);
    byte buf[] = {42};
    dv.read(buf, 1, littleEndian);
    
    EXPECT_THROW(dv.toRational(3), std::exception);
}

// Test large buffer
TEST_F(DataValueTest_797, ReadLargeBuffer_797) {
    DataValue dv(TypeId::undefined);
    std::vector<byte> buf(1000, 0xAB);
    dv.read(buf.data(), buf.size(), littleEndian);
    
    EXPECT_EQ(dv.count(), 1000u);
    EXPECT_EQ(dv.size(), 1000u);
    EXPECT_EQ(dv.toInt64(0), 0xAB);
    EXPECT_EQ(dv.toInt64(999), 0xAB);
}

// Test write with all zero bytes
TEST_F(DataValueTest_797, WriteAllZeroBytes_797) {
    DataValue dv(TypeId::undefined);
    byte buf[] = {0, 0, 0};
    dv.read(buf, 3, littleEndian);
    std::ostringstream os;
    dv.write(os);
    EXPECT_EQ(os.str(), "0 0 0");
}

// Test copy preserves byte order independence for DataValue
TEST_F(DataValueTest_797, CopyBigEndian_797) {
    DataValue dv(TypeId::undefined);
    byte input[] = {10, 20, 30};
    dv.read(input, 3, bigEndian);
    
    byte output[3] = {0};
    size_t copied = dv.copy(output, bigEndian);
    EXPECT_EQ(copied, 3u);
    EXPECT_EQ(output[0], 10);
    EXPECT_EQ(output[1], 20);
    EXPECT_EQ(output[2], 30);
}

// Test string read with spaces
TEST_F(DataValueTest_797, ReadStringMultipleSpaces_797) {
    DataValue dv(TypeId::undefined);
    int result = dv.read("10 20 30");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(dv.count(), 3u);
    EXPECT_EQ(dv.toInt64(0), 10);
    EXPECT_EQ(dv.toInt64(1), 20);
    EXPECT_EQ(dv.toInt64(2), 30);
}

// Test toUint32 out of range
TEST_F(DataValueTest_797, ToUint32OutOfRange_797) {
    DataValue dv(TypeId::undefined);
    byte buf[] = {42};
    dv.read(buf, 1, littleEndian);
    
    EXPECT_THROW(dv.toUint32(2), std::exception);
}

// Test clone of empty DataValue
TEST_F(DataValueTest_797, CloneEmpty_797) {
    DataValue dv(TypeId::undefined);
    auto cloned = dv.clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->count(), 0u);
    EXPECT_EQ(cloned->size(), 0u);
}
