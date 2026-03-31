#include <gtest/gtest.h>
#include <sstream>
#include <cstring>
#include <exiv2/value.hpp>

using namespace Exiv2;

// ============================================================================
// Tests for ValueType<uint16_t> (UShortValue)
// ============================================================================

class ValueTypeUShortTest_153 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(ValueTypeUShortTest_153, DefaultConstructor_153) {
    ValueType<uint16_t> v;
    EXPECT_EQ(v.count(), 0u);
    EXPECT_EQ(v.size(), 0u);
}

TEST_F(ValueTypeUShortTest_153, ConstructorWithValue_153) {
    ValueType<uint16_t> v(42, TypeId::unsignedShort);
    EXPECT_EQ(v.count(), 1u);
    EXPECT_EQ(v.toInt64(0), 42);
}

TEST_F(ValueTypeUShortTest_153, ReadFromString_153) {
    ValueType<uint16_t> v;
    v.read("100 200 300");
    EXPECT_EQ(v.count(), 3u);
    EXPECT_EQ(v.toInt64(0), 100);
    EXPECT_EQ(v.toInt64(1), 200);
    EXPECT_EQ(v.toInt64(2), 300);
}

TEST_F(ValueTypeUShortTest_153, ReadFromStringSingleValue_153) {
    ValueType<uint16_t> v;
    v.read("65535");
    EXPECT_EQ(v.count(), 1u);
    EXPECT_EQ(v.toUint32(0), 65535u);
}

TEST_F(ValueTypeUShortTest_153, WriteToStream_153) {
    ValueType<uint16_t> v;
    v.read("10 20 30");
    std::ostringstream os;
    v.write(os);
    EXPECT_EQ(os.str(), "10 20 30");
}

TEST_F(ValueTypeUShortTest_153, WriteToStreamSingleValue_153) {
    ValueType<uint16_t> v;
    v.read("42");
    std::ostringstream os;
    v.write(os);
    EXPECT_EQ(os.str(), "42");
}

TEST_F(ValueTypeUShortTest_153, WriteToStreamEmpty_153) {
    ValueType<uint16_t> v;
    std::ostringstream os;
    v.write(os);
    EXPECT_EQ(os.str(), "");
}

TEST_F(ValueTypeUShortTest_153, ToString_153) {
    ValueType<uint16_t> v;
    v.read("10 20 30");
    EXPECT_EQ(v.toString(0), "10");
    EXPECT_EQ(v.toString(1), "20");
    EXPECT_EQ(v.toString(2), "30");
}

TEST_F(ValueTypeUShortTest_153, ToFloat_153) {
    ValueType<uint16_t> v;
    v.read("42");
    EXPECT_FLOAT_EQ(v.toFloat(0), 42.0f);
}

TEST_F(ValueTypeUShortTest_153, ToRational_153) {
    ValueType<uint16_t> v;
    v.read("42");
    Rational r = v.toRational(0);
    EXPECT_EQ(r.first, 42);
    EXPECT_EQ(r.second, 1);
}

TEST_F(ValueTypeUShortTest_153, CopyConstructor_153) {
    ValueType<uint16_t> v;
    v.read("10 20");
    ValueType<uint16_t> v2(v);
    EXPECT_EQ(v2.count(), 2u);
    EXPECT_EQ(v2.toInt64(0), 10);
    EXPECT_EQ(v2.toInt64(1), 20);
}

TEST_F(ValueTypeUShortTest_153, AssignmentOperator_153) {
    ValueType<uint16_t> v;
    v.read("10 20");
    ValueType<uint16_t> v2;
    v2 = v;
    EXPECT_EQ(v2.count(), 2u);
    EXPECT_EQ(v2.toInt64(0), 10);
    EXPECT_EQ(v2.toInt64(1), 20);
}

TEST_F(ValueTypeUShortTest_153, Clone_153) {
    ValueType<uint16_t> v;
    v.read("10 20");
    auto c = v.clone();
    ASSERT_NE(c, nullptr);
    EXPECT_EQ(c->count(), 2u);
    EXPECT_EQ(c->toInt64(0), 10);
    EXPECT_EQ(c->toInt64(1), 20);
}

TEST_F(ValueTypeUShortTest_153, ReadFromBuffer_153) {
    ValueType<uint16_t> v;
    uint16_t data[] = {0x0001, 0x0002, 0x0003};
    // Read as little-endian
    v.read(reinterpret_cast<const byte*>(data), sizeof(data), littleEndian);
    EXPECT_EQ(v.count(), 3u);
    EXPECT_EQ(v.toInt64(0), 1);
    EXPECT_EQ(v.toInt64(1), 2);
    EXPECT_EQ(v.toInt64(2), 3);
}

TEST_F(ValueTypeUShortTest_153, CopyToBuffer_153) {
    ValueType<uint16_t> v;
    v.read("1 2 3");
    byte buf[6];
    std::memset(buf, 0, sizeof(buf));
    size_t sz = v.copy(buf, littleEndian);
    EXPECT_EQ(sz, 6u);
}

TEST_F(ValueTypeUShortTest_153, SizeReturnsCorrectBytes_153) {
    ValueType<uint16_t> v;
    v.read("1 2 3");
    EXPECT_EQ(v.size(), 6u); // 3 * sizeof(uint16_t)
}

TEST_F(ValueTypeUShortTest_153, DataAreaInitiallyEmpty_153) {
    ValueType<uint16_t> v;
    EXPECT_EQ(v.sizeDataArea(), 0u);
}

TEST_F(ValueTypeUShortTest_153, SetDataArea_153) {
    ValueType<uint16_t> v;
    byte data[] = {0x01, 0x02, 0x03, 0x04};
    v.setDataArea(data, sizeof(data));
    EXPECT_EQ(v.sizeDataArea(), 4u);
    DataBuf db = v.dataArea();
    EXPECT_EQ(db.size(), 4u);
}

// ============================================================================
// Tests for ValueType<uint32_t> (ULongValue)
// ============================================================================

class ValueTypeULongTest_153 : public ::testing::Test {};

TEST_F(ValueTypeULongTest_153, DefaultConstructor_153) {
    ValueType<uint32_t> v;
    EXPECT_EQ(v.count(), 0u);
}

TEST_F(ValueTypeULongTest_153, ReadFromString_153) {
    ValueType<uint32_t> v;
    v.read("1000000 2000000");
    EXPECT_EQ(v.count(), 2u);
    EXPECT_EQ(v.toInt64(0), 1000000);
    EXPECT_EQ(v.toInt64(1), 2000000);
}

TEST_F(ValueTypeULongTest_153, WriteMultipleValues_153) {
    ValueType<uint32_t> v;
    v.read("100 200 300 400");
    std::ostringstream os;
    v.write(os);
    EXPECT_EQ(os.str(), "100 200 300 400");
}

TEST_F(ValueTypeULongTest_153, ToUint32_153) {
    ValueType<uint32_t> v;
    v.read("4294967295");
    EXPECT_EQ(v.toUint32(0), 4294967295u);
}

// ============================================================================
// Tests for ValueType<int16_t> (ShortValue)
// ============================================================================

class ValueTypeShortTest_153 : public ::testing::Test {};

TEST_F(ValueTypeShortTest_153, NegativeValues_153) {
    ValueType<int16_t> v;
    v.read("-100 -200");
    EXPECT_EQ(v.count(), 2u);
    EXPECT_EQ(v.toInt64(0), -100);
    EXPECT_EQ(v.toInt64(1), -200);
}

TEST_F(ValueTypeShortTest_153, WriteNegativeValues_153) {
    ValueType<int16_t> v;
    v.read("-10 20 -30");
    std::ostringstream os;
    v.write(os);
    EXPECT_EQ(os.str(), "-10 20 -30");
}

// ============================================================================
// Tests for ValueType<Rational>
// ============================================================================

class ValueTypeRationalTest_153 : public ::testing::Test {};

TEST_F(ValueTypeRationalTest_153, DefaultConstructor_153) {
    ValueType<Rational> v;
    EXPECT_EQ(v.count(), 0u);
}

TEST_F(ValueTypeRationalTest_153, ReadFromString_153) {
    ValueType<Rational> v;
    v.read("1/2 3/4");
    EXPECT_EQ(v.count(), 2u);
}

TEST_F(ValueTypeRationalTest_153, ToFloat_153) {
    ValueType<Rational> v;
    v.read("1/2");
    EXPECT_FLOAT_EQ(v.toFloat(0), 0.5f);
}

TEST_F(ValueTypeRationalTest_153, ToInt64_153) {
    ValueType<Rational> v;
    v.read("10/2");
    EXPECT_EQ(v.toInt64(0), 5);
}

TEST_F(ValueTypeRationalTest_153, ToUint32_153) {
    ValueType<Rational> v;
    v.read("10/2");
    EXPECT_EQ(v.toUint32(0), 5u);
}

TEST_F(ValueTypeRationalTest_153, ToRational_153) {
    ValueType<Rational> v;
    v.read("3/7");
    Rational r = v.toRational(0);
    EXPECT_EQ(r.first, 3);
    EXPECT_EQ(r.second, 7);
}

TEST_F(ValueTypeRationalTest_153, ZeroDenominator_153) {
    ValueType<Rational> v;
    v.read("5/0");
    EXPECT_EQ(v.count(), 1u);
    // toFloat with zero denominator
    float f = v.toFloat(0);
    // Result may be inf or some special value; we just ensure it doesn't crash
    (void)f;
}

TEST_F(ValueTypeRationalTest_153, WriteToStream_153) {
    ValueType<Rational> v;
    v.read("1/2 3/4");
    std::ostringstream os;
    v.write(os);
    EXPECT_EQ(os.str(), "1/2 3/4");
}

// ============================================================================
// Tests for ValueType<URational>
// ============================================================================

class ValueTypeURationalTest_153 : public ::testing::Test {};

TEST_F(ValueTypeURationalTest_153, ReadAndConvert_153) {
    ValueType<URational> v;
    v.read("10/3");
    EXPECT_EQ(v.count(), 1u);
    EXPECT_FLOAT_EQ(v.toFloat(0), 10.0f / 3.0f);
}

TEST_F(ValueTypeURationalTest_153, ToInt64_153) {
    ValueType<URational> v;
    v.read("20/4");
    EXPECT_EQ(v.toInt64(0), 5);
}

TEST_F(ValueTypeURationalTest_153, ToUint32_153) {
    ValueType<URational> v;
    v.read("20/4");
    EXPECT_EQ(v.toUint32(0), 5u);
}

TEST_F(ValueTypeURationalTest_153, ToRational_153) {
    ValueType<URational> v;
    v.read("7/3");
    Rational r = v.toRational(0);
    EXPECT_EQ(r.first, 7);
    EXPECT_EQ(r.second, 3);
}

TEST_F(ValueTypeURationalTest_153, WriteToStream_153) {
    ValueType<URational> v;
    v.read("1/10 2/10 3/10");
    std::ostringstream os;
    v.write(os);
    EXPECT_EQ(os.str(), "1/10 2/10 3/10");
}

// ============================================================================
// Tests for ValueType<float>
// ============================================================================

class ValueTypeFloatTest_153 : public ::testing::Test {};

TEST_F(ValueTypeFloatTest_153, DefaultConstructor_153) {
    ValueType<float> v;
    EXPECT_EQ(v.count(), 0u);
}

TEST_F(ValueTypeFloatTest_153, ReadFromString_153) {
    ValueType<float> v;
    v.read("1.5 2.5 3.5");
    EXPECT_EQ(v.count(), 3u);
    EXPECT_FLOAT_EQ(v.toFloat(0), 1.5f);
    EXPECT_FLOAT_EQ(v.toFloat(1), 2.5f);
    EXPECT_FLOAT_EQ(v.toFloat(2), 3.5f);
}

TEST_F(ValueTypeFloatTest_153, ToInt64_153) {
    ValueType<float> v;
    v.read("3.7");
    EXPECT_EQ(v.toInt64(0), 3);
}

TEST_F(ValueTypeFloatTest_153, ToUint32_153) {
    ValueType<float> v;
    v.read("3.7");
    EXPECT_EQ(v.toUint32(0), 3u);
}

TEST_F(ValueTypeFloatTest_153, ToRational_153) {
    ValueType<float> v;
    v.read("0.5");
    Rational r = v.toRational(0);
    // Should represent 0.5 as some rational
    EXPECT_NE(r.second, 0);
    float reconstructed = static_cast<float>(r.first) / static_cast<float>(r.second);
    EXPECT_NEAR(reconstructed, 0.5f, 0.001f);
}

TEST_F(ValueTypeFloatTest_153, WriteToStream_153) {
    ValueType<float> v;
    v.read("1.5 2.5");
    std::ostringstream os;
    v.write(os);
    std::string result = os.str();
    // Should contain both values separated by space
    EXPECT_NE(result.find(" "), std::string::npos);
}

// ============================================================================
// Tests for ValueType<double>
// ============================================================================

class ValueTypeDoubleTest_153 : public ::testing::Test {};

TEST_F(ValueTypeDoubleTest_153, DefaultConstructor_153) {
    ValueType<double> v;
    EXPECT_EQ(v.count(), 0u);
}

TEST_F(ValueTypeDoubleTest_153, ReadFromString_153) {
    ValueType<double> v;
    v.read("1.123456789012345 2.987654321098765");
    EXPECT_EQ(v.count(), 2u);
}

TEST_F(ValueTypeDoubleTest_153, ToInt64_153) {
    ValueType<double> v;
    v.read("99.9");
    EXPECT_EQ(v.toInt64(0), 99);
}

TEST_F(ValueTypeDoubleTest_153, ToUint32_153) {
    ValueType<double> v;
    v.read("99.9");
    EXPECT_EQ(v.toUint32(0), 99u);
}

TEST_F(ValueTypeDoubleTest_153, ToRational_153) {
    ValueType<double> v;
    v.read("0.25");
    Rational r = v.toRational(0);
    EXPECT_NE(r.second, 0);
    double reconstructed = static_cast<double>(r.first) / static_cast<double>(r.second);
    EXPECT_NEAR(reconstructed, 0.25, 0.001);
}

TEST_F(ValueTypeDoubleTest_153, WriteHighPrecision_153) {
    ValueType<double> v;
    v.read("3.141592653589793");
    std::ostringstream os;
    v.write(os);
    std::string result = os.str();
    // With setprecision(15), we should get many digits
    EXPECT_TRUE(result.find("3.14159") != std::string::npos);
}

// ============================================================================
// Tests for ValueType<int32_t> (LongValue)
// ============================================================================

class ValueTypeLongTest_153 : public ::testing::Test {};

TEST_F(ValueTypeLongTest_153, NegativeValues_153) {
    ValueType<int32_t> v;
    v.read("-2147483648 2147483647");
    EXPECT_EQ(v.count(), 2u);
    EXPECT_EQ(v.toInt64(0), -2147483648LL);
    EXPECT_EQ(v.toInt64(1), 2147483647LL);
}

TEST_F(ValueTypeLongTest_153, WriteToStream_153) {
    ValueType<int32_t> v;
    v.read("-1 0 1");
    std::ostringstream os;
    v.write(os);
    EXPECT_EQ(os.str(), "-1 0 1");
}

// ============================================================================
// Edge case tests
// ============================================================================

class ValueTypeEdgeCaseTest_153 : public ::testing::Test {};

TEST_F(ValueTypeEdgeCaseTest_153, EmptyReadString_153) {
    ValueType<uint16_t> v;
    v.read("");
    EXPECT_EQ(v.count(), 0u);
}

TEST_F(ValueTypeEdgeCaseTest_153, DirectValueAccess_153) {
    ValueType<uint16_t> v;
    v.read("10 20 30");
    EXPECT_EQ(v.value_.size(), 3u);
    EXPECT_EQ(v.value_[0], 10);
    EXPECT_EQ(v.value_[1], 20);
    EXPECT_EQ(v.value_[2], 30);
}

TEST_F(ValueTypeEdgeCaseTest_153, ValueListManipulation_153) {
    ValueType<uint16_t> v;
    v.value_.push_back(100);
    v.value_.push_back(200);
    EXPECT_EQ(v.count(), 2u);
    EXPECT_EQ(v.toInt64(0), 100);
    EXPECT_EQ(v.toInt64(1), 200);
}

TEST_F(ValueTypeEdgeCaseTest_153, SetDataAreaAndRetrieve_153) {
    ValueType<uint32_t> v;
    byte data[] = {0xDE, 0xAD, 0xBE, 0xEF};
    int result = v.setDataArea(data, sizeof(data));
    EXPECT_EQ(result, 0);
    EXPECT_EQ(v.sizeDataArea(), 4u);
    DataBuf db = v.dataArea();
    EXPECT_EQ(db.size(), 4u);
    EXPECT_EQ(db.data()[0], 0xDE);
    EXPECT_EQ(db.data()[1], 0xAD);
    EXPECT_EQ(db.data()[2], 0xBE);
    EXPECT_EQ(db.data()[3], 0xEF);
}

TEST_F(ValueTypeEdgeCaseTest_153, ReadOverwritesPreviousData_153) {
    ValueType<uint16_t> v;
    v.read("1 2 3");
    EXPECT_EQ(v.count(), 3u);
    v.read("10 20");
    EXPECT_EQ(v.count(), 2u);
    EXPECT_EQ(v.toInt64(0), 10);
    EXPECT_EQ(v.toInt64(1), 20);
}

TEST_F(ValueTypeEdgeCaseTest_153, ConstructFromBuffer_153) {
    // Construct uint16_t values from byte buffer
    byte buf[] = {0x01, 0x00, 0x02, 0x00}; // 1 and 2 in little endian
    ValueType<uint16_t> v(buf, sizeof(buf), littleEndian, TypeId::unsignedShort);
    EXPECT_EQ(v.count(), 2u);
    EXPECT_EQ(v.toInt64(0), 1);
    EXPECT_EQ(v.toInt64(1), 2);
}

TEST_F(ValueTypeEdgeCaseTest_153, CopyToBufferBigEndian_153) {
    ValueType<uint16_t> v;
    v.read("256"); // 0x0100
    byte buf[2] = {0, 0};
    size_t sz = v.copy(buf, bigEndian);
    EXPECT_EQ(sz, 2u);
    EXPECT_EQ(buf[0], 0x01);
    EXPECT_EQ(buf[1], 0x00);
}

TEST_F(ValueTypeEdgeCaseTest_153, CopyToBufferLittleEndian_153) {
    ValueType<uint16_t> v;
    v.read("256"); // 0x0100
    byte buf[2] = {0, 0};
    size_t sz = v.copy(buf, littleEndian);
    EXPECT_EQ(sz, 2u);
    EXPECT_EQ(buf[0], 0x00);
    EXPECT_EQ(buf[1], 0x01);
}

TEST_F(ValueTypeEdgeCaseTest_153, WriteSingleElement_153) {
    ValueType<uint32_t> v;
    v.read("42");
    std::ostringstream os;
    v.write(os);
    // Single element, no trailing space
    EXPECT_EQ(os.str(), "42");
}

TEST_F(ValueTypeEdgeCaseTest_153, RationalZeroDenominatorToInt64_153) {
    ValueType<Rational> v;
    v.read("5/0");
    // This should not crash, behavior is implementation-defined
    // We just make sure it doesn't throw or segfault
    try {
        int64_t val = v.toInt64(0);
        (void)val;
    } catch (...) {
        // acceptable
    }
}

TEST_F(ValueTypeEdgeCaseTest_153, URationalZeroDenominatorToFloat_153) {
    ValueType<URational> v;
    v.read("5/0");
    float f = v.toFloat(0);
    (void)f; // Just ensure no crash
}

TEST_F(ValueTypeEdgeCaseTest_153, MultipleReadsAccumulate_153) {
    // Test that reading from buffer doesn't accumulate (resets)
    ValueType<uint16_t> v;
    byte buf1[] = {0x01, 0x00};
    v.read(buf1, sizeof(buf1), littleEndian);
    EXPECT_EQ(v.count(), 1u);
    
    byte buf2[] = {0x02, 0x00, 0x03, 0x00};
    v.read(buf2, sizeof(buf2), littleEndian);
    EXPECT_EQ(v.count(), 2u);
}
