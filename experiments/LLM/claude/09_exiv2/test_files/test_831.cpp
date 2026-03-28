#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/value.hpp>
#include <cstring>
#include <vector>

// Test fixture for XmpValue-derived types
// Since XmpValue is abstract (has pure virtual write()), we test through concrete subclasses
// like XmpTextValue, XmpArrayValue, etc.

class XmpTextValueTest_831 : public ::testing::Test {
protected:
    void SetUp() override {
    }
};

// Test that XmpTextValue can be created and read back
TEST_F(XmpTextValueTest_831, DefaultConstructor_831) {
    Exiv2::XmpTextValue value;
    EXPECT_EQ(value.count(), 0u);
}

// Test reading a simple string value
TEST_F(XmpTextValueTest_831, ReadSimpleString_831) {
    Exiv2::XmpTextValue value;
    value.read("Hello World");
    EXPECT_EQ(value.toString(), "Hello World");
}

// Test copy method copies data to buffer correctly
TEST_F(XmpTextValueTest_831, CopyToBuffer_831) {
    Exiv2::XmpTextValue value;
    value.read("Test");
    
    std::vector<Exiv2::byte> buf(100, 0);
    size_t copied = value.copy(buf.data(), Exiv2::littleEndian);
    
    EXPECT_EQ(copied, 4u);
    EXPECT_EQ(std::string(reinterpret_cast<char*>(buf.data()), copied), "Test");
}

// Test copy method with empty value
TEST_F(XmpTextValueTest_831, CopyEmptyValue_831) {
    Exiv2::XmpTextValue value;
    value.read("");
    
    std::vector<Exiv2::byte> buf(100, 0);
    size_t copied = value.copy(buf.data(), Exiv2::littleEndian);
    
    EXPECT_EQ(copied, 0u);
}

// Test copy method returns correct size for various lengths
TEST_F(XmpTextValueTest_831, CopyReturnsSizeCorrectly_831) {
    Exiv2::XmpTextValue value;
    std::string testStr = "A longer test string with spaces and 12345";
    value.read(testStr);
    
    std::vector<Exiv2::byte> buf(200, 0);
    size_t copied = value.copy(buf.data(), Exiv2::bigEndian);
    
    EXPECT_EQ(copied, testStr.size());
    EXPECT_EQ(std::string(reinterpret_cast<char*>(buf.data()), copied), testStr);
}

// Test that byte order doesn't affect the copy for XmpTextValue
TEST_F(XmpTextValueTest_831, CopyByteOrderIndependent_831) {
    Exiv2::XmpTextValue value;
    value.read("ByteOrderTest");
    
    std::vector<Exiv2::byte> buf1(100, 0);
    std::vector<Exiv2::byte> buf2(100, 0);
    
    size_t copied1 = value.copy(buf1.data(), Exiv2::littleEndian);
    size_t copied2 = value.copy(buf2.data(), Exiv2::bigEndian);
    
    EXPECT_EQ(copied1, copied2);
    EXPECT_EQ(std::memcmp(buf1.data(), buf2.data(), copied1), 0);
}

// Test toString returns the value set via read
TEST_F(XmpTextValueTest_831, ToStringReturnsReadValue_831) {
    Exiv2::XmpTextValue value;
    value.read("some xmp text");
    EXPECT_EQ(value.toString(), "some xmp text");
}

// Test clone creates a proper copy
TEST_F(XmpTextValueTest_831, CloneCreatesProperCopy_831) {
    Exiv2::XmpTextValue value;
    value.read("cloneable");
    
    auto cloned = value.clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->toString(), "cloneable");
}

// Test reading unicode / special characters
TEST_F(XmpTextValueTest_831, ReadSpecialCharacters_831) {
    Exiv2::XmpTextValue value;
    value.read("Special: <>&\"'");
    EXPECT_EQ(value.toString(), "Special: <>&\"'");
}

// Test XmpTextValue size method
TEST_F(XmpTextValueTest_831, SizeMethod_831) {
    Exiv2::XmpTextValue value;
    value.read("12345");
    EXPECT_EQ(value.size(), 5u);
}

// Test that size returns 0 for empty value
TEST_F(XmpTextValueTest_831, SizeEmptyValue_831) {
    Exiv2::XmpTextValue value;
    value.read("");
    EXPECT_EQ(value.size(), 0u);
}

// Test copy with single character
TEST_F(XmpTextValueTest_831, CopySingleCharacter_831) {
    Exiv2::XmpTextValue value;
    value.read("X");
    
    std::vector<Exiv2::byte> buf(10, 0);
    size_t copied = value.copy(buf.data(), Exiv2::littleEndian);
    
    EXPECT_EQ(copied, 1u);
    EXPECT_EQ(buf[0], 'X');
}

// Test with XmpArrayValue
class XmpArrayValueTest_831 : public ::testing::Test {
};

TEST_F(XmpArrayValueTest_831, ReadAndToString_831) {
    Exiv2::XmpArrayValue value(Exiv2::xmpBag);
    value.read("item1");
    EXPECT_EQ(value.count(), 1u);
    EXPECT_EQ(value.toString(0), "item1");
}

TEST_F(XmpArrayValueTest_831, CopyToBuffer_831) {
    Exiv2::XmpArrayValue value(Exiv2::xmpBag);
    value.read("item1");
    
    std::vector<Exiv2::byte> buf(100, 0);
    size_t copied = value.copy(buf.data(), Exiv2::littleEndian);
    
    EXPECT_GT(copied, 0u);
}

// Test with LangAltValue
class LangAltValueTest_831 : public ::testing::Test {
};

TEST_F(LangAltValueTest_831, ReadLangAlt_831) {
    Exiv2::LangAltValue value;
    value.read("lang=\"x-default\" A default value");
    EXPECT_EQ(value.toString(), "lang=\"x-default\" A default value");
}

TEST_F(LangAltValueTest_831, CopyLangAlt_831) {
    Exiv2::LangAltValue value;
    value.read("lang=\"x-default\" Test");
    
    std::vector<Exiv2::byte> buf(200, 0);
    size_t copied = value.copy(buf.data(), Exiv2::littleEndian);
    
    EXPECT_GT(copied, 0u);
}

// Test multiple reads overwrite previous value for XmpTextValue
TEST_F(XmpTextValueTest_831, MultipleReadsOverwrite_831) {
    Exiv2::XmpTextValue value;
    value.read("first");
    EXPECT_EQ(value.toString(), "first");
    
    value.read("second");
    EXPECT_EQ(value.toString(), "second");
}

// Test copy with a large string
TEST_F(XmpTextValueTest_831, CopyLargeString_831) {
    Exiv2::XmpTextValue value;
    std::string largeStr(10000, 'A');
    value.read(largeStr);
    
    std::vector<Exiv2::byte> buf(10001, 0);
    size_t copied = value.copy(buf.data(), Exiv2::littleEndian);
    
    EXPECT_EQ(copied, 10000u);
    EXPECT_EQ(std::string(reinterpret_cast<char*>(buf.data()), copied), largeStr);
}
