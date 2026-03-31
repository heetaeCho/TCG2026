#include <gtest/gtest.h>
#include <string>
#include "catch2/internal/catch_textflow.hpp"

using namespace Catch::TextFlow;

// =====================================================
// AnsiSkippingString construction and basic properties
// =====================================================

TEST(AnsiSkippingStringTest_613, DefaultConstruction_FromLValueString_613) {
    std::string text = "Hello, World!";
    AnsiSkippingString ass(text);
    EXPECT_EQ(ass.size(), 13u);
}

TEST(AnsiSkippingStringTest_613, DefaultConstruction_FromRValueString_613) {
    AnsiSkippingString ass(std::string("Hello"));
    EXPECT_EQ(ass.size(), 5u);
}

TEST(AnsiSkippingStringTest_613, EmptyString_613) {
    AnsiSkippingString ass(std::string(""));
    EXPECT_EQ(ass.size(), 0u);
}

TEST(AnsiSkippingStringTest_613, BeginEqualsEndForEmptyString_613) {
    AnsiSkippingString ass(std::string(""));
    EXPECT_TRUE(ass.begin() == ass.end());
}

TEST(AnsiSkippingStringTest_613, BeginNotEqualsEndForNonEmptyString_613) {
    AnsiSkippingString ass(std::string("abc"));
    EXPECT_TRUE(ass.begin() != ass.end());
}

// =====================================================
// Iterator basic operations
// =====================================================

TEST(AnsiSkippingStringIteratorTest_613, DereferenceBegin_613) {
    AnsiSkippingString ass(std::string("Hello"));
    auto it = ass.begin();
    EXPECT_EQ(*it, 'H');
}

TEST(AnsiSkippingStringIteratorTest_613, IncrementIterator_613) {
    AnsiSkippingString ass(std::string("Hi"));
    auto it = ass.begin();
    EXPECT_EQ(*it, 'H');
    ++it;
    EXPECT_EQ(*it, 'i');
}

TEST(AnsiSkippingStringIteratorTest_613, PostIncrementIterator_613) {
    AnsiSkippingString ass(std::string("AB"));
    auto it = ass.begin();
    auto prev = it++;
    EXPECT_EQ(*prev, 'A');
    EXPECT_EQ(*it, 'B');
}

TEST(AnsiSkippingStringIteratorTest_613, DecrementIterator_613) {
    AnsiSkippingString ass(std::string("AB"));
    auto it = ass.begin();
    ++it;
    EXPECT_EQ(*it, 'B');
    --it;
    EXPECT_EQ(*it, 'A');
}

TEST(AnsiSkippingStringIteratorTest_613, PostDecrementIterator_613) {
    AnsiSkippingString ass(std::string("XY"));
    auto it = ass.begin();
    ++it;
    auto prev = it--;
    EXPECT_EQ(*prev, 'Y');
    EXPECT_EQ(*it, 'X');
}

TEST(AnsiSkippingStringIteratorTest_613, IterateToEnd_613) {
    AnsiSkippingString ass(std::string("abc"));
    auto it = ass.begin();
    ++it; // b
    ++it; // c
    ++it; // end
    EXPECT_TRUE(it == ass.end());
}

TEST(AnsiSkippingStringIteratorTest_613, EqualityOperator_613) {
    AnsiSkippingString ass(std::string("abc"));
    auto it1 = ass.begin();
    auto it2 = ass.begin();
    EXPECT_TRUE(it1 == it2);
}

TEST(AnsiSkippingStringIteratorTest_613, InequalityOperator_613) {
    AnsiSkippingString ass(std::string("abc"));
    auto it1 = ass.begin();
    auto it2 = ass.begin();
    ++it2;
    EXPECT_TRUE(it1 != it2);
}

TEST(AnsiSkippingStringIteratorTest_613, LessOrEqualOperator_613) {
    AnsiSkippingString ass(std::string("abc"));
    auto it1 = ass.begin();
    auto it2 = ass.begin();
    EXPECT_TRUE(it1 <= it2);
    ++it2;
    EXPECT_TRUE(it1 <= it2);
}

TEST(AnsiSkippingStringIteratorTest_613, OneBeforeIterator_613) {
    AnsiSkippingString ass(std::string("AB"));
    auto it = ass.begin();
    ++it;
    auto before = it.oneBefore();
    EXPECT_EQ(*before, 'A');
}

// =====================================================
// Substring extraction
// =====================================================

TEST(AnsiSkippingStringTest_613, SubstringFullString_613) {
    AnsiSkippingString ass(std::string("Hello"));
    std::string sub = ass.substring(ass.begin(), ass.end());
    EXPECT_EQ(sub, "Hello");
}

TEST(AnsiSkippingStringTest_613, SubstringPartialString_613) {
    AnsiSkippingString ass(std::string("Hello"));
    auto begin = ass.begin();
    auto end = ass.begin();
    ++end; // e
    ++end; // l
    ++end; // past 'l'
    std::string sub = ass.substring(begin, end);
    EXPECT_EQ(sub, "Hel");
}

TEST(AnsiSkippingStringTest_613, SubstringEmptyRange_613) {
    AnsiSkippingString ass(std::string("Hello"));
    std::string sub = ass.substring(ass.begin(), ass.begin());
    EXPECT_EQ(sub, "");
}

// =====================================================
// ANSI escape sequence handling
// =====================================================

TEST(AnsiSkippingStringTest_613, AnsiEscapeSequenceSkipped_613) {
    // ANSI escape: ESC[31m (red color)
    std::string text = "\033[31mHello\033[0m";
    AnsiSkippingString ass(text);
    // The visible size should only count non-ANSI characters
    EXPECT_EQ(ass.size(), 5u);
}

TEST(AnsiSkippingStringTest_613, AnsiEscapeIteratorSkipsSequences_613) {
    std::string text = "\033[31mAB\033[0m";
    AnsiSkippingString ass(text);
    auto it = ass.begin();
    EXPECT_EQ(*it, 'A');
    ++it;
    EXPECT_EQ(*it, 'B');
    ++it;
    EXPECT_TRUE(it == ass.end());
}

TEST(AnsiSkippingStringTest_613, AnsiEscapeSubstring_613) {
    std::string text = "\033[31mHello\033[0m";
    AnsiSkippingString ass(text);
    std::string sub = ass.substring(ass.begin(), ass.end());
    // substring should include the ANSI sequences in the raw string
    EXPECT_EQ(sub, text);
}

TEST(AnsiSkippingStringTest_613, MultipleAnsiSequences_613) {
    std::string text = "\033[1m\033[31mBold Red\033[0m";
    AnsiSkippingString ass(text);
    EXPECT_EQ(ass.size(), 8u); // "Bold Red" = 8 chars
}

// =====================================================
// Whitespace and boundary-related behaviors
// =====================================================

TEST(AnsiSkippingStringTest_613, StringWithSpaces_613) {
    AnsiSkippingString ass(std::string("Hello World"));
    EXPECT_EQ(ass.size(), 11u);
}

TEST(AnsiSkippingStringTest_613, StringWithOnlyWhitespace_613) {
    AnsiSkippingString ass(std::string("   "));
    EXPECT_EQ(ass.size(), 3u);
}

TEST(AnsiSkippingStringTest_613, SingleCharacterString_613) {
    AnsiSkippingString ass(std::string("A"));
    auto it = ass.begin();
    EXPECT_EQ(*it, 'A');
    ++it;
    EXPECT_TRUE(it == ass.end());
}

// =====================================================
// Special characters that might affect boundary detection
// =====================================================

TEST(AnsiSkippingStringTest_613, StringWithHyphens_613) {
    AnsiSkippingString ass(std::string("well-known"));
    EXPECT_EQ(ass.size(), 10u);
    auto it = ass.begin();
    for (int i = 0; i < 10; ++i) {
        EXPECT_TRUE(it != ass.end());
        ++it;
    }
    EXPECT_TRUE(it == ass.end());
}

TEST(AnsiSkippingStringTest_613, StringWithTabs_613) {
    AnsiSkippingString ass(std::string("a\tb"));
    EXPECT_EQ(ass.size(), 3u);
}

TEST(AnsiSkippingStringTest_613, StringWithNewlines_613) {
    AnsiSkippingString ass(std::string("a\nb"));
    EXPECT_EQ(ass.size(), 3u);
}

// =====================================================
// Iteration full traversal
// =====================================================

TEST(AnsiSkippingStringTest_613, FullTraversalMatchesSize_613) {
    std::string text = "The quick brown fox";
    AnsiSkippingString ass(text);
    size_t count = 0;
    for (auto it = ass.begin(); it != ass.end(); ++it) {
        ++count;
    }
    EXPECT_EQ(count, ass.size());
}

TEST(AnsiSkippingStringTest_613, FullTraversalWithAnsiMatchesSize_613) {
    std::string text = "\033[32mGreen\033[0m text";
    AnsiSkippingString ass(text);
    size_t count = 0;
    for (auto it = ass.begin(); it != ass.end(); ++it) {
        ++count;
    }
    EXPECT_EQ(count, ass.size());
}

// =====================================================
// Edge cases
// =====================================================

TEST(AnsiSkippingStringTest_613, OnlyAnsiSequence_613) {
    std::string text = "\033[31m\033[0m";
    AnsiSkippingString ass(text);
    EXPECT_EQ(ass.size(), 0u);
    EXPECT_TRUE(ass.begin() == ass.end());
}

TEST(AnsiSkippingStringTest_613, IncompleteAnsiSequence_613) {
    // ESC without proper termination - behavior may vary
    std::string text = "\033[Hello";
    AnsiSkippingString ass(text);
    // Just verify it doesn't crash and has some size
    EXPECT_GT(ass.size(), 0u);
}

TEST(AnsiSkippingStringTest_613, LongString_613) {
    std::string text(1000, 'x');
    AnsiSkippingString ass(text);
    EXPECT_EQ(ass.size(), 1000u);
}

TEST(AnsiSkippingStringTest_613, MixedContentSubstring_613) {
    std::string text = "abc def";
    AnsiSkippingString ass(text);
    auto begin = ass.begin();
    ++begin; // 'b'
    ++begin; // 'c'
    ++begin; // ' '
    auto end = begin;
    ++end;   // 'd'
    ++end;   // 'e'
    ++end;   // 'f'
    std::string sub = ass.substring(begin, end);
    EXPECT_EQ(sub, " de");
}
