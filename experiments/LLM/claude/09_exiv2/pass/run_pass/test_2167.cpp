#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <sstream>
#include <cstring>

using namespace Exiv2;

// Test fixture for CommentValue tests
class CommentValueTest_2167 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ============================================================
// Construction Tests
// ============================================================

TEST_F(CommentValueTest_2167, DefaultConstruction_2167) {
    CommentValue cv;
    EXPECT_EQ(cv.size(), 0u);
    EXPECT_EQ(cv.count(), 0u);
}

TEST_F(CommentValueTest_2167, ConstructWithSimpleString_2167) {
    CommentValue cv("Hello World");
    EXPECT_GT(cv.size(), 0u);
}

TEST_F(CommentValueTest_2167, ConstructWithEmptyString_2167) {
    CommentValue cv("");
    // Empty string should result in size 0 or minimal size
    EXPECT_EQ(cv.size(), 0u);
}

TEST_F(CommentValueTest_2167, ConstructWithCharsetASCII_2167) {
    CommentValue cv("charset=Ascii Hello ASCII");
    EXPECT_GT(cv.size(), 0u);
}

TEST_F(CommentValueTest_2167, ConstructWithCharsetUnicode_2167) {
    CommentValue cv("charset=Unicode Hello Unicode");
    EXPECT_GT(cv.size(), 0u);
}

TEST_F(CommentValueTest_2167, ConstructWithCharsetJis_2167) {
    CommentValue cv("charset=Jis Hello JIS");
    EXPECT_GT(cv.size(), 0u);
}

TEST_F(CommentValueTest_2167, ConstructWithCharsetUndefined_2167) {
    CommentValue cv("charset=Undefined Some data");
    EXPECT_GT(cv.size(), 0u);
}

// ============================================================
// Read Tests (from string)
// ============================================================

TEST_F(CommentValueTest_2167, ReadSimpleComment_2167) {
    CommentValue cv;
    int result = cv.read("Test comment");
    EXPECT_EQ(result, 0);
    EXPECT_GT(cv.size(), 0u);
}

TEST_F(CommentValueTest_2167, ReadEmptyComment_2167) {
    CommentValue cv;
    int result = cv.read(std::string(""));
    EXPECT_EQ(result, 0);
}

TEST_F(CommentValueTest_2167, ReadCommentWithCharset_2167) {
    CommentValue cv;
    int result = cv.read("charset=Ascii A test comment");
    EXPECT_EQ(result, 0);
    EXPECT_GT(cv.size(), 0u);
}

TEST_F(CommentValueTest_2167, ReadOverwritesPreviousValue_2167) {
    CommentValue cv("First comment");
    size_t firstSize = cv.size();
    cv.read("Second much longer comment here");
    size_t secondSize = cv.size();
    // The two sizes should differ since strings differ
    EXPECT_NE(firstSize, secondSize);
}

// ============================================================
// Read Tests (from byte buffer)
// ============================================================

TEST_F(CommentValueTest_2167, ReadFromByteBuffer_2167) {
    CommentValue cv;
    // EXIF comment: 8 bytes charset header + data
    // ASCII charset ID: "ASCII\0\0\0"
    byte buf[] = {'A', 'S', 'C', 'I', 'I', 0, 0, 0, 'H', 'e', 'l', 'l', 'o'};
    int result = cv.read(buf, sizeof(buf), littleEndian);
    EXPECT_EQ(result, 0);
    EXPECT_GT(cv.size(), 0u);
}

TEST_F(CommentValueTest_2167, ReadFromEmptyByteBuffer_2167) {
    CommentValue cv;
    byte buf[1] = {0};
    int result = cv.read(buf, 0, littleEndian);
    EXPECT_EQ(result, 0);
}

// ============================================================
// Write Tests
// ============================================================

TEST_F(CommentValueTest_2167, WriteToOutputStream_2167) {
    CommentValue cv("charset=Ascii Hello World");
    std::ostringstream os;
    cv.write(os);
    std::string output = os.str();
    EXPECT_FALSE(output.empty());
}

TEST_F(CommentValueTest_2167, WriteEmptyComment_2167) {
    CommentValue cv;
    std::ostringstream os;
    cv.write(os);
    // Should not crash; output may be empty
}

// ============================================================
// Comment retrieval Tests
// ============================================================

TEST_F(CommentValueTest_2167, CommentReturnsText_2167) {
    CommentValue cv("charset=Ascii Hello World");
    std::string c = cv.comment();
    EXPECT_FALSE(c.empty());
    // The comment should contain "Hello World"
    EXPECT_NE(c.find("Hello World"), std::string::npos);
}

TEST_F(CommentValueTest_2167, CommentDefaultCharset_2167) {
    CommentValue cv("Simple comment without charset");
    std::string c = cv.comment();
    // Should return the comment text
    EXPECT_FALSE(c.empty());
}

// ============================================================
// CharsetId Tests
// ============================================================

TEST_F(CommentValueTest_2167, CharsetIdForAscii_2167) {
    CommentValue cv("charset=Ascii Test");
    auto id = cv.charsetId();
    // Should return a valid charset id (we can at least verify it doesn't crash)
    (void)id;
}

TEST_F(CommentValueTest_2167, CharsetIdForDefault_2167) {
    CommentValue cv;
    auto id = cv.charsetId();
    (void)id;
}

// ============================================================
// DetectCharset Tests
// ============================================================

TEST_F(CommentValueTest_2167, DetectCharsetOnAsciiComment_2167) {
    CommentValue cv("charset=Ascii Hello");
    std::string c;
    const char* charset = cv.detectCharset(c);
    // charset might be non-null for ASCII
    if (charset) {
        EXPECT_TRUE(strlen(charset) > 0);
    }
}

TEST_F(CommentValueTest_2167, DetectCharsetOnEmptyComment_2167) {
    CommentValue cv;
    std::string c;
    const char* charset = cv.detectCharset(c);
    // May return nullptr for empty comment
    (void)charset;
}

// ============================================================
// Copy Tests
// ============================================================

TEST_F(CommentValueTest_2167, CopyToBuffer_2167) {
    CommentValue cv("charset=Ascii Test copy");
    size_t sz = cv.size();
    if (sz > 0) {
        std::vector<byte> buf(sz);
        size_t copied = cv.copy(buf.data(), littleEndian);
        EXPECT_EQ(copied, sz);
    }
}

TEST_F(CommentValueTest_2167, CopyEmptyValue_2167) {
    CommentValue cv;
    size_t sz = cv.size();
    EXPECT_EQ(sz, 0u);
    if (sz == 0) {
        byte dummy;
        size_t copied = cv.copy(&dummy, littleEndian);
        EXPECT_EQ(copied, 0u);
    }
}

// ============================================================
// Count and Size Tests
// ============================================================

TEST_F(CommentValueTest_2167, CountMatchesSize_2167) {
    CommentValue cv("charset=Ascii Hello");
    // For string-based values, count and size may be related
    EXPECT_GT(cv.count(), 0u);
    EXPECT_GT(cv.size(), 0u);
}

TEST_F(CommentValueTest_2167, SizeChangesAfterRead_2167) {
    CommentValue cv;
    EXPECT_EQ(cv.size(), 0u);
    cv.read("charset=Ascii New data");
    EXPECT_GT(cv.size(), 0u);
}

// ============================================================
// Clone Tests
// ============================================================

TEST_F(CommentValueTest_2167, CloneProducesEqualValue_2167) {
    CommentValue cv("charset=Ascii Clone test");
    auto cloned = cv.clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->size(), cv.size());

    // Compare by writing to streams
    std::ostringstream os1, os2;
    cv.write(os1);
    cloned->write(os2);
    EXPECT_EQ(os1.str(), os2.str());
}

// ============================================================
// Numeric conversion Tests (should throw or return default for comment)
// ============================================================

TEST_F(CommentValueTest_2167, ToInt64OnComment_2167) {
    CommentValue cv("charset=Ascii 42");
    // toInt64 on a comment value - behavior depends on implementation
    // It may throw or return some value; we just ensure it doesn't crash
    try {
        int64_t val = cv.toInt64(0);
        (void)val;
    } catch (...) {
        // Exception is acceptable
    }
}

TEST_F(CommentValueTest_2167, ToUint32OnComment_2167) {
    CommentValue cv("charset=Ascii 42");
    try {
        uint32_t val = cv.toUint32(0);
        (void)val;
    } catch (...) {
        // Exception is acceptable
    }
}

TEST_F(CommentValueTest_2167, ToFloatOnComment_2167) {
    CommentValue cv("charset=Ascii 3.14");
    try {
        float val = cv.toFloat(0);
        (void)val;
    } catch (...) {
        // Exception is acceptable
    }
}

TEST_F(CommentValueTest_2167, ToRationalOnComment_2167) {
    CommentValue cv("charset=Ascii 1/2");
    try {
        auto val = cv.toRational(0);
        (void)val;
    } catch (...) {
        // Exception is acceptable
    }
}

// ============================================================
// Boundary / Edge Case Tests
// ============================================================

TEST_F(CommentValueTest_2167, VeryLongComment_2167) {
    std::string longComment(10000, 'A');
    CommentValue cv(longComment);
    EXPECT_GT(cv.size(), 0u);
    std::string c = cv.comment();
    EXPECT_FALSE(c.empty());
}

TEST_F(CommentValueTest_2167, CommentWithSpecialCharacters_2167) {
    CommentValue cv("charset=Ascii !@#$%^&*()_+-=[]{}|;':\",./<>?");
    EXPECT_GT(cv.size(), 0u);
    std::string c = cv.comment();
    EXPECT_FALSE(c.empty());
}

TEST_F(CommentValueTest_2167, CommentWithNewlines_2167) {
    CommentValue cv("charset=Ascii Line1\nLine2\nLine3");
    EXPECT_GT(cv.size(), 0u);
    std::string c = cv.comment();
    EXPECT_FALSE(c.empty());
}

TEST_F(CommentValueTest_2167, CommentCharsetOnly_2167) {
    CommentValue cv("charset=Ascii ");
    // Just charset prefix with space, no actual text
    // Should still work without crashing
    EXPECT_GE(cv.size(), 0u);
}

TEST_F(CommentValueTest_2167, MultipleReadCalls_2167) {
    CommentValue cv;
    cv.read("First");
    size_t s1 = cv.size();
    cv.read("Second longer text");
    size_t s2 = cv.size();
    cv.read("Third");
    size_t s3 = cv.size();
    
    // Values should change with each read
    EXPECT_NE(s1, s2);
    EXPECT_NE(s2, s3);
}

TEST_F(CommentValueTest_2167, ReadFromByteBufferWithUnicodeHeader_2167) {
    CommentValue cv;
    // Unicode charset header: "UNICODE\0"
    byte buf[] = {'U', 'N', 'I', 'C', 'O', 'D', 'E', 0, 0, 'H', 0, 'i'};
    int result = cv.read(buf, sizeof(buf), littleEndian);
    EXPECT_EQ(result, 0);
}

TEST_F(CommentValueTest_2167, CopyAndVerifyContent_2167) {
    CommentValue cv("charset=Ascii Hello");
    size_t sz = cv.size();
    ASSERT_GT(sz, 0u);
    
    std::vector<byte> buf1(sz);
    std::vector<byte> buf2(sz);
    
    size_t c1 = cv.copy(buf1.data(), littleEndian);
    size_t c2 = cv.copy(buf2.data(), bigEndian);
    
    // Copy should produce same result regardless of byte order for string data
    EXPECT_EQ(c1, c2);
    EXPECT_EQ(buf1, buf2);
}

TEST_F(CommentValueTest_2167, TypeIdIsUndefined_2167) {
    CommentValue cv("Test");
    EXPECT_EQ(cv.typeId(), Exiv2::undefined);
}
