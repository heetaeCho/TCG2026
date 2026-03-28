#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "exiv2/value.hpp"

using namespace Exiv2;

// Test fixture for AsciiValue
class AsciiValueTest_813 : public ::testing::Test {
protected:
    void SetUp() override {
    }
};

// Test default constructor creates an AsciiValue with asciiString type
TEST_F(AsciiValueTest_813, DefaultConstructor_813) {
    AsciiValue val;
    EXPECT_EQ(val.typeId(), asciiString);
    EXPECT_EQ(val.size(), 0u);
}

// Test constructor with string argument
TEST_F(AsciiValueTest_813, StringConstructor_813) {
    AsciiValue val("Hello");
    EXPECT_EQ(val.typeId(), asciiString);
    // "Hello" + null terminator = 6 bytes
    EXPECT_GE(val.size(), 5u);
}

// Test read with a normal string appends null terminator
TEST_F(AsciiValueTest_813, ReadNormalString_813) {
    AsciiValue val;
    int result = val.read("Hello");
    EXPECT_EQ(result, 0);
    // The value should have "Hello\0", size = 6
    EXPECT_EQ(val.size(), 6u);
}

// Test read with a string that already ends with null terminator
TEST_F(AsciiValueTest_813, ReadStringWithNullTerminator_813) {
    AsciiValue val;
    std::string buf = "Hello";
    buf += '\0';  // Already has null terminator
    int result = val.read(buf);
    EXPECT_EQ(result, 0);
    // Should not add another null terminator
    EXPECT_EQ(val.size(), 6u);
}

// Test read with an empty string
TEST_F(AsciiValueTest_813, ReadEmptyString_813) {
    AsciiValue val;
    int result = val.read("");
    EXPECT_EQ(result, 0);
    // Empty string should get a null terminator appended, size = 1
    EXPECT_EQ(val.size(), 1u);
}

// Test read with a string that is just a null character
TEST_F(AsciiValueTest_813, ReadNullCharOnly_813) {
    AsciiValue val;
    std::string buf(1, '\0');
    int result = val.read(buf);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(val.size(), 1u);
}

// Test that read replaces previous value
TEST_F(AsciiValueTest_813, ReadReplacesValue_813) {
    AsciiValue val;
    val.read("First");
    EXPECT_EQ(val.size(), 6u);  // "First\0"
    
    val.read("Second value");
    EXPECT_EQ(val.size(), 13u);  // "Second value\0"
}

// Test count returns the number of characters including null
TEST_F(AsciiValueTest_813, CountReturnsSize_813) {
    AsciiValue val;
    val.read("Test");
    // count() for StringValueBase returns size()
    EXPECT_EQ(val.count(), val.size());
}

// Test write outputs the value without the trailing null
TEST_F(AsciiValueTest_813, WriteOutputsString_813) {
    AsciiValue val;
    val.read("Hello World");
    std::ostringstream os;
    val.write(os);
    std::string output = os.str();
    // write should output the string (typically without trailing null in the stream)
    EXPECT_EQ(output, "Hello World");
}

// Test write with empty value after reading empty string
TEST_F(AsciiValueTest_813, WriteEmptyValue_813) {
    AsciiValue val;
    val.read("");
    std::ostringstream os;
    val.write(os);
    std::string output = os.str();
    EXPECT_TRUE(output.empty());
}

// Test copy copies the value into a byte buffer
TEST_F(AsciiValueTest_813, CopyToBuffer_813) {
    AsciiValue val;
    val.read("ABC");
    byte buf[10] = {};
    size_t copied = val.copy(buf, invalidByteOrder);
    EXPECT_EQ(copied, 4u);  // "ABC\0"
    EXPECT_EQ(buf[0], 'A');
    EXPECT_EQ(buf[1], 'B');
    EXPECT_EQ(buf[2], 'C');
    EXPECT_EQ(buf[3], '\0');
}

// Test clone creates an independent copy
TEST_F(AsciiValueTest_813, CloneCreatesIndependentCopy_813) {
    AsciiValue val;
    val.read("Original");
    auto cloned = val.clone();
    EXPECT_NE(cloned.get(), nullptr);
    EXPECT_EQ(cloned->typeId(), asciiString);
    
    // Verify the clone has the same size
    EXPECT_EQ(cloned->size(), val.size());
}

// Test read from byte buffer
TEST_F(AsciiValueTest_813, ReadFromByteBuffer_813) {
    AsciiValue val;
    const byte data[] = {'T', 'e', 's', 't', '\0'};
    int result = val.read(data, sizeof(data), invalidByteOrder);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(val.size(), 5u);
}

// Test toInt64 with numeric string
TEST_F(AsciiValueTest_813, ToInt64WithNumericString_813) {
    AsciiValue val;
    val.read("42");
    int64_t result = val.toInt64(0);
    EXPECT_EQ(result, 42);
}

// Test toFloat with numeric string
TEST_F(AsciiValueTest_813, ToFloatWithNumericString_813) {
    AsciiValue val;
    val.read("3.14");
    float result = val.toFloat(0);
    EXPECT_NEAR(result, 3.14f, 0.01f);
}

// Test toUint32 with numeric string
TEST_F(AsciiValueTest_813, ToUint32WithNumericString_813) {
    AsciiValue val;
    val.read("100");
    uint32_t result = val.toUint32(0);
    EXPECT_EQ(result, 100u);
}

// Test read with a long string
TEST_F(AsciiValueTest_813, ReadLongString_813) {
    AsciiValue val;
    std::string longStr(1000, 'A');
    int result = val.read(longStr);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(val.size(), 1001u);  // 1000 'A's + null terminator
}

// Test read with string containing embedded nulls (only last matters for termination check)
TEST_F(AsciiValueTest_813, ReadStringWithEmbeddedNulls_813) {
    AsciiValue val;
    std::string buf = "AB";
    buf += '\0';
    buf += "CD";
    // buf = "AB\0CD" (size 5), does not end with \0
    int result = val.read(buf);
    EXPECT_EQ(result, 0);
    // Should append null terminator since last char is 'D'
    EXPECT_EQ(val.size(), 6u);
}

// Test that string ending with null doesn't get double null
TEST_F(AsciiValueTest_813, NoDoubleNullTerminator_813) {
    AsciiValue val;
    std::string buf = "Test";
    buf += '\0';
    val.read(buf);
    size_t firstSize = val.size();
    
    // Read again with already-terminated string
    val.read(buf);
    EXPECT_EQ(val.size(), firstSize);
}

// Test constructor with string that needs null termination
TEST_F(AsciiValueTest_813, ConstructorAppliesNullTermination_813) {
    AsciiValue val("Test");
    std::ostringstream os;
    val.write(os);
    EXPECT_EQ(os.str(), "Test");
}

// Test write after multiple reads
TEST_F(AsciiValueTest_813, WriteAfterMultipleReads_813) {
    AsciiValue val;
    val.read("First");
    val.read("Second");
    std::ostringstream os;
    val.write(os);
    EXPECT_EQ(os.str(), "Second");
}

// Test toRational with numeric string
TEST_F(AsciiValueTest_813, ToRationalWithNumericString_813) {
    AsciiValue val;
    val.read("5");
    Rational r = val.toRational(0);
    // Expected to convert "5" to some rational representation
    EXPECT_EQ(r.first, 5);
    EXPECT_EQ(r.second, 1);
}
