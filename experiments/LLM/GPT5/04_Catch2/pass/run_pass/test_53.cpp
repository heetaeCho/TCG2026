// File: columns_iterator_equality_53_tests.cpp

#include <gtest/gtest.h>

// Use the public interface only.
#include "catch2/internal/catch_textflow.hpp"

using Catch::TextFlow::Column;
using Catch::TextFlow::Columns;

namespace {

// Helper to create a Columns instance with a couple of columns.
// (Relies only on public construction/append operations.)
Columns makeTwoCols() {
    Columns cols;
    cols += Column("alpha");
    cols += Column("beta");
    return cols;
}

} // namespace

// 1) Reflexivity: an iterator compares equal to itself.
TEST(ColumnsIteratorEquality_53, IteratorIsEqualToItself_53) {
    auto cols = makeTwoCols();
    auto it = cols.begin();
    EXPECT_TRUE(it == it);
}

// 2) Begin vs End on the same Columns: distinct positions are not equal.
TEST(ColumnsIteratorEquality_53, BeginIsNotEqualToEnd_53) {
    auto cols = makeTwoCols();
    auto b = cols.begin();
    auto e = cols.end();
    EXPECT_FALSE(b == e);
    EXPECT_TRUE(b != e); // also checks the negation behaves consistently
}

// 3) End iterators from the same Columns compare equal.
TEST(ColumnsIteratorEquality_53, EndIteratorsFromSameColumnsAreEqual_53) {
    auto cols = makeTwoCols();
    auto e1 = cols.end();
    auto e2 = cols.end();
    EXPECT_TRUE(e1 == e2);
    EXPECT_FALSE(e1 != e2);
}

// 4) Iterators from different Columns are not equal, even if the content matches.
TEST(ColumnsIteratorEquality_53, IteratorsFromDifferentColumnsAreNotEqual_53) {
    auto cols1 = makeTwoCols();
    auto cols2 = makeTwoCols(); // same textual content, distinct container

    auto b1 = cols1.begin();
    auto b2 = cols2.begin();
    auto e1 = cols1.end();
    auto e2 = cols2.end();

    // Begin vs begin from different containers: should not be equal
    EXPECT_FALSE(b1 == b2);
    EXPECT_TRUE(b1 != b2);

    // End vs end from different containers: should not be equal
    EXPECT_FALSE(e1 == e2);
    EXPECT_TRUE(e1 != e2);
}

// 5) Equality is preserved across copies of the same iterator.
TEST(ColumnsIteratorEquality_53, CopiedIteratorsRemainEqual_53) {
    auto cols = makeTwoCols();
    auto it1 = cols.begin();
    auto it2 = it1;  // copy
    EXPECT_TRUE(it1 == it2);
    EXPECT_FALSE(it1 != it2);

    // Advance one copy and they should no longer be equal (observable difference)
    ++it2;
    EXPECT_FALSE(it1 == it2);
    EXPECT_TRUE(it1 != it2);
}
