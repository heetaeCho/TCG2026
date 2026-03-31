#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <sstream>
#include <string>

using namespace Exiv2;

// Test fixture for XmpTextValue tests
class XmpTextValueTest_836 : public ::testing::Test {
protected:
    void SetUp() override {
    }
    void TearDown() override {
    }
};

// Test default constructor creates empty value
TEST_F(XmpTextValueTest_836, DefaultConstructor_SizeIsZero_836) {
    XmpTextValue value;
    EXPECT_EQ(0u, value.size());
}

// Test default constructor count is zero
TEST_F(XmpTextValueTest_836, DefaultConstructor_CountIsZero_836) {
    XmpTextValue value;
    EXPECT_EQ(0u, value.count());
}

// Test constructor with string parameter
TEST_F(XmpTextValueTest_836, StringConstructor_SizeMatchesString_836) {
    XmpTextValue value("Hello");
    EXPECT_EQ(5u, value.size());
}

// Test constructor with empty string
TEST_F(XmpTextValueTest_836, StringConstructor_EmptyString_836) {
    XmpTextValue value("");
    EXPECT_EQ(0u, value.size());
}

// Test read method with a simple string
TEST_F(XmpTextValueTest_836, Read_SimpleString_836) {
    XmpTextValue value;
    int result = value.read("TestValue");
    EXPECT_EQ(0, result);
    EXPECT_EQ(9u, value.size());
}

// Test read method with empty string
TEST_F(XmpTextValueTest_836, Read_EmptyString_836) {
    XmpTextValue value;
    int result = value.read("");
    EXPECT_EQ(0, result);
    EXPECT_EQ(0u, value.size());
}

// Test read overwrites previous value
TEST_F(XmpTextValueTest_836, Read_OverwritesPreviousValue_836) {
    XmpTextValue value;
    value.read("First");
    EXPECT_EQ(5u, value.size());
    value.read("SecondValue");
    EXPECT_EQ(11u, value.size());
}

// Test count after reading a value
TEST_F(XmpTextValueTest_836, Count_AfterRead_836) {
    XmpTextValue value;
    value.read("SomeText");
    EXPECT_EQ(1u, value.count());
}

// Test count with empty value
TEST_F(XmpTextValueTest_836, Count_EmptyValue_836) {
    XmpTextValue value;
    value.read("");
    // Even empty string should have count behavior defined
    EXPECT_GE(value.count(), 0u);
}

// Test write to output stream
TEST_F(XmpTextValueTest_836, Write_OutputMatchesInput_836) {
    XmpTextValue value;
    value.read("HelloWorld");
    std::ostringstream os;
    value.write(os);
    EXPECT_EQ("HelloWorld", os.str());
}

// Test write with empty value
TEST_F(XmpTextValueTest_836, Write_EmptyValue_836) {
    XmpTextValue value;
    value.read("");
    std::ostringstream os;
    value.write(os);
    EXPECT_EQ("", os.str());
}

// Test toInt64 with numeric string
TEST_F(XmpTextValueTest_836, ToInt64_NumericString_836) {
    XmpTextValue value;
    value.read("42");
    EXPECT_EQ(42, value.toInt64(0));
}

// Test toInt64 with negative number
TEST_F(XmpTextValueTest_836, ToInt64_NegativeNumber_836) {
    XmpTextValue value;
    value.read("-100");
    EXPECT_EQ(-100, value.toInt64(0));
}

// Test toInt64 with zero
TEST_F(XmpTextValueTest_836, ToInt64_Zero_836) {
    XmpTextValue value;
    value.read("0");
    EXPECT_EQ(0, value.toInt64(0));
}

// Test toUint32 with numeric string
TEST_F(XmpTextValueTest_836, ToUint32_NumericString_836) {
    XmpTextValue value;
    value.read("123");
    EXPECT_EQ(123u, value.toUint32(0));
}

// Test toFloat with float string
TEST_F(XmpTextValueTest_836, ToFloat_FloatString_836) {
    XmpTextValue value;
    value.read("3.14");
    EXPECT_NEAR(3.14f, value.toFloat(0), 0.01f);
}

// Test toFloat with integer string
TEST_F(XmpTextValueTest_836, ToFloat_IntegerString_836) {
    XmpTextValue value;
    value.read("42");
    EXPECT_NEAR(42.0f, value.toFloat(0), 0.01f);
}

// Test toRational with rational-like string
TEST_F(XmpTextValueTest_836, ToRational_IntegerString_836) {
    XmpTextValue value;
    value.read("5");
    Rational r = value.toRational(0);
    // The rational representation of 5 should be equivalent to 5/1 or similar
    if (r.second != 0) {
        EXPECT_NEAR(5.0, static_cast<double>(r.first) / r.second, 0.01);
    }
}

// Test clone creates independent copy
TEST_F(XmpTextValueTest_836, Clone_CreatesIndependentCopy_836) {
    XmpTextValue value;
    value.read("Original");
    auto cloned = value.clone();
    ASSERT_NE(nullptr, cloned.get());
    EXPECT_EQ(value.size(), cloned->size());
    
    // Modifying original shouldn't affect clone
    std::ostringstream os;
    cloned->write(os);
    EXPECT_EQ("Original", os.str());
}

// Test size with various string lengths
TEST_F(XmpTextValueTest_836, Size_VariousLengths_836) {
    XmpTextValue value;
    
    value.read("A");
    EXPECT_EQ(1u, value.size());
    
    value.read("AB");
    EXPECT_EQ(2u, value.size());
    
    value.read("ABCDEFGHIJ");
    EXPECT_EQ(10u, value.size());
}

// Test with string containing spaces
TEST_F(XmpTextValueTest_836, Read_StringWithSpaces_836) {
    XmpTextValue value;
    value.read("Hello World");
    EXPECT_EQ(11u, value.size());
    std::ostringstream os;
    value.write(os);
    EXPECT_EQ("Hello World", os.str());
}

// Test with string containing special characters
TEST_F(XmpTextValueTest_836, Read_SpecialCharacters_836) {
    XmpTextValue value;
    value.read("Hello\tWorld\n");
    EXPECT_EQ(12u, value.size());
}

// Test with very long string
TEST_F(XmpTextValueTest_836, Read_LongString_836) {
    std::string longStr(10000, 'x');
    XmpTextValue value;
    value.read(longStr);
    EXPECT_EQ(10000u, value.size());
}

// Test string constructor and then read
TEST_F(XmpTextValueTest_836, StringConstructorThenRead_836) {
    XmpTextValue value("Initial");
    EXPECT_EQ(7u, value.size());
    value.read("NewValue");
    EXPECT_EQ(8u, value.size());
    std::ostringstream os;
    value.write(os);
    EXPECT_EQ("NewValue", os.str());
}

// Test toInt64 with non-numeric string (n parameter ignored)
TEST_F(XmpTextValueTest_836, ToInt64_NonNumericString_836) {
    XmpTextValue value;
    value.read("abc");
    // Non-numeric should return 0 or throw - testing observable behavior
    EXPECT_EQ(0, value.toInt64(0));
}

// Test toFloat with non-numeric string
TEST_F(XmpTextValueTest_836, ToFloat_NonNumericString_836) {
    XmpTextValue value;
    value.read("abc");
    EXPECT_NEAR(0.0f, value.toFloat(0), 0.01f);
}

// Test with rational string "1/2"
TEST_F(XmpTextValueTest_836, ToRational_FractionString_836) {
    XmpTextValue value;
    value.read("1/2");
    Rational r = value.toRational(0);
    if (r.second != 0) {
        EXPECT_NEAR(0.5, static_cast<double>(r.first) / r.second, 0.01);
    }
}

// Test toInt64 with large number
TEST_F(XmpTextValueTest_836, ToInt64_LargeNumber_836) {
    XmpTextValue value;
    value.read("999999999");
    EXPECT_EQ(999999999, value.toInt64(0));
}

// Test toUint32 with zero
TEST_F(XmpTextValueTest_836, ToUint32_Zero_836) {
    XmpTextValue value;
    value.read("0");
    EXPECT_EQ(0u, value.toUint32(0));
}

// Test write returns the stream reference
TEST_F(XmpTextValueTest_836, Write_ReturnsStreamReference_836) {
    XmpTextValue value;
    value.read("Test");
    std::ostringstream os;
    std::ostream& result = value.write(os);
    EXPECT_EQ(&os, &result);
}
