// File: tests/ansi_skipping_string_tests_1092.cpp

#include <gtest/gtest.h>
#include <string>
#include <iterator>

// Include the public interface under test
#include "catch2/internal/catch_textflow.hpp"

using Catch::TextFlow::AnsiSkippingString;

namespace {

// Small helper that advances a const_iterator by n steps using only ++
template <typename It>
It advance_visible(It it, std::size_t n) {
    for (std::size_t i = 0; i < n; ++i) { ++it; }
    return it;
}

} // namespace

// --- Boundary: empty input ---
TEST(AnsiSkippingStringTest_1092, EmptyString_BeginEndAndSize_1092) {
    const std::string input;
    const AnsiSkippingString s(input);

    auto b = s.begin();
    auto e = s.end();

    EXPECT_EQ(s.size(), 0u);                         // observable size
    EXPECT_TRUE(b == e);                             // no visible chars
    EXPECT_EQ(s.substring(b, e), std::string{});     // empty substring
}

// --- Normal: plain text (no ANSI) ---
TEST(AnsiSkippingStringTest_1092, PlainText_SizeAndWholeSubstring_1092) {
    const std::string input = "Hello";
    const AnsiSkippingString s(input);

    auto b = s.begin();
    auto e = s.end();

    EXPECT_EQ(s.size(), 5u);                         // matches visible count
    EXPECT_EQ(s.substring(b, e), std::string("Hello"));
}

// --- Normal: partial substring via iterators ---
TEST(AnsiSkippingStringTest_1092, PlainText_PartialSubstring_1092) {
    const std::string input = "Hello";
    const AnsiSkippingString s(input);

    auto b = s.begin();
    auto mid = advance_visible(b, 2);                // use only ++ to advance
    EXPECT_EQ(s.substring(b, mid), std::string("He"));

    auto e = s.end();
    auto last3 = advance_visible(b, 2);
    EXPECT_EQ(s.substring(last3, e), std::string("llo"));
}

// --- Move construction with rvalue input ---
TEST(AnsiSkippingStringTest_1092, MoveCtor_PreservesObservableContent_1092) {
    std::string src = "World";
    AnsiSkippingString s(std::move(src));            // do not assert anything about src after move

    auto b = s.begin();
    auto e = s.end();

    EXPECT_EQ(s.size(), 5u);
    EXPECT_EQ(s.substring(b, e), std::string("World"));
}

// --- ANSI escapes: visible content & size should reflect printed text only ---
TEST(AnsiSkippingStringTest_1092, AnsiEscapes_AreNotCountedAsVisible_1092) {
    // "\x1b[31m" = set red, "\x1b[0m" = reset
    const std::string input = "\x1b[31mRed\x1b[0m";
    const AnsiSkippingString s(input);

    auto b = s.begin();
    auto e = s.end();

    // Observable behavior: visible characters are "Red"
    EXPECT_EQ(s.size(), 3u);
    EXPECT_EQ(s.substring(b, e), std::string("Red"));
}

// --- Mixed content: text + escapes + more text ---
TEST(AnsiSkippingStringTest_1092, AnsiEscapes_MixedSegments_1092) {
    // Visible sequence should be "A" + "BC" + "D" = "ABCD"
    const std::string input =
        "A\x1b[1mBC\x1b[0mD";
    const AnsiSkippingString s(input);

    auto b = s.begin();
    auto e = s.end();

    EXPECT_EQ(s.size(), 4u);
    EXPECT_EQ(s.substring(b, e), std::string("ABCD"));

    // Partial: first 3 visible characters
    auto first3 = advance_visible(b, 3);
    EXPECT_EQ(s.substring(b, first3), std::string("ABC"));
}
