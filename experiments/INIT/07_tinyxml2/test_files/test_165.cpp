// File: ./TestProjects/tinyxml2/xmlutil_tostr_int_test_165.cpp

#include <gtest/gtest.h>

#include <climits>
#include <cstring>
#include <string>

#include "tinyxml2.h"

namespace {

class XMLUtilToStrIntTest_165 : public ::testing::Test {
protected:
    static std::string CallToStr(int v, int bufferSize) {
        // Allocate a little extra so we can also do sentinel checks when desired.
        std::string storage(static_cast<size_t>(bufferSize > 0 ? bufferSize : 1), '\x7F');
        tinyxml2::XMLUtil::ToStr(v, storage.data(), bufferSize);
        // If bufferSize <= 0, storage content isn't meaningful as a C-string.
        if (bufferSize <= 0) {
            return std::string();
        }
        // Ensure we only read within the provided buffer.
        return std::string(storage.c_str());
    }
};

TEST_F(XMLUtilToStrIntTest_165, FormatsZero_165) {
    char buf[32] = {};
    tinyxml2::XMLUtil::ToStr(0, buf, static_cast<int>(sizeof(buf)));
    EXPECT_STREQ("0", buf);
}

TEST_F(XMLUtilToStrIntTest_165, FormatsPositiveNumber_165) {
    char buf[32] = {};
    tinyxml2::XMLUtil::ToStr(12345, buf, static_cast<int>(sizeof(buf)));
    EXPECT_STREQ("12345", buf);
}

TEST_F(XMLUtilToStrIntTest_165, FormatsNegativeNumber_165) {
    char buf[32] = {};
    tinyxml2::XMLUtil::ToStr(-678, buf, static_cast<int>(sizeof(buf)));
    EXPECT_STREQ("-678", buf);
}

TEST_F(XMLUtilToStrIntTest_165, FormatsIntMax_165) {
    char buf[64] = {};
    tinyxml2::XMLUtil::ToStr(INT_MAX, buf, static_cast<int>(sizeof(buf)));
    EXPECT_EQ(std::to_string(INT_MAX), std::string(buf));
}

TEST_F(XMLUtilToStrIntTest_165, FormatsIntMin_165) {
    char buf[64] = {};
    tinyxml2::XMLUtil::ToStr(INT_MIN, buf, static_cast<int>(sizeof(buf)));
    EXPECT_EQ(std::to_string(INT_MIN), std::string(buf));
}

TEST_F(XMLUtilToStrIntTest_165, BufferSizeOneWritesOnlyNullTerminator_165) {
    // With size 1, a snprintf-like routine can only write '\0'.
    char buf[1];
    buf[0] = 'X';
    tinyxml2::XMLUtil::ToStr(42, buf, 1);
    EXPECT_EQ('\0', buf[0]);
}

TEST_F(XMLUtilToStrIntTest_165, BufferSizeZeroDoesNotOverwriteMemoryPastBuffer_165) {
    // Provide a valid pointer but bufferSize=0: should not write any bytes.
    // We check adjacent sentinel bytes remain unchanged.
    unsigned char raw[4];
    raw[0] = 0xAA;  // "buffer" start
    raw[1] = 0xBB;  // sentinel 1
    raw[2] = 0xCC;  // sentinel 2
    raw[3] = 0xDD;  // sentinel 3

    char* buf = reinterpret_cast<char*>(&raw[0]);
    tinyxml2::XMLUtil::ToStr(999, buf, 0);

    EXPECT_EQ(0xAA, raw[0]);
    EXPECT_EQ(0xBB, raw[1]);
    EXPECT_EQ(0xCC, raw[2]);
    EXPECT_EQ(0xDD, raw[3]);
}

TEST_F(XMLUtilToStrIntTest_165, TruncatesAndNullTerminatesWhenBufferTooSmall_165) {
    // "12345" needs 6 bytes including null. Give only 3 => expect "12" + '\0'.
    char buf[3];
    buf[0] = 'X';
    buf[1] = 'Y';
    buf[2] = 'Z';

    tinyxml2::XMLUtil::ToStr(12345, buf, 3);

    // Must be null-terminated within the buffer.
    EXPECT_EQ('\0', buf[2]);
    // And should contain the prefix that fits.
    EXPECT_EQ('1', buf[0]);
    EXPECT_EQ('2', buf[1]);
}

TEST_F(XMLUtilToStrIntTest_165, DoesNotWriteBeyondProvidedBufferSize_165) {
    // Place sentinels right after the writable region and ensure they remain unchanged.
    // Writable region length = kSize.
    constexpr int kSize = 8;
    unsigned char raw[kSize + 2];

    std::memset(raw, 0xEE, sizeof(raw));
    raw[kSize] = 0x11;     // sentinel
    raw[kSize + 1] = 0x22; // sentinel

    char* buf = reinterpret_cast<char*>(raw);
    tinyxml2::XMLUtil::ToStr(-1234567, buf, kSize);

    // Verify sentinels weren't touched.
    EXPECT_EQ(0x11, raw[kSize]);
    EXPECT_EQ(0x22, raw[kSize + 1]);

    // Also ensure the produced string is null-terminated within kSize bytes.
    bool hasNull = false;
    for (int i = 0; i < kSize; ++i) {
        if (buf[i] == '\0') {
            hasNull = true;
            break;
        }
    }
    EXPECT_TRUE(hasNull);
}

}  // namespace
