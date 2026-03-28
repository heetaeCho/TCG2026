#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <sstream>
#include <cstring>

using namespace Exiv2;

// Helper: StringValue is a concrete subclass of StringValueBase in exiv2.
// We use it for testing since StringValueBase might be abstract or we need a concrete type.
// Actually, looking at the interface, StringValueBase itself can be constructed.
// Let's use the available concrete types. In exiv2, StringValue and AsciiValue derive from StringValueBase.
// We'll use Value::create to get instances or construct StringValueBase-derived types directly.

class StringValueBaseTest_2166 : public ::testing::Test {
protected:
    void SetUp() override {
    }
};

// Test construction with a string initializes value correctly
TEST_F(StringValueBaseTest_2166, ConstructWithString_2166) {
    auto val = Value::create(string);
    ASSERT_NE(val, nullptr);
    val->read("Hello World");
    EXPECT_EQ(val->toString(), "Hello World");
}

// Test construction with empty string
TEST_F(StringValueBaseTest_2166, ConstructWithEmptyString_2166) {
    auto val = Value::create(string);
    ASSERT_NE(val, nullptr);
    val->read("");
    EXPECT_EQ(val->toString(), "");
}

// Test size returns correct string length
TEST_F(StringValueBaseTest_2166, SizeReturnsStringLength_2166) {
    auto val = Value::create(string);
    ASSERT_NE(val, nullptr);
    val->read("Test");
    EXPECT_EQ(val->size(), 4u);
}

// Test size for empty string
TEST_F(StringValueBaseTest_2166, SizeEmptyString_2166) {
    auto val = Value::create(string);
    ASSERT_NE(val, nullptr);
    val->read("");
    EXPECT_EQ(val->size(), 0u);
}

// Test count returns 1 for StringValueBase
TEST_F(StringValueBaseTest_2166, CountReturnsOne_2166) {
    auto val = Value::create(string);
    ASSERT_NE(val, nullptr);
    val->read("Hello");
    EXPECT_EQ(val->count(), 1u);
}

// Test read from string
TEST_F(StringValueBaseTest_2166, ReadFromString_2166) {
    auto val = Value::create(string);
    ASSERT_NE(val, nullptr);
    int result = val->read("New Value");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(val->toString(), "New Value");
}

// Test read from byte buffer
TEST_F(StringValueBaseTest_2166, ReadFromByteBuffer_2166) {
    auto val = Value::create(string);
    ASSERT_NE(val, nullptr);
    const std::string data = "ByteData";
    int result = val->read(reinterpret_cast<const byte*>(data.c_str()), data.size(), littleEndian);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(val->toString(), "ByteData");
}

// Test copy to byte buffer
TEST_F(StringValueBaseTest_2166, CopyToBuffer_2166) {
    auto val = Value::create(string);
    ASSERT_NE(val, nullptr);
    val->read("Copy");
    byte buf[10] = {0};
    size_t copied = val->copy(buf, littleEndian);
    EXPECT_EQ(copied, 4u);
    EXPECT_EQ(std::string(reinterpret_cast<char*>(buf), copied), "Copy");
}

// Test write to ostream
TEST_F(StringValueBaseTest_2166, WriteToStream_2166) {
    auto val = Value::create(string);
    ASSERT_NE(val, nullptr);
    val->read("StreamTest");
    std::ostringstream os;
    val->write(os);
    EXPECT_EQ(os.str(), "StreamTest");
}

// Test toInt64 with numeric string
TEST_F(StringValueBaseTest_2166, ToInt64WithNumericString_2166) {
    auto val = Value::create(string);
    ASSERT_NE(val, nullptr);
    val->read("12345");
    int64_t result = val->toInt64(0);
    EXPECT_EQ(result, 12345);
}

// Test toUint32 with numeric string
TEST_F(StringValueBaseTest_2166, ToUint32WithNumericString_2166) {
    auto val = Value::create(string);
    ASSERT_NE(val, nullptr);
    val->read("42");
    uint32_t result = val->toUint32(0);
    EXPECT_EQ(result, 42u);
}

// Test toFloat with numeric string
TEST_F(StringValueBaseTest_2166, ToFloatWithNumericString_2166) {
    auto val = Value::create(string);
    ASSERT_NE(val, nullptr);
    val->read("3.14");
    float result = val->toFloat(0);
    EXPECT_NEAR(result, 3.14f, 0.01f);
}

// Test toRational with numeric string
TEST_F(StringValueBaseTest_2166, ToRationalWithNumericString_2166) {
    auto val = Value::create(string);
    ASSERT_NE(val, nullptr);
    val->read("5");
    Rational result = val->toRational(0);
    // Rational is typically a pair<int32_t, int32_t>
    // For integer 5, expect 5/1
    EXPECT_EQ(result.first, 5);
    EXPECT_EQ(result.second, 1);
}

// Test typeId returns correct type
TEST_F(StringValueBaseTest_2166, TypeIdReturnsString_2166) {
    auto val = Value::create(string);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->typeId(), string);
}

// Test reading replaces previous value
TEST_F(StringValueBaseTest_2166, ReadReplacesValue_2166) {
    auto val = Value::create(string);
    ASSERT_NE(val, nullptr);
    val->read("First");
    EXPECT_EQ(val->toString(), "First");
    val->read("Second");
    EXPECT_EQ(val->toString(), "Second");
    EXPECT_EQ(val->size(), 6u);
}

// Test clone creates independent copy
TEST_F(StringValueBaseTest_2166, CloneCreatesIndependentCopy_2166) {
    auto val = Value::create(string);
    ASSERT_NE(val, nullptr);
    val->read("Original");
    auto cloned = val->clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->toString(), "Original");
    // Modify original, clone should remain unchanged
    val->read("Modified");
    EXPECT_EQ(cloned->toString(), "Original");
    EXPECT_EQ(val->toString(), "Modified");
}

// Test ok() returns true after valid read
TEST_F(StringValueBaseTest_2166, OkReturnsTrueAfterValidRead_2166) {
    auto val = Value::create(string);
    ASSERT_NE(val, nullptr);
    val->read("Valid");
    EXPECT_TRUE(val->ok());
}

// Test with string containing special characters
TEST_F(StringValueBaseTest_2166, StringWithSpecialCharacters_2166) {
    auto val = Value::create(string);
    ASSERT_NE(val, nullptr);
    val->read("Hello\tWorld\n");
    EXPECT_EQ(val->toString(), "Hello\tWorld\n");
    EXPECT_EQ(val->size(), 12u);
}

// Test with very long string
TEST_F(StringValueBaseTest_2166, LongString_2166) {
    auto val = Value::create(string);
    ASSERT_NE(val, nullptr);
    std::string longStr(10000, 'A');
    val->read(longStr);
    EXPECT_EQ(val->toString(), longStr);
    EXPECT_EQ(val->size(), 10000u);
}

// Test sizeDataArea returns 0 (no data area for string values)
TEST_F(StringValueBaseTest_2166, SizeDataAreaReturnsZero_2166) {
    auto val = Value::create(string);
    ASSERT_NE(val, nullptr);
    val->read("test");
    EXPECT_EQ(val->sizeDataArea(), 0u);
}

// Test read from byte buffer with zero length
TEST_F(StringValueBaseTest_2166, ReadFromByteBufferZeroLength_2166) {
    auto val = Value::create(string);
    ASSERT_NE(val, nullptr);
    const byte buf[] = {0};
    int result = val->read(buf, 0, littleEndian);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(val->size(), 0u);
}

// Test toInt64 with non-numeric string
TEST_F(StringValueBaseTest_2166, ToInt64WithNonNumericString_2166) {
    auto val = Value::create(string);
    ASSERT_NE(val, nullptr);
    val->read("abc");
    // Should return 0 for non-numeric, and ok() might be false
    int64_t result = val->toInt64(0);
    EXPECT_EQ(result, 0);
}

// Test toFloat with non-numeric string
TEST_F(StringValueBaseTest_2166, ToFloatWithNonNumericString_2166) {
    auto val = Value::create(string);
    ASSERT_NE(val, nullptr);
    val->read("notanumber");
    float result = val->toFloat(0);
    EXPECT_EQ(result, 0.0f);
}

// Test with string containing null bytes via byte buffer read
TEST_F(StringValueBaseTest_2166, ReadByteBufferWithNullBytes_2166) {
    auto val = Value::create(string);
    ASSERT_NE(val, nullptr);
    const byte buf[] = {'H', 'e', 0, 'l', 'o'};
    int result = val->read(buf, 5, littleEndian);
    EXPECT_EQ(result, 0);
    // The size should reflect all bytes read
    EXPECT_EQ(val->size(), 5u);
}

// Test copy to buffer matches size
TEST_F(StringValueBaseTest_2166, CopyMatchesSize_2166) {
    auto val = Value::create(string);
    ASSERT_NE(val, nullptr);
    val->read("ExactCopy");
    byte buf[20] = {0};
    size_t copied = val->copy(buf, bigEndian);
    EXPECT_EQ(copied, val->size());
}

// Test with negative number string for toInt64
TEST_F(StringValueBaseTest_2166, ToInt64WithNegativeNumber_2166) {
    auto val = Value::create(string);
    ASSERT_NE(val, nullptr);
    val->read("-42");
    int64_t result = val->toInt64(0);
    EXPECT_EQ(result, -42);
}

// Test with floating point string for toFloat
TEST_F(StringValueBaseTest_2166, ToFloatWithNegativeFloat_2166) {
    auto val = Value::create(string);
    ASSERT_NE(val, nullptr);
    val->read("-2.5");
    float result = val->toFloat(0);
    EXPECT_NEAR(result, -2.5f, 0.01f);
}

// Test write to stream with empty value
TEST_F(StringValueBaseTest_2166, WriteEmptyToStream_2166) {
    auto val = Value::create(string);
    ASSERT_NE(val, nullptr);
    val->read("");
    std::ostringstream os;
    val->write(os);
    EXPECT_EQ(os.str(), "");
}

// Test creating with asciiString type
TEST_F(StringValueBaseTest_2166, AsciiStringType_2166) {
    auto val = Value::create(asciiString);
    ASSERT_NE(val, nullptr);
    val->read("ASCII test");
    EXPECT_EQ(val->typeId(), asciiString);
    EXPECT_EQ(val->toString(), "ASCII test");
}

// Test count is always 1 regardless of content
TEST_F(StringValueBaseTest_2166, CountAlwaysOne_2166) {
    auto val = Value::create(string);
    ASSERT_NE(val, nullptr);
    val->read("");
    EXPECT_EQ(val->count(), 1u);
    val->read("a b c d e");
    EXPECT_EQ(val->count(), 1u);
}
