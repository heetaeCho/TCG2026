#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <sstream>
#include <cstring>

using namespace Exiv2;

// Type aliases for convenience
using UShortValue = ValueType<uint16_t>;
using ULongValue = ValueType<uint32_t>;
using URationalValue = ValueType<URational>;
using RationalValue = ValueType<Rational>;
using FloatValue = ValueType<float>;
using DoubleValue = ValueType<double>;
using ShortValue = ValueType<int16_t>;
using LongValue = ValueType<int32_t>;

// ============================================================
// Tests for ValueType<uint16_t> (UShortValue)
// ============================================================

class ValueTypeUShortTest_149 : public ::testing::Test {
protected:
    UShortValue value;
};

TEST_F(ValueTypeUShortTest_149, DefaultConstructor_EmptyValue_149) {
    EXPECT_EQ(value.count(), 0u);
    EXPECT_EQ(value.size(), 0u);
}

TEST_F(ValueTypeUShortTest_149, ReadStringSingleValue_149) {
    int result = value.read("42");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(value.count(), 1u);
    EXPECT_EQ(value.toInt64(0), 42);
}

TEST_F(ValueTypeUShortTest_149, ReadStringMultipleValues_149) {
    int result = value.read("1 2 3 4 5");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(value.count(), 5u);
    EXPECT_EQ(value.toInt64(0), 1);
    EXPECT_EQ(value.toInt64(1), 2);
    EXPECT_EQ(value.toInt64(2), 3);
    EXPECT_EQ(value.toInt64(3), 4);
    EXPECT_EQ(value.toInt64(4), 5);
}

TEST_F(ValueTypeUShortTest_149, ReadStringEmpty_149) {
    int result = value.read("");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(value.count(), 0u);
}

TEST_F(ValueTypeUShortTest_149, ReadStringInvalid_149) {
    int result = value.read("abc");
    EXPECT_EQ(result, 1);
}

TEST_F(ValueTypeUShortTest_149, ReadStringPartiallyInvalid_149) {
    int result = value.read("1 2 abc");
    EXPECT_EQ(result, 1);
}

TEST_F(ValueTypeUShortTest_149, ToStringValid_149) {
    value.read("100");
    std::string s = value.toString(0);
    EXPECT_EQ(s, "100");
}

TEST_F(ValueTypeUShortTest_149, WriteToStream_149) {
    value.read("10 20 30");
    std::ostringstream os;
    value.write(os);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

TEST_F(ValueTypeUShortTest_149, ToFloat_149) {
    value.read("42");
    float f = value.toFloat(0);
    EXPECT_FLOAT_EQ(f, 42.0f);
}

TEST_F(ValueTypeUShortTest_149, ToUint32_149) {
    value.read("65535");
    uint32_t u = value.toUint32(0);
    EXPECT_EQ(u, 65535u);
}

TEST_F(ValueTypeUShortTest_149, ToRational_149) {
    value.read("10");
    Rational r = value.toRational(0);
    EXPECT_EQ(r.first, 10);
    EXPECT_EQ(r.second, 1);
}

TEST_F(ValueTypeUShortTest_149, CopyBytes_149) {
    value.read("256");
    byte buf[2] = {0};
    size_t copied = value.copy(buf, littleEndian);
    EXPECT_EQ(copied, 2u);
}

TEST_F(ValueTypeUShortTest_149, ReadFromBytesLittleEndian_149) {
    byte buf[] = {0x01, 0x00};  // 1 in little endian
    int result = value.read(buf, sizeof(buf), littleEndian);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(value.count(), 1u);
    EXPECT_EQ(value.toInt64(0), 1);
}

TEST_F(ValueTypeUShortTest_149, ReadFromBytesBigEndian_149) {
    byte buf[] = {0x00, 0x01};  // 1 in big endian
    int result = value.read(buf, sizeof(buf), bigEndian);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(value.count(), 1u);
    EXPECT_EQ(value.toInt64(0), 1);
}

TEST_F(ValueTypeUShortTest_149, SizeAfterRead_149) {
    value.read("1 2 3");
    EXPECT_EQ(value.size(), 3u * 2u);  // 3 uint16_t values, 2 bytes each
}

TEST_F(ValueTypeUShortTest_149, DataAreaInitiallyEmpty_149) {
    EXPECT_EQ(value.sizeDataArea(), 0u);
}

TEST_F(ValueTypeUShortTest_149, SetDataArea_149) {
    byte data[] = {0x01, 0x02, 0x03};
    int result = value.setDataArea(data, sizeof(data));
    EXPECT_EQ(result, 0);
    EXPECT_EQ(value.sizeDataArea(), 3u);
    DataBuf db = value.dataArea();
    EXPECT_EQ(db.size(), 3u);
}

TEST_F(ValueTypeUShortTest_149, Clone_149) {
    value.read("42 43");
    auto cloned = value.clone();
    EXPECT_NE(cloned.get(), nullptr);
    EXPECT_EQ(cloned->count(), 2u);
    EXPECT_EQ(cloned->toInt64(0), 42);
    EXPECT_EQ(cloned->toInt64(1), 43);
}

// ============================================================
// Tests for ValueType<uint32_t> (ULongValue)
// ============================================================

class ValueTypeULongTest_149 : public ::testing::Test {
protected:
    ULongValue value;
};

TEST_F(ValueTypeULongTest_149, DefaultConstructor_149) {
    EXPECT_EQ(value.count(), 0u);
}

TEST_F(ValueTypeULongTest_149, ReadStringSingleValue_149) {
    int result = value.read("100000");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(value.count(), 1u);
    EXPECT_EQ(value.toInt64(0), 100000);
}

TEST_F(ValueTypeULongTest_149, ReadStringMultipleValues_149) {
    int result = value.read("1 2 3");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(value.count(), 3u);
}

TEST_F(ValueTypeULongTest_149, SizeCheck_149) {
    value.read("1 2");
    EXPECT_EQ(value.size(), 2u * 4u);  // 2 uint32_t values, 4 bytes each
}

TEST_F(ValueTypeULongTest_149, CopyAndReadBack_149) {
    value.read("12345");
    byte buf[4] = {0};
    size_t copied = value.copy(buf, littleEndian);
    EXPECT_EQ(copied, 4u);

    ULongValue value2;
    value2.read(buf, 4, littleEndian);
    EXPECT_EQ(value2.toInt64(0), 12345);
}

// ============================================================
// Tests for ValueType<int32_t> (LongValue)
// ============================================================

class ValueTypeLongTest_149 : public ::testing::Test {
protected:
    LongValue value;
};

TEST_F(ValueTypeLongTest_149, ReadNegativeValue_149) {
    int result = value.read("-42");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(value.count(), 1u);
    EXPECT_EQ(value.toInt64(0), -42);
}

TEST_F(ValueTypeLongTest_149, ReadMixedValues_149) {
    int result = value.read("-1 0 1");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(value.count(), 3u);
    EXPECT_EQ(value.toInt64(0), -1);
    EXPECT_EQ(value.toInt64(1), 0);
    EXPECT_EQ(value.toInt64(2), 1);
}

// ============================================================
// Tests for ValueType<Rational>
// ============================================================

class ValueTypeRationalTest_149 : public ::testing::Test {
protected:
    RationalValue value;
};

TEST_F(ValueTypeRationalTest_149, DefaultConstructor_149) {
    EXPECT_EQ(value.count(), 0u);
}

TEST_F(ValueTypeRationalTest_149, ReadStringSingleRational_149) {
    int result = value.read("1/2");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(value.count(), 1u);
}

TEST_F(ValueTypeRationalTest_149, ReadStringMultipleRationals_149) {
    int result = value.read("1/2 3/4 5/6");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(value.count(), 3u);
}

TEST_F(ValueTypeRationalTest_149, ToFloatRational_149) {
    value.read("1/2");
    float f = value.toFloat(0);
    EXPECT_FLOAT_EQ(f, 0.5f);
}

TEST_F(ValueTypeRationalTest_149, ToInt64Rational_149) {
    value.read("10/2");
    int64_t i = value.toInt64(0);
    EXPECT_EQ(i, 5);
}

TEST_F(ValueTypeRationalTest_149, ToUint32Rational_149) {
    value.read("10/2");
    uint32_t u = value.toUint32(0);
    EXPECT_EQ(u, 5u);
}

TEST_F(ValueTypeRationalTest_149, ToRationalReturnsIdentity_149) {
    value.read("3/7");
    Rational r = value.toRational(0);
    EXPECT_EQ(r.first, 3);
    EXPECT_EQ(r.second, 7);
}

TEST_F(ValueTypeRationalTest_149, NegativeRational_149) {
    value.read("-3/4");
    Rational r = value.toRational(0);
    EXPECT_EQ(r.first, -3);
    EXPECT_EQ(r.second, 4);
    float f = value.toFloat(0);
    EXPECT_FLOAT_EQ(f, -0.75f);
}

TEST_F(ValueTypeRationalTest_149, ZeroDenominatorRational_149) {
    value.read("1/0");
    EXPECT_EQ(value.count(), 1u);
    Rational r = value.toRational(0);
    EXPECT_EQ(r.first, 1);
    EXPECT_EQ(r.second, 0);
}

TEST_F(ValueTypeRationalTest_149, SizeRational_149) {
    value.read("1/2 3/4");
    // Each Rational is 8 bytes (two int32_t)
    EXPECT_EQ(value.size(), 2u * 8u);
}

TEST_F(ValueTypeRationalTest_149, WriteToStreamRational_149) {
    value.read("1/2 3/4");
    std::ostringstream os;
    value.write(os);
    std::string s = os.str();
    EXPECT_FALSE(s.empty());
}

TEST_F(ValueTypeRationalTest_149, CopyAndReadBackRational_149) {
    value.read("1/2");
    byte buf[8] = {0};
    size_t copied = value.copy(buf, littleEndian);
    EXPECT_EQ(copied, 8u);

    RationalValue value2;
    value2.read(buf, 8, littleEndian);
    EXPECT_EQ(value2.count(), 1u);
    Rational r = value2.toRational(0);
    EXPECT_EQ(r.first, 1);
    EXPECT_EQ(r.second, 2);
}

// ============================================================
// Tests for ValueType<URational>
// ============================================================

class ValueTypeURationalTest_149 : public ::testing::Test {
protected:
    URationalValue value;
};

TEST_F(ValueTypeURationalTest_149, ReadSingleURational_149) {
    int result = value.read("3/4");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(value.count(), 1u);
}

TEST_F(ValueTypeURationalTest_149, ToFloatURational_149) {
    value.read("3/4");
    float f = value.toFloat(0);
    EXPECT_FLOAT_EQ(f, 0.75f);
}

TEST_F(ValueTypeURationalTest_149, ToInt64URational_149) {
    value.read("7/2");
    int64_t i = value.toInt64(0);
    EXPECT_EQ(i, 3);  // integer division: 7/2 = 3
}

TEST_F(ValueTypeURationalTest_149, ToUint32URational_149) {
    value.read("10/5");
    uint32_t u = value.toUint32(0);
    EXPECT_EQ(u, 2u);
}

TEST_F(ValueTypeURationalTest_149, ToRationalURational_149) {
    value.read("5/3");
    Rational r = value.toRational(0);
    EXPECT_EQ(r.first, 5);
    EXPECT_EQ(r.second, 3);
}

// ============================================================
// Tests for ValueType<float>
// ============================================================

class ValueTypeFloatTest_149 : public ::testing::Test {
protected:
    FloatValue value;
};

TEST_F(ValueTypeFloatTest_149, ReadSingleFloat_149) {
    int result = value.read("3.14");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(value.count(), 1u);
    EXPECT_NEAR(value.toFloat(0), 3.14f, 0.01f);
}

TEST_F(ValueTypeFloatTest_149, ReadMultipleFloats_149) {
    int result = value.read("1.1 2.2 3.3");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(value.count(), 3u);
}

TEST_F(ValueTypeFloatTest_149, ToInt64Float_149) {
    value.read("3.7");
    int64_t i = value.toInt64(0);
    EXPECT_EQ(i, 3);  // truncation expected
}

TEST_F(ValueTypeFloatTest_149, ToUint32Float_149) {
    value.read("3.7");
    uint32_t u = value.toUint32(0);
    EXPECT_EQ(u, 3u);
}

TEST_F(ValueTypeFloatTest_149, ToRationalFloat_149) {
    value.read("0.5");
    Rational r = value.toRational(0);
    // Should approximate 0.5 as a rational
    EXPECT_NE(r.second, 0);
    float approx = static_cast<float>(r.first) / static_cast<float>(r.second);
    EXPECT_NEAR(approx, 0.5f, 0.001f);
}

TEST_F(ValueTypeFloatTest_149, NegativeFloat_149) {
    value.read("-2.5");
    EXPECT_EQ(value.count(), 1u);
    EXPECT_FLOAT_EQ(value.toFloat(0), -2.5f);
}

TEST_F(ValueTypeFloatTest_149, SizeFloat_149) {
    value.read("1.0 2.0");
    EXPECT_EQ(value.size(), 2u * 4u);  // 2 floats, 4 bytes each
}

// ============================================================
// Tests for ValueType<double>
// ============================================================

class ValueTypeDoubleTest_149 : public ::testing::Test {
protected:
    DoubleValue value;
};

TEST_F(ValueTypeDoubleTest_149, ReadSingleDouble_149) {
    int result = value.read("3.141592653589793");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(value.count(), 1u);
    EXPECT_NEAR(value.toFloat(0), 3.14159f, 0.001f);
}

TEST_F(ValueTypeDoubleTest_149, ToInt64Double_149) {
    value.read("9.99");
    int64_t i = value.toInt64(0);
    EXPECT_EQ(i, 9);
}

TEST_F(ValueTypeDoubleTest_149, ToUint32Double_149) {
    value.read("9.99");
    uint32_t u = value.toUint32(0);
    EXPECT_EQ(u, 9u);
}

TEST_F(ValueTypeDoubleTest_149, ToRationalDouble_149) {
    value.read("0.25");
    Rational r = value.toRational(0);
    EXPECT_NE(r.second, 0);
    double approx = static_cast<double>(r.first) / static_cast<double>(r.second);
    EXPECT_NEAR(approx, 0.25, 0.001);
}

TEST_F(ValueTypeDoubleTest_149, SizeDouble_149) {
    value.read("1.0 2.0 3.0");
    EXPECT_EQ(value.size(), 3u * 8u);  // 3 doubles, 8 bytes each
}

// ============================================================
// Tests for copy constructor and assignment
// ============================================================

TEST(ValueTypeCopyTest_149, CopyConstructor_149) {
    UShortValue original;
    original.read("10 20 30");
    UShortValue copy(original);
    EXPECT_EQ(copy.count(), 3u);
    EXPECT_EQ(copy.toInt64(0), 10);
    EXPECT_EQ(copy.toInt64(1), 20);
    EXPECT_EQ(copy.toInt64(2), 30);
}

TEST(ValueTypeCopyTest_149, AssignmentOperator_149) {
    UShortValue original;
    original.read("10 20");
    UShortValue assigned;
    assigned = original;
    EXPECT_EQ(assigned.count(), 2u);
    EXPECT_EQ(assigned.toInt64(0), 10);
    EXPECT_EQ(assigned.toInt64(1), 20);
}

TEST(ValueTypeCopyTest_149, CopyConstructorIndependence_149) {
    UShortValue original;
    original.read("10 20");
    UShortValue copy(original);
    original.read("99");
    // Copy should be independent
    EXPECT_EQ(copy.count(), 2u);
    EXPECT_EQ(copy.toInt64(0), 10);
    EXPECT_EQ(original.count(), 1u);
    EXPECT_EQ(original.toInt64(0), 99);
}

// ============================================================
// Tests for ValueType constructor with initial value
// ============================================================

TEST(ValueTypeConstructorTest_149, ConstructWithValue_149) {
    uint16_t val = 42;
    UShortValue v(val, unsignedShort);
    EXPECT_EQ(v.count(), 1u);
    EXPECT_EQ(v.toInt64(0), 42);
}

TEST(ValueTypeConstructorTest_149, ConstructRationalWithValue_149) {
    Rational rat(3, 7);
    RationalValue v(rat, signedRational);
    EXPECT_EQ(v.count(), 1u);
    Rational r = v.toRational(0);
    EXPECT_EQ(r.first, 3);
    EXPECT_EQ(r.second, 7);
}

// ============================================================
// Tests for boundary conditions
// ============================================================

TEST(ValueTypeBoundaryTest_149, ReadFromEmptyBytes_149) {
    UShortValue value;
    byte buf[1] = {0};
    int result = value.read(buf, 0, littleEndian);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(value.count(), 0u);
}

TEST(ValueTypeBoundaryTest_149, LargeNumberOfValues_149) {
    ULongValue value;
    std::string bigStr;
    for (int i = 0; i < 100; ++i) {
        if (i > 0) bigStr += " ";
        bigStr += std::to_string(i);
    }
    int result = value.read(bigStr);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(value.count(), 100u);
    EXPECT_EQ(value.toInt64(0), 0);
    EXPECT_EQ(value.toInt64(99), 99);
}

TEST(ValueTypeBoundaryTest_149, SingleSpaceString_149) {
    UShortValue value;
    int result = value.read(" ");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(value.count(), 0u);
}

TEST(ValueTypeBoundaryTest_149, LeadingAndTrailingSpaces_149) {
    UShortValue value;
    int result = value.read("  42  ");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(value.count(), 1u);
    EXPECT_EQ(value.toInt64(0), 42);
}

// ============================================================
// Tests for ValueType read replacing previous values
// ============================================================

TEST(ValueTypeReplaceTest_149, ReadReplacesOldValues_149) {
    UShortValue value;
    value.read("1 2 3");
    EXPECT_EQ(value.count(), 3u);
    value.read("10 20");
    EXPECT_EQ(value.count(), 2u);
    EXPECT_EQ(value.toInt64(0), 10);
    EXPECT_EQ(value.toInt64(1), 20);
}

// ============================================================
// Tests for clone
// ============================================================

TEST(ValueTypeCloneTest_149, ClonePreservesData_149) {
    RationalValue value;
    value.read("1/3 2/5");
    auto cloned = value.clone();
    EXPECT_NE(cloned.get(), nullptr);
    EXPECT_EQ(cloned->count(), 2u);
    EXPECT_EQ(cloned->toInt64(0), value.toInt64(0));
}

TEST(ValueTypeCloneTest_149, CloneIsIndependent_149) {
    ULongValue value;
    value.read("100 200");
    auto cloned = value.clone();
    value.read("999");
    EXPECT_EQ(cloned->count(), 2u);
    EXPECT_EQ(value.count(), 1u);
}

// ============================================================
// Tests for DataArea functionality
// ============================================================

TEST(ValueTypeDataAreaTest_149, SetAndGetDataArea_149) {
    UShortValue value;
    byte data[] = {0xAA, 0xBB, 0xCC, 0xDD};
    int result = value.setDataArea(data, sizeof(data));
    EXPECT_EQ(result, 0);
    EXPECT_EQ(value.sizeDataArea(), 4u);
    DataBuf db = value.dataArea();
    EXPECT_EQ(db.size(), 4u);
}

TEST(ValueTypeDataAreaTest_149, EmptyDataArea_149) {
    ULongValue value;
    EXPECT_EQ(value.sizeDataArea(), 0u);
    DataBuf db = value.dataArea();
    EXPECT_EQ(db.size(), 0u);
}

// ============================================================
// Tests for write output format
// ============================================================

TEST(ValueTypeWriteTest_149, WriteUShortMultiple_149) {
    UShortValue value;
    value.read("10 20 30");
    std::ostringstream os;
    value.write(os);
    std::string s = os.str();
    // Should contain the values somehow
    EXPECT_NE(s.find("10"), std::string::npos);
    EXPECT_NE(s.find("20"), std::string::npos);
    EXPECT_NE(s.find("30"), std::string::npos);
}

TEST(ValueTypeWriteTest_149, WriteRational_149) {
    RationalValue value;
    value.read("1/2");
    std::ostringstream os;
    value.write(os);
    std::string s = os.str();
    EXPECT_NE(s.find("1"), std::string::npos);
    EXPECT_NE(s.find("2"), std::string::npos);
}

// ============================================================
// Tests for toString
// ============================================================

TEST(ValueTypeToStringTest_149, ToStringMultipleElements_149) {
    ULongValue value;
    value.read("100 200 300");
    EXPECT_EQ(value.toString(0), "100");
    EXPECT_EQ(value.toString(1), "200");
    EXPECT_EQ(value.toString(2), "300");
}

TEST(ValueTypeToStringTest_149, ToStringRational_149) {
    RationalValue value;
    value.read("3/7");
    std::string s = value.toString(0);
    EXPECT_NE(s.find("3"), std::string::npos);
    EXPECT_NE(s.find("7"), std::string::npos);
}

// ============================================================
// Tests for reading from byte buffer with multiple values
// ============================================================

TEST(ValueTypeByteReadTest_149, ReadMultipleUShortFromBytes_149) {
    byte buf[] = {0x01, 0x00, 0x02, 0x00};  // 1, 2 in little endian
    UShortValue value;
    int result = value.read(buf, sizeof(buf), littleEndian);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(value.count(), 2u);
    EXPECT_EQ(value.toInt64(0), 1);
    EXPECT_EQ(value.toInt64(1), 2);
}

TEST(ValueTypeByteReadTest_149, ReadMultipleULongFromBytesBigEndian_149) {
    byte buf[] = {0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x14};  // 10, 20 in big endian
    ULongValue value;
    int result = value.read(buf, sizeof(buf), bigEndian);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(value.count(), 2u);
    EXPECT_EQ(value.toInt64(0), 10);
    EXPECT_EQ(value.toInt64(1), 20);
}

// ============================================================
// Tests for endianness in copy
// ============================================================

TEST(ValueTypeCopyBytesTest_149, CopyLittleEndian_149) {
    UShortValue value;
    value.read("258");  // 0x0102
    byte buf[2] = {0};
    value.copy(buf, littleEndian);
    EXPECT_EQ(buf[0], 0x02);
    EXPECT_EQ(buf[1], 0x01);
}

TEST(ValueTypeCopyBytesTest_149, CopyBigEndian_149) {
    UShortValue value;
    value.read("258");  // 0x0102
    byte buf[2] = {0};
    value.copy(buf, bigEndian);
    EXPECT_EQ(buf[0], 0x01);
    EXPECT_EQ(buf[1], 0x02);
}

// ============================================================
// Tests for zero value
// ============================================================

TEST(ValueTypeZeroTest_149, ZeroUShort_149) {
    UShortValue value;
    value.read("0");
    EXPECT_EQ(value.count(), 1u);
    EXPECT_EQ(value.toInt64(0), 0);
    EXPECT_EQ(value.toUint32(0), 0u);
    EXPECT_FLOAT_EQ(value.toFloat(0), 0.0f);
}

TEST(ValueTypeZeroTest_149, ZeroRational_149) {
    RationalValue value;
    value.read("0/1");
    EXPECT_EQ(value.count(), 1u);
    EXPECT_FLOAT_EQ(value.toFloat(0), 0.0f);
    EXPECT_EQ(value.toInt64(0), 0);
}
