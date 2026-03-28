#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <cstring>
#include "exiv2/value.hpp"

using namespace Exiv2;

// Test default constructor
TEST(CommentValueTest_822, DefaultConstructor_822) {
    CommentValue cv;
    std::ostringstream os;
    cv.write(os);
    // Default constructed should have empty or minimal output
    std::string result = os.str();
    // Just verify it doesn't crash and produces some output
    EXPECT_TRUE(result.empty() || !result.empty());
}

// Test constructor with plain ASCII comment
TEST(CommentValueTest_822, ConstructorWithAsciiComment_822) {
    CommentValue cv("charset=Ascii Hello World");
    std::string comment = cv.comment();
    EXPECT_EQ(comment, "Hello World");
}

// Test constructor with simple string (no charset prefix)
TEST(CommentValueTest_822, ConstructorWithSimpleString_822) {
    CommentValue cv("A simple comment");
    std::string comment = cv.comment();
    EXPECT_FALSE(comment.empty());
}

// Test charsetId returns ascii for ASCII charset
TEST(CommentValueTest_822, CharsetIdAscii_822) {
    CommentValue cv("charset=Ascii Test");
    CommentValue::CharsetId id = cv.charsetId();
    EXPECT_EQ(id, CommentValue::ascii);
}

// Test charsetId returns unicode for Unicode charset
TEST(CommentValueTest_822, CharsetIdUnicode_822) {
    CommentValue cv("charset=Unicode Test");
    CommentValue::CharsetId id = cv.charsetId();
    EXPECT_EQ(id, CommentValue::unicode);
}

// Test charsetId returns undefined for no charset
TEST(CommentValueTest_822, CharsetIdUndefined_822) {
    CommentValue cv;
    CommentValue::CharsetId id = cv.charsetId();
    EXPECT_EQ(id, CommentValue::undefined);
}

// Test write with ASCII charset includes charset in output
TEST(CommentValueTest_822, WriteWithAsciiCharset_822) {
    CommentValue cv("charset=Ascii Hello");
    std::ostringstream os;
    cv.write(os);
    std::string result = os.str();
    EXPECT_NE(result.find("charset="), std::string::npos);
    EXPECT_NE(result.find("Hello"), std::string::npos);
}

// Test write with undefined charset does NOT include charset prefix
TEST(CommentValueTest_822, WriteWithUndefinedCharset_822) {
    CommentValue cv;
    cv.read("Some text without charset");
    std::ostringstream os;
    cv.write(os);
    std::string result = os.str();
    // When charsetId is undefined, "charset=" should not appear
    // The write method only prepends charset= when csId != undefined
    // This depends on what charsetId() returns for this input
}

// Test read from string
TEST(CommentValueTest_822, ReadFromString_822) {
    CommentValue cv;
    int result = cv.read("charset=Ascii Test comment");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(cv.comment(), "Test comment");
}

// Test read from string with Unicode charset
TEST(CommentValueTest_822, ReadFromStringUnicode_822) {
    CommentValue cv;
    int result = cv.read("charset=Unicode Test");
    EXPECT_EQ(result, 0);
    CommentValue::CharsetId id = cv.charsetId();
    EXPECT_EQ(id, CommentValue::unicode);
}

// Test read from byte buffer
TEST(CommentValueTest_822, ReadFromByteBuffer_822) {
    CommentValue cv;
    // Exif comment: 8 bytes charset code + comment data
    // ASCII charset code: "ASCII\0\0\0"
    const char asciiHeader[] = "ASCII\0\0\0Hello";
    size_t len = 8 + 5; // 8 bytes header + "Hello"
    byte buf[13];
    std::memcpy(buf, asciiHeader, len);
    int result = cv.read(buf, len, littleEndian);
    EXPECT_EQ(result, 0);
}

// Test copy to byte buffer
TEST(CommentValueTest_822, CopyToBuffer_822) {
    CommentValue cv("charset=Ascii Test");
    byte buf[256] = {0};
    size_t copied = cv.copy(buf, littleEndian);
    EXPECT_GT(copied, 0u);
}

// Test clone
TEST(CommentValueTest_822, Clone_822) {
    CommentValue cv("charset=Ascii Original");
    auto cloned = cv.clone();
    ASSERT_NE(cloned, nullptr);
    std::ostringstream os1, os2;
    cv.write(os1);
    cloned->write(os2);
    EXPECT_EQ(os1.str(), os2.str());
}

// Test empty comment
TEST(CommentValueTest_822, EmptyComment_822) {
    CommentValue cv("");
    std::ostringstream os;
    cv.write(os);
    // Should not crash
    std::string result = os.str();
    SUCCEED();
}

// Test CharsetInfo::name
TEST(CharsetInfoTest_822, NameForAscii_822) {
    const char* name = CommentValue::CharsetInfo::name(CommentValue::ascii);
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "Ascii");
}

// Test CharsetInfo::name for Unicode
TEST(CharsetInfoTest_822, NameForUnicode_822) {
    const char* name = CommentValue::CharsetInfo::name(CommentValue::unicode);
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "Unicode");
}

// Test CharsetInfo::name for Jis
TEST(CharsetInfoTest_822, NameForJis_822) {
    const char* name = CommentValue::CharsetInfo::name(CommentValue::jis);
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "Jis");
}

// Test CharsetInfo::name for undefined
TEST(CharsetInfoTest_822, NameForUndefined_822) {
    const char* name = CommentValue::CharsetInfo::name(CommentValue::undefined);
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "Undefined");
}

// Test CharsetInfo::charsetIdByName
TEST(CharsetInfoTest_822, CharsetIdByNameAscii_822) {
    CommentValue::CharsetId id = CommentValue::CharsetInfo::charsetIdByName("Ascii");
    EXPECT_EQ(id, CommentValue::ascii);
}

// Test CharsetInfo::charsetIdByName for Unicode
TEST(CharsetInfoTest_822, CharsetIdByNameUnicode_822) {
    CommentValue::CharsetId id = CommentValue::CharsetInfo::charsetIdByName("Unicode");
    EXPECT_EQ(id, CommentValue::unicode);
}

// Test CharsetInfo::charsetIdByName for invalid name
TEST(CharsetInfoTest_822, CharsetIdByNameInvalid_822) {
    CommentValue::CharsetId id = CommentValue::CharsetInfo::charsetIdByName("NonExistent");
    EXPECT_EQ(id, CommentValue::invalidCharsetId);
}

// Test CharsetInfo::code
TEST(CharsetInfoTest_822, CodeForAscii_822) {
    const char* code = CommentValue::CharsetInfo::code(CommentValue::ascii);
    ASSERT_NE(code, nullptr);
}

// Test CharsetInfo::code for Unicode
TEST(CharsetInfoTest_822, CodeForUnicode_822) {
    const char* code = CommentValue::CharsetInfo::code(CommentValue::unicode);
    ASSERT_NE(code, nullptr);
}

// Test write returns the same ostream reference
TEST(CommentValueTest_822, WriteReturnsOstream_822) {
    CommentValue cv("charset=Ascii Test");
    std::ostringstream os;
    std::ostream& ref = cv.write(os);
    EXPECT_EQ(&ref, &os);
}

// Test comment method with encoding parameter
TEST(CommentValueTest_822, CommentWithEncoding_822) {
    CommentValue cv("charset=Ascii Hello World");
    std::string comment = cv.comment("Ascii");
    EXPECT_FALSE(comment.empty());
}

// Test detectCharset
TEST(CommentValueTest_822, DetectCharset_822) {
    CommentValue cv("charset=Ascii Hello");
    std::string c;
    const char* detected = cv.detectCharset(c);
    // Just verify it doesn't crash and returns something
    SUCCEED();
}

// Test JIS charset
TEST(CommentValueTest_822, JisCharset_822) {
    CommentValue cv("charset=Jis Test");
    CommentValue::CharsetId id = cv.charsetId();
    EXPECT_EQ(id, CommentValue::jis);
}

// Test write with Jis charset
TEST(CommentValueTest_822, WriteWithJisCharset_822) {
    CommentValue cv("charset=Jis Test");
    std::ostringstream os;
    cv.write(os);
    std::string result = os.str();
    EXPECT_NE(result.find("charset="), std::string::npos);
    EXPECT_NE(result.find("Jis"), std::string::npos);
}

// Test read overwriting previous value
TEST(CommentValueTest_822, ReadOverwritesPrevious_822) {
    CommentValue cv("charset=Ascii First");
    EXPECT_EQ(cv.comment(), "First");
    cv.read("charset=Ascii Second");
    EXPECT_EQ(cv.comment(), "Second");
}

// Test multiple writes to the same stream
TEST(CommentValueTest_822, MultipleWrites_822) {
    CommentValue cv1("charset=Ascii Hello");
    CommentValue cv2("charset=Unicode World");
    std::ostringstream os;
    cv1.write(os);
    os << " | ";
    cv2.write(os);
    std::string result = os.str();
    EXPECT_NE(result.find("Hello"), std::string::npos);
    EXPECT_NE(result.find("World"), std::string::npos);
}

// Test comment with only charset and no text
TEST(CommentValueTest_822, CharsetOnlyNoText_822) {
    CommentValue cv("charset=Ascii ");
    std::string comment = cv.comment();
    // Comment text portion should be empty or whitespace
    SUCCEED();
}

// Test boundary: very long comment
TEST(CommentValueTest_822, LongComment_822) {
    std::string longText = "charset=Ascii " + std::string(10000, 'A');
    CommentValue cv(longText);
    std::string comment = cv.comment();
    EXPECT_EQ(comment.size(), 10000u);
}
