#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <cstring>
#include <sstream>

using namespace Exiv2;

// Test fixture for DataValue tests
class DataValueTest_802 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// ==================== Construction Tests ====================

TEST_F(DataValueTest_802, DefaultConstruction_WithUndefinedType_802) {
    DataValue dv(undefined);
    EXPECT_EQ(dv.typeId(), undefined);
    EXPECT_EQ(dv.count(), 0u);
    EXPECT_EQ(dv.size(), 0u);
}

TEST_F(DataValueTest_802, ConstructionWithByteTypeId_802) {
    DataValue dv(unsignedByte);
    EXPECT_EQ(dv.typeId(), unsignedByte);
    EXPECT_EQ(dv.count(), 0u);
}

TEST_F(DataValueTest_802, ConstructionWithBufferAndLength_802) {
    const byte data[] = {0x01, 0x02, 0x03};
    DataValue dv(data, 3, littleEndian, undefined);
    EXPECT_EQ(dv.typeId(), undefined);
    EXPECT_EQ(dv.count(), 3u);
    EXPECT_EQ(dv.size(), 3u);
}

// ==================== Read Tests ====================

TEST_F(DataValueTest_802, ReadFromByteBuffer_802) {
    DataValue dv(undefined);
    const byte data[] = {0x10, 0x20, 0x30, 0x40};
    int result = dv.read(data, 4, littleEndian);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(dv.count(), 4u);
    EXPECT_EQ(dv.size(), 4u);
}

TEST_F(DataValueTest_802, ReadFromEmptyByteBuffer_802) {
    DataValue dv(undefined);
    const byte data[] = {0x00};
    int result = dv.read(data, 0, littleEndian);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(dv.count(), 0u);
    EXPECT_EQ(dv.size(), 0u);
}

TEST_F(DataValueTest_802, ReadFromString_802) {
    DataValue dv(undefined);
    std::string buf = "48 65 6C 6C 6F";
    int result = dv.read(buf);
    EXPECT_EQ(result, 0);
    EXPECT_GT(dv.count(), 0u);
}

TEST_F(DataValueTest_802, ReadFromEmptyString_802) {
    DataValue dv(undefined);
    std::string buf = "";
    int result = dv.read(buf);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(dv.count(), 0u);
}

// ==================== Copy Tests ====================

TEST_F(DataValueTest_802, CopyToBuffer_802) {
    const byte data[] = {0xAA, 0xBB, 0xCC};
    DataValue dv(data, 3, littleEndian, undefined);
    
    byte buf[3] = {0};
    size_t copied = dv.copy(buf, littleEndian);
    EXPECT_EQ(copied, 3u);
    EXPECT_EQ(buf[0], 0xAA);
    EXPECT_EQ(buf[1], 0xBB);
    EXPECT_EQ(buf[2], 0xCC);
}

TEST_F(DataValueTest_802, CopyEmptyValue_802) {
    DataValue dv(undefined);
    byte buf[1] = {0xFF};
    size_t copied = dv.copy(buf, littleEndian);
    EXPECT_EQ(copied, 0u);
}

// ==================== Count and Size Tests ====================

TEST_F(DataValueTest_802, CountMatchesNumberOfBytes_802) {
    const byte data[] = {1, 2, 3, 4, 5};
    DataValue dv(data, 5, littleEndian, undefined);
    EXPECT_EQ(dv.count(), 5u);
}

TEST_F(DataValueTest_802, SizeMatchesNumberOfBytes_802) {
    const byte data[] = {1, 2, 3, 4, 5};
    DataValue dv(data, 5, littleEndian, undefined);
    EXPECT_EQ(dv.size(), 5u);
}

// ==================== Write Tests ====================

TEST_F(DataValueTest_802, WriteToOutputStream_802) {
    const byte data[] = {0x41, 0x42, 0x43};
    DataValue dv(data, 3, littleEndian, undefined);
    
    std::ostringstream os;
    dv.write(os);
    std::string output = os.str();
    EXPECT_FALSE(output.empty());
}

TEST_F(DataValueTest_802, WriteEmptyValueToOutputStream_802) {
    DataValue dv(undefined);
    std::ostringstream os;
    dv.write(os);
    // Empty DataValue should produce empty or minimal output
    // Just verify it doesn't crash
}

// ==================== toString Tests ====================

TEST_F(DataValueTest_802, ToStringWithIndex_802) {
    const byte data[] = {0x41, 0x42, 0x43};
    DataValue dv(data, 3, littleEndian, undefined);
    
    std::string str0 = dv.toString(0);
    std::string str1 = dv.toString(1);
    std::string str2 = dv.toString(2);
    
    EXPECT_FALSE(str0.empty());
    EXPECT_FALSE(str1.empty());
    EXPECT_FALSE(str2.empty());
}

TEST_F(DataValueTest_802, ToStringOutOfRange_802) {
    const byte data[] = {0x41};
    DataValue dv(data, 1, littleEndian, undefined);
    
    // Accessing out of range should throw
    EXPECT_THROW(dv.toString(5), std::out_of_range);
}

// ==================== toInt64 Tests ====================

TEST_F(DataValueTest_802, ToInt64WithValidIndex_802) {
    const byte data[] = {0x0A, 0x14, 0x1E};
    DataValue dv(data, 3, littleEndian, undefined);
    
    EXPECT_EQ(dv.toInt64(0), 0x0A);
    EXPECT_EQ(dv.toInt64(1), 0x14);
    EXPECT_EQ(dv.toInt64(2), 0x1E);
    EXPECT_TRUE(dv.ok());
}

TEST_F(DataValueTest_802, ToInt64ZeroValue_802) {
    const byte data[] = {0x00};
    DataValue dv(data, 1, littleEndian, undefined);
    
    EXPECT_EQ(dv.toInt64(0), 0);
    EXPECT_TRUE(dv.ok());
}

TEST_F(DataValueTest_802, ToInt64MaxByteValue_802) {
    const byte data[] = {0xFF};
    DataValue dv(data, 1, littleEndian, undefined);
    
    EXPECT_EQ(dv.toInt64(0), 0xFF);
    EXPECT_TRUE(dv.ok());
}

TEST_F(DataValueTest_802, ToInt64OutOfRange_802) {
    const byte data[] = {0x0A};
    DataValue dv(data, 1, littleEndian, undefined);
    
    EXPECT_THROW(dv.toInt64(5), std::out_of_range);
}

// ==================== toUint32 Tests ====================

TEST_F(DataValueTest_802, ToUint32WithValidIndex_802) {
    const byte data[] = {0x0A, 0x14};
    DataValue dv(data, 2, littleEndian, undefined);
    
    EXPECT_EQ(dv.toUint32(0), 0x0Au);
    EXPECT_EQ(dv.toUint32(1), 0x14u);
    EXPECT_TRUE(dv.ok());
}

TEST_F(DataValueTest_802, ToUint32OutOfRange_802) {
    const byte data[] = {0x0A};
    DataValue dv(data, 1, littleEndian, undefined);
    
    EXPECT_THROW(dv.toUint32(10), std::out_of_range);
}

// ==================== toFloat Tests ====================

TEST_F(DataValueTest_802, ToFloatWithValidIndex_802) {
    const byte data[] = {0x0A, 0x14};
    DataValue dv(data, 2, littleEndian, undefined);
    
    EXPECT_FLOAT_EQ(dv.toFloat(0), 10.0f);
    EXPECT_FLOAT_EQ(dv.toFloat(1), 20.0f);
    EXPECT_TRUE(dv.ok());
}

TEST_F(DataValueTest_802, ToFloatOutOfRange_802) {
    const byte data[] = {0x0A};
    DataValue dv(data, 1, littleEndian, undefined);
    
    EXPECT_THROW(dv.toFloat(5), std::out_of_range);
}

// ==================== toRational Tests ====================

TEST_F(DataValueTest_802, ToRationalWithValidIndex_802) {
    const byte data[] = {0x05, 0x0A, 0x0F};
    DataValue dv(data, 3, littleEndian, undefined);
    
    Rational r0 = dv.toRational(0);
    EXPECT_EQ(r0.first, 5);
    EXPECT_EQ(r0.second, 1);
    EXPECT_TRUE(dv.ok());
    
    Rational r1 = dv.toRational(1);
    EXPECT_EQ(r1.first, 10);
    EXPECT_EQ(r1.second, 1);
    
    Rational r2 = dv.toRational(2);
    EXPECT_EQ(r2.first, 15);
    EXPECT_EQ(r2.second, 1);
}

TEST_F(DataValueTest_802, ToRationalZeroValue_802) {
    const byte data[] = {0x00};
    DataValue dv(data, 1, littleEndian, undefined);
    
    Rational r = dv.toRational(0);
    EXPECT_EQ(r.first, 0);
    EXPECT_EQ(r0.second, 1);
    EXPECT_TRUE(dv.ok());
}

TEST_F(DataValueTest_802, ToRationalOutOfRange_802) {
    const byte data[] = {0x05};
    DataValue dv(data, 1, littleEndian, undefined);
    
    EXPECT_THROW(dv.toRational(5), std::out_of_range);
}

TEST_F(DataValueTest_802, ToRationalSetsOkTrue_802) {
    const byte data[] = {0x07};
    DataValue dv(data, 1, littleEndian, undefined);
    
    dv.toRational(0);
    EXPECT_TRUE(dv.ok());
}

// ==================== Clone Tests ====================

TEST_F(DataValueTest_802, ClonePreservesData_802) {
    const byte data[] = {0x01, 0x02, 0x03};
    DataValue dv(data, 3, littleEndian, undefined);
    
    auto cloned = dv.clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->typeId(), undefined);
    EXPECT_EQ(cloned->count(), 3u);
    EXPECT_EQ(cloned->size(), 3u);
}

TEST_F(DataValueTest_802, CloneEmptyValue_802) {
    DataValue dv(undefined);
    auto cloned = dv.clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->count(), 0u);
    EXPECT_EQ(cloned->size(), 0u);
}

// ==================== Re-read (overwrite) Tests ====================

TEST_F(DataValueTest_802, ReadOverwritesPreviousData_802) {
    DataValue dv(undefined);
    
    const byte data1[] = {0x01, 0x02, 0x03};
    dv.read(data1, 3, littleEndian);
    EXPECT_EQ(dv.count(), 3u);
    
    const byte data2[] = {0x0A, 0x0B};
    dv.read(data2, 2, littleEndian);
    EXPECT_EQ(dv.count(), 2u);
    EXPECT_EQ(dv.toInt64(0), 0x0A);
    EXPECT_EQ(dv.toInt64(1), 0x0B);
}

// ==================== Boundary Tests ====================

TEST_F(DataValueTest_802, SingleByteData_802) {
    const byte data[] = {0xFF};
    DataValue dv(data, 1, littleEndian, undefined);
    
    EXPECT_EQ(dv.count(), 1u);
    EXPECT_EQ(dv.size(), 1u);
    EXPECT_EQ(dv.toInt64(0), 0xFF);
    EXPECT_EQ(dv.toUint32(0), 0xFFu);
}

TEST_F(DataValueTest_802, LargeData_802) {
    std::vector<byte> data(1000, 0x42);
    DataValue dv(data.data(), data.size(), littleEndian, undefined);
    
    EXPECT_EQ(dv.count(), 1000u);
    EXPECT_EQ(dv.size(), 1000u);
    EXPECT_EQ(dv.toInt64(0), 0x42);
    EXPECT_EQ(dv.toInt64(999), 0x42);
}

// ==================== ByteOrder Independence Tests ====================

TEST_F(DataValueTest_802, ReadWithBigEndian_802) {
    const byte data[] = {0x01, 0x02};
    DataValue dv(data, 2, bigEndian, undefined);
    
    EXPECT_EQ(dv.count(), 2u);
    EXPECT_EQ(dv.toInt64(0), 0x01);
    EXPECT_EQ(dv.toInt64(1), 0x02);
}

TEST_F(DataValueTest_802, CopyWithBigEndian_802) {
    const byte data[] = {0xAA, 0xBB};
    DataValue dv(data, 2, littleEndian, undefined);
    
    byte buf[2] = {0};
    size_t copied = dv.copy(buf, bigEndian);
    EXPECT_EQ(copied, 2u);
    EXPECT_EQ(buf[0], 0xAA);
    EXPECT_EQ(buf[1], 0xBB);
}

// ==================== ok() State Tests ====================

TEST_F(DataValueTest_802, OkReturnsTrueInitially_802) {
    DataValue dv(undefined);
    EXPECT_TRUE(dv.ok());
}

TEST_F(DataValueTest_802, OkReturnsTrueAfterSuccessfulConversion_802) {
    const byte data[] = {0x05};
    DataValue dv(data, 1, littleEndian, undefined);
    
    dv.toInt64(0);
    EXPECT_TRUE(dv.ok());
    
    dv.toFloat(0);
    EXPECT_TRUE(dv.ok());
    
    dv.toRational(0);
    EXPECT_TRUE(dv.ok());
}

// ==================== Value base class methods ====================

TEST_F(DataValueTest_802, TypeIdReturnsCorrectType_802) {
    DataValue dv1(undefined);
    EXPECT_EQ(dv1.typeId(), undefined);
    
    DataValue dv2(unsignedByte);
    EXPECT_EQ(dv2.typeId(), unsignedByte);
}

TEST_F(DataValueTest_802, SizeDataAreaReturnsZero_802) {
    DataValue dv(undefined);
    EXPECT_EQ(dv.sizeDataArea(), 0u);
}

TEST_F(DataValueTest_802, DataAreaReturnsEmptyBuffer_802) {
    DataValue dv(undefined);
    DataBuf buf = dv.dataArea();
    EXPECT_EQ(buf.size(), 0u);
}

// ==================== String representation consistency ====================

TEST_F(DataValueTest_802, ToStringNoArgMatchesFirstElement_802) {
    const byte data[] = {0x41};
    DataValue dv(data, 1, littleEndian, undefined);
    
    std::string strDefault = dv.toString();
    std::string str0 = dv.toString(0);
    // The no-arg toString should contain at least the representation of the first element
    EXPECT_FALSE(strDefault.empty());
}
#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <cstring>
#include <sstream>
#include <vector>

using namespace Exiv2;

class DataValueTest_802 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== Construction Tests ====================

TEST_F(DataValueTest_802, DefaultConstruction_WithUndefinedType_802) {
    DataValue dv(undefined);
    EXPECT_EQ(dv.typeId(), undefined);
    EXPECT_EQ(dv.count(), 0u);
    EXPECT_EQ(dv.size(), 0u);
}

TEST_F(DataValueTest_802, ConstructionWithByteTypeId_802) {
    DataValue dv(unsignedByte);
    EXPECT_EQ(dv.typeId(), unsignedByte);
    EXPECT_EQ(dv.count(), 0u);
}

TEST_F(DataValueTest_802, ConstructionWithBufferAndLength_802) {
    const byte data[] = {0x01, 0x02, 0x03};
    DataValue dv(data, 3, littleEndian, undefined);
    EXPECT_EQ(dv.typeId(), undefined);
    EXPECT_EQ(dv.count(), 3u);
    EXPECT_EQ(dv.size(), 3u);
}

// ==================== Read Tests ====================

TEST_F(DataValueTest_802, ReadFromByteBuffer_802) {
    DataValue dv(undefined);
    const byte data[] = {0x10, 0x20, 0x30, 0x40};
    int result = dv.read(data, 4, littleEndian);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(dv.count(), 4u);
    EXPECT_EQ(dv.size(), 4u);
}

TEST_F(DataValueTest_802, ReadFromEmptyByteBuffer_802) {
    DataValue dv(undefined);
    const byte* data = nullptr;
    int result = dv.read(data, 0, littleEndian);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(dv.count(), 0u);
    EXPECT_EQ(dv.size(), 0u);
}

TEST_F(DataValueTest_802, ReadFromString_802) {
    DataValue dv(undefined);
    std::string buf = "48 65 6C 6C 6F";
    int result = dv.read(buf);
    EXPECT_EQ(result, 0);
    EXPECT_GT(dv.count(), 0u);
}

TEST_F(DataValueTest_802, ReadFromEmptyString_802) {
    DataValue dv(undefined);
    std::string buf = "";
    int result = dv.read(buf);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(dv.count(), 0u);
}

// ==================== Copy Tests ====================

TEST_F(DataValueTest_802, CopyToBuffer_802) {
    const byte data[] = {0xAA, 0xBB, 0xCC};
    DataValue dv(data, 3, littleEndian, undefined);

    byte buf[3] = {0};
    size_t copied = dv.copy(buf, littleEndian);
    EXPECT_EQ(copied, 3u);
    EXPECT_EQ(buf[0], 0xAA);
    EXPECT_EQ(buf[1], 0xBB);
    EXPECT_EQ(buf[2], 0xCC);
}

TEST_F(DataValueTest_802, CopyEmptyValue_802) {
    DataValue dv(undefined);
    byte buf[1] = {0xFF};
    size_t copied = dv.copy(buf, littleEndian);
    EXPECT_EQ(copied, 0u);
}

// ==================== Count and Size Tests ====================

TEST_F(DataValueTest_802, CountMatchesNumberOfBytes_802) {
    const byte data[] = {1, 2, 3, 4, 5};
    DataValue dv(data, 5, littleEndian, undefined);
    EXPECT_EQ(dv.count(), 5u);
}

TEST_F(DataValueTest_802, SizeMatchesNumberOfBytes_802) {
    const byte data[] = {1, 2, 3, 4, 5};
    DataValue dv(data, 5, littleEndian, undefined);
    EXPECT_EQ(dv.size(), 5u);
}

// ==================== Write Tests ====================

TEST_F(DataValueTest_802, WriteToOutputStream_802) {
    const byte data[] = {0x41, 0x42, 0x43};
    DataValue dv(data, 3, littleEndian, undefined);

    std::ostringstream os;
    dv.write(os);
    std::string output = os.str();
    EXPECT_FALSE(output.empty());
}

TEST_F(DataValueTest_802, WriteEmptyValueToOutputStream_802) {
    DataValue dv(undefined);
    std::ostringstream os;
    dv.write(os);
    // Just verify it doesn't crash
}

// ==================== toString Tests ====================

TEST_F(DataValueTest_802, ToStringWithIndex_802) {
    const byte data[] = {0x41, 0x42, 0x43};
    DataValue dv(data, 3, littleEndian, undefined);

    std::string str0 = dv.toString(0);
    std::string str1 = dv.toString(1);
    std::string str2 = dv.toString(2);

    EXPECT_FALSE(str0.empty());
    EXPECT_FALSE(str1.empty());
    EXPECT_FALSE(str2.empty());
}

TEST_F(DataValueTest_802, ToStringOutOfRange_802) {
    const byte data[] = {0x41};
    DataValue dv(data, 1, littleEndian, undefined);

    EXPECT_THROW(dv.toString(5), std::out_of_range);
}

// ==================== toInt64 Tests ====================

TEST_F(DataValueTest_802, ToInt64WithValidIndex_802) {
    const byte data[] = {0x0A, 0x14, 0x1E};
    DataValue dv(data, 3, littleEndian, undefined);

    EXPECT_EQ(dv.toInt64(0), 0x0A);
    EXPECT_EQ(dv.toInt64(1), 0x14);
    EXPECT_EQ(dv.toInt64(2), 0x1E);
    EXPECT_TRUE(dv.ok());
}

TEST_F(DataValueTest_802, ToInt64ZeroValue_802) {
    const byte data[] = {0x00};
    DataValue dv(data, 1, littleEndian, undefined);

    EXPECT_EQ(dv.toInt64(0), 0);
    EXPECT_TRUE(dv.ok());
}

TEST_F(DataValueTest_802, ToInt64MaxByteValue_802) {
    const byte data[] = {0xFF};
    DataValue dv(data, 1, littleEndian, undefined);

    EXPECT_EQ(dv.toInt64(0), 0xFF);
    EXPECT_TRUE(dv.ok());
}

TEST_F(DataValueTest_802, ToInt64OutOfRange_802) {
    const byte data[] = {0x0A};
    DataValue dv(data, 1, littleEndian, undefined);

    EXPECT_THROW(dv.toInt64(5), std::out_of_range);
}

// ==================== toUint32 Tests ====================

TEST_F(DataValueTest_802, ToUint32WithValidIndex_802) {
    const byte data[] = {0x0A, 0x14};
    DataValue dv(data, 2, littleEndian, undefined);

    EXPECT_EQ(dv.toUint32(0), 0x0Au);
    EXPECT_EQ(dv.toUint32(1), 0x14u);
    EXPECT_TRUE(dv.ok());
}

TEST_F(DataValueTest_802, ToUint32OutOfRange_802) {
    const byte data[] = {0x0A};
    DataValue dv(data, 1, littleEndian, undefined);

    EXPECT_THROW(dv.toUint32(10), std::out_of_range);
}

// ==================== toFloat Tests ====================

TEST_F(DataValueTest_802, ToFloatWithValidIndex_802) {
    const byte data[] = {0x0A, 0x14};
    DataValue dv(data, 2, littleEndian, undefined);

    EXPECT_FLOAT_EQ(dv.toFloat(0), 10.0f);
    EXPECT_FLOAT_EQ(dv.toFloat(1), 20.0f);
    EXPECT_TRUE(dv.ok());
}

TEST_F(DataValueTest_802, ToFloatOutOfRange_802) {
    const byte data[] = {0x0A};
    DataValue dv(data, 1, littleEndian, undefined);

    EXPECT_THROW(dv.toFloat(5), std::out_of_range);
}

// ==================== toRational Tests ====================

TEST_F(DataValueTest_802, ToRationalWithValidIndex_802) {
    const byte data[] = {0x05, 0x0A, 0x0F};
    DataValue dv(data, 3, littleEndian, undefined);

    Rational r0 = dv.toRational(0);
    EXPECT_EQ(r0.first, 5);
    EXPECT_EQ(r0.second, 1);
    EXPECT_TRUE(dv.ok());

    Rational r1 = dv.toRational(1);
    EXPECT_EQ(r1.first, 10);
    EXPECT_EQ(r1.second, 1);

    Rational r2 = dv.toRational(2);
    EXPECT_EQ(r2.first, 15);
    EXPECT_EQ(r2.second, 1);
}

TEST_F(DataValueTest_802, ToRationalZeroValue_802) {
    const byte data[] = {0x00};
    DataValue dv(data, 1, littleEndian, undefined);

    Rational r = dv.toRational(0);
    EXPECT_EQ(r.first, 0);
    EXPECT_EQ(r.second, 1);
    EXPECT_TRUE(dv.ok());
}

TEST_F(DataValueTest_802, ToRationalOutOfRange_802) {
    const byte data[] = {0x05};
    DataValue dv(data, 1, littleEndian, undefined);

    EXPECT_THROW(dv.toRational(5), std::out_of_range);
}

TEST_F(DataValueTest_802, ToRationalSetsOkTrue_802) {
    const byte data[] = {0x07};
    DataValue dv(data, 1, littleEndian, undefined);

    dv.toRational(0);
    EXPECT_TRUE(dv.ok());
}

// ==================== Clone Tests ====================

TEST_F(DataValueTest_802, ClonePreservesData_802) {
    const byte data[] = {0x01, 0x02, 0x03};
    DataValue dv(data, 3, littleEndian, undefined);

    auto cloned = dv.clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->typeId(), undefined);
    EXPECT_EQ(cloned->count(), 3u);
    EXPECT_EQ(cloned->size(), 3u);
}

TEST_F(DataValueTest_802, CloneEmptyValue_802) {
    DataValue dv(undefined);
    auto cloned = dv.clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->count(), 0u);
    EXPECT_EQ(cloned->size(), 0u);
}

// ==================== Re-read (overwrite) Tests ====================

TEST_F(DataValueTest_802, ReadOverwritesPreviousData_802) {
    DataValue dv(undefined);

    const byte data1[] = {0x01, 0x02, 0x03};
    dv.read(data1, 3, littleEndian);
    EXPECT_EQ(dv.count(), 3u);

    const byte data2[] = {0x0A, 0x0B};
    dv.read(data2, 2, littleEndian);
    EXPECT_EQ(dv.count(), 2u);
    EXPECT_EQ(dv.toInt64(0), 0x0A);
    EXPECT_EQ(dv.toInt64(1), 0x0B);
}

// ==================== Boundary Tests ====================

TEST_F(DataValueTest_802, SingleByteData_802) {
    const byte data[] = {0xFF};
    DataValue dv(data, 1, littleEndian, undefined);

    EXPECT_EQ(dv.count(), 1u);
    EXPECT_EQ(dv.size(), 1u);
    EXPECT_EQ(dv.toInt64(0), 0xFF);
    EXPECT_EQ(dv.toUint32(0), 0xFFu);
}

TEST_F(DataValueTest_802, LargeData_802) {
    std::vector<byte> data(1000, 0x42);
    DataValue dv(data.data(), data.size(), littleEndian, undefined);

    EXPECT_EQ(dv.count(), 1000u);
    EXPECT_EQ(dv.size(), 1000u);
    EXPECT_EQ(dv.toInt64(0), 0x42);
    EXPECT_EQ(dv.toInt64(999), 0x42);
}

// ==================== ByteOrder Independence Tests ====================

TEST_F(DataValueTest_802, ReadWithBigEndian_802) {
    const byte data[] = {0x01, 0x02};
    DataValue dv(data, 2, bigEndian, undefined);

    EXPECT_EQ(dv.count(), 2u);
    EXPECT_EQ(dv.toInt64(0), 0x01);
    EXPECT_EQ(dv.toInt64(1), 0x02);
}

TEST_F(DataValueTest_802, CopyWithBigEndian_802) {
    const byte data[] = {0xAA, 0xBB};
    DataValue dv(data, 2, littleEndian, undefined);

    byte buf[2] = {0};
    size_t copied = dv.copy(buf, bigEndian);
    EXPECT_EQ(copied, 2u);
    EXPECT_EQ(buf[0], 0xAA);
    EXPECT_EQ(buf[1], 0xBB);
}

// ==================== ok() State Tests ====================

TEST_F(DataValueTest_802, OkReturnsTrueInitially_802) {
    DataValue dv(undefined);
    EXPECT_TRUE(dv.ok());
}

TEST_F(DataValueTest_802, OkReturnsTrueAfterSuccessfulConversion_802) {
    const byte data[] = {0x05};
    DataValue dv(data, 1, littleEndian, undefined);

    dv.toInt64(0);
    EXPECT_TRUE(dv.ok());

    dv.toFloat(0);
    EXPECT_TRUE(dv.ok());

    dv.toRational(0);
    EXPECT_TRUE(dv.ok());
}

// ==================== Value base class methods ====================

TEST_F(DataValueTest_802, TypeIdReturnsCorrectType_802) {
    DataValue dv1(undefined);
    EXPECT_EQ(dv1.typeId(), undefined);

    DataValue dv2(unsignedByte);
    EXPECT_EQ(dv2.typeId(), unsignedByte);
}

TEST_F(DataValueTest_802, SizeDataAreaReturnsZero_802) {
    DataValue dv(undefined);
    EXPECT_EQ(dv.sizeDataArea(), 0u);
}

TEST_F(DataValueTest_802, DataAreaReturnsEmptyBuffer_802) {
    DataValue dv(undefined);
    DataBuf buf = dv.dataArea();
    EXPECT_EQ(buf.size(), 0u);
}

TEST_F(DataValueTest_802, ToStringNoArg_802) {
    const byte data[] = {0x41};
    DataValue dv(data, 1, littleEndian, undefined);

    std::string strDefault = dv.toString();
    EXPECT_FALSE(strDefault.empty());
}
