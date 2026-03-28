#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <cstring>
#include <sstream>

using namespace Exiv2;

// Helper: StringValue is a concrete subclass of StringValueBase that we can instantiate
// In exiv2, StringValue derives from StringValueBase. We'll use it for testing.

class StringValueBaseTest_803 : public ::testing::Test {
protected:
    void SetUp() override {
    }
};

// Test reading a string and verifying the value_ member
TEST_F(StringValueBaseTest_803, ReadStringStoresValue_803) {
    StringValue sv;
    int result = sv.read("Hello, World!");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(sv.value_, "Hello, World!");
}

// Test reading an empty string
TEST_F(StringValueBaseTest_803, ReadEmptyString_803) {
    StringValue sv;
    int result = sv.read("");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(sv.value_, "");
}

// Test reading replaces previous value
TEST_F(StringValueBaseTest_803, ReadReplacesExistingValue_803) {
    StringValue sv;
    sv.read("First");
    EXPECT_EQ(sv.value_, "First");
    sv.read("Second");
    EXPECT_EQ(sv.value_, "Second");
}

// Test size() returns the length of the stored string
TEST_F(StringValueBaseTest_803, SizeReturnsStringLength_803) {
    StringValue sv;
    sv.read("ABCDE");
    EXPECT_EQ(sv.size(), 5u);
}

// Test size() for empty string
TEST_F(StringValueBaseTest_803, SizeEmptyString_803) {
    StringValue sv;
    sv.read("");
    EXPECT_EQ(sv.size(), 0u);
}

// Test count() returns the expected count
TEST_F(StringValueBaseTest_803, CountReturnsExpected_803) {
    StringValue sv;
    sv.read("test");
    // count() for a string value typically returns 1 or the size
    // We observe the behavior
    size_t c = sv.count();
    EXPECT_GE(c, 1u);
}

// Test copy() copies data to buffer
TEST_F(StringValueBaseTest_803, CopyToBuffer_803) {
    StringValue sv;
    sv.read("Hello");
    byte buf[10] = {};
    size_t copied = sv.copy(buf, invalidByteOrder);
    EXPECT_EQ(copied, 5u);
    EXPECT_EQ(std::memcmp(buf, "Hello", 5), 0);
}

// Test copy() with empty string
TEST_F(StringValueBaseTest_803, CopyEmptyString_803) {
    StringValue sv;
    sv.read("");
    byte buf[10] = {0xFF};
    size_t copied = sv.copy(buf, invalidByteOrder);
    EXPECT_EQ(copied, 0u);
}

// Test write() outputs to stream
TEST_F(StringValueBaseTest_803, WriteToStream_803) {
    StringValue sv;
    sv.read("StreamTest");
    std::ostringstream oss;
    sv.write(oss);
    EXPECT_EQ(oss.str(), "StreamTest");
}

// Test write() with empty string
TEST_F(StringValueBaseTest_803, WriteEmptyToStream_803) {
    StringValue sv;
    sv.read("");
    std::ostringstream oss;
    sv.write(oss);
    EXPECT_EQ(oss.str(), "");
}

// Test read from byte buffer
TEST_F(StringValueBaseTest_803, ReadFromByteBuffer_803) {
    StringValue sv;
    const byte data[] = "ByteData";
    int result = sv.read(data, 8, invalidByteOrder);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(sv.value_, "ByteData");
}

// Test read from byte buffer with zero length
TEST_F(StringValueBaseTest_803, ReadFromByteBufferZeroLength_803) {
    StringValue sv;
    const byte data[] = "Something";
    int result = sv.read(data, 0, invalidByteOrder);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(sv.value_, "");
}

// Test read from byte buffer with partial length
TEST_F(StringValueBaseTest_803, ReadFromByteBufferPartial_803) {
    StringValue sv;
    const byte data[] = "PartialRead";
    int result = sv.read(data, 7, invalidByteOrder);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(sv.value_, "Partial");
}

// Test toInt64 with numeric string
TEST_F(StringValueBaseTest_803, ToInt64WithNumericString_803) {
    StringValue sv;
    sv.read("12345");
    int64_t val = sv.toInt64(0);
    EXPECT_EQ(val, 12345);
}

// Test toUint32 with numeric string
TEST_F(StringValueBaseTest_803, ToUint32WithNumericString_803) {
    StringValue sv;
    sv.read("42");
    uint32_t val = sv.toUint32(0);
    EXPECT_EQ(val, 42u);
}

// Test toFloat with numeric string
TEST_F(StringValueBaseTest_803, ToFloatWithNumericString_803) {
    StringValue sv;
    sv.read("3.14");
    float val = sv.toFloat(0);
    EXPECT_NEAR(val, 3.14f, 0.01f);
}

// Test toRational with numeric string
TEST_F(StringValueBaseTest_803, ToRationalWithNumericString_803) {
    StringValue sv;
    sv.read("5");
    Rational rat = sv.toRational(0);
    // The rational representation of 5 should have a non-zero first element
    if (rat.second != 0) {
        EXPECT_NEAR(static_cast<double>(rat.first) / rat.second, 5.0, 0.01);
    }
}

// Test clone returns a valid copy
TEST_F(StringValueBaseTest_803, CloneReturnsCopy_803) {
    StringValue sv;
    sv.read("CloneMe");
    auto cloned = sv.clone();
    ASSERT_NE(cloned, nullptr);
    std::ostringstream oss;
    cloned->write(oss);
    EXPECT_EQ(oss.str(), "CloneMe");
}

// Test with string containing special characters
TEST_F(StringValueBaseTest_803, ReadStringWithSpecialChars_803) {
    StringValue sv;
    sv.read("Hello\nWorld\t!");
    EXPECT_EQ(sv.value_, "Hello\nWorld\t!");
    EXPECT_EQ(sv.size(), 13u);
}

// Test with string containing null-like characters embedded
TEST_F(StringValueBaseTest_803, ReadFromByteBufferWithNullByte_803) {
    StringValue sv;
    const byte data[] = {'A', 'B', '\0', 'C', 'D'};
    int result = sv.read(data, 5, invalidByteOrder);
    EXPECT_EQ(result, 0);
    // The string may be truncated at null or include all bytes
    EXPECT_GE(sv.size(), 2u); // At least "AB"
}

// Test with very long string
TEST_F(StringValueBaseTest_803, ReadLongString_803) {
    StringValue sv;
    std::string longStr(10000, 'X');
    int result = sv.read(longStr);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(sv.value_, longStr);
    EXPECT_EQ(sv.size(), 10000u);
}

// Test toInt64 with non-numeric string
TEST_F(StringValueBaseTest_803, ToInt64WithNonNumericString_803) {
    StringValue sv;
    sv.read("abc");
    // Should return 0 or throw; we just check it doesn't crash
    int64_t val = sv.toInt64(0);
    EXPECT_EQ(val, 0);
}

// Test toFloat with non-numeric string
TEST_F(StringValueBaseTest_803, ToFloatWithNonNumericString_803) {
    StringValue sv;
    sv.read("notanumber");
    float val = sv.toFloat(0);
    EXPECT_EQ(val, 0.0f);
}

// Test multiple reads overwrite correctly
TEST_F(StringValueBaseTest_803, MultipleReadsOverwrite_803) {
    StringValue sv;
    sv.read("First");
    EXPECT_EQ(sv.size(), 5u);
    sv.read("AB");
    EXPECT_EQ(sv.size(), 2u);
    EXPECT_EQ(sv.value_, "AB");
}

// Test copy with large string
TEST_F(StringValueBaseTest_803, CopyLargeString_803) {
    StringValue sv;
    std::string data(1000, 'Z');
    sv.read(data);
    std::vector<byte> buf(1000);
    size_t copied = sv.copy(buf.data(), invalidByteOrder);
    EXPECT_EQ(copied, 1000u);
    for (size_t i = 0; i < 1000; ++i) {
        EXPECT_EQ(buf[i], 'Z');
    }
}

// Test negative number conversion
TEST_F(StringValueBaseTest_803, ToInt64NegativeNumber_803) {
    StringValue sv;
    sv.read("-42");
    int64_t val = sv.toInt64(0);
    EXPECT_EQ(val, -42);
}

// Test toFloat with negative float
TEST_F(StringValueBaseTest_803, ToFloatNegativeNumber_803) {
    StringValue sv;
    sv.read("-2.5");
    float val = sv.toFloat(0);
    EXPECT_NEAR(val, -2.5f, 0.01f);
}
