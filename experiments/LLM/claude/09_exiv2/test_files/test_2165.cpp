#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <sstream>
#include <vector>
#include <cstring>

using namespace Exiv2;

// Test fixture for DataValue tests
class DataValueTest_2165 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test default construction with a specific TypeId
TEST_F(DataValueTest_2165, DefaultConstruction_UndefinedType_2165) {
    DataValue dv(undefined);
    EXPECT_EQ(dv.typeId(), undefined);
    EXPECT_EQ(dv.count(), 0u);
    EXPECT_EQ(dv.size(), 0u);
}

// Test construction with byte buffer
TEST_F(DataValueTest_2165, ConstructionWithBuffer_2165) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04};
    DataValue dv(data, sizeof(data), littleEndian, undefined);
    EXPECT_EQ(dv.typeId(), undefined);
    EXPECT_EQ(dv.count(), 4u);
    EXPECT_EQ(dv.size(), 4u);
}

// Test read from byte buffer
TEST_F(DataValueTest_2165, ReadFromByteBuffer_2165) {
    DataValue dv(undefined);
    const byte data[] = {0xAA, 0xBB, 0xCC};
    int result = dv.read(data, sizeof(data), littleEndian);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(dv.count(), 3u);
    EXPECT_EQ(dv.size(), 3u);
}

// Test read from string
TEST_F(DataValueTest_2165, ReadFromString_2165) {
    DataValue dv(undefined);
    std::string buf = "48 65 6C 6C 6F";  // "Hello" in hex
    int result = dv.read(buf);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(dv.count(), 5u);
    EXPECT_EQ(dv.size(), 5u);
}

// Test copy to byte buffer
TEST_F(DataValueTest_2165, CopyToBuffer_2165) {
    const byte data[] = {0x01, 0x02, 0x03};
    DataValue dv(data, sizeof(data), littleEndian, undefined);
    
    byte buf[3] = {0};
    size_t copied = dv.copy(buf, littleEndian);
    EXPECT_EQ(copied, 3u);
    EXPECT_EQ(buf[0], 0x01);
    EXPECT_EQ(buf[1], 0x02);
    EXPECT_EQ(buf[2], 0x03);
}

// Test count returns correct number of bytes
TEST_F(DataValueTest_2165, CountReturnsNumberOfBytes_2165) {
    const byte data[] = {0x10, 0x20, 0x30, 0x40, 0x50};
    DataValue dv(data, sizeof(data), bigEndian, undefined);
    EXPECT_EQ(dv.count(), 5u);
}

// Test size returns correct size
TEST_F(DataValueTest_2165, SizeReturnsCorrectSize_2165) {
    const byte data[] = {0xFF, 0xFE};
    DataValue dv(data, sizeof(data), littleEndian, undefined);
    EXPECT_EQ(dv.size(), 2u);
}

// Test write to output stream
TEST_F(DataValueTest_2165, WriteToOutputStream_2165) {
    const byte data[] = {0x01, 0x02, 0x03};
    DataValue dv(data, sizeof(data), littleEndian, undefined);
    
    std::ostringstream os;
    dv.write(os);
    std::string output = os.str();
    EXPECT_FALSE(output.empty());
}

// Test toString for specific index
TEST_F(DataValueTest_2165, ToStringAtIndex_2165) {
    const byte data[] = {0x41};  // 'A' = 65
    DataValue dv(data, sizeof(data), littleEndian, undefined);
    
    std::string str = dv.toString(0);
    EXPECT_FALSE(str.empty());
}

// Test toInt64 conversion
TEST_F(DataValueTest_2165, ToInt64Conversion_2165) {
    const byte data[] = {0x05};
    DataValue dv(data, sizeof(data), littleEndian, undefined);
    
    int64_t val = dv.toInt64(0);
    EXPECT_EQ(val, 5);
}

// Test toUint32 conversion
TEST_F(DataValueTest_2165, ToUint32Conversion_2165) {
    const byte data[] = {0xFF};
    DataValue dv(data, sizeof(data), littleEndian, undefined);
    
    uint32_t val = dv.toUint32(0);
    EXPECT_EQ(val, 255u);
}

// Test toFloat conversion
TEST_F(DataValueTest_2165, ToFloatConversion_2165) {
    const byte data[] = {0x0A};
    DataValue dv(data, sizeof(data), littleEndian, undefined);
    
    float val = dv.toFloat(0);
    EXPECT_FLOAT_EQ(val, 10.0f);
}

// Test toRational conversion
TEST_F(DataValueTest_2165, ToRationalConversion_2165) {
    const byte data[] = {0x07};
    DataValue dv(data, sizeof(data), littleEndian, undefined);
    
    Rational rat = dv.toRational(0);
    EXPECT_EQ(rat.first, 7);
    EXPECT_EQ(rat.second, 1);
}

// Test clone creates a proper copy
TEST_F(DataValueTest_2165, CloneCreatesCopy_2165) {
    const byte data[] = {0x01, 0x02, 0x03};
    DataValue dv(data, sizeof(data), littleEndian, undefined);
    
    auto cloned = dv.clone();
    EXPECT_NE(cloned.get(), nullptr);
    EXPECT_EQ(cloned->typeId(), undefined);
    EXPECT_EQ(cloned->count(), 3u);
    EXPECT_EQ(cloned->size(), 3u);
}

// Test empty data
TEST_F(DataValueTest_2165, EmptyDataValue_2165) {
    DataValue dv(undefined);
    EXPECT_EQ(dv.count(), 0u);
    EXPECT_EQ(dv.size(), 0u);
}

// Test read with zero-length buffer
TEST_F(DataValueTest_2165, ReadZeroLengthBuffer_2165) {
    DataValue dv(undefined);
    const byte data[] = {0x00};
    int result = dv.read(data, 0, littleEndian);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(dv.count(), 0u);
    EXPECT_EQ(dv.size(), 0u);
}

// Test read overwrites previous data
TEST_F(DataValueTest_2165, ReadOverwritesPreviousData_2165) {
    const byte data1[] = {0x01, 0x02, 0x03};
    DataValue dv(data1, sizeof(data1), littleEndian, undefined);
    EXPECT_EQ(dv.count(), 3u);
    
    const byte data2[] = {0x04, 0x05};
    dv.read(data2, sizeof(data2), littleEndian);
    EXPECT_EQ(dv.count(), 2u);
    EXPECT_EQ(dv.size(), 2u);
}

// Test with single byte
TEST_F(DataValueTest_2165, SingleByteData_2165) {
    const byte data[] = {0x42};
    DataValue dv(data, 1, littleEndian, undefined);
    EXPECT_EQ(dv.count(), 1u);
    EXPECT_EQ(dv.size(), 1u);
    EXPECT_EQ(dv.toInt64(0), 0x42);
}

// Test copy preserves data integrity
TEST_F(DataValueTest_2165, CopyPreservesDataIntegrity_2165) {
    const byte data[] = {0x00, 0x7F, 0x80, 0xFF};
    DataValue dv(data, sizeof(data), littleEndian, undefined);
    
    byte buf[4] = {0};
    size_t copied = dv.copy(buf, littleEndian);
    EXPECT_EQ(copied, 4u);
    EXPECT_EQ(std::memcmp(data, buf, 4), 0);
}

// Test with big endian byte order (DataValue should be byte-order independent)
TEST_F(DataValueTest_2165, BigEndianByteOrder_2165) {
    const byte data[] = {0x01, 0x02, 0x03};
    DataValue dv(data, sizeof(data), bigEndian, undefined);
    EXPECT_EQ(dv.count(), 3u);
    EXPECT_EQ(dv.size(), 3u);
    
    byte buf[3] = {0};
    dv.copy(buf, bigEndian);
    EXPECT_EQ(buf[0], 0x01);
    EXPECT_EQ(buf[1], 0x02);
    EXPECT_EQ(buf[2], 0x03);
}

// Test ok() returns true after valid construction
TEST_F(DataValueTest_2165, OkReturnsTrueAfterValidConstruction_2165) {
    const byte data[] = {0x01, 0x02};
    DataValue dv(data, sizeof(data), littleEndian, undefined);
    EXPECT_TRUE(dv.ok());
}

// Test typeId returns the correct type
TEST_F(DataValueTest_2165, TypeIdReturnsCorrectType_2165) {
    DataValue dv(undefined);
    EXPECT_EQ(dv.typeId(), undefined);
}

// Test read from string with empty string
TEST_F(DataValueTest_2165, ReadFromEmptyString_2165) {
    DataValue dv(undefined);
    std::string buf = "";
    int result = dv.read(buf);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(dv.count(), 0u);
}

// Test write to stream for empty data
TEST_F(DataValueTest_2165, WriteEmptyData_2165) {
    DataValue dv(undefined);
    std::ostringstream os;
    dv.write(os);
    // Empty data should produce empty or minimal output
    // Just verifying no crash
}

// Test large buffer
TEST_F(DataValueTest_2165, LargeBuffer_2165) {
    std::vector<byte> data(1000, 0xAB);
    DataValue dv(data.data(), data.size(), littleEndian, undefined);
    EXPECT_EQ(dv.count(), 1000u);
    EXPECT_EQ(dv.size(), 1000u);
    
    std::vector<byte> buf(1000, 0);
    size_t copied = dv.copy(buf.data(), littleEndian);
    EXPECT_EQ(copied, 1000u);
    for (size_t i = 0; i < 1000; ++i) {
        EXPECT_EQ(buf[i], 0xAB);
    }
}

// Test toInt64 with multiple elements
TEST_F(DataValueTest_2165, ToInt64MultipleElements_2165) {
    const byte data[] = {0x0A, 0x14, 0x1E};
    DataValue dv(data, sizeof(data), littleEndian, undefined);
    
    EXPECT_EQ(dv.toInt64(0), 0x0A);
    EXPECT_EQ(dv.toInt64(1), 0x14);
    EXPECT_EQ(dv.toInt64(2), 0x1E);
}

// Test toUint32 with multiple elements
TEST_F(DataValueTest_2165, ToUint32MultipleElements_2165) {
    const byte data[] = {0x00, 0x80, 0xFF};
    DataValue dv(data, sizeof(data), littleEndian, undefined);
    
    EXPECT_EQ(dv.toUint32(0), 0u);
    EXPECT_EQ(dv.toUint32(1), 128u);
    EXPECT_EQ(dv.toUint32(2), 255u);
}

// Test toFloat with multiple elements
TEST_F(DataValueTest_2165, ToFloatMultipleElements_2165) {
    const byte data[] = {0x00, 0x01, 0x02};
    DataValue dv(data, sizeof(data), littleEndian, undefined);
    
    EXPECT_FLOAT_EQ(dv.toFloat(0), 0.0f);
    EXPECT_FLOAT_EQ(dv.toFloat(1), 1.0f);
    EXPECT_FLOAT_EQ(dv.toFloat(2), 2.0f);
}

// Test read from string with hex values
TEST_F(DataValueTest_2165, ReadFromStringHexValues_2165) {
    DataValue dv(undefined);
    std::string buf = "FF 00 AB";
    int result = dv.read(buf);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(dv.count(), 3u);
    
    EXPECT_EQ(dv.toUint32(0), 0xFF);
    EXPECT_EQ(dv.toUint32(1), 0x00);
    EXPECT_EQ(dv.toUint32(2), 0xAB);
}

// Test sizeDataArea returns 0 for DataValue
TEST_F(DataValueTest_2165, SizeDataAreaReturnsZero_2165) {
    DataValue dv(undefined);
    EXPECT_EQ(dv.sizeDataArea(), 0u);
}

// Test toString (no index) returns non-empty for data with values
TEST_F(DataValueTest_2165, ToStringNoIndex_2165) {
    const byte data[] = {0x41, 0x42};
    DataValue dv(data, sizeof(data), littleEndian, undefined);
    std::string str = dv.toString();
    EXPECT_FALSE(str.empty());
}

// Test value_ is accessible and reflects data
TEST_F(DataValueTest_2165, ValueMemberReflectsData_2165) {
    const byte data[] = {0x01, 0x02, 0x03};
    DataValue dv(data, sizeof(data), littleEndian, undefined);
    EXPECT_EQ(dv.value_.size(), 3u);
    EXPECT_EQ(dv.value_[0], 0x01);
    EXPECT_EQ(dv.value_[1], 0x02);
    EXPECT_EQ(dv.value_[2], 0x03);
}

// Test construction with different byte orders produces same result for DataValue
TEST_F(DataValueTest_2165, ByteOrderIndependence_2165) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04};
    DataValue dv_le(data, sizeof(data), littleEndian, undefined);
    DataValue dv_be(data, sizeof(data), bigEndian, undefined);
    
    EXPECT_EQ(dv_le.count(), dv_be.count());
    EXPECT_EQ(dv_le.size(), dv_be.size());
    
    byte buf_le[4] = {0};
    byte buf_be[4] = {0};
    dv_le.copy(buf_le, littleEndian);
    dv_be.copy(buf_be, bigEndian);
    EXPECT_EQ(std::memcmp(buf_le, buf_be, 4), 0);
}
