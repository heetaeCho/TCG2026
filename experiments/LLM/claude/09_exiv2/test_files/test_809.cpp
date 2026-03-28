#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <cstring>
#include <sstream>
#include <stdexcept>

using namespace Exiv2;

// Helper: StringValue is a concrete subclass of StringValueBase
// We use StringValue for testing since StringValueBase is typically abstract-ish
// but we can also use AsciiValue or StringValue which inherit from StringValueBase.

class StringValueBaseTest_809 : public ::testing::Test {
protected:
    void SetUp() override {
    }
};

// Test that reading a string sets value_ correctly
TEST_F(StringValueBaseTest_809, ReadStringSetsValue_809) {
    StringValue sv("Hello");
    EXPECT_EQ(sv.value_, "Hello");
}

// Test that read() from string works and returns 0
TEST_F(StringValueBaseTest_809, ReadStringReturnsZero_809) {
    StringValue sv("");
    int result = sv.read("TestString");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(sv.value_, "TestString");
}

// Test that read() from byte buffer works
TEST_F(StringValueBaseTest_809, ReadFromByteBuffer_809) {
    StringValue sv("");
    const std::string data = "ByteData";
    int result = sv.read(reinterpret_cast<const byte*>(data.c_str()), data.size(), littleEndian);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(sv.value_, "ByteData");
}

// Test size() returns correct length of the string
TEST_F(StringValueBaseTest_809, SizeReturnsStringLength_809) {
    StringValue sv("ABCDE");
    EXPECT_EQ(sv.size(), 5u);
}

// Test size() for empty string
TEST_F(StringValueBaseTest_809, SizeEmptyString_809) {
    StringValue sv("");
    EXPECT_EQ(sv.size(), 0u);
}

// Test count() returns expected value (should be 1 for string values)
TEST_F(StringValueBaseTest_809, CountReturnsOne_809) {
    StringValue sv("Hello World");
    EXPECT_EQ(sv.count(), 1u);
}

// Test copy() copies the string to a buffer
TEST_F(StringValueBaseTest_809, CopyCopiesDataToBuffer_809) {
    StringValue sv("Test");
    byte buf[10] = {0};
    size_t copied = sv.copy(buf, littleEndian);
    EXPECT_EQ(copied, 4u);
    EXPECT_EQ(std::string(reinterpret_cast<char*>(buf), copied), "Test");
}

// Test write() outputs the value to an ostream
TEST_F(StringValueBaseTest_809, WriteOutputsToStream_809) {
    StringValue sv("Output");
    std::ostringstream os;
    sv.write(os);
    EXPECT_EQ(os.str(), "Output");
}

// Test toInt64() with valid index
TEST_F(StringValueBaseTest_809, ToInt64ReturnsCharValue_809) {
    StringValue sv("A");
    int64_t val = sv.toInt64(0);
    EXPECT_EQ(val, static_cast<int64_t>('A'));
    EXPECT_TRUE(sv.ok());
}

// Test toInt64() with index in multi-char string
TEST_F(StringValueBaseTest_809, ToInt64ReturnsCharAtIndex_809) {
    StringValue sv("ABC");
    int64_t val0 = sv.toInt64(0);
    int64_t val1 = sv.toInt64(1);
    int64_t val2 = sv.toInt64(2);
    EXPECT_EQ(val0, static_cast<int64_t>('A'));
    EXPECT_EQ(val1, static_cast<int64_t>('B'));
    EXPECT_EQ(val2, static_cast<int64_t>('C'));
}

// Test toInt64() with out-of-range index throws
TEST_F(StringValueBaseTest_809, ToInt64OutOfRangeThrows_809) {
    StringValue sv("A");
    EXPECT_THROW(sv.toInt64(5), std::out_of_range);
}

// Test toUint32() returns character value as uint32
TEST_F(StringValueBaseTest_809, ToUint32ReturnsCharValue_809) {
    StringValue sv("Z");
    uint32_t val = sv.toUint32(0);
    EXPECT_EQ(val, static_cast<uint32_t>('Z'));
}

// Test toFloat() returns character value as float
TEST_F(StringValueBaseTest_809, ToFloatReturnsCharValue_809) {
    StringValue sv("B");
    float val = sv.toFloat(0);
    EXPECT_FLOAT_EQ(val, static_cast<float>('B'));
}

// Test toRational() returns a rational representation
TEST_F(StringValueBaseTest_809, ToRationalReturnsRational_809) {
    StringValue sv("C");
    Rational r = sv.toRational(0);
    EXPECT_EQ(r.first, static_cast<int>('C'));
    EXPECT_EQ(r.second, 1);
}

// Test clone creates a copy
TEST_F(StringValueBaseTest_809, CloneCreatesACopy_809) {
    StringValue sv("CloneMe");
    auto cloned = sv.clone();
    ASSERT_NE(cloned, nullptr);
    // The cloned value should write the same string
    std::ostringstream os;
    cloned->write(os);
    EXPECT_EQ(os.str(), "CloneMe");
}

// Test typeId returns the correct type
TEST_F(StringValueBaseTest_809, TypeIdReturnsStringType_809) {
    StringValue sv("test");
    EXPECT_EQ(sv.typeId(), string);
}

// Test reading an empty byte buffer
TEST_F(StringValueBaseTest_809, ReadEmptyByteBuffer_809) {
    StringValue sv("initial");
    const byte* data = reinterpret_cast<const byte*>("");
    int result = sv.read(data, 0, littleEndian);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(sv.size(), 0u);
}

// Test overwriting value with read
TEST_F(StringValueBaseTest_809, ReadOverwritesPreviousValue_809) {
    StringValue sv("first");
    EXPECT_EQ(sv.value_, "first");
    sv.read("second");
    EXPECT_EQ(sv.value_, "second");
}

// Test toString returns the string value
TEST_F(StringValueBaseTest_809, ToStringReturnsValue_809) {
    StringValue sv("hello");
    EXPECT_EQ(sv.toString(), "hello");
}

// Test with special characters
TEST_F(StringValueBaseTest_809, SpecialCharacters_809) {
    StringValue sv("a\tb\nc");
    EXPECT_EQ(sv.size(), 5u);
    EXPECT_EQ(sv.toInt64(0), static_cast<int64_t>('a'));
    EXPECT_EQ(sv.toInt64(1), static_cast<int64_t>('\t'));
    EXPECT_EQ(sv.toInt64(2), static_cast<int64_t>('b'));
}

// Test with null characters in the middle
TEST_F(StringValueBaseTest_809, NullCharacterInByteBuffer_809) {
    StringValue sv("");
    const char data[] = {'H', 'i', '\0', '!'};
    sv.read(reinterpret_cast<const byte*>(data), 4, littleEndian);
    // The string may be truncated at null or include it depending on implementation
    // We just verify it doesn't crash and size is reasonable
    EXPECT_LE(sv.size(), 4u);
}

// Test ok() after successful toInt64
TEST_F(StringValueBaseTest_809, OkTrueAfterToInt64_809) {
    StringValue sv("X");
    sv.toInt64(0);
    EXPECT_TRUE(sv.ok());
}

// Test sizeDataArea returns 0 by default
TEST_F(StringValueBaseTest_809, SizeDataAreaReturnsZero_809) {
    StringValue sv("data");
    EXPECT_EQ(sv.sizeDataArea(), 0u);
}

// Test dataArea returns empty by default
TEST_F(StringValueBaseTest_809, DataAreaReturnsEmpty_809) {
    StringValue sv("data");
    DataBuf buf = sv.dataArea();
    EXPECT_EQ(buf.size(), 0u);
}

// Test using AsciiValue (another StringValueBase subclass)
TEST_F(StringValueBaseTest_809, AsciiValueBasicOperation_809) {
    AsciiValue av("ascii test");
    EXPECT_EQ(av.value_, "ascii test");
    EXPECT_EQ(av.typeId(), asciiString);
    EXPECT_EQ(av.toInt64(0), static_cast<int64_t>('a'));
}

// Test with a long string
TEST_F(StringValueBaseTest_809, LongString_809) {
    std::string longStr(1000, 'x');
    StringValue sv(longStr);
    EXPECT_EQ(sv.size(), 1000u);
    EXPECT_EQ(sv.toInt64(999), static_cast<int64_t>('x'));
}

// Test copy with big endian (should not matter for strings)
TEST_F(StringValueBaseTest_809, CopyBigEndian_809) {
    StringValue sv("End");
    byte buf[10] = {0};
    size_t copied = sv.copy(buf, bigEndian);
    EXPECT_EQ(copied, 3u);
    EXPECT_EQ(std::string(reinterpret_cast<char*>(buf), copied), "End");
}
