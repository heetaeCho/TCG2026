#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <exiv2/types.hpp>
#include <cstring>
#include <sstream>
#include <vector>

using namespace Exiv2;

// ============================================================================
// Tests for ValueType<uint16_t> (UShortValue)
// ============================================================================

class ValueTypeUShortTest_148 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(ValueTypeUShortTest_148, DefaultConstructor_148) {
    ValueType<uint16_t> v;
    EXPECT_EQ(v.typeId(), unsignedShort);
    EXPECT_EQ(v.count(), 0u);
    EXPECT_EQ(v.size(), 0u);
}

TEST_F(ValueTypeUShortTest_148, ReadFromBuffer_LittleEndian_148) {
    ValueType<uint16_t> v;
    byte buf[] = {0x01, 0x00, 0x02, 0x00};
    int rc = v.read(buf, sizeof(buf), littleEndian);
    EXPECT_EQ(rc, 0);
    EXPECT_EQ(v.count(), 2u);
    EXPECT_EQ(v.value_[0], 1);
    EXPECT_EQ(v.value_[1], 2);
}

TEST_F(ValueTypeUShortTest_148, ReadFromBuffer_BigEndian_148) {
    ValueType<uint16_t> v;
    byte buf[] = {0x00, 0x01, 0x00, 0x02};
    int rc = v.read(buf, sizeof(buf), bigEndian);
    EXPECT_EQ(rc, 0);
    EXPECT_EQ(v.count(), 2u);
    EXPECT_EQ(v.value_[0], 1);
    EXPECT_EQ(v.value_[1], 2);
}

TEST_F(ValueTypeUShortTest_148, ReadTruncatesExtraBytes_148) {
    ValueType<uint16_t> v;
    // 5 bytes: only 4 should be used (2 uint16 values), last byte truncated
    byte buf[] = {0x01, 0x00, 0x02, 0x00, 0xFF};
    int rc = v.read(buf, 5, littleEndian);
    EXPECT_EQ(rc, 0);
    EXPECT_EQ(v.count(), 2u);
}

TEST_F(ValueTypeUShortTest_148, ReadEmptyBuffer_148) {
    ValueType<uint16_t> v;
    byte buf[] = {0x00};
    int rc = v.read(buf, 0, littleEndian);
    EXPECT_EQ(rc, 0);
    EXPECT_EQ(v.count(), 0u);
}

TEST_F(ValueTypeUShortTest_148, ReadClearsExistingValues_148) {
    ValueType<uint16_t> v;
    byte buf1[] = {0x01, 0x00, 0x02, 0x00};
    v.read(buf1, sizeof(buf1), littleEndian);
    EXPECT_EQ(v.count(), 2u);

    byte buf2[] = {0x03, 0x00};
    v.read(buf2, sizeof(buf2), littleEndian);
    EXPECT_EQ(v.count(), 1u);
    EXPECT_EQ(v.value_[0], 3);
}

TEST_F(ValueTypeUShortTest_148, ReadSingleByteTruncatesToZero_148) {
    ValueType<uint16_t> v;
    byte buf[] = {0xFF};
    int rc = v.read(buf, 1, littleEndian);
    EXPECT_EQ(rc, 0);
    EXPECT_EQ(v.count(), 0u);
}

TEST_F(ValueTypeUShortTest_148, CopyToBuffer_148) {
    ValueType<uint16_t> v;
    byte buf[] = {0x01, 0x00, 0x02, 0x00};
    v.read(buf, sizeof(buf), littleEndian);

    byte outBuf[4] = {};
    size_t copied = v.copy(outBuf, littleEndian);
    EXPECT_EQ(copied, 4u);
    EXPECT_EQ(outBuf[0], 0x01);
    EXPECT_EQ(outBuf[1], 0x00);
    EXPECT_EQ(outBuf[2], 0x02);
    EXPECT_EQ(outBuf[3], 0x00);
}

TEST_F(ValueTypeUShortTest_148, ToInt64_148) {
    ValueType<uint16_t> v;
    byte buf[] = {0x05, 0x00, 0x0A, 0x00};
    v.read(buf, sizeof(buf), littleEndian);
    EXPECT_EQ(v.toInt64(0), 5);
    EXPECT_EQ(v.toInt64(1), 10);
}

TEST_F(ValueTypeUShortTest_148, ToUint32_148) {
    ValueType<uint16_t> v;
    byte buf[] = {0xFF, 0xFF};
    v.read(buf, sizeof(buf), littleEndian);
    EXPECT_EQ(v.toUint32(0), 65535u);
}

TEST_F(ValueTypeUShortTest_148, ToFloat_148) {
    ValueType<uint16_t> v;
    byte buf[] = {0x0A, 0x00};
    v.read(buf, sizeof(buf), littleEndian);
    EXPECT_FLOAT_EQ(v.toFloat(0), 10.0f);
}

TEST_F(ValueTypeUShortTest_148, SizeReturnsCorrectBytes_148) {
    ValueType<uint16_t> v;
    byte buf[] = {0x01, 0x00, 0x02, 0x00, 0x03, 0x00};
    v.read(buf, sizeof(buf), littleEndian);
    EXPECT_EQ(v.size(), 6u);
}

TEST_F(ValueTypeUShortTest_148, Clone_148) {
    ValueType<uint16_t> v;
    byte buf[] = {0x07, 0x00};
    v.read(buf, sizeof(buf), littleEndian);

    auto cloned = v.clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->typeId(), unsignedShort);
    EXPECT_EQ(cloned->count(), 1u);
    EXPECT_EQ(cloned->toInt64(0), 7);
}

TEST_F(ValueTypeUShortTest_148, WriteToStream_148) {
    ValueType<uint16_t> v;
    byte buf[] = {0x01, 0x00, 0x02, 0x00};
    v.read(buf, sizeof(buf), littleEndian);

    std::ostringstream os;
    v.write(os);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

TEST_F(ValueTypeUShortTest_148, ToString_148) {
    ValueType<uint16_t> v;
    byte buf[] = {0x05, 0x00};
    v.read(buf, sizeof(buf), littleEndian);
    std::string str = v.toString(0);
    EXPECT_EQ(str, "5");
}

// ============================================================================
// Tests for ValueType<uint32_t> (ULongValue)
// ============================================================================

class ValueTypeULongTest_148 : public ::testing::Test {};

TEST_F(ValueTypeULongTest_148, DefaultConstructor_148) {
    ValueType<uint32_t> v;
    EXPECT_EQ(v.typeId(), unsignedLong);
    EXPECT_EQ(v.count(), 0u);
}

TEST_F(ValueTypeULongTest_148, ReadFromBuffer_LittleEndian_148) {
    ValueType<uint32_t> v;
    byte buf[] = {0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00};
    int rc = v.read(buf, sizeof(buf), littleEndian);
    EXPECT_EQ(rc, 0);
    EXPECT_EQ(v.count(), 2u);
    EXPECT_EQ(v.value_[0], 1u);
    EXPECT_EQ(v.value_[1], 2u);
}

TEST_F(ValueTypeULongTest_148, ReadTruncatesExtraBytes_148) {
    ValueType<uint32_t> v;
    // 7 bytes: only 4 should be used (1 uint32 value)
    byte buf[] = {0x01, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF};
    int rc = v.read(buf, 7, littleEndian);
    EXPECT_EQ(rc, 0);
    EXPECT_EQ(v.count(), 1u);
    EXPECT_EQ(v.value_[0], 1u);
}

TEST_F(ValueTypeULongTest_148, ReadLessThanTypeSize_148) {
    ValueType<uint32_t> v;
    byte buf[] = {0x01, 0x02, 0x03};
    int rc = v.read(buf, 3, littleEndian);
    EXPECT_EQ(rc, 0);
    EXPECT_EQ(v.count(), 0u);
}

TEST_F(ValueTypeULongTest_148, ToRational_148) {
    ValueType<uint32_t> v;
    byte buf[] = {0x0A, 0x00, 0x00, 0x00};
    v.read(buf, sizeof(buf), littleEndian);
    Rational r = v.toRational(0);
    EXPECT_EQ(r.first, 10);
    EXPECT_EQ(r.second, 1);
}

TEST_F(ValueTypeULongTest_148, CopyAndRead_BigEndian_148) {
    ValueType<uint32_t> v;
    byte buf[] = {0x00, 0x00, 0x00, 0x0A};
    v.read(buf, sizeof(buf), bigEndian);
    EXPECT_EQ(v.count(), 1u);
    EXPECT_EQ(v.value_[0], 10u);

    byte outBuf[4] = {};
    size_t copied = v.copy(outBuf, bigEndian);
    EXPECT_EQ(copied, 4u);
    EXPECT_EQ(memcmp(buf, outBuf, 4), 0);
}

// ============================================================================
// Tests for ValueType<int16_t> (SShortValue)
// ============================================================================

class ValueTypeSShortTest_148 : public ::testing::Test {};

TEST_F(ValueTypeSShortTest_148, ReadNegativeValues_148) {
    ValueType<int16_t> v;
    // -1 in little endian is 0xFF, 0xFF
    byte buf[] = {0xFF, 0xFF};
    int rc = v.read(buf, sizeof(buf), littleEndian);
    EXPECT_EQ(rc, 0);
    EXPECT_EQ(v.count(), 1u);
    EXPECT_EQ(v.value_[0], -1);
}

TEST_F(ValueTypeSShortTest_148, ToInt64Negative_148) {
    ValueType<int16_t> v;
    byte buf[] = {0x00, 0x80}; // -32768 in LE
    v.read(buf, sizeof(buf), littleEndian);
    EXPECT_EQ(v.toInt64(0), -32768);
}

// ============================================================================
// Tests for ValueType<Rational> (RationalValue)
// ============================================================================

class ValueTypeRationalTest_148 : public ::testing::Test {};

TEST_F(ValueTypeRationalTest_148, DefaultConstructor_148) {
    ValueType<Rational> v;
    EXPECT_EQ(v.typeId(), signedRational);
    EXPECT_EQ(v.count(), 0u);
}

TEST_F(ValueTypeRationalTest_148, ReadRational_LittleEndian_148) {
    ValueType<Rational> v;
    // Rational is two int32_t: numerator=1, denominator=2
    byte buf[] = {
        0x01, 0x00, 0x00, 0x00,  // numerator = 1
        0x02, 0x00, 0x00, 0x00   // denominator = 2
    };
    int rc = v.read(buf, sizeof(buf), littleEndian);
    EXPECT_EQ(rc, 0);
    EXPECT_EQ(v.count(), 1u);
    EXPECT_EQ(v.value_[0].first, 1);
    EXPECT_EQ(v.value_[0].second, 2);
}

TEST_F(ValueTypeRationalTest_148, ToFloat_148) {
    ValueType<Rational> v;
    byte buf[] = {
        0x01, 0x00, 0x00, 0x00,
        0x04, 0x00, 0x00, 0x00
    };
    v.read(buf, sizeof(buf), littleEndian);
    EXPECT_FLOAT_EQ(v.toFloat(0), 0.25f);
}

TEST_F(ValueTypeRationalTest_148, ToRational_148) {
    ValueType<Rational> v;
    byte buf[] = {
        0x03, 0x00, 0x00, 0x00,
        0x07, 0x00, 0x00, 0x00
    };
    v.read(buf, sizeof(buf), littleEndian);
    Rational r = v.toRational(0);
    EXPECT_EQ(r.first, 3);
    EXPECT_EQ(r.second, 7);
}

TEST_F(ValueTypeRationalTest_148, ToInt64_148) {
    ValueType<Rational> v;
    byte buf[] = {
        0x0A, 0x00, 0x00, 0x00,
        0x02, 0x00, 0x00, 0x00
    };
    v.read(buf, sizeof(buf), littleEndian);
    EXPECT_EQ(v.toInt64(0), 5);
}

// ============================================================================
// Tests for ValueType<URational> (URationalValue)
// ============================================================================

class ValueTypeURationalTest_148 : public ::testing::Test {};

TEST_F(ValueTypeURationalTest_148, ReadURational_148) {
    ValueType<URational> v;
    byte buf[] = {
        0x64, 0x00, 0x00, 0x00,  // numerator = 100
        0x03, 0x00, 0x00, 0x00   // denominator = 3
    };
    int rc = v.read(buf, sizeof(buf), littleEndian);
    EXPECT_EQ(rc, 0);
    EXPECT_EQ(v.count(), 1u);
    EXPECT_EQ(v.value_[0].first, 100u);
    EXPECT_EQ(v.value_[0].second, 3u);
}

TEST_F(ValueTypeURationalTest_148, ToFloat_148) {
    ValueType<URational> v;
    byte buf[] = {
        0x01, 0x00, 0x00, 0x00,
        0x03, 0x00, 0x00, 0x00
    };
    v.read(buf, sizeof(buf), littleEndian);
    EXPECT_NEAR(v.toFloat(0), 1.0f / 3.0f, 0.001f);
}

// ============================================================================
// Tests for ValueType<float> (FloatValue)
// ============================================================================

class ValueTypeFloatTest_148 : public ::testing::Test {};

TEST_F(ValueTypeFloatTest_148, DefaultConstructor_148) {
    ValueType<float> v;
    EXPECT_EQ(v.typeId(), tiffFloat);
    EXPECT_EQ(v.count(), 0u);
}

TEST_F(ValueTypeFloatTest_148, ReadFloat_LittleEndian_148) {
    ValueType<float> v;
    float val = 3.14f;
    byte buf[4];
    std::memcpy(buf, &val, 4);
    int rc = v.read(buf, sizeof(buf), littleEndian);
    EXPECT_EQ(rc, 0);
    EXPECT_EQ(v.count(), 1u);
    EXPECT_FLOAT_EQ(v.value_[0], 3.14f);
}

TEST_F(ValueTypeFloatTest_148, ToRational_148) {
    ValueType<float> v;
    float val = 0.5f;
    byte buf[4];
    std::memcpy(buf, &val, 4);
    v.read(buf, sizeof(buf), littleEndian);
    Rational r = v.toRational(0);
    // Check that the rational approximates 0.5
    EXPECT_NEAR(static_cast<double>(r.first) / r.second, 0.5, 0.01);
}

// ============================================================================
// Tests for ValueType<double> (DoubleValue)
// ============================================================================

class ValueTypeDoubleTest_148 : public ::testing::Test {};

TEST_F(ValueTypeDoubleTest_148, DefaultConstructor_148) {
    ValueType<double> v;
    EXPECT_EQ(v.typeId(), tiffDouble);
    EXPECT_EQ(v.count(), 0u);
}

TEST_F(ValueTypeDoubleTest_148, ReadDouble_148) {
    ValueType<double> v;
    double val = 2.71828;
    byte buf[8];
    std::memcpy(buf, &val, 8);
    int rc = v.read(buf, sizeof(buf), littleEndian);
    EXPECT_EQ(rc, 0);
    EXPECT_EQ(v.count(), 1u);
    EXPECT_DOUBLE_EQ(v.value_[0], 2.71828);
}

TEST_F(ValueTypeDoubleTest_148, ToInt64_148) {
    ValueType<double> v;
    double val = 42.7;
    byte buf[8];
    std::memcpy(buf, &val, 8);
    v.read(buf, sizeof(buf), littleEndian);
    EXPECT_EQ(v.toInt64(0), 42);
}

TEST_F(ValueTypeDoubleTest_148, ToUint32_148) {
    ValueType<double> v;
    double val = 255.9;
    byte buf[8];
    std::memcpy(buf, &val, 8);
    v.read(buf, sizeof(buf), littleEndian);
    EXPECT_EQ(v.toUint32(0), 255u);
}

// ============================================================================
// Tests for constructors with initial value
// ============================================================================

class ValueTypeConstructorTest_148 : public ::testing::Test {};

TEST_F(ValueTypeConstructorTest_148, ConstructWithValue_148) {
    ValueType<uint16_t> v(static_cast<uint16_t>(42), unsignedShort);
    EXPECT_EQ(v.count(), 1u);
    EXPECT_EQ(v.value_[0], 42);
    EXPECT_EQ(v.typeId(), unsignedShort);
}

TEST_F(ValueTypeConstructorTest_148, ConstructFromBufferAndByteOrder_148) {
    byte buf[] = {0x05, 0x00, 0x0A, 0x00};
    ValueType<uint16_t> v(buf, sizeof(buf), littleEndian, unsignedShort);
    EXPECT_EQ(v.count(), 2u);
    EXPECT_EQ(v.value_[0], 5);
    EXPECT_EQ(v.value_[1], 10);
}

TEST_F(ValueTypeConstructorTest_148, CopyConstructor_148) {
    ValueType<uint16_t> v1;
    byte buf[] = {0x01, 0x00, 0x02, 0x00};
    v1.read(buf, sizeof(buf), littleEndian);

    ValueType<uint16_t> v2(v1);
    EXPECT_EQ(v2.count(), 2u);
    EXPECT_EQ(v2.value_[0], 1);
    EXPECT_EQ(v2.value_[1], 2);
}

TEST_F(ValueTypeConstructorTest_148, AssignmentOperator_148) {
    ValueType<uint16_t> v1;
    byte buf[] = {0x07, 0x00};
    v1.read(buf, sizeof(buf), littleEndian);

    ValueType<uint16_t> v2;
    v2 = v1;
    EXPECT_EQ(v2.count(), 1u);
    EXPECT_EQ(v2.value_[0], 7);
}

// ============================================================================
// Tests for DataArea
// ============================================================================

class ValueTypeDataAreaTest_148 : public ::testing::Test {};

TEST_F(ValueTypeDataAreaTest_148, SetDataArea_148) {
    ValueType<uint16_t> v;
    byte data[] = {0x01, 0x02, 0x03, 0x04};
    int rc = v.setDataArea(data, sizeof(data));
    EXPECT_EQ(rc, 0);
    EXPECT_EQ(v.sizeDataArea(), 4u);
}

TEST_F(ValueTypeDataAreaTest_148, DataAreaRetrieve_148) {
    ValueType<uint16_t> v;
    byte data[] = {0xAA, 0xBB, 0xCC};
    v.setDataArea(data, sizeof(data));
    DataBuf db = v.dataArea();
    EXPECT_EQ(db.size(), 3u);
}

TEST_F(ValueTypeDataAreaTest_148, EmptyDataArea_148) {
    ValueType<uint16_t> v;
    EXPECT_EQ(v.sizeDataArea(), 0u);
}

// ============================================================================
// Tests for read from string
// ============================================================================

class ValueTypeReadStringTest_148 : public ::testing::Test {};

TEST_F(ValueTypeReadStringTest_148, ReadFromString_UShort_148) {
    ValueType<uint16_t> v;
    int rc = v.read("10 20 30");
    EXPECT_EQ(rc, 0);
    EXPECT_EQ(v.count(), 3u);
    EXPECT_EQ(v.value_[0], 10);
    EXPECT_EQ(v.value_[1], 20);
    EXPECT_EQ(v.value_[2], 30);
}

TEST_F(ValueTypeReadStringTest_148, ReadFromString_SingleValue_148) {
    ValueType<uint32_t> v;
    int rc = v.read("12345");
    EXPECT_EQ(rc, 0);
    EXPECT_EQ(v.count(), 1u);
    EXPECT_EQ(v.value_[0], 12345u);
}

TEST_F(ValueTypeReadStringTest_148, ReadFromString_Rational_148) {
    ValueType<Rational> v;
    int rc = v.read("1/2");
    EXPECT_EQ(rc, 0);
    EXPECT_EQ(v.count(), 1u);
    EXPECT_EQ(v.value_[0].first, 1);
    EXPECT_EQ(v.value_[0].second, 2);
}

// ============================================================================
// Tests for Value::create factory
// ============================================================================

class ValueCreateTest_148 : public ::testing::Test {};

TEST_F(ValueCreateTest_148, CreateUShortValue_148) {
    auto v = Value::create(unsignedShort);
    ASSERT_NE(v, nullptr);
    EXPECT_EQ(v->typeId(), unsignedShort);
}

TEST_F(ValueCreateTest_148, CreateULongValue_148) {
    auto v = Value::create(unsignedLong);
    ASSERT_NE(v, nullptr);
    EXPECT_EQ(v->typeId(), unsignedLong);
}

TEST_F(ValueCreateTest_148, CreateSignedRationalValue_148) {
    auto v = Value::create(signedRational);
    ASSERT_NE(v, nullptr);
    EXPECT_EQ(v->typeId(), signedRational);
}

TEST_F(ValueCreateTest_148, CreateUnsignedRationalValue_148) {
    auto v = Value::create(unsignedRational);
    ASSERT_NE(v, nullptr);
    EXPECT_EQ(v->typeId(), unsignedRational);
}

// ============================================================================
// Tests for multiple values read/copy round-trip
// ============================================================================

class ValueTypeRoundTripTest_148 : public ::testing::Test {};

TEST_F(ValueTypeRoundTripTest_148, UShortRoundTrip_148) {
    ValueType<uint16_t> v;
    byte inBuf[] = {0x10, 0x27, 0xE8, 0x03}; // 10000, 1000 in LE
    v.read(inBuf, sizeof(inBuf), littleEndian);
    EXPECT_EQ(v.count(), 2u);

    byte outBuf[4] = {};
    v.copy(outBuf, littleEndian);
    EXPECT_EQ(memcmp(inBuf, outBuf, 4), 0);
}

TEST_F(ValueTypeRoundTripTest_148, ULongRoundTrip_BigEndian_148) {
    ValueType<uint32_t> v;
    byte inBuf[] = {0x00, 0x01, 0x00, 0x00}; // 65536 in BE
    v.read(inBuf, sizeof(inBuf), bigEndian);
    EXPECT_EQ(v.count(), 1u);
    EXPECT_EQ(v.value_[0], 65536u);

    byte outBuf[4] = {};
    v.copy(outBuf, bigEndian);
    EXPECT_EQ(memcmp(inBuf, outBuf, 4), 0);
}

// ============================================================================
// Tests for ok() state
// ============================================================================

class ValueOkTest_148 : public ::testing::Test {};

TEST_F(ValueOkTest_148, OkAfterConstruction_148) {
    ValueType<uint16_t> v;
    EXPECT_TRUE(v.ok());
}

TEST_F(ValueOkTest_148, OkAfterRead_148) {
    ValueType<uint16_t> v;
    byte buf[] = {0x01, 0x00};
    v.read(buf, sizeof(buf), littleEndian);
    EXPECT_TRUE(v.ok());
}

// ============================================================================
// Edge case: Multiple reads should clear previous state
// ============================================================================

class ValueTypeMultipleReadsTest_148 : public ::testing::Test {};

TEST_F(ValueTypeMultipleReadsTest_148, MultipleBufferReads_148) {
    ValueType<uint16_t> v;
    byte buf1[] = {0x01, 0x00, 0x02, 0x00, 0x03, 0x00};
    v.read(buf1, sizeof(buf1), littleEndian);
    EXPECT_EQ(v.count(), 3u);

    byte buf2[] = {0x0A, 0x00};
    v.read(buf2, sizeof(buf2), littleEndian);
    EXPECT_EQ(v.count(), 1u);
    EXPECT_EQ(v.value_[0], 10);
}

TEST_F(ValueTypeMultipleReadsTest_148, StringReadClearsPrevious_148) {
    ValueType<uint16_t> v;
    v.read("1 2 3 4 5");
    EXPECT_EQ(v.count(), 5u);

    v.read("100");
    EXPECT_EQ(v.count(), 1u);
    EXPECT_EQ(v.value_[0], 100);
}

// ============================================================================
// Tests for int32_t (signedLong)
// ============================================================================

class ValueTypeSLongTest_148 : public ::testing::Test {};

TEST_F(ValueTypeSLongTest_148, ReadNegativeValue_148) {
    ValueType<int32_t> v;
    // -1 in little endian
    byte buf[] = {0xFF, 0xFF, 0xFF, 0xFF};
    int rc = v.read(buf, sizeof(buf), littleEndian);
    EXPECT_EQ(rc, 0);
    EXPECT_EQ(v.count(), 1u);
    EXPECT_EQ(v.value_[0], -1);
    EXPECT_EQ(v.toInt64(0), -1);
}

TEST_F(ValueTypeSLongTest_148, ReadMultipleNegativeValues_148) {
    ValueType<int32_t> v;
    v.read("-100 -200");
    EXPECT_EQ(v.count(), 2u);
    EXPECT_EQ(v.value_[0], -100);
    EXPECT_EQ(v.value_[1], -200);
}
