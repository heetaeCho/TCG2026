// File: ./TestProjects/tinyxml2/test_xmlutil_tostr_int64_170.cpp

#include <gtest/gtest.h>

#include <cstdint>
#include <cstring>
#include <limits>

#include "tinyxml2.h"

namespace tinyxml2 {

class XMLUtilToStrInt64Test_170 : public ::testing::Test {
protected:
    static constexpr int kBufSize = 64;

    static void Fill(char* buf, int size, unsigned char value = 0xA5) {
        std::memset(buf, value, static_cast<size_t>(size));
    }
};

TEST_F(XMLUtilToStrInt64Test_170, WritesZero_170) {
    char buf[kBufSize];
    Fill(buf, kBufSize);
    XMLUtil::ToStr(static_cast<int64_t>(0), buf, kBufSize);
    EXPECT_STREQ("0", buf);
}

TEST_F(XMLUtilToStrInt64Test_170, WritesPositiveValue_170) {
    char buf[kBufSize];
    Fill(buf, kBufSize);
    XMLUtil::ToStr(static_cast<int64_t>(1234567890LL), buf, kBufSize);
    EXPECT_STREQ("1234567890", buf);
}

TEST_F(XMLUtilToStrInt64Test_170, WritesNegativeValue_170) {
    char buf[kBufSize];
    Fill(buf, kBufSize);
    XMLUtil::ToStr(static_cast<int64_t>(-42), buf, kBufSize);
    EXPECT_STREQ("-42", buf);
}

TEST_F(XMLUtilToStrInt64Test_170, WritesInt64Max_170) {
    char buf[kBufSize];
    Fill(buf, kBufSize);
    const int64_t v = (std::numeric_limits<int64_t>::max)();
    XMLUtil::ToStr(v, buf, kBufSize);

    // 9223372036854775807
    EXPECT_STREQ("9223372036854775807", buf);
}

TEST_F(XMLUtilToStrInt64Test_170, WritesInt64Min_170) {
    char buf[kBufSize];
    Fill(buf, kBufSize);
    const int64_t v = (std::numeric_limits<int64_t>::min)();
    XMLUtil::ToStr(v, buf, kBufSize);

    // -9223372036854775808
    EXPECT_STREQ("-9223372036854775808", buf);
}

TEST_F(XMLUtilToStrInt64Test_170, SmallBufferStillNullTerminates_170) {
    // Boundary condition: buffer size 2 can hold "0" + '\0'
    char buf[2];
    Fill(buf, 2);
    XMLUtil::ToStr(static_cast<int64_t>(0), buf, 2);
    EXPECT_EQ('0', buf[0]);
    EXPECT_EQ('\0', buf[1]);
}

TEST_F(XMLUtilToStrInt64Test_170, BufferSizeOneProducesNullTerminatedString_170) {
    // Boundary condition: with size 1, only room for '\0'.
    char buf[1];
    Fill(buf, 1);
    XMLUtil::ToStr(static_cast<int64_t>(123), buf, 1);
    EXPECT_EQ('\0', buf[0]);
}

TEST_F(XMLUtilToStrInt64Test_170, BufferSizeZeroDoesNotCrash_170) {
    // Error/exceptional-ish case: size 0. We can only assert it doesn't crash.
    // Use a valid pointer to avoid UB from null dereference in some implementations.
    char buf[4];
    Fill(buf, 4);
    EXPECT_NO_THROW(XMLUtil::ToStr(static_cast<int64_t>(123), buf, 0));
}

TEST_F(XMLUtilToStrInt64Test_170, TruncatesLongNumberWhenBufferTooSmall_170) {
    // We don't assume exact truncation strategy beyond null-termination and prefix matching,
    // which is observable without re-implementing formatting.
    char buf[6]; // can hold at most 5 chars + '\0'
    Fill(buf, 6);
    XMLUtil::ToStr(static_cast<int64_t>(123456789LL), buf, 6);

    // Must be null-terminated within buffer.
    EXPECT_EQ('\0', buf[5]);

    // Should start with the correct prefix (since truncation should keep earlier chars).
    // "12345" is the longest possible content here.
    EXPECT_EQ('1', buf[0]);
    EXPECT_EQ('2', buf[1]);
    EXPECT_EQ('3', buf[2]);
    EXPECT_EQ('4', buf[3]);
    EXPECT_EQ('5', buf[4]);
}

TEST_F(XMLUtilToStrInt64Test_170, DoesNotWriteOutsideProvidedBuffer_170) {
    // Place sentinels around a small buffer region and ensure they remain unchanged.
    unsigned char raw[16];
    std::memset(raw, 0xCC, sizeof(raw));

    // Use a sub-span [4..11] as the buffer (size 8).
    char* buf = reinterpret_cast<char*>(raw + 4);
    const int bufSize = 8;

    XMLUtil::ToStr(static_cast<int64_t>(-123456789LL), buf, bufSize);

    // Sentinels before and after should remain intact.
    EXPECT_EQ(0xCC, raw[0]);
    EXPECT_EQ(0xCC, raw[1]);
    EXPECT_EQ(0xCC, raw[2]);
    EXPECT_EQ(0xCC, raw[3]);

    EXPECT_EQ(0xCC, raw[12]);
    EXPECT_EQ(0xCC, raw[13]);
    EXPECT_EQ(0xCC, raw[14]);
    EXPECT_EQ(0xCC, raw[15]);

    // Also ensure buffer is null-terminated within the provided region.
    bool foundNull = false;
    for (int i = 0; i < bufSize; ++i) {
        if (buf[i] == '\0') {
            foundNull = true;
            break;
        }
    }
    EXPECT_TRUE(foundNull);
}

}  // namespace tinyxml2
