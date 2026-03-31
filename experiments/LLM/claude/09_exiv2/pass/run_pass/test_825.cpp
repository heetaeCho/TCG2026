#include <gtest/gtest.h>
#include <string>
#include "exiv2/value.hpp"
#include "exiv2/types.hpp"

using namespace Exiv2;

class CommentValueTest_825 : public ::testing::Test {
protected:
    void SetUp() override {
    }
};

// Test: detectCharset identifies UTF-8 BOM and strips it
TEST_F(CommentValueTest_825, DetectCharsetUTF8BOM_825) {
    CommentValue cv;
    // Read with little endian byte order (shouldn't matter for BOM detection)
    const byte utf8Data[] = {0xef, 0xbb, 0xbf, 'H', 'e', 'l', 'l', 'o'};
    cv.read(utf8Data, sizeof(utf8Data), littleEndian);

    std::string c(reinterpret_cast<const char*>(utf8Data), sizeof(utf8Data));
    const char* charset = cv.detectCharset(c);

    EXPECT_STREQ(charset, "UTF-8");
    EXPECT_EQ(c, "Hello");
}

// Test: detectCharset identifies UCS-2LE BOM and strips it
TEST_F(CommentValueTest_825, DetectCharsetUCS2LEBOM_825) {
    CommentValue cv;
    const byte ucs2leData[] = {0xff, 0xfe, 'H', 0, 'i', 0};
    cv.read(ucs2leData, sizeof(ucs2leData), littleEndian);

    std::string c(reinterpret_cast<const char*>(ucs2leData), sizeof(ucs2leData));
    const char* charset = cv.detectCharset(c);

    EXPECT_STREQ(charset, "UCS-2LE");
    // BOM should be stripped (first 2 bytes removed)
    std::string expected(reinterpret_cast<const char*>(ucs2leData + 2), sizeof(ucs2leData) - 2);
    EXPECT_EQ(c, expected);
}

// Test: detectCharset identifies UCS-2BE BOM and strips it
TEST_F(CommentValueTest_825, DetectCharsetUCS2BEBOM_825) {
    CommentValue cv;
    const byte ucs2beData[] = {0xfe, 0xff, 0, 'H', 0, 'i'};
    cv.read(ucs2beData, sizeof(ucs2beData), bigEndian);

    std::string c(reinterpret_cast<const char*>(ucs2beData), sizeof(ucs2beData));
    const char* charset = cv.detectCharset(c);

    EXPECT_STREQ(charset, "UCS-2BE");
    // BOM should be stripped (first 2 bytes removed)
    std::string expected(reinterpret_cast<const char*>(ucs2beData + 2), sizeof(ucs2beData) - 2);
    EXPECT_EQ(c, expected);
}

// Test: detectCharset falls back to UCS-2LE when byte order is little endian and no BOM
TEST_F(CommentValueTest_825, DetectCharsetNoBOMLittleEndian_825) {
    CommentValue cv;
    const byte data[] = {'H', 0, 'i', 0};
    cv.read(data, sizeof(data), littleEndian);

    std::string c(reinterpret_cast<const char*>(data), sizeof(data));
    const char* charset = cv.detectCharset(c);

    EXPECT_STREQ(charset, "UCS-2LE");
    // String should not be modified when there's no BOM
    std::string expected(reinterpret_cast<const char*>(data), sizeof(data));
    EXPECT_EQ(c, expected);
}

// Test: detectCharset falls back to UCS-2BE when byte order is big endian and no BOM
TEST_F(CommentValueTest_825, DetectCharsetNoBOMBigEndian_825) {
    CommentValue cv;
    const byte data[] = {0, 'H', 0, 'i'};
    cv.read(data, sizeof(data), bigEndian);

    std::string c(reinterpret_cast<const char*>(data), sizeof(data));
    const char* charset = cv.detectCharset(c);

    EXPECT_STREQ(charset, "UCS-2BE");
    // String should not be modified when there's no BOM
    std::string expected(reinterpret_cast<const char*>(data), sizeof(data));
    EXPECT_EQ(c, expected);
}

// Test: UTF-8 BOM with empty content after BOM
TEST_F(CommentValueTest_825, DetectCharsetUTF8BOMEmptyContent_825) {
    CommentValue cv;
    const byte utf8BomOnly[] = {0xef, 0xbb, 0xbf};
    cv.read(utf8BomOnly, sizeof(utf8BomOnly), littleEndian);

    std::string c(reinterpret_cast<const char*>(utf8BomOnly), sizeof(utf8BomOnly));
    const char* charset = cv.detectCharset(c);

    EXPECT_STREQ(charset, "UTF-8");
    EXPECT_TRUE(c.empty());
}

// Test: UCS-2LE BOM with empty content after BOM
TEST_F(CommentValueTest_825, DetectCharsetUCS2LEBOMEmptyContent_825) {
    CommentValue cv;
    const byte ucs2leBomOnly[] = {0xff, 0xfe};
    cv.read(ucs2leBomOnly, sizeof(ucs2leBomOnly), littleEndian);

    std::string c(reinterpret_cast<const char*>(ucs2leBomOnly), sizeof(ucs2leBomOnly));
    const char* charset = cv.detectCharset(c);

    EXPECT_STREQ(charset, "UCS-2LE");
    EXPECT_TRUE(c.empty());
}

// Test: UCS-2BE BOM with empty content after BOM
TEST_F(CommentValueTest_825, DetectCharsetUCS2BEBOMEmptyContent_825) {
    CommentValue cv;
    const byte ucs2beBomOnly[] = {0xfe, 0xff};
    cv.read(ucs2beBomOnly, sizeof(ucs2beBomOnly), bigEndian);

    std::string c(reinterpret_cast<const char*>(ucs2beBomOnly), sizeof(ucs2beBomOnly));
    const char* charset = cv.detectCharset(c);

    EXPECT_STREQ(charset, "UCS-2BE");
    EXPECT_TRUE(c.empty());
}

// Test: Default constructor creates a valid CommentValue
TEST_F(CommentValueTest_825, DefaultConstructor_825) {
    CommentValue cv;
    // Should be constructible without error
    SUCCEED();
}

// Test: Constructor with string parameter
TEST_F(CommentValueTest_825, StringConstructor_825) {
    CommentValue cv("charset=\"Ascii\" Hello World");
    std::string comment = cv.comment();
    // We just verify it doesn't crash and returns something
    EXPECT_FALSE(comment.empty());
}

// Test: read from string
TEST_F(CommentValueTest_825, ReadFromString_825) {
    CommentValue cv;
    int result = cv.read("charset=\"Ascii\" Test comment");
    EXPECT_EQ(result, 0);
}

// Test: clone returns a valid object
TEST_F(CommentValueTest_825, Clone_825) {
    CommentValue cv("charset=\"Ascii\" Test");
    auto cloned = cv.clone();
    EXPECT_NE(cloned.get(), nullptr);
}

// Test: write to ostream
TEST_F(CommentValueTest_825, WriteToOstream_825) {
    CommentValue cv("charset=\"Ascii\" Hello");
    std::ostringstream os;
    cv.write(os);
    // Just verify it produces some output
    EXPECT_FALSE(os.str().empty());
}

// Test: detectCharset with data starting with 0xef but not full UTF-8 BOM
// (0xef followed by something other than 0xbb)
TEST_F(CommentValueTest_825, DetectCharsetPartialUTF8BOM_825) {
    CommentValue cv;
    const byte data[] = {0xef, 0x00, 0x00, 'H', 'e', 'l', 'l', 'o'};
    cv.read(data, sizeof(data), littleEndian);

    std::string c(reinterpret_cast<const char*>(data), sizeof(data));
    const char* charset = cv.detectCharset(c);

    // Should fall back to byte order based detection since it's not a valid BOM
    EXPECT_STREQ(charset, "UCS-2LE");
}

// Test: detectCharset with data starting with 0xff but second byte not 0xfe
TEST_F(CommentValueTest_825, DetectCharsetPartialUCS2LEBOM_825) {
    CommentValue cv;
    const byte data[] = {0xff, 0x00, 'H', 'i'};
    cv.read(data, sizeof(data), bigEndian);

    std::string c(reinterpret_cast<const char*>(data), sizeof(data));
    const char* charset = cv.detectCharset(c);

    // Should fall back to byte order based detection
    EXPECT_STREQ(charset, "UCS-2BE");
}

// Test: detectCharset with data starting with 0xfe but second byte not 0xff
TEST_F(CommentValueTest_825, DetectCharsetPartialUCS2BEBOM_825) {
    CommentValue cv;
    const byte data[] = {0xfe, 0x00, 'H', 'i'};
    cv.read(data, sizeof(data), littleEndian);

    std::string c(reinterpret_cast<const char*>(data), sizeof(data));
    const char* charset = cv.detectCharset(c);

    // Should fall back to byte order based detection
    EXPECT_STREQ(charset, "UCS-2LE");
}

// Test: copy to buffer
TEST_F(CommentValueTest_825, CopyToBuffer_825) {
    CommentValue cv("charset=\"Ascii\" Test");
    byte buf[256] = {0};
    size_t copied = cv.copy(buf, littleEndian);
    EXPECT_GT(copied, 0u);
}

// Test: charsetId returns a valid charset
TEST_F(CommentValueTest_825, CharsetId_825) {
    CommentValue cv("charset=\"Ascii\" Hello");
    auto id = cv.charsetId();
    // Just verify it doesn't crash; the exact value depends on implementation
    (void)id;
    SUCCEED();
}

// Test: read from byte buffer with little endian
TEST_F(CommentValueTest_825, ReadFromByteBufferLittleEndian_825) {
    CommentValue cv;
    const byte data[] = {'A', 'S', 'C', 'I', 'I', 0, 0, 0, 'H', 'e', 'l', 'l', 'o'};
    int result = cv.read(data, sizeof(data), littleEndian);
    EXPECT_EQ(result, 0);
}

// Test: read from byte buffer with big endian
TEST_F(CommentValueTest_825, ReadFromByteBufferBigEndian_825) {
    CommentValue cv;
    const byte data[] = {'A', 'S', 'C', 'I', 'I', 0, 0, 0, 'H', 'e', 'l', 'l', 'o'};
    int result = cv.read(data, sizeof(data), bigEndian);
    EXPECT_EQ(result, 0);
}
