#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <cstring>
#include <sstream>

using namespace Exiv2;

// Helper: StringValue is a concrete subclass of StringValueBase that we can instantiate
// In exiv2, StringValue derives from StringValueBase

class StringValueBaseTest_806 : public ::testing::Test {
protected:
    void SetUp() override {
    }
};

// Test that count() returns the size of the string (same as size())
TEST_F(StringValueBaseTest_806, CountReturnsSize_806) {
    StringValue val("Hello");
    EXPECT_EQ(val.count(), val.size());
}

// Test with empty string
TEST_F(StringValueBaseTest_806, EmptyStringCountIsZero_806) {
    StringValue val("");
    EXPECT_EQ(val.count(), 0u);
    EXPECT_EQ(val.size(), 0u);
}

// Test read from string
TEST_F(StringValueBaseTest_806, ReadFromString_806) {
    StringValue val("");
    int result = val.read("TestString");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(val.count(), 10u);
    EXPECT_EQ(val.size(), 10u);
}

// Test read from byte buffer
TEST_F(StringValueBaseTest_806, ReadFromByteBuffer_806) {
    StringValue val("");
    const std::string data = "Hello";
    int result = val.read(reinterpret_cast<const byte*>(data.c_str()), data.size(), littleEndian);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(val.size(), data.size());
    EXPECT_EQ(val.count(), data.size());
}

// Test copy to byte buffer
TEST_F(StringValueBaseTest_806, CopyToBuffer_806) {
    StringValue val("Hello");
    byte buf[10] = {0};
    size_t copied = val.copy(buf, littleEndian);
    EXPECT_EQ(copied, 5u);
    EXPECT_EQ(std::string(reinterpret_cast<char*>(buf), copied), "Hello");
}

// Test write to ostream
TEST_F(StringValueBaseTest_806, WriteToOstream_806) {
    StringValue val("TestOutput");
    std::ostringstream os;
    val.write(os);
    EXPECT_EQ(os.str(), "TestOutput");
}

// Test toInt64 with numeric string
TEST_F(StringValueBaseTest_806, ToInt64WithNumericString_806) {
    StringValue val("12345");
    int64_t result = val.toInt64(0);
    EXPECT_EQ(result, 12345);
}

// Test toUint32 with numeric string
TEST_F(StringValueBaseTest_806, ToUint32WithNumericString_806) {
    StringValue val("42");
    uint32_t result = val.toUint32(0);
    EXPECT_EQ(result, 42u);
}

// Test toFloat with numeric string
TEST_F(StringValueBaseTest_806, ToFloatWithNumericString_806) {
    StringValue val("3.14");
    float result = val.toFloat(0);
    EXPECT_NEAR(result, 3.14f, 0.01f);
}

// Test toRational with numeric string
TEST_F(StringValueBaseTest_806, ToRationalWithNumericString_806) {
    StringValue val("5");
    Rational result = val.toRational(0);
    // Rational is typically a pair of int32_t
    // The exact representation depends on implementation, but value should represent 5
    EXPECT_NE(result.second, 0);
    if (result.second != 0) {
        EXPECT_FLOAT_EQ(static_cast<float>(result.first) / result.second, 5.0f);
    }
}

// Test clone
TEST_F(StringValueBaseTest_806, ClonePreservesValue_806) {
    StringValue val("CloneMe");
    auto cloned = val.clone();
    ASSERT_NE(cloned, nullptr);
    std::ostringstream os1, os2;
    val.write(os1);
    cloned->write(os2);
    EXPECT_EQ(os1.str(), os2.str());
}

// Test reading overwrites previous value
TEST_F(StringValueBaseTest_806, ReadOverwritesPreviousValue_806) {
    StringValue val("First");
    EXPECT_EQ(val.size(), 5u);
    val.read("SecondValue");
    EXPECT_EQ(val.size(), 11u);
    EXPECT_EQ(val.count(), 11u);
}

// Test single character string
TEST_F(StringValueBaseTest_806, SingleCharacterString_806) {
    StringValue val("X");
    EXPECT_EQ(val.count(), 1u);
    EXPECT_EQ(val.size(), 1u);
}

// Test with non-numeric string conversion
TEST_F(StringValueBaseTest_806, ToInt64WithNonNumericString_806) {
    StringValue val("abc");
    // Should return 0 or handle gracefully for non-numeric
    int64_t result = val.toInt64(0);
    EXPECT_EQ(result, 0);
}

// Test with negative numeric string
TEST_F(StringValueBaseTest_806, ToInt64WithNegativeString_806) {
    StringValue val("-123");
    int64_t result = val.toInt64(0);
    EXPECT_EQ(result, -123);
}

// Test copy with empty string
TEST_F(StringValueBaseTest_806, CopyEmptyString_806) {
    StringValue val("");
    byte buf[10] = {0};
    size_t copied = val.copy(buf, littleEndian);
    EXPECT_EQ(copied, 0u);
}

// Test read from zero-length byte buffer
TEST_F(StringValueBaseTest_806, ReadFromZeroLengthByteBuffer_806) {
    StringValue val("initial");
    const byte empty = 0;
    int result = val.read(&empty, 0, littleEndian);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(val.size(), 0u);
}

// Test string with spaces
TEST_F(StringValueBaseTest_806, StringWithSpaces_806) {
    StringValue val("Hello World");
    EXPECT_EQ(val.count(), 11u);
    std::ostringstream os;
    val.write(os);
    EXPECT_EQ(os.str(), "Hello World");
}

// Test byte order independence (StringValueBase should ignore byte order)
TEST_F(StringValueBaseTest_806, ByteOrderIndependence_806) {
    StringValue val1("");
    StringValue val2("");
    const std::string data = "TestData";
    val1.read(reinterpret_cast<const byte*>(data.c_str()), data.size(), littleEndian);
    val2.read(reinterpret_cast<const byte*>(data.c_str()), data.size(), bigEndian);
    EXPECT_EQ(val1.size(), val2.size());
    
    byte buf1[20] = {0}, buf2[20] = {0};
    size_t c1 = val1.copy(buf1, littleEndian);
    size_t c2 = val2.copy(buf2, bigEndian);
    EXPECT_EQ(c1, c2);
    EXPECT_EQ(std::memcmp(buf1, buf2, c1), 0);
}

// Test with large string
TEST_F(StringValueBaseTest_806, LargeString_806) {
    std::string largeStr(10000, 'A');
    StringValue val(largeStr);
    EXPECT_EQ(val.count(), 10000u);
    EXPECT_EQ(val.size(), 10000u);
}

// Test toFloat with non-numeric returns 0
TEST_F(StringValueBaseTest_806, ToFloatWithNonNumeric_806) {
    StringValue val("notanumber");
    float result = val.toFloat(0);
    EXPECT_FLOAT_EQ(result, 0.0f);
}
