// File: stringmaker_wstring_view_convert_test_265.cpp
#include <gtest/gtest.h>
#include <string>
#include <string_view>

// Adjust the include path to match your project layout
#include "catch2/catch_tostring.hpp"

namespace {

using Catch::StringMaker;

// A tiny helper to call both overloads and compare results.
// We don't assert anything about the string content itself;
// we only verify that the wstring_view overload produces the same
// observable result as the std::wstring overload.
static void ExpectEquivalentThroughWString(const std::wstring_view view) {
    const std::string via_view = StringMaker<std::wstring_view>::convert(view);
    const std::wstring wcopy(view); // Matches the production code's construction
    const std::string via_wstring = StringMaker<std::wstring>::convert(wcopy);
    EXPECT_EQ(via_view, via_wstring);
}

} // namespace

// Normal operation with simple ASCII-wide text
TEST(StringMakerWStringViewTest_265, CompareEquivalence_NonEmptyAscii_265) {
    std::wstring_view v(L"Hello Wide");
    ExpectEquivalentThroughWString(v);
}

// Normal operation with Unicode characters (e.g., Korean)
TEST(StringMakerWStringViewTest_265, CompareEquivalence_Unicode_265) {
    std::wstring_view v(L"안녕하세요 🌊");
    ExpectEquivalentThroughWString(v);
}

// Boundary condition: empty view
TEST(StringMakerWStringViewTest_265, CompareEquivalence_Empty_265) {
    std::wstring_view v; // empty
    ExpectEquivalentThroughWString(v);
}

// Boundary condition: view that contains an embedded NUL character
TEST(StringMakerWStringViewTest_265, CompareEquivalence_EmbeddedNull_265) {
    // Create a wide string with an embedded NUL between 'A' and 'B'
    const wchar_t raw_with_null[] = { L'A', L'\0', L'B', L'\0' }; // trailing terminator
    // Make a std::wstring of length 3: 'A' '\0' 'B'
    const std::wstring with_null(raw_with_null, raw_with_null + 3);
    const std::wstring_view v(with_null.data(), with_null.size());
    ExpectEquivalentThroughWString(v);
}

// Boundary/normal: substring view (non-owning, not starting at begin())
TEST(StringMakerWStringViewTest_265, CompareEquivalence_SubstringView_265) {
    const std::wstring backing = L"Prefix-내용-Postfix";
    // Create a view to the middle portion "내용"
    const std::size_t start = 7;                 // after "Prefix-"
    const std::size_t len   = 2;                 // "내용" is 2 wide characters
    const std::wstring_view v(backing.data() + start, len);
    ExpectEquivalentThroughWString(v);
}
