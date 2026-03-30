// File: tests/ColumnConstIteratorEquals_45.cpp
#include <gtest/gtest.h>
#include "catch2/internal/catch_textflow.hpp"

using Catch::TextFlow::Column;

class ColumnConstIteratorTest_45 : public ::testing::Test {
protected:
    // Helper to create small Columns for iteration
    static Column makeCol(const std::string& s) {
        // Rely on Column's public interface; treat implementation as black box.
        // In Catch2, Column is constructible from a string (width is optional).
        return Column{s};
    }
};

// [Normal] Iterators constructed from the same Column at the same position compare equal
TEST_F(ColumnConstIteratorTest_45, EqualWhenSameColumnAndPosition_45) {
    auto col = ColumnConstIteratorTest_45::makeCol("alpha\nbeta");
    Column::const_iterator it1{col};
    Column::const_iterator it2{col};

    EXPECT_TRUE(it1 == it2);
    EXPECT_FALSE(it1 != it2);
}

// [Boundary / Movement] After advancing one iterator, they are not equal anymore (same Column)
TEST_F(ColumnConstIteratorTest_45, NotEqualWhenDifferentPositionSameColumn_45) {
    auto col = ColumnConstIteratorTest_45::makeCol("line1\nline2");
    Column::const_iterator it_begin{col};
    Column::const_iterator it_other{col};

    ++it_other; // move to next observable position (black-box movement)
    EXPECT_FALSE(it_begin == it_other);
    EXPECT_TRUE(it_begin != it_other);
}

// [Distinguish Owner] Iterators at the same apparent position but from different Columns are not equal
TEST_F(ColumnConstIteratorTest_45, NotEqualWhenDifferentColumnsSamePosition_45) {
    auto colA = ColumnConstIteratorTest_45::makeCol("same");
    auto colB = ColumnConstIteratorTest_45::makeCol("same");

    Column::const_iterator itA{colA};
    Column::const_iterator itB{colB};

    // Even if their dereferenced content might match, equality ties to the owning Column
    EXPECT_FALSE(itA == itB);
    EXPECT_TRUE(itA != itB);
}

// [Post-increment contract] post++ returns an iterator equal to the pre-increment state
TEST_F(ColumnConstIteratorTest_45, PostIncrementReturnsOldIterator_45) {
    auto col = ColumnConstIteratorTest_45::makeCol("x\ny");
    Column::const_iterator it{col};

    Column::const_iterator before = it;   // snapshot current position
    Column::const_iterator returned = it++; // returned should equal 'before'

    EXPECT_TRUE(returned == before);
    EXPECT_FALSE(returned != before);
    // And after the post++, 'it' should have moved so it's no longer equal to 'before'
    EXPECT_FALSE(it == before);
}

// [Relation properties] Equality is reflexive and symmetric
TEST_F(ColumnConstIteratorTest_45, EqualityIsReflexiveAndSymmetric_45) {
    auto col = ColumnConstIteratorTest_45::makeCol("a\nb\nc");
    Column::const_iterator it1{col};
    Column::const_iterator it2{col};

    // Reflexive
    EXPECT_TRUE(it1 == it1);

    // Symmetric
    EXPECT_TRUE(it1 == it2);
    EXPECT_TRUE(it2 == it1);

    // After movement, symmetry holds for inequality as well
    ++it2;
    EXPECT_TRUE(it1 != it2);
    EXPECT_TRUE(it2 != it1);
}
