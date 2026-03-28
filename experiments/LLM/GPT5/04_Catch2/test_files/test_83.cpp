// File: convert_unsigned_char_ptr_tests_83.cpp

#include <gtest/gtest.h>
#include <string>
#include <array>

// Include the header under test (path based on the prompt)
#include "Catch2/src/catch2/catch_tostring.hpp"

namespace {

using ::Catch::StringMaker;

// Helper to reinterpret unsigned-char buffers as char*, for comparison target.
inline const char* AsChar(const unsigned char* p) {
    return reinterpret_cast<const char*>(p);
}

} // namespace

// Normal operation: basic ASCII content
TEST(ConvertUnsignedCharPtrTest_83, MatchesCharConstBehavior_Normal_83) {
    const std::string s = "hello, world";
    const unsigned char* uptr = reinterpret_cast<const unsigned char*>(s.c_str());

    const std::string as_unsigned = ::Catch::convert(uptr);
    const std::string as_char     = StringMaker<char const*>::convert(AsChar(uptr));

    EXPECT_EQ(as_unsigned, as_char);
}

// Boundary: empty string
TEST(ConvertUnsignedCharPtrTest_83, MatchesCharConstBehavior_EmptyString_83) {
    const std::string s = "";
    const unsigned char* uptr = reinterpret_cast<const unsigned char*>(s.c_str());

    const std::string as_unsigned = ::Catch::convert(uptr);
    const std::string as_char     = StringMaker<char const*>::convert(AsChar(uptr));

    EXPECT_EQ(as_unsigned, as_char);
}

// Exceptional/edge: nullptr input — observable via returned string, compared to char* handling
TEST(ConvertUnsignedCharPtrTest_83, MatchesCharConstBehavior_Nullptr_83) {
    const unsigned char* uptr = nullptr;
    const char* cptr = nullptr;

    const std::string as_unsigned = ::Catch::convert(uptr);
    const std::string as_char     = StringMaker<char const*>::convert(cptr);

    EXPECT_EQ(as_unsigned, as_char);
}

// Boundary: embedded NUL should terminate the viewed range (no read past NUL)
TEST(ConvertUnsignedCharPtrTest_83, StopsAtFirstNull_AndMatchesCharConst_83) {
    // "abc\0def" — convert should only consider "abc"
    const std::array<unsigned char, 8> buf{{'a','b','c','\0','d','e','f','\0'}};

    const std::string as_unsigned = ::Catch::convert(buf.data());
    const std::string as_char     = StringMaker<char const*>::convert(AsChar(buf.data()));

    // Consistency with char-typed conversion
    EXPECT_EQ(as_unsigned, as_char);

    // And it must not contain the tail after the first NUL ("def")
    EXPECT_EQ(as_unsigned.find("def"), std::string::npos);
}

// Non-ASCII bytes (e.g., UTF-8 sequence) should behave consistently with char*
TEST(ConvertUnsignedCharPtrTest_83, NonAsciiBytes_MatchesCharConstBehavior_83) {
    // UTF-8 for "é" = 0xC3 0xA9
    const std::array<unsigned char, 3> u8_e_acute{{0xC3u, 0xA9u, 0x00u}};

    const std::string as_unsigned = ::Catch::convert(u8_e_acute.data());
    const std::string as_char     = StringMaker<char const*>::convert(AsChar(u8_e_acute.data()));

    EXPECT_EQ(as_unsigned, as_char);
}
