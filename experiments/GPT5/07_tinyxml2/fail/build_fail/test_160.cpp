// File: test_strpair_getstr_160.cpp

#include <gtest/gtest.h>
#include <cstring>
#include <string>
#include <vector>

#include "tinyxml2.h"

using namespace tinyxml2;

namespace {

class StrPairGetStrTest_160 : public ::testing::Test {
protected:
    // Creates a writable buffer that ends with a sentinel char, and sets StrPair
    // so that `_end` points to the sentinel (where GetStr() will write '\0' when flushing).
    static void SetFromTextWithSentinel(StrPair& sp,
                                       std::vector<char>& buf,
                                       const char* text,
                                       int flags) {
        const size_t n = std::strlen(text);
        buf.assign(text, text + n);
        buf.push_back('X');              // sentinel at logical end
        // Ensure there is at least one writable byte at end pointer.
        sp.Set(buf.data(), buf.data() + n, flags);
    }
};

}  // namespace

TEST_F(StrPairGetStrTest_160, GetStrFlushesAndReturnsStartPointer_160) {
    StrPair sp;
    std::vector<char> buf;

    // Minimal flush behavior: should write a null terminator at `_end` and return `_start`.
    SetFromTextWithSentinel(sp, buf, "abc", tinyxml2::StrPair::NEEDS_FLUSH);

    const char* out = sp.GetStr();
    ASSERT_NE(out, nullptr);
    EXPECT_EQ(out, buf.data());
    EXPECT_STREQ(out, "abc");
}

TEST_F(StrPairGetStrTest_160, GetStrIsIdempotentAfterFirstCall_160) {
    StrPair sp;
    std::vector<char> buf;

    SetFromTextWithSentinel(sp, buf, "abc", tinyxml2::StrPair::NEEDS_FLUSH);

    const char* out1 = sp.GetStr();
    ASSERT_NE(out1, nullptr);
    EXPECT_STREQ(out1, "abc");

    // Second call should still return a valid, stable C-string.
    const char* out2 = sp.GetStr();
    ASSERT_NE(out2, nullptr);
    EXPECT_EQ(out2, out1);
    EXPECT_STREQ(out2, "abc");
}

TEST_F(StrPairGetStrTest_160, GetStrNormalizesCRLFToLFWhenFlagSet_160) {
    StrPair sp;

    // Build buffer manually so we can include CR/LF bytes explicitly.
    std::vector<char> buf = {'a', '\r', '\n', 'b', 'X'};
    sp.Set(buf.data(), buf.data() + 4,
           tinyxml2::StrPair::NEEDS_FLUSH | tinyxml2::StrPair::NEEDS_NEWLINE_NORMALIZATION);

    const char* out = sp.GetStr();
    ASSERT_NE(out, nullptr);
    EXPECT_STREQ(out, "a\nb");
}

TEST_F(StrPairGetStrTest_160, GetStrNormalizesLFCRToLFWhenFlagSet_160) {
    StrPair sp;

    std::vector<char> buf = {'a', '\n', '\r', 'b', 'X'};
    sp.Set(buf.data(), buf.data() + 4,
           tinyxml2::StrPair::NEEDS_FLUSH | tinyxml2::StrPair::NEEDS_NEWLINE_NORMALIZATION);

    const char* out = sp.GetStr();
    ASSERT_NE(out, nullptr);
    EXPECT_STREQ(out, "a\nb");
}

TEST_F(StrPairGetStrTest_160, GetStrProcessesNamedEntitiesWhenFlagSet_160) {
    StrPair sp;
    std::vector<char> buf;

    SetFromTextWithSentinel(
        sp, buf, "Tom &amp; Jerry &lt;3&gt;",
        tinyxml2::StrPair::NEEDS_FLUSH | tinyxml2::StrPair::NEEDS_ENTITY_PROCESSING);

    const char* out = sp.GetStr();
    ASSERT_NE(out, nullptr);
    EXPECT_STREQ(out, "Tom & Jerry <3>");
}

TEST_F(StrPairGetStrTest_160, GetStrProcessesMultipleEntitiesInSequence_160) {
    StrPair sp;
    std::vector<char> buf;

    SetFromTextWithSentinel(
        sp, buf, "&lt;&gt;&amp;&apos;&quot;",
        tinyxml2::StrPair::NEEDS_FLUSH | tinyxml2::StrPair::NEEDS_ENTITY_PROCESSING);

    const char* out = sp.GetStr();
    ASSERT_NE(out, nullptr);
    EXPECT_STREQ(out, "<>&'\"");
}

TEST_F(StrPairGetStrTest_160, GetStrWithWhitespaceCollapsingDoesNotChangeSimpleText_160) {
    StrPair sp;
    std::vector<char> buf;

    // Choose a string where "collapsing whitespace" should have no observable effect
    // (single internal space, no leading/trailing whitespace).
    SetFromTextWithSentinel(
        sp, buf, "a b",
        tinyxml2::StrPair::NEEDS_FLUSH | tinyxml2::StrPair::NEEDS_WHITESPACE_COLLAPSING);

    const char* out = sp.GetStr();
    ASSERT_NE(out, nullptr);
    EXPECT_STREQ(out, "a b");
}

TEST_F(StrPairGetStrTest_160, GetStrAfterResetTriggersAssertionInDebug_160) {
    StrPair sp;
    sp.Reset();

#if GTEST_HAS_DEATH_TEST && !defined(NDEBUG)
    // In debug builds, GetStr asserts that internal pointers are valid.
    EXPECT_DEATH({ (void)sp.GetStr(); }, ".*");
#else
    // In release builds, we avoid calling GetStr() in an invalid state because behavior
    // may not be observable/defined without assertions.
    GTEST_SKIP() << "Death test requires assertions enabled (debug build).";
#endif
}
