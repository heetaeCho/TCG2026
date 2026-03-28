#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <exiv2/types.hpp>
#include <sstream>
#include <cstring>

using namespace Exiv2;

// ============================================================
// Tests for ValueType<uint16_t> (UShortValue)
// ============================================================

class ValueTypeUShortTest_137 : public ::testing::Test {
protected:
    void SetUp() override {
    }
};

TEST_F(ValueTypeUShortTest_137, DefaultConstructor_137) {
    ValueType<uint16_t> v;
    EXPECT_EQ(v.count(), 0u);
    EXPECT_EQ(v.size(), 0u);
    EXPECT_EQ(v.typeId(), unsignedShort);
}

TEST_F(ValueTypeUShortTest_137, ConstructorWithValue_137) {
    ValueType<uint16_t> v(42, unsignedShort);
    EXPECT_EQ(v.count(), 1u);
    EXPECT_EQ(v.toInt64(0), 42);
}

TEST_F(ValueTypeUShortTest_137, ReadFromString_137) {
    ValueType<uint16_t> v;
    v.read("100 200 300");
    EXPECT_EQ(v.count(), 3u);
    EXPECT_EQ(v.toInt64(0), 100);
    EXPECT_EQ(v.toInt64(1), 200);
    EXPECT_EQ(v.toInt64(2), 300);
}

TEST_F(ValueTypeUShortTest_137, ReadFromBuffer_137) {
    uint16_t data[] = {0x0001, 0x0002};
    ValueType<uint16_t> v;
    v.read(reinterpret_cast<const byte*>(data), sizeof(data), littleEndian);
    EXPECT_EQ(v.count(), 2u);
    EXPECT_EQ(v.toInt64(0), 1);
    EXPECT_EQ(v.toInt64(1), 2);
}

TEST_F(ValueTypeUShortTest_137, CopyToBuffer_137) {
    ValueType<uint16_t> v;
    v.read("1 2 3");
    byte buf[6];
    size_t copied = v.copy(buf, littleEndian);
    EXPECT_EQ(copied, 6u);
}

TEST_F(ValueTypeUShortTest_137, ToString_137) {
    ValueType<uint16_t> v;
    v.read("42");
    EXPECT_EQ(v.toString(0), "42");
}

TEST_F(ValueTypeUShortTest_137, WriteToStream_137) {
    ValueType<uint16_t> v;
    v.read("10 20");
    std::ostringstream os;
    v.write(os);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

TEST_F(ValueTypeUShortTest_137, Clone_137) {
    ValueType<uint16_t> v;
    v.read("5 10 15");
    auto cloned = v.clone();
    EXPECT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->count(), 3u);
    EXPECT_EQ(cloned->toInt64(0), 5);
    EXPECT_EQ(cloned->toInt64(1), 10);
    EXPECT_EQ(cloned->toInt64(2), 15);
}

TEST_F(ValueTypeUShortTest_137, CopyConstructor_137) {
    ValueType<uint16_t> v;
    v.read("7 14");
    ValueType<uint16_t> v2(v);
    EXPECT_EQ(v2.count(), 2u);
    EXPECT_EQ(v2.toInt64(0), 7);
    EXPECT_EQ(v2.toInt64(1), 14);
}

TEST_F(ValueTypeUShortTest_137, AssignmentOperator_137) {
    ValueType<uint16_t> v;
    v.read("1 2 3");
    ValueType<uint16_t> v2;
    v2 = v;
    EXPECT_EQ(v2.count(), 3u);
    EXPECT_EQ(v2.toInt64(0), 1);
    EXPECT_EQ(v2.toInt64(1), 2);
    EXPECT_EQ(v2.toInt64(2), 3);
}

TEST_F(ValueTypeUShortTest_137, ToFloat_137) {
    ValueType<uint16_t> v(100, unsignedShort);
    EXPECT_FLOAT_EQ(v.toFloat(0), 100.0f);
}

TEST_F(ValueTypeUShortTest_137, ToRational_137) {
    ValueType<uint16_t> v(50, unsignedShort);
    Rational r = v.toRational(0);
    EXPECT_EQ(r.first, 50);
    EXPECT_EQ(r.second, 1);
}

TEST_F(ValueTypeUShortTest_137, ToUint32_137) {
    ValueType<uint16_t> v(65535, unsignedShort);
    EXPECT_EQ(v.toUint32(0), 65535u);
}

TEST_F(ValueTypeUShortTest_137, SizeCorrect_137) {
    ValueType<uint16_t> v;
    v.read("1 2 3 4 5");
    EXPECT_EQ(v.size(), 10u); // 5 * sizeof(uint16_t)
}

TEST_F(ValueTypeUShortTest_137, EmptyCount_137) {
    ValueType<uint16_t> v;
    EXPECT_EQ(v.count(), 0u);
}

TEST_F(ValueTypeUShortTest_137, DataAreaInitiallyEmpty_137) {
    ValueType<uint16_t> v;
    EXPECT_EQ(v.sizeDataArea(), 0u);
}

TEST_F(ValueTypeUShortTest_137, SetDataArea_137) {
    ValueType<uint16_t> v;
    byte data[] = {0x01, 0x02, 0x03, 0x04};
    v.setDataArea(data, sizeof(data));
    EXPECT_EQ(v.sizeDataArea(), 4u);
    DataBuf db = v.dataArea();
    EXPECT_EQ(db.size(), 4u);
}

// ============================================================
// Tests for ValueType<uint32_t> (ULongValue)
// ============================================================

class ValueTypeULongTest_137 : public ::testing::Test {};

TEST_F(ValueTypeULongTest_137, DefaultConstructor_137) {
    ValueType<uint32_t> v;
    EXPECT_EQ(v.count(), 0u);
    EXPECT_EQ(v.typeId(), unsignedLong);
}

TEST_F(ValueTypeULongTest_137, ReadFromString_137) {
    ValueType<uint32_t> v;
    v.read("1000000 2000000");
    EXPECT_EQ(v.count(), 2u);
    EXPECT_EQ(v.toInt64(0), 1000000);
    EXPECT_EQ(v.toInt64(1), 2000000);
}

TEST_F(ValueTypeULongTest_137, LargeValue_137) {
    ValueType<uint32_t> v(4294967295u, unsignedLong);
    EXPECT_EQ(v.toUint32(0), 4294967295u);
}

TEST_F(ValueTypeULongTest_137, Clone_137) {
    ValueType<uint32_t> v;
    v.read("123456789");
    auto c = v.clone();
    EXPECT_EQ(c->count(), 1u);
    EXPECT_EQ(c->toInt64(0), 123456789);
}

// ============================================================
// Tests for ValueType<int16_t> (ShortValue)
// ============================================================

class ValueTypeShortTest_137 : public ::testing::Test {};

TEST_F(ValueTypeShortTest_137, NegativeValue_137) {
    ValueType<int16_t> v;
    v.read("-100");
    EXPECT_EQ(v.count(), 1u);
    EXPECT_EQ(v.toInt64(0), -100);
}

TEST_F(ValueTypeShortTest_137, MultipleValues_137) {
    ValueType<int16_t> v;
    v.read("-1 0 1");
    EXPECT_EQ(v.count(), 3u);
    EXPECT_EQ(v.toInt64(0), -1);
    EXPECT_EQ(v.toInt64(1), 0);
    EXPECT_EQ(v.toInt64(2), 1);
}

// ============================================================
// Tests for ValueType<Rational>
// ============================================================

class ValueTypeRationalTest_137 : public ::testing::Test {};

TEST_F(ValueTypeRationalTest_137, DefaultConstructor_137) {
    ValueType<Rational> v;
    EXPECT_EQ(v.count(), 0u);
    EXPECT_EQ(v.typeId(), signedRational);
}

TEST_F(ValueTypeRationalTest_137, ReadFromString_137) {
    ValueType<Rational> v;
    v.read("1/2 3/4");
    EXPECT_EQ(v.count(), 2u);
    Rational r0 = v.toRational(0);
    EXPECT_EQ(r0.first, 1);
    EXPECT_EQ(r0.second, 2);
    Rational r1 = v.toRational(1);
    EXPECT_EQ(r1.first, 3);
    EXPECT_EQ(r1.second, 4);
}

TEST_F(ValueTypeRationalTest_137, ToFloat_137) {
    ValueType<Rational> v;
    v.read("1/2");
    EXPECT_FLOAT_EQ(v.toFloat(0), 0.5f);
}

TEST_F(ValueTypeRationalTest_137, ToInt64_137) {
    ValueType<Rational> v;
    v.read("10/3");
    EXPECT_EQ(v.toInt64(0), 3);
}

TEST_F(ValueTypeRationalTest_137, ZeroDenominator_137) {
    ValueType<Rational> v;
    v.read("1/0");
    // When denominator is 0, toFloat should handle it
    float f = v.toFloat(0);
    // The behavior might be implementation-defined, just ensure no crash
    (void)f;
}

TEST_F(ValueTypeRationalTest_137, NegativeRational_137) {
    ValueType<Rational> v;
    v.read("-1/2");
    Rational r = v.toRational(0);
    EXPECT_EQ(r.first, -1);
    EXPECT_EQ(r.second, 2);
    EXPECT_FLOAT_EQ(v.toFloat(0), -0.5f);
}

TEST_F(ValueTypeRationalTest_137, Clone_137) {
    ValueType<Rational> v;
    v.read("22/7");
    auto c = v.clone();
    EXPECT_EQ(c->count(), 1u);
    Rational r = c->toRational(0);
    EXPECT_EQ(r.first, 22);
    EXPECT_EQ(r.second, 7);
}

TEST_F(ValueTypeRationalTest_137, CopyConstructor_137) {
    ValueType<Rational> v;
    v.read("3/5");
    ValueType<Rational> v2(v);
    EXPECT_EQ(v2.count(), 1u);
    Rational r = v2.toRational(0);
    EXPECT_EQ(r.first, 3);
    EXPECT_EQ(r.second, 5);
}

TEST_F(ValueTypeRationalTest_137, ToString_137) {
    ValueType<Rational> v;
    v.read("1/4");
    std::string s = v.toString(0);
    EXPECT_EQ(s, "1/4");
}

TEST_F(ValueTypeRationalTest_137, Size_137) {
    ValueType<Rational> v;
    v.read("1/2 3/4");
    // Rational is two int32_t values = 8 bytes each
    EXPECT_EQ(v.size(), 16u);
}

// ============================================================
// Tests for ValueType<URational>
// ============================================================

class ValueTypeURationalTest_137 : public ::testing::Test {};

TEST_F(ValueTypeURationalTest_137, DefaultConstructor_137) {
    ValueType<URational> v;
    EXPECT_EQ(v.count(), 0u);
    EXPECT_EQ(v.typeId(), unsignedRational);
}

TEST_F(ValueTypeURationalTest_137, ReadFromString_137) {
    ValueType<URational> v;
    v.read("3/2");
    EXPECT_EQ(v.count(), 1u);
    EXPECT_FLOAT_EQ(v.toFloat(0), 1.5f);
}

TEST_F(ValueTypeURationalTest_137, ToInt64_137) {
    ValueType<URational> v;
    v.read("7/2");
    EXPECT_EQ(v.toInt64(0), 3);
}

TEST_F(ValueTypeURationalTest_137, ToUint32_137) {
    ValueType<URational> v;
    v.read("10/3");
    EXPECT_EQ(v.toUint32(0), 3u);
}

TEST_F(ValueTypeURationalTest_137, ToRational_137) {
    ValueType<URational> v;
    v.read("5/3");
    Rational r = v.toRational(0);
    EXPECT_EQ(r.first, 5);
    EXPECT_EQ(r.second, 3);
}

// ============================================================
// Tests for ValueType<float>
// ============================================================

class ValueTypeFloatTest_137 : public ::testing::Test {};

TEST_F(ValueTypeFloatTest_137, DefaultConstructor_137) {
    ValueType<float> v;
    EXPECT_EQ(v.count(), 0u);
    EXPECT_EQ(v.typeId(), tiffFloat);
}

TEST_F(ValueTypeFloatTest_137, ReadFromString_137) {
    ValueType<float> v;
    v.read("3.14");
    EXPECT_EQ(v.count(), 1u);
    EXPECT_NEAR(v.toFloat(0), 3.14f, 0.01f);
}

TEST_F(ValueTypeFloatTest_137, ToInt64_137) {
    ValueType<float> v;
    v.read("3.7");
    EXPECT_EQ(v.toInt64(0), 3);
}

TEST_F(ValueTypeFloatTest_137, ToUint32_137) {
    ValueType<float> v;
    v.read("42.9");
    EXPECT_EQ(v.toUint32(0), 42u);
}

TEST_F(ValueTypeFloatTest_137, ToRational_137) {
    ValueType<float> v;
    v.read("0.5");
    Rational r = v.toRational(0);
    // The rational representation should approximate 0.5
    if (r.second != 0) {
        EXPECT_NEAR(static_cast<float>(r.first) / static_cast<float>(r.second), 0.5f, 0.001f);
    }
}

TEST_F(ValueTypeFloatTest_137, NegativeFloat_137) {
    ValueType<float> v;
    v.read("-2.5");
    EXPECT_NEAR(v.toFloat(0), -2.5f, 0.01f);
}

TEST_F(ValueTypeFloatTest_137, Clone_137) {
    ValueType<float> v;
    v.read("1.23");
    auto c = v.clone();
    EXPECT_EQ(c->count(), 1u);
    EXPECT_NEAR(c->toFloat(0), 1.23f, 0.01f);
}

// ============================================================
// Tests for ValueType<double>
// ============================================================

class ValueTypeDoubleTest_137 : public ::testing::Test {};

TEST_F(ValueTypeDoubleTest_137, DefaultConstructor_137) {
    ValueType<double> v;
    EXPECT_EQ(v.count(), 0u);
    EXPECT_EQ(v.typeId(), tiffDouble);
}

TEST_F(ValueTypeDoubleTest_137, ReadFromString_137) {
    ValueType<double> v;
    v.read("3.141592653589793");
    EXPECT_EQ(v.count(), 1u);
    EXPECT_NEAR(v.toFloat(0), 3.14159f, 0.001f);
}

TEST_F(ValueTypeDoubleTest_137, ToInt64_137) {
    ValueType<double> v;
    v.read("9.99");
    EXPECT_EQ(v.toInt64(0), 9);
}

TEST_F(ValueTypeDoubleTest_137, ToUint32_137) {
    ValueType<double> v;
    v.read("100.7");
    EXPECT_EQ(v.toUint32(0), 100u);
}

TEST_F(ValueTypeDoubleTest_137, ToRational_137) {
    ValueType<double> v;
    v.read("0.25");
    Rational r = v.toRational(0);
    if (r.second != 0) {
        EXPECT_NEAR(static_cast<double>(r.first) / static_cast<double>(r.second), 0.25, 0.001);
    }
}

// ============================================================
// Tests for ValueType<int32_t> (LongValue)
// ============================================================

class ValueTypeLongTest_137 : public ::testing::Test {};

TEST_F(ValueTypeLongTest_137, DefaultConstructor_137) {
    ValueType<int32_t> v;
    EXPECT_EQ(v.count(), 0u);
    EXPECT_EQ(v.typeId(), signedLong);
}

TEST_F(ValueTypeLongTest_137, ReadFromString_137) {
    ValueType<int32_t> v;
    v.read("-100 0 100");
    EXPECT_EQ(v.count(), 3u);
    EXPECT_EQ(v.toInt64(0), -100);
    EXPECT_EQ(v.toInt64(1), 0);
    EXPECT_EQ(v.toInt64(2), 100);
}

TEST_F(ValueTypeLongTest_137, ValueMemberAccess_137) {
    ValueType<int32_t> v;
    v.read("10 20 30");
    EXPECT_EQ(v.value_.size(), 3u);
    EXPECT_EQ(v.value_[0], 10);
    EXPECT_EQ(v.value_[1], 20);
    EXPECT_EQ(v.value_[2], 30);
}

// ============================================================
// Boundary and edge case tests
// ============================================================

class ValueTypeBoundaryTest_137 : public ::testing::Test {};

TEST_F(ValueTypeBoundaryTest_137, SingleElementRead_137) {
    ValueType<uint16_t> v;
    v.read("0");
    EXPECT_EQ(v.count(), 1u);
    EXPECT_EQ(v.toInt64(0), 0);
}

TEST_F(ValueTypeBoundaryTest_137, ReadEmptyBuffer_137) {
    ValueType<uint16_t> v;
    int result = v.read(nullptr, 0, littleEndian);
    EXPECT_EQ(v.count(), 0u);
    (void)result;
}

TEST_F(ValueTypeBoundaryTest_137, OutOfRangeAccess_137) {
    ValueType<uint16_t> v;
    v.read("42");
    // Accessing index beyond count -- may throw or return 0
    // Just ensure it doesn't crash for n=0
    EXPECT_EQ(v.toInt64(0), 42);
}

TEST_F(ValueTypeBoundaryTest_137, MultipleReads_137) {
    ValueType<uint16_t> v;
    v.read("1 2 3");
    EXPECT_EQ(v.count(), 3u);
    // Reading again should replace
    v.read("10 20");
    EXPECT_EQ(v.count(), 2u);
    EXPECT_EQ(v.toInt64(0), 10);
    EXPECT_EQ(v.toInt64(1), 20);
}

TEST_F(ValueTypeBoundaryTest_137, DataAreaSetAndGet_137) {
    ValueType<uint32_t> v;
    v.read("1");
    byte area[] = {0xDE, 0xAD, 0xBE, 0xEF};
    v.setDataArea(area, 4);
    EXPECT_EQ(v.sizeDataArea(), 4u);
    DataBuf buf = v.dataArea();
    EXPECT_EQ(buf.size(), 4u);
}

TEST_F(ValueTypeBoundaryTest_137, WriteMultipleValuesToStream_137) {
    ValueType<int32_t> v;
    v.read("1 2 3");
    std::ostringstream os;
    v.write(os);
    std::string output = os.str();
    // Output should contain all values
    EXPECT_NE(output.find("1"), std::string::npos);
    EXPECT_NE(output.find("2"), std::string::npos);
    EXPECT_NE(output.find("3"), std::string::npos);
}

TEST_F(ValueTypeBoundaryTest_137, ConstructFromBufferBigEndian_137) {
    // Big-endian uint16_t: 0x0100 = 256
    byte data[] = {0x01, 0x00};
    ValueType<uint16_t> v(data, sizeof(data), bigEndian, unsignedShort);
    EXPECT_EQ(v.count(), 1u);
    EXPECT_EQ(v.toInt64(0), 256);
}

TEST_F(ValueTypeBoundaryTest_137, ConstructFromBufferLittleEndian_137) {
    // Little-endian uint16_t: 0x00, 0x01 = 256
    byte data[] = {0x00, 0x01};
    ValueType<uint16_t> v(data, sizeof(data), littleEndian, unsignedShort);
    EXPECT_EQ(v.count(), 1u);
    EXPECT_EQ(v.toInt64(0), 256);
}

TEST_F(ValueTypeBoundaryTest_137, CopyByteOrderConsistency_137) {
    byte data[] = {0x01, 0x00, 0x02, 0x00};
    ValueType<uint16_t> v;
    v.read(data, sizeof(data), littleEndian);
    EXPECT_EQ(v.count(), 2u);

    byte outBuf[4];
    size_t s = v.copy(outBuf, littleEndian);
    EXPECT_EQ(s, 4u);
    EXPECT_EQ(std::memcmp(data, outBuf, 4), 0);
}

// ============================================================
// Tests for ValueType with value_ member direct access
// ============================================================

class ValueTypeDirectAccessTest_137 : public ::testing::Test {};

TEST_F(ValueTypeDirectAccessTest_137, ValueListDirectAccess_137) {
    ValueType<uint16_t> v;
    v.value_.push_back(10);
    v.value_.push_back(20);
    v.value_.push_back(30);
    EXPECT_EQ(v.count(), 3u);
    EXPECT_EQ(v.toInt64(0), 10);
    EXPECT_EQ(v.toInt64(1), 20);
    EXPECT_EQ(v.toInt64(2), 30);
}

TEST_F(ValueTypeDirectAccessTest_137, ValueListClearAndReread_137) {
    ValueType<uint16_t> v;
    v.read("1 2 3");
    EXPECT_EQ(v.count(), 3u);
    v.value_.clear();
    EXPECT_EQ(v.count(), 0u);
}

TEST_F(ValueTypeDirectAccessTest_137, RationalValueList_137) {
    ValueType<Rational> v;
    v.value_.push_back(Rational(1, 3));
    v.value_.push_back(Rational(2, 3));
    EXPECT_EQ(v.count(), 2u);
    EXPECT_FLOAT_EQ(v.toFloat(0), 1.0f / 3.0f);
    EXPECT_FLOAT_EQ(v.toFloat(1), 2.0f / 3.0f);
}
