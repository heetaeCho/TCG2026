#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <cstring>
#include <sstream>

using namespace Exiv2;

// StringValueBase is abstract-ish but we can use StringValue (a concrete subclass)
// or we can use AsciiValue. Let's check what concrete classes exist.
// StringValue and AsciiValue are typical concrete subclasses of StringValueBase.
// We'll use StringValue for testing.

class StringValueBaseTest_129 : public ::testing::Test {
protected:
    void SetUp() override {
    }
    void TearDown() override {
    }
};

TEST_F(StringValueBaseTest_129, ConstructorWithEmptyString_129) {
    StringValue val("");
    EXPECT_EQ(val.size(), 0u);
    EXPECT_EQ(val.count(), 0u);
}

TEST_F(StringValueBaseTest_129, ConstructorWithNonEmptyString_129) {
    StringValue val("Hello World");
    EXPECT_EQ(val.size(), 11u);
    EXPECT_EQ(val.count(), 11u);
}

TEST_F(StringValueBaseTest_129, ReadFromString_129) {
    StringValue val("");
    int result = val.read("Test String");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(val.size(), 11u);
}

TEST_F(StringValueBaseTest_129, ReadFromEmptyString_129) {
    StringValue val("initial");
    int result = val.read("");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(val.size(), 0u);
}

TEST_F(StringValueBaseTest_129, ReadFromByteBuffer_129) {
    StringValue val("");
    const byte buf[] = "Hello";
    int result = val.read(buf, 5, littleEndian);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(val.size(), 5u);
}

TEST_F(StringValueBaseTest_129, ReadFromByteBufferZeroLength_129) {
    StringValue val("initial");
    const byte buf[] = "Hello";
    int result = val.read(buf, 0, littleEndian);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(val.size(), 0u);
}

TEST_F(StringValueBaseTest_129, CopyToBuffer_129) {
    StringValue val("ABCDE");
    byte buf[10] = {0};
    size_t copied = val.copy(buf, littleEndian);
    EXPECT_EQ(copied, 5u);
    EXPECT_EQ(std::string(reinterpret_cast<char*>(buf), 5), "ABCDE");
}

TEST_F(StringValueBaseTest_129, CopyEmptyValue_129) {
    StringValue val("");
    byte buf[10] = {0};
    size_t copied = val.copy(buf, littleEndian);
    EXPECT_EQ(copied, 0u);
}

TEST_F(StringValueBaseTest_129, CountMatchesSize_129) {
    StringValue val("Test");
    EXPECT_EQ(val.count(), val.size());
}

TEST_F(StringValueBaseTest_129, SizeReturnsCorrectLength_129) {
    StringValue val("12345");
    EXPECT_EQ(val.size(), 5u);
}

TEST_F(StringValueBaseTest_129, WriteToStream_129) {
    StringValue val("Hello");
    std::ostringstream os;
    val.write(os);
    EXPECT_EQ(os.str(), "Hello");
}

TEST_F(StringValueBaseTest_129, WriteEmptyToStream_129) {
    StringValue val("");
    std::ostringstream os;
    val.write(os);
    EXPECT_EQ(os.str(), "");
}

TEST_F(StringValueBaseTest_129, ToInt64WithNumericString_129) {
    StringValue val("42");
    int64_t result = val.toInt64(0);
    EXPECT_EQ(result, 42);
}

TEST_F(StringValueBaseTest_129, ToInt64WithNonNumericString_129) {
    StringValue val("abc");
    int64_t result = val.toInt64(0);
    EXPECT_EQ(result, 0);
}

TEST_F(StringValueBaseTest_129, ToUint32WithNumericString_129) {
    StringValue val("123");
    uint32_t result = val.toUint32(0);
    EXPECT_EQ(result, 123u);
}

TEST_F(StringValueBaseTest_129, ToUint32WithNonNumericString_129) {
    StringValue val("xyz");
    uint32_t result = val.toUint32(0);
    EXPECT_EQ(result, 0u);
}

TEST_F(StringValueBaseTest_129, ToFloatWithNumericString_129) {
    StringValue val("3.14");
    float result = val.toFloat(0);
    EXPECT_NEAR(result, 3.14f, 0.01f);
}

TEST_F(StringValueBaseTest_129, ToFloatWithNonNumericString_129) {
    StringValue val("notanumber");
    float result = val.toFloat(0);
    EXPECT_FLOAT_EQ(result, 0.0f);
}

TEST_F(StringValueBaseTest_129, ToRationalWithNumericString_129) {
    StringValue val("5");
    Rational result = val.toRational(0);
    EXPECT_EQ(result.first, 5);
    EXPECT_EQ(result.second, 1);
}

TEST_F(StringValueBaseTest_129, CloneReturnsValidCopy_129) {
    StringValue val("CloneMe");
    auto cloned = val.clone();
    ASSERT_NE(cloned, nullptr);
    
    std::ostringstream os1, os2;
    val.write(os1);
    cloned->write(os2);
    EXPECT_EQ(os1.str(), os2.str());
}

TEST_F(StringValueBaseTest_129, CloneIsIndependent_129) {
    StringValue val("Original");
    auto cloned = val.clone();
    
    // Modify original
    val.read("Modified");
    
    std::ostringstream osCloned;
    cloned->write(osCloned);
    EXPECT_EQ(osCloned.str(), "Original");
    
    std::ostringstream osOriginal;
    val.write(osOriginal);
    EXPECT_EQ(osOriginal.str(), "Modified");
}

TEST_F(StringValueBaseTest_129, ReadOverwritesPreviousValue_129) {
    StringValue val("First");
    EXPECT_EQ(val.size(), 5u);
    
    val.read("SecondValue");
    EXPECT_EQ(val.size(), 11u);
    
    std::ostringstream os;
    val.write(os);
    EXPECT_EQ(os.str(), "SecondValue");
}

TEST_F(StringValueBaseTest_129, ReadByteBufferBigEndian_129) {
    StringValue val("");
    const byte buf[] = "BigEndianTest";
    int result = val.read(buf, 13, bigEndian);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(val.size(), 13u);
    
    std::ostringstream os;
    val.write(os);
    EXPECT_EQ(os.str(), "BigEndianTest");
}

TEST_F(StringValueBaseTest_129, CopyByteOrderIndependent_129) {
    StringValue val("ByteOrder");
    byte buf1[20] = {0};
    byte buf2[20] = {0};
    
    size_t copied1 = val.copy(buf1, littleEndian);
    size_t copied2 = val.copy(buf2, bigEndian);
    
    EXPECT_EQ(copied1, copied2);
    EXPECT_EQ(std::memcmp(buf1, buf2, copied1), 0);
}

TEST_F(StringValueBaseTest_129, LongStringValue_129) {
    std::string longStr(1000, 'x');
    StringValue val(longStr);
    EXPECT_EQ(val.size(), 1000u);
    EXPECT_EQ(val.count(), 1000u);
    
    std::ostringstream os;
    val.write(os);
    EXPECT_EQ(os.str(), longStr);
}

TEST_F(StringValueBaseTest_129, StringWithSpecialCharacters_129) {
    StringValue val("Hello\tWorld\n");
    EXPECT_EQ(val.size(), 12u);
    
    std::ostringstream os;
    val.write(os);
    EXPECT_EQ(os.str(), "Hello\tWorld\n");
}

TEST_F(StringValueBaseTest_129, ToInt64WithNegativeNumber_129) {
    StringValue val("-100");
    int64_t result = val.toInt64(0);
    EXPECT_EQ(result, -100);
}

TEST_F(StringValueBaseTest_129, ValueMemberAccess_129) {
    StringValue val("DirectAccess");
    EXPECT_EQ(val.value_, "DirectAccess");
}

TEST_F(StringValueBaseTest_129, ValueMemberAfterRead_129) {
    StringValue val("");
    val.read("Updated");
    EXPECT_EQ(val.value_, "Updated");
}

TEST_F(StringValueBaseTest_129, AsciiValueBasicTest_129) {
    AsciiValue val("AsciiTest");
    EXPECT_EQ(val.size(), 9u);
    
    std::ostringstream os;
    val.write(os);
    EXPECT_EQ(os.str(), "AsciiTest");
}

TEST_F(StringValueBaseTest_129, ToInt64WithLeadingSpaces_129) {
    StringValue val("  42");
    int64_t result = val.toInt64(0);
    // Behavior depends on implementation - strtol typically handles leading spaces
    EXPECT_EQ(result, 42);
}

TEST_F(StringValueBaseTest_129, SingleCharacterString_129) {
    StringValue val("A");
    EXPECT_EQ(val.size(), 1u);
    EXPECT_EQ(val.count(), 1u);
    
    byte buf[2] = {0};
    size_t copied = val.copy(buf, littleEndian);
    EXPECT_EQ(copied, 1u);
    EXPECT_EQ(buf[0], 'A');
}
