// TEST_ID: 166
#include <gtest/gtest.h>
#include <limits>
#include <cstring>

#include "TestProjects/tinyxml2/tinyxml2.h"

namespace {

class XMLUtilToStrUnsignedTest_166 : public ::testing::Test {
protected:
    tinyxml2::XMLUtil util;
};

TEST_F(XMLUtilToStrUnsignedTest_166, ConvertsTypicalValue_166) {
    char buf[32] = {};
    util.ToStr(12345u, buf, static_cast<int>(sizeof(buf)));
    EXPECT_STREQ("12345", buf);
}

TEST_F(XMLUtilToStrUnsignedTest_166, ConvertsZero_166) {
    char buf[8] = {};
    util.ToStr(0u, buf, static_cast<int>(sizeof(buf)));
    EXPECT_STREQ("0", buf);
}

TEST_F(XMLUtilToStrUnsignedTest_166, ConvertsMaxUnsigned_166) {
    char buf[64] = {};
    const unsigned maxU = std::numeric_limits<unsigned>::max();
    util.ToStr(maxU, buf, static_cast<int>(sizeof(buf)));

    // Compare against a reference formatting done by the C library.
    char ref[64] = {};
    std::snprintf(ref, sizeof(ref), "%u", maxU);
    EXPECT_STREQ(ref, buf);
}

TEST_F(XMLUtilToStrUnsignedTest_166, TruncatesWhenBufferTooSmall_166) {
    // "12345" needs 6 bytes including '\0'. Provide only 4 -> should hold "123" + '\0'.
    char buf[8];
    std::memset(buf, 'Z', sizeof(buf));

    util.ToStr(12345u, buf, 4);

    EXPECT_EQ('1', buf[0]);
    EXPECT_EQ('2', buf[1]);
    EXPECT_EQ('3', buf[2]);
    EXPECT_EQ('\0', buf[3]);        // must be terminated within provided size (when size > 0)
    EXPECT_EQ('Z', buf[4]);         // verify no write beyond bufferSize
    EXPECT_EQ('Z', buf[5]);
}

TEST_F(XMLUtilToStrUnsignedTest_166, BufferSizeOneLeavesOnlyTerminator_166) {
    char buf[4];
    std::memset(buf, 'Q', sizeof(buf));

    util.ToStr(999u, buf, 1);

    // With size 1, only room for '\0' (no digits).
    EXPECT_EQ('\0', buf[0]);
    EXPECT_EQ('Q', buf[1]); // ensure no overwrite beyond bufferSize
}

TEST_F(XMLUtilToStrUnsignedTest_166, BufferSizeZeroDoesNotWritePastBuffer_166) {
    char buf[4];
    std::memset(buf, 'A', sizeof(buf));

    // Observable requirement: should not crash. For size 0, we only verify no memory past start is modified.
    util.ToStr(42u, buf, 0);

    EXPECT_EQ('A', buf[0]);
    EXPECT_EQ('A', buf[1]);
    EXPECT_EQ('A', buf[2]);
    EXPECT_EQ('A', buf[3]);
}

} // namespace
