#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <sstream>
#include <string>
#include <cstdint>

using namespace Exiv2;

// Test fixture for XmpTextValue
class XmpTextValueTest_835 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test default constructor creates a valid object
TEST_F(XmpTextValueTest_835, DefaultConstructor_835) {
    XmpTextValue value;
    EXPECT_EQ(value.size(), 0u);
    EXPECT_EQ(value.count(), 0u);
}

// Test constructor with string argument
TEST_F(XmpTextValueTest_835, StringConstructor_835) {
    XmpTextValue value("Hello World");
    EXPECT_GT(value.size(), 0u);
}

// Test read method with a simple string
TEST_F(XmpTextValueTest_835, ReadSimpleString_835) {
    XmpTextValue value;
    int result = value.read("test string");
    EXPECT_EQ(result, 0);
    EXPECT_GT(value.size(), 0u);
}

// Test read method with empty string
TEST_F(XmpTextValueTest_835, ReadEmptyString_835) {
    XmpTextValue value;
    int result = value.read("");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(value.size(), 0u);
}

// Test size returns correct length
TEST_F(XmpTextValueTest_835, SizeReturnsCorrectLength_835) {
    XmpTextValue value;
    value.read("12345");
    EXPECT_EQ(value.size(), 5u);
}

// Test count returns expected value
TEST_F(XmpTextValueTest_835, CountReturnsExpected_835) {
    XmpTextValue value;
    value.read("some text");
    EXPECT_EQ(value.count(), 1u);
}

// Test count for empty value
TEST_F(XmpTextValueTest_835, CountEmptyValue_835) {
    XmpTextValue value;
    EXPECT_EQ(value.count(), 0u);
}

// Test write outputs the stored text
TEST_F(XmpTextValueTest_835, WriteOutputsText_835) {
    XmpTextValue value;
    value.read("Hello");
    std::ostringstream os;
    value.write(os);
    EXPECT_EQ(os.str(), "Hello");
}

// Test write with empty value
TEST_F(XmpTextValueTest_835, WriteEmptyValue_835) {
    XmpTextValue value;
    std::ostringstream os;
    value.write(os);
    EXPECT_EQ(os.str(), "");
}

// Test toInt64 with numeric string
TEST_F(XmpTextValueTest_835, ToInt64WithNumericString_835) {
    XmpTextValue value;
    value.read("42");
    EXPECT_EQ(value.toInt64(0), 42);
}

// Test toInt64 with negative numeric string
TEST_F(XmpTextValueTest_835, ToInt64WithNegativeNumber_835) {
    XmpTextValue value;
    value.read("-100");
    EXPECT_EQ(value.toInt64(0), -100);
}

// Test toInt64 with zero
TEST_F(XmpTextValueTest_835, ToInt64WithZero_835) {
    XmpTextValue value;
    value.read("0");
    EXPECT_EQ(value.toInt64(0), 0);
}

// Test toUint32 with numeric string
TEST_F(XmpTextValueTest_835, ToUint32WithNumericString_835) {
    XmpTextValue value;
    value.read("123");
    EXPECT_EQ(value.toUint32(0), 123u);
}

// Test toFloat with float string
TEST_F(XmpTextValueTest_835, ToFloatWithFloatString_835) {
    XmpTextValue value;
    value.read("3.14");
    EXPECT_FLOAT_EQ(value.toFloat(0), 3.14f);
}

// Test toFloat with integer string
TEST_F(XmpTextValueTest_835, ToFloatWithIntegerString_835) {
    XmpTextValue value;
    value.read("42");
    EXPECT_FLOAT_EQ(value.toFloat(0), 42.0f);
}

// Test toRational with integer string
TEST_F(XmpTextValueTest_835, ToRationalWithInteger_835) {
    XmpTextValue value;
    value.read("5");
    Rational r = value.toRational(0);
    // The rational representation of 5 should have numerator/denominator = 5
    EXPECT_NE(r.second, 0);
    if (r.second != 0) {
        EXPECT_FLOAT_EQ(static_cast<float>(r.first) / static_cast<float>(r.second), 5.0f);
    }
}

// Test clone creates a copy
TEST_F(XmpTextValueTest_835, CloneCreatesCopy_835) {
    XmpTextValue value;
    value.read("clone test");
    auto cloned = value.clone();
    ASSERT_NE(cloned, nullptr);

    std::ostringstream os1, os2;
    value.write(os1);
    cloned->write(os2);
    EXPECT_EQ(os1.str(), os2.str());
}

// Test clone of empty value
TEST_F(XmpTextValueTest_835, CloneEmptyValue_835) {
    XmpTextValue value;
    auto cloned = value.clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->size(), 0u);
}

// Test read overwrites previous value
TEST_F(XmpTextValueTest_835, ReadOverwritesPreviousValue_835) {
    XmpTextValue value;
    value.read("first");
    value.read("second");
    std::ostringstream os;
    value.write(os);
    EXPECT_EQ(os.str(), "second");
}

// Test size after overwrite
TEST_F(XmpTextValueTest_835, SizeAfterOverwrite_835) {
    XmpTextValue value;
    value.read("short");
    EXPECT_EQ(value.size(), 5u);
    value.read("a much longer string");
    EXPECT_EQ(value.size(), 20u);
}

// Test with special characters
TEST_F(XmpTextValueTest_835, ReadSpecialCharacters_835) {
    XmpTextValue value;
    value.read("special chars: !@#$%^&*()");
    std::ostringstream os;
    value.write(os);
    EXPECT_EQ(os.str(), "special chars: !@#$%^&*()");
}

// Test with whitespace string
TEST_F(XmpTextValueTest_835, ReadWhitespaceString_835) {
    XmpTextValue value;
    value.read("   ");
    EXPECT_EQ(value.size(), 3u);
    std::ostringstream os;
    value.write(os);
    EXPECT_EQ(os.str(), "   ");
}

// Test string constructor and then verify via write
TEST_F(XmpTextValueTest_835, StringConstructorWrite_835) {
    XmpTextValue value("constructor value");
    std::ostringstream os;
    value.write(os);
    EXPECT_EQ(os.str(), "constructor value");
}

// Test toInt64 with non-numeric string (boundary/error case)
TEST_F(XmpTextValueTest_835, ToInt64WithNonNumericString_835) {
    XmpTextValue value;
    value.read("not a number");
    // Should return 0 or throw - we just test it doesn't crash
    int64_t result = value.toInt64(0);
    EXPECT_EQ(result, 0);
}

// Test toFloat with non-numeric string
TEST_F(XmpTextValueTest_835, ToFloatWithNonNumericString_835) {
    XmpTextValue value;
    value.read("abc");
    float result = value.toFloat(0);
    EXPECT_FLOAT_EQ(result, 0.0f);
}

// Test toUint32 with zero
TEST_F(XmpTextValueTest_835, ToUint32WithZero_835) {
    XmpTextValue value;
    value.read("0");
    EXPECT_EQ(value.toUint32(0), 0u);
}

// Test large numeric value for toInt64
TEST_F(XmpTextValueTest_835, ToInt64LargeValue_835) {
    XmpTextValue value;
    value.read("9999999999");
    EXPECT_EQ(value.toInt64(0), 9999999999LL);
}

// Test clone independence - modifying original doesn't affect clone
TEST_F(XmpTextValueTest_835, CloneIndependence_835) {
    XmpTextValue value;
    value.read("original");
    auto cloned = value.clone();

    value.read("modified");

    std::ostringstream osClone;
    cloned->write(osClone);
    EXPECT_EQ(osClone.str(), "original");

    std::ostringstream osOriginal;
    value.write(osOriginal);
    EXPECT_EQ(osOriginal.str(), "modified");
}

// Test with rational-like string for toRational
TEST_F(XmpTextValueTest_835, ToRationalWithRationalString_835) {
    XmpTextValue value;
    value.read("1/3");
    Rational r = value.toRational(0);
    // Check that the rational is valid
    EXPECT_NE(r.second, 0);
}

// Test with very long string
TEST_F(XmpTextValueTest_835, ReadVeryLongString_835) {
    std::string longStr(10000, 'x');
    XmpTextValue value;
    int result = value.read(longStr);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(value.size(), 10000u);
}

// Test with newlines in string
TEST_F(XmpTextValueTest_835, ReadStringWithNewlines_835) {
    XmpTextValue value;
    value.read("line1\nline2\nline3");
    std::ostringstream os;
    value.write(os);
    EXPECT_EQ(os.str(), "line1\nline2\nline3");
}

// Test count after reading non-empty string is 1
TEST_F(XmpTextValueTest_835, CountAfterReadNonEmpty_835) {
    XmpTextValue value;
    value.read("any text");
    EXPECT_EQ(value.count(), 1u);
}

// Test toFloat with rational-like string
TEST_F(XmpTextValueTest_835, ToFloatWithRationalString_835) {
    XmpTextValue value;
    value.read("1/2");
    float result = value.toFloat(0);
    EXPECT_FLOAT_EQ(result, 0.5f);
}
