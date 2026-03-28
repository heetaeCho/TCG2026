#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <cstring>
#include <sstream>
#include <vector>

using namespace Exiv2;

// Test fixture for DataValue
class DataValueTest_801 : public ::testing::Test {
protected:
    void SetUp() override {
    }
    void TearDown() override {
    }
};

// ==================== Construction Tests ====================

TEST_F(DataValueTest_801, ConstructWithUndefinedType_801) {
    DataValue dv(undefined);
    EXPECT_EQ(dv.typeId(), undefined);
    EXPECT_EQ(dv.count(), 0u);
    EXPECT_EQ(dv.size(), 0u);
}

TEST_F(DataValueTest_801, ConstructWithUnsignedByte_801) {
    DataValue dv(unsignedByte);
    EXPECT_EQ(dv.typeId(), unsignedByte);
    EXPECT_EQ(dv.count(), 0u);
}

TEST_F(DataValueTest_801, ConstructFromBuffer_801) {
    const byte buf[] = {0x01, 0x02, 0x03, 0x04};
    DataValue dv(buf, sizeof(buf), littleEndian, undefined);
    EXPECT_EQ(dv.typeId(), undefined);
    EXPECT_EQ(dv.count(), 4u);
    EXPECT_EQ(dv.size(), 4u);
}

// ==================== Read Tests ====================

TEST_F(DataValueTest_801, ReadFromByteBuffer_801) {
    DataValue dv(undefined);
    const byte buf[] = {0x10, 0x20, 0x30};
    int result = dv.read(buf, sizeof(buf), littleEndian);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(dv.count(), 3u);
    EXPECT_EQ(dv.size(), 3u);
}

TEST_F(DataValueTest_801, ReadFromString_801) {
    DataValue dv(undefined);
    std::string str = "48 65 6C 6C 6F"; // "Hello" in hex
    int result = dv.read(str);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(dv.count(), 5u);
}

TEST_F(DataValueTest_801, ReadEmptyBuffer_801) {
    DataValue dv(undefined);
    int result = dv.read(nullptr, 0, littleEndian);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(dv.count(), 0u);
    EXPECT_EQ(dv.size(), 0u);
}

TEST_F(DataValueTest_801, ReadEmptyString_801) {
    DataValue dv(undefined);
    int result = dv.read("");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(dv.count(), 0u);
}

TEST_F(DataValueTest_801, ReadOverwritesPreviousData_801) {
    DataValue dv(undefined);
    const byte buf1[] = {0x01, 0x02, 0x03};
    dv.read(buf1, sizeof(buf1), littleEndian);
    EXPECT_EQ(dv.count(), 3u);

    const byte buf2[] = {0x04, 0x05};
    dv.read(buf2, sizeof(buf2), littleEndian);
    EXPECT_EQ(dv.count(), 2u);
}

// ==================== Copy Tests ====================

TEST_F(DataValueTest_801, CopyToBuffer_801) {
    const byte input[] = {0xAA, 0xBB, 0xCC};
    DataValue dv(input, sizeof(input), littleEndian, undefined);

    byte output[3] = {0};
    size_t copied = dv.copy(output, littleEndian);
    EXPECT_EQ(copied, 3u);
    EXPECT_EQ(output[0], 0xAA);
    EXPECT_EQ(output[1], 0xBB);
    EXPECT_EQ(output[2], 0xCC);
}

TEST_F(DataValueTest_801, CopyEmptyValue_801) {
    DataValue dv(undefined);
    byte output[1] = {0xFF};
    size_t copied = dv.copy(output, littleEndian);
    EXPECT_EQ(copied, 0u);
}

// ==================== Count and Size Tests ====================

TEST_F(DataValueTest_801, CountMatchesNumberOfBytes_801) {
    const byte buf[] = {1, 2, 3, 4, 5};
    DataValue dv(buf, sizeof(buf), littleEndian, undefined);
    EXPECT_EQ(dv.count(), 5u);
}

TEST_F(DataValueTest_801, SizeMatchesNumberOfBytes_801) {
    const byte buf[] = {1, 2, 3, 4, 5};
    DataValue dv(buf, sizeof(buf), littleEndian, undefined);
    EXPECT_EQ(dv.size(), 5u);
}

// ==================== Write Tests ====================

TEST_F(DataValueTest_801, WriteToStream_801) {
    const byte buf[] = {0x41, 0x42, 0x43}; // 'A', 'B', 'C'
    DataValue dv(buf, sizeof(buf), littleEndian, undefined);

    std::ostringstream os;
    dv.write(os);
    std::string output = os.str();
    EXPECT_FALSE(output.empty());
}

TEST_F(DataValueTest_801, WriteEmptyValue_801) {
    DataValue dv(undefined);
    std::ostringstream os;
    dv.write(os);
    std::string output = os.str();
    // Empty value should produce empty or minimal output
    // We just verify no crash
}

// ==================== ToString Tests ====================

TEST_F(DataValueTest_801, ToStringWithIndex_801) {
    const byte buf[] = {0x41, 0x42};
    DataValue dv(buf, sizeof(buf), littleEndian, undefined);
    std::string s0 = dv.toString(0);
    std::string s1 = dv.toString(1);
    EXPECT_FALSE(s0.empty());
    EXPECT_FALSE(s1.empty());
}

TEST_F(DataValueTest_801, ToStringOutOfRange_801) {
    const byte buf[] = {0x41};
    DataValue dv(buf, sizeof(buf), littleEndian, undefined);
    EXPECT_THROW(dv.toString(5), std::out_of_range);
}

// ==================== toFloat Tests ====================

TEST_F(DataValueTest_801, ToFloatValidIndex_801) {
    const byte buf[] = {10, 20, 30};
    DataValue dv(buf, sizeof(buf), littleEndian, undefined);
    
    float val0 = dv.toFloat(0);
    EXPECT_FLOAT_EQ(val0, 10.0f);
    EXPECT_TRUE(dv.ok());

    float val1 = dv.toFloat(1);
    EXPECT_FLOAT_EQ(val1, 20.0f);
    EXPECT_TRUE(dv.ok());

    float val2 = dv.toFloat(2);
    EXPECT_FLOAT_EQ(val2, 30.0f);
    EXPECT_TRUE(dv.ok());
}

TEST_F(DataValueTest_801, ToFloatOutOfRange_801) {
    const byte buf[] = {10};
    DataValue dv(buf, sizeof(buf), littleEndian, undefined);
    EXPECT_THROW(dv.toFloat(5), std::out_of_range);
}

TEST_F(DataValueTest_801, ToFloatZeroValue_801) {
    const byte buf[] = {0};
    DataValue dv(buf, sizeof(buf), littleEndian, undefined);
    float val = dv.toFloat(0);
    EXPECT_FLOAT_EQ(val, 0.0f);
    EXPECT_TRUE(dv.ok());
}

TEST_F(DataValueTest_801, ToFloatMaxByteValue_801) {
    const byte buf[] = {255};
    DataValue dv(buf, sizeof(buf), littleEndian, undefined);
    float val = dv.toFloat(0);
    EXPECT_FLOAT_EQ(val, 255.0f);
    EXPECT_TRUE(dv.ok());
}

// ==================== toInt64 Tests ====================

TEST_F(DataValueTest_801, ToInt64ValidIndex_801) {
    const byte buf[] = {42, 100, 200};
    DataValue dv(buf, sizeof(buf), littleEndian, undefined);
    
    EXPECT_EQ(dv.toInt64(0), 42);
    EXPECT_TRUE(dv.ok());
    
    EXPECT_EQ(dv.toInt64(1), 100);
    EXPECT_TRUE(dv.ok());
    
    EXPECT_EQ(dv.toInt64(2), 200);
    EXPECT_TRUE(dv.ok());
}

TEST_F(DataValueTest_801, ToInt64OutOfRange_801) {
    const byte buf[] = {42};
    DataValue dv(buf, sizeof(buf), littleEndian, undefined);
    EXPECT_THROW(dv.toInt64(10), std::out_of_range);
}

// ==================== toUint32 Tests ====================

TEST_F(DataValueTest_801, ToUint32ValidIndex_801) {
    const byte buf[] = {0, 128, 255};
    DataValue dv(buf, sizeof(buf), littleEndian, undefined);
    
    EXPECT_EQ(dv.toUint32(0), 0u);
    EXPECT_EQ(dv.toUint32(1), 128u);
    EXPECT_EQ(dv.toUint32(2), 255u);
}

TEST_F(DataValueTest_801, ToUint32OutOfRange_801) {
    DataValue dv(undefined);
    EXPECT_THROW(dv.toUint32(0), std::out_of_range);
}

// ==================== toRational Tests ====================

TEST_F(DataValueTest_801, ToRationalValidIndex_801) {
    const byte buf[] = {42};
    DataValue dv(buf, sizeof(buf), littleEndian, undefined);
    Rational r = dv.toRational(0);
    EXPECT_EQ(r.first, 42);
    EXPECT_EQ(r.second, 1);
}

TEST_F(DataValueTest_801, ToRationalOutOfRange_801) {
    DataValue dv(undefined);
    EXPECT_THROW(dv.toRational(0), std::out_of_range);
}

// ==================== Clone Tests ====================

TEST_F(DataValueTest_801, ClonePreservesData_801) {
    const byte buf[] = {0x01, 0x02, 0x03};
    DataValue dv(buf, sizeof(buf), littleEndian, undefined);
    
    auto cloned = dv.clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->typeId(), undefined);
    EXPECT_EQ(cloned->count(), 3u);
    EXPECT_EQ(cloned->size(), 3u);
}

TEST_F(DataValueTest_801, CloneEmptyValue_801) {
    DataValue dv(undefined);
    auto cloned = dv.clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->count(), 0u);
}

// ==================== Byte Order Independence Tests ====================

TEST_F(DataValueTest_801, ByteOrderDoesNotAffectRead_801) {
    const byte buf[] = {0x01, 0x02, 0x03};
    
    DataValue dv1(undefined);
    dv1.read(buf, sizeof(buf), littleEndian);
    
    DataValue dv2(undefined);
    dv2.read(buf, sizeof(buf), bigEndian);
    
    EXPECT_EQ(dv1.count(), dv2.count());
    EXPECT_EQ(dv1.size(), dv2.size());
    
    for (size_t i = 0; i < dv1.count(); ++i) {
        EXPECT_EQ(dv1.toInt64(i), dv2.toInt64(i));
    }
}

// ==================== DataArea Tests ====================

TEST_F(DataValueTest_801, DataAreaDefaultEmpty_801) {
    DataValue dv(undefined);
    EXPECT_EQ(dv.sizeDataArea(), 0u);
    DataBuf area = dv.dataArea();
    EXPECT_EQ(area.size(), 0u);
}

// ==================== Single Byte Boundary Tests ====================

TEST_F(DataValueTest_801, SingleByteValue_801) {
    const byte buf[] = {0x7F};
    DataValue dv(buf, 1, littleEndian, undefined);
    EXPECT_EQ(dv.count(), 1u);
    EXPECT_EQ(dv.size(), 1u);
    EXPECT_EQ(dv.toInt64(0), 0x7F);
    EXPECT_FLOAT_EQ(dv.toFloat(0), 127.0f);
}

// ==================== Large Buffer Tests ====================

TEST_F(DataValueTest_801, LargeBufferRead_801) {
    std::vector<byte> buf(1000, 0xAB);
    DataValue dv(undefined);
    int result = dv.read(buf.data(), buf.size(), littleEndian);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(dv.count(), 1000u);
    EXPECT_EQ(dv.size(), 1000u);
    
    // Check first and last elements
    EXPECT_EQ(dv.toInt64(0), 0xAB);
    EXPECT_EQ(dv.toInt64(999), 0xAB);
}

// ==================== Read from String with Hex Values ====================

TEST_F(DataValueTest_801, ReadFromStringHexValues_801) {
    DataValue dv(undefined);
    std::string hexStr = "FF 00 AB";
    int result = dv.read(hexStr);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(dv.count(), 3u);
    EXPECT_EQ(dv.toInt64(0), 0xFF);
    EXPECT_EQ(dv.toInt64(1), 0x00);
    EXPECT_EQ(dv.toInt64(2), 0xAB);
}

// ==================== Ok Flag Tests ====================

TEST_F(DataValueTest_801, OkFlagTrueAfterSuccessfulConversion_801) {
    const byte buf[] = {42};
    DataValue dv(buf, sizeof(buf), littleEndian, undefined);
    dv.toFloat(0);
    EXPECT_TRUE(dv.ok());
    dv.toInt64(0);
    EXPECT_TRUE(dv.ok());
    dv.toUint32(0);
    EXPECT_TRUE(dv.ok());
}

// ==================== Copy Roundtrip Test ====================

TEST_F(DataValueTest_801, CopyRoundtrip_801) {
    const byte input[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    DataValue dv(input, sizeof(input), littleEndian, undefined);
    
    byte output[5] = {0};
    size_t copied = dv.copy(output, littleEndian);
    EXPECT_EQ(copied, sizeof(input));
    
    for (size_t i = 0; i < sizeof(input); ++i) {
        EXPECT_EQ(output[i], input[i]);
    }
}
