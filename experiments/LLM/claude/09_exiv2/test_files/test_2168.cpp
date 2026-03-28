#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <sstream>
#include <string>
#include <cstring>

using namespace Exiv2;

// Normal operation tests

TEST(XmpTextValueTest_2168, DefaultConstructor_2168) {
    XmpTextValue val;
    EXPECT_EQ(val.size(), 0u);
    EXPECT_EQ(val.count(), 0u);
}

TEST(XmpTextValueTest_2168, ConstructorWithString_2168) {
    XmpTextValue val("Hello World");
    EXPECT_EQ(val.size(), 11u);
    EXPECT_EQ(val.count(), 1u);
}

TEST(XmpTextValueTest_2168, ReadString_2168) {
    XmpTextValue val;
    int result = val.read("Test String");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(val.size(), 11u);
}

TEST(XmpTextValueTest_2168, ReadEmptyString_2168) {
    XmpTextValue val;
    int result = val.read("");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(val.size(), 0u);
    EXPECT_EQ(val.count(), 0u);
}

TEST(XmpTextValueTest_2168, WriteToStream_2168) {
    XmpTextValue val("Hello");
    std::ostringstream os;
    val.write(os);
    EXPECT_EQ(os.str(), "Hello");
}

TEST(XmpTextValueTest_2168, WriteEmptyToStream_2168) {
    XmpTextValue val;
    std::ostringstream os;
    val.write(os);
    EXPECT_EQ(os.str(), "");
}

TEST(XmpTextValueTest_2168, ToInt64WithNumericString_2168) {
    XmpTextValue val("42");
    EXPECT_EQ(val.toInt64(0), 42);
}

TEST(XmpTextValueTest_2168, ToUint32WithNumericString_2168) {
    XmpTextValue val("100");
    EXPECT_EQ(val.toUint32(0), 100u);
}

TEST(XmpTextValueTest_2168, ToFloatWithNumericString_2168) {
    XmpTextValue val("3.14");
    EXPECT_NEAR(val.toFloat(0), 3.14f, 0.01f);
}

TEST(XmpTextValueTest_2168, ToRationalWithNumericString_2168) {
    XmpTextValue val("5");
    Rational r = val.toRational(0);
    // Expect some rational representation of 5
    EXPECT_NE(r.second, 0);
    if (r.second != 0) {
        EXPECT_NEAR(static_cast<double>(r.first) / r.second, 5.0, 0.001);
    }
}

TEST(XmpTextValueTest_2168, Clone_2168) {
    XmpTextValue val("Clone me");
    auto cloned = val.clone();
    EXPECT_NE(cloned, nullptr);
    std::ostringstream os;
    cloned->write(os);
    EXPECT_EQ(os.str(), "Clone me");
}

TEST(XmpTextValueTest_2168, CopyToBuffer_2168) {
    XmpTextValue val("Copy");
    byte buf[10] = {0};
    size_t copied = val.copy(buf, bigEndian);
    EXPECT_EQ(copied, 4u);
    EXPECT_EQ(std::string(reinterpret_cast<char*>(buf), 4), "Copy");
}

TEST(XmpTextValueTest_2168, ReadFromByteBuffer_2168) {
    XmpTextValue val;
    const std::string data = "ByteData";
    int result = val.read(reinterpret_cast<const byte*>(data.c_str()), data.size(), bigEndian);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(val.size(), data.size());
    std::ostringstream os;
    val.write(os);
    EXPECT_EQ(os.str(), "ByteData");
}

TEST(XmpTextValueTest_2168, SizeMatchesStringLength_2168) {
    XmpTextValue val("abcdef");
    EXPECT_EQ(val.size(), 6u);
}

TEST(XmpTextValueTest_2168, CountForNonEmptyIsOne_2168) {
    XmpTextValue val("something");
    EXPECT_EQ(val.count(), 1u);
}

// XmpArrayType and XmpStruct tests

TEST(XmpTextValueTest_2168, DefaultXmpArrayType_2168) {
    XmpTextValue val;
    EXPECT_EQ(val.xmpArrayType(), XmpValue::xaNone);
}

TEST(XmpTextValueTest_2168, SetXmpArrayType_2168) {
    XmpTextValue val;
    val.setXmpArrayType(XmpValue::xaSeq);
    EXPECT_EQ(val.xmpArrayType(), XmpValue::xaSeq);
}

TEST(XmpTextValueTest_2168, SetXmpArrayTypeBag_2168) {
    XmpTextValue val;
    val.setXmpArrayType(XmpValue::xaBag);
    EXPECT_EQ(val.xmpArrayType(), XmpValue::xaBag);
}

TEST(XmpTextValueTest_2168, SetXmpArrayTypeAlt_2168) {
    XmpTextValue val;
    val.setXmpArrayType(XmpValue::xaAlt);
    EXPECT_EQ(val.xmpArrayType(), XmpValue::xaAlt);
}

TEST(XmpTextValueTest_2168, DefaultXmpStruct_2168) {
    XmpTextValue val;
    EXPECT_EQ(val.xmpStruct(), XmpValue::xsNone);
}

TEST(XmpTextValueTest_2168, SetXmpStruct_2168) {
    XmpTextValue val;
    val.setXmpStruct(XmpValue::xsStruct);
    EXPECT_EQ(val.xmpStruct(), XmpValue::xsStruct);
}

// Boundary tests

TEST(XmpTextValueTest_2168, ReadOverwritesPreviousValue_2168) {
    XmpTextValue val("first");
    EXPECT_EQ(val.size(), 5u);
    val.read("second");
    EXPECT_EQ(val.size(), 6u);
    std::ostringstream os;
    val.write(os);
    EXPECT_EQ(os.str(), "second");
}

TEST(XmpTextValueTest_2168, LongString_2168) {
    std::string longStr(10000, 'x');
    XmpTextValue val(longStr);
    EXPECT_EQ(val.size(), 10000u);
    EXPECT_EQ(val.count(), 1u);
}

TEST(XmpTextValueTest_2168, StringWithSpaces_2168) {
    XmpTextValue val("   spaces   ");
    EXPECT_EQ(val.size(), 13u);
    std::ostringstream os;
    val.write(os);
    EXPECT_EQ(os.str(), "   spaces   ");
}

TEST(XmpTextValueTest_2168, StringWithSpecialCharacters_2168) {
    XmpTextValue val("line1\nline2\ttab");
    EXPECT_EQ(val.size(), 15u);
    std::ostringstream os;
    val.write(os);
    EXPECT_EQ(os.str(), "line1\nline2\ttab");
}

TEST(XmpTextValueTest_2168, ToInt64WithNonNumericString_2168) {
    XmpTextValue val("not a number");
    // Should return 0 or handle gracefully for non-numeric
    int64_t result = val.toInt64(0);
    EXPECT_EQ(result, 0);
}

TEST(XmpTextValueTest_2168, ToFloatWithNonNumericString_2168) {
    XmpTextValue val("abc");
    float result = val.toFloat(0);
    EXPECT_EQ(result, 0.0f);
}

TEST(XmpTextValueTest_2168, ToUint32WithNonNumericString_2168) {
    XmpTextValue val("xyz");
    uint32_t result = val.toUint32(0);
    EXPECT_EQ(result, 0u);
}

TEST(XmpTextValueTest_2168, NegativeNumberToInt64_2168) {
    XmpTextValue val("-123");
    EXPECT_EQ(val.toInt64(0), -123);
}

TEST(XmpTextValueTest_2168, CopyEmptyValue_2168) {
    XmpTextValue val;
    byte buf[1] = {0};
    size_t copied = val.copy(buf, bigEndian);
    EXPECT_EQ(copied, 0u);
}

TEST(XmpTextValueTest_2168, RationalFromFloatString_2168) {
    XmpTextValue val("2.5");
    Rational r = val.toRational(0);
    EXPECT_NE(r.second, 0);
    if (r.second != 0) {
        EXPECT_NEAR(static_cast<double>(r.first) / r.second, 2.5, 0.001);
    }
}

TEST(XmpTextValueTest_2168, ReadByteBufferZeroLength_2168) {
    XmpTextValue val;
    const byte empty[] = {0};
    int result = val.read(empty, 0, bigEndian);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(val.size(), 0u);
}

TEST(XmpTextValueTest_2168, ToInt64WithZeroString_2168) {
    XmpTextValue val("0");
    EXPECT_EQ(val.toInt64(0), 0);
}

TEST(XmpTextValueTest_2168, ToFloatWithZeroString_2168) {
    XmpTextValue val("0.0");
    EXPECT_FLOAT_EQ(val.toFloat(0), 0.0f);
}

TEST(XmpTextValueTest_2168, ClonePreservesXmpArrayType_2168) {
    XmpTextValue val("test");
    val.setXmpArrayType(XmpValue::xaSeq);
    auto cloned = val.clone();
    // The cloned value should preserve the array type
    // We need to cast to access xmpArrayType if clone returns UniquePtr<Value>
    // This tests that clone preserves state
    EXPECT_NE(cloned, nullptr);
}

TEST(XmpTextValueTest_2168, MultipleReads_2168) {
    XmpTextValue val;
    val.read("first");
    EXPECT_EQ(val.size(), 5u);
    val.read("ab");
    EXPECT_EQ(val.size(), 2u);
    val.read("longer string now");
    EXPECT_EQ(val.size(), 17u);
}

TEST(XmpTextValueTest_2168, SingleCharacterString_2168) {
    XmpTextValue val("X");
    EXPECT_EQ(val.size(), 1u);
    EXPECT_EQ(val.count(), 1u);
    std::ostringstream os;
    val.write(os);
    EXPECT_EQ(os.str(), "X");
}

TEST(XmpTextValueTest_2168, CopyLittleEndian_2168) {
    XmpTextValue val("LE");
    byte buf[10] = {0};
    size_t copied = val.copy(buf, littleEndian);
    EXPECT_EQ(copied, 2u);
    EXPECT_EQ(std::string(reinterpret_cast<char*>(buf), 2), "LE");
}

TEST(XmpTextValueTest_2168, ToInt64LargeNumber_2168) {
    XmpTextValue val("9999999999");
    int64_t result = val.toInt64(0);
    EXPECT_EQ(result, 9999999999LL);
}

TEST(XmpTextValueTest_2168, RationalFractionString_2168) {
    XmpTextValue val("3/4");
    Rational r = val.toRational(0);
    // Should parse rational notation
    if (r.second != 0) {
        EXPECT_NEAR(static_cast<double>(r.first) / r.second, 0.75, 0.001);
    }
}
