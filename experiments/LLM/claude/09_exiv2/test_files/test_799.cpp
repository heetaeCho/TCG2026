#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <cstring>
#include <sstream>
#include <vector>

using namespace Exiv2;

class DataValueTest_799 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test default construction with undefined type
TEST_F(DataValueTest_799, ConstructWithUndefinedType_799) {
    DataValue dv(TypeId::undefined);
    EXPECT_EQ(dv.typeId(), TypeId::undefined);
    EXPECT_EQ(dv.count(), 0u);
    EXPECT_EQ(dv.size(), 0u);
}

// Test construction with byte buffer
TEST_F(DataValueTest_799, ConstructWithByteBuffer_799) {
    const byte buf[] = {0x01, 0x02, 0x03, 0x04};
    DataValue dv(buf, sizeof(buf), littleEndian, TypeId::undefined);
    EXPECT_EQ(dv.typeId(), TypeId::undefined);
    EXPECT_EQ(dv.count(), 4u);
    EXPECT_EQ(dv.size(), 4u);
}

// Test read from byte buffer
TEST_F(DataValueTest_799, ReadFromByteBuffer_799) {
    DataValue dv(TypeId::undefined);
    const byte buf[] = {0x0A, 0x0B, 0x0C};
    int result = dv.read(buf, sizeof(buf), littleEndian);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(dv.count(), 3u);
    EXPECT_EQ(dv.size(), 3u);
}

// Test read from string
TEST_F(DataValueTest_799, ReadFromString_799) {
    DataValue dv(TypeId::undefined);
    std::string input = "48 49 50";
    int result = dv.read(input);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(dv.count(), 3u);
}

// Test toInt64 with valid index
TEST_F(DataValueTest_799, ToInt64ValidIndex_799) {
    const byte buf[] = {0x05, 0x0A, 0xFF};
    DataValue dv(buf, sizeof(buf), littleEndian, TypeId::undefined);
    EXPECT_EQ(dv.toInt64(0), 0x05);
    EXPECT_EQ(dv.toInt64(1), 0x0A);
    EXPECT_EQ(dv.toInt64(2), 0xFF);
    EXPECT_TRUE(dv.ok());
}

// Test toInt64 with out-of-range index throws
TEST_F(DataValueTest_799, ToInt64OutOfRange_799) {
    const byte buf[] = {0x01, 0x02};
    DataValue dv(buf, sizeof(buf), littleEndian, TypeId::undefined);
    EXPECT_THROW(dv.toInt64(5), std::out_of_range);
}

// Test toUint32 with valid index
TEST_F(DataValueTest_799, ToUint32ValidIndex_799) {
    const byte buf[] = {0x00, 0x7F, 0xFF};
    DataValue dv(buf, sizeof(buf), littleEndian, TypeId::undefined);
    EXPECT_EQ(dv.toUint32(0), 0x00u);
    EXPECT_EQ(dv.toUint32(1), 0x7Fu);
    EXPECT_EQ(dv.toUint32(2), 0xFFu);
    EXPECT_TRUE(dv.ok());
}

// Test toFloat with valid index
TEST_F(DataValueTest_799, ToFloatValidIndex_799) {
    const byte buf[] = {0x03, 0x06};
    DataValue dv(buf, sizeof(buf), littleEndian, TypeId::undefined);
    EXPECT_FLOAT_EQ(dv.toFloat(0), 3.0f);
    EXPECT_FLOAT_EQ(dv.toFloat(1), 6.0f);
    EXPECT_TRUE(dv.ok());
}

// Test toRational with valid index
TEST_F(DataValueTest_799, ToRationalValidIndex_799) {
    const byte buf[] = {0x0A};
    DataValue dv(buf, sizeof(buf), littleEndian, TypeId::undefined);
    Rational r = dv.toRational(0);
    EXPECT_EQ(r.first, 0x0A);
    EXPECT_EQ(r.second, 1);
}

// Test copy method
TEST_F(DataValueTest_799, CopyToBuffer_799) {
    const byte buf[] = {0x01, 0x02, 0x03};
    DataValue dv(buf, sizeof(buf), littleEndian, TypeId::undefined);
    byte outBuf[3] = {0};
    size_t copied = dv.copy(outBuf, littleEndian);
    EXPECT_EQ(copied, 3u);
    EXPECT_EQ(outBuf[0], 0x01);
    EXPECT_EQ(outBuf[1], 0x02);
    EXPECT_EQ(outBuf[2], 0x03);
}

// Test write to ostream
TEST_F(DataValueTest_799, WriteToStream_799) {
    const byte buf[] = {0x01, 0x02, 0x03};
    DataValue dv(buf, sizeof(buf), littleEndian, TypeId::undefined);
    std::ostringstream os;
    dv.write(os);
    std::string output = os.str();
    EXPECT_FALSE(output.empty());
}

// Test toString with valid index
TEST_F(DataValueTest_799, ToStringValidIndex_799) {
    const byte buf[] = {0x41}; // 'A' = 65
    DataValue dv(buf, sizeof(buf), littleEndian, TypeId::undefined);
    std::string str = dv.toString(0);
    EXPECT_EQ(str, "65");
}

// Test clone produces independent copy
TEST_F(DataValueTest_799, CloneProducesIndependentCopy_799) {
    const byte buf[] = {0x01, 0x02, 0x03};
    DataValue dv(buf, sizeof(buf), littleEndian, TypeId::undefined);
    auto cloned = dv.clone();
    EXPECT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->count(), dv.count());
    EXPECT_EQ(cloned->typeId(), dv.typeId());
}

// Test empty DataValue
TEST_F(DataValueTest_799, EmptyDataValue_799) {
    DataValue dv(TypeId::undefined);
    EXPECT_EQ(dv.count(), 0u);
    EXPECT_EQ(dv.size(), 0u);
    std::ostringstream os;
    dv.write(os);
    EXPECT_TRUE(os.str().empty());
}

// Test read from empty byte buffer
TEST_F(DataValueTest_799, ReadEmptyByteBuffer_799) {
    DataValue dv(TypeId::undefined);
    int result = dv.read(nullptr, 0, littleEndian);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(dv.count(), 0u);
}

// Test read from string with single value
TEST_F(DataValueTest_799, ReadFromStringSingleValue_799) {
    DataValue dv(TypeId::undefined);
    std::string input = "255";
    int result = dv.read(input);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(dv.count(), 1u);
    EXPECT_EQ(dv.toInt64(0), 255);
}

// Test overwriting data with new read
TEST_F(DataValueTest_799, OverwriteWithNewRead_799) {
    DataValue dv(TypeId::undefined);
    const byte buf1[] = {0x01, 0x02};
    dv.read(buf1, sizeof(buf1), littleEndian);
    EXPECT_EQ(dv.count(), 2u);

    const byte buf2[] = {0x03, 0x04, 0x05};
    dv.read(buf2, sizeof(buf2), littleEndian);
    EXPECT_EQ(dv.count(), 3u);
    EXPECT_EQ(dv.toInt64(0), 0x03);
}

// Test ok() returns true after successful toInt64
TEST_F(DataValueTest_799, OkAfterSuccessfulToInt64_799) {
    const byte buf[] = {0x42};
    DataValue dv(buf, sizeof(buf), littleEndian, TypeId::undefined);
    int64_t val = dv.toInt64(0);
    EXPECT_TRUE(dv.ok());
    EXPECT_EQ(val, 0x42);
}

// Test with boundary byte values
TEST_F(DataValueTest_799, BoundaryByteValues_799) {
    const byte buf[] = {0x00, 0xFF};
    DataValue dv(buf, sizeof(buf), littleEndian, TypeId::undefined);
    EXPECT_EQ(dv.toInt64(0), 0);
    EXPECT_EQ(dv.toInt64(1), 255);
    EXPECT_EQ(dv.toUint32(0), 0u);
    EXPECT_EQ(dv.toUint32(1), 255u);
}

// Test large buffer
TEST_F(DataValueTest_799, LargeBuffer_799) {
    std::vector<byte> buf(1000, 0x7F);
    DataValue dv(buf.data(), buf.size(), littleEndian, TypeId::undefined);
    EXPECT_EQ(dv.count(), 1000u);
    EXPECT_EQ(dv.size(), 1000u);
    EXPECT_EQ(dv.toInt64(0), 0x7F);
    EXPECT_EQ(dv.toInt64(999), 0x7F);
}

// Test copy returns correct size
TEST_F(DataValueTest_799, CopyReturnsCorrectSize_799) {
    const byte buf[] = {0xAA, 0xBB, 0xCC, 0xDD, 0xEE};
    DataValue dv(buf, sizeof(buf), littleEndian, TypeId::undefined);
    byte outBuf[5] = {0};
    size_t copied = dv.copy(outBuf, bigEndian);
    EXPECT_EQ(copied, 5u);
    for (size_t i = 0; i < 5; ++i) {
        EXPECT_EQ(outBuf[i], buf[i]);
    }
}

// Test sizeDataArea returns 0 for DataValue (inherited default)
TEST_F(DataValueTest_799, SizeDataAreaDefault_799) {
    DataValue dv(TypeId::undefined);
    EXPECT_EQ(dv.sizeDataArea(), 0u);
}

// Test dataArea returns empty for DataValue (inherited default)
TEST_F(DataValueTest_799, DataAreaDefault_799) {
    DataValue dv(TypeId::undefined);
    DataBuf db = dv.dataArea();
    EXPECT_EQ(db.size(), 0u);
}

// Test read from string with multiple space-separated hex values
TEST_F(DataValueTest_799, ReadFromStringMultipleValues_799) {
    DataValue dv(TypeId::undefined);
    std::string input = "0 128 255";
    int result = dv.read(input);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(dv.count(), 3u);
    EXPECT_EQ(dv.toInt64(0), 0);
    EXPECT_EQ(dv.toInt64(1), 128);
    EXPECT_EQ(dv.toInt64(2), 255);
}

// Test toString base (no arg) on DataValue
TEST_F(DataValueTest_799, ToStringBase_799) {
    const byte buf[] = {0x41, 0x42};
    DataValue dv(buf, sizeof(buf), littleEndian, TypeId::undefined);
    std::string str = dv.toString();
    EXPECT_FALSE(str.empty());
}
