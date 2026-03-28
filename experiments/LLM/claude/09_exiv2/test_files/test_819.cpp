#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/value.hpp>
#include <exiv2/error.hpp>
#include <exiv2/types.hpp>
#include <sstream>
#include <string>

namespace {

class CommentValueTest_819 : public ::testing::Test {
protected:
    void SetUp() override {
        // Suppress warnings during tests to avoid noise
        Exiv2::LogMsg::setLevel(Exiv2::LogMsg::mute);
    }

    void TearDown() override {
        Exiv2::LogMsg::setLevel(Exiv2::LogMsg::warn);
    }
};

// Test default constructor creates a valid CommentValue
TEST_F(CommentValueTest_819, DefaultConstructor_819) {
    Exiv2::CommentValue cv;
    EXPECT_EQ(cv.size(), 8u); // Should have 8-byte charset code for undefined
}

// Test constructor with a plain string (no charset prefix)
TEST_F(CommentValueTest_819, ConstructorWithPlainString_819) {
    Exiv2::CommentValue cv("Hello World");
    // The value should contain 8-byte charset code + the comment text
    EXPECT_GE(cv.size(), 8u + 11u);
}

// Test read with a simple comment (no charset specification)
TEST_F(CommentValueTest_819, ReadPlainComment_819) {
    Exiv2::CommentValue cv;
    int result = cv.read("Hello World");
    EXPECT_EQ(result, 0);
    EXPECT_GE(cv.size(), 8u + 11u);
}

// Test read with charset=Ascii prefix
TEST_F(CommentValueTest_819, ReadCharsetAscii_819) {
    Exiv2::CommentValue cv;
    int result = cv.read("charset=Ascii Hello ASCII");
    EXPECT_EQ(result, 0);
    std::string comment = cv.comment();
    EXPECT_EQ(comment, "Hello ASCII");
}

// Test read with charset=Unicode prefix
TEST_F(CommentValueTest_819, ReadCharsetUnicode_819) {
    Exiv2::CommentValue cv;
    int result = cv.read("charset=Unicode Hello Unicode");
    EXPECT_EQ(result, 0);
}

// Test read with charset=Jis prefix
TEST_F(CommentValueTest_819, ReadCharsetJis_819) {
    Exiv2::CommentValue cv;
    int result = cv.read("charset=Jis Hello JIS");
    EXPECT_EQ(result, 0);
}

// Test read with charset=Undefined prefix
TEST_F(CommentValueTest_819, ReadCharsetUndefined_819) {
    Exiv2::CommentValue cv;
    int result = cv.read("charset=Undefined Hello Undefined");
    EXPECT_EQ(result, 0);
}

// Test read with an invalid charset returns error (1)
TEST_F(CommentValueTest_819, ReadInvalidCharset_819) {
    Exiv2::CommentValue cv;
    int result = cv.read("charset=InvalidCharset Some text");
    EXPECT_EQ(result, 1);
}

// Test read with empty comment
TEST_F(CommentValueTest_819, ReadEmptyComment_819) {
    Exiv2::CommentValue cv;
    int result = cv.read("");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(cv.size(), 8u); // Only charset code, no text
}

// Test read with charset= but no space after charset name (entire string is charset spec)
TEST_F(CommentValueTest_819, ReadCharsetNoSpaceAfter_819) {
    Exiv2::CommentValue cv;
    int result = cv.read("charset=Ascii");
    EXPECT_EQ(result, 0);
    // No space found, so comment part should be empty
    EXPECT_EQ(cv.size(), 8u);
}

// Test read with charset name in quotes
TEST_F(CommentValueTest_819, ReadCharsetQuoted_819) {
    Exiv2::CommentValue cv;
    int result = cv.read("charset=\"Ascii\" Quoted charset");
    EXPECT_EQ(result, 0);
    std::string comment = cv.comment();
    EXPECT_EQ(comment, "Quoted charset");
}

// Test read with charset name in quotes - invalid charset
TEST_F(CommentValueTest_819, ReadCharsetQuotedInvalid_819) {
    Exiv2::CommentValue cv;
    int result = cv.read("charset=\"Bogus\" Some text");
    EXPECT_EQ(result, 1);
}

// Test charsetId returns correct value for ASCII
TEST_F(CommentValueTest_819, CharsetIdAscii_819) {
    Exiv2::CommentValue cv;
    cv.read("charset=Ascii Test");
    EXPECT_EQ(cv.charsetId(), Exiv2::CommentValue::ascii);
}

// Test charsetId returns correct value for Unicode
TEST_F(CommentValueTest_819, CharsetIdUnicode_819) {
    Exiv2::CommentValue cv;
    cv.read("charset=Unicode Test");
    EXPECT_EQ(cv.charsetId(), Exiv2::CommentValue::unicode);
}

// Test charsetId returns correct value for Undefined (default)
TEST_F(CommentValueTest_819, CharsetIdUndefined_819) {
    Exiv2::CommentValue cv;
    cv.read("charset=Undefined Test");
    EXPECT_EQ(cv.charsetId(), Exiv2::CommentValue::undefined);
}

// Test charsetId returns undefined for plain comment (no charset prefix)
TEST_F(CommentValueTest_819, CharsetIdDefault_819) {
    Exiv2::CommentValue cv;
    cv.read("Plain comment");
    EXPECT_EQ(cv.charsetId(), Exiv2::CommentValue::undefined);
}

// Test comment() returns the text portion
TEST_F(CommentValueTest_819, CommentReturnsText_819) {
    Exiv2::CommentValue cv;
    cv.read("charset=Ascii Hello");
    std::string comment = cv.comment();
    EXPECT_EQ(comment, "Hello");
}

// Test comment() for plain text (no charset prefix)
TEST_F(CommentValueTest_819, CommentPlainText_819) {
    Exiv2::CommentValue cv;
    cv.read("Just a plain comment");
    std::string comment = cv.comment();
    EXPECT_EQ(comment, "Just a plain comment");
}

// Test write to ostream
TEST_F(CommentValueTest_819, WriteToStream_819) {
    Exiv2::CommentValue cv;
    cv.read("charset=Ascii Stream test");
    std::ostringstream os;
    cv.write(os);
    std::string output = os.str();
    EXPECT_FALSE(output.empty());
}

// Test clone creates a copy
TEST_F(CommentValueTest_819, Clone_819) {
    Exiv2::CommentValue cv;
    cv.read("charset=Ascii Clone test");
    auto cloned = cv.clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->size(), cv.size());
}

// Test copy to buffer
TEST_F(CommentValueTest_819, CopyToBuffer_819) {
    Exiv2::CommentValue cv;
    cv.read("charset=Ascii Copy test");
    size_t sz = cv.size();
    std::vector<Exiv2::byte> buf(sz);
    size_t copied = cv.copy(buf.data(), Exiv2::littleEndian);
    EXPECT_EQ(copied, sz);
}

// Test read from byte buffer
TEST_F(CommentValueTest_819, ReadFromByteBuffer_819) {
    // First create a known comment value, copy it to bytes, then read back
    Exiv2::CommentValue cv1;
    cv1.read("charset=Ascii Byte buffer test");
    size_t sz = cv1.size();
    std::vector<Exiv2::byte> buf(sz);
    cv1.copy(buf.data(), Exiv2::littleEndian);

    Exiv2::CommentValue cv2;
    int result = cv2.read(buf.data(), sz, Exiv2::littleEndian);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(cv2.size(), cv1.size());
}

// Test count returns expected value
TEST_F(CommentValueTest_819, CountValue_819) {
    Exiv2::CommentValue cv;
    cv.read("charset=Ascii Count test");
    EXPECT_GT(cv.count(), 0u);
}

// Test with a string that starts with "charset=" but has empty charset name
TEST_F(CommentValueTest_819, ReadEmptyCharsetName_819) {
    Exiv2::CommentValue cv;
    int result = cv.read("charset= Some text");
    // Empty charset name after stripping quotes - should be invalid
    EXPECT_EQ(result, 1);
}

// Test with charset= followed by only space
TEST_F(CommentValueTest_819, ReadCharsetOnlySpace_819) {
    Exiv2::CommentValue cv;
    // "charset=" with first space at position 8, so name = "" which is empty -> invalidCharsetId
    int result = cv.read("charset= ");
    EXPECT_EQ(result, 1);
}

// Test CharsetInfo::name for known charset IDs
TEST_F(CommentValueTest_819, CharsetInfoNameAscii_819) {
    const char* name = Exiv2::CommentValue::CharsetInfo::name(Exiv2::CommentValue::ascii);
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "Ascii");
}

TEST_F(CommentValueTest_819, CharsetInfoNameUnicode_819) {
    const char* name = Exiv2::CommentValue::CharsetInfo::name(Exiv2::CommentValue::unicode);
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "Unicode");
}

TEST_F(CommentValueTest_819, CharsetInfoNameJis_819) {
    const char* name = Exiv2::CommentValue::CharsetInfo::name(Exiv2::CommentValue::jis);
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "Jis");
}

TEST_F(CommentValueTest_819, CharsetInfoNameUndefined_819) {
    const char* name = Exiv2::CommentValue::CharsetInfo::name(Exiv2::CommentValue::undefined);
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "Undefined");
}

// Test CharsetInfo::charsetIdByName
TEST_F(CommentValueTest_819, CharsetIdByNameAscii_819) {
    Exiv2::CommentValue::CharsetId id = Exiv2::CommentValue::CharsetInfo::charsetIdByName("Ascii");
    EXPECT_EQ(id, Exiv2::CommentValue::ascii);
}

TEST_F(CommentValueTest_819, CharsetIdByNameUnicode_819) {
    Exiv2::CommentValue::CharsetId id = Exiv2::CommentValue::CharsetInfo::charsetIdByName("Unicode");
    EXPECT_EQ(id, Exiv2::CommentValue::unicode);
}

TEST_F(CommentValueTest_819, CharsetIdByNameInvalid_819) {
    Exiv2::CommentValue::CharsetId id = Exiv2::CommentValue::CharsetInfo::charsetIdByName("NonExistent");
    EXPECT_EQ(id, Exiv2::CommentValue::invalidCharsetId);
}

// Test CharsetInfo::code returns 8-byte code
TEST_F(CommentValueTest_819, CharsetInfoCodeLength_819) {
    const char* code = Exiv2::CommentValue::CharsetInfo::code(Exiv2::CommentValue::ascii);
    ASSERT_NE(code, nullptr);
    // The code is always 8 bytes
    std::string codeStr(code, 8);
    EXPECT_EQ(codeStr.size(), 8u);
}

// Test reading a very long comment
TEST_F(CommentValueTest_819, ReadLongComment_819) {
    std::string longComment(10000, 'A');
    Exiv2::CommentValue cv;
    int result = cv.read(longComment);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(cv.size(), 8u + 10000u);
}

// Test reading a comment with special characters
TEST_F(CommentValueTest_819, ReadSpecialCharacters_819) {
    Exiv2::CommentValue cv;
    int result = cv.read("charset=Ascii Special chars: !@#$%^&*()");
    EXPECT_EQ(result, 0);
    std::string comment = cv.comment();
    EXPECT_EQ(comment, "Special chars: !@#$%^&*()");
}

// Test reading with charset= prefix but text contains multiple spaces
TEST_F(CommentValueTest_819, ReadMultipleSpaces_819) {
    Exiv2::CommentValue cv;
    int result = cv.read("charset=Ascii   Multiple   spaces");
    EXPECT_EQ(result, 0);
    std::string comment = cv.comment();
    // The first space separates charset from comment; rest is comment text
    EXPECT_EQ(comment, "  Multiple   spaces");
}

// Test that the string "charset=" alone is handled
TEST_F(CommentValueTest_819, ReadCharsetEqualsOnly_819) {
    Exiv2::CommentValue cv;
    // "charset=" with no charset name and no space -> name = "" which is empty -> invalidCharsetId
    int result = cv.read("charset=");
    EXPECT_EQ(result, 1);
}

// Test detectCharset
TEST_F(CommentValueTest_819, DetectCharsetAscii_819) {
    Exiv2::CommentValue cv;
    cv.read("charset=Ascii Detection test");
    std::string c;
    const char* detected = cv.detectCharset(c);
    // Should detect the charset
    if (detected != nullptr) {
        EXPECT_TRUE(std::string(detected).length() > 0);
    }
}

// Test that constructor with comment string works like read
TEST_F(CommentValueTest_819, ConstructorEquivalentToRead_819) {
    Exiv2::CommentValue cv1("charset=Ascii Constructor test");
    
    Exiv2::CommentValue cv2;
    cv2.read("charset=Ascii Constructor test");
    
    EXPECT_EQ(cv1.size(), cv2.size());
    EXPECT_EQ(cv1.charsetId(), cv2.charsetId());
    EXPECT_EQ(cv1.comment(), cv2.comment());
}

// Test re-reading overwrites previous value
TEST_F(CommentValueTest_819, ReadOverwritesPrevious_819) {
    Exiv2::CommentValue cv;
    cv.read("charset=Ascii First");
    std::string first = cv.comment();
    
    cv.read("charset=Ascii Second");
    std::string second = cv.comment();
    
    EXPECT_EQ(first, "First");
    EXPECT_EQ(second, "Second");
}

// Test with single-character comment
TEST_F(CommentValueTest_819, ReadSingleCharComment_819) {
    Exiv2::CommentValue cv;
    int result = cv.read("X");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(cv.size(), 8u + 1u);
}

// Test that Jis charset ID is correctly identified
TEST_F(CommentValueTest_819, CharsetIdJis_819) {
    Exiv2::CommentValue cv;
    cv.read("charset=Jis Test");
    EXPECT_EQ(cv.charsetId(), Exiv2::CommentValue::jis);
}

} // namespace
