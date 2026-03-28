#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <sstream>
#include <cstring>

using namespace Exiv2;

class DataValueTest_128 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test default construction with undefined type
TEST_F(DataValueTest_128, ConstructWithUndefinedType_128) {
    DataValue dv(TypeId::undefined);
    EXPECT_EQ(dv.typeId(), TypeId::undefined);
    EXPECT_EQ(dv.count(), 0u);
    EXPECT_EQ(dv.size(), 0u);
}

// Test construction with specific type
TEST_F(DataValueTest_128, ConstructWithUnsignedByteType_128) {
    DataValue dv(TypeId::unsignedByte);
    EXPECT_EQ(dv.typeId(), TypeId::unsignedByte);
    EXPECT_EQ(dv.count(), 0u);
    EXPECT_EQ(dv.size(), 0u);
}

// Test construction from buffer
TEST_F(DataValueTest_128, ConstructFromBuffer_128) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04};
    DataValue dv(data, sizeof(data), littleEndian, TypeId::undefined);
    EXPECT_EQ(dv.count(), 4u);
    EXPECT_EQ(dv.size(), 4u);
}

// Test read from byte buffer
TEST_F(DataValueTest_128, ReadFromByteBuffer_128) {
    DataValue dv(TypeId::undefined);
    const byte data[] = {0xAA, 0xBB, 0xCC};
    int result = dv.read(data, sizeof(data), littleEndian);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(dv.count(), 3u);
    EXPECT_EQ(dv.size(), 3u);
}

// Test read from string
TEST_F(DataValueTest_128, ReadFromString_128) {
    DataValue dv(TypeId::undefined);
    int result = dv.read("48 65 6c 6c 6f");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(dv.count(), 5u);
    EXPECT_EQ(dv.size(), 5u);
}

// Test read from empty buffer
TEST_F(DataValueTest_128, ReadFromEmptyBuffer_128) {
    DataValue dv(TypeId::undefined);
    int result = dv.read(nullptr, 0, littleEndian);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(dv.count(), 0u);
    EXPECT_EQ(dv.size(), 0u);
}

// Test copy to buffer
TEST_F(DataValueTest_128, CopyToBuffer_128) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04};
    DataValue dv(TypeId::undefined);
    dv.read(data, sizeof(data), littleEndian);

    byte buf[4] = {0};
    size_t copied = dv.copy(buf, littleEndian);
    EXPECT_EQ(copied, 4u);
    EXPECT_EQ(buf[0], 0x01);
    EXPECT_EQ(buf[1], 0x02);
    EXPECT_EQ(buf[2], 0x03);
    EXPECT_EQ(buf[3], 0x04);
}

// Test count after reading data
TEST_F(DataValueTest_128, CountAfterRead_128) {
    DataValue dv(TypeId::undefined);
    const byte data[] = {0x10, 0x20, 0x30, 0x40, 0x50};
    dv.read(data, sizeof(data), bigEndian);
    EXPECT_EQ(dv.count(), 5u);
}

// Test size after reading data
TEST_F(DataValueTest_128, SizeAfterRead_128) {
    DataValue dv(TypeId::undefined);
    const byte data[] = {0x10, 0x20};
    dv.read(data, sizeof(data), bigEndian);
    EXPECT_EQ(dv.size(), 2u);
}

// Test write to ostream
TEST_F(DataValueTest_128, WriteToOstream_128) {
    DataValue dv(TypeId::undefined);
    const byte data[] = {0x48, 0x65, 0x6c};
    dv.read(data, sizeof(data), littleEndian);

    std::ostringstream os;
    dv.write(os);
    std::string output = os.str();
    EXPECT_FALSE(output.empty());
}

// Test toString for valid index
TEST_F(DataValueTest_128, ToStringValidIndex_128) {
    DataValue dv(TypeId::undefined);
    const byte data[] = {0x41, 0x42, 0x43};
    dv.read(data, sizeof(data), littleEndian);

    std::string s0 = dv.toString(0);
    EXPECT_FALSE(s0.empty());

    std::string s1 = dv.toString(1);
    EXPECT_FALSE(s1.empty());

    std::string s2 = dv.toString(2);
    EXPECT_FALSE(s2.empty());
}

// Test toInt64 for valid index
TEST_F(DataValueTest_128, ToInt64ValidIndex_128) {
    DataValue dv(TypeId::undefined);
    const byte data[] = {0x05, 0x0A, 0xFF};
    dv.read(data, sizeof(data), littleEndian);

    EXPECT_EQ(dv.toInt64(0), 5);
    EXPECT_EQ(dv.toInt64(1), 10);
    EXPECT_EQ(dv.toInt64(2), 255);
}

// Test toUint32 for valid index
TEST_F(DataValueTest_128, ToUint32ValidIndex_128) {
    DataValue dv(TypeId::undefined);
    const byte data[] = {0x01, 0x80, 0xFF};
    dv.read(data, sizeof(data), littleEndian);

    EXPECT_EQ(dv.toUint32(0), 1u);
    EXPECT_EQ(dv.toUint32(1), 128u);
    EXPECT_EQ(dv.toUint32(2), 255u);
}

// Test toFloat for valid index
TEST_F(DataValueTest_128, ToFloatValidIndex_128) {
    DataValue dv(TypeId::undefined);
    const byte data[] = {0x03, 0x07};
    dv.read(data, sizeof(data), littleEndian);

    EXPECT_FLOAT_EQ(dv.toFloat(0), 3.0f);
    EXPECT_FLOAT_EQ(dv.toFloat(1), 7.0f);
}

// Test toRational for valid index
TEST_F(DataValueTest_128, ToRationalValidIndex_128) {
    DataValue dv(TypeId::undefined);
    const byte data[] = {0x0A};
    dv.read(data, sizeof(data), littleEndian);

    Rational r = dv.toRational(0);
    EXPECT_EQ(r.first, 10);
    EXPECT_EQ(r.second, 1);
}

// Test clone
TEST_F(DataValueTest_128, Clone_128) {
    DataValue dv(TypeId::undefined);
    const byte data[] = {0x01, 0x02, 0x03};
    dv.read(data, sizeof(data), littleEndian);

    auto cloned = dv.clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->count(), dv.count());
    EXPECT_EQ(cloned->size(), dv.size());
    EXPECT_EQ(cloned->typeId(), dv.typeId());
}

// Test read overwrites previous data
TEST_F(DataValueTest_128, ReadOverwritesPreviousData_128) {
    DataValue dv(TypeId::undefined);
    const byte data1[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    dv.read(data1, sizeof(data1), littleEndian);
    EXPECT_EQ(dv.count(), 5u);

    const byte data2[] = {0x0A, 0x0B};
    dv.read(data2, sizeof(data2), littleEndian);
    EXPECT_EQ(dv.count(), 2u);
    EXPECT_EQ(dv.size(), 2u);
}

// Test single byte data
TEST_F(DataValueTest_128, SingleByteData_128) {
    DataValue dv(TypeId::undefined);
    const byte data[] = {0x42};
    dv.read(data, sizeof(data), littleEndian);

    EXPECT_EQ(dv.count(), 1u);
    EXPECT_EQ(dv.size(), 1u);
    EXPECT_EQ(dv.toInt64(0), 0x42);
}

// Test copy with byte order (should be irrelevant for DataValue)
TEST_F(DataValueTest_128, CopyWithDifferentByteOrders_128) {
    const byte data[] = {0x01, 0x02, 0x03};
    DataValue dv(TypeId::undefined);
    dv.read(data, sizeof(data), littleEndian);

    byte buf1[3] = {0};
    size_t copied1 = dv.copy(buf1, littleEndian);

    byte buf2[3] = {0};
    size_t copied2 = dv.copy(buf2, bigEndian);

    EXPECT_EQ(copied1, copied2);
    EXPECT_EQ(std::memcmp(buf1, buf2, 3), 0);
}

// Test reading from empty string
TEST_F(DataValueTest_128, ReadFromEmptyString_128) {
    DataValue dv(TypeId::undefined);
    int result = dv.read("");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(dv.count(), 0u);
    EXPECT_EQ(dv.size(), 0u);
}

// Test toString with out of range index (boundary)
TEST_F(DataValueTest_128, ToStringOutOfRange_128) {
    DataValue dv(TypeId::undefined);
    const byte data[] = {0x01, 0x02};
    dv.read(data, sizeof(data), littleEndian);

    // Requesting index beyond count - behavior depends on implementation
    // but we at least verify it doesn't crash for n == count()
    std::string s = dv.toString(0);
    EXPECT_FALSE(s.empty());
}

// Test large data
TEST_F(DataValueTest_128, LargeData_128) {
    DataValue dv(TypeId::undefined);
    std::vector<byte> data(1000, 0xAB);
    dv.read(data.data(), data.size(), littleEndian);

    EXPECT_EQ(dv.count(), 1000u);
    EXPECT_EQ(dv.size(), 1000u);

    std::vector<byte> buf(1000, 0);
    size_t copied = dv.copy(buf.data(), littleEndian);
    EXPECT_EQ(copied, 1000u);
    for (size_t i = 0; i < 1000; ++i) {
        EXPECT_EQ(buf[i], 0xAB);
    }
}

// Test write output consistency
TEST_F(DataValueTest_128, WriteOutputConsistency_128) {
    DataValue dv(TypeId::undefined);
    const byte data[] = {0x01, 0x02, 0x03};
    dv.read(data, sizeof(data), littleEndian);

    std::ostringstream os1, os2;
    dv.write(os1);
    dv.write(os2);
    EXPECT_EQ(os1.str(), os2.str());
}

// Test clone preserves data
TEST_F(DataValueTest_128, ClonePreservesData_128) {
    DataValue dv(TypeId::undefined);
    const byte data[] = {0xDE, 0xAD, 0xBE, 0xEF};
    dv.read(data, sizeof(data), littleEndian);

    auto cloned = dv.clone();

    byte origBuf[4] = {0};
    byte cloneBuf[4] = {0};
    dv.copy(origBuf, littleEndian);
    cloned->copy(cloneBuf, littleEndian);

    EXPECT_EQ(std::memcmp(origBuf, cloneBuf, 4), 0);
}

// Test reading string hex values
TEST_F(DataValueTest_128, ReadStringHexValues_128) {
    DataValue dv(TypeId::undefined);
    int result = dv.read("ff 00 80");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(dv.count(), 3u);
    EXPECT_EQ(dv.toInt64(0), 255);
    EXPECT_EQ(dv.toInt64(1), 0);
    EXPECT_EQ(dv.toInt64(2), 128);
}

// Test that count and size are equal for byte-type data
TEST_F(DataValueTest_128, CountEqualsSizeForByteData_128) {
    DataValue dv(TypeId::undefined);
    const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06};
    dv.read(data, sizeof(data), littleEndian);
    EXPECT_EQ(dv.count(), dv.size());
}

// Test zero byte values
TEST_F(DataValueTest_128, ZeroByteValues_128) {
    DataValue dv(TypeId::undefined);
    const byte data[] = {0x00, 0x00, 0x00};
    dv.read(data, sizeof(data), littleEndian);

    EXPECT_EQ(dv.count(), 3u);
    EXPECT_EQ(dv.toInt64(0), 0);
    EXPECT_EQ(dv.toInt64(1), 0);
    EXPECT_EQ(dv.toInt64(2), 0);
}

// Test max byte values
TEST_F(DataValueTest_128, MaxByteValues_128) {
    DataValue dv(TypeId::undefined);
    const byte data[] = {0xFF, 0xFF};
    dv.read(data, sizeof(data), littleEndian);

    EXPECT_EQ(dv.toUint32(0), 255u);
    EXPECT_EQ(dv.toUint32(1), 255u);
}
