// File: tests/tag_equals_tests_993.cpp
#include <gtest/gtest.h>

// Public interfaces under test
#include <catch2/catch_test_case_info.hpp>              // Catch::Tag
#include <catch2/internal/catch_stringref.hpp>          // Catch::StringRef

using Catch::Tag;
using Catch::StringRef;

//
// The tests below rely ONLY on the public interface:
//  - Tag(StringRef)
//  - operator==(const Tag&, const Tag&)
// We do not re-implement or assume any internal logic.
//

// Normal operation: equal ignoring ASCII case differences.
TEST(TagEquals_993, EqualIgnoringCase_993) {
    Tag a{ StringRef("Fast") };
    Tag b{ StringRef("fAsT") };
    EXPECT_TRUE(a == b);
    EXPECT_TRUE(b == a); // symmetry check (still observable behavior)
}

// Normal operation: not equal when text differs beyond case.
TEST(TagEquals_993, NotEqualDifferentText_993) {
    Tag a{ StringRef("fast") };
    Tag b{ StringRef("faster") };
    EXPECT_FALSE(a == b);
}

// Boundary: empty strings compare equal.
TEST(TagEquals_993, EmptyStringsEqual_993) {
    Tag a{ StringRef("") };
    Tag b{ StringRef("") };
    EXPECT_TRUE(a == b);
}

// Boundary/observable behavior: whitespace differences are significant.
TEST(TagEquals_993, NotEqualWithTrailingWhitespace_993) {
    Tag a{ StringRef("fast") };
    Tag b{ StringRef("fast ") }; // extra space
    EXPECT_FALSE(a == b);
}

// Additional observable properties: reflexivity and transitivity (via observable ==).
TEST(TagEquals_993, ReflexivityAndTransitivity_993) {
    Tag a{ StringRef("ReGrEsSiOn") };
    Tag b{ StringRef("regression") };
    Tag c{ StringRef("REGRESSION") };

    // Reflexivity
    EXPECT_TRUE(a == a);
    EXPECT TRUE(b == b);
    EXPECT_TRUE(c == c);

    // Symmetry and transitivity via observable comparisons
    EXPECT_TRUE(a == b);
    EXPECT_TRUE(b == a);
    EXPECT_TRUE(b == c);
    EXPECT_TRUE(a == c);
}

// Normal operation with non-alpha characters: case-insensitive only affects letters.
TEST(TagEquals_993, AlnumAndSymbols_993) {
    Tag a{ StringRef("ci-123_alpha.beta") };
    Tag b{ StringRef("CI-123_ALPHA.beta") };
    EXPECT_TRUE(a == b);
}

// Negative case: same letters, different punctuation -> not equal.
TEST(TagEquals_993, NotEqualDifferentPunctuation_993) {
    Tag a{ StringRef("perf:test") };
    Tag b{ StringRef("perf_test") };
    EXPECT_FALSE(a == b);
}
