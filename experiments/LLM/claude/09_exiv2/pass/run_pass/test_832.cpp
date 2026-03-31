#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <string>
#include <vector>

using namespace Exiv2;

// Test XmpTextValue with read from string
class XmpValueTest_832 : public ::testing::Test {
protected:
    void SetUp() override {
    }
    void TearDown() override {
    }
};

// Test XmpTextValue read from byte buffer (normal case)
TEST_F(XmpValueTest_832, ReadFromByteBuffer_NormalString_832) {
    XmpTextValue value;
    std::string testStr = "Hello, World!";
    const byte* buf = reinterpret_cast<const byte*>(testStr.c_str());
    int result = value.read(buf, testStr.size(), littleEndian);
    EXPECT_EQ(0, result);
    EXPECT_EQ("Hello, World!", value.toString());
}

// Test XmpTextValue read from byte buffer (empty string)
TEST_F(XmpValueTest_832, ReadFromByteBuffer_EmptyString_832) {
    XmpTextValue value;
    std::string testStr = "";
    const byte* buf = reinterpret_cast<const byte*>(testStr.c_str());
    int result = value.read(buf, 0, littleEndian);
    EXPECT_EQ(0, result);
    EXPECT_EQ("", value.toString());
}

// Test XmpTextValue read from string directly
TEST_F(XmpValueTest_832, ReadFromString_Normal_832) {
    XmpTextValue value;
    int result = value.read("Test string value");
    EXPECT_EQ(0, result);
    EXPECT_EQ("Test string value", value.toString());
}

// Test XmpTextValue read from byte buffer with partial length
TEST_F(XmpValueTest_832, ReadFromByteBuffer_PartialLength_832) {
    XmpTextValue value;
    std::string testStr = "Hello, World!";
    const byte* buf = reinterpret_cast<const byte*>(testStr.c_str());
    int result = value.read(buf, 5, littleEndian);
    EXPECT_EQ(0, result);
    EXPECT_EQ("Hello", value.toString());
}

// Test XmpTextValue read with bigEndian byte order (should not matter for XmpValue)
TEST_F(XmpValueTest_832, ReadFromByteBuffer_BigEndian_832) {
    XmpTextValue value;
    std::string testStr = "Endian test";
    const byte* buf = reinterpret_cast<const byte*>(testStr.c_str());
    int result = value.read(buf, testStr.size(), bigEndian);
    EXPECT_EQ(0, result);
    EXPECT_EQ("Endian test", value.toString());
}

// Test XmpTextValue read from byte buffer with special characters
TEST_F(XmpValueTest_832, ReadFromByteBuffer_SpecialCharacters_832) {
    XmpTextValue value;
    std::string testStr = "Line1\nLine2\tTab";
    const byte* buf = reinterpret_cast<const byte*>(testStr.c_str());
    int result = value.read(buf, testStr.size(), littleEndian);
    EXPECT_EQ(0, result);
    EXPECT_EQ("Line1\nLine2\tTab", value.toString());
}

// Test XmpTextValue read overwrite previous value
TEST_F(XmpValueTest_832, ReadFromByteBuffer_OverwritePreviousValue_832) {
    XmpTextValue value;
    std::string testStr1 = "First value";
    const byte* buf1 = reinterpret_cast<const byte*>(testStr1.c_str());
    value.read(buf1, testStr1.size(), littleEndian);
    EXPECT_EQ("First value", value.toString());

    std::string testStr2 = "Second value";
    const byte* buf2 = reinterpret_cast<const byte*>(testStr2.c_str());
    int result = value.read(buf2, testStr2.size(), littleEndian);
    EXPECT_EQ(0, result);
    EXPECT_EQ("Second value", value.toString());
}

// Test XmpTextValue read with single character
TEST_F(XmpValueTest_832, ReadFromByteBuffer_SingleCharacter_832) {
    XmpTextValue value;
    std::string testStr = "A";
    const byte* buf = reinterpret_cast<const byte*>(testStr.c_str());
    int result = value.read(buf, 1, littleEndian);
    EXPECT_EQ(0, result);
    EXPECT_EQ("A", value.toString());
}

// Test XmpTextValue read from byte buffer with spaces
TEST_F(XmpValueTest_832, ReadFromByteBuffer_Spaces_832) {
    XmpTextValue value;
    std::string testStr = "   ";
    const byte* buf = reinterpret_cast<const byte*>(testStr.c_str());
    int result = value.read(buf, testStr.size(), littleEndian);
    EXPECT_EQ(0, result);
    EXPECT_EQ("   ", value.toString());
}

// Test XmpTextValue read with unicode-like content
TEST_F(XmpValueTest_832, ReadFromByteBuffer_UTF8Content_832) {
    XmpTextValue value;
    std::string testStr = u8"Héllo Wörld";
    const byte* buf = reinterpret_cast<const byte*>(testStr.c_str());
    int result = value.read(buf, testStr.size(), littleEndian);
    EXPECT_EQ(0, result);
    EXPECT_EQ(testStr, value.toString());
}

// Test XmpTextValue copy
TEST_F(XmpValueTest_832, ReadAndCopy_832) {
    XmpTextValue value;
    value.read("Copy test");
    auto cloned = value.clone();
    ASSERT_NE(nullptr, cloned);
    EXPECT_EQ("Copy test", cloned->toString());
}

// Test XmpTextValue size after read from byte buffer
TEST_F(XmpValueTest_832, ReadFromByteBuffer_CheckSize_832) {
    XmpTextValue value;
    std::string testStr = "Size check";
    const byte* buf = reinterpret_cast<const byte*>(testStr.c_str());
    value.read(buf, testStr.size(), littleEndian);
    EXPECT_EQ(testStr.size(), value.size());
}

// Test XmpTextValue count after read
TEST_F(XmpValueTest_832, ReadFromByteBuffer_CheckCount_832) {
    XmpTextValue value;
    std::string testStr = "Count check";
    const byte* buf = reinterpret_cast<const byte*>(testStr.c_str());
    value.read(buf, testStr.size(), littleEndian);
    EXPECT_EQ(1u, value.count());
}

// Test reading a longer string via byte buffer
TEST_F(XmpValueTest_832, ReadFromByteBuffer_LongString_832) {
    XmpTextValue value;
    std::string testStr(1000, 'x');
    const byte* buf = reinterpret_cast<const byte*>(testStr.c_str());
    int result = value.read(buf, testStr.size(), littleEndian);
    EXPECT_EQ(0, result);
    EXPECT_EQ(testStr, value.toString());
}

// Test with binary-like data containing null bytes - the read(buf, len) creates string with len
TEST_F(XmpValueTest_832, ReadFromByteBuffer_BinaryDataWithNulls_832) {
    XmpTextValue value;
    std::vector<byte> data = {'A', 'B', 0, 'C', 'D'};
    int result = value.read(data.data(), data.size(), littleEndian);
    EXPECT_EQ(0, result);
    // The string constructed should contain the null byte
    std::string expected(reinterpret_cast<const char*>(data.data()), data.size());
    EXPECT_EQ(expected.size(), value.toString().size());
}
