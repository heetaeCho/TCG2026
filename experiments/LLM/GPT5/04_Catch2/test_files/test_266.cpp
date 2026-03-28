// File: test_stringmaker_wchar_const_ptr_266.cpp

#include <gtest/gtest.h>
#include <string>
#include "catch2/catch_tostring.hpp"  // Path as given in the prompt

// Shorthand to reduce verbosity
using Catch::StringMaker;

// The tests verify only observable behavior via the public interface:
// - For non-null pointers, the result must match the conversion of an
//   equivalent std::wstring using StringMaker<std::wstring>::convert.
// - For null pointers, the function must return "{null string}".

TEST(StringMakerWCharConstPtr_266, ReturnsNullStringForNullPtr_266) {
    const wchar_t* p = nullptr;

    const std::string actual = StringMaker<const wchar_t*>::convert(p);

    EXPECT_EQ(actual, "{null string}");
}

TEST(StringMakerWCharConstPtr_266, MatchesWStringConversionForSimpleText_266) {
    const wchar_t* p = L"Hello Catch2";

    const std::string from_ptr = StringMaker<const wchar_t*>::convert(p);
    const std::string from_wstr = StringMaker<std::wstring>::convert(std::wstring{p});

    EXPECT_EQ(from_ptr, from_wstr);
}

TEST(StringMakerWCharConstPtr_266, HandlesEmptyWideString_266) {
    const wchar_t* p = L"";

    const std::string from_ptr = StringMaker<const wchar_t*>::convert(p);
    const std::string from_wstr = StringMaker<std::wstring>::convert(std::wstring{p});

    EXPECT_EQ(from_ptr, from_wstr);
}

TEST(StringMakerWCharConstPtr_266, HandlesUnicodeCharacters_266) {
    // Include a mix of non-ASCII characters to ensure consistent observable output
    // (comparison is against the public std::wstring overload).
    const wchar_t* p = L"안녕하세요 😊 Καλημέρα";

    const std::string from_ptr = StringMaker<const wchar_t*>::convert(p);
    const std::string from_wstr = StringMaker<std::wstring>::convert(std::wstring{p});

    EXPECT_EQ(from_ptr, from_wstr);
}

TEST(StringMakerWCharConstPtr_266, WorksWithTemporaryWStringBuffer_266) {
    // Validate behavior when the pointer originates from a temporary wstring's buffer.
    // We only compare immediate observable results; no assumptions about lifetime beyond this call.
    std::wstring tmp = L"Temporary wide string";
    const wchar_t* p = tmp.c_str();

    const std::string from_ptr = StringMaker<const wchar_t*>::convert(p);
    const std::string from_wstr = StringMaker<std::wstring>::convert(tmp);

    EXPECT_EQ(from_ptr, from_wstr);
}
