#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <exiv2/types.hpp>
#include <sstream>
#include <cstring>

using namespace Exiv2;

// ============================================================
// Tests for ValueType<uint16_t> (UShortValue)
// ============================================================

class ValueTypeUShortTest_147 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(ValueTypeUShortTest_147, DefaultConstructor_147) {
    ValueType<uint16_t> v;
    EXPECT_EQ(v.count(), 0u);
    EXPECT_EQ(v.size(), 0u);
    EXPECT_EQ(v.typeId(), unsignedShort);
}

TEST_F(ValueTypeUShortTest_147, ConstructorWithValue_147) {
    ValueType<uint16_t> v(42, unsignedShort);
    EXPECT_EQ(v.count(), 1u);
    EXPECT_EQ(v.toInt64(0), 42);
}

TEST_F(ValueTypeUShortTest_147, CopyConstructor_147) {
    ValueType<uint16_t> v1(100, unsignedShort);
    ValueType<uint16_t> v2(v1);
    EXPECT_EQ(v2.count(), 1u);
    EXPECT_EQ(v2.toInt64(0), 100);
}

TEST_F(ValueTypeUShortTest_147, AssignmentOperator_147) {
    ValueType<uint16_t> v1(200, unsignedShort);
    ValueType<uint16_t> v2;
    v2 = v1;
    EXPECT_EQ(v2.count(), 1u);
    EXPECT_EQ(v2.toInt64(0), 200);
}

TEST_F(ValueTypeUShortTest_147, SelfAssignment_147) {
    ValueType<uint16_t> v(300, unsignedShort);
    v = v;
    EXPECT_EQ(v.count(), 1u);
    EXPECT_EQ(v.toInt64(0), 300);
}

TEST_F(ValueTypeUShortTest_147, ReadFromString_147) {
    ValueType<uint16_t> v;
    v.read("10 20 30");
    EXPECT_EQ(v.count(), 3u);
    EXPECT_EQ(v.toInt64(0), 10);
    EXPECT_EQ(v.toInt64(1), 20);
    EXPECT_EQ(v.toInt64(2), 30);
}

TEST_F(ValueTypeUShortTest_147, ReadFromBuffer_147) {
    uint16_t data[] = {1, 2, 3};
    // Write in little-endian
    byte buf[6];
    std::memcpy(buf, data, 6);
    ValueType<uint16_t> v;
    v.read(buf, 6, littleEndian);
    EXPECT_EQ(v.count(), 3u);
}

TEST_F(ValueTypeUShortTest_147, CopyToBuffer_147) {
    ValueType<uint16_t> v;
    v.read("100 200");
    byte buf[4];
    size_t copied = v.copy(buf, littleEndian);
    EXPECT_EQ(copied, 4u);
}

TEST_F(ValueTypeUShortTest_147, ToString_147) {
    ValueType<uint16_t> v(42, unsignedShort);
    std::string s = v.toString(0);
    EXPECT_EQ(s, "42");
}

TEST_F(ValueTypeUShortTest_147, ToFloat_147) {
    ValueType<uint16_t> v(55, unsignedShort);
    float f = v.toFloat(0);
    EXPECT_FLOAT_EQ(f, 55.0f);
}

TEST_F(ValueTypeUShortTest_147, ToRational_147) {
    ValueType<uint16_t> v(7, unsignedShort);
    Rational r = v.toRational(0);
    EXPECT_EQ(r.first, 7);
    EXPECT_EQ(r.second, 1);
}

TEST_F(ValueTypeUShortTest_147, ToUint32_147) {
    ValueType<uint16_t> v(999, unsignedShort);
    uint32_t u = v.toUint32(0);
    EXPECT_EQ(u, 999u);
}

TEST_F(ValueTypeUShortTest_147, WriteToStream_147) {
    ValueType<uint16_t> v;
    v.read("10 20 30");
    std::ostringstream os;
    v.write(os);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

TEST_F(ValueTypeUShortTest_147, SizeCalculation_147) {
    ValueType<uint16_t> v;
    v.read("1 2 3 4 5");
    EXPECT_EQ(v.count(), 5u);
    EXPECT_EQ(v.size(), 10u); // 5 * sizeof(uint16_t) = 10
}

TEST_F(ValueTypeUShortTest_147, EmptyCount_147) {
    ValueType<uint16_t> v;
    EXPECT_EQ(v.count(), 0u);
    EXPECT_EQ(v.size(), 0u);
}

TEST_F(ValueTypeUShortTest_147, Clone_147) {
    ValueType<uint16_t> v(42, unsignedShort);
    auto cloned = v.clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->count(), 1u);
    EXPECT_EQ(cloned->toInt64(0), 42);
}

// ============================================================
// Tests for ValueType<uint32_t> (ULongValue)
// ============================================================

class ValueTypeULongTest_147 : public ::testing::Test {};

TEST_F(ValueTypeULongTest_147, DefaultConstructor_147) {
    ValueType<uint32_t> v;
    EXPECT_EQ(v.count(), 0u);
    EXPECT_EQ(v.typeId(), unsignedLong);
}

TEST_F(ValueTypeULongTest_147, ConstructWithValue_147) {
    ValueType<uint32_t> v(123456, unsignedLong);
    EXPECT_EQ(v.count(), 1u);
    EXPECT_EQ(v.toInt64(0), 123456);
}

TEST_F(ValueTypeULongTest_147, ReadString_147) {
    ValueType<uint32_t> v;
    v.read("100 200 300");
    EXPECT_EQ(v.count(), 3u);
    EXPECT_EQ(v.toInt64(0), 100);
    EXPECT_EQ(v.toInt64(1), 200);
    EXPECT_EQ(v.toInt64(2), 300);
}

TEST_F(ValueTypeULongTest_147, Size_147) {
    ValueType<uint32_t> v;
    v.read("1 2 3");
    EXPECT_EQ(v.size(), 12u); // 3 * 4
}

TEST_F(ValueTypeULongTest_147, ToStringIndex_147) {
    ValueType<uint32_t> v;
    v.read("111 222");
    EXPECT_EQ(v.toString(0), "111");
    EXPECT_EQ(v.toString(1), "222");
}

// ============================================================
// Tests for ValueType<int16_t> (ShortValue)
// ============================================================

class ValueTypeShortTest_147 : public ::testing::Test {};

TEST_F(ValueTypeShortTest_147, NegativeValue_147) {
    ValueType<int16_t> v;
    v.read("-100 50");
    EXPECT_EQ(v.count(), 2u);
    EXPECT_EQ(v.toInt64(0), -100);
    EXPECT_EQ(v.toInt64(1), 50);
}

TEST_F(ValueTypeShortTest_147, ZeroValue_147) {
    ValueType<int16_t> v(0, signedShort);
    EXPECT_EQ(v.toInt64(0), 0);
}

// ============================================================
// Tests for ValueType<Rational>
// ============================================================

class ValueTypeRationalTest_147 : public ::testing::Test {};

TEST_F(ValueTypeRationalTest_147, DefaultConstructor_147) {
    ValueType<Rational> v;
    EXPECT_EQ(v.count(), 0u);
    EXPECT_EQ(v.typeId(), signedRational);
}

TEST_F(ValueTypeRationalTest_147, ReadFromString_147) {
    ValueType<Rational> v;
    v.read("1/2 3/4");
    EXPECT_EQ(v.count(), 2u);
}

TEST_F(ValueTypeRationalTest_147, ToFloat_147) {
    ValueType<Rational> v;
    v.read("1/2");
    EXPECT_FLOAT_EQ(v.toFloat(0), 0.5f);
}

TEST_F(ValueTypeRationalTest_147, ToInt64_147) {
    ValueType<Rational> v;
    v.read("10/2");
    EXPECT_EQ(v.toInt64(0), 5);
}

TEST_F(ValueTypeRationalTest_147, ToUint32_147) {
    ValueType<Rational> v;
    v.read("10/2");
    EXPECT_EQ(v.toUint32(0), 5u);
}

TEST_F(ValueTypeRationalTest_147, ToRational_147) {
    ValueType<Rational> v;
    v.read("3/7");
    Rational r = v.toRational(0);
    EXPECT_EQ(r.first, 3);
    EXPECT_EQ(r.second, 7);
}

TEST_F(ValueTypeRationalTest_147, ZeroDenominator_147) {
    ValueType<Rational> v;
    v.read("1/0");
    EXPECT_EQ(v.count(), 1u);
    // toFloat with zero denominator - should handle gracefully
    // Just verify it doesn't crash
    v.toFloat(0);
}

TEST_F(ValueTypeRationalTest_147, NegativeRational_147) {
    ValueType<Rational> v;
    v.read("-3/4");
    EXPECT_EQ(v.count(), 1u);
    Rational r = v.toRational(0);
    EXPECT_EQ(r.first, -3);
    EXPECT_EQ(r.second, 4);
}

// ============================================================
// Tests for ValueType<URational>
// ============================================================

class ValueTypeURationalTest_147 : public ::testing::Test {};

TEST_F(ValueTypeURationalTest_147, ReadFromString_147) {
    ValueType<URational> v;
    v.read("3/5 7/11");
    EXPECT_EQ(v.count(), 2u);
}

TEST_F(ValueTypeURationalTest_147, ToFloat_147) {
    ValueType<URational> v;
    v.read("1/4");
    EXPECT_FLOAT_EQ(v.toFloat(0), 0.25f);
}

TEST_F(ValueTypeURationalTest_147, ToInt64_147) {
    ValueType<URational> v;
    v.read("20/4");
    EXPECT_EQ(v.toInt64(0), 5);
}

TEST_F(ValueTypeURationalTest_147, ToUint32_147) {
    ValueType<URational> v;
    v.read("20/4");
    EXPECT_EQ(v.toUint32(0), 5u);
}

TEST_F(ValueTypeURationalTest_147, ToRational_147) {
    ValueType<URational> v;
    v.read("5/8");
    Rational r = v.toRational(0);
    EXPECT_EQ(r.first, 5);
    EXPECT_EQ(r.second, 8);
}

// ============================================================
// Tests for ValueType<float>
// ============================================================

class ValueTypeFloatTest_147 : public ::testing::Test {};

TEST_F(ValueTypeFloatTest_147, DefaultConstructor_147) {
    ValueType<float> v;
    EXPECT_EQ(v.count(), 0u);
    EXPECT_EQ(v.typeId(), tiffFloat);
}

TEST_F(ValueTypeFloatTest_147, ReadFromString_147) {
    ValueType<float> v;
    v.read("3.14");
    EXPECT_EQ(v.count(), 1u);
    EXPECT_NEAR(v.toFloat(0), 3.14f, 0.01f);
}

TEST_F(ValueTypeFloatTest_147, ToInt64_147) {
    ValueType<float> v;
    v.read("3.7");
    EXPECT_EQ(v.toInt64(0), 3);
}

TEST_F(ValueTypeFloatTest_147, ToUint32_147) {
    ValueType<float> v;
    v.read("3.7");
    EXPECT_EQ(v.toUint32(0), 3u);
}

TEST_F(ValueTypeFloatTest_147, ToRational_147) {
    ValueType<float> v;
    v.read("0.5");
    Rational r = v.toRational(0);
    // Should be some rational approximation of 0.5
    if (r.second != 0) {
        EXPECT_NEAR(static_cast<float>(r.first) / r.second, 0.5f, 0.001f);
    }
}

// ============================================================
// Tests for ValueType<double>
// ============================================================

class ValueTypeDoubleTest_147 : public ::testing::Test {};

TEST_F(ValueTypeDoubleTest_147, DefaultConstructor_147) {
    ValueType<double> v;
    EXPECT_EQ(v.count(), 0u);
    EXPECT_EQ(v.typeId(), tiffDouble);
}

TEST_F(ValueTypeDoubleTest_147, ReadFromString_147) {
    ValueType<double> v;
    v.read("2.718281828");
    EXPECT_EQ(v.count(), 1u);
    EXPECT_NEAR(v.toFloat(0), 2.718281828f, 0.0001f);
}

TEST_F(ValueTypeDoubleTest_147, ToInt64_147) {
    ValueType<double> v;
    v.read("9.99");
    EXPECT_EQ(v.toInt64(0), 9);
}

TEST_F(ValueTypeDoubleTest_147, ToUint32_147) {
    ValueType<double> v;
    v.read("9.99");
    EXPECT_EQ(v.toUint32(0), 9u);
}

TEST_F(ValueTypeDoubleTest_147, ToRational_147) {
    ValueType<double> v;
    v.read("0.25");
    Rational r = v.toRational(0);
    if (r.second != 0) {
        EXPECT_NEAR(static_cast<double>(r.first) / r.second, 0.25, 0.001);
    }
}

// ============================================================
// Tests for DataArea functionality
// ============================================================

class ValueTypeDataAreaTest_147 : public ::testing::Test {};

TEST_F(ValueTypeDataAreaTest_147, NoDataAreaByDefault_147) {
    ValueType<uint16_t> v(42, unsignedShort);
    EXPECT_EQ(v.sizeDataArea(), 0u);
}

TEST_F(ValueTypeDataAreaTest_147, SetDataArea_147) {
    ValueType<uint16_t> v(42, unsignedShort);
    byte data[] = {1, 2, 3, 4, 5};
    v.setDataArea(data, 5);
    EXPECT_EQ(v.sizeDataArea(), 5u);
    DataBuf buf = v.dataArea();
    EXPECT_EQ(buf.size(), 5u);
}

TEST_F(ValueTypeDataAreaTest_147, AssignmentCopiesDataArea_147) {
    ValueType<uint16_t> v1(42, unsignedShort);
    byte data[] = {10, 20, 30};
    v1.setDataArea(data, 3);

    ValueType<uint16_t> v2;
    v2 = v1;
    EXPECT_EQ(v2.sizeDataArea(), 3u);
    EXPECT_EQ(v2.toInt64(0), 42);
}

TEST_F(ValueTypeDataAreaTest_147, CopyConstructorCopiesDataArea_147) {
    ValueType<uint16_t> v1(42, unsignedShort);
    byte data[] = {10, 20, 30};
    v1.setDataArea(data, 3);

    ValueType<uint16_t> v2(v1);
    EXPECT_EQ(v2.sizeDataArea(), 3u);
}

TEST_F(ValueTypeDataAreaTest_147, AssignmentClearsDataAreaWhenSourceHasNone_147) {
    ValueType<uint16_t> v1(42, unsignedShort);
    byte data[] = {10, 20, 30};
    v1.setDataArea(data, 3);

    ValueType<uint16_t> v2(99, unsignedShort);
    // v2 has no data area
    v1 = v2;
    EXPECT_EQ(v1.sizeDataArea(), 0u);
    EXPECT_EQ(v1.toInt64(0), 99);
}

// ============================================================
// Tests for ValueType<int32_t> (LongValue)
// ============================================================

class ValueTypeLongTest_147 : public ::testing::Test {};

TEST_F(ValueTypeLongTest_147, NegativeValues_147) {
    ValueType<int32_t> v;
    v.read("-1000 500 -999");
    EXPECT_EQ(v.count(), 3u);
    EXPECT_EQ(v.toInt64(0), -1000);
    EXPECT_EQ(v.toInt64(1), 500);
    EXPECT_EQ(v.toInt64(2), -999);
}

TEST_F(ValueTypeLongTest_147, Size_147) {
    ValueType<int32_t> v;
    v.read("1 2");
    EXPECT_EQ(v.size(), 8u); // 2 * 4
}

// ============================================================
// Tests for boundary / error conditions
// ============================================================

class ValueTypeBoundaryTest_147 : public ::testing::Test {};

TEST_F(ValueTypeBoundaryTest_147, ToStringOutOfRange_147) {
    ValueType<uint16_t> v;
    v.read("10 20");
    // Index within range
    EXPECT_EQ(v.toString(0), "10");
    EXPECT_EQ(v.toString(1), "20");
    // Out of range index - just verify no crash, behavior is implementation-defined
    // Some implementations throw, some return empty
    try {
        v.toString(5);
    } catch (...) {
        // Expected for out-of-range
    }
}

TEST_F(ValueTypeBoundaryTest_147, ToInt64OutOfRange_147) {
    ValueType<uint16_t> v;
    v.read("10");
    // Valid
    EXPECT_EQ(v.toInt64(0), 10);
    // Out of range
    try {
        v.toInt64(5);
    } catch (...) {
        // Expected
    }
}

TEST_F(ValueTypeBoundaryTest_147, ReadEmptyString_147) {
    ValueType<uint16_t> v;
    v.read("");
    // Might result in 0 count or implementation-specific behavior
    // Just ensure no crash
}

TEST_F(ValueTypeBoundaryTest_147, SingleElementAccess_147) {
    ValueType<uint16_t> v(65535, unsignedShort);
    EXPECT_EQ(v.toInt64(0), 65535);
    EXPECT_EQ(v.toUint32(0), 65535u);
    EXPECT_FLOAT_EQ(v.toFloat(0), 65535.0f);
}

TEST_F(ValueTypeBoundaryTest_147, MultipleReads_147) {
    ValueType<uint16_t> v;
    v.read("1 2 3");
    EXPECT_EQ(v.count(), 3u);
    v.read("10 20");
    // After second read, count should reflect new data
    // Implementation may append or replace - check count
    size_t c = v.count();
    EXPECT_GE(c, 2u);
}

TEST_F(ValueTypeBoundaryTest_147, CopyToBufferAndReadBack_147) {
    ValueType<uint16_t> v;
    v.read("100 200 300");
    
    byte buf[6];
    size_t copied = v.copy(buf, littleEndian);
    EXPECT_EQ(copied, 6u);
    
    ValueType<uint16_t> v2;
    v2.read(buf, 6, littleEndian);
    EXPECT_EQ(v2.count(), 3u);
    EXPECT_EQ(v2.toInt64(0), v.toInt64(0));
    EXPECT_EQ(v2.toInt64(1), v.toInt64(1));
    EXPECT_EQ(v2.toInt64(2), v.toInt64(2));
}

TEST_F(ValueTypeBoundaryTest_147, WriteToStream_147) {
    ValueType<uint32_t> v;
    v.read("42");
    std::ostringstream os;
    v.write(os);
    EXPECT_EQ(os.str(), "42");
}

TEST_F(ValueTypeBoundaryTest_147, WriteMultipleToStream_147) {
    ValueType<uint32_t> v;
    v.read("1 2 3");
    std::ostringstream os;
    v.write(os);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
    // Should contain all values
    EXPECT_NE(result.find("1"), std::string::npos);
    EXPECT_NE(result.find("2"), std::string::npos);
    EXPECT_NE(result.find("3"), std::string::npos);
}

// ============================================================
// Test ValueType value_ direct access
// ============================================================

class ValueTypeDirectAccessTest_147 : public ::testing::Test {};

TEST_F(ValueTypeDirectAccessTest_147, ValueListAccess_147) {
    ValueType<uint16_t> v;
    v.read("10 20 30");
    EXPECT_EQ(v.value_.size(), 3u);
    EXPECT_EQ(v.value_[0], 10);
    EXPECT_EQ(v.value_[1], 20);
    EXPECT_EQ(v.value_[2], 30);
}

TEST_F(ValueTypeDirectAccessTest_147, ModifyValueList_147) {
    ValueType<uint16_t> v;
    v.read("10 20 30");
    v.value_.push_back(40);
    EXPECT_EQ(v.count(), 4u);
    EXPECT_EQ(v.toInt64(3), 40);
}

// ============================================================
// Tests for byte order handling
// ============================================================

class ValueTypeByteOrderTest_147 : public ::testing::Test {};

TEST_F(ValueTypeByteOrderTest_147, LittleEndianReadWrite_147) {
    ValueType<uint32_t> v;
    v.read("0x01020304");
    
    byte buf[4];
    v.copy(buf, littleEndian);
    
    ValueType<uint32_t> v2;
    v2.read(buf, 4, littleEndian);
    EXPECT_EQ(v.toInt64(0), v2.toInt64(0));
}

TEST_F(ValueTypeByteOrderTest_147, BigEndianReadWrite_147) {
    ValueType<uint32_t> v;
    v.read("256");
    
    byte buf[4];
    v.copy(buf, bigEndian);
    
    ValueType<uint32_t> v2;
    v2.read(buf, 4, bigEndian);
    EXPECT_EQ(v.toInt64(0), v2.toInt64(0));
}
