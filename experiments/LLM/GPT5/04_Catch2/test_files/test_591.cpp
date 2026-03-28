// File: tests/catch_string_manip_tests.cpp

#include <gtest/gtest.h>
#include <clocale>   // setlocale
#include <cctype>    // std::tolower confirmation not used to define behavior, only standard ref
#include "catch_string_manip.hpp" // or the appropriate header that declares Catch::toLower

// If there is no public header, you can forward-declare based on the provided interface:
// namespace Catch { char toLower(char c); }

class CatchStringManipTest_591 : public ::testing::Test {
protected:
    void SetUp() override {
        // Force "C" locale to make character classification predictable across platforms.
        // We do not test locale-specific mappings beyond ASCII.
        std::setlocale(LC_CTYPE, "C");
    }
};

TEST_F(CatchStringManipTest_591, UppercaseLettersAreLowercased_591) {
    // Normal operation: ASCII uppercase -> lowercase
    EXPECT_EQ('a', Catch::toLower('A'));
    EXPECT_EQ('z', Catch::toLower('Z'));
    EXPECT_EQ('m', Catch::toLower('M'));
}

TEST_F(CatchStringManipTest_591, LowercaseLettersRemainUnchanged_591) {
    // Normal operation: already-lowercase characters should not change
    EXPECT_EQ('a', Catch::toLower('a'));
    EXPECT_EQ('m', Catch::toLower('m'));
    EXPECT_EQ('z', Catch::toLower('z'));
}

TEST_F(CatchStringManipTest_591, DigitsRemainUnchanged_591) {
    // Boundary/other visible behavior: non-alpha characters are unaffected in "C" locale
    EXPECT_EQ('0', Catch::toLower('0'));
    EXPECT_EQ('5', Catch::toLower('5'));
    EXPECT_EQ('9', Catch::toLower('9'));
}

TEST_F(CatchStringManipTest_591, PunctuationRemainsUnchanged_591) {
    // Boundary/other visible behavior: punctuation unaffected in "C" locale
    EXPECT_EQ('!', Catch::toLower('!'));
    EXPECT_EQ('@', Catch::toLower('@'));
    EXPECT_EQ('_', Catch::toLower('_'));
}

TEST_F(CatchStringManipTest_591, ExtendedCharDoesNotInvokeUBAndIsStableInCLocale_591) {
    // Exceptional/boundary case:
    // When 'char' is signed, values with the high bit set are negative.
    // The implementation casts to unsigned char before calling std::tolower,
    // which should avoid undefined behavior. In the "C" locale, these
    // extended values have no lowercase mapping and should remain unchanged.
    // We verify observable behavior (no crash and value unchanged in "C").
    const char extended1 = static_cast<char>(0xC0); // À in Latin-1; negative on platforms with signed char
    const char extended2 = static_cast<char>(0xFF); // ÿ in Latin-1; negative on platforms with signed char

    EXPECT_EQ(extended1, Catch::toLower(extended1));
    EXPECT_EQ(extended2, Catch::toLower(extended2));
}

TEST_F(CatchStringManipTest_591, NullCharRemainsUnchanged_591) {
    // Boundary: NUL character should pass through unchanged
    EXPECT_EQ('\0', Catch::toLower('\0'));
}
