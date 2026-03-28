// TagInfo_all_tests_603.cpp
#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <algorithm>

// Headers from the provided partial code
#include "Catch2/src/catch2/internal/catch_list.hpp"
#include "Catch2/src/catch2/internal/catch_stringref.hpp"

using namespace Catch;

// Helper: extract bracketed tokens like "[alpha]" -> "alpha"
static std::vector<std::string> ExtractBracketedTokens(const std::string& s) {
    std::vector<std::string> out;
    std::size_t i = 0;
    while (i < s.size()) {
        auto l = s.find('[', i);
        if (l == std::string::npos) break;
        auto r = s.find(']', l + 1);
        if (r == std::string::npos) break;
        out.emplace_back(s.substr(l + 1, r - (l + 1)));
        i = r + 1;
    }
    return out;
}

TEST(TagInfoAllTest_603, EmptyReturnsEmpty_603) {
    TagInfo tags;
    // No additions
    const std::string out = tags.all();
    EXPECT_TRUE(out.empty());
}

TEST(TagInfoAllTest_603, SingleSpellingWrappedInBrackets_603) {
    TagInfo tags;
    tags.add(StringRef("alpha"));
    const std::string out = tags.all();

    EXPECT_EQ(out, "[alpha]");
    auto tokens = ExtractBracketedTokens(out);
    ASSERT_EQ(tokens.size(), 1u);
    EXPECT_EQ(tokens[0], "alpha");
}

TEST(TagInfoAllTest_603, MultipleSpellingsConcatenatedAndBracketed_603) {
    TagInfo tags;
    tags.add(StringRef("a"));
    tags.add(StringRef("bb"));

    const std::string out = tags.all();

    // Order is not specified; verify content and size in an order-agnostic way
    auto tokens = ExtractBracketedTokens(out);
    ASSERT_EQ(tokens.size(), 2u);
    // Check that the two expected tokens are present (in any order)
    std::sort(tokens.begin(), tokens.end());
    std::vector<std::string> expected = {"a", "bb"};
    std::sort(expected.begin(), expected.end());
    EXPECT_EQ(tokens, expected);

    // Length must equal sum(len(token)) + 2 * count (two brackets per token)
    const std::size_t expectedLen = std::string("a").size() + std::string("bb").size() + 2 * 2;
    EXPECT_EQ(out.size(), expectedLen);
}

TEST(TagInfoAllTest_603, DuplicateSpellingsAppearOnce_603) {
    TagInfo tags;

    std::string dup = "dup";
    tags.add(StringRef(dup));       // from std::string
    tags.add(StringRef("dup"));     // same value again (duplicate)
    tags.add(StringRef("x"));

    const std::string out = tags.all();
    auto tokens = ExtractBracketedTokens(out);

    // Expect only two unique tokens present
    std::sort(tokens.begin(), tokens.end());
    ASSERT_EQ(tokens.size(), 2u);
    EXPECT_TRUE(std::binary_search(tokens.begin(), tokens.end(), "dup"));
    EXPECT_TRUE(std::binary_search(tokens.begin(), tokens.end(), "x"));

    // Ensure the bracketed "[dup]" occurs exactly once in the output string
    EXPECT_NE(out.find("[dup]"), std::string::npos);
    auto second = out.find("[dup]", out.find("[dup]") + 1);
    EXPECT_EQ(second, std::string::npos);
}

TEST(TagInfoAllTest_603, SupportsDifferentStringRefConstructors_603) {
    TagInfo tags;

    // raw pointer + explicit size
    const char* raw = "abcXYZ";
    tags.add(StringRef(raw, 3)); // "abc"

    // raw null-terminated
    tags.add(StringRef("pq"));

    // std::string
    std::string s = "longer";
    tags.add(StringRef(s));

    const std::string out = tags.all();
    auto tokens = ExtractBracketedTokens(out);
    std::sort(tokens.begin(), tokens.end());

    std::vector<std::string> expected = {"abc", "pq", "longer"};
    std::sort(expected.begin(), expected.end());

    EXPECT_EQ(tokens, expected);

    // Size check: sum of token sizes + 2 brackets per token
    std::size_t sumLen = 3 + 2 + 6;
    EXPECT_EQ(out.size(), sumLen + 2 * expected.size());
}

TEST(TagInfoAllTest_603, HandlesSpecialCharacters_603) {
    TagInfo tags;
    tags.add(StringRef("a b"));
    tags.add(StringRef("x-y_!"));

    const std::string out = tags.all();
    auto tokens = ExtractBracketedTokens(out);
    std::sort(tokens.begin(), tokens.end());

    std::vector<std::string> expected = {"a b", "x-y_!"};
    std::sort(expected.begin(), expected.end());
    EXPECT_EQ(tokens, expected);

    // Ensure exact bracket-wrapped substrings appear
    EXPECT_NE(out.find("[a b]"), std::string::npos);
    EXPECT_NE(out.find("[x-y_!]"), std::string::npos);

    // Length check independent of order
    const std::size_t expectedLen =
        std::string("a b").size() + std::string("x-y_!").size() + 2 * 2;
    EXPECT_EQ(out.size(), expectedLen);
}
