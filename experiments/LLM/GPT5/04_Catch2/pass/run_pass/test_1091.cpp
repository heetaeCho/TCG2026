// File: tests/AnsiSkippingStringTests_1091.cpp

#include <gtest/gtest.h>
#include <string>

// Include the public header that declares AnsiSkippingString
#include "Catch2/src/catch2/internal/catch_textflow.hpp"

using Catch::TextFlow::AnsiSkippingString;

class AnsiSkippingStringTest_1091 : public ::testing::Test {};

// --- Construction ---

TEST_F(AnsiSkippingStringTest_1091, ConstructsFromLvalue_BasicConsistency_1091) {
    const std::string input = "hello";
    AnsiSkippingString s(input);

    // Observable contract: full-range substring length equals size()
    const auto beg = s.begin();
    const auto end = s.end();
    const std::string whole = s.substring(beg, end);

    EXPECT_EQ(whole.size(), s.size());
}

TEST_F(AnsiSkippingStringTest_1091, ConstructsFromRvalue_BasicConsistency_1091) {
    std::string input = "world";
    AnsiSkippingString s(std::move(input));

    const auto beg = s.begin();
    const auto end = s.end();
    const std::string whole = s.substring(beg, end);

    EXPECT_EQ(whole.size(), s.size());
    // We do not assert anything about 'input' after move (standard allows unspecified content).
}

// --- Boundary conditions ---

TEST_F(AnsiSkippingStringTest_1091, EmptyString_HasZeroSizeAndEmptySubstring_1091) {
    const std::string empty;
    AnsiSkippingString s(empty);

    EXPECT_EQ(s.size(), 0u);

    const auto beg = s.begin();
    const auto end = s.end();
    const std::string whole = s.substring(beg, end);
    EXPECT_TRUE(whole.empty());

    // Zero-length subrange [begin, begin] should also be empty
    const std::string zero_len = s.substring(beg, beg);
    EXPECT_TRUE(zero_len.empty());
}

TEST_F(AnsiSkippingStringTest_1091, ZeroLengthSubrangeAtEnd_IsEmpty_1091) {
    const std::string input = "x";
    AnsiSkippingString s(input);

    const auto e = s.end();
    const std::string zero_len = s.substring(e, e);
    EXPECT_TRUE(zero_len.empty());
}

// --- General observable properties ---

TEST_F(AnsiSkippingStringTest_1091, FullSubstringLengthEqualsSize_ForVariousInputs_1091) {
    // A mix of simple cases (we do not assume any ANSI handling behavior).
    const std::string samples[] = {
        "abc",
        "   leading and trailing spaces   ",
        "line1\nline2\nline3",
        "\t tabs \t inside",
        "\x1b[31mred\x1b[0mtext",  // Contains ANSI-looking bytes; we only check API invariants.
    };

    for (const auto& text : samples) {
        AnsiSkippingString s(text);
        const auto beg = s.begin();
        const auto end = s.end();
        const std::string whole = s.substring(beg, end);

        EXPECT_EQ(whole.size(), s.size()) << "Input: " << text;
    }
}

TEST_F(AnsiSkippingStringTest_1091, MultipleBeginEndCalls_AreConsistent_1091) {
    const std::string input = "consistency";
    AnsiSkippingString s(input);

    const auto b1 = s.begin();
    const auto e1 = s.end();
    const auto b2 = s.begin();
    const auto e2 = s.end();

    const std::string w1 = s.substring(b1, e1);
    const std::string w2 = s.substring(b2, e2);

    EXPECT_EQ(w1.size(), s.size());
    EXPECT_EQ(w2.size(), s.size());
    EXPECT_EQ(w1, w2);
}

// --- Interaction with original source string (observable from API only) ---

TEST_F(AnsiSkippingStringTest_1091, ModifyingOriginalAfterLvalueConstruction_DoesNotAffectInstance_1091) {
    std::string original = "stable";
    AnsiSkippingString s(original);

    // Record observable properties
    const auto beg = s.begin();
    const auto end = s.end();
    const std::string whole_before = s.substring(beg, end);
    const auto size_before = s.size();

    // Mutate the original source string (the class should be independent after construction)
    original.clear();
    original.append("changed");

    const std::string whole_after = s.substring(s.begin(), s.end());
    const auto size_after = s.size();

    EXPECT_EQ(whole_before, whole_after);
    EXPECT_EQ(size_before, size_after);
}

// --- Robustness with mixed content ---

TEST_F(AnsiSkippingStringTest_1091, MixedEscapesAndText_APIInvariantsHold_1091) {
    // Mix bytes that look like ANSI escapes with regular text. We do not assert any
    // particular interpretation — only that public APIs are self-consistent.
    const std::string input = "start\x1b[1mBOLD\x1b[0m_mid\x1b[38;5;123mCOLOR\x1b[0m_end";
    AnsiSkippingString s(input);

    const std::string whole = s.substring(s.begin(), s.end());
    EXPECT_EQ(whole.size(), s.size());
    // Also check zero-length subrange in the middle (begin, begin)
    const auto beg = s.begin();
    const std::string empty_mid = s.substring(beg, beg);
    EXPECT_TRUE(empty_mid.empty());
}
