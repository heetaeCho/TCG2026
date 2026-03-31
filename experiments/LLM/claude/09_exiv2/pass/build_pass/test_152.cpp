#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <exiv2/types.hpp>
#include <sstream>
#include <cstring>

using namespace Exiv2;

// ============================================================
// Tests for ValueType<T>::size()
// ============================================================

class ValueTypeSizeTest_152 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that default-constructed ValueType<uint16_t> has size 0
TEST_F(ValueTypeSizeTest_152, DefaultConstructedUint16HasZeroSize_152) {
    ValueType<uint16_t> v;
    EXPECT_EQ(0u, v.size());
}

// Test that default-constructed ValueType<uint32_t> has size 0
TEST_F(ValueTypeSizeTest_152, DefaultConstructedUint32HasZeroSize_152) {
    ValueType<uint32_t> v;
    EXPECT_EQ(0u, v.size());
}

// Test that default-constructed ValueType<int16_t> has size 0
TEST_F(ValueTypeSizeTest_152, DefaultConstructedInt16HasZeroSize_152) {
    ValueType<int16_t> v;
    EXPECT_EQ(0u, v.size());
}

// Test that default-constructed ValueType<int32_t> has size 0
TEST_F(ValueTypeSizeTest_152, DefaultConstructedInt32HasZeroSize_152) {
    ValueType<int32_t> v;
    EXPECT_EQ(0u, v.size());
}

// Test that ValueType<uint16_t> constructed with a single value has correct size
TEST_F(ValueTypeSizeTest_152, SingleValueUint16HasCorrectSize_152) {
    ValueType<uint16_t> v(static_cast<uint16_t>(42));
    size_t expectedSize = TypeInfo::typeSize(v.typeId()) * v.count();
    EXPECT_EQ(expectedSize, v.size());
    EXPECT_EQ(1u, v.count());
}

// Test that ValueType<uint32_t> constructed with a single value has correct size
TEST_F(ValueTypeSizeTest_152, SingleValueUint32HasCorrectSize_152) {
    ValueType<uint32_t> v(static_cast<uint32_t>(100));
    size_t expectedSize = TypeInfo::typeSize(v.typeId()) * v.count();
    EXPECT_EQ(expectedSize, v.size());
    EXPECT_EQ(1u, v.count());
}

// Test that ValueType<Rational> constructed with a value has correct size
TEST_F(ValueTypeSizeTest_152, SingleValueRationalHasCorrectSize_152) {
    Rational r(1, 2);
    ValueType<Rational> v(r);
    size_t expectedSize = TypeInfo::typeSize(v.typeId()) * v.count();
    EXPECT_EQ(expectedSize, v.size());
    EXPECT_EQ(1u, v.count());
}

// Test that ValueType<URational> constructed with a value has correct size
TEST_F(ValueTypeSizeTest_152, SingleValueURationalHasCorrectSize_152) {
    URational r(3, 4);
    ValueType<URational> v(r);
    size_t expectedSize = TypeInfo::typeSize(v.typeId()) * v.count();
    EXPECT_EQ(expectedSize, v.size());
    EXPECT_EQ(1u, v.count());
}

// Test size after adding multiple values via value_ member
TEST_F(ValueTypeSizeTest_152, MultipleValuesUint16HasCorrectSize_152) {
    ValueType<uint16_t> v;
    v.value_.push_back(1);
    v.value_.push_back(2);
    v.value_.push_back(3);
    size_t expectedSize = TypeInfo::typeSize(v.typeId()) * 3;
    EXPECT_EQ(expectedSize, v.size());
    EXPECT_EQ(3u, v.count());
}

// Test size after reading from a buffer (uint16_t, little-endian)
TEST_F(ValueTypeSizeTest_152, ReadFromBufferUint16Size_152) {
    byte buf[6];
    // Store three uint16_t values in little-endian
    buf[0] = 0x01; buf[1] = 0x00; // 1
    buf[2] = 0x02; buf[3] = 0x00; // 2
    buf[4] = 0x03; buf[5] = 0x00; // 3
    ValueType<uint16_t> v;
    v.read(buf, 6, littleEndian);
    size_t expectedSize = TypeInfo::typeSize(v.typeId()) * v.count();
    EXPECT_EQ(expectedSize, v.size());
    EXPECT_EQ(3u, v.count());
}

// Test size after reading from a buffer (uint32_t, big-endian)
TEST_F(ValueTypeSizeTest_152, ReadFromBufferUint32Size_152) {
    byte buf[8];
    // Store two uint32_t values in big-endian
    buf[0] = 0x00; buf[1] = 0x00; buf[2] = 0x00; buf[3] = 0x0A; // 10
    buf[4] = 0x00; buf[5] = 0x00; buf[6] = 0x00; buf[7] = 0x14; // 20
    ValueType<uint32_t> v;
    v.read(buf, 8, bigEndian);
    size_t expectedSize = TypeInfo::typeSize(v.typeId()) * v.count();
    EXPECT_EQ(expectedSize, v.size());
    EXPECT_EQ(2u, v.count());
}

// Test that size is consistent with typeSize * count for float type
TEST_F(ValueTypeSizeTest_152, SingleFloatValueHasCorrectSize_152) {
    ValueType<float> v(3.14f);
    size_t typeSize = TypeInfo::typeSize(v.typeId());
    EXPECT_EQ(typeSize * v.count(), v.size());
}

// Test that size is consistent with typeSize * count for double type
TEST_F(ValueTypeSizeTest_152, SingleDoubleValueHasCorrectSize_152) {
    ValueType<double> v(2.718);
    size_t typeSize = TypeInfo::typeSize(v.typeId());
    EXPECT_EQ(typeSize * v.count(), v.size());
}

// Test size after copy construction
TEST_F(ValueTypeSizeTest_152, CopyConstructedHasSameSize_152) {
    ValueType<uint16_t> v;
    v.value_.push_back(10);
    v.value_.push_back(20);
    ValueType<uint16_t> v2(v);
    EXPECT_EQ(v.size(), v2.size());
    EXPECT_EQ(v.count(), v2.count());
}

// Test size after assignment
TEST_F(ValueTypeSizeTest_152, AssignedHasSameSize_152) {
    ValueType<uint16_t> v;
    v.value_.push_back(10);
    v.value_.push_back(20);
    v.value_.push_back(30);
    ValueType<uint16_t> v2;
    v2 = v;
    EXPECT_EQ(v.size(), v2.size());
    EXPECT_EQ(v.count(), v2.count());
}

// Test size with Rational having multiple values
TEST_F(ValueTypeSizeTest_152, MultipleRationalValuesSize_152) {
    ValueType<Rational> v;
    v.value_.push_back(Rational(1, 2));
    v.value_.push_back(Rational(3, 4));
    v.value_.push_back(Rational(5, 6));
    v.value_.push_back(Rational(7, 8));
    size_t typeSize = TypeInfo::typeSize(v.typeId());
    EXPECT_EQ(typeSize * 4, v.size());
    EXPECT_EQ(4u, v.count());
}

// Test size remains zero after clearing values
TEST_F(ValueTypeSizeTest_152, ClearedValuesHaveZeroSize_152) {
    ValueType<uint16_t> v;
    v.value_.push_back(1);
    v.value_.push_back(2);
    EXPECT_GT(v.size(), 0u);
    v.value_.clear();
    EXPECT_EQ(0u, v.size());
}

// Test that size is proportional to count
TEST_F(ValueTypeSizeTest_152, SizeIsProportionalToCount_152) {
    ValueType<uint32_t> v;
    size_t typeSize = TypeInfo::typeSize(v.typeId());
    
    v.value_.push_back(1);
    EXPECT_EQ(typeSize * 1, v.size());
    
    v.value_.push_back(2);
    EXPECT_EQ(typeSize * 2, v.size());
    
    v.value_.push_back(3);
    EXPECT_EQ(typeSize * 3, v.size());
}

// Test reading from string and checking size for uint16_t
TEST_F(ValueTypeSizeTest_152, ReadFromStringUint16Size_152) {
    ValueType<uint16_t> v;
    v.read("1 2 3 4 5");
    size_t typeSize = TypeInfo::typeSize(v.typeId());
    EXPECT_EQ(typeSize * 5, v.size());
    EXPECT_EQ(5u, v.count());
}

// Test reading from string and checking size for int32_t
TEST_F(ValueTypeSizeTest_152, ReadFromStringInt32Size_152) {
    ValueType<int32_t> v;
    v.read("10 20");
    size_t typeSize = TypeInfo::typeSize(v.typeId());
    EXPECT_EQ(typeSize * 2, v.size());
    EXPECT_EQ(2u, v.count());
}

// ============================================================
// Additional tests for other ValueType methods to ensure
// comprehensive coverage of the interface
// ============================================================

class ValueTypeGeneralTest_152 : public ::testing::Test {};

// Test typeId returns correct type for uint16_t
TEST_F(ValueTypeGeneralTest_152, TypeIdUint16_152) {
    ValueType<uint16_t> v;
    EXPECT_EQ(unsignedShort, v.typeId());
}

// Test typeId returns correct type for uint32_t
TEST_F(ValueTypeGeneralTest_152, TypeIdUint32_152) {
    ValueType<uint32_t> v;
    EXPECT_EQ(unsignedLong, v.typeId());
}

// Test typeId returns correct type for Rational
TEST_F(ValueTypeGeneralTest_152, TypeIdRational_152) {
    ValueType<Rational> v;
    EXPECT_EQ(signedRational, v.typeId());
}

// Test typeId returns correct type for URational
TEST_F(ValueTypeGeneralTest_152, TypeIdURational_152) {
    ValueType<URational> v;
    EXPECT_EQ(unsignedRational, v.typeId());
}

// Test toString for a single uint16_t value
TEST_F(ValueTypeGeneralTest_152, ToStringUint16_152) {
    ValueType<uint16_t> v(static_cast<uint16_t>(42));
    EXPECT_EQ("42", v.toString(0));
}

// Test toInt64 for uint32_t
TEST_F(ValueTypeGeneralTest_152, ToInt64Uint32_152) {
    ValueType<uint32_t> v(static_cast<uint32_t>(12345));
    EXPECT_EQ(12345, v.toInt64(0));
}

// Test toUint32 for uint16_t
TEST_F(ValueTypeGeneralTest_152, ToUint32Uint16_152) {
    ValueType<uint16_t> v(static_cast<uint16_t>(999));
    EXPECT_EQ(999u, v.toUint32(0));
}

// Test toFloat for Rational
TEST_F(ValueTypeGeneralTest_152, ToFloatRational_152) {
    Rational r(1, 2);
    ValueType<Rational> v(r);
    EXPECT_FLOAT_EQ(0.5f, v.toFloat(0));
}

// Test toFloat for URational
TEST_F(ValueTypeGeneralTest_152, ToFloatURational_152) {
    URational r(3, 4);
    ValueType<URational> v(r);
    EXPECT_FLOAT_EQ(0.75f, v.toFloat(0));
}

// Test toRational for Rational
TEST_F(ValueTypeGeneralTest_152, ToRationalRational_152) {
    Rational r(5, 7);
    ValueType<Rational> v(r);
    Rational result = v.toRational(0);
    EXPECT_EQ(5, result.first);
    EXPECT_EQ(7, result.second);
}

// Test toRational for URational
TEST_F(ValueTypeGeneralTest_152, ToRationalURational_152) {
    URational r(11, 13);
    ValueType<URational> v(r);
    Rational result = v.toRational(0);
    EXPECT_EQ(11, result.first);
    EXPECT_EQ(13, result.second);
}

// Test write to ostream
TEST_F(ValueTypeGeneralTest_152, WriteToStream_152) {
    ValueType<uint16_t> v;
    v.value_.push_back(10);
    v.value_.push_back(20);
    std::ostringstream os;
    v.write(os);
    std::string output = os.str();
    EXPECT_FALSE(output.empty());
}

// Test clone produces independent copy
TEST_F(ValueTypeGeneralTest_152, CloneProducesIndependentCopy_152) {
    ValueType<uint16_t> v;
    v.value_.push_back(42);
    auto cloned = v.clone();
    EXPECT_NE(nullptr, cloned.get());
    EXPECT_EQ(v.typeId(), cloned->typeId());
    EXPECT_EQ(v.count(), cloned->count());
    EXPECT_EQ(v.size(), cloned->size());
}

// Test sizeDataArea is 0 by default
TEST_F(ValueTypeGeneralTest_152, SizeDataAreaDefault_152) {
    ValueType<uint16_t> v;
    EXPECT_EQ(0u, v.sizeDataArea());
}

// Test setDataArea and sizeDataArea
TEST_F(ValueTypeGeneralTest_152, SetDataAreaAndSize_152) {
    ValueType<uint16_t> v;
    byte data[] = {0x01, 0x02, 0x03, 0x04};
    v.setDataArea(data, 4);
    EXPECT_EQ(4u, v.sizeDataArea());
}

// Test dataArea returns the data previously set
TEST_F(ValueTypeGeneralTest_152, DataAreaReturnsSetData_152) {
    ValueType<uint16_t> v;
    byte data[] = {0xAA, 0xBB, 0xCC};
    v.setDataArea(data, 3);
    DataBuf buf = v.dataArea();
    EXPECT_EQ(3u, buf.size());
}

// Test copy to buffer
TEST_F(ValueTypeGeneralTest_152, CopyToBuffer_152) {
    ValueType<uint16_t> v;
    v.value_.push_back(0x0102);
    byte buf[2] = {0};
    size_t copied = v.copy(buf, bigEndian);
    EXPECT_EQ(v.size(), copied);
}

// Test ok() returns true by default
TEST_F(ValueTypeGeneralTest_152, OkReturnsTrueByDefault_152) {
    ValueType<uint16_t> v;
    EXPECT_TRUE(v.ok());
}

// Test Value::create factory
TEST_F(ValueTypeGeneralTest_152, ValueCreateFactory_152) {
    auto val = Value::create(unsignedShort);
    EXPECT_NE(nullptr, val.get());
    EXPECT_EQ(unsignedShort, val->typeId());
}

// Test int16_t ValueType size
TEST_F(ValueTypeGeneralTest_152, Int16ValueTypeSize_152) {
    ValueType<int16_t> v;
    v.value_.push_back(-10);
    v.value_.push_back(20);
    size_t typeSize = TypeInfo::typeSize(v.typeId());
    EXPECT_EQ(typeSize * 2, v.size());
}

// Test toInt64 for Rational
TEST_F(ValueTypeGeneralTest_152, ToInt64Rational_152) {
    Rational r(10, 3);
    ValueType<Rational> v(r);
    int64_t result = v.toInt64(0);
    EXPECT_EQ(3, result); // 10/3 = 3 (integer division)
}

// Test toUint32 for URational
TEST_F(ValueTypeGeneralTest_152, ToUint32URational_152) {
    URational r(10, 3);
    ValueType<URational> v(r);
    uint32_t result = v.toUint32(0);
    EXPECT_EQ(3u, result); // 10/3 = 3 (integer division)
}

// Test toFloat for float ValueType
TEST_F(ValueTypeGeneralTest_152, ToFloatFloat_152) {
    ValueType<float> v(2.5f);
    EXPECT_FLOAT_EQ(2.5f, v.toFloat(0));
}

// Test toFloat for double ValueType
TEST_F(ValueTypeGeneralTest_152, ToFloatDouble_152) {
    ValueType<double> v(3.14);
    EXPECT_NEAR(3.14f, v.toFloat(0), 0.001f);
}

// Test toInt64 for float ValueType
TEST_F(ValueTypeGeneralTest_152, ToInt64Float_152) {
    ValueType<float> v(7.9f);
    int64_t result = v.toInt64(0);
    EXPECT_EQ(7, result);
}

// Test toInt64 for double ValueType
TEST_F(ValueTypeGeneralTest_152, ToInt64Double_152) {
    ValueType<double> v(99.1);
    int64_t result = v.toInt64(0);
    EXPECT_EQ(99, result);
}

// Test toRational for float ValueType
TEST_F(ValueTypeGeneralTest_152, ToRationalFloat_152) {
    ValueType<float> v(0.5f);
    Rational r = v.toRational(0);
    // Should give something that approximates 0.5
    if (r.second != 0) {
        float approx = static_cast<float>(r.first) / static_cast<float>(r.second);
        EXPECT_NEAR(0.5f, approx, 0.01f);
    }
}

// Test toRational for double ValueType
TEST_F(ValueTypeGeneralTest_152, ToRationalDouble_152) {
    ValueType<double> v(0.25);
    Rational r = v.toRational(0);
    if (r.second != 0) {
        double approx = static_cast<double>(r.first) / static_cast<double>(r.second);
        EXPECT_NEAR(0.25, approx, 0.01);
    }
}

// Test reading from string for Rational type
TEST_F(ValueTypeGeneralTest_152, ReadFromStringRational_152) {
    ValueType<Rational> v;
    v.read("1/2 3/4");
    EXPECT_EQ(2u, v.count());
    size_t typeSize = TypeInfo::typeSize(v.typeId());
    EXPECT_EQ(typeSize * 2, v.size());
}

// Test count returns 0 for empty value
TEST_F(ValueTypeGeneralTest_152, CountReturnsZeroForEmpty_152) {
    ValueType<uint32_t> v;
    EXPECT_EQ(0u, v.count());
}

// Test count returns correct number after multiple pushes
TEST_F(ValueTypeGeneralTest_152, CountReturnsCorrectAfterPushes_152) {
    ValueType<uint32_t> v;
    for (int i = 0; i < 10; ++i) {
        v.value_.push_back(static_cast<uint32_t>(i));
    }
    EXPECT_EQ(10u, v.count());
}

// Test that size equals 0 when no values are present
TEST_F(ValueTypeGeneralTest_152, SizeZeroWhenEmpty_152) {
    ValueType<Rational> v;
    EXPECT_EQ(0u, v.size());
}

// Test constructor with typeId override
TEST_F(ValueTypeGeneralTest_152, ConstructorWithTypeIdOverride_152) {
    uint16_t val = 100;
    ValueType<uint16_t> v(val, unsignedShort);
    EXPECT_EQ(unsignedShort, v.typeId());
    EXPECT_EQ(1u, v.count());
}

// Test copy construction preserves all data
TEST_F(ValueTypeGeneralTest_152, CopyConstructionPreservesData_152) {
    ValueType<int32_t> v;
    v.value_.push_back(-100);
    v.value_.push_back(200);
    v.value_.push_back(-300);
    
    ValueType<int32_t> v2(v);
    EXPECT_EQ(v.count(), v2.count());
    EXPECT_EQ(v.size(), v2.size());
    EXPECT_EQ(v.toInt64(0), v2.toInt64(0));
    EXPECT_EQ(v.toInt64(1), v2.toInt64(1));
    EXPECT_EQ(v.toInt64(2), v2.toInt64(2));
}

// Test assignment operator
TEST_F(ValueTypeGeneralTest_152, AssignmentOperator_152) {
    ValueType<uint16_t> v1;
    v1.value_.push_back(11);
    v1.value_.push_back(22);
    
    ValueType<uint16_t> v2;
    v2 = v1;
    
    EXPECT_EQ(v1.count(), v2.count());
    EXPECT_EQ(v1.size(), v2.size());
    EXPECT_EQ(v1.toInt64(0), v2.toInt64(0));
    EXPECT_EQ(v1.toInt64(1), v2.toInt64(1));
}
