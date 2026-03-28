#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <exiv2/error.hpp>
#include <cstring>
#include <string>
#include <sstream>

namespace {

class CommentValueTest_823 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test default constructor creates an empty CommentValue
TEST_F(CommentValueTest_823, DefaultConstructor_823) {
    Exiv2::CommentValue cv;
    EXPECT_EQ(cv.size(), 0u);
    EXPECT_EQ(cv.count(), 0u);
}

// Test constructor with a simple ASCII comment
TEST_F(CommentValueTest_823, ConstructWithAsciiComment_823) {
    Exiv2::CommentValue cv("charset=Ascii Hello World");
    std::string comment = cv.comment();
    EXPECT_EQ(comment, "Hello World");
}

// Test constructor with plain text (no charset specification)
TEST_F(CommentValueTest_823, ConstructWithPlainComment_823) {
    Exiv2::CommentValue cv("Hello World");
    std::string comment = cv.comment();
    EXPECT_EQ(comment, "Hello World");
}

// Test read from string with ASCII charset
TEST_F(CommentValueTest_823, ReadAsciiCharsetComment_823) {
    Exiv2::CommentValue cv;
    cv.read("charset=Ascii Test comment");
    std::string comment = cv.comment();
    EXPECT_EQ(comment, "Test comment");
}

// Test comment() returns empty string when value is too short (less than 8 bytes)
TEST_F(CommentValueTest_823, CommentReturnsEmptyWhenValueTooShort_823) {
    Exiv2::CommentValue cv;
    // Read raw bytes that are shorter than 8 bytes
    const Exiv2::byte buf[] = {0x00, 0x00, 0x00};
    cv.read(buf, 3, Exiv2::littleEndian);
    std::string comment = cv.comment();
    EXPECT_TRUE(comment.empty());
}

// Test comment with undefined charset
TEST_F(CommentValueTest_823, UndefinedCharsetComment_823) {
    Exiv2::CommentValue cv;
    // Undefined charset: 8 bytes of 0x00 followed by comment
    std::vector<Exiv2::byte> buf(8, 0x00);
    std::string text = "Test undefined";
    buf.insert(buf.end(), text.begin(), text.end());
    cv.read(buf.data(), buf.size(), Exiv2::littleEndian);
    std::string comment = cv.comment();
    // Undefined charset should truncate at null
    EXPECT_FALSE(comment.empty());
}

// Test charsetId for ASCII charset
TEST_F(CommentValueTest_823, CharsetIdAscii_823) {
    Exiv2::CommentValue cv("charset=Ascii Some text");
    Exiv2::CommentValue::CharsetId id = cv.charsetId();
    EXPECT_EQ(id, Exiv2::CommentValue::ascii);
}

// Test charsetId for undefined charset
TEST_F(CommentValueTest_823, CharsetIdUndefined_823) {
    Exiv2::CommentValue cv;
    // 8 bytes of 0x00 for undefined charset header + some text
    std::vector<Exiv2::byte> buf(8, 0x00);
    std::string text = "Some text";
    buf.insert(buf.end(), text.begin(), text.end());
    cv.read(buf.data(), buf.size(), Exiv2::littleEndian);
    Exiv2::CommentValue::CharsetId id = cv.charsetId();
    EXPECT_EQ(id, Exiv2::CommentValue::undefined);
}

// Test copy method
TEST_F(CommentValueTest_823, CopyMethod_823) {
    Exiv2::CommentValue cv("charset=Ascii Hello");
    size_t sz = cv.size();
    std::vector<Exiv2::byte> buf(sz);
    size_t copied = cv.copy(buf.data(), Exiv2::littleEndian);
    EXPECT_EQ(copied, sz);
}

// Test write method outputs to stream
TEST_F(CommentValueTest_823, WriteToStream_823) {
    Exiv2::CommentValue cv("charset=Ascii Hello");
    std::ostringstream os;
    cv.write(os);
    std::string output = os.str();
    EXPECT_FALSE(output.empty());
}

// Test clone method
TEST_F(CommentValueTest_823, CloneMethod_823) {
    Exiv2::CommentValue cv("charset=Ascii Clone test");
    auto cloned = cv.clone();
    EXPECT_NE(cloned, nullptr);
    std::ostringstream os1, os2;
    cv.write(os1);
    cloned->write(os2);
    EXPECT_EQ(os1.str(), os2.str());
}

// Test comment with null character in ASCII value - should truncate at null
TEST_F(CommentValueTest_823, AsciiCommentTruncatesAtNull_823) {
    Exiv2::CommentValue cv;
    // ASCII charset header
    const char asciiHeader[] = "ASCII\0\0\0";
    std::vector<Exiv2::byte> buf(asciiHeader, asciiHeader + 8);
    std::string textWithNull = "Hello";
    textWithNull += '\0';
    textWithNull += "World";
    buf.insert(buf.end(), textWithNull.begin(), textWithNull.end());
    cv.read(buf.data(), buf.size(), Exiv2::littleEndian);
    std::string comment = cv.comment();
    EXPECT_EQ(comment, "Hello");
}

// Test read from string and then retrieve comment
TEST_F(CommentValueTest_823, ReadStringAndRetrieveComment_823) {
    Exiv2::CommentValue cv;
    int result = cv.read("charset=Ascii A quick test");
    EXPECT_EQ(result, 0);
    std::string comment = cv.comment();
    EXPECT_EQ(comment, "A quick test");
}

// Test empty comment string
TEST_F(CommentValueTest_823, EmptyCommentString_823) {
    Exiv2::CommentValue cv("");
    std::string comment = cv.comment();
    // Empty string should result in empty or specific behavior
    // since value_ will be less than 8 bytes
    EXPECT_TRUE(comment.empty());
}

// Test comment with encoding parameter as nullptr
TEST_F(CommentValueTest_823, CommentWithNullEncoding_823) {
    Exiv2::CommentValue cv("charset=Ascii Some text here");
    std::string comment = cv.comment(nullptr);
    EXPECT_EQ(comment, "Some text here");
}

// Test comment with encoding parameter as empty string
TEST_F(CommentValueTest_823, CommentWithEmptyEncoding_823) {
    Exiv2::CommentValue cv("charset=Ascii Some text here");
    std::string comment = cv.comment("");
    EXPECT_EQ(comment, "Some text here");
}

// Test size is consistent with the internal value
TEST_F(CommentValueTest_823, SizeConsistency_823) {
    Exiv2::CommentValue cv("charset=Ascii Test");
    EXPECT_GT(cv.size(), 0u);
}

// Test count returns expected value
TEST_F(CommentValueTest_823, CountReturnsExpected_823) {
    Exiv2::CommentValue cv("charset=Ascii Test");
    EXPECT_GT(cv.count(), 0u);
}

// Test reading from byte buffer with ASCII header
TEST_F(CommentValueTest_823, ReadFromByteBufferAscii_823) {
    const char asciiHeader[] = "ASCII\0\0\0";
    std::vector<Exiv2::byte> buf(asciiHeader, asciiHeader + 8);
    std::string text = "Byte buffer test";
    buf.insert(buf.end(), text.begin(), text.end());

    Exiv2::CommentValue cv;
    cv.read(buf.data(), buf.size(), Exiv2::littleEndian);
    
    std::string comment = cv.comment();
    EXPECT_EQ(comment, "Byte buffer test");
}

// Test reading exactly 8 bytes (header only, no content)
TEST_F(CommentValueTest_823, ReadExactlyHeaderNoContent_823) {
    const char asciiHeader[] = "ASCII\0\0\0";
    std::vector<Exiv2::byte> buf(asciiHeader, asciiHeader + 8);

    Exiv2::CommentValue cv;
    cv.read(buf.data(), buf.size(), Exiv2::littleEndian);
    
    std::string comment = cv.comment();
    EXPECT_TRUE(comment.empty());
}

// Test with Unicode charset specification
TEST_F(CommentValueTest_823, UnicodeCharsetComment_823) {
    Exiv2::CommentValue cv("charset=Unicode Hello");
    Exiv2::CommentValue::CharsetId id = cv.charsetId();
    EXPECT_EQ(id, Exiv2::CommentValue::unicode);
}

// Test reading 7 bytes (less than header size)
TEST_F(CommentValueTest_823, ReadLessThanHeaderSize_823) {
    const Exiv2::byte buf[] = {0x41, 0x53, 0x43, 0x49, 0x49, 0x00, 0x00};
    Exiv2::CommentValue cv;
    cv.read(buf, 7, Exiv2::littleEndian);
    std::string comment = cv.comment();
    EXPECT_TRUE(comment.empty());
}

// Test that re-reading overwrites previous value
TEST_F(CommentValueTest_823, ReReadOverwritesPreviousValue_823) {
    Exiv2::CommentValue cv("charset=Ascii First");
    std::string comment1 = cv.comment();
    EXPECT_EQ(comment1, "First");

    cv.read("charset=Ascii Second");
    std::string comment2 = cv.comment();
    EXPECT_EQ(comment2, "Second");
}

// Test toInt64 - StringValueBase typically converts string to int
TEST_F(CommentValueTest_823, ToInt64_823) {
    Exiv2::CommentValue cv("charset=Ascii 42");
    // This may throw or return 0 depending on internal implementation
    // We just verify it doesn't crash for a basic case
    try {
        int64_t val = cv.toInt64(0);
        // If it succeeds, any value is acceptable
        (void)val;
    } catch (...) {
        // Exception is also acceptable behavior
    }
}

// Test toFloat
TEST_F(CommentValueTest_823, ToFloat_823) {
    Exiv2::CommentValue cv("charset=Ascii 3.14");
    try {
        float val = cv.toFloat(0);
        (void)val;
    } catch (...) {
        // Exception is acceptable
    }
}

} // namespace
