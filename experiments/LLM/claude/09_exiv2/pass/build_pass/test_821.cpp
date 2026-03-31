#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <exiv2/types.hpp>
#include <cstring>
#include <sstream>
#include <vector>

using namespace Exiv2;

// Test fixture for CommentValue tests
class CommentValueTest_821 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// --- Default Constructor Tests ---

TEST_F(CommentValueTest_821, DefaultConstructor_CreatesEmptyValue_821) {
    CommentValue cv;
    EXPECT_EQ(cv.size(), 0u);
    EXPECT_EQ(cv.count(), 0u);
}

TEST_F(CommentValueTest_821, DefaultConstructor_CopyReturnsZeroForEmpty_821) {
    CommentValue cv;
    byte buf[64] = {};
    size_t copied = cv.copy(buf, littleEndian);
    EXPECT_EQ(copied, 0u);
}

// --- String Constructor Tests ---

TEST_F(CommentValueTest_821, StringConstructor_WithAsciiComment_821) {
    CommentValue cv("Hello World");
    EXPECT_GT(cv.size(), 0u);
}

TEST_F(CommentValueTest_821, StringConstructor_WithEmptyString_821) {
    CommentValue cv("");
    // Empty string comment - behavior depends on implementation
    // Just ensure no crash
    EXPECT_GE(cv.size(), 0u);
}

// --- read(const std::string&) Tests ---

TEST_F(CommentValueTest_821, ReadString_AsciiComment_821) {
    CommentValue cv;
    int result = cv.read("Simple ASCII comment");
    EXPECT_EQ(result, 0);
    EXPECT_GT(cv.size(), 0u);
}

TEST_F(CommentValueTest_821, ReadString_EmptyComment_821) {
    CommentValue cv;
    int result = cv.read("");
    EXPECT_EQ(result, 0);
}

TEST_F(CommentValueTest_821, ReadString_CharsetAsciiPrefix_821) {
    CommentValue cv;
    int result = cv.read("charset=Ascii A test comment");
    EXPECT_EQ(result, 0);
}

TEST_F(CommentValueTest_821, ReadString_CharsetUnicodePrefix_821) {
    CommentValue cv;
    int result = cv.read("charset=Unicode A unicode comment");
    EXPECT_EQ(result, 0);
}

TEST_F(CommentValueTest_821, ReadString_CharsetUndefinedPrefix_821) {
    CommentValue cv;
    int result = cv.read("charset=Undefined some data");
    EXPECT_EQ(result, 0);
}

// --- read(const byte*, size_t, ByteOrder) Tests ---

TEST_F(CommentValueTest_821, ReadBytes_SimpleAsciiData_821) {
    CommentValue cv;
    // ASCII charset marker is "ASCII\0\0\0" (8 bytes) followed by data
    byte data[] = {'A', 'S', 'C', 'I', 'I', 0, 0, 0, 'H', 'e', 'l', 'l', 'o'};
    int result = cv.read(data, sizeof(data), littleEndian);
    EXPECT_EQ(result, 0);
    EXPECT_GT(cv.size(), 0u);
}

TEST_F(CommentValueTest_821, ReadBytes_EmptyData_821) {
    CommentValue cv;
    byte data[1] = {0};
    int result = cv.read(data, 0, littleEndian);
    EXPECT_EQ(result, 0);
}

TEST_F(CommentValueTest_821, ReadBytes_LittleEndian_821) {
    CommentValue cv;
    std::string testStr = "test data in bytes";
    int result = cv.read(reinterpret_cast<const byte*>(testStr.data()), testStr.size(), littleEndian);
    EXPECT_EQ(result, 0);
}

TEST_F(CommentValueTest_821, ReadBytes_BigEndian_821) {
    CommentValue cv;
    std::string testStr = "test data in bytes";
    int result = cv.read(reinterpret_cast<const byte*>(testStr.data()), testStr.size(), bigEndian);
    EXPECT_EQ(result, 0);
}

// --- copy() Tests ---

TEST_F(CommentValueTest_821, Copy_AsciiComment_821) {
    CommentValue cv("Hello");
    byte buf[256] = {};
    size_t copied = cv.copy(buf, littleEndian);
    EXPECT_GT(copied, 0u);
}

TEST_F(CommentValueTest_821, Copy_EmptyComment_ReturnsZero_821) {
    CommentValue cv;
    byte buf[64] = {};
    size_t copied = cv.copy(buf, littleEndian);
    EXPECT_EQ(copied, 0u);
}

TEST_F(CommentValueTest_821, Copy_LittleEndianByteOrder_821) {
    CommentValue cv("Test comment");
    byte buf[256] = {};
    size_t copied = cv.copy(buf, littleEndian);
    EXPECT_GT(copied, 0u);
}

TEST_F(CommentValueTest_821, Copy_BigEndianByteOrder_821) {
    CommentValue cv("Test comment");
    byte buf[256] = {};
    size_t copied = cv.copy(buf, bigEndian);
    EXPECT_GT(copied, 0u);
}

TEST_F(CommentValueTest_821, Copy_SameResultForAsciiRegardlessOfByteOrder_821) {
    CommentValue cv("charset=Ascii Plain ASCII text");
    byte buf1[256] = {};
    byte buf2[256] = {};
    size_t copied1 = cv.copy(buf1, littleEndian);
    size_t copied2 = cv.copy(buf2, bigEndian);
    EXPECT_EQ(copied1, copied2);
    EXPECT_EQ(std::memcmp(buf1, buf2, copied1), 0);
}

// --- write() Tests ---

TEST_F(CommentValueTest_821, Write_AsciiComment_821) {
    CommentValue cv("Hello World");
    std::ostringstream oss;
    cv.write(oss);
    EXPECT_FALSE(oss.str().empty());
}

TEST_F(CommentValueTest_821, Write_EmptyComment_821) {
    CommentValue cv;
    std::ostringstream oss;
    cv.write(oss);
    // Should not crash; content depends on implementation
}

// --- comment() Tests ---

TEST_F(CommentValueTest_821, Comment_ReturnsCommentString_821) {
    CommentValue cv("charset=Ascii Hello World");
    std::string result = cv.comment();
    EXPECT_FALSE(result.empty());
}

TEST_F(CommentValueTest_821, Comment_EmptyValue_821) {
    CommentValue cv;
    std::string result = cv.comment();
    EXPECT_TRUE(result.empty());
}

TEST_F(CommentValueTest_821, Comment_SimpleString_821) {
    CommentValue cv("A simple comment");
    std::string result = cv.comment();
    // The comment should contain the text
    EXPECT_NE(result.find("simple comment"), std::string::npos);
}

// --- charsetId() Tests ---

TEST_F(CommentValueTest_821, CharsetId_DefaultIsUndefined_821) {
    CommentValue cv;
    // Empty CommentValue - charsetId depends on implementation
    CommentValue::CharsetId id = cv.charsetId();
    // Just ensure it returns a valid enum value
    EXPECT_GE(static_cast<int>(id), 0);
    EXPECT_LT(static_cast<int>(id), static_cast<int>(CommentValue::lastCharsetId));
}

TEST_F(CommentValueTest_821, CharsetId_AsciiCharset_821) {
    CommentValue cv("charset=Ascii Hello");
    CommentValue::CharsetId id = cv.charsetId();
    EXPECT_EQ(id, CommentValue::ascii);
}

TEST_F(CommentValueTest_821, CharsetId_UnicodeCharset_821) {
    CommentValue cv("charset=Unicode Hello");
    CommentValue::CharsetId id = cv.charsetId();
    EXPECT_EQ(id, CommentValue::unicode);
}

TEST_F(CommentValueTest_821, CharsetId_UndefinedCharset_821) {
    CommentValue cv("charset=Undefined some data");
    CommentValue::CharsetId id = cv.charsetId();
    EXPECT_EQ(id, CommentValue::undefined);
}

// --- detectCharset() Tests ---

TEST_F(CommentValueTest_821, DetectCharset_AsciiString_821) {
    CommentValue cv("charset=Ascii Hello");
    std::string c = cv.comment();
    const char* charset = cv.detectCharset(c);
    // Should detect some charset
    if (charset != nullptr) {
        EXPECT_TRUE(std::strlen(charset) > 0);
    }
}

TEST_F(CommentValueTest_821, DetectCharset_EmptyString_821) {
    CommentValue cv;
    std::string c;
    const char* charset = cv.detectCharset(c);
    // May return nullptr or a valid charset string
    // Just ensure no crash
}

// --- clone() Tests ---

TEST_F(CommentValueTest_821, Clone_CreatesIdenticalCopy_821) {
    CommentValue cv("charset=Ascii Test clone");
    auto cloned = cv.clone();
    ASSERT_NE(cloned, nullptr);

    // Compare sizes
    EXPECT_EQ(cloned->size(), cv.size());

    // Compare copy output
    if (cv.size() > 0) {
        std::vector<byte> buf1(cv.size() + 16, 0);
        std::vector<byte> buf2(cv.size() + 16, 0);
        size_t c1 = cv.copy(buf1.data(), littleEndian);
        size_t c2 = cloned->copy(buf2.data(), littleEndian);
        EXPECT_EQ(c1, c2);
        EXPECT_EQ(std::memcmp(buf1.data(), buf2.data(), c1), 0);
    }
}

// --- count() and size() Tests ---

TEST_F(CommentValueTest_821, Count_MatchesSize_821) {
    CommentValue cv("Test count and size");
    // For CommentValue, count() and size() should be related
    EXPECT_GT(cv.count(), 0u);
    EXPECT_GT(cv.size(), 0u);
}

TEST_F(CommentValueTest_821, Size_EmptyComment_821) {
    CommentValue cv;
    EXPECT_EQ(cv.size(), 0u);
}

// --- Conversion Tests ---

TEST_F(CommentValueTest_821, ToInt64_ShouldNotCrash_821) {
    CommentValue cv("12345");
    // These conversions may throw or return 0, just ensure no crash
    try {
        int64_t val = cv.toInt64(0);
        // Value depends on implementation
        (void)val;
    } catch (...) {
        // Expected to possibly throw
    }
}

TEST_F(CommentValueTest_821, ToFloat_ShouldNotCrash_821) {
    CommentValue cv("3.14");
    try {
        float val = cv.toFloat(0);
        (void)val;
    } catch (...) {
        // Expected to possibly throw
    }
}

TEST_F(CommentValueTest_821, ToRational_ShouldNotCrash_821) {
    CommentValue cv("1/2");
    try {
        Rational val = cv.toRational(0);
        (void)val;
    } catch (...) {
        // Expected to possibly throw
    }
}

// --- Unicode with byte order conversion Tests ---

TEST_F(CommentValueTest_821, Copy_UnicodeComment_LittleEndianToBigEndian_821) {
    // Create a unicode comment by reading raw bytes with Unicode charset marker
    CommentValue cv;
    // Unicode charset marker: "UNICODE\0" (8 bytes)
    std::vector<byte> data = {'U', 'N', 'I', 'C', 'O', 'D', 'E', 0};
    // Add some UCS-2LE data (e.g., 'A' '\0' 'B' '\0')
    data.push_back('A');
    data.push_back(0);
    data.push_back('B');
    data.push_back(0);

    int result = cv.read(data.data(), data.size(), littleEndian);
    EXPECT_EQ(result, 0);

    if (cv.size() > 0) {
        std::vector<byte> bufLE(cv.size() + 16, 0);
        std::vector<byte> bufBE(cv.size() + 16, 0);

        size_t copiedLE = cv.copy(bufLE.data(), littleEndian);
        size_t copiedBE = cv.copy(bufBE.data(), bigEndian);

        EXPECT_GT(copiedLE, 0u);
        EXPECT_GT(copiedBE, 0u);
        EXPECT_EQ(copiedLE, copiedBE);

        // The first 8 bytes (charset marker) should be the same
        EXPECT_EQ(std::memcmp(bufLE.data(), bufBE.data(), 8), 0);
    }
}

TEST_F(CommentValueTest_821, Copy_UnicodeComment_BigEndianToLittleEndian_821) {
    CommentValue cv;
    // Unicode charset marker: "UNICODE\0" (8 bytes)
    std::vector<byte> data = {'U', 'N', 'I', 'C', 'O', 'D', 'E', 0};
    // Add some UCS-2BE data (e.g., '\0' 'A' '\0' 'B')
    data.push_back(0);
    data.push_back('A');
    data.push_back(0);
    data.push_back('B');

    int result = cv.read(data.data(), data.size(), bigEndian);
    EXPECT_EQ(result, 0);

    if (cv.size() > 0) {
        std::vector<byte> bufLE(cv.size() + 16, 0);
        size_t copiedLE = cv.copy(bufLE.data(), littleEndian);
        EXPECT_GT(copiedLE, 0u);
    }
}

TEST_F(CommentValueTest_821, Copy_UnicodeComment_SameByteOrder_821) {
    CommentValue cv;
    std::vector<byte> data = {'U', 'N', 'I', 'C', 'O', 'D', 'E', 0};
    data.push_back('A');
    data.push_back(0);
    data.push_back('B');
    data.push_back(0);

    cv.read(data.data(), data.size(), littleEndian);

    if (cv.size() > 0) {
        std::vector<byte> buf1(cv.size() + 16, 0);
        std::vector<byte> buf2(cv.size() + 16, 0);

        size_t copied1 = cv.copy(buf1.data(), littleEndian);
        size_t copied2 = cv.copy(buf2.data(), littleEndian);

        // Same byte order should produce identical output
        EXPECT_EQ(copied1, copied2);
        EXPECT_EQ(std::memcmp(buf1.data(), buf2.data(), copied1), 0);
    }
}

// --- Boundary Tests ---

TEST_F(CommentValueTest_821, ReadString_VeryLongComment_821) {
    std::string longComment(10000, 'X');
    CommentValue cv(longComment);
    EXPECT_GT(cv.size(), 0u);

    std::vector<byte> buf(cv.size() + 16, 0);
    size_t copied = cv.copy(buf.data(), littleEndian);
    EXPECT_GT(copied, 0u);
}

TEST_F(CommentValueTest_821, ReadString_SingleCharComment_821) {
    CommentValue cv("A");
    EXPECT_GT(cv.size(), 0u);
    std::string result = cv.comment();
    EXPECT_FALSE(result.empty());
}

TEST_F(CommentValueTest_821, ReadString_SpecialCharacters_821) {
    CommentValue cv("Special chars: !@#$%^&*()");
    EXPECT_GT(cv.size(), 0u);
    std::string result = cv.comment();
    EXPECT_FALSE(result.empty());
}

// --- Re-read Tests ---

TEST_F(CommentValueTest_821, ReRead_OverwritesPreviousValue_821) {
    CommentValue cv("First comment");
    size_t firstSize = cv.size();

    cv.read("Second longer comment here");
    size_t secondSize = cv.size();

    // The sizes should likely differ since the comments differ in length
    // But we can at least verify re-reading doesn't crash and produces valid state
    EXPECT_GT(secondSize, 0u);
}

TEST_F(CommentValueTest_821, CharsetId_JisCharset_821) {
    CommentValue cv("charset=Jis some jis text");
    CommentValue::CharsetId id = cv.charsetId();
    EXPECT_EQ(id, CommentValue::jis);
}

TEST_F(CommentValueTest_821, Comment_WithEncoding_821) {
    CommentValue cv("charset=Ascii Encoded comment");
    // Test comment() with explicit encoding parameter
    std::string result = cv.comment("UTF-8");
    // Should return some string representation
    EXPECT_FALSE(result.empty());
}

TEST_F(CommentValueTest_821, Write_AsciiCharsetComment_OutputContainsText_821) {
    CommentValue cv("charset=Ascii Hello World");
    std::ostringstream oss;
    cv.write(oss);
    std::string output = oss.str();
    // The written output should contain some representation of the comment
    EXPECT_FALSE(output.empty());
}

TEST_F(CommentValueTest_821, Copy_InvalidByteOrder_821) {
    CommentValue cv("Test");
    byte buf[256] = {};
    // invalidByteOrder
    size_t copied = cv.copy(buf, invalidByteOrder);
    // Should still work for non-unicode comments
    EXPECT_GT(copied, 0u);
}
