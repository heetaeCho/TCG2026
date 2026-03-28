#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <sstream>
#include <vector>
#include <stdexcept>

using namespace Exiv2;

// Test fixture for DataValue tests
class DataValueTest_800 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// ============================================================
// Constructor Tests
// ============================================================

TEST_F(DataValueTest_800, DefaultConstructorWithUndefinedType_800) {
    DataValue dv(TypeId::undefined);
    EXPECT_EQ(dv.typeId(), TypeId::undefined);
    EXPECT_EQ(dv.count(), 0u);
    EXPECT_EQ(dv.size(), 0u);
}

TEST_F(DataValueTest_800, DefaultConstructorWithUnsignedByte_800) {
    DataValue dv(TypeId::unsignedByte);
    EXPECT_EQ(dv.typeId(), TypeId::unsignedByte);
    EXPECT_EQ(dv.count(), 0u);
    EXPECT_EQ(dv.size(), 0u);
}

TEST_F(DataValueTest_800, ConstructorWithBufferData_800) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04};
    DataValue dv(data, sizeof(data), littleEndian, TypeId::undefined);
    EXPECT_EQ(dv.typeId(), TypeId::undefined);
    EXPECT_EQ(dv.count(), 4u);
    EXPECT_EQ(dv.size(), 4u);
}

// ============================================================
// read() from byte buffer tests
// ============================================================

TEST_F(DataValueTest_800, ReadFromByteBuffer_800) {
    DataValue dv(TypeId::undefined);
    const byte data[] = {0x10, 0x20, 0x30};
    int result = dv.read(data, sizeof(data), littleEndian);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(dv.count(), 3u);
    EXPECT_EQ(dv.size(), 3u);
}

TEST_F(DataValueTest_800, ReadFromEmptyByteBuffer_800) {
    DataValue dv(TypeId::undefined);
    const byte data[] = {0x00};
    int result = dv.read(data, 0, littleEndian);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(dv.count(), 0u);
    EXPECT_EQ(dv.size(), 0u);
}

TEST_F(DataValueTest_800, ReadFromByteBufferOverwritesPrevious_800) {
    DataValue dv(TypeId::undefined);
    const byte data1[] = {0x01, 0x02, 0x03};
    dv.read(data1, sizeof(data1), littleEndian);
    EXPECT_EQ(dv.count(), 3u);

    const byte data2[] = {0x04, 0x05};
    dv.read(data2, sizeof(data2), littleEndian);
    EXPECT_EQ(dv.count(), 2u);
}

// ============================================================
// read() from string tests
// ============================================================

TEST_F(DataValueTest_800, ReadFromString_800) {
    DataValue dv(TypeId::undefined);
    // String format expected: space-separated integers
    int result = dv.read("1 2 3 4 5");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(dv.count(), 5u);
}

TEST_F(DataValueTest_800, ReadFromEmptyString_800) {
    DataValue dv(TypeId::undefined);
    int result = dv.read("");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(dv.count(), 0u);
}

TEST_F(DataValueTest_800, ReadFromStringSingleValue_800) {
    DataValue dv(TypeId::undefined);
    int result = dv.read("42");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(dv.count(), 1u);
}

// ============================================================
// copy() tests
// ============================================================

TEST_F(DataValueTest_800, CopyToBuffer_800) {
    const byte data[] = {0xAA, 0xBB, 0xCC};
    DataValue dv(data, sizeof(data), littleEndian, TypeId::undefined);

    byte buf[3] = {0};
    size_t copied = dv.copy(buf, littleEndian);
    EXPECT_EQ(copied, 3u);
    EXPECT_EQ(buf[0], 0xAA);
    EXPECT_EQ(buf[1], 0xBB);
    EXPECT_EQ(buf[2], 0xCC);
}

TEST_F(DataValueTest_800, CopyEmptyValue_800) {
    DataValue dv(TypeId::undefined);
    byte buf[1] = {0xFF};
    size_t copied = dv.copy(buf, littleEndian);
    EXPECT_EQ(copied, 0u);
}

// ============================================================
// count() tests
// ============================================================

TEST_F(DataValueTest_800, CountEmptyValue_800) {
    DataValue dv(TypeId::undefined);
    EXPECT_EQ(dv.count(), 0u);
}

TEST_F(DataValueTest_800, CountAfterRead_800) {
    DataValue dv(TypeId::undefined);
    const byte data[] = {1, 2, 3, 4, 5};
    dv.read(data, sizeof(data), littleEndian);
    EXPECT_EQ(dv.count(), 5u);
}

// ============================================================
// size() tests
// ============================================================

TEST_F(DataValueTest_800, SizeMatchesBufferLength_800) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06};
    DataValue dv(data, sizeof(data), littleEndian, TypeId::undefined);
    EXPECT_EQ(dv.size(), 6u);
}

TEST_F(DataValueTest_800, SizeEmptyValue_800) {
    DataValue dv(TypeId::undefined);
    EXPECT_EQ(dv.size(), 0u);
}

// ============================================================
// toUint32() tests
// ============================================================

TEST_F(DataValueTest_800, ToUint32ValidIndex_800) {
    const byte data[] = {10, 20, 30};
    DataValue dv(data, sizeof(data), littleEndian, TypeId::undefined);
    EXPECT_EQ(dv.toUint32(0), 10u);
    EXPECT_EQ(dv.toUint32(1), 20u);
    EXPECT_EQ(dv.toUint32(2), 30u);
    EXPECT_TRUE(dv.ok());
}

TEST_F(DataValueTest_800, ToUint32OutOfRange_800) {
    const byte data[] = {10, 20};
    DataValue dv(data, sizeof(data), littleEndian, TypeId::undefined);
    EXPECT_THROW(dv.toUint32(5), std::out_of_range);
}

TEST_F(DataValueTest_800, ToUint32FirstElement_800) {
    DataValue dv(TypeId::undefined);
    dv.read("255");
    uint32_t val = dv.toUint32(0);
    EXPECT_EQ(val, 255u);
    EXPECT_TRUE(dv.ok());
}

// ============================================================
// toInt64() tests
// ============================================================

TEST_F(DataValueTest_800, ToInt64ValidIndex_800) {
    const byte data[] = {5, 10, 15};
    DataValue dv(data, sizeof(data), littleEndian, TypeId::undefined);
    EXPECT_EQ(dv.toInt64(0), 5);
    EXPECT_EQ(dv.toInt64(1), 10);
    EXPECT_EQ(dv.toInt64(2), 15);
    EXPECT_TRUE(dv.ok());
}

TEST_F(DataValueTest_800, ToInt64OutOfRange_800) {
    DataValue dv(TypeId::undefined);
    const byte data[] = {1};
    dv.read(data, sizeof(data), littleEndian);
    EXPECT_THROW(dv.toInt64(10), std::out_of_range);
}

// ============================================================
// toFloat() tests
// ============================================================

TEST_F(DataValueTest_800, ToFloatValidIndex_800) {
    const byte data[] = {7, 14};
    DataValue dv(data, sizeof(data), littleEndian, TypeId::undefined);
    EXPECT_FLOAT_EQ(dv.toFloat(0), 7.0f);
    EXPECT_FLOAT_EQ(dv.toFloat(1), 14.0f);
    EXPECT_TRUE(dv.ok());
}

TEST_F(DataValueTest_800, ToFloatOutOfRange_800) {
    DataValue dv(TypeId::undefined);
    EXPECT_THROW(dv.toFloat(0), std::out_of_range);
}

// ============================================================
// toRational() tests
// ============================================================

TEST_F(DataValueTest_800, ToRationalValidIndex_800) {
    const byte data[] = {42};
    DataValue dv(data, sizeof(data), littleEndian, TypeId::undefined);
    Rational r = dv.toRational(0);
    EXPECT_EQ(r.first, 42);
    EXPECT_EQ(r.second, 1);
    EXPECT_TRUE(dv.ok());
}

TEST_F(DataValueTest_800, ToRationalOutOfRange_800) {
    DataValue dv(TypeId::undefined);
    EXPECT_THROW(dv.toRational(0), std::out_of_range);
}

// ============================================================
// toString() tests
// ============================================================

TEST_F(DataValueTest_800, ToStringValidIndex_800) {
    const byte data[] = {65};  // 'A' = 65
    DataValue dv(data, sizeof(data), littleEndian, TypeId::undefined);
    std::string s = dv.toString(0);
    EXPECT_EQ(s, "65");
}

TEST_F(DataValueTest_800, ToStringMultipleElements_800) {
    const byte data[] = {1, 2, 3};
    DataValue dv(data, sizeof(data), littleEndian, TypeId::undefined);
    std::string s0 = dv.toString(0);
    std::string s1 = dv.toString(1);
    std::string s2 = dv.toString(2);
    EXPECT_EQ(s0, "1");
    EXPECT_EQ(s1, "2");
    EXPECT_EQ(s2, "3");
}

// ============================================================
// write() tests
// ============================================================

TEST_F(DataValueTest_800, WriteToOstream_800) {
    const byte data[] = {10, 20, 30};
    DataValue dv(data, sizeof(data), littleEndian, TypeId::undefined);
    std::ostringstream os;
    dv.write(os);
    std::string output = os.str();
    EXPECT_FALSE(output.empty());
}

TEST_F(DataValueTest_800, WriteEmptyToOstream_800) {
    DataValue dv(TypeId::undefined);
    std::ostringstream os;
    dv.write(os);
    std::string output = os.str();
    // Empty DataValue might produce empty or specific output
    // We just verify it doesn't crash
}

// ============================================================
// clone() tests
// ============================================================

TEST_F(DataValueTest_800, ClonePreservesData_800) {
    const byte data[] = {1, 2, 3, 4};
    DataValue dv(data, sizeof(data), littleEndian, TypeId::undefined);
    auto cloned = dv.clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->typeId(), TypeId::undefined);
    EXPECT_EQ(cloned->count(), 4u);
    EXPECT_EQ(cloned->size(), 4u);
}

TEST_F(DataValueTest_800, CloneEmptyDataValue_800) {
    DataValue dv(TypeId::undefined);
    auto cloned = dv.clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->count(), 0u);
}

// ============================================================
// ok() tests
// ============================================================

TEST_F(DataValueTest_800, OkAfterSuccessfulConversion_800) {
    const byte data[] = {100};
    DataValue dv(data, sizeof(data), littleEndian, TypeId::undefined);
    dv.toUint32(0);
    EXPECT_TRUE(dv.ok());
}

// ============================================================
// typeId() tests
// ============================================================

TEST_F(DataValueTest_800, TypeIdReturnsCorrectType_800) {
    DataValue dv1(TypeId::undefined);
    EXPECT_EQ(dv1.typeId(), TypeId::undefined);

    DataValue dv2(TypeId::unsignedByte);
    EXPECT_EQ(dv2.typeId(), TypeId::unsignedByte);
}

// ============================================================
// Boundary: Single byte data
// ============================================================

TEST_F(DataValueTest_800, SingleByteData_800) {
    const byte data[] = {0x00};
    DataValue dv(data, sizeof(data), littleEndian, TypeId::undefined);
    EXPECT_EQ(dv.count(), 1u);
    EXPECT_EQ(dv.size(), 1u);
    EXPECT_EQ(dv.toUint32(0), 0u);
}

TEST_F(DataValueTest_800, SingleByteMaxValue_800) {
    const byte data[] = {0xFF};
    DataValue dv(data, sizeof(data), littleEndian, TypeId::undefined);
    EXPECT_EQ(dv.toUint32(0), 255u);
}

// ============================================================
// Boundary: Large data
// ============================================================

TEST_F(DataValueTest_800, LargeBufferRead_800) {
    std::vector<byte> data(1000, 0x42);
    DataValue dv(TypeId::undefined);
    int result = dv.read(data.data(), data.size(), littleEndian);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(dv.count(), 1000u);
    EXPECT_EQ(dv.size(), 1000u);
    EXPECT_EQ(dv.toUint32(0), 0x42u);
    EXPECT_EQ(dv.toUint32(999), 0x42u);
}

// ============================================================
// DataValue with different byte orders
// ============================================================

TEST_F(DataValueTest_800, ReadWithBigEndian_800) {
    const byte data[] = {0x01, 0x02};
    DataValue dv(TypeId::undefined);
    int result = dv.read(data, sizeof(data), bigEndian);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(dv.count(), 2u);
    // DataValue stores individual bytes, byte order shouldn't matter for byte-level access
    EXPECT_EQ(dv.toUint32(0), 1u);
    EXPECT_EQ(dv.toUint32(1), 2u);
}

// ============================================================
// Value::create() factory for DataValue-related types
// ============================================================

TEST_F(DataValueTest_800, CreateUndefinedTypeReturnsDataValue_800) {
    auto val = Value::create(TypeId::undefined);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->typeId(), TypeId::undefined);
}

// ============================================================
// Re-read data replaces old data
// ============================================================

TEST_F(DataValueTest_800, ReReadDataReplacesOldData_800) {
    DataValue dv(TypeId::undefined);
    const byte data1[] = {1, 2, 3};
    dv.read(data1, sizeof(data1), littleEndian);
    EXPECT_EQ(dv.count(), 3u);
    EXPECT_EQ(dv.toUint32(0), 1u);

    const byte data2[] = {100, 200};
    dv.read(data2, sizeof(data2), littleEndian);
    EXPECT_EQ(dv.count(), 2u);
    EXPECT_EQ(dv.toUint32(0), 100u);
    EXPECT_EQ(dv.toUint32(1), 200u);
}

// ============================================================
// String read with various formats
// ============================================================

TEST_F(DataValueTest_800, ReadFromStringWithMultipleSpaces_800) {
    DataValue dv(TypeId::undefined);
    dv.read("10  20  30");
    // Behavior depends on implementation parsing
    EXPECT_GE(dv.count(), 1u);
}

TEST_F(DataValueTest_800, ReadFromStringZeroValues_800) {
    DataValue dv(TypeId::undefined);
    dv.read("0 0 0");
    EXPECT_EQ(dv.count(), 3u);
    EXPECT_EQ(dv.toUint32(0), 0u);
    EXPECT_EQ(dv.toUint32(1), 0u);
    EXPECT_EQ(dv.toUint32(2), 0u);
}

// ============================================================
// Copy round-trip test
// ============================================================

TEST_F(DataValueTest_800, CopyRoundTrip_800) {
    const byte original[] = {11, 22, 33, 44, 55};
    DataValue dv(original, sizeof(original), littleEndian, TypeId::undefined);

    byte copied[5] = {0};
    size_t sz = dv.copy(copied, littleEndian);
    EXPECT_EQ(sz, 5u);

    for (size_t i = 0; i < 5; ++i) {
        EXPECT_EQ(copied[i], original[i]);
    }
}

// ============================================================
// sizeDataArea and dataArea tests (inherited from Value)
// ============================================================

TEST_F(DataValueTest_800, SizeDataAreaDefault_800) {
    DataValue dv(TypeId::undefined);
    EXPECT_EQ(dv.sizeDataArea(), 0u);
}

TEST_F(DataValueTest_800, DataAreaDefault_800) {
    DataValue dv(TypeId::undefined);
    DataBuf buf = dv.dataArea();
    EXPECT_EQ(buf.size(), 0u);
}
