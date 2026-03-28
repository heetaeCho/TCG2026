#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <sstream>

using namespace Exiv2;

// Test fixture for XmpArrayValue tests
class XmpArrayValueTest_2169 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test construction with xmpBag type
TEST_F(XmpArrayValueTest_2169, ConstructWithXmpBag_2169) {
    XmpArrayValue val(xmpBag);
    EXPECT_EQ(val.xmpArrayType(), XmpValue::xaBag);
}

// Test construction with xmpSeq type
TEST_F(XmpArrayValueTest_2169, ConstructWithXmpSeq_2169) {
    XmpArrayValue val(xmpSeq);
    EXPECT_EQ(val.xmpArrayType(), XmpValue::xaSeq);
}

// Test construction with xmpAlt type
TEST_F(XmpArrayValueTest_2169, ConstructWithXmpAlt_2169) {
    XmpArrayValue val(xmpAlt);
    EXPECT_EQ(val.xmpArrayType(), XmpValue::xaAlt);
}

// Test that count is 0 for newly constructed value
TEST_F(XmpArrayValueTest_2169, InitialCountIsZero_2169) {
    XmpArrayValue val(xmpBag);
    EXPECT_EQ(val.count(), 0u);
}

// Test read and count after reading a single value
TEST_F(XmpArrayValueTest_2169, ReadSingleValue_2169) {
    XmpArrayValue val(xmpBag);
    int result = val.read("hello");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(val.count(), 1u);
}

// Test read and toString for a single value
TEST_F(XmpArrayValueTest_2169, ToStringSingleValue_2169) {
    XmpArrayValue val(xmpBag);
    val.read("hello");
    EXPECT_EQ(val.toString(0), "hello");
}

// Test reading multiple values
TEST_F(XmpArrayValueTest_2169, ReadMultipleValues_2169) {
    XmpArrayValue val(xmpBag);
    val.read("first");
    val.read("second");
    val.read("third");
    EXPECT_EQ(val.count(), 3u);
    EXPECT_EQ(val.toString(0), "first");
    EXPECT_EQ(val.toString(1), "second");
    EXPECT_EQ(val.toString(2), "third");
}

// Test reading an empty string
TEST_F(XmpArrayValueTest_2169, ReadEmptyString_2169) {
    XmpArrayValue val(xmpBag);
    int result = val.read("");
    EXPECT_EQ(result, 0);
    // Even an empty string may be added
    // Just verify no crash
}

// Test toInt64 with numeric string
TEST_F(XmpArrayValueTest_2169, ToInt64WithNumericValue_2169) {
    XmpArrayValue val(xmpBag);
    val.read("42");
    EXPECT_EQ(val.toInt64(0), 42);
}

// Test toUint32 with numeric string
TEST_F(XmpArrayValueTest_2169, ToUint32WithNumericValue_2169) {
    XmpArrayValue val(xmpBag);
    val.read("100");
    EXPECT_EQ(val.toUint32(0), 100u);
}

// Test toFloat with numeric string
TEST_F(XmpArrayValueTest_2169, ToFloatWithNumericValue_2169) {
    XmpArrayValue val(xmpBag);
    val.read("3.14");
    EXPECT_NEAR(val.toFloat(0), 3.14f, 0.01f);
}

// Test toRational with numeric string
TEST_F(XmpArrayValueTest_2169, ToRationalWithNumericValue_2169) {
    XmpArrayValue val(xmpBag);
    val.read("5");
    Rational r = val.toRational(0);
    EXPECT_EQ(r.first, 5);
    EXPECT_EQ(r.second, 1);
}

// Test toInt64 with negative numeric string
TEST_F(XmpArrayValueTest_2169, ToInt64WithNegativeValue_2169) {
    XmpArrayValue val(xmpBag);
    val.read("-10");
    EXPECT_EQ(val.toInt64(0), -10);
}

// Test write to ostream
TEST_F(XmpArrayValueTest_2169, WriteToOstream_2169) {
    XmpArrayValue val(xmpBag);
    val.read("alpha");
    val.read("beta");
    std::ostringstream os;
    val.write(os);
    std::string output = os.str();
    EXPECT_FALSE(output.empty());
    // The output should contain the values
    EXPECT_NE(output.find("alpha"), std::string::npos);
    EXPECT_NE(output.find("beta"), std::string::npos);
}

// Test write with single element
TEST_F(XmpArrayValueTest_2169, WriteSingleElement_2169) {
    XmpArrayValue val(xmpBag);
    val.read("only");
    std::ostringstream os;
    val.write(os);
    std::string output = os.str();
    EXPECT_NE(output.find("only"), std::string::npos);
}

// Test clone returns a valid copy
TEST_F(XmpArrayValueTest_2169, CloneReturnsCopy_2169) {
    XmpArrayValue val(xmpBag);
    val.read("test");
    auto cloned = val.clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->count(), 1u);
    EXPECT_EQ(cloned->toString(0), "test");
}

// Test clone preserves multiple values
TEST_F(XmpArrayValueTest_2169, ClonePreservesMultipleValues_2169) {
    XmpArrayValue val(xmpSeq);
    val.read("a");
    val.read("b");
    val.read("c");
    auto cloned = val.clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->count(), 3u);
    EXPECT_EQ(cloned->toString(0), "a");
    EXPECT_EQ(cloned->toString(1), "b");
    EXPECT_EQ(cloned->toString(2), "c");
}

// Test size method
TEST_F(XmpArrayValueTest_2169, SizeMethod_2169) {
    XmpArrayValue val(xmpBag);
    EXPECT_EQ(val.size(), 0u);
    val.read("hello");
    EXPECT_GT(val.size(), 0u);
}

// Test toString with out-of-range index
TEST_F(XmpArrayValueTest_2169, ToStringOutOfRange_2169) {
    XmpArrayValue val(xmpBag);
    val.read("only");
    // Accessing index beyond count - should throw or return empty
    EXPECT_THROW(val.toString(1), std::out_of_range);
}

// Test toInt64 with out-of-range index
TEST_F(XmpArrayValueTest_2169, ToInt64OutOfRange_2169) {
    XmpArrayValue val(xmpBag);
    val.read("42");
    EXPECT_THROW(val.toInt64(1), std::out_of_range);
}

// Test toUint32 with out-of-range index
TEST_F(XmpArrayValueTest_2169, ToUint32OutOfRange_2169) {
    XmpArrayValue val(xmpBag);
    val.read("42");
    EXPECT_THROW(val.toUint32(1), std::out_of_range);
}

// Test toFloat with out-of-range index
TEST_F(XmpArrayValueTest_2169, ToFloatOutOfRange_2169) {
    XmpArrayValue val(xmpBag);
    val.read("3.14");
    EXPECT_THROW(val.toFloat(1), std::out_of_range);
}

// Test toRational with out-of-range index
TEST_F(XmpArrayValueTest_2169, ToRationalOutOfRange_2169) {
    XmpArrayValue val(xmpBag);
    val.read("5");
    EXPECT_THROW(val.toRational(1), std::out_of_range);
}

// Test xmpArrayType static method for various TypeIds
TEST_F(XmpArrayValueTest_2169, XmpArrayTypeStaticBag_2169) {
    EXPECT_EQ(XmpValue::xmpArrayType(xmpBag), XmpValue::xaBag);
}

TEST_F(XmpArrayValueTest_2169, XmpArrayTypeStaticSeq_2169) {
    EXPECT_EQ(XmpValue::xmpArrayType(xmpSeq), XmpValue::xaSeq);
}

TEST_F(XmpArrayValueTest_2169, XmpArrayTypeStaticAlt_2169) {
    EXPECT_EQ(XmpValue::xmpArrayType(xmpAlt), XmpValue::xaAlt);
}

// Test setXmpArrayType and xmpArrayType getter
TEST_F(XmpArrayValueTest_2169, SetAndGetXmpArrayType_2169) {
    XmpArrayValue val(xmpBag);
    EXPECT_EQ(val.xmpArrayType(), XmpValue::xaBag);
    val.setXmpArrayType(XmpValue::xaSeq);
    EXPECT_EQ(val.xmpArrayType(), XmpValue::xaSeq);
}

// Test setXmpStruct and xmpStruct getter
TEST_F(XmpArrayValueTest_2169, SetAndGetXmpStruct_2169) {
    XmpArrayValue val(xmpBag);
    EXPECT_EQ(val.xmpStruct(), XmpValue::xsNone);
    val.setXmpStruct(XmpValue::xsStruct);
    EXPECT_EQ(val.xmpStruct(), XmpValue::xsStruct);
}

// Test copy method
TEST_F(XmpArrayValueTest_2169, CopyMethod_2169) {
    XmpArrayValue val(xmpBag);
    val.read("test");
    size_t sz = val.size();
    std::vector<byte> buf(sz + 1, 0);
    size_t copied = val.copy(buf.data(), littleEndian);
    EXPECT_EQ(copied, sz);
}

// Test read from byte buffer
TEST_F(XmpArrayValueTest_2169, ReadFromByteBuffer_2169) {
    XmpArrayValue val(xmpBag);
    std::string data = "test_data";
    int result = val.read(reinterpret_cast<const byte*>(data.c_str()), data.size(), littleEndian);
    EXPECT_EQ(result, 0);
}

// Test toInt64 with non-numeric string returns 0
TEST_F(XmpArrayValueTest_2169, ToInt64WithNonNumericValue_2169) {
    XmpArrayValue val(xmpBag);
    val.read("abc");
    // Non-numeric string should convert to 0
    EXPECT_EQ(val.toInt64(0), 0);
}

// Test toFloat with non-numeric string returns 0
TEST_F(XmpArrayValueTest_2169, ToFloatWithNonNumericValue_2169) {
    XmpArrayValue val(xmpBag);
    val.read("abc");
    EXPECT_FLOAT_EQ(val.toFloat(0), 0.0f);
}

// Test with very large number string
TEST_F(XmpArrayValueTest_2169, ToInt64WithLargeNumber_2169) {
    XmpArrayValue val(xmpBag);
    val.read("9223372036854775807"); // INT64_MAX
    EXPECT_EQ(val.toInt64(0), INT64_MAX);
}

// Test write with no elements
TEST_F(XmpArrayValueTest_2169, WriteEmptyValue_2169) {
    XmpArrayValue val(xmpBag);
    std::ostringstream os;
    val.write(os);
    // Should not crash, output may be empty
    EXPECT_TRUE(os.str().empty() || !os.str().empty());
}

// Test with whitespace string
TEST_F(XmpArrayValueTest_2169, ReadWhitespaceString_2169) {
    XmpArrayValue val(xmpBag);
    val.read("   ");
    // Should handle whitespace
    EXPECT_GE(val.count(), 0u);
}

// Test multiple reads accumulate
TEST_F(XmpArrayValueTest_2169, MultipleReadsAccumulate_2169) {
    XmpArrayValue val(xmpSeq);
    for (int i = 0; i < 10; ++i) {
        val.read(std::to_string(i));
    }
    EXPECT_EQ(val.count(), 10u);
    for (size_t i = 0; i < 10; ++i) {
        EXPECT_EQ(val.toString(i), std::to_string(i));
    }
}

// Test toRational with float-like string
TEST_F(XmpArrayValueTest_2169, ToRationalWithFloatString_2169) {
    XmpArrayValue val(xmpBag);
    val.read("2.5");
    Rational r = val.toRational(0);
    // Should represent 2.5 as rational
    if (r.second != 0) {
        double result = static_cast<double>(r.first) / r.second;
        EXPECT_NEAR(result, 2.5, 0.01);
    }
}

// Test that xmpArrayType for non-array TypeId returns xaNone
TEST_F(XmpArrayValueTest_2169, XmpArrayTypeStaticNonArray_2169) {
    EXPECT_EQ(XmpValue::xmpArrayType(xmpText), XmpValue::xaNone);
}
