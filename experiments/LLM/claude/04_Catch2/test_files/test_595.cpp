#include <gtest/gtest.h>
#include <vector>
#include <string>

// Include the necessary headers
#include "catch2/internal/catch_stringref.hpp"

namespace Catch {
    std::vector<StringRef> splitStringRef(StringRef str, char delimiter);
}

class SplitStringRefTest_595 : public ::testing::Test {
protected:
    // Helper to convert vector of StringRef to vector of string for easier comparison
    std::vector<std::string> toStrings(const std::vector<Catch::StringRef>& refs) {
        std::vector<std::string> result;
        for (const auto& ref : refs) {
            result.push_back(std::string(ref));
        }
        return result;
    }
};

TEST_F(SplitStringRefTest_595, EmptyString_595) {
    auto result = Catch::splitStringRef(Catch::StringRef(""), ',');
    EXPECT_TRUE(result.empty());
}

TEST_F(SplitStringRefTest_595, NoDelimiterPresent_595) {
    auto result = Catch::splitStringRef(Catch::StringRef("hello"), ',');
    auto strings = toStrings(result);
    ASSERT_EQ(strings.size(), 1u);
    EXPECT_EQ(strings[0], "hello");
}

TEST_F(SplitStringRefTest_595, SingleDelimiterInMiddle_595) {
    auto result = Catch::splitStringRef(Catch::StringRef("hello,world"), ',');
    auto strings = toStrings(result);
    ASSERT_EQ(strings.size(), 2u);
    EXPECT_EQ(strings[0], "hello");
    EXPECT_EQ(strings[1], "world");
}

TEST_F(SplitStringRefTest_595, MultipleDelimiters_595) {
    auto result = Catch::splitStringRef(Catch::StringRef("a,b,c,d"), ',');
    auto strings = toStrings(result);
    ASSERT_EQ(strings.size(), 4u);
    EXPECT_EQ(strings[0], "a");
    EXPECT_EQ(strings[1], "b");
    EXPECT_EQ(strings[2], "c");
    EXPECT_EQ(strings[3], "d");
}

TEST_F(SplitStringRefTest_595, DelimiterAtStart_595) {
    // When delimiter is at start, the substring before it has length 0 which is not > 1, so it's skipped
    auto result = Catch::splitStringRef(Catch::StringRef(",hello"), ',');
    auto strings = toStrings(result);
    ASSERT_EQ(strings.size(), 1u);
    EXPECT_EQ(strings[0], "hello");
}

TEST_F(SplitStringRefTest_595, DelimiterAtEnd_595) {
    auto result = Catch::splitStringRef(Catch::StringRef("hello,"), ',');
    auto strings = toStrings(result);
    // "hello" has length 5 > 1, so it's included. After delimiter, nothing remains.
    ASSERT_EQ(strings.size(), 1u);
    EXPECT_EQ(strings[0], "hello");
}

TEST_F(SplitStringRefTest_595, ConsecutiveDelimiters_595) {
    // Two consecutive delimiters: substring between them has length 0, not > 1, so skipped
    auto result = Catch::splitStringRef(Catch::StringRef("a,,b"), ',');
    auto strings = toStrings(result);
    ASSERT_EQ(strings.size(), 2u);
    EXPECT_EQ(strings[0], "a");
    EXPECT_EQ(strings[1], "b");
}

TEST_F(SplitStringRefTest_595, OnlyDelimiters_595) {
    auto result = Catch::splitStringRef(Catch::StringRef(",,,"), ',');
    EXPECT_TRUE(result.empty());
}

TEST_F(SplitStringRefTest_595, SingleCharNoDelimiter_595) {
    auto result = Catch::splitStringRef(Catch::StringRef("x"), ',');
    auto strings = toStrings(result);
    ASSERT_EQ(strings.size(), 1u);
    EXPECT_EQ(strings[0], "x");
}

TEST_F(SplitStringRefTest_595, SingleCharIsDelimiter_595) {
    auto result = Catch::splitStringRef(Catch::StringRef(","), ',');
    EXPECT_TRUE(result.empty());
}

TEST_F(SplitStringRefTest_595, SingleCharSubstringsSkipped_595) {
    // The condition is pos - start > 1, meaning single character substrings between delimiters ARE included
    // Wait, let me re-read: if pos - start > 1, it pushes. So if pos - start == 1 (single char), it does NOT push.
    // This is a quirky behavior: single character tokens between delimiters are dropped
    auto result = Catch::splitStringRef(Catch::StringRef(",a,"), ',');
    auto strings = toStrings(result);
    // 'a' is between positions 1 and 2, so pos=2, start=1, pos-start=1 which is NOT > 1, so 'a' is dropped
    EXPECT_TRUE(result.empty());
}

TEST_F(SplitStringRefTest_595, TwoCharSubstringKept_595) {
    // pos - start > 1 means length 2 or more is kept
    auto result = Catch::splitStringRef(Catch::StringRef(",ab,"), ',');
    auto strings = toStrings(result);
    ASSERT_EQ(strings.size(), 1u);
    EXPECT_EQ(strings[0], "ab");
}

TEST_F(SplitStringRefTest_595, SingleCharAtEndKept_595) {
    // After last delimiter, the trailing part uses: start < str.size(), so it pushes regardless of length
    // Actually the trailing part is pushed via substr(start, str.size()-start) without the > 1 check
    auto result = Catch::splitStringRef(Catch::StringRef(",a"), ',');
    auto strings = toStrings(result);
    ASSERT_EQ(strings.size(), 1u);
    EXPECT_EQ(strings[0], "a");
}

TEST_F(SplitStringRefTest_595, DifferentDelimiter_595) {
    auto result = Catch::splitStringRef(Catch::StringRef("hello world test"), ' ');
    auto strings = toStrings(result);
    ASSERT_EQ(strings.size(), 3u);
    EXPECT_EQ(strings[0], "hello");
    EXPECT_EQ(strings[1], "world");
    EXPECT_EQ(strings[2], "test");
}

TEST_F(SplitStringRefTest_595, NewlineDelimiter_595) {
    auto result = Catch::splitStringRef(Catch::StringRef("line1\nline2\nline3"), '\n');
    auto strings = toStrings(result);
    ASSERT_EQ(strings.size(), 3u);
    EXPECT_EQ(strings[0], "line1");
    EXPECT_EQ(strings[1], "line2");
    EXPECT_EQ(strings[2], "line3");
}

TEST_F(SplitStringRefTest_595, MixOfSingleAndMultiCharTokens_595) {
    // Between delimiters: "ab" (len 2, kept), "c" (len 1, dropped), "de" (len 2, kept)
    auto result = Catch::splitStringRef(Catch::StringRef("ab,c,de"), ',');
    auto strings = toStrings(result);
    ASSERT_EQ(strings.size(), 2u);
    EXPECT_EQ(strings[0], "ab");
    EXPECT_EQ(strings[1], "de");
}

TEST_F(SplitStringRefTest_595, TrailingSingleCharAfterDelimiter_595) {
    // Trailing "c" after last delimiter uses the non-length-checked path
    auto result = Catch::splitStringRef(Catch::StringRef("ab,c"), ',');
    auto strings = toStrings(result);
    ASSERT_EQ(strings.size(), 2u);
    EXPECT_EQ(strings[0], "ab");
    EXPECT_EQ(strings[1], "c");
}

TEST_F(SplitStringRefTest_595, StdStringInput_595) {
    std::string input = "foo,bar,baz";
    auto result = Catch::splitStringRef(Catch::StringRef(input), ',');
    auto strings = toStrings(result);
    ASSERT_EQ(strings.size(), 3u);
    EXPECT_EQ(strings[0], "foo");
    EXPECT_EQ(strings[1], "bar");
    EXPECT_EQ(strings[2], "baz");
}

TEST_F(SplitStringRefTest_595, MultipleConsecutiveDelimitersAtStart_595) {
    auto result = Catch::splitStringRef(Catch::StringRef(",,,hello"), ',');
    auto strings = toStrings(result);
    ASSERT_EQ(strings.size(), 1u);
    EXPECT_EQ(strings[0], "hello");
}

TEST_F(SplitStringRefTest_595, MultipleConsecutiveDelimitersAtEnd_595) {
    auto result = Catch::splitStringRef(Catch::StringRef("hello,,,"), ',');
    auto strings = toStrings(result);
    ASSERT_EQ(strings.size(), 1u);
    EXPECT_EQ(strings[0], "hello");
}

TEST_F(SplitStringRefTest_595, LongString_595) {
    std::string input = "abcdefghij,klmnopqrst,uvwxyz";
    auto result = Catch::splitStringRef(Catch::StringRef(input), ',');
    auto strings = toStrings(result);
    ASSERT_EQ(strings.size(), 3u);
    EXPECT_EQ(strings[0], "abcdefghij");
    EXPECT_EQ(strings[1], "klmnopqrst");
    EXPECT_EQ(strings[2], "uvwxyz");
}

TEST_F(SplitStringRefTest_595, DefaultStringRef_595) {
    Catch::StringRef emptyRef;
    auto result = Catch::splitStringRef(emptyRef, ',');
    EXPECT_TRUE(result.empty());
}

TEST_F(SplitStringRefTest_595, TwoCharStringNoDelimiter_595) {
    auto result = Catch::splitStringRef(Catch::StringRef("ab"), ',');
    auto strings = toStrings(result);
    ASSERT_EQ(strings.size(), 1u);
    EXPECT_EQ(strings[0], "ab");
}

TEST_F(SplitStringRefTest_595, ExactlyOneCharBetweenTwoDelimiters_595) {
    // ",x," => 'x' between delimiters has length 1 which is NOT > 1, so dropped
    auto result = Catch::splitStringRef(Catch::StringRef(",x,"), ',');
    EXPECT_TRUE(result.empty());
}

TEST_F(SplitStringRefTest_595, ExactlyTwoCharsBetweenTwoDelimiters_595) {
    // ",xy," => 'xy' between delimiters has length 2 which IS > 1, so kept
    auto result = Catch::splitStringRef(Catch::StringRef(",xy,"), ',');
    auto strings = toStrings(result);
    ASSERT_EQ(strings.size(), 1u);
    EXPECT_EQ(strings[0], "xy");
}
