// File: tests/stringref_compare_tests_682.cpp

#include <gtest/gtest.h>
#include <string>
#include "catch2/internal/catch_stringref.hpp"

using Catch::StringRef;

// A small helper to assert consistency between compare() and operator<
static void ExpectStrictWeakOrderConsistent(const StringRef& a, const StringRef& b) {
    const int c = a.compare(b);
    // compare/relational consistency (observable via public API only)
    if (c == 0) {
        EXPECT_FALSE(a < b);
        EXPECT_FALSE(b < a);
    } else if (c < 0) {
        EXPECT_TRUE(a < b);
        EXPECT_FALSE(b < a);
    } else {
        EXPECT_TRUE(b < a);
        EXPECT_FALSE(a < b);
    }
}

// Normal operation: equal strings -> compare returns 0
TEST(StringRefCompareTest_682, Compare_EqualStrings_ReturnsZero_682) {
    StringRef a("abc");
    StringRef b("abc");
    EXPECT_EQ(0, a.compare(b));
    EXPECT_EQ(0, b.compare(a));

    ExpectStrictWeakOrderConsistent(a, b);
}

// Boundary: lhs is prefix of rhs -> compare < 0
TEST(StringRefCompareTest_682, Compare_LhsPrefixOfRhs_ReturnsNegative_682) {
    StringRef a("ab");
    StringRef b("abc");
    EXPECT_LT(a.compare(b), 0);
    EXPECT_GT(b.compare(a), 0);

    ExpectStrictWeakOrderConsistent(a, b);
}

// Boundary: rhs is prefix of lhs -> compare > 0
TEST(StringRefCompareTest_682, Compare_RhsPrefixOfLhs_ReturnsPositive_682) {
    StringRef a("abc");
    StringRef b("ab");
    EXPECT_GT(a.compare(b), 0);
    EXPECT_LT(b.compare(a), 0);

    ExpectStrictWeakOrderConsistent(a, b);
}

// Normal operation: first differing character decides sign
TEST(StringRefCompareTest_682, Compare_FirstDifferingChar_DeterminesOrdering_682) {
    StringRef a("abc");
    StringRef b("xbc");
    EXPECT_LT(a.compare(b), 0); // 'a' < 'x'
    EXPECT_GT(b.compare(a), 0);

    ExpectStrictWeakOrderConsistent(a, b);
}

// Boundary: empty vs non-empty and empty vs empty
TEST(StringRefCompareTest_682, Compare_EmptyStrings_And_AgainstNonEmpty_682) {
    StringRef empty("");
    StringRef nonEmpty("a");

    EXPECT_EQ(0, empty.compare(StringRef("")));   // empty vs empty
    EXPECT_LT(empty.compare(nonEmpty), 0);        // empty < non-empty
    EXPECT_GT(nonEmpty.compare(empty), 0);        // non-empty > empty

    ExpectStrictWeakOrderConsistent(empty, nonEmpty);
}

// Exceptional-like edge (observable): embedded NULs via sized ctor
// NOTE: This uses the (char*, size) ctor to ensure the StringRef can include '\0'.
// The observable behavior here is that comparison stops at the first '\0' as if
// the strings were equal up to that point, and with equal sizes compare returns 0.
TEST(StringRefCompareTest_682, Compare_EmbeddedNulls_WithSizedConstructor_682) {
    const char lhsBuf[] = { 'a', '\0', 'b' };
    const char rhsBuf[] = { 'a', '\0', 'c' };

    StringRef lhs(lhsBuf, 3);
    StringRef rhs(rhsBuf, 3);

    // Observable expectation from provided implementation: treated as equal
    // because comparison stops at the first '\0' and sizes are equal.
    EXPECT_EQ(0, lhs.compare(rhs));
    EXPECT_EQ(0, rhs.compare(lhs));

    ExpectStrictWeakOrderConsistent(lhs, rhs);
}

// Consistency check across a few representative pairs for operator< vs compare
TEST(StringRefCompareTest_682, OperatorLess_IsConsistentWithCompare_682) {
    struct Pair { StringRef a; StringRef b; };
    Pair cases[] = {
        { StringRef("abc"), StringRef("abc") },
        { StringRef("ab"),  StringRef("abc") },
        { StringRef("abc"), StringRef("ab") },
        { StringRef("abc"), StringRef("xbc") },
        { StringRef(""),    StringRef("a")   },
    };

    for (const auto& p : cases) {
        ExpectStrictWeakOrderConsistent(p.a, p.b);
    }
}
