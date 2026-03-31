#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <sstream>
#include <cstring>

using namespace Exiv2;

// Test fixture for ValueType tests
class ValueTypeTest_2156 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== Default Constructor Tests ====================

TEST_F(ValueTypeTest_2156, DefaultConstructorUint16_2156) {
    ValueType<uint16_t> v;
    EXPECT_EQ(v.typeId(), getType<uint16_t>());
    EXPECT_EQ(v.count(), 0u);
    EXPECT_EQ(v.size(), 0u);
}

TEST_F(ValueTypeTest_2156, DefaultConstructorUint32_2156) {
    ValueType<uint32_t> v;
    EXPECT_EQ(v.typeId(), getType<uint32_t>());
    EXPECT_EQ(v.count(), 0u);
}

TEST_F(ValueTypeTest_2156, DefaultConstructorInt16_2156) {
    ValueType<int16_t> v;
    EXPECT_EQ(v.typeId(), getType<int16_t>());
    EXPECT_EQ(v.count(), 0u);
}

TEST_F(ValueTypeTest_2156, DefaultConstructorRational_2156) {
    ValueType<Rational> v;
    EXPECT_EQ(v.typeId(), getType<Rational>());
    EXPECT_EQ(v.count(), 0u);
}

TEST_F(ValueTypeTest_2156, DefaultConstructorURational_2156) {
    ValueType<URational> v;
    EXPECT_EQ(v.typeId(), getType<URational>());
    EXPECT_EQ(v.count(), 0u);
}

TEST_F(ValueTypeTest_2156, DefaultConstructorFloat_2156) {
    ValueType<float> v;
    EXPECT_EQ(v.typeId(), getType<float>());
    EXPECT_EQ(v.count(), 0u);
}

TEST_F(ValueTypeTest_2156, DefaultConstructorDouble_2156) {
    ValueType<double> v;
    EXPECT_EQ(v.typeId(), getType<double>());
    EXPECT_EQ(v.count(), 0u);
}

// ==================== Value Constructor Tests ====================

TEST_F(ValueTypeTest_2156, ValueConstructorUint16_2156) {
    uint16_t val = 42;
    ValueType<uint16_t> v(val, getType<uint16_t>());
    EXPECT_EQ(v.count(), 1u);
    EXPECT_EQ(v.toInt64(0), 42);
}

TEST_F(ValueTypeTest_2156, ValueConstructorInt32_2156) {
    int32_t val = -100;
    ValueType<int32_t> v(val, getType<int32_t>());
    EXPECT_EQ(v.count(), 1u);
    EXPECT_EQ(v.toInt64(0), -100);
}

TEST_F(ValueTypeTest_2156, ValueConstructorRational_2156) {
    Rational val(3, 4);
    ValueType<Rational> v(val, getType<Rational>());
    EXPECT_EQ(v.count(), 1u);
    Rational r = v.toRational(0);
    EXPECT_EQ(r.first, 3);
    EXPECT_EQ(r.second, 4);
}

TEST_F(ValueTypeTest_2156, ValueConstructorFloat_2156) {
    float val = 3.14f;
    ValueType<float> v(val, getType<float>());
    EXPECT_EQ(v.count(), 1u);
    EXPECT_FLOAT_EQ(v.toFloat(0), 3.14f);
}

// ==================== Copy Constructor Tests ====================

TEST_F(ValueTypeTest_2156, CopyConstructorUint16_2156) {
    ValueType<uint16_t> v1;
    v1.value_.push_back(10);
    v1.value_.push_back(20);
    ValueType<uint16_t> v2(v1);
    EXPECT_EQ(v2.count(), 2u);
    EXPECT_EQ(v2.toInt64(0), 10);
    EXPECT_EQ(v2.toInt64(1), 20);
    EXPECT_EQ(v2.typeId(), v1.typeId());
}

TEST_F(ValueTypeTest_2156, CopyConstructorPreservesDataArea_2156) {
    ValueType<uint16_t> v1;
    v1.value_.push_back(5);
    const byte data[] = {0x01, 0x02, 0x03, 0x04};
    v1.setDataArea(data, sizeof(data));
    ValueType<uint16_t> v2(v1);
    EXPECT_EQ(v2.sizeDataArea(), sizeof(data));
    DataBuf buf = v2.dataArea();
    EXPECT_EQ(buf.size(), sizeof(data));
}

TEST_F(ValueTypeTest_2156, CopyConstructorEmptyValue_2156) {
    ValueType<uint32_t> v1;
    ValueType<uint32_t> v2(v1);
    EXPECT_EQ(v2.count(), 0u);
    EXPECT_EQ(v2.size(), 0u);
}

// ==================== Assignment Operator Tests ====================

TEST_F(ValueTypeTest_2156, AssignmentOperator_2156) {
    ValueType<uint16_t> v1;
    v1.value_.push_back(100);
    v1.value_.push_back(200);
    ValueType<uint16_t> v2;
    v2 = v1;
    EXPECT_EQ(v2.count(), 2u);
    EXPECT_EQ(v2.toInt64(0), 100);
    EXPECT_EQ(v2.toInt64(1), 200);
}

TEST_F(ValueTypeTest_2156, AssignmentOperatorWithDataArea_2156) {
    ValueType<uint16_t> v1;
    v1.value_.push_back(5);
    const byte data[] = {0xAA, 0xBB};
    v1.setDataArea(data, sizeof(data));
    ValueType<uint16_t> v2;
    v2 = v1;
    EXPECT_EQ(v2.sizeDataArea(), sizeof(data));
}

TEST_F(ValueTypeTest_2156, SelfAssignment_2156) {
    ValueType<uint16_t> v;
    v.value_.push_back(42);
    v = v;
    EXPECT_EQ(v.count(), 1u);
    EXPECT_EQ(v.toInt64(0), 42);
}

// ==================== Read from buffer Tests ====================

TEST_F(ValueTypeTest_2156, ReadUint16FromBuffer_2156) {
    ValueType<uint16_t> v;
    byte buf[] = {0x00, 0x0A, 0x00, 0x14}; // 10, 20 in big endian
    int result = v.read(buf, sizeof(buf), bigEndian);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(v.count(), 2u);
    EXPECT_EQ(v.toInt64(0), 10);
    EXPECT_EQ(v.toInt64(1), 20);
}

TEST_F(ValueTypeTest_2156, ReadUint16LittleEndian_2156) {
    ValueType<uint16_t> v;
    byte buf[] = {0x0A, 0x00, 0x14, 0x00}; // 10, 20 in little endian
    int result = v.read(buf, sizeof(buf), littleEndian);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(v.count(), 2u);
    EXPECT_EQ(v.toInt64(0), 10);
    EXPECT_EQ(v.toInt64(1), 20);
}

TEST_F(ValueTypeTest_2156, ReadUint32FromBuffer_2156) {
    ValueType<uint32_t> v;
    byte buf[] = {0x00, 0x00, 0x00, 0x01}; // 1 in big endian
    int result = v.read(buf, sizeof(buf), bigEndian);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(v.count(), 1u);
    EXPECT_EQ(v.toInt64(0), 1);
}

// ==================== Read from string Tests ====================

TEST_F(ValueTypeTest_2156, ReadUint16FromString_2156) {
    ValueType<uint16_t> v;
    int result = v.read("10 20 30");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(v.count(), 3u);
    EXPECT_EQ(v.toInt64(0), 10);
    EXPECT_EQ(v.toInt64(1), 20);
    EXPECT_EQ(v.toInt64(2), 30);
}

TEST_F(ValueTypeTest_2156, ReadInt32FromString_2156) {
    ValueType<int32_t> v;
    int result = v.read("-5 0 100");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(v.count(), 3u);
    EXPECT_EQ(v.toInt64(0), -5);
    EXPECT_EQ(v.toInt64(1), 0);
    EXPECT_EQ(v.toInt64(2), 100);
}

TEST_F(ValueTypeTest_2156, ReadRationalFromString_2156) {
    ValueType<Rational> v;
    int result = v.read("3/4");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(v.count(), 1u);
    Rational r = v.toRational(0);
    EXPECT_EQ(r.first, 3);
    EXPECT_EQ(r.second, 4);
}

TEST_F(ValueTypeTest_2156, ReadURationalFromString_2156) {
    ValueType<URational> v;
    int result = v.read("1/2");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(v.count(), 1u);
}

TEST_F(ValueTypeTest_2156, ReadSingleValue_2156) {
    ValueType<uint16_t> v;
    int result = v.read("42");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(v.count(), 1u);
    EXPECT_EQ(v.toInt64(0), 42);
}

// ==================== Count Tests ====================

TEST_F(ValueTypeTest_2156, CountEmptyValue_2156) {
    ValueType<uint16_t> v;
    EXPECT_EQ(v.count(), 0u);
}

TEST_F(ValueTypeTest_2156, CountAfterPushBack_2156) {
    ValueType<uint16_t> v;
    v.value_.push_back(1);
    EXPECT_EQ(v.count(), 1u);
    v.value_.push_back(2);
    EXPECT_EQ(v.count(), 2u);
    v.value_.push_back(3);
    EXPECT_EQ(v.count(), 3u);
}

// ==================== Size Tests ====================

TEST_F(ValueTypeTest_2156, SizeUint16_2156) {
    ValueType<uint16_t> v;
    v.value_.push_back(1);
    v.value_.push_back(2);
    EXPECT_EQ(v.size(), 2u * sizeof(uint16_t));
}

TEST_F(ValueTypeTest_2156, SizeUint32_2156) {
    ValueType<uint32_t> v;
    v.value_.push_back(1);
    EXPECT_EQ(v.size(), sizeof(uint32_t));
}

TEST_F(ValueTypeTest_2156, SizeRational_2156) {
    ValueType<Rational> v;
    v.value_.push_back(Rational(1, 2));
    // Rational is pair of int32_t, so 8 bytes
    EXPECT_EQ(v.size(), 8u);
}

TEST_F(ValueTypeTest_2156, SizeEmpty_2156) {
    ValueType<uint16_t> v;
    EXPECT_EQ(v.size(), 0u);
}

// ==================== Copy to buffer Tests ====================

TEST_F(ValueTypeTest_2156, CopyUint16BigEndian_2156) {
    ValueType<uint16_t> v;
    v.value_.push_back(10);
    byte buf[2] = {0};
    size_t copied = v.copy(buf, bigEndian);
    EXPECT_EQ(copied, 2u);
    EXPECT_EQ(buf[0], 0x00);
    EXPECT_EQ(buf[1], 0x0A);
}

TEST_F(ValueTypeTest_2156, CopyUint16LittleEndian_2156) {
    ValueType<uint16_t> v;
    v.value_.push_back(10);
    byte buf[2] = {0};
    size_t copied = v.copy(buf, littleEndian);
    EXPECT_EQ(copied, 2u);
    EXPECT_EQ(buf[0], 0x0A);
    EXPECT_EQ(buf[1], 0x00);
}

TEST_F(ValueTypeTest_2156, CopyMultipleValues_2156) {
    ValueType<uint16_t> v;
    v.value_.push_back(1);
    v.value_.push_back(2);
    byte buf[4] = {0};
    size_t copied = v.copy(buf, bigEndian);
    EXPECT_EQ(copied, 4u);
}

// ==================== Write to stream Tests ====================

TEST_F(ValueTypeTest_2156, WriteUint16ToStream_2156) {
    ValueType<uint16_t> v;
    v.value_.push_back(42);
    std::ostringstream os;
    v.write(os);
    EXPECT_FALSE(os.str().empty());
    EXPECT_NE(os.str().find("42"), std::string::npos);
}

TEST_F(ValueTypeTest_2156, WriteMultipleValuesToStream_2156) {
    ValueType<uint16_t> v;
    v.value_.push_back(10);
    v.value_.push_back(20);
    std::ostringstream os;
    v.write(os);
    std::string result = os.str();
    EXPECT_NE(result.find("10"), std::string::npos);
    EXPECT_NE(result.find("20"), std::string::npos);
}

// ==================== ToString Tests ====================

TEST_F(ValueTypeTest_2156, ToStringUint16_2156) {
    ValueType<uint16_t> v;
    v.value_.push_back(42);
    std::string s = v.toString(0);
    EXPECT_EQ(s, "42");
}

TEST_F(ValueTypeTest_2156, ToStringInt32Negative_2156) {
    ValueType<int32_t> v;
    v.value_.push_back(-10);
    std::string s = v.toString(0);
    EXPECT_EQ(s, "-10");
}

TEST_F(ValueTypeTest_2156, ToStringRational_2156) {
    ValueType<Rational> v;
    v.value_.push_back(Rational(3, 4));
    std::string s = v.toString(0);
    EXPECT_NE(s.find("3"), std::string::npos);
    EXPECT_NE(s.find("4"), std::string::npos);
}

// ==================== toInt64 Tests ====================

TEST_F(ValueTypeTest_2156, ToInt64Uint16_2156) {
    ValueType<uint16_t> v;
    v.value_.push_back(65535);
    EXPECT_EQ(v.toInt64(0), 65535);
}

TEST_F(ValueTypeTest_2156, ToInt64Int32_2156) {
    ValueType<int32_t> v;
    v.value_.push_back(-1000);
    EXPECT_EQ(v.toInt64(0), -1000);
}

TEST_F(ValueTypeTest_2156, ToInt64Float_2156) {
    ValueType<float> v;
    v.value_.push_back(3.7f);
    int64_t result = v.toInt64(0);
    // Float to int truncation
    EXPECT_EQ(result, 3);
}

TEST_F(ValueTypeTest_2156, ToInt64Double_2156) {
    ValueType<double> v;
    v.value_.push_back(9.9);
    int64_t result = v.toInt64(0);
    EXPECT_EQ(result, 9);
}

TEST_F(ValueTypeTest_2156, ToInt64Rational_2156) {
    ValueType<Rational> v;
    v.value_.push_back(Rational(7, 2));
    int64_t result = v.toInt64(0);
    EXPECT_EQ(result, 3); // 7/2 = 3.5, truncated to 3
}

TEST_F(ValueTypeTest_2156, ToInt64URational_2156) {
    ValueType<URational> v;
    v.value_.push_back(URational(10, 3));
    int64_t result = v.toInt64(0);
    EXPECT_EQ(result, 3); // 10/3 = 3.33, truncated to 3
}

// ==================== toUint32 Tests ====================

TEST_F(ValueTypeTest_2156, ToUint32Uint16_2156) {
    ValueType<uint16_t> v;
    v.value_.push_back(1000);
    EXPECT_EQ(v.toUint32(0), 1000u);
}

TEST_F(ValueTypeTest_2156, ToUint32Float_2156) {
    ValueType<float> v;
    v.value_.push_back(5.9f);
    uint32_t result = v.toUint32(0);
    EXPECT_EQ(result, 5u);
}

TEST_F(ValueTypeTest_2156, ToUint32Double_2156) {
    ValueType<double> v;
    v.value_.push_back(100.1);
    uint32_t result = v.toUint32(0);
    EXPECT_EQ(result, 100u);
}

TEST_F(ValueTypeTest_2156, ToUint32Rational_2156) {
    ValueType<Rational> v;
    v.value_.push_back(Rational(10, 3));
    uint32_t result = v.toUint32(0);
    EXPECT_EQ(result, 3u);
}

TEST_F(ValueTypeTest_2156, ToUint32URational_2156) {
    ValueType<URational> v;
    v.value_.push_back(URational(8, 3));
    uint32_t result = v.toUint32(0);
    EXPECT_EQ(result, 2u);
}

// ==================== toFloat Tests ====================

TEST_F(ValueTypeTest_2156, ToFloatUint16_2156) {
    ValueType<uint16_t> v;
    v.value_.push_back(42);
    EXPECT_FLOAT_EQ(v.toFloat(0), 42.0f);
}

TEST_F(ValueTypeTest_2156, ToFloatRational_2156) {
    ValueType<Rational> v;
    v.value_.push_back(Rational(1, 2));
    EXPECT_FLOAT_EQ(v.toFloat(0), 0.5f);
}

TEST_F(ValueTypeTest_2156, ToFloatURational_2156) {
    ValueType<URational> v;
    v.value_.push_back(URational(3, 4));
    EXPECT_FLOAT_EQ(v.toFloat(0), 0.75f);
}

TEST_F(ValueTypeTest_2156, ToFloatFloat_2156) {
    ValueType<float> v;
    v.value_.push_back(3.14f);
    EXPECT_FLOAT_EQ(v.toFloat(0), 3.14f);
}

TEST_F(ValueTypeTest_2156, ToFloatDouble_2156) {
    ValueType<double> v;
    v.value_.push_back(2.718);
    EXPECT_NEAR(v.toFloat(0), 2.718f, 0.001f);
}

// ==================== toRational Tests ====================

TEST_F(ValueTypeTest_2156, ToRationalUint16_2156) {
    ValueType<uint16_t> v;
    v.value_.push_back(5);
    Rational r = v.toRational(0);
    EXPECT_EQ(r.first, 5);
    EXPECT_EQ(r.second, 1);
}

TEST_F(ValueTypeTest_2156, ToRationalRational_2156) {
    ValueType<Rational> v;
    v.value_.push_back(Rational(3, 7));
    Rational r = v.toRational(0);
    EXPECT_EQ(r.first, 3);
    EXPECT_EQ(r.second, 7);
}

TEST_F(ValueTypeTest_2156, ToRationalURational_2156) {
    ValueType<URational> v;
    v.value_.push_back(URational(5, 8));
    Rational r = v.toRational(0);
    EXPECT_EQ(r.first, 5);
    EXPECT_EQ(r.second, 8);
}

TEST_F(ValueTypeTest_2156, ToRationalFloat_2156) {
    ValueType<float> v;
    v.value_.push_back(0.5f);
    Rational r = v.toRational(0);
    // Should represent 0.5 as a rational
    EXPECT_NE(r.second, 0);
    float result = static_cast<float>(r.first) / static_cast<float>(r.second);
    EXPECT_NEAR(result, 0.5f, 0.001f);
}

TEST_F(ValueTypeTest_2156, ToRationalDouble_2156) {
    ValueType<double> v;
    v.value_.push_back(0.25);
    Rational r = v.toRational(0);
    EXPECT_NE(r.second, 0);
    double result = static_cast<double>(r.first) / static_cast<double>(r.second);
    EXPECT_NEAR(result, 0.25, 0.001);
}

// ==================== DataArea Tests ====================

TEST_F(ValueTypeTest_2156, SetDataArea_2156) {
    ValueType<uint16_t> v;
    const byte data[] = {0x01, 0x02, 0x03};
    int result = v.setDataArea(data, sizeof(data));
    EXPECT_EQ(result, 0);
    EXPECT_EQ(v.sizeDataArea(), sizeof(data));
}

TEST_F(ValueTypeTest_2156, DataAreaRetrieval_2156) {
    ValueType<uint16_t> v;
    const byte data[] = {0xAA, 0xBB, 0xCC, 0xDD};
    v.setDataArea(data, sizeof(data));
    DataBuf buf = v.dataArea();
    EXPECT_EQ(buf.size(), sizeof(data));
}

TEST_F(ValueTypeTest_2156, EmptyDataArea_2156) {
    ValueType<uint16_t> v;
    EXPECT_EQ(v.sizeDataArea(), 0u);
    DataBuf buf = v.dataArea();
    EXPECT_EQ(buf.size(), 0u);
}

TEST_F(ValueTypeTest_2156, SetDataAreaOverwrite_2156) {
    ValueType<uint16_t> v;
    const byte data1[] = {0x01, 0x02};
    v.setDataArea(data1, sizeof(data1));
    EXPECT_EQ(v.sizeDataArea(), 2u);

    const byte data2[] = {0x03, 0x04, 0x05};
    v.setDataArea(data2, sizeof(data2));
    EXPECT_EQ(v.sizeDataArea(), 3u);
}

// ==================== Clone Tests ====================

TEST_F(ValueTypeTest_2156, CloneUint16_2156) {
    ValueType<uint16_t> v;
    v.value_.push_back(42);
    v.value_.push_back(84);
    auto cloned = v.clone();
    EXPECT_NE(cloned.get(), nullptr);
    EXPECT_EQ(cloned->typeId(), v.typeId());
    EXPECT_EQ(cloned->count(), 2u);
    EXPECT_EQ(cloned->toInt64(0), 42);
    EXPECT_EQ(cloned->toInt64(1), 84);
}

TEST_F(ValueTypeTest_2156, CloneRational_2156) {
    ValueType<Rational> v;
    v.value_.push_back(Rational(1, 3));
    auto cloned = v.clone();
    EXPECT_EQ(cloned->count(), 1u);
    EXPECT_FLOAT_EQ(cloned->toFloat(0), 1.0f / 3.0f);
}

// ==================== Multiple Values Tests ====================

TEST_F(ValueTypeTest_2156, MultipleValuesAccessByIndex_2156) {
    ValueType<uint16_t> v;
    v.value_.push_back(10);
    v.value_.push_back(20);
    v.value_.push_back(30);
    EXPECT_EQ(v.toInt64(0), 10);
    EXPECT_EQ(v.toInt64(1), 20);
    EXPECT_EQ(v.toInt64(2), 30);
    EXPECT_EQ(v.count(), 3u);
}

// ==================== Boundary Tests ====================

TEST_F(ValueTypeTest_2156, Uint16MaxValue_2156) {
    ValueType<uint16_t> v;
    v.value_.push_back(65535);
    EXPECT_EQ(v.toInt64(0), 65535);
    EXPECT_EQ(v.toUint32(0), 65535u);
}

TEST_F(ValueTypeTest_2156, Uint16ZeroValue_2156) {
    ValueType<uint16_t> v;
    v.value_.push_back(0);
    EXPECT_EQ(v.toInt64(0), 0);
}

TEST_F(ValueTypeTest_2156, Int32MinValue_2156) {
    ValueType<int32_t> v;
    v.value_.push_back(std::numeric_limits<int32_t>::min());
    EXPECT_EQ(v.toInt64(0), std::numeric_limits<int32_t>::min());
}

TEST_F(ValueTypeTest_2156, Int32MaxValue_2156) {
    ValueType<int32_t> v;
    v.value_.push_back(std::numeric_limits<int32_t>::max());
    EXPECT_EQ(v.toInt64(0), std::numeric_limits<int32_t>::max());
}

TEST_F(ValueTypeTest_2156, RationalZeroDenominator_2156) {
    ValueType<Rational> v;
    v.value_.push_back(Rational(1, 0));
    // Behavior is implementation-defined, but it should not crash
    // Just check that toFloat handles it
    float result = v.toFloat(0);
    // Don't assert specific value since division by zero behavior varies
    (void)result;
}

TEST_F(ValueTypeTest_2156, URationalZeroDenominator_2156) {
    ValueType<URational> v;
    v.value_.push_back(URational(1, 0));
    float result = v.toFloat(0);
    (void)result;
}

// ==================== Read Overwrite Tests ====================

TEST_F(ValueTypeTest_2156, ReadOverwritesPreviousValues_2156) {
    ValueType<uint16_t> v;
    v.read("10 20 30");
    EXPECT_EQ(v.count(), 3u);

    v.read("40 50");
    EXPECT_EQ(v.count(), 2u);
    EXPECT_EQ(v.toInt64(0), 40);
    EXPECT_EQ(v.toInt64(1), 50);
}

// ==================== Buffer Constructor Tests ====================

TEST_F(ValueTypeTest_2156, BufferConstructorUint16_2156) {
    byte buf[] = {0x00, 0x0A}; // 10 in big endian
    ValueType<uint16_t> v(buf, sizeof(buf), bigEndian, getType<uint16_t>());
    EXPECT_EQ(v.count(), 1u);
    EXPECT_EQ(v.toInt64(0), 10);
}

TEST_F(ValueTypeTest_2156, BufferConstructorUint32_2156) {
    byte buf[] = {0x00, 0x00, 0x01, 0x00}; // 256 in big endian
    ValueType<uint32_t> v(buf, sizeof(buf), bigEndian, getType<uint32_t>());
    EXPECT_EQ(v.count(), 1u);
    EXPECT_EQ(v.toInt64(0), 256);
}

// ==================== Value::create Tests ====================

TEST_F(ValueTypeTest_2156, CreateUint16Value_2156) {
    auto v = Value::create(unsignedShort);
    EXPECT_NE(v.get(), nullptr);
    EXPECT_EQ(v->typeId(), unsignedShort);
}

TEST_F(ValueTypeTest_2156, CreateUint32Value_2156) {
    auto v = Value::create(unsignedLong);
    EXPECT_NE(v.get(), nullptr);
    EXPECT_EQ(v->typeId(), unsignedLong);
}

TEST_F(ValueTypeTest_2156, CreateRationalValue_2156) {
    auto v = Value::create(signedRational);
    EXPECT_NE(v.get(), nullptr);
    EXPECT_EQ(v->typeId(), signedRational);
}

// ==================== Direct value_ access Tests ====================

TEST_F(ValueTypeTest_2156, DirectValueAccess_2156) {
    ValueType<uint16_t> v;
    v.value_.push_back(100);
    v.value_.push_back(200);
    v.value_.push_back(300);
    EXPECT_EQ(v.value_.size(), 3u);
    EXPECT_EQ(v.value_[0], 100);
    EXPECT_EQ(v.value_[1], 200);
    EXPECT_EQ(v.value_[2], 300);
}

// ==================== ok() Tests ====================

TEST_F(ValueTypeTest_2156, OkAfterConstruction_2156) {
    ValueType<uint16_t> v;
    EXPECT_TRUE(v.ok());
}

TEST_F(ValueTypeTest_2156, OkAfterRead_2156) {
    ValueType<uint16_t> v;
    v.read("10 20");
    EXPECT_TRUE(v.ok());
}

// ==================== TypeId Tests ====================

TEST_F(ValueTypeTest_2156, TypeIdConsistency_2156) {
    ValueType<uint16_t> v1;
    EXPECT_EQ(v1.typeId(), unsignedShort);

    ValueType<int16_t> v2;
    EXPECT_EQ(v2.typeId(), signedShort);

    ValueType<uint32_t> v3;
    EXPECT_EQ(v3.typeId(), unsignedLong);

    ValueType<int32_t> v4;
    EXPECT_EQ(v4.typeId(), signedLong);

    ValueType<Rational> v5;
    EXPECT_EQ(v5.typeId(), signedRational);

    ValueType<URational> v6;
    EXPECT_EQ(v6.typeId(), unsignedRational);

    ValueType<float> v7;
    EXPECT_EQ(v7.typeId(), tiffFloat);

    ValueType<double> v8;
    EXPECT_EQ(v8.typeId(), tiffDouble);
}

// ==================== Round-trip Tests ====================

TEST_F(ValueTypeTest_2156, RoundTripUint16_2156) {
    ValueType<uint16_t> v1;
    v1.value_.push_back(12345);
    byte buf[2] = {0};
    v1.copy(buf, bigEndian);

    ValueType<uint16_t> v2;
    v2.read(buf, sizeof(buf), bigEndian);
    EXPECT_EQ(v2.count(), 1u);
    EXPECT_EQ(v2.toInt64(0), 12345);
}

TEST_F(ValueTypeTest_2156, RoundTripUint32_2156) {
    ValueType<uint32_t> v1;
    v1.value_.push_back(0xDEADBEEF);
    byte buf[4] = {0};
    v1.copy(buf, littleEndian);

    ValueType<uint32_t> v2;
    v2.read(buf, sizeof(buf), littleEndian);
    EXPECT_EQ(v2.count(), 1u);
    EXPECT_EQ(v2.toUint32(0), 0xDEADBEEF);
}

TEST_F(ValueTypeTest_2156, RoundTripMultipleUint16_2156) {
    ValueType<uint16_t> v1;
    v1.value_.push_back(100);
    v1.value_.push_back(200);
    v1.value_.push_back(300);
    byte buf[6] = {0};
    v1.copy(buf, bigEndian);

    ValueType<uint16_t> v2;
    v2.read(buf, sizeof(buf), bigEndian);
    EXPECT_EQ(v2.count(), 3u);
    EXPECT_EQ(v2.toInt64(0), 100);
    EXPECT_EQ(v2.toInt64(1), 200);
    EXPECT_EQ(v2.toInt64(2), 300);
}
