// StartsWith tests (TEST_ID: 585)

#include <gtest/gtest.h>
#include <string>

// Public interface headers (treating impl as a black box)
#include "catch2/internal/catch_stringref.hpp"

// Forward declaration of the function under test (interface only).
namespace Catch {
    bool startsWith(StringRef s, char prefix);
}

using Catch::StringRef;
using Catch::startsWith;

// ---------- Normal operation ----------

TEST(StartsWithTest_585, ReturnsTrueWhenFirstCharMatches_585) {
    StringRef s("hello");
    EXPECT_TRUE(startsWith(s, 'h'));
}

TEST(StartsWithTest_585, ReturnsFalseWhenFirstCharDoesNotMatch_585) {
    StringRef s("hello");
    EXPECT_FALSE(startsWith(s, 'x'));
}

TEST(StartsWithTest_585, WorksWithStdStringConstructor_585) {
    std::string str = "world";
    StringRef s(str);
    EXPECT_TRUE(startsWith(s, 'w'));
    EXPECT_FALSE(startsWith(s, 'W'));
}

// ---------- Boundary conditions ----------

TEST(StartsWithTest_585, EmptyStringRefDefaultConstructedIsFalse_585) {
    StringRef empty;  // default constructed
    EXPECT_FALSE(startsWith(empty, 'a'));
}

TEST(StartsWithTest_585, EmptyCStringIsFalse_585) {
    StringRef empty("");
    EXPECT_FALSE(startsWith(empty, 'a'));
}

TEST(StartsWithTest_585, SingleCharacterStringMatchesAndMismatches_585) {
    StringRef one("z");
    EXPECT_TRUE(startsWith(one, 'z'));
    EXPECT_FALSE(startsWith(one, 'a'));
}

TEST(StartsWithTest_585, LeadingWhitespaceHandled_585) {
    StringRef s(" abc");
    EXPECT_TRUE(startsWith(s, ' '));
    EXPECT_FALSE(startsWith(s, 'a'));
}

TEST(StartsWithTest_585, CaseSensitivityVerified_585) {
    StringRef s("Hello");
    EXPECT_TRUE(startsWith(s, 'H'));
    EXPECT_FALSE(startsWith(s, 'h'));
}

// ---------- Special character / embedded NUL scenarios ----------

TEST(StartsWithTest_585, EmbeddedNulAfterFirstChar_585) {
    // Using a C-string with an embedded NUL after the first character.
    // Construction from raw C-string uses its visible leading char.
    const char withNul[] = "a\0b"; // literal yields array; C-string length is 1
    StringRef s(withNul);
    EXPECT_TRUE(startsWith(s, 'a'));
    EXPECT_FALSE(startsWith(s, 'b'));
}

TEST(StartsWithTest_585, ExplicitSizeAllowsLeadingNul_585) {
    // Use the (char const*, size) constructor to allow leading '\0'
    const char buf[] = { '\0', 'x', 'y' };
    StringRef s(buf, 3);
    EXPECT_TRUE(startsWith(s, '\0'));
    EXPECT_FALSE(startsWith(s, 'x'));
}
