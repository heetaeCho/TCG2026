#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <sstream>
#include <vector>
#include <cstring>

using namespace Exiv2;

// Test fixture for DataValue tests
class DataValueTest_798 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// ==================== Constructor Tests ====================

TEST_F(DataValueTest_798, DefaultConstructor_CreatesEmptyDataValue_798) {
    DataValue dv(TypeId::undefined);
    EXPECT_EQ(dv.typeId(), TypeId::undefined);
    EXPECT_EQ(dv.count(), 0u);
    EXPECT_EQ(dv.size(), 0u);
}

TEST_F(DataValueTest_798, ConstructorWithByteType_798) {
    DataValue dv(TypeId::unsignedByte);
    EXPECT_EQ(dv.typeId(), TypeId::unsignedByte);
    EXPECT_EQ(dv.count(), 0u);
}

TEST_F(DataValueTest_798, ConstructorWithBufferAndLength_798) {
    const byte data[] = {0x01, 0x02, 0x03};
    DataValue dv(data, 3, littleEndian, TypeId::undefined);
    EXPECT_EQ(dv.typeId(), TypeId::undefined);
    EXPECT_EQ(dv.count(), 3u);
    EXPECT_EQ(dv.size(), 3u);
}

// ==================== read() from buffer Tests ====================

TEST_F(DataValueTest_798, ReadFromBuffer_PopulatesValue_798) {
    DataValue dv(TypeId::undefined);
    const byte data[] = {0x10, 0x20, 0x30, 0x40};
    int result = dv.read(data, 4, littleEndian);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(dv.count(), 4u);
    EXPECT_EQ(dv.size(), 4u);
}

TEST_F(DataValueTest_798, ReadFromBuffer_EmptyBuffer_798) {
    DataValue dv(TypeId::undefined);
    const byte* data = nullptr;
    int result = dv.read(data, 0, littleEndian);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(dv.count(), 0u);
    EXPECT_EQ(dv.size(), 0u);
}

TEST_F(DataValueTest_798, ReadFromBuffer_SingleByte_798) {
    DataValue dv(TypeId::undefined);
    const byte data[] = {0xFF};
    int result = dv.read(data, 1, littleEndian);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(dv.count(), 1u);
    EXPECT_EQ(dv.size(), 1u);
}

TEST_F(DataValueTest_798, ReadFromBuffer_ReplacesExistingData_798) {
    DataValue dv(TypeId::undefined);
    const byte data1[] = {0x01, 0x02, 0x03};
    dv.read(data1, 3, littleEndian);
    EXPECT_EQ(dv.count(), 3u);

    const byte data2[] = {0x04, 0x05};
    dv.read(data2, 2, littleEndian);
    EXPECT_EQ(dv.count(), 2u);
}

// ==================== read() from string Tests ====================

TEST_F(DataValueTest_798, ReadFromString_SpaceSeparatedValues_798) {
    DataValue dv(TypeId::undefined);
    int result = dv.read("1 2 3 4 5");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(dv.count(), 5u);
}

TEST_F(DataValueTest_798, ReadFromString_SingleValue_798) {
    DataValue dv(TypeId::undefined);
    int result = dv.read("42");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(dv.count(), 1u);
}

TEST_F(DataValueTest_798, ReadFromString_EmptyString_798) {
    DataValue dv(TypeId::undefined);
    int result = dv.read("");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(dv.count(), 0u);
}

// ==================== toString() Tests ====================

TEST_F(DataValueTest_798, ToString_SingleElement_798) {
    DataValue dv(TypeId::undefined);
    const byte data[] = {42};
    dv.read(data, 1, littleEndian);
    std::string result = dv.toString(0);
    EXPECT_EQ(result, "42");
    EXPECT_TRUE(dv.ok());
}

TEST_F(DataValueTest_798, ToString_MultipleElements_798) {
    DataValue dv(TypeId::undefined);
    const byte data[] = {10, 20, 30};
    dv.read(data, 3, littleEndian);
    EXPECT_EQ(dv.toString(0), "10");
    EXPECT_EQ(dv.toString(1), "20");
    EXPECT_EQ(dv.toString(2), "30");
}

TEST_F(DataValueTest_798, ToString_ZeroValue_798) {
    DataValue dv(TypeId::undefined);
    const byte data[] = {0};
    dv.read(data, 1, littleEndian);
    EXPECT_EQ(dv.toString(0), "0");
}

TEST_F(DataValueTest_798, ToString_MaxByteValue_798) {
    DataValue dv(TypeId::undefined);
    const byte data[] = {255};
    dv.read(data, 1, littleEndian);
    EXPECT_EQ(dv.toString(0), "255");
}

TEST_F(DataValueTest_798, ToString_OutOfRange_ThrowsOrHandles_798) {
    DataValue dv(TypeId::undefined);
    const byte data[] = {1, 2};
    dv.read(data, 2, littleEndian);
    // Accessing out of range should throw std::out_of_range due to at()
    EXPECT_THROW(dv.toString(5), std::out_of_range);
}

TEST_F(DataValueTest_798, ToString_NoArgument_798) {
    DataValue dv(TypeId::undefined);
    const byte data[] = {10, 20, 30};
    dv.read(data, 3, littleEndian);
    std::string result = dv.toString();
    // toString() without argument should return the full representation
    EXPECT_FALSE(result.empty());
}

// ==================== toInt64() Tests ====================

TEST_F(DataValueTest_798, ToInt64_ValidIndex_798) {
    DataValue dv(TypeId::undefined);
    const byte data[] = {100};
    dv.read(data, 1, littleEndian);
    int64_t result = dv.toInt64(0);
    EXPECT_EQ(result, 100);
}

TEST_F(DataValueTest_798, ToInt64_MultipleValues_798) {
    DataValue dv(TypeId::undefined);
    const byte data[] = {0, 128, 255};
    dv.read(data, 3, littleEndian);
    EXPECT_EQ(dv.toInt64(0), 0);
    EXPECT_EQ(dv.toInt64(1), 128);
    EXPECT_EQ(dv.toInt64(2), 255);
}

// ==================== toUint32() Tests ====================

TEST_F(DataValueTest_798, ToUint32_ValidIndex_798) {
    DataValue dv(TypeId::undefined);
    const byte data[] = {200};
    dv.read(data, 1, littleEndian);
    uint32_t result = dv.toUint32(0);
    EXPECT_EQ(result, 200u);
}

TEST_F(DataValueTest_798, ToUint32_ZeroValue_798) {
    DataValue dv(TypeId::undefined);
    const byte data[] = {0};
    dv.read(data, 1, littleEndian);
    EXPECT_EQ(dv.toUint32(0), 0u);
}

// ==================== toFloat() Tests ====================

TEST_F(DataValueTest_798, ToFloat_ValidIndex_798) {
    DataValue dv(TypeId::undefined);
    const byte data[] = {50};
    dv.read(data, 1, littleEndian);
    float result = dv.toFloat(0);
    EXPECT_FLOAT_EQ(result, 50.0f);
}

// ==================== toRational() Tests ====================

TEST_F(DataValueTest_798, ToRational_ValidIndex_798) {
    DataValue dv(TypeId::undefined);
    const byte data[] = {75};
    dv.read(data, 1, littleEndian);
    Rational result = dv.toRational(0);
    EXPECT_EQ(result.first, 75);
    EXPECT_EQ(result.second, 1);
}

// ==================== copy() Tests ====================

TEST_F(DataValueTest_798, Copy_CopiesDataToBuffer_798) {
    DataValue dv(TypeId::undefined);
    const byte data[] = {0xAA, 0xBB, 0xCC};
    dv.read(data, 3, littleEndian);

    byte buf[3] = {0};
    size_t copied = dv.copy(buf, littleEndian);
    EXPECT_EQ(copied, 3u);
    EXPECT_EQ(buf[0], 0xAA);
    EXPECT_EQ(buf[1], 0xBB);
    EXPECT_EQ(buf[2], 0xCC);
}

TEST_F(DataValueTest_798, Copy_EmptyDataValue_798) {
    DataValue dv(TypeId::undefined);
    byte buf[1] = {0xFF};
    size_t copied = dv.copy(buf, littleEndian);
    EXPECT_EQ(copied, 0u);
}

// ==================== count() Tests ====================

TEST_F(DataValueTest_798, Count_EmptyValue_798) {
    DataValue dv(TypeId::undefined);
    EXPECT_EQ(dv.count(), 0u);
}

TEST_F(DataValueTest_798, Count_AfterReadFromBuffer_798) {
    DataValue dv(TypeId::undefined);
    const byte data[] = {1, 2, 3, 4, 5};
    dv.read(data, 5, littleEndian);
    EXPECT_EQ(dv.count(), 5u);
}

// ==================== size() Tests ====================

TEST_F(DataValueTest_798, Size_EmptyValue_798) {
    DataValue dv(TypeId::undefined);
    EXPECT_EQ(dv.size(), 0u);
}

TEST_F(DataValueTest_798, Size_AfterReadFromBuffer_798) {
    DataValue dv(TypeId::undefined);
    const byte data[] = {1, 2, 3};
    dv.read(data, 3, littleEndian);
    EXPECT_EQ(dv.size(), 3u);
}

// ==================== write() Tests ====================

TEST_F(DataValueTest_798, Write_OutputsToStream_798) {
    DataValue dv(TypeId::undefined);
    const byte data[] = {10, 20, 30};
    dv.read(data, 3, littleEndian);

    std::ostringstream os;
    dv.write(os);
    std::string output = os.str();
    EXPECT_FALSE(output.empty());
}

TEST_F(DataValueTest_798, Write_EmptyDataValue_798) {
    DataValue dv(TypeId::undefined);
    std::ostringstream os;
    dv.write(os);
    std::string output = os.str();
    // Empty data value may produce empty or specific output
    // Just verify it doesn't crash
}

// ==================== clone() Tests ====================

TEST_F(DataValueTest_798, Clone_CreatesIndependentCopy_798) {
    DataValue dv(TypeId::undefined);
    const byte data[] = {1, 2, 3};
    dv.read(data, 3, littleEndian);

    auto cloned = dv.clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->count(), 3u);
    EXPECT_EQ(cloned->typeId(), TypeId::undefined);
}

TEST_F(DataValueTest_798, Clone_EmptyValue_798) {
    DataValue dv(TypeId::undefined);
    auto cloned = dv.clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->count(), 0u);
}

// ==================== ok() Tests ====================

TEST_F(DataValueTest_798, Ok_TrueAfterSuccessfulToString_798) {
    DataValue dv(TypeId::undefined);
    const byte data[] = {42};
    dv.read(data, 1, littleEndian);
    dv.toString(0);
    EXPECT_TRUE(dv.ok());
}

// ==================== typeId() Tests ====================

TEST_F(DataValueTest_798, TypeId_ReturnsCorrectType_798) {
    DataValue dv1(TypeId::undefined);
    EXPECT_EQ(dv1.typeId(), TypeId::undefined);

    DataValue dv2(TypeId::unsignedByte);
    EXPECT_EQ(dv2.typeId(), TypeId::unsignedByte);
}

// ==================== ByteOrder independence Tests ====================

TEST_F(DataValueTest_798, ReadAndCopy_ByteOrderIndependent_798) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04};

    DataValue dvLittle(TypeId::undefined);
    dvLittle.read(data, 4, littleEndian);

    DataValue dvBig(TypeId::undefined);
    dvBig.read(data, 4, bigEndian);

    // DataValue stores raw bytes, so byte order shouldn't matter
    EXPECT_EQ(dvLittle.count(), dvBig.count());
    EXPECT_EQ(dvLittle.size(), dvBig.size());

    byte bufLittle[4] = {0};
    byte bufBig[4] = {0};
    dvLittle.copy(bufLittle, littleEndian);
    dvBig.copy(bufBig, bigEndian);

    EXPECT_EQ(std::memcmp(bufLittle, bufBig, 4), 0);
}

// ==================== Large data Tests ====================

TEST_F(DataValueTest_798, LargeData_ReadAndAccess_798) {
    std::vector<byte> largeData(1000);
    for (size_t i = 0; i < largeData.size(); ++i) {
        largeData[i] = static_cast<byte>(i % 256);
    }

    DataValue dv(TypeId::undefined);
    int result = dv.read(largeData.data(), largeData.size(), littleEndian);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(dv.count(), 1000u);
    EXPECT_EQ(dv.size(), 1000u);

    // Check first and last elements
    EXPECT_EQ(dv.toString(0), "0");
    EXPECT_EQ(dv.toString(999), std::to_string(999 % 256));
}

// ==================== Constructor with buffer Tests ====================

TEST_F(DataValueTest_798, ConstructorWithBuffer_CorrectData_798) {
    const byte data[] = {5, 10, 15, 20, 25};
    DataValue dv(data, 5, littleEndian, TypeId::undefined);

    EXPECT_EQ(dv.count(), 5u);
    EXPECT_EQ(dv.size(), 5u);
    EXPECT_EQ(dv.toString(0), "5");
    EXPECT_EQ(dv.toString(4), "25");
}

// ==================== read from string with various formats ====================

TEST_F(DataValueTest_798, ReadFromString_HexValues_798) {
    DataValue dv(TypeId::undefined);
    // Read string with hex-like decimal values
    int result = dv.read("255 0 128");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(dv.count(), 3u);
    EXPECT_EQ(dv.toInt64(0), 255);
    EXPECT_EQ(dv.toInt64(1), 0);
    EXPECT_EQ(dv.toInt64(2), 128);
}

// ==================== Consistency Tests ====================

TEST_F(DataValueTest_798, ConsistencyBetweenToStringAndToInt64_798) {
    DataValue dv(TypeId::undefined);
    const byte data[] = {42, 100, 200};
    dv.read(data, 3, littleEndian);

    for (size_t i = 0; i < dv.count(); ++i) {
        std::string strVal = dv.toString(i);
        int64_t intVal = dv.toInt64(i);
        EXPECT_EQ(strVal, std::to_string(intVal));
    }
}

TEST_F(DataValueTest_798, ConsistencyBetweenToFloatAndToInt64_798) {
    DataValue dv(TypeId::undefined);
    const byte data[] = {50};
    dv.read(data, 1, littleEndian);

    float floatVal = dv.toFloat(0);
    int64_t intVal = dv.toInt64(0);
    EXPECT_FLOAT_EQ(floatVal, static_cast<float>(intVal));
}
