// TEST_ID: 159
// File: test_strpair_parsename_159.cpp

#include <gtest/gtest.h>

#include "TestProjects/tinyxml2/tinyxml2.h"

using namespace tinyxml2;

class StrPairParseNameTest_159 : public ::testing::Test {
protected:
    StrPair sp;
};

TEST_F(StrPairParseNameTest_159, NullInputReturnsNull_159) {
    char* p = nullptr;

    char* ret = sp.ParseName(p);

    EXPECT_EQ(ret, nullptr);
    EXPECT_TRUE(sp.Empty());
}

TEST_F(StrPairParseNameTest_159, EmptyStringReturnsNull_159) {
    char buf[] = "";

    char* ret = sp.ParseName(buf);

    EXPECT_EQ(ret, nullptr);
    EXPECT_TRUE(sp.Empty());
}

TEST_F(StrPairParseNameTest_159, InvalidStartCharacterReturnsNull_159) {
    char buf[] = "1abc";

    char* ret = sp.ParseName(buf);

    EXPECT_EQ(ret, nullptr);
    EXPECT_TRUE(sp.Empty());
}

TEST_F(StrPairParseNameTest_159, ParsesSimpleNameAdvancesToNullTerminator_159) {
    char buf[] = "abc";

    char* ret = sp.ParseName(buf);

    ASSERT_NE(ret, nullptr);
    EXPECT_EQ(ret, buf + 3);                  // points at '\0'
    ASSERT_NE(sp.GetStr(), nullptr);
    EXPECT_STREQ(sp.GetStr(), "abc");
    EXPECT_FALSE(sp.Empty());
}

TEST_F(StrPairParseNameTest_159, ParsesNameStopsAtFirstNonNameChar_159) {
    char buf[] = "abc def";

    char* ret = sp.ParseName(buf);

    ASSERT_NE(ret, nullptr);
    EXPECT_EQ(*ret, ' ');                     // stopped at space
    ASSERT_NE(sp.GetStr(), nullptr);
    EXPECT_STREQ(sp.GetStr(), "abc");
    EXPECT_FALSE(sp.Empty());
}

TEST_F(StrPairParseNameTest_159, SingleCharacterNameParsesCorrectly_159) {
    char buf[] = "a";

    char* ret = sp.ParseName(buf);

    ASSERT_NE(ret, nullptr);
    EXPECT_EQ(ret, buf + 1);
    ASSERT_NE(sp.GetStr(), nullptr);
    EXPECT_STREQ(sp.GetStr(), "a");
    EXPECT_FALSE(sp.Empty());
}

TEST_F(StrPairParseNameTest_159, ParsesNameWithCommonXmlNameCharsUntilDelimiter_159) {
    // Uses common XML NameChar candidates after a valid ASCII start:
    // digits, underscore, hyphen, dot, colon.
    char buf[] = "a1_b-.:c/";

    char* ret = sp.ParseName(buf);

    ASSERT_NE(ret, nullptr);
    EXPECT_EQ(*ret, '/');                     // delimiter
    ASSERT_NE(sp.GetStr(), nullptr);
    EXPECT_STREQ(sp.GetStr(), "a1_b-.:c");
    EXPECT_FALSE(sp.Empty());
}

TEST_F(StrPairParseNameTest_159, ReuseAfterResetParsesNewName_159) {
    char first[] = "first ";
    char second[] = "second";

    char* ret1 = sp.ParseName(first);
    ASSERT_NE(ret1, nullptr);
    ASSERT_NE(sp.GetStr(), nullptr);
    EXPECT_STREQ(sp.GetStr(), "first");

    sp.Reset();
    EXPECT_TRUE(sp.Empty());

    char* ret2 = sp.ParseName(second);
    ASSERT_NE(ret2, nullptr);
    ASSERT_NE(sp.GetStr(), nullptr);
    EXPECT_STREQ(sp.GetStr(), "second");
    EXPECT_FALSE(sp.Empty());
}
