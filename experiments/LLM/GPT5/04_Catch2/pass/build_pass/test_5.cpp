// File: stringref_not_equal_tests_5.cpp
#include <gtest/gtest.h>
#include <string>
#include <type_traits>
#include "catch2/internal/catch_stringref.hpp"

using Catch::StringRef;

// Compile-time contract: operator!= is noexcept per the interface
static_assert(
    noexcept(std::declval<const StringRef&>() != std::declval<const StringRef&>()),
    "StringRef::operator!= must be noexcept");

// ---------------------- Tests ----------------------

TEST(StringRefTest_5, NotEqualIsNegation_ForIdenticalLiterals_5) {
    StringRef a("hello");
    StringRef b("hello");

    // Core requirement: != must be logical negation of ==
    EXPECT_EQ(a != b, !(a == b));
    // Sanity for common usage
    EXPECT_FALSE(a != b);
    EXPECT_TRUE(a == b);
}

TEST(StringRefTest_5, NotEqualIsNegation_ForDifferentLiterals_5) {
    StringRef a("hello");
    StringRef b("world");

    EXPECT_EQ(a != b, !(a == b));
}

TEST(StringRefTest_5, NotEqualIsNegation_EmptyVsEmpty_5) {
    StringRef a;        // default-constructed empty
    StringRef b("");    // explicit empty

    EXPECT_EQ(a != b, !(a == b));
}

TEST(StringRefTest_5, NotEqualIsNegation_EmptyVsNonEmpty_5) {
    StringRef empty;
    StringRef nonEmpty("x");

    EXPECT_EQ(empty != nonEmpty, !(empty == nonEmpty));
    EXPECT_EQ(nonEmpty != empty, !(nonEmpty == empty));
}

TEST(StringRefTest_5, NotEqualIsNegation_WithStdStringCtor_5) {
    std::string s = "abc";
    StringRef a(s);         // std::string constructor
    StringRef b("abc");     // c-string constructor

    EXPECT_EQ(a != b, !(a == b));
}

TEST(StringRefTest_5, NotEqualIsNegation_WithEmbeddedNullsAndSizedCtor_5) {
    // Use sized constructor to create views that may include embedded '\0'
    const char raw1[] = { 'a', '\0', 'b' };
    const char raw2[] = { 'a', '\0', 'b' };
    const char raw3[] = { 'a' };

    StringRef s1(raw1, 3);
    StringRef s2(raw2, 3);
    StringRef s3(raw3, 1);

    // Same content/size
    EXPECT_EQ(s1 != s2, !(s1 == s2));

    // Different size/content when compared to "a"
    EXPECT_EQ(s1 != s3, !(s1 == s3));
    EXPECT_EQ(s3 != s1, !(s3 == s1));
}

TEST(StringRefTest_5, NotEqualIsSymmetric_ForRepresentativePairs_5) {
    StringRef pairs[][2] = {
        { StringRef("abc"), StringRef("abc") },
        { StringRef("abc"), StringRef("abd") },
        { StringRef(""),    StringRef("")    },
        { StringRef(""),    StringRef("a")   },
    };

    for (auto& p : pairs) {
        const StringRef& a = p[0];
        const StringRef& b = p[1];
        // Symmetry: a != b equals b != a
        EXPECT_EQ(a != b, b != a);
        // Still must be negation of ==
        EXPECT_EQ(a != b, !(a == b));
        EXPECT_EQ(b != a, !(b == a));
    }
}
