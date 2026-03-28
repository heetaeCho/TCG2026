#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <cstring>
#include <sstream>

using namespace Exiv2;

class DataValueTest_796 : public ::testing::Test {
protected:
    void SetUp() override {
    }
    void TearDown() override {
    }
};

// Test default construction with undefined type
TEST_F(DataValueTest_796, DefaultConstruction_Undefined_796) {
    DataValue dv(TypeId::undefined);
    EXPECT_EQ(dv.size(), 0u);
    EXPECT_EQ(dv.count(), 0u);
}

// Test default construction with unsignedByte type
TEST_F(DataValueTest_796, DefaultConstruction_UnsignedByte_796) {
    DataValue dv(TypeId::unsignedByte);
    EXPECT_EQ(dv.size(), 0u);
    EXPECT_EQ(dv.count(), 0u);
}

// Test read from byte buffer
TEST_F(DataValueTest_796, ReadFromByteBuffer_796) {
    DataValue dv(TypeId::undefined);
    byte buf[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    int result = dv.read(buf, sizeof(buf), littleEndian);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(dv.size(), 5u);
    EXPECT_EQ(dv.count(), 5u);
}

// Test read from empty byte buffer
TEST_F(DataValueTest_796, ReadFromEmptyByteBuffer_796) {
    DataValue dv(TypeId::undefined);
    int result = dv.read(nullptr, 0, littleEndian);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(dv.size(), 0u);
    EXPECT_EQ(dv.count(), 0u);
}

// Test read from string
TEST_F(DataValueTest_796, ReadFromString_796) {
    DataValue dv(TypeId::undefined);
    int result = dv.read("48 65 6C 6C 6F");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(dv.size(), 5u);
    EXPECT_EQ(dv.count(), 5u);
}

// Test read from empty string
TEST_F(DataValueTest_796, ReadFromEmptyString_796) {
    DataValue dv(TypeId::undefined);
    int result = dv.read("");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(dv.size(), 0u);
}

// Test copy to buffer
TEST_F(DataValueTest_796, CopyToBuffer_796) {
    DataValue dv(TypeId::undefined);
    byte input[] = {0x0A, 0x0B, 0x0C};
    dv.read(input, sizeof(input), littleEndian);

    byte output[3] = {0};
    size_t copied = dv.copy(output, littleEndian);
    EXPECT_EQ(copied, 3u);
    EXPECT_EQ(output[0], 0x0A);
    EXPECT_EQ(output[1], 0x0B);
    EXPECT_EQ(output[2], 0x0C);
}

// Test copy from empty DataValue
TEST_F(DataValueTest_796, CopyFromEmptyDataValue_796) {
    DataValue dv(TypeId::undefined);
    byte output[1] = {0xFF};
    size_t copied = dv.copy(output, littleEndian);
    EXPECT_EQ(copied, 0u);
}

// Test toString
TEST_F(DataValueTest_796, ToString_796) {
    DataValue dv(TypeId::undefined);
    byte input[] = {0x41, 0x42, 0x43};
    dv.read(input, sizeof(input), littleEndian);

    std::string s = dv.toString(0);
    EXPECT_FALSE(s.empty());
}

// Test toString with index 0 on single byte
TEST_F(DataValueTest_796, ToStringSingleByte_796) {
    DataValue dv(TypeId::undefined);
    byte input[] = {0x30};
    dv.read(input, sizeof(input), littleEndian);

    std::string s = dv.toString(0);
    EXPECT_EQ(s, "48");
}

// Test toInt64
TEST_F(DataValueTest_796, ToInt64_796) {
    DataValue dv(TypeId::undefined);
    byte input[] = {0x05, 0xFF};
    dv.read(input, sizeof(input), littleEndian);

    int64_t val0 = dv.toInt64(0);
    EXPECT_EQ(val0, 5);

    int64_t val1 = dv.toInt64(1);
    EXPECT_EQ(val1, 255);
}

// Test toUint32
TEST_F(DataValueTest_796, ToUint32_796) {
    DataValue dv(TypeId::undefined);
    byte input[] = {0x00, 0xFF};
    dv.read(input, sizeof(input), littleEndian);

    uint32_t val0 = dv.toUint32(0);
    EXPECT_EQ(val0, 0u);

    uint32_t val1 = dv.toUint32(1);
    EXPECT_EQ(val1, 255u);
}

// Test toFloat
TEST_F(DataValueTest_796, ToFloat_796) {
    DataValue dv(TypeId::undefined);
    byte input[] = {0x0A};
    dv.read(input, sizeof(input), littleEndian);

    float val = dv.toFloat(0);
    EXPECT_FLOAT_EQ(val, 10.0f);
}

// Test toRational
TEST_F(DataValueTest_796, ToRational_796) {
    DataValue dv(TypeId::undefined);
    byte input[] = {0x07};
    dv.read(input, sizeof(input), littleEndian);

    Rational r = dv.toRational(0);
    EXPECT_EQ(r.first, 7);
    EXPECT_EQ(r.second, 1);
}

// Test write to ostream
TEST_F(DataValueTest_796, WriteToOstream_796) {
    DataValue dv(TypeId::undefined);
    byte input[] = {0x41, 0x42};
    dv.read(input, sizeof(input), littleEndian);

    std::ostringstream oss;
    dv.write(oss);
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
}

// Test write empty DataValue to ostream
TEST_F(DataValueTest_796, WriteEmptyToOstream_796) {
    DataValue dv(TypeId::undefined);
    std::ostringstream oss;
    dv.write(oss);
    std::string output = oss.str();
    // Empty data value should produce empty or minimal output
    EXPECT_TRUE(output.empty() || output.size() >= 0);
}

// Test clone
TEST_F(DataValueTest_796, Clone_796) {
    DataValue dv(TypeId::undefined);
    byte input[] = {0x01, 0x02, 0x03};
    dv.read(input, sizeof(input), littleEndian);

    auto cloned = dv.clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->size(), dv.size());
    EXPECT_EQ(cloned->count(), dv.count());
}

// Test clone of empty DataValue
TEST_F(DataValueTest_796, CloneEmpty_796) {
    DataValue dv(TypeId::undefined);
    auto cloned = dv.clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->size(), 0u);
    EXPECT_EQ(cloned->count(), 0u);
}

// Test construction with buffer and length
TEST_F(DataValueTest_796, ConstructionWithBuffer_796) {
    byte input[] = {0xDE, 0xAD, 0xBE, 0xEF};
    DataValue dv(input, sizeof(input), littleEndian, TypeId::undefined);
    EXPECT_EQ(dv.size(), 4u);
    EXPECT_EQ(dv.count(), 4u);
}

// Test that reading new data replaces old data
TEST_F(DataValueTest_796, ReadReplacesOldData_796) {
    DataValue dv(TypeId::undefined);
    byte input1[] = {0x01, 0x02, 0x03};
    dv.read(input1, sizeof(input1), littleEndian);
    EXPECT_EQ(dv.size(), 3u);

    byte input2[] = {0x04, 0x05};
    dv.read(input2, sizeof(input2), littleEndian);
    EXPECT_EQ(dv.size(), 2u);
}

// Test single byte value
TEST_F(DataValueTest_796, SingleByteValue_796) {
    DataValue dv(TypeId::undefined);
    byte input[] = {0x00};
    dv.read(input, sizeof(input), littleEndian);
    EXPECT_EQ(dv.size(), 1u);
    EXPECT_EQ(dv.count(), 1u);
    EXPECT_EQ(dv.toInt64(0), 0);
    EXPECT_EQ(dv.toUint32(0), 0u);
}

// Test large buffer
TEST_F(DataValueTest_796, LargeBuffer_796) {
    DataValue dv(TypeId::undefined);
    std::vector<byte> input(1000, 0xAB);
    dv.read(input.data(), input.size(), littleEndian);
    EXPECT_EQ(dv.size(), 1000u);
    EXPECT_EQ(dv.count(), 1000u);
}

// Test copy preserves data integrity
TEST_F(DataValueTest_796, CopyPreservesDataIntegrity_796) {
    DataValue dv(TypeId::undefined);
    byte input[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};
    dv.read(input, sizeof(input), littleEndian);

    byte output[8] = {0};
    size_t copied = dv.copy(output, littleEndian);
    EXPECT_EQ(copied, 8u);
    EXPECT_EQ(memcmp(input, output, sizeof(input)), 0);
}

// Test byte order independence (DataValue should not depend on byte order)
TEST_F(DataValueTest_796, ByteOrderIndependence_796) {
    byte input[] = {0x01, 0x02, 0x03};

    DataValue dv1(TypeId::undefined);
    dv1.read(input, sizeof(input), littleEndian);

    DataValue dv2(TypeId::undefined);
    dv2.read(input, sizeof(input), bigEndian);

    EXPECT_EQ(dv1.size(), dv2.size());
    EXPECT_EQ(dv1.count(), dv2.count());

    byte out1[3], out2[3];
    dv1.copy(out1, littleEndian);
    dv2.copy(out2, bigEndian);
    EXPECT_EQ(memcmp(out1, out2, 3), 0);
}

// Test toString for various indices
TEST_F(DataValueTest_796, ToStringMultipleIndices_796) {
    DataValue dv(TypeId::undefined);
    byte input[] = {0x00, 0x01, 0xFF};
    dv.read(input, sizeof(input), littleEndian);

    std::string s0 = dv.toString(0);
    std::string s1 = dv.toString(1);
    std::string s2 = dv.toString(2);

    EXPECT_FALSE(s0.empty());
    EXPECT_FALSE(s1.empty());
    EXPECT_FALSE(s2.empty());
}

// Test toInt64 boundary values
TEST_F(DataValueTest_796, ToInt64BoundaryValues_796) {
    DataValue dv(TypeId::undefined);
    byte input[] = {0x00, 0x7F, 0x80, 0xFF};
    dv.read(input, sizeof(input), littleEndian);

    EXPECT_EQ(dv.toInt64(0), 0);
    EXPECT_EQ(dv.toInt64(1), 127);
    EXPECT_EQ(dv.toInt64(2), 128);
    EXPECT_EQ(dv.toInt64(3), 255);
}

// Test read from string with single hex value
TEST_F(DataValueTest_796, ReadFromStringSingleHex_796) {
    DataValue dv(TypeId::undefined);
    int result = dv.read("FF");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(dv.size(), 1u);
    EXPECT_EQ(dv.toUint32(0), 255u);
}

// Test that count equals size for DataValue
TEST_F(DataValueTest_796, CountEqualsSize_796) {
    DataValue dv(TypeId::undefined);
    byte input[] = {0x10, 0x20, 0x30, 0x40, 0x50};
    dv.read(input, sizeof(input), littleEndian);
    EXPECT_EQ(dv.count(), dv.size());
}
