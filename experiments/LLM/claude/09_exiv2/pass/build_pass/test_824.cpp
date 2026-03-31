#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <sstream>
#include <string>
#include <cstring>

using namespace Exiv2;

// ============================================================
// Tests for CommentValue::charsetId()
// ============================================================

class CommentValueCharsetIdTest_824 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test default constructed CommentValue has undefined charsetId
TEST_F(CommentValueCharsetIdTest_824, DefaultConstructedHasUndefinedCharsetId_824) {
    CommentValue cv;
    EXPECT_EQ(CommentValue::undefined, cv.charsetId());
}

// Test CommentValue with ASCII charset prefix
TEST_F(CommentValueCharsetIdTest_824, AsciiCharsetId_824) {
    CommentValue cv;
    // ASCII charset code is "ASCII\0\0\0" (8 bytes)
    const char* asciiCode = CommentValue::CharsetInfo::code(CommentValue::ascii);
    ASSERT_NE(nullptr, asciiCode);
    std::string asciiPrefix(asciiCode, 8);
    std::string fullComment = asciiPrefix + "Hello World";
    
    // Use byte-based read to set raw value
    cv.read(reinterpret_cast<const Exiv2::byte*>(fullComment.data()), fullComment.size(), littleEndian);
    EXPECT_EQ(CommentValue::ascii, cv.charsetId());
}

// Test CommentValue with Unicode charset prefix
TEST_F(CommentValueCharsetIdTest_824, UnicodeCharsetId_824) {
    CommentValue cv;
    const char* unicodeCode = CommentValue::CharsetInfo::code(CommentValue::unicode);
    ASSERT_NE(nullptr, unicodeCode);
    std::string unicodePrefix(unicodeCode, 8);
    std::string fullComment = unicodePrefix + "Some unicode text";
    
    cv.read(reinterpret_cast<const Exiv2::byte*>(fullComment.data()), fullComment.size(), littleEndian);
    EXPECT_EQ(CommentValue::unicode, cv.charsetId());
}

// Test CommentValue with JIS charset prefix
TEST_F(CommentValueCharsetIdTest_824, JisCharsetId_824) {
    CommentValue cv;
    const char* jisCode = CommentValue::CharsetInfo::code(CommentValue::jis);
    ASSERT_NE(nullptr, jisCode);
    std::string jisPrefix(jisCode, 8);
    std::string fullComment = jisPrefix + "Some JIS text";
    
    cv.read(reinterpret_cast<const Exiv2::byte*>(fullComment.data()), fullComment.size(), littleEndian);
    EXPECT_EQ(CommentValue::jis, cv.charsetId());
}

// Test CommentValue with undefined charset prefix
TEST_F(CommentValueCharsetIdTest_824, UndefinedCharsetId_824) {
    CommentValue cv;
    const char* undefinedCode = CommentValue::CharsetInfo::code(CommentValue::undefined);
    ASSERT_NE(nullptr, undefinedCode);
    std::string undefinedPrefix(undefinedCode, 8);
    std::string fullComment = undefinedPrefix + "Some text";
    
    cv.read(reinterpret_cast<const Exiv2::byte*>(fullComment.data()), fullComment.size(), littleEndian);
    EXPECT_EQ(CommentValue::undefined, cv.charsetId());
}

// Test CommentValue with value shorter than 8 bytes returns undefined
TEST_F(CommentValueCharsetIdTest_824, ShortValueReturnsUndefined_824) {
    CommentValue cv;
    std::string shortVal = "SHORT";  // less than 8 bytes
    cv.read(reinterpret_cast<const Exiv2::byte*>(shortVal.data()), shortVal.size(), littleEndian);
    EXPECT_EQ(CommentValue::undefined, cv.charsetId());
}

// Test CommentValue with exactly 8 bytes of unrecognized code
TEST_F(CommentValueCharsetIdTest_824, UnrecognizedCodeReturnsInvalidOrUndefined_824) {
    CommentValue cv;
    std::string garbage = "XXXXXXXX";  // 8 bytes, not a valid charset code
    cv.read(reinterpret_cast<const Exiv2::byte*>(garbage.data()), garbage.size(), littleEndian);
    // Should return invalidCharsetId or undefined depending on implementation
    CommentValue::CharsetId id = cv.charsetId();
    // The value should not be ascii, jis, or unicode
    EXPECT_NE(CommentValue::ascii, id);
    EXPECT_NE(CommentValue::jis, id);
    EXPECT_NE(CommentValue::unicode, id);
}

// Test empty value returns undefined charset
TEST_F(CommentValueCharsetIdTest_824, EmptyValueReturnsUndefined_824) {
    CommentValue cv;
    // Don't read anything, value_ should be empty
    EXPECT_EQ(CommentValue::undefined, cv.charsetId());
}

// Test CommentValue with exactly 7 bytes returns undefined
TEST_F(CommentValueCharsetIdTest_824, SevenBytesReturnsUndefined_824) {
    CommentValue cv;
    std::string sevenBytes = "1234567";  // exactly 7 bytes
    cv.read(reinterpret_cast<const Exiv2::byte*>(sevenBytes.data()), sevenBytes.size(), littleEndian);
    EXPECT_EQ(CommentValue::undefined, cv.charsetId());
}

// Test CommentValue with exactly 8 bytes (valid ascii code, no trailing text)
TEST_F(CommentValueCharsetIdTest_824, ExactlyEightBytesAsciiCode_824) {
    CommentValue cv;
    const char* asciiCode = CommentValue::CharsetInfo::code(CommentValue::ascii);
    ASSERT_NE(nullptr, asciiCode);
    std::string exactEight(asciiCode, 8);
    
    cv.read(reinterpret_cast<const Exiv2::byte*>(exactEight.data()), exactEight.size(), littleEndian);
    EXPECT_EQ(CommentValue::ascii, cv.charsetId());
}

// ============================================================
// Tests for CharsetInfo static methods
// ============================================================

class CharsetInfoTest_824 : public ::testing::Test {};

TEST_F(CharsetInfoTest_824, NameReturnsNonNullForValidIds_824) {
    EXPECT_NE(nullptr, CommentValue::CharsetInfo::name(CommentValue::ascii));
    EXPECT_NE(nullptr, CommentValue::CharsetInfo::name(CommentValue::jis));
    EXPECT_NE(nullptr, CommentValue::CharsetInfo::name(CommentValue::unicode));
    EXPECT_NE(nullptr, CommentValue::CharsetInfo::name(CommentValue::undefined));
}

TEST_F(CharsetInfoTest_824, CodeReturnsNonNullForValidIds_824) {
    EXPECT_NE(nullptr, CommentValue::CharsetInfo::code(CommentValue::ascii));
    EXPECT_NE(nullptr, CommentValue::CharsetInfo::code(CommentValue::jis));
    EXPECT_NE(nullptr, CommentValue::CharsetInfo::code(CommentValue::unicode));
    EXPECT_NE(nullptr, CommentValue::CharsetInfo::code(CommentValue::undefined));
}

TEST_F(CharsetInfoTest_824, CharsetIdByNameRoundTrip_824) {
    const char* asciiName = CommentValue::CharsetInfo::name(CommentValue::ascii);
    ASSERT_NE(nullptr, asciiName);
    EXPECT_EQ(CommentValue::ascii, CommentValue::CharsetInfo::charsetIdByName(asciiName));
}

TEST_F(CharsetInfoTest_824, CharsetIdByCodeRoundTrip_824) {
    const char* asciiCode = CommentValue::CharsetInfo::code(CommentValue::ascii);
    ASSERT_NE(nullptr, asciiCode);
    std::string codeStr(asciiCode, 8);
    EXPECT_EQ(CommentValue::ascii, CommentValue::CharsetInfo::charsetIdByCode(codeStr));
}

TEST_F(CharsetInfoTest_824, InvalidNameReturnsInvalidCharsetId_824) {
    CommentValue::CharsetId id = CommentValue::CharsetInfo::charsetIdByName("nonexistent_charset");
    EXPECT_EQ(CommentValue::invalidCharsetId, id);
}

TEST_F(CharsetInfoTest_824, InvalidCodeReturnsInvalidCharsetId_824) {
    CommentValue::CharsetId id = CommentValue::CharsetInfo::charsetIdByCode("XXXXXXXX");
    EXPECT_EQ(CommentValue::invalidCharsetId, id);
}

// ============================================================
// Tests for CommentValue string-based constructor and read
// ============================================================

class CommentValueReadWriteTest_824 : public ::testing::Test {};

TEST_F(CommentValueReadWriteTest_824, StringConstructorWithCharsetPrefix_824) {
    CommentValue cv("charset=Ascii Hello World");
    EXPECT_EQ(CommentValue::ascii, cv.charsetId());
}

TEST_F(CommentValueReadWriteTest_824, StringConstructorWithoutCharsetPrefix_824) {
    CommentValue cv("Hello World");
    // Without charset prefix, should default to undefined
    CommentValue::CharsetId id = cv.charsetId();
    EXPECT_EQ(CommentValue::undefined, id);
}

TEST_F(CommentValueReadWriteTest_824, ReadStringMethod_824) {
    CommentValue cv;
    cv.read("charset=Ascii Test comment");
    EXPECT_EQ(CommentValue::ascii, cv.charsetId());
}

TEST_F(CommentValueReadWriteTest_824, WriteToStream_824) {
    CommentValue cv("charset=Ascii Hello");
    std::ostringstream os;
    cv.write(os);
    std::string output = os.str();
    // The output should contain the comment text
    EXPECT_FALSE(output.empty());
}

TEST_F(CommentValueReadWriteTest_824, CommentMethodReturnsText_824) {
    CommentValue cv("charset=Ascii Hello World");
    std::string c = cv.comment();
    // Should return the comment part
    EXPECT_FALSE(c.empty());
}

TEST_F(CommentValueReadWriteTest_824, CopyMethod_824) {
    CommentValue cv("charset=Ascii Hello");
    size_t sz = cv.size();
    ASSERT_GT(sz, 0u);
    std::vector<Exiv2::byte> buf(sz);
    size_t copied = cv.copy(buf.data(), littleEndian);
    EXPECT_EQ(sz, copied);
}

TEST_F(CommentValueReadWriteTest_824, SizeMethod_824) {
    CommentValue cv;
    EXPECT_EQ(0u, cv.size());
    
    cv.read("charset=Ascii Test");
    EXPECT_GT(cv.size(), 0u);
}

TEST_F(CommentValueReadWriteTest_824, CountMethod_824) {
    CommentValue cv("charset=Ascii Test");
    EXPECT_GT(cv.count(), 0u);
}

TEST_F(CommentValueReadWriteTest_824, CloneMethod_824) {
    CommentValue cv("charset=Ascii Clone test");
    auto cloned = cv.clone();
    ASSERT_NE(nullptr, cloned);
}

TEST_F(CommentValueReadWriteTest_824, UnicodeCharsetViaString_824) {
    CommentValue cv("charset=Unicode Hello");
    EXPECT_EQ(CommentValue::unicode, cv.charsetId());
}

TEST_F(CommentValueReadWriteTest_824, JisCharsetViaString_824) {
    CommentValue cv("charset=Jis Hello");
    EXPECT_EQ(CommentValue::jis, cv.charsetId());
}

TEST_F(CommentValueReadWriteTest_824, EmptyComment_824) {
    CommentValue cv("");
    EXPECT_EQ(CommentValue::undefined, cv.charsetId());
}

TEST_F(CommentValueReadWriteTest_824, DetectCharset_824) {
    CommentValue cv("charset=Ascii Test for detect");
    std::string c;
    const char* result = cv.detectCharset(c);
    // result may or may not be null, but this should not crash
    (void)result;
}
