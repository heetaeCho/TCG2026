// File: test_stringmaker_wchar_ptr_267.cpp

#include <gtest/gtest.h>
#include <string>
#include <cwchar>

// Headers under test
#include "catch2/catch_tostring.hpp"

namespace {

using Catch::StringMaker;

// ---------- Normal operation ----------

TEST(StringMakerWCharPtr_267, ConvertsNonNullAscii_267) {
    wchar_t buffer[] = L"Hello World";
    std::string result = StringMaker<wchar_t *>::convert(buffer);

    // Observable expectations from the interface:
    //  - Non-null input does NOT return the null sentinel.
    //  - The textual content should be present in the resulting std::string.
    EXPECT_NE(result, "{null string}");
    EXPECT_NE(result.find("Hello World"), std::string::npos);
}

TEST(StringMakerWCharPtr_267, ConsistencyWithConstOverload_267) {
    // The interface exposes both wchar_t* and wchar_t const* overloads.
    // For the same logical input, their observable outputs should match.
    const wchar_t* cptr = L"Sample";
    wchar_t mutable_buf[] = L"Sample";

    std::string from_mutable = StringMaker<wchar_t *>::convert(mutable_buf);
    std::string from_const   = StringMaker<wchar_t const *>::convert(cptr);

    EXPECT_EQ(from_mutable, from_const);
}

// ---------- Boundary conditions ----------

TEST(StringMakerWCharPtr_267, ReturnsSentinelForNullptr_267) {
    wchar_t* ptr = nullptr;
    std::string result = StringMaker<wchar_t *>::convert(ptr);
    EXPECT_EQ(result, "{null string}");
}

TEST(StringMakerWCharPtr_267, HandlesEmptyString_267) {
    wchar_t empty[] = L"";
    std::string result_ptr  = StringMaker<wchar_t *>::convert(empty);
    std::string result_cptr = StringMaker<wchar_t const *>::convert(empty);

    // Non-null empty input should not be treated as null.
    EXPECT_NE(result_ptr, "{null string}");
    // Consistency with const-overload for the same input.
    EXPECT_EQ(result_ptr, result_cptr);
}

TEST(StringMakerWCharPtr_267, StopsAtFirstNullTerminator_EmbeddedNull_267) {
    // Create a buffer with an embedded null and trailing data.
    // The observable behavior, via standard C-string semantics,
    // is to read only up to the first null terminator.
    wchar_t with_null[4] = { L'A', L'\0', L'B', L'\0' };

    std::string result_embedded = StringMaker<wchar_t *>::convert(with_null);

    // Compare with a single-character buffer "A" to confirm boundary behavior.
    wchar_t just_A[] = L"A";
    std::string result_A = StringMaker<wchar_t *>::convert(just_A);

    EXPECT_EQ(result_embedded, result_A);
    EXPECT_NE(result_embedded, "{null string}");
}

// ---------- Non-mutating behavior (observable) ----------

TEST(StringMakerWCharPtr_267, DoesNotModifyInputBuffer_267) {
    wchar_t mutable_buf[] = L"KeepMe";
    const std::wstring before(mutable_buf);

    (void)StringMaker<wchar_t *>::convert(mutable_buf);

    const std::wstring after(mutable_buf);
    EXPECT_EQ(before, after);
}

// ---------- Larger input (still observable-only) ----------

TEST(StringMakerWCharPtr_267, ConvertsLongString_267) {
    // A longer input ensures no truncation/crash is observable via interface.
    std::wstring long_ws(1024, L'x'); // 1024 'x' characters
    std::string result = StringMaker<wchar_t *>::convert(&long_ws[0]);

    EXPECT_NE(result, "{null string}");
    // Spot-check that some recognizable portion is present.
    EXPECT_NE(result.find("xxx"), std::string::npos);
}

} // namespace
