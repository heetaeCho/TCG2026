// File: tests/cased_string_case_suffix_217_test.cpp
#include <gtest/gtest.h>

// Headers from the provided interface
#include "catch2/catch_case_sensitive.hpp"
#include "catch2/matchers/catch_matchers_string.hpp"
// If StringRef literal is defined in a dedicated header in your tree,
// include it as needed. Otherwise the two above typically pull it in.

using Catch::CaseSensitive;
using Catch::Matchers::CasedString;
using Catch::StringRef;
using namespace Catch::literals; // for "_sr" literal, if provided by Catch2

// No fixture state is needed, but we keep a fixture for consistent naming.
class CasedStringTest_217 : public ::testing::Test {};

// [Normal] Case-sensitive: suffix should be empty.
TEST_F(CasedStringTest_217, CaseSensitiveYes_ReturnsEmptySuffix_217) {
    CasedString cs("Hello", CaseSensitive::Yes);
    StringRef suffix = cs.caseSensitivitySuffix();

    // Expect exactly empty suffix for case-sensitive mode.
    EXPECT_EQ(""_sr, suffix);
}

// [Normal] Case-insensitive: suffix should be the documented phrase.
TEST_F(CasedStringTest_217, CaseSensitiveNo_ReturnsExpectedSuffix_217) {
    CasedString cs("Hello", CaseSensitive::No);
    StringRef suffix = cs.caseSensitivitySuffix();

    EXPECT_EQ(" (case insensitive)"_sr, suffix);
}

// [Boundary] Empty input string should not affect the suffix (only sensitivity matters).
TEST_F(CasedStringTest_217, EmptyInputString_StillReturnsExpectedSuffixWhenNo_217) {
    CasedString cs("", CaseSensitive::No);
    StringRef suffix = cs.caseSensitivitySuffix();

    EXPECT_EQ(" (case insensitive)"_sr, suffix);
}

// [Stability] Repeated calls should return equal results.
TEST_F(CasedStringTest_217, RepeatedCalls_ReturnEqualSuffix_217) {
    CasedString cs("World", CaseSensitive::No);

    StringRef s1 = cs.caseSensitivitySuffix();
    StringRef s2 = cs.caseSensitivitySuffix();

    // We only verify observable equality, not identity.
    EXPECT_EQ(s1, s2);
    EXPECT_EQ(" (case insensitive)"_sr, s1);
}

// [Independence] Suffix is independent of underlying stored string value.
TEST_F(CasedStringTest_217, DifferentStrings_SameSuffixWhenNo_217) {
    CasedString a("AAA", CaseSensitive::No);
    CasedString b("bbb", CaseSensitive::No);

    EXPECT_EQ(a.caseSensitivitySuffix(), b.caseSensitivitySuffix());
    EXPECT_EQ(" (case insensitive)"_sr, a.caseSensitivitySuffix());
}

// [Cross-check] Switching sensitivity changes the observable suffix accordingly.
TEST_F(CasedStringTest_217, SensitivitySwitch_ChangesSuffix_217) {
    CasedString cs_yes("Data", CaseSensitive::Yes);
    CasedString cs_no ("Data", CaseSensitive::No);

    EXPECT_EQ(""_sr, cs_yes.caseSensitivitySuffix());
    EXPECT_EQ(" (case insensitive)"_sr, cs_no.caseSensitivitySuffix());
}
