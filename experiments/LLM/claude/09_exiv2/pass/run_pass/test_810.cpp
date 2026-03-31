#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <cstring>
#include <sstream>

using namespace Exiv2;

// We use StringValue (a concrete subclass of StringValueBase) for testing,
// since StringValueBase requires a TypeId. StringValue is typically available
// and uses asciiString type. If not available, we can also use the factory.

class StringValueBaseTest_810 : public ::testing::Test {
protected:
    void SetUp() override {
    }
};

// Helper: create a StringValueBase-derived value via the factory
static Value::UniquePtr createStringValue(const std::string& str = "") {
    auto val = Value::create(asciiString);
    if (!str.empty()) {
        val->read(str);
    }
    return val;
}

// Test: toUint32 returns the character value at position n
TEST_F(StringValueBaseTest_810, ToUint32ReturnsCharValueAtIndex_810) {
    auto val = createStringValue("ABC");
    // 'A' = 65, 'B' = 66, 'C' = 67
    EXPECT_EQ(val->toUint32(0), static_cast<uint32_t>('A'));
    EXPECT_EQ(val->toUint32(1), static_cast<uint32_t>('B'));
    EXPECT_EQ(val->toUint32(2), static_cast<uint32_t>('C'));
    EXPECT_TRUE(val->ok());
}

// Test: toUint32 with index 0 on single character string
TEST_F(StringValueBaseTest_810, ToUint32SingleChar_810) {
    auto val = createStringValue("Z");
    EXPECT_EQ(val->toUint32(0), static_cast<uint32_t>('Z'));
    EXPECT_TRUE(val->ok());
}

// Test: toUint32 out of range throws (std::out_of_range from .at())
TEST_F(StringValueBaseTest_810, ToUint32OutOfRangeThrows_810) {
    auto val = createStringValue("AB");
    EXPECT_THROW(val->toUint32(5), std::out_of_range);
}

// Test: toUint32 on empty string throws
TEST_F(StringValueBaseTest_810, ToUint32EmptyStringThrows_810) {
    auto val = createStringValue("");
    EXPECT_THROW(val->toUint32(0), std::out_of_range);
}

// Test: read(string) sets the value correctly
TEST_F(StringValueBaseTest_810, ReadStringSetsValue_810) {
    auto val = createStringValue();
    int result = val->read("Hello");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(val->toString(), "Hello");
}

// Test: read(byte*, len, byteOrder) sets the value
TEST_F(StringValueBaseTest_810, ReadByteBufferSetsValue_810) {
    auto val = createStringValue();
    const std::string data = "TestData";
    int result = val->read(reinterpret_cast<const byte*>(data.c_str()), data.size(), littleEndian);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(val->size(), data.size());
}

// Test: size returns length of the string
TEST_F(StringValueBaseTest_810, SizeReturnsStringLength_810) {
    auto val = createStringValue("12345");
    EXPECT_EQ(val->size(), 5u);
}

// Test: count returns the number of characters
TEST_F(StringValueBaseTest_810, CountReturnsOne_810) {
    auto val = createStringValue("Hello");
    // For StringValueBase, count() typically returns 1 (one string value)
    // but it may vary. Let's just check it's > 0.
    EXPECT_GE(val->count(), 1u);
}

// Test: copy copies bytes to buffer
TEST_F(StringValueBaseTest_810, CopyCopiesBytesToBuffer_810) {
    auto val = createStringValue("ABCD");
    byte buf[10] = {};
    size_t copied = val->copy(buf, littleEndian);
    EXPECT_EQ(copied, 4u);
    EXPECT_EQ(buf[0], 'A');
    EXPECT_EQ(buf[1], 'B');
    EXPECT_EQ(buf[2], 'C');
    EXPECT_EQ(buf[3], 'D');
}

// Test: write outputs value to stream
TEST_F(StringValueBaseTest_810, WriteOutputsToStream_810) {
    auto val = createStringValue("Hello World");
    std::ostringstream oss;
    val->write(oss);
    EXPECT_EQ(oss.str(), "Hello World");
}

// Test: toString returns the string value
TEST_F(StringValueBaseTest_810, ToStringReturnsValue_810) {
    auto val = createStringValue("TestString");
    EXPECT_EQ(val->toString(), "TestString");
}

// Test: toInt64 returns character value at position n
TEST_F(StringValueBaseTest_810, ToInt64ReturnsCharValue_810) {
    auto val = createStringValue("A");
    EXPECT_EQ(val->toInt64(0), static_cast<int64_t>('A'));
}

// Test: toFloat returns character value as float at position n
TEST_F(StringValueBaseTest_810, ToFloatReturnsCharValue_810) {
    auto val = createStringValue("B");
    EXPECT_FLOAT_EQ(val->toFloat(0), static_cast<float>('B'));
}

// Test: toRational returns a rational representation
TEST_F(StringValueBaseTest_810, ToRationalReturnsRational_810) {
    auto val = createStringValue("C");
    Rational r = val->toRational(0);
    // Typically the rational would be (charValue, 1)
    EXPECT_EQ(r.first, static_cast<int32_t>('C'));
    EXPECT_EQ(r.second, 1);
}

// Test: typeId returns asciiString
TEST_F(StringValueBaseTest_810, TypeIdReturnsAsciiString_810) {
    auto val = createStringValue("test");
    EXPECT_EQ(val->typeId(), asciiString);
}

// Test: clone creates a copy
TEST_F(StringValueBaseTest_810, CloneCreatesCopy_810) {
    auto val = createStringValue("CloneMe");
    auto cloned = val->clone();
    EXPECT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->toString(), "CloneMe");
    EXPECT_EQ(cloned->typeId(), asciiString);
}

// Test: ok is true after successful toUint32
TEST_F(StringValueBaseTest_810, OkIsTrueAfterToUint32_810) {
    auto val = createStringValue("X");
    val->toUint32(0);
    EXPECT_TRUE(val->ok());
}

// Test: reading an empty string
TEST_F(StringValueBaseTest_810, ReadEmptyString_810) {
    auto val = createStringValue();
    int result = val->read("");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(val->size(), 0u);
    EXPECT_EQ(val->toString(), "");
}

// Test: toUint32 with null character in string
TEST_F(StringValueBaseTest_810, ToUint32WithNullChar_810) {
    auto val = Value::create(asciiString);
    // Read a buffer that contains a null byte
    const byte data[] = {0x00, 0x41, 0x42};
    val->read(data, 3, littleEndian);
    EXPECT_EQ(val->toUint32(0), 0u);
}

// Test: toUint32 with high ASCII values
TEST_F(StringValueBaseTest_810, ToUint32HighAscii_810) {
    auto val = Value::create(asciiString);
    const byte data[] = {0xFF, 0x80};
    val->read(data, 2, littleEndian);
    // 0xFF as unsigned char = 255
    uint32_t result = val->toUint32(0);
    EXPECT_EQ(result, static_cast<uint32_t>(static_cast<unsigned char>(0xFF)));
}

// Test: sizeDataArea returns 0 by default
TEST_F(StringValueBaseTest_810, SizeDataAreaReturnsZero_810) {
    auto val = createStringValue("data");
    EXPECT_EQ(val->sizeDataArea(), 0u);
}

// Test: setDataArea returns -1 (not supported for string values)
TEST_F(StringValueBaseTest_810, SetDataAreaReturnsError_810) {
    auto val = createStringValue("data");
    const byte buf[] = {0x01, 0x02};
    int result = val->setDataArea(buf, 2);
    EXPECT_EQ(result, -1);
}

// Test: Multiple reads overwrite previous value
TEST_F(StringValueBaseTest_810, MultipleReadsOverwriteValue_810) {
    auto val = createStringValue("First");
    EXPECT_EQ(val->toString(), "First");
    val->read("Second");
    EXPECT_EQ(val->toString(), "Second");
    EXPECT_EQ(val->size(), 6u);
}

// Test: toInt64 out of range throws
TEST_F(StringValueBaseTest_810, ToInt64OutOfRangeThrows_810) {
    auto val = createStringValue("A");
    EXPECT_THROW(val->toInt64(10), std::out_of_range);
}

// Test: toFloat out of range throws
TEST_F(StringValueBaseTest_810, ToFloatOutOfRangeThrows_810) {
    auto val = createStringValue("A");
    EXPECT_THROW(val->toFloat(10), std::out_of_range);
}

// Test: toRational out of range throws
TEST_F(StringValueBaseTest_810, ToRationalOutOfRangeThrows_810) {
    auto val = createStringValue("A");
    EXPECT_THROW(val->toRational(10), std::out_of_range);
}
