// File: ./TestProjects/tinyxml2/tests/xmlutil_skipwhitespace_test_34.cpp

#include <gtest/gtest.h>
#include <cstring>

#include "tinyxml2.h"

namespace tinyxml2 {

class SkipWhiteSpaceTest_34 : public ::testing::Test {
protected:
    // Helper: returns pointer offset as integer distance from base.
    static ptrdiff_t Offset(const char* base, const char* p) {
        return p - base;
    }
};

TEST_F(SkipWhiteSpaceTest_34, ReturnsSamePointerWhenNoLeadingWhitespace_34) {
    const char* s = "abc";
    int line = 7;
    const char* out = XMLUtil::SkipWhiteSpace(s, &line);

    EXPECT_EQ(out, s);
    EXPECT_STREQ(out, "abc");
    EXPECT_EQ(line, 7); // no newline encountered
}

TEST_F(SkipWhiteSpaceTest_34, SkipsSpacesAndTabs_34) {
    const char* s = " \t\t  abc";
    int line = 0;
    const char* out = XMLUtil::SkipWhiteSpace(s, &line);

    EXPECT_EQ(Offset(s, out), 5); // " \t\t  " = 5 chars
    EXPECT_STREQ(out, "abc");
    EXPECT_EQ(line, 0); // no newline encountered
}

TEST_F(SkipWhiteSpaceTest_34, SkipsNewlinesAndIncrementsLineCounter_34) {
    const char* s = "\n\n  \tX";
    int line = 10;
    const char* out = XMLUtil::SkipWhiteSpace(s, &line);

    // Two '\n' then two spaces then one tab => 5 chars skipped.
    EXPECT_EQ(Offset(s, out), 5);
    EXPECT_EQ(*out, 'X');
    EXPECT_EQ(line, 12); // incremented for each '\n'
}

TEST_F(SkipWhiteSpaceTest_34, HandlesNullLineCounterPointer_34) {
    const char* s = "\n \tZ";
    const char* out = XMLUtil::SkipWhiteSpace(s, nullptr);

    EXPECT_EQ(*out, 'Z');
}

TEST_F(SkipWhiteSpaceTest_34, ReturnsPointerToNullTerminatorWhenAllWhitespace_34) {
    const char* s = " \t\n\r";
    int line = 1;
    const char* out = XMLUtil::SkipWhiteSpace(s, &line);

    // Should end at string terminator.
    EXPECT_EQ(*out, '\0');

    // At least verifies newline counting is observable (only for '\n').
    // The input has exactly one '\n'.
    EXPECT_EQ(line, 2);
}

TEST_F(SkipWhiteSpaceTest_34, EmptyStringReturnsSamePointer_34) {
    const char* s = "";
    int line = 3;
    const char* out = XMLUtil::SkipWhiteSpace(s, &line);

    EXPECT_EQ(out, s);
    EXPECT_EQ(*out, '\0');
    EXPECT_EQ(line, 3);
}

// Optional: observable error behavior when passing nullptr.
// Many builds compile tinyxml2 with assertions enabled (TIXMLASSERT),
// which typically aborts. Guarding this keeps tests stable in release builds.
#ifndef NDEBUG
TEST_F(SkipWhiteSpaceTest_34, DeathOnNullInputPointerInDebug_34) {
    int line = 0;
    ASSERT_DEATH((void)XMLUtil::SkipWhiteSpace(nullptr, &line), ".*");
}
#endif

} // namespace tinyxml2
