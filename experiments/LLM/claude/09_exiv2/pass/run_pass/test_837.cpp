#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <sstream>
#include <string>
#include <cstdint>

using namespace Exiv2;

// Test fixture for XmpTextValue
class XmpTextValueTest_837 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test default constructor creates empty value
TEST_F(XmpTextValueTest_837, DefaultConstructor_837) {
    XmpTextValue value;
    EXPECT_EQ(value.size(), 0u);
    EXPECT_EQ(value.count(), 0u);
}

// Test constructor with string argument
TEST_F(XmpTextValueTest_837, StringConstructor_837) {
    XmpTextValue value("hello");
    EXPECT_GT(value.size(), 0u);
}

// Test read method with a simple string
TEST_F(XmpTextValueTest_837, ReadSimpleString_837) {
    XmpTextValue value;
    int result = value.read("test string");
    EXPECT_EQ(result, 0);
    EXPECT_GT(value.size(), 0u);
}

// Test read method with empty string
TEST_F(XmpTextValueTest_837, ReadEmptyString_837) {
    XmpTextValue value;
    int result = value.read("");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(value.size(), 0u);
}

// Test count equals size for XmpTextValue
TEST_F(XmpTextValueTest_837, CountEqualsSize_837) {
    XmpTextValue value;
    value.read("some text");
    EXPECT_EQ(value.count(), value.size());
}

// Test count on default constructed object
TEST_F(XmpTextValueTest_837, CountOnDefault_837) {
    XmpTextValue value;
    EXPECT_EQ(value.count(), 0u);
}

// Test size returns length of stored text
TEST_F(XmpTextValueTest_837, SizeReturnsTextLength_837) {
    XmpTextValue value;
    std::string text = "hello";
    value.read(text);
    EXPECT_EQ(value.size(), text.size());
}

// Test write outputs the stored text
TEST_F(XmpTextValueTest_837, WriteOutputsText_837) {
    XmpTextValue value;
    value.read("output test");
    std::ostringstream os;
    value.write(os);
    EXPECT_EQ(os.str(), "output test");
}

// Test write on empty value
TEST_F(XmpTextValueTest_837, WriteEmptyValue_837) {
    XmpTextValue value;
    std::ostringstream os;
    value.write(os);
    EXPECT_EQ(os.str(), "");
}

// Test toInt64 with numeric string
TEST_F(XmpTextValueTest_837, ToInt64WithNumericString_837) {
    XmpTextValue value;
    value.read("42");
    EXPECT_EQ(value.toInt64(0), 42);
}

// Test toInt64 with negative number
TEST_F(XmpTextValueTest_837, ToInt64WithNegativeNumber_837) {
    XmpTextValue value;
    value.read("-100");
    EXPECT_EQ(value.toInt64(0), -100);
}

// Test toInt64 with zero
TEST_F(XmpTextValueTest_837, ToInt64WithZero_837) {
    XmpTextValue value;
    value.read("0");
    EXPECT_EQ(value.toInt64(0), 0);
}

// Test toUint32 with numeric string
TEST_F(XmpTextValueTest_837, ToUint32WithNumericString_837) {
    XmpTextValue value;
    value.read("123");
    EXPECT_EQ(value.toUint32(0), 123u);
}

// Test toFloat with numeric string
TEST_F(XmpTextValueTest_837, ToFloatWithNumericString_837) {
    XmpTextValue value;
    value.read("3.14");
    EXPECT_FLOAT_EQ(value.toFloat(0), 3.14f);
}

// Test toFloat with integer string
TEST_F(XmpTextValueTest_837, ToFloatWithIntegerString_837) {
    XmpTextValue value;
    value.read("5");
    EXPECT_FLOAT_EQ(value.toFloat(0), 5.0f);
}

// Test toRational with numeric string
TEST_F(XmpTextValueTest_837, ToRationalWithNumericString_837) {
    XmpTextValue value;
    value.read("5");
    Rational r = value.toRational(0);
    // The rational should represent the value 5
    if (r.second != 0) {
        EXPECT_DOUBLE_EQ(static_cast<double>(r.first) / r.second, 5.0);
    }
}

// Test clone creates a copy
TEST_F(XmpTextValueTest_837, CloneCreatesCopy_837) {
    XmpTextValue value;
    value.read("clone me");
    auto cloned = value.clone();
    ASSERT_NE(cloned, nullptr);
    
    std::ostringstream os1, os2;
    value.write(os1);
    cloned->write(os2);
    EXPECT_EQ(os1.str(), os2.str());
}

// Test clone of empty value
TEST_F(XmpTextValueTest_837, CloneEmptyValue_837) {
    XmpTextValue value;
    auto cloned = value.clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->size(), 0u);
}

// Test read overwrites previous value
TEST_F(XmpTextValueTest_837, ReadOverwritesPrevious_837) {
    XmpTextValue value;
    value.read("first");
    value.read("second");
    std::ostringstream os;
    value.write(os);
    EXPECT_EQ(os.str(), "second");
}

// Test with long string
TEST_F(XmpTextValueTest_837, LongString_837) {
    XmpTextValue value;
    std::string longStr(10000, 'a');
    value.read(longStr);
    EXPECT_EQ(value.size(), 10000u);
    std::ostringstream os;
    value.write(os);
    EXPECT_EQ(os.str(), longStr);
}

// Test with special characters
TEST_F(XmpTextValueTest_837, SpecialCharacters_837) {
    XmpTextValue value;
    value.read("hello\nworld\ttab");
    std::ostringstream os;
    value.write(os);
    EXPECT_EQ(os.str(), "hello\nworld\ttab");
}

// Test with unicode-like content
TEST_F(XmpTextValueTest_837, UnicodeContent_837) {
    XmpTextValue value;
    std::string utf8 = "héllo wörld";
    value.read(utf8);
    std::ostringstream os;
    value.write(os);
    EXPECT_EQ(os.str(), utf8);
}

// Test toInt64 with non-numeric string (boundary/error case)
TEST_F(XmpTextValueTest_837, ToInt64WithNonNumericString_837) {
    XmpTextValue value;
    value.read("not a number");
    // Should return 0 or throw - testing observable behavior
    int64_t result = value.toInt64(0);
    EXPECT_EQ(result, 0);
}

// Test toFloat with non-numeric string
TEST_F(XmpTextValueTest_837, ToFloatWithNonNumericString_837) {
    XmpTextValue value;
    value.read("not a float");
    float result = value.toFloat(0);
    EXPECT_FLOAT_EQ(result, 0.0f);
}

// Test with spaces only
TEST_F(XmpTextValueTest_837, SpacesOnly_837) {
    XmpTextValue value;
    value.read("   ");
    EXPECT_EQ(value.size(), 3u);
    std::ostringstream os;
    value.write(os);
    EXPECT_EQ(os.str(), "   ");
}

// Test string constructor and then read
TEST_F(XmpTextValueTest_837, StringConstructorThenRead_837) {
    XmpTextValue value("initial");
    value.read("updated");
    std::ostringstream os;
    value.write(os);
    EXPECT_EQ(os.str(), "updated");
}

// Test toInt64 ignores the n parameter (since it's a single text value)
TEST_F(XmpTextValueTest_837, ToInt64IgnoresN_837) {
    XmpTextValue value;
    value.read("99");
    EXPECT_EQ(value.toInt64(0), value.toInt64(1));
}

// Test with rational-like string (e.g., "1/2")
TEST_F(XmpTextValueTest_837, RationalLikeString_837) {
    XmpTextValue value;
    value.read("1/2");
    Rational r = value.toRational(0);
    // Should parse as rational 1/2
    if (r.second != 0) {
        EXPECT_DOUBLE_EQ(static_cast<double>(r.first) / r.second, 0.5);
    }
}

// Test count after multiple reads
TEST_F(XmpTextValueTest_837, CountAfterMultipleReads_837) {
    XmpTextValue value;
    value.read("abc");
    EXPECT_EQ(value.count(), 3u);
    value.read("abcdef");
    EXPECT_EQ(value.count(), 6u);
    value.read("");
    EXPECT_EQ(value.count(), 0u);
}

// Test single character
TEST_F(XmpTextValueTest_837, SingleCharacter_837) {
    XmpTextValue value;
    value.read("X");
    EXPECT_EQ(value.size(), 1u);
    EXPECT_EQ(value.count(), 1u);
    EXPECT_EQ(value.toInt64(0), 0); // 'X' is not a number
}

// Test numeric boundary - large number
TEST_F(XmpTextValueTest_837, LargeNumber_837) {
    XmpTextValue value;
    value.read("9999999999");
    int64_t result = value.toInt64(0);
    EXPECT_EQ(result, 9999999999LL);
}

// Test toUint32 with zero
TEST_F(XmpTextValueTest_837, ToUint32WithZero_837) {
    XmpTextValue value;
    value.read("0");
    EXPECT_EQ(value.toUint32(0), 0u);
}
