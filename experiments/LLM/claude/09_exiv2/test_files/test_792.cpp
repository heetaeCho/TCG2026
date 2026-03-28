#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <cstring>
#include <sstream>
#include <vector>

using namespace Exiv2;

class DataValueTest_792 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test default construction with undefined type
TEST_F(DataValueTest_792, ConstructWithUndefinedType_792) {
    DataValue dv(TypeId::undefined);
    EXPECT_EQ(dv.count(), 0u);
    EXPECT_EQ(dv.size(), 0u);
}

// Test construction with unsignedByte type
TEST_F(DataValueTest_792, ConstructWithUnsignedByteType_792) {
    DataValue dv(TypeId::unsignedByte);
    EXPECT_EQ(dv.count(), 0u);
    EXPECT_EQ(dv.size(), 0u);
}

// Test read from byte buffer
TEST_F(DataValueTest_792, ReadFromByteBuffer_792) {
    DataValue dv(TypeId::undefined);
    const byte buf[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    int result = dv.read(buf, 5, littleEndian);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(dv.size(), 5u);
    EXPECT_EQ(dv.count(), 5u);
}

// Test read from string
TEST_F(DataValueTest_792, ReadFromString_792) {
    DataValue dv(TypeId::undefined);
    std::string input = "48 65 6C 6C 6F";  // "Hello" in hex
    int result = dv.read(input);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(dv.count(), dv.size());
}

// Test count equals size
TEST_F(DataValueTest_792, CountEqualsSize_792) {
    DataValue dv(TypeId::undefined);
    const byte buf[] = {0xAA, 0xBB, 0xCC};
    dv.read(buf, 3, littleEndian);
    EXPECT_EQ(dv.count(), dv.size());
}

// Test copy to buffer
TEST_F(DataValueTest_792, CopyToBuffer_792) {
    DataValue dv(TypeId::undefined);
    const byte input[] = {0x10, 0x20, 0x30};
    dv.read(input, 3, littleEndian);

    byte output[3] = {0};
    size_t copied = dv.copy(output, littleEndian);
    EXPECT_EQ(copied, 3u);
    EXPECT_EQ(output[0], 0x10);
    EXPECT_EQ(output[1], 0x20);
    EXPECT_EQ(output[2], 0x30);
}

// Test empty buffer read
TEST_F(DataValueTest_792, ReadEmptyBuffer_792) {
    DataValue dv(TypeId::undefined);
    const byte buf[] = {0};
    int result = dv.read(buf, 0, littleEndian);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(dv.count(), 0u);
    EXPECT_EQ(dv.size(), 0u);
}

// Test toString with valid index
TEST_F(DataValueTest_792, ToStringValidIndex_792) {
    DataValue dv(TypeId::undefined);
    const byte buf[] = {65};  // 'A' = 65
    dv.read(buf, 1, littleEndian);
    std::string s = dv.toString(0);
    EXPECT_FALSE(s.empty());
}

// Test toInt64 with valid index
TEST_F(DataValueTest_792, ToInt64ValidIndex_792) {
    DataValue dv(TypeId::undefined);
    const byte buf[] = {42};
    dv.read(buf, 1, littleEndian);
    int64_t val = dv.toInt64(0);
    EXPECT_EQ(val, 42);
}

// Test toUint32 with valid index
TEST_F(DataValueTest_792, ToUint32ValidIndex_792) {
    DataValue dv(TypeId::undefined);
    const byte buf[] = {255};
    dv.read(buf, 1, littleEndian);
    uint32_t val = dv.toUint32(0);
    EXPECT_EQ(val, 255u);
}

// Test toFloat with valid index
TEST_F(DataValueTest_792, ToFloatValidIndex_792) {
    DataValue dv(TypeId::undefined);
    const byte buf[] = {100};
    dv.read(buf, 1, littleEndian);
    float val = dv.toFloat(0);
    EXPECT_FLOAT_EQ(val, 100.0f);
}

// Test toRational with valid index
TEST_F(DataValueTest_792, ToRationalValidIndex_792) {
    DataValue dv(TypeId::undefined);
    const byte buf[] = {7};
    dv.read(buf, 1, littleEndian);
    Rational r = dv.toRational(0);
    EXPECT_EQ(r.first, 7);
    EXPECT_EQ(r.second, 1);
}

// Test write to ostream
TEST_F(DataValueTest_792, WriteToOstream_792) {
    DataValue dv(TypeId::undefined);
    const byte buf[] = {0x0A, 0x0B};
    dv.read(buf, 2, littleEndian);

    std::ostringstream os;
    dv.write(os);
    std::string output = os.str();
    EXPECT_FALSE(output.empty());
}

// Test clone
TEST_F(DataValueTest_792, ClonePreservesData_792) {
    DataValue dv(TypeId::undefined);
    const byte buf[] = {1, 2, 3};
    dv.read(buf, 3, littleEndian);

    auto cloned = dv.clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->count(), dv.count());
    EXPECT_EQ(cloned->size(), dv.size());
}

// Test multiple reads overwrite previous data
TEST_F(DataValueTest_792, MultipleReadsOverwriteData_792) {
    DataValue dv(TypeId::undefined);
    const byte buf1[] = {1, 2, 3, 4, 5};
    dv.read(buf1, 5, littleEndian);
    EXPECT_EQ(dv.size(), 5u);

    const byte buf2[] = {10, 20};
    dv.read(buf2, 2, littleEndian);
    EXPECT_EQ(dv.size(), 2u);
    EXPECT_EQ(dv.count(), 2u);
}

// Test single byte value
TEST_F(DataValueTest_792, SingleByteValue_792) {
    DataValue dv(TypeId::undefined);
    const byte buf[] = {0x00};
    dv.read(buf, 1, littleEndian);
    EXPECT_EQ(dv.count(), 1u);
    EXPECT_EQ(dv.toInt64(0), 0);
}

// Test copy with byte order (should be ignored for DataValue)
TEST_F(DataValueTest_792, CopyWithDifferentByteOrder_792) {
    DataValue dv(TypeId::undefined);
    const byte input[] = {0x01, 0x02, 0x03};
    dv.read(input, 3, bigEndian);

    byte output_le[3] = {0};
    byte output_be[3] = {0};
    dv.copy(output_le, littleEndian);
    dv.copy(output_be, bigEndian);

    // DataValue should not reorder bytes
    EXPECT_EQ(output_le[0], output_be[0]);
    EXPECT_EQ(output_le[1], output_be[1]);
    EXPECT_EQ(output_le[2], output_be[2]);
}

// Test construction from buffer and parameters
TEST_F(DataValueTest_792, ConstructFromBuffer_792) {
    const byte buf[] = {0xDE, 0xAD, 0xBE, 0xEF};
    DataValue dv(buf, 4, littleEndian, TypeId::undefined);
    EXPECT_EQ(dv.size(), 4u);
    EXPECT_EQ(dv.count(), 4u);

    byte output[4] = {0};
    size_t copied = dv.copy(output, littleEndian);
    EXPECT_EQ(copied, 4u);
    EXPECT_EQ(output[0], 0xDE);
    EXPECT_EQ(output[1], 0xAD);
    EXPECT_EQ(output[2], 0xBE);
    EXPECT_EQ(output[3], 0xEF);
}

// Test large buffer
TEST_F(DataValueTest_792, LargeBuffer_792) {
    DataValue dv(TypeId::undefined);
    std::vector<byte> buf(1000, 0x42);
    int result = dv.read(buf.data(), buf.size(), littleEndian);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(dv.size(), 1000u);
    EXPECT_EQ(dv.count(), 1000u);
}

// Test toInt64 for boundary byte values
TEST_F(DataValueTest_792, ToInt64BoundaryValues_792) {
    DataValue dv(TypeId::undefined);
    const byte buf[] = {0, 127, 128, 255};
    dv.read(buf, 4, littleEndian);

    EXPECT_EQ(dv.toInt64(0), 0);
    EXPECT_EQ(dv.toInt64(1), 127);
    EXPECT_EQ(dv.toInt64(2), 128);
    EXPECT_EQ(dv.toInt64(3), 255);
}

// Test toUint32 for boundary byte values
TEST_F(DataValueTest_792, ToUint32BoundaryValues_792) {
    DataValue dv(TypeId::undefined);
    const byte buf[] = {0, 255};
    dv.read(buf, 2, littleEndian);

    EXPECT_EQ(dv.toUint32(0), 0u);
    EXPECT_EQ(dv.toUint32(1), 255u);
}

// Test read from string with single value
TEST_F(DataValueTest_792, ReadFromStringSingleValue_792) {
    DataValue dv(TypeId::undefined);
    int result = dv.read("FF");
    EXPECT_EQ(result, 0);
    EXPECT_GE(dv.count(), 1u);
}

// Test empty string read
TEST_F(DataValueTest_792, ReadFromEmptyString_792) {
    DataValue dv(TypeId::undefined);
    int result = dv.read("");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(dv.count(), 0u);
}

// Test toString with index 0 for multi-byte data
TEST_F(DataValueTest_792, ToStringMultipleBytesIndex0_792) {
    DataValue dv(TypeId::undefined);
    const byte buf[] = {0x41, 0x42, 0x43};
    dv.read(buf, 3, littleEndian);
    std::string s = dv.toString(0);
    EXPECT_FALSE(s.empty());
}

// Test write on empty DataValue
TEST_F(DataValueTest_792, WriteEmptyDataValue_792) {
    DataValue dv(TypeId::undefined);
    std::ostringstream os;
    dv.write(os);
    // Should not crash; output may be empty
}

// Test copy on empty DataValue
TEST_F(DataValueTest_792, CopyEmptyDataValue_792) {
    DataValue dv(TypeId::undefined);
    byte output[1] = {0xFF};
    size_t copied = dv.copy(output, littleEndian);
    EXPECT_EQ(copied, 0u);
}
