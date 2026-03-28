// File: ./TestProjects/tinyxml2/StrPair_ParseText_158_test.cpp

#include <gtest/gtest.h>
#include <cstring>
#include <string>
#include <vector>

#include "tinyxml2.h"

using namespace tinyxml2;

namespace {

class StrPairParseTextTest_158 : public ::testing::Test {
protected:
    static std::vector<char> MakeBuffer(const std::string& s) {
        std::vector<char> buf(s.begin(), s.end());
        buf.push_back('\0');
        return buf;
    }
};

TEST_F(StrPairParseTextTest_158, ReturnsPointerAfterEndTagAndStoresText_158) {
    StrPair sp;

    auto buf = MakeBuffer("hello</tag>trailing");
    char* p = buf.data();
    int line = 1;

    char* ret = sp.ParseText(p, "</tag>", /*strFlags=*/0, &line);

    ASSERT_NE(ret, nullptr);
    EXPECT_EQ(ret, p + std::strlen("hello</tag>"));
    EXPECT_EQ(line, 1);

    const char* s = sp.GetStr();
    ASSERT_NE(s, nullptr);
    EXPECT_STREQ(s, "hello");
}

TEST_F(StrPairParseTextTest_158, IncrementsLineNumberForNewlinesBeforeEndTag_158) {
    StrPair sp;

    auto buf = MakeBuffer("a\nb\nc</tag>");
    char* p = buf.data();
    int line = 10;

    char* ret = sp.ParseText(p, "</tag>", /*strFlags=*/0, &line);

    ASSERT_NE(ret, nullptr);
    EXPECT_EQ(ret, p + std::strlen("a\nb\nc</tag>"));
    EXPECT_EQ(line, 12);  // two '\n' encountered

    const char* s = sp.GetStr();
    ASSERT_NE(s, nullptr);
    EXPECT_STREQ(s, "a\nb\nc");
}

TEST_F(StrPairParseTextTest_158, SkipsPartialMatchesAndFindsLaterExactEndTag_158) {
    StrPair sp;

    auto buf = MakeBuffer("x</taX>y</tag>z");
    char* p = buf.data();
    int line = 1;

    char* ret = sp.ParseText(p, "</tag>", /*strFlags=*/0, &line);

    ASSERT_NE(ret, nullptr);
    // Should return after the exact "</tag>" (not after "</taX>")
    const std::string prefix_up_to_exact = "x</taX>y</tag>";
    EXPECT_EQ(ret, p + static_cast<std::ptrdiff_t>(prefix_up_to_exact.size()));
    EXPECT_EQ(line, 1);

    const char* s = sp.GetStr();
    ASSERT_NE(s, nullptr);
    EXPECT_STREQ(s, "x</taX>y");
}

TEST_F(StrPairParseTextTest_158, EndTagAtStartProducesEmptyText_158) {
    StrPair sp;

    auto buf = MakeBuffer("</tag>after");
    char* p = buf.data();
    int line = 1;

    char* ret = sp.ParseText(p, "</tag>", /*strFlags=*/0, &line);

    ASSERT_NE(ret, nullptr);
    EXPECT_EQ(ret, p + std::strlen("</tag>"));
    EXPECT_EQ(line, 1);

    const char* s = sp.GetStr();
    // Be tolerant: some implementations may return "" or possibly nullptr for empty.
    EXPECT_TRUE(s == nullptr || std::string(s).empty());
}

TEST_F(StrPairParseTextTest_158, ReturnsNullWhenEndTagNotFoundAndDoesNotAdvanceLinePastInput_158) {
    StrPair sp;

    auto buf = MakeBuffer("no end tag here\nstill none");
    char* p = buf.data();
    int line = 5;

    EXPECT_TRUE(sp.Empty());

    char* ret = sp.ParseText(p, "</tag>", /*strFlags=*/0, &line);

    EXPECT_EQ(ret, nullptr);
    // One newline exists in the input; ParseText should count it while scanning.
    EXPECT_EQ(line, 6);

    // Observable state should still look empty if parsing failed (best-effort check).
    EXPECT_TRUE(sp.Empty());
}

TEST_F(StrPairParseTextTest_158, CanStartParsingFromMiddleOfBuffer_158) {
    StrPair sp;

    auto buf = MakeBuffer("prefix:DATA</tag>suffix");
    char* p = buf.data();
    char* start = p + std::strlen("prefix:");
    int line = 1;

    char* ret = sp.ParseText(start, "</tag>", /*strFlags=*/0, &line);

    ASSERT_NE(ret, nullptr);
    EXPECT_EQ(ret, start + std::strlen("DATA</tag>"));

    const char* s = sp.GetStr();
    ASSERT_NE(s, nullptr);
    EXPECT_STREQ(s, "DATA");
}

TEST_F(StrPairParseTextTest_158, HandlesMultiCharacterEndTag_158) {
    StrPair sp;

    auto buf = MakeBuffer("content]]>tail");
    char* p = buf.data();
    int line = 1;

    char* ret = sp.ParseText(p, "]]>", /*strFlags=*/0, &line);

    ASSERT_NE(ret, nullptr);
    EXPECT_EQ(ret, p + std::strlen("content]]>"));
    EXPECT_EQ(line, 1);

    const char* s = sp.GetStr();
    ASSERT_NE(s, nullptr);
    EXPECT_STREQ(s, "content");
}

#if GTEST_HAS_DEATH_TEST
TEST_F(StrPairParseTextTest_158, DeathOnNullInputPointer_158) {
    StrPair sp;
    int line = 1;
    EXPECT_DEATH_IF_SUPPORTED(sp.ParseText(nullptr, "</tag>", 0, &line), "");
}

TEST_F(StrPairParseTextTest_158, DeathOnNullEndTag_158) {
    StrPair sp;
    auto buf = MakeBuffer("abc</tag>");
    int line = 1;
    EXPECT_DEATH_IF_SUPPORTED(sp.ParseText(buf.data(), nullptr, 0, &line), "");
}

TEST_F(StrPairParseTextTest_158, DeathOnEmptyEndTag_158) {
    StrPair sp;
    auto buf = MakeBuffer("abc</tag>");
    int line = 1;
    EXPECT_DEATH_IF_SUPPORTED(sp.ParseText(buf.data(), "", 0, &line), "");
}

TEST_F(StrPairParseTextTest_158, DeathOnNullLineNumberPointer_158) {
    StrPair sp;
    auto buf = MakeBuffer("abc</tag>");
    EXPECT_DEATH_IF_SUPPORTED(sp.ParseText(buf.data(), "</tag>", 0, nullptr), "");
}
#endif  // GTEST_HAS_DEATH_TEST

}  // namespace
