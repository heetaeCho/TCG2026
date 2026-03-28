// File: tests/stringmaker_wstring_convert_264_test.cpp

#include <gtest/gtest.h>
#include <string>

// Headers under test
// Adjust include paths as needed for your project layout
#include "catch2/catch_tostring.hpp"

namespace {

using Catch::StringMaker;

// Test fixture kept minimal for clarity/consistency
class StringMakerWStringTest_264 : public ::testing::Test {};

TEST_F(StringMakerWStringTest_264, AsciiPassthrough_264) {
    // Normal operation: pure ASCII should pass through unchanged,
    // and then be processed by Catch::Detail::stringify for std::string.
    const std::wstring input = L"Hello, world!";
    const std::string expected_ascii = "Hello, world!";

    const std::string actual =
        StringMaker<std::wstring>::convert(input);

    EXPECT_EQ(actual, ::Catch::Detail::stringify(expected_ascii));
}

TEST_F(StringMakerWStringTest_264, EmptyString_264) {
    // Boundary: empty input should yield stringify of empty std::string.
    const std::wstring input;
    const std::string expected_ascii;

    const std::string actual =
        StringMaker<std::wstring>::convert(input);

    EXPECT_EQ(actual, ::Catch::Detail::stringify(expected_ascii));
}

TEST_F(StringMakerWStringTest_264, NonAsciiReplacedWithQuestionMark_264) {
    // Observable rule: code points > 0xff become '?' before stringify.
    // Example characters: U+00E9 (é) == 233 (<= 0xff) -> cast to char
    // U+0100 (Ā) == 256 (> 0xff) -> '?'
    // U+03A9 (Ω) == 937 (> 0xff) -> '?'
    const std::wstring input = { L'A', 0x00E9, 0x0100, 0x03A9, L'Z' };
    // After mapping: 'A', char(0xE9), '?', '?', 'Z'
    std::string expected_ascii;
    expected_ascii += 'A';
    expected_ascii += static_cast<char>(0xE9); // implementation casts when <= 0xff
    expected_ascii += '?';
    expected_ascii += '?';
    expected_ascii += 'Z';

    const std::string actual =
        StringMaker<std::wstring>::convert(input);

    EXPECT_EQ(actual, ::Catch::Detail::stringify(expected_ascii));
}

TEST_F(StringMakerWStringTest_264, BoundaryValuesFFAnd100_264) {
    // Boundary: exactly 0xff passes through; 0x100 becomes '?'.
    const std::wstring input = { 0x00FF, 0x0100 };
    std::string expected_ascii;
    expected_ascii += static_cast<char>(0xFF); // allowed
    expected_ascii += '?';                     // > 0xff -> '?'

    const std::string actual =
        StringMaker<std::wstring>::convert(input);

    EXPECT_EQ(actual, ::Catch::Detail::stringify(expected_ascii));
}

TEST_F(StringMakerWStringTest_264, MixedAsciiAndEmoji_264) {
    // Mixed content: ASCII, then emoji (>0xff) which should become '?',
    // then more ASCII.
    // Emoji example: U+1F600 (GRINNING FACE) > 0xff -> '?'
    const std::wstring input = L"OK " + std::wstring{ 0x1F600 } + L" done";
    std::string expected_ascii = "OK ? done";

    const std::string actual =
        StringMaker<std::wstring>::convert(input);

    EXPECT_EQ(actual, ::Catch::Detail::stringify(expected_ascii));
}

} // namespace
