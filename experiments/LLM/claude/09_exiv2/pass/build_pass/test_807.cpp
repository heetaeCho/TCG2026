#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <cstring>
#include <sstream>

using namespace Exiv2;

// Helper: StringValue is a concrete subclass of StringValueBase we can use for testing
// In exiv2, StringValue derives from StringValueBase

class StringValueBaseTest_807 : public ::testing::Test {
protected:
    void SetUp() override {
    }
};

// Test size() returns 0 for empty string
TEST_F(StringValueBaseTest_807, SizeReturnsZeroForEmptyString_807) {
    StringValue val;
    EXPECT_EQ(0u, val.size());
}

// Test size() returns correct value after reading a string
TEST_F(StringValueBaseTest_807, SizeReturnsCorrectValueAfterRead_807) {
    StringValue val;
    val.read("Hello");
    EXPECT_EQ(5u, val.size());
}

// Test size() returns correct value for single character
TEST_F(StringValueBaseTest_807, SizeReturnOneForSingleChar_807) {
    StringValue val;
    val.read("X");
    EXPECT_EQ(1u, val.size());
}

// Test count() returns same as size()
TEST_F(StringValueBaseTest_807, CountReturnsSameAsSize_807) {
    StringValue val;
    val.read("Test123");
    EXPECT_EQ(val.size(), val.count());
}

// Test read from string returns 0 (success)
TEST_F(StringValueBaseTest_807, ReadFromStringReturnsZero_807) {
    StringValue val;
    int result = val.read("Hello World");
    EXPECT_EQ(0, result);
}

// Test read from byte buffer
TEST_F(StringValueBaseTest_807, ReadFromByteBuffer_807) {
    StringValue val;
    const std::string data = "ByteData";
    int result = val.read(reinterpret_cast<const byte*>(data.c_str()), data.size(), littleEndian);
    EXPECT_EQ(0, result);
    EXPECT_EQ(data.size(), val.size());
}

// Test copy to byte buffer
TEST_F(StringValueBaseTest_807, CopyToByteBuffer_807) {
    StringValue val;
    val.read("CopyMe");
    byte buf[10] = {0};
    size_t copied = val.copy(buf, littleEndian);
    EXPECT_EQ(6u, copied);
    EXPECT_EQ(0, std::memcmp(buf, "CopyMe", 6));
}

// Test write to ostream
TEST_F(StringValueBaseTest_807, WriteToOstream_807) {
    StringValue val;
    val.read("Output");
    std::ostringstream os;
    val.write(os);
    EXPECT_EQ("Output", os.str());
}

// Test toInt64 with valid numeric string
TEST_F(StringValueBaseTest_807, ToInt64WithNumericString_807) {
    StringValue val;
    val.read("12345");
    int64_t result = val.toInt64(0);
    EXPECT_EQ(12345, result);
}

// Test toUint32 with valid numeric string
TEST_F(StringValueBaseTest_807, ToUint32WithNumericString_807) {
    StringValue val;
    val.read("42");
    uint32_t result = val.toUint32(0);
    EXPECT_EQ(42u, result);
}

// Test toFloat with valid numeric string
TEST_F(StringValueBaseTest_807, ToFloatWithNumericString_807) {
    StringValue val;
    val.read("3.14");
    float result = val.toFloat(0);
    EXPECT_NEAR(3.14f, result, 0.01f);
}

// Test toRational with numeric string
TEST_F(StringValueBaseTest_807, ToRationalWithNumericString_807) {
    StringValue val;
    val.read("5");
    Rational r = val.toRational(0);
    // The rational representation of 5 should have numerator/denominator such that num/den == 5
    if (r.second != 0) {
        EXPECT_DOUBLE_EQ(5.0, static_cast<double>(r.first) / static_cast<double>(r.second));
    }
}

// Test clone creates a proper copy
TEST_F(StringValueBaseTest_807, CloneCreatesCopy_807) {
    StringValue val;
    val.read("CloneMe");
    auto cloned = val.clone();
    ASSERT_NE(nullptr, cloned.get());
    EXPECT_EQ(val.size(), cloned->size());
    
    std::ostringstream os1, os2;
    val.write(os1);
    cloned->write(os2);
    EXPECT_EQ(os1.str(), os2.str());
}

// Test read overwrites previous value
TEST_F(StringValueBaseTest_807, ReadOverwritesPreviousValue_807) {
    StringValue val;
    val.read("First");
    EXPECT_EQ(5u, val.size());
    val.read("SecondLonger");
    EXPECT_EQ(12u, val.size());
}

// Test read with empty string
TEST_F(StringValueBaseTest_807, ReadEmptyString_807) {
    StringValue val;
    int result = val.read("");
    EXPECT_EQ(0, result);
    EXPECT_EQ(0u, val.size());
}

// Test read from byte buffer with zero length
TEST_F(StringValueBaseTest_807, ReadFromByteBufferZeroLength_807) {
    StringValue val;
    const byte b = 0;
    int result = val.read(&b, 0, littleEndian);
    EXPECT_EQ(0, result);
    EXPECT_EQ(0u, val.size());
}

// Test copy with empty value
TEST_F(StringValueBaseTest_807, CopyWithEmptyValue_807) {
    StringValue val;
    byte buf[1] = {0xFF};
    size_t copied = val.copy(buf, littleEndian);
    EXPECT_EQ(0u, copied);
}

// Test size after reading string with special characters
TEST_F(StringValueBaseTest_807, SizeWithSpecialCharacters_807) {
    StringValue val;
    val.read("Hello\0World");  // Note: std::string constructor stops at \0
    // The string "Hello\0World" when constructed from const char* will be "Hello"
    // But if we use std::string with explicit length, it could differ
    // Using the const char* constructor, size should be 5
    EXPECT_EQ(5u, val.size());
}

// Test size with string containing spaces
TEST_F(StringValueBaseTest_807, SizeWithSpaces_807) {
    StringValue val;
    val.read("Hello World Test");
    EXPECT_EQ(16u, val.size());
}

// Test read from byte buffer with big endian (byte order shouldn't matter for strings)
TEST_F(StringValueBaseTest_807, ReadFromByteBufferBigEndian_807) {
    StringValue val;
    const std::string data = "EndianTest";
    int result = val.read(reinterpret_cast<const byte*>(data.c_str()), data.size(), bigEndian);
    EXPECT_EQ(0, result);
    EXPECT_EQ(data.size(), val.size());
    
    std::ostringstream os;
    val.write(os);
    EXPECT_EQ("EndianTest", os.str());
}

// Test toInt64 with non-numeric string
TEST_F(StringValueBaseTest_807, ToInt64WithNonNumericString_807) {
    StringValue val;
    val.read("abc");
    // Should return 0 or handle gracefully
    int64_t result = val.toInt64(0);
    EXPECT_EQ(0, result);
}

// Test toFloat with non-numeric string
TEST_F(StringValueBaseTest_807, ToFloatWithNonNumericString_807) {
    StringValue val;
    val.read("notanumber");
    float result = val.toFloat(0);
    EXPECT_EQ(0.0f, result);
}

// Test large string
TEST_F(StringValueBaseTest_807, LargeString_807) {
    StringValue val;
    std::string largeStr(10000, 'A');
    val.read(largeStr);
    EXPECT_EQ(10000u, val.size());
}

// Test copy produces exact byte content
TEST_F(StringValueBaseTest_807, CopyProducesExactContent_807) {
    StringValue val;
    val.read("ABCDEF");
    byte buf[10] = {0};
    size_t copied = val.copy(buf, littleEndian);
    EXPECT_EQ(6u, copied);
    EXPECT_EQ('A', buf[0]);
    EXPECT_EQ('B', buf[1]);
    EXPECT_EQ('C', buf[2]);
    EXPECT_EQ('D', buf[3]);
    EXPECT_EQ('E', buf[4]);
    EXPECT_EQ('F', buf[5]);
}

// Test negative number conversion
TEST_F(StringValueBaseTest_807, ToInt64WithNegativeNumber_807) {
    StringValue val;
    val.read("-42");
    int64_t result = val.toInt64(0);
    EXPECT_EQ(-42, result);
}
