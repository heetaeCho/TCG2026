// File: column_const_iterator_inequality_46_tests.cpp
#include <gtest/gtest.h>
#include "catch2/internal/catch_textflow.hpp"

using Catch::TextFlow::Column;

class ColumnIteratorTest_46 : public ::testing::Test {};

// [Normal] begin vs end: begin must not equal end; inequality mirrors equality.
TEST_F(ColumnIteratorTest_46, BeginNotEqualEnd_46) {
    Column col{"Hello world"};
    auto it = col.begin();
    auto ed = col.end();

    // Sanity: standard range property
    EXPECT_NE(it, ed);

    // Core contract for this pair
    EXPECT_EQ((it != ed), !(it == ed));
    EXPECT_EQ((ed != it), !(ed == it));
}

// [Normal] identical iterators compare equal; inequality is false.
TEST_F(ColumnIteratorTest_46, IdenticalIteratorsAreEqual_NotInequal_46) {
    Column col{"single line"};
    auto it1 = col.begin();
    auto it2 = it1; // copy-constructed iterator to same position

    EXPECT_EQ(it1, it2);
    EXPECT_FALSE(it1 != it2);
    EXPECT_EQ((it1 != it2), !(it1 == it2));
    EXPECT_EQ((it2 != it1), !(it2 == it1));
}

// [Progression] iterate to end: at end, iterator equals end; inequality is false.
TEST_F(ColumnIteratorTest_46, AdvancingEventuallyEqualsEnd_46) {
    Column col{"This string will produce one or more lines depending on formatting."};
    auto it = col.begin();
    auto ed = col.end();

    // Walk until end using only public interface
    while (it != ed) {
        ++it;
    }

    // Now 'it' is at end — verify equality/inequality relationship
    EXPECT_EQ(it, ed);
    EXPECT_FALSE(it != ed);
    EXPECT_EQ((it != ed), !(it == ed));
    EXPECT_EQ((ed != it), !(ed == it));
}

// [Operator forms] postfix vs prefix increments keep inequality consistent with equality.
TEST_F(ColumnIteratorTest_46, PrefixPostfixIncrementConsistency_46) {
    Column col{"Short text"};
    auto it_prefix = col.begin();
    auto it_post   = col.begin();
    auto ed        = col.end();

    // If already at end, this still holds; otherwise step once with each form
    if (it_prefix != ed) {
        ++it_prefix;   // prefix
    }
    if (it_post != ed) {
        it_post++;     // postfix
    }

    // For each, inequality should be logical negation of equality when compared to end
    EXPECT_EQ((it_prefix != ed), !(it_prefix == ed));
    EXPECT_EQ((it_post   != ed), !(it_post   == ed));
}

// [Symmetry] inequality is symmetric; and also equals negation of equality both ways.
TEST_F(ColumnIteratorTest_46, InequalityIsSymmetric_46) {
    Column col{"Symmetry check\nwith multiple potential lines"};
    auto a = col.begin();
    auto b = col.begin();
    auto e = col.end();

    // Case 1: same position
    EXPECT_EQ(a, b);
    EXPECT_FALSE(a != b);
    EXPECT_FALSE(b != a);
    EXPECT_EQ((a != b), !(a == b));
    EXPECT_EQ((b != a), !(b == a));

    // Case 2: different positions (advance one of them if possible)
    if (b != e) {
        ++b;
        // Now positions differ (unless the range was empty, in which case loop didn't run)
        if (a != b) {
            EXPECT_TRUE(a != b);
            EXPECT_TRUE(b != a);
            EXPECT_EQ((a != b), !(a == b));
            EXPECT_EQ((b != a), !(b == a));
        }
    }
}
