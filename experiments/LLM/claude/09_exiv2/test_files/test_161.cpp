#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <exiv2/types.hpp>
#include <sstream>
#include <cstring>

using namespace Exiv2;

// ============================================================
// Tests for ValueType<Rational>
// ============================================================

class ValueTypeRationalTest_161 : public ::testing::Test {
protected:
    using RationalValue = ValueType<Rational>;
};

TEST_F(ValueTypeRationalTest_161, DefaultConstructor_161) {
    RationalValue v;
    EXPECT_EQ(v.count(), 0u);
    EXPECT_EQ(v.size(), 0u);
}

TEST_F(ValueTypeRationalTest_161, ConstructWithSingleValue_161) {
    Rational r(1, 2);
    RationalValue v(r);
    EXPECT_EQ(v.count(), 1u);
    EXPECT_EQ(v.value_[0], r);
}

TEST_F(ValueTypeRationalTest_161, ToInt64_PositiveRational_161) {
    Rational r(7, 2);
    RationalValue v(r);
    EXPECT_EQ(v.toInt64(0), 3);  // 7/2 = 3 (integer truncation)
}

TEST_F(ValueTypeRationalTest_161, ToInt64_NegativeRational_161) {
    Rational r(-7, 2);
    RationalValue v(r);
    EXPECT_EQ(v.toInt64(0), -3);  // -7/2 = -3
}

TEST_F(ValueTypeRationalTest_161, ToInt64_ExactDivision_161) {
    Rational r(10, 5);
    RationalValue v(r);
    EXPECT_EQ(v.toInt64(0), 2);
}

TEST_F(ValueTypeRationalTest_161, ToInt64_ZeroNumerator_161) {
    Rational r(0, 1);
    RationalValue v(r);
    EXPECT_EQ(v.toInt64(0), 0);
}

TEST_F(ValueTypeRationalTest_161, ToInt64_ZeroDenominator_161) {
    Rational r(5, 0);
    RationalValue v(r);
    // When denominator is 0, behavior should still not crash
    // The result depends on implementation; just ensure no crash
    v.toInt64(0);
}

TEST_F(ValueTypeRationalTest_161, ToInt64_NegativeDenominator_161) {
    Rational r(7, -2);
    RationalValue v(r);
    int64_t result = v.toInt64(0);
    EXPECT_EQ(result, -3);
}

TEST_F(ValueTypeRationalTest_161, ToInt64_MultipleValues_161) {
    RationalValue v;
    v.value_.push_back(Rational(1, 1));
    v.value_.push_back(Rational(10, 3));
    v.value_.push_back(Rational(99, 10));
    EXPECT_EQ(v.count(), 3u);
    EXPECT_EQ(v.toInt64(0), 1);
    EXPECT_EQ(v.toInt64(1), 3);   // 10/3 = 3
    EXPECT_EQ(v.toInt64(2), 9);   // 99/10 = 9
}

TEST_F(ValueTypeRationalTest_161, ToUint32_PositiveRational_161) {
    Rational r(7, 2);
    RationalValue v(r);
    EXPECT_EQ(v.toUint32(0), 3u);
}

TEST_F(ValueTypeRationalTest_161, ToFloat_PositiveRational_161) {
    Rational r(1, 4);
    RationalValue v(r);
    EXPECT_FLOAT_EQ(v.toFloat(0), 0.25f);
}

TEST_F(ValueTypeRationalTest_161, ToFloat_NegativeRational_161) {
    Rational r(-3, 4);
    RationalValue v(r);
    EXPECT_FLOAT_EQ(v.toFloat(0), -0.75f);
}

TEST_F(ValueTypeRationalTest_161, ToRational_ReturnsSame_161) {
    Rational r(3, 7);
    RationalValue v(r);
    Rational result = v.toRational(0);
    EXPECT_EQ(result.first, 3);
    EXPECT_EQ(result.second, 7);
}

TEST_F(ValueTypeRationalTest_161, ToString_161) {
    Rational r(1, 2);
    RationalValue v(r);
    std::string s = v.toString(0);
    EXPECT_EQ(s, "1/2");
}

TEST_F(ValueTypeRationalTest_161, Write_161) {
    Rational r(3, 4);
    RationalValue v(r);
    std::ostringstream os;
    v.write(os);
    EXPECT_EQ(os.str(), "3/4");
}

TEST_F(ValueTypeRationalTest_161, CopyAndCount_161) {
    RationalValue v;
    v.value_.push_back(Rational(1, 2));
    v.value_.push_back(Rational(3, 4));
    EXPECT_EQ(v.count(), 2u);
    EXPECT_EQ(v.size(), 2u * 8u);  // Each Rational is 2 * 4 bytes = 8 bytes
}

TEST_F(ValueTypeRationalTest_161, CopyToBuffer_161) {
    Rational r(1, 2);
    RationalValue v(r);
    byte buf[8];
    size_t copied = v.copy(buf, bigEndian);
    EXPECT_EQ(copied, 8u);
}

TEST_F(ValueTypeRationalTest_161, ReadFromBuffer_161) {
    // Prepare a buffer with a Rational in big-endian: 1/2
    byte buf[8];
    buf[0] = 0; buf[1] = 0; buf[2] = 0; buf[3] = 1;  // numerator = 1
    buf[4] = 0; buf[5] = 0; buf[6] = 0; buf[7] = 2;  // denominator = 2
    RationalValue v;
    int rc = v.read(buf, 8, bigEndian);
    EXPECT_EQ(rc, 0);
    EXPECT_EQ(v.count(), 1u);
    EXPECT_EQ(v.toInt64(0), 0);  // 1/2 truncated to int = 0
    EXPECT_FLOAT_EQ(v.toFloat(0), 0.5f);
}

TEST_F(ValueTypeRationalTest_161, ReadFromString_161) {
    RationalValue v;
    int rc = v.read("3/4");
    EXPECT_EQ(rc, 0);
    EXPECT_EQ(v.count(), 1u);
    EXPECT_EQ(v.toRational(0).first, 3);
    EXPECT_EQ(v.toRational(0).second, 4);
}

TEST_F(ValueTypeRationalTest_161, ReadMultipleFromString_161) {
    RationalValue v;
    int rc = v.read("1/2 3/4 5/6");
    EXPECT_EQ(rc, 0);
    EXPECT_EQ(v.count(), 3u);
    EXPECT_EQ(v.toRational(0), Rational(1, 2));
    EXPECT_EQ(v.toRational(1), Rational(3, 4));
    EXPECT_EQ(v.toRational(2), Rational(5, 6));
}

TEST_F(ValueTypeRationalTest_161, CloneProducesCopy_161) {
    Rational r(5, 3);
    RationalValue v(r);
    auto cloned = v.clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->count(), 1u);
    EXPECT_EQ(cloned->toInt64(0), 1);  // 5/3 = 1
}

TEST_F(ValueTypeRationalTest_161, AssignmentOperator_161) {
    Rational r1(1, 2);
    Rational r2(3, 4);
    RationalValue v1(r1);
    RationalValue v2(r2);
    v1 = v2;
    EXPECT_EQ(v1.count(), 1u);
    EXPECT_EQ(v1.toRational(0), Rational(3, 4));
}

TEST_F(ValueTypeRationalTest_161, CopyConstructor_161) {
    Rational r(7, 3);
    RationalValue v1(r);
    RationalValue v2(v1);
    EXPECT_EQ(v2.count(), 1u);
    EXPECT_EQ(v2.toRational(0), Rational(7, 3));
}

TEST_F(ValueTypeRationalTest_161, DataArea_EmptyByDefault_161) {
    RationalValue v;
    EXPECT_EQ(v.sizeDataArea(), 0u);
    DataBuf db = v.dataArea();
    EXPECT_EQ(db.size(), 0u);
}

TEST_F(ValueTypeRationalTest_161, SetDataArea_161) {
    RationalValue v;
    byte data[] = {1, 2, 3, 4};
    int rc = v.setDataArea(data, sizeof(data));
    EXPECT_EQ(rc, 0);
    EXPECT_EQ(v.sizeDataArea(), 4u);
    DataBuf db = v.dataArea();
    EXPECT_EQ(db.size(), 4u);
}

TEST_F(ValueTypeRationalTest_161, ToInt64_LargeRational_161) {
    Rational r(1000000, 1);
    RationalValue v(r);
    EXPECT_EQ(v.toInt64(0), 1000000);
}

TEST_F(ValueTypeRationalTest_161, ToInt64_UnitRational_161) {
    Rational r(1, 1);
    RationalValue v(r);
    EXPECT_EQ(v.toInt64(0), 1);
}

// ============================================================
// Tests for ValueType<URational>
// ============================================================

class ValueTypeURationalTest_161 : public ::testing::Test {
protected:
    using URationalValue = ValueType<URational>;
};

TEST_F(ValueTypeURationalTest_161, DefaultConstructor_161) {
    URationalValue v;
    EXPECT_EQ(v.count(), 0u);
}

TEST_F(ValueTypeURationalTest_161, ToInt64_161) {
    URational r(10, 3);
    URationalValue v(r);
    EXPECT_EQ(v.toInt64(0), 3);  // 10/3 = 3
}

TEST_F(ValueTypeURationalTest_161, ToUint32_161) {
    URational r(10, 3);
    URationalValue v(r);
    EXPECT_EQ(v.toUint32(0), 3u);
}

TEST_F(ValueTypeURationalTest_161, ToFloat_161) {
    URational r(1, 4);
    URationalValue v(r);
    EXPECT_FLOAT_EQ(v.toFloat(0), 0.25f);
}

TEST_F(ValueTypeURationalTest_161, ToRational_161) {
    URational ur(3, 7);
    URationalValue v(ur);
    Rational r = v.toRational(0);
    EXPECT_EQ(r.first, 3);
    EXPECT_EQ(r.second, 7);
}

TEST_F(ValueTypeURationalTest_161, ToInt64_ZeroDenominator_161) {
    URational r(5, 0);
    URationalValue v(r);
    // Should not crash
    v.toInt64(0);
}

TEST_F(ValueTypeURationalTest_161, ZeroNumerator_161) {
    URational r(0, 100);
    URationalValue v(r);
    EXPECT_EQ(v.toInt64(0), 0);
    EXPECT_FLOAT_EQ(v.toFloat(0), 0.0f);
}

// ============================================================
// Tests for ValueType<float>
// ============================================================

class ValueTypeFloatTest_161 : public ::testing::Test {
protected:
    using FloatValue = ValueType<float>;
};

TEST_F(ValueTypeFloatTest_161, DefaultConstructor_161) {
    FloatValue v;
    EXPECT_EQ(v.count(), 0u);
}

TEST_F(ValueTypeFloatTest_161, ConstructWithValue_161) {
    FloatValue v(3.14f);
    EXPECT_EQ(v.count(), 1u);
    EXPECT_FLOAT_EQ(v.toFloat(0), 3.14f);
}

TEST_F(ValueTypeFloatTest_161, ToInt64_161) {
    FloatValue v(3.7f);
    EXPECT_EQ(v.toInt64(0), 3);
}

TEST_F(ValueTypeFloatTest_161, ToInt64_Negative_161) {
    FloatValue v(-3.7f);
    EXPECT_EQ(v.toInt64(0), -3);
}

TEST_F(ValueTypeFloatTest_161, ToUint32_161) {
    FloatValue v(5.9f);
    EXPECT_EQ(v.toUint32(0), 5u);
}

TEST_F(ValueTypeFloatTest_161, ToRational_161) {
    FloatValue v(0.5f);
    Rational r = v.toRational(0);
    // Should represent 0.5 as a rational
    EXPECT_NE(r.second, 0);
    float reconstructed = static_cast<float>(r.first) / static_cast<float>(r.second);
    EXPECT_NEAR(reconstructed, 0.5f, 0.001f);
}

TEST_F(ValueTypeFloatTest_161, ToInt64_Zero_161) {
    FloatValue v(0.0f);
    EXPECT_EQ(v.toInt64(0), 0);
}

// ============================================================
// Tests for ValueType<double>
// ============================================================

class ValueTypeDoubleTest_161 : public ::testing::Test {
protected:
    using DoubleValue = ValueType<double>;
};

TEST_F(ValueTypeDoubleTest_161, DefaultConstructor_161) {
    DoubleValue v;
    EXPECT_EQ(v.count(), 0u);
}

TEST_F(ValueTypeDoubleTest_161, ToInt64_161) {
    DoubleValue v(9.99);
    EXPECT_EQ(v.toInt64(0), 9);
}

TEST_F(ValueTypeDoubleTest_161, ToInt64_Negative_161) {
    DoubleValue v(-9.99);
    EXPECT_EQ(v.toInt64(0), -9);
}

TEST_F(ValueTypeDoubleTest_161, ToUint32_161) {
    DoubleValue v(42.1);
    EXPECT_EQ(v.toUint32(0), 42u);
}

TEST_F(ValueTypeDoubleTest_161, ToFloat_161) {
    DoubleValue v(1.5);
    EXPECT_FLOAT_EQ(v.toFloat(0), 1.5f);
}

TEST_F(ValueTypeDoubleTest_161, ToRational_161) {
    DoubleValue v(0.25);
    Rational r = v.toRational(0);
    EXPECT_NE(r.second, 0);
    double reconstructed = static_cast<double>(r.first) / static_cast<double>(r.second);
    EXPECT_NEAR(reconstructed, 0.25, 0.001);
}

// ============================================================
// Tests for ValueType<uint16_t> (UShortValue)
// ============================================================

class ValueTypeUShortTest_161 : public ::testing::Test {
protected:
    using UShortValue = ValueType<uint16_t>;
};

TEST_F(ValueTypeUShortTest_161, DefaultConstructor_161) {
    UShortValue v;
    EXPECT_EQ(v.count(), 0u);
}

TEST_F(ValueTypeUShortTest_161, ConstructWithValue_161) {
    UShortValue v(static_cast<uint16_t>(42));
    EXPECT_EQ(v.count(), 1u);
    EXPECT_EQ(v.toInt64(0), 42);
}

TEST_F(ValueTypeUShortTest_161, ToFloat_161) {
    UShortValue v(static_cast<uint16_t>(100));
    EXPECT_FLOAT_EQ(v.toFloat(0), 100.0f);
}

TEST_F(ValueTypeUShortTest_161, ToRational_161) {
    UShortValue v(static_cast<uint16_t>(5));
    Rational r = v.toRational(0);
    EXPECT_EQ(r.first, 5);
    EXPECT_EQ(r.second, 1);
}

TEST_F(ValueTypeUShortTest_161, ReadFromString_161) {
    UShortValue v;
    int rc = v.read("10 20 30");
    EXPECT_EQ(rc, 0);
    EXPECT_EQ(v.count(), 3u);
    EXPECT_EQ(v.toInt64(0), 10);
    EXPECT_EQ(v.toInt64(1), 20);
    EXPECT_EQ(v.toInt64(2), 30);
}

TEST_F(ValueTypeUShortTest_161, ReadFromBuffer_161) {
    byte buf[4];
    // big-endian: 0x0001 = 1, 0x0002 = 2
    buf[0] = 0; buf[1] = 1;
    buf[2] = 0; buf[3] = 2;
    UShortValue v;
    int rc = v.read(buf, 4, bigEndian);
    EXPECT_EQ(rc, 0);
    EXPECT_EQ(v.count(), 2u);
    EXPECT_EQ(v.toInt64(0), 1);
    EXPECT_EQ(v.toInt64(1), 2);
}

TEST_F(ValueTypeUShortTest_161, CopyToBuffer_161) {
    UShortValue v(static_cast<uint16_t>(0x1234));
    byte buf[2];
    size_t copied = v.copy(buf, bigEndian);
    EXPECT_EQ(copied, 2u);
    EXPECT_EQ(buf[0], 0x12);
    EXPECT_EQ(buf[1], 0x34);
}

TEST_F(ValueTypeUShortTest_161, Size_161) {
    UShortValue v;
    v.value_.push_back(1);
    v.value_.push_back(2);
    v.value_.push_back(3);
    EXPECT_EQ(v.size(), 6u);  // 3 * sizeof(uint16_t) = 6
}

TEST_F(ValueTypeUShortTest_161, BoundaryMaxValue_161) {
    UShortValue v(static_cast<uint16_t>(65535));
    EXPECT_EQ(v.toInt64(0), 65535);
    EXPECT_EQ(v.toUint32(0), 65535u);
}

TEST_F(ValueTypeUShortTest_161, BoundaryMinValue_161) {
    UShortValue v(static_cast<uint16_t>(0));
    EXPECT_EQ(v.toInt64(0), 0);
}

// ============================================================
// Tests for ValueType<int32_t> (LongValue)
// ============================================================

class ValueTypeLongTest_161 : public ::testing::Test {
protected:
    using LongValue = ValueType<int32_t>;
};

TEST_F(ValueTypeLongTest_161, ConstructWithValue_161) {
    LongValue v(static_cast<int32_t>(-12345));
    EXPECT_EQ(v.count(), 1u);
    EXPECT_EQ(v.toInt64(0), -12345);
}

TEST_F(ValueTypeLongTest_161, ToFloat_161) {
    LongValue v(static_cast<int32_t>(42));
    EXPECT_FLOAT_EQ(v.toFloat(0), 42.0f);
}

TEST_F(ValueTypeLongTest_161, ToRational_161) {
    LongValue v(static_cast<int32_t>(7));
    Rational r = v.toRational(0);
    EXPECT_EQ(r.first, 7);
    EXPECT_EQ(r.second, 1);
}

TEST_F(ValueTypeLongTest_161, Clone_161) {
    LongValue v(static_cast<int32_t>(99));
    auto c = v.clone();
    ASSERT_NE(c, nullptr);
    EXPECT_EQ(c->toInt64(0), 99);
}

// ============================================================
// Tests for edge cases with ValueType<Rational> write/toString
// ============================================================

class ValueTypeRationalWriteTest_161 : public ::testing::Test {
protected:
    using RationalValue = ValueType<Rational>;
};

TEST_F(ValueTypeRationalWriteTest_161, WriteMultipleValues_161) {
    RationalValue v;
    v.value_.push_back(Rational(1, 2));
    v.value_.push_back(Rational(3, 4));
    std::ostringstream os;
    v.write(os);
    std::string result = os.str();
    EXPECT_NE(result.find("1/2"), std::string::npos);
    EXPECT_NE(result.find("3/4"), std::string::npos);
}

TEST_F(ValueTypeRationalWriteTest_161, ToStringIndexed_161) {
    RationalValue v;
    v.value_.push_back(Rational(1, 2));
    v.value_.push_back(Rational(3, 4));
    EXPECT_EQ(v.toString(0), "1/2");
    EXPECT_EQ(v.toString(1), "3/4");
}

TEST_F(ValueTypeRationalWriteTest_161, NegativeRationalToString_161) {
    RationalValue v;
    v.value_.push_back(Rational(-5, 3));
    EXPECT_EQ(v.toString(0), "-5/3");
}

// ============================================================
// Round-trip test: read from buffer then copy back
// ============================================================

TEST(ValueTypeRoundTrip_161, RationalRoundTrip_161) {
    using RationalValue = ValueType<Rational>;
    
    // Create a rational value
    RationalValue v1;
    v1.value_.push_back(Rational(123, 456));
    
    // Copy to buffer
    byte buf[8];
    size_t copied = v1.copy(buf, littleEndian);
    EXPECT_EQ(copied, 8u);
    
    // Read back
    RationalValue v2;
    int rc = v2.read(buf, 8, littleEndian);
    EXPECT_EQ(rc, 0);
    EXPECT_EQ(v2.count(), 1u);
    EXPECT_EQ(v2.toRational(0), Rational(123, 456));
}

TEST(ValueTypeRoundTrip_161, UShortRoundTrip_161) {
    using UShortValue = ValueType<uint16_t>;
    
    UShortValue v1;
    v1.value_.push_back(100);
    v1.value_.push_back(200);
    v1.value_.push_back(300);
    
    byte buf[6];
    size_t copied = v1.copy(buf, bigEndian);
    EXPECT_EQ(copied, 6u);
    
    UShortValue v2;
    int rc = v2.read(buf, 6, bigEndian);
    EXPECT_EQ(rc, 0);
    EXPECT_EQ(v2.count(), 3u);
    EXPECT_EQ(v2.toInt64(0), 100);
    EXPECT_EQ(v2.toInt64(1), 200);
    EXPECT_EQ(v2.toInt64(2), 300);
}
