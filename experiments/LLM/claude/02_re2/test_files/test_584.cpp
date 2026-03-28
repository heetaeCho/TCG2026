#include "re2/sparse_array.h"
#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <algorithm>

namespace re2 {

// Test fixture for SparseArray with int values
class SparseArrayTest_584 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Constructor tests
TEST_F(SparseArrayTest_584, DefaultConstructor_584) {
    SparseArray<int> sa;
    EXPECT_EQ(sa.size(), 0);
    EXPECT_TRUE(sa.empty());
}

TEST_F(SparseArrayTest_584, ConstructorWithMaxSize_584) {
    SparseArray<int> sa(100);
    EXPECT_EQ(sa.size(), 0);
    EXPECT_TRUE(sa.empty());
    EXPECT_EQ(sa.max_size(), 100);
}

TEST_F(SparseArrayTest_584, ConstructorWithZeroMaxSize_584) {
    SparseArray<int> sa(0);
    EXPECT_EQ(sa.size(), 0);
    EXPECT_TRUE(sa.empty());
    EXPECT_EQ(sa.max_size(), 0);
}

// Copy constructor
TEST_F(SparseArrayTest_584, CopyConstructor_584) {
    SparseArray<int> sa(10);
    sa.set(3, 30);
    sa.set(7, 70);

    SparseArray<int> copy(sa);
    EXPECT_EQ(copy.size(), 2);
    EXPECT_TRUE(copy.has_index(3));
    EXPECT_TRUE(copy.has_index(7));
    EXPECT_EQ(copy.get_existing(3), 30);
    EXPECT_EQ(copy.get_existing(7), 70);
}

// Move constructor
TEST_F(SparseArrayTest_584, MoveConstructor_584) {
    SparseArray<int> sa(10);
    sa.set(3, 30);
    sa.set(7, 70);

    SparseArray<int> moved(std::move(sa));
    EXPECT_EQ(moved.size(), 2);
    EXPECT_TRUE(moved.has_index(3));
    EXPECT_TRUE(moved.has_index(7));
    EXPECT_EQ(moved.get_existing(3), 30);
    EXPECT_EQ(moved.get_existing(7), 70);
}

// Copy assignment
TEST_F(SparseArrayTest_584, CopyAssignment_584) {
    SparseArray<int> sa(10);
    sa.set(2, 20);
    sa.set(5, 50);

    SparseArray<int> other(5);
    other = sa;
    EXPECT_EQ(other.size(), 2);
    EXPECT_TRUE(other.has_index(2));
    EXPECT_TRUE(other.has_index(5));
    EXPECT_EQ(other.get_existing(2), 20);
    EXPECT_EQ(other.get_existing(5), 50);
}

// Move assignment
TEST_F(SparseArrayTest_584, MoveAssignment_584) {
    SparseArray<int> sa(10);
    sa.set(2, 20);
    sa.set(5, 50);

    SparseArray<int> other(5);
    other = std::move(sa);
    EXPECT_EQ(other.size(), 2);
    EXPECT_TRUE(other.has_index(2));
    EXPECT_TRUE(other.has_index(5));
    EXPECT_EQ(other.get_existing(2), 20);
    EXPECT_EQ(other.get_existing(5), 50);
}

// set() tests
TEST_F(SparseArrayTest_584, SetNewElement_584) {
    SparseArray<int> sa(10);
    sa.set(3, 42);
    EXPECT_EQ(sa.size(), 1);
    EXPECT_TRUE(sa.has_index(3));
    EXPECT_EQ(sa.get_existing(3), 42);
}

TEST_F(SparseArrayTest_584, SetOverwriteExistingElement_584) {
    SparseArray<int> sa(10);
    sa.set(3, 42);
    sa.set(3, 99);
    EXPECT_EQ(sa.size(), 1);
    EXPECT_TRUE(sa.has_index(3));
    EXPECT_EQ(sa.get_existing(3), 99);
}

TEST_F(SparseArrayTest_584, SetMultipleElements_584) {
    SparseArray<int> sa(10);
    sa.set(0, 100);
    sa.set(5, 500);
    sa.set(9, 900);
    EXPECT_EQ(sa.size(), 3);
    EXPECT_TRUE(sa.has_index(0));
    EXPECT_TRUE(sa.has_index(5));
    EXPECT_TRUE(sa.has_index(9));
    EXPECT_EQ(sa.get_existing(0), 100);
    EXPECT_EQ(sa.get_existing(5), 500);
    EXPECT_EQ(sa.get_existing(9), 900);
}

// set_new() tests
TEST_F(SparseArrayTest_584, SetNew_584) {
    SparseArray<int> sa(10);
    sa.set_new(4, 44);
    EXPECT_EQ(sa.size(), 1);
    EXPECT_TRUE(sa.has_index(4));
    EXPECT_EQ(sa.get_existing(4), 44);
}

// set_existing() tests
TEST_F(SparseArrayTest_584, SetExisting_584) {
    SparseArray<int> sa(10);
    sa.set(4, 44);
    sa.set_existing(4, 88);
    EXPECT_EQ(sa.size(), 1);
    EXPECT_TRUE(sa.has_index(4));
    EXPECT_EQ(sa.get_existing(4), 88);
}

// has_index() tests
TEST_F(SparseArrayTest_584, HasIndexReturnsFalseForUnset_584) {
    SparseArray<int> sa(10);
    EXPECT_FALSE(sa.has_index(0));
    EXPECT_FALSE(sa.has_index(5));
    EXPECT_FALSE(sa.has_index(9));
}

TEST_F(SparseArrayTest_584, HasIndexReturnsTrueForSet_584) {
    SparseArray<int> sa(10);
    sa.set(5, 50);
    EXPECT_TRUE(sa.has_index(5));
}

// clear() tests
TEST_F(SparseArrayTest_584, ClearEmptiesArray_584) {
    SparseArray<int> sa(10);
    sa.set(1, 10);
    sa.set(3, 30);
    sa.set(5, 50);
    EXPECT_EQ(sa.size(), 3);

    sa.clear();
    EXPECT_EQ(sa.size(), 0);
    EXPECT_TRUE(sa.empty());
    EXPECT_FALSE(sa.has_index(1));
    EXPECT_FALSE(sa.has_index(3));
    EXPECT_FALSE(sa.has_index(5));
}

TEST_F(SparseArrayTest_584, ClearOnEmptyArray_584) {
    SparseArray<int> sa(10);
    sa.clear();
    EXPECT_EQ(sa.size(), 0);
    EXPECT_TRUE(sa.empty());
}

// empty() tests
TEST_F(SparseArrayTest_584, EmptyOnNewArray_584) {
    SparseArray<int> sa(10);
    EXPECT_TRUE(sa.empty());
}

TEST_F(SparseArrayTest_584, NotEmptyAfterSet_584) {
    SparseArray<int> sa(10);
    sa.set(0, 1);
    EXPECT_FALSE(sa.empty());
}

// size() tests
TEST_F(SparseArrayTest_584, SizeIncreasesWithNewElements_584) {
    SparseArray<int> sa(10);
    EXPECT_EQ(sa.size(), 0);
    sa.set(0, 1);
    EXPECT_EQ(sa.size(), 1);
    sa.set(1, 2);
    EXPECT_EQ(sa.size(), 2);
    sa.set(2, 3);
    EXPECT_EQ(sa.size(), 3);
}

TEST_F(SparseArrayTest_584, SizeDoesNotIncreaseOnOverwrite_584) {
    SparseArray<int> sa(10);
    sa.set(0, 1);
    sa.set(0, 2);
    EXPECT_EQ(sa.size(), 1);
}

// max_size() tests
TEST_F(SparseArrayTest_584, MaxSizeReflectsConstructorArg_584) {
    SparseArray<int> sa(50);
    EXPECT_EQ(sa.max_size(), 50);
}

// resize() tests
TEST_F(SparseArrayTest_584, ResizeIncreases_584) {
    SparseArray<int> sa(5);
    EXPECT_EQ(sa.max_size(), 5);
    sa.resize(20);
    EXPECT_EQ(sa.max_size(), 20);
}

TEST_F(SparseArrayTest_584, ResizePreservesExistingElements_584) {
    SparseArray<int> sa(10);
    sa.set(2, 20);
    sa.set(4, 40);
    sa.resize(20);
    EXPECT_EQ(sa.size(), 2);
    EXPECT_TRUE(sa.has_index(2));
    EXPECT_TRUE(sa.has_index(4));
    EXPECT_EQ(sa.get_existing(2), 20);
    EXPECT_EQ(sa.get_existing(4), 40);
}

TEST_F(SparseArrayTest_584, ResizeToSmallerTruncatesElements_584) {
    SparseArray<int> sa(10);
    sa.set(2, 20);
    sa.set(8, 80);
    sa.resize(5);
    EXPECT_EQ(sa.max_size(), 5);
    // Index 2 should be within range, index 8 should not
    EXPECT_TRUE(sa.has_index(2));
    EXPECT_EQ(sa.get_existing(2), 20);
}

// Iterator tests
TEST_F(SparseArrayTest_584, BeginEndOnEmpty_584) {
    SparseArray<int> sa(10);
    EXPECT_EQ(sa.begin(), sa.end());
}

TEST_F(SparseArrayTest_584, IteratorTraversal_584) {
    SparseArray<int> sa(10);
    sa.set(1, 10);
    sa.set(3, 30);
    sa.set(5, 50);

    int count = 0;
    for (auto it = sa.begin(); it != sa.end(); ++it) {
        count++;
    }
    EXPECT_EQ(count, 3);
}

TEST_F(SparseArrayTest_584, IteratorValues_584) {
    SparseArray<int> sa(10);
    sa.set(2, 20);
    sa.set(4, 40);

    std::vector<std::pair<int, int>> entries;
    for (auto it = sa.begin(); it != sa.end(); ++it) {
        entries.push_back({it->index(), it->value()});
    }
    EXPECT_EQ(entries.size(), 2u);

    // Check that both entries are present (order may vary)
    bool found2 = false, found4 = false;
    for (const auto& e : entries) {
        if (e.first == 2 && e.second == 20) found2 = true;
        if (e.first == 4 && e.second == 40) found4 = true;
    }
    EXPECT_TRUE(found2);
    EXPECT_TRUE(found4);
}

// Test with string values
TEST_F(SparseArrayTest_584, StringValues_584) {
    SparseArray<std::string> sa(10);
    sa.set(0, "hello");
    sa.set(9, "world");
    EXPECT_EQ(sa.size(), 2);
    EXPECT_TRUE(sa.has_index(0));
    EXPECT_TRUE(sa.has_index(9));
    EXPECT_EQ(sa.get_existing(0), "hello");
    EXPECT_EQ(sa.get_existing(9), "world");
}

// Test set returns iterator
TEST_F(SparseArrayTest_584, SetReturnsIterator_584) {
    SparseArray<int> sa(10);
    auto it = sa.set(5, 50);
    EXPECT_EQ(it->index(), 5);
    EXPECT_EQ(it->value(), 50);
}

TEST_F(SparseArrayTest_584, SetNewReturnsIterator_584) {
    SparseArray<int> sa(10);
    auto it = sa.set_new(7, 70);
    EXPECT_EQ(it->index(), 7);
    EXPECT_EQ(it->value(), 70);
}

TEST_F(SparseArrayTest_584, SetExistingReturnsIterator_584) {
    SparseArray<int> sa(10);
    sa.set(3, 30);
    auto it = sa.set_existing(3, 33);
    EXPECT_EQ(it->index(), 3);
    EXPECT_EQ(it->value(), 33);
}

// Boundary: fill entire array
TEST_F(SparseArrayTest_584, FillEntireArray_584) {
    const int max_size = 100;
    SparseArray<int> sa(max_size);
    for (int i = 0; i < max_size; i++) {
        sa.set(i, i * 10);
    }
    EXPECT_EQ(sa.size(), max_size);
    for (int i = 0; i < max_size; i++) {
        EXPECT_TRUE(sa.has_index(i));
        EXPECT_EQ(sa.get_existing(i), i * 10);
    }
}

// Boundary: index 0
TEST_F(SparseArrayTest_584, IndexZero_584) {
    SparseArray<int> sa(10);
    sa.set(0, 999);
    EXPECT_TRUE(sa.has_index(0));
    EXPECT_EQ(sa.get_existing(0), 999);
}

// Boundary: last valid index
TEST_F(SparseArrayTest_584, LastValidIndex_584) {
    SparseArray<int> sa(10);
    sa.set(9, 999);
    EXPECT_TRUE(sa.has_index(9));
    EXPECT_EQ(sa.get_existing(9), 999);
}

// less() static function test
TEST_F(SparseArrayTest_584, LessComparison_584) {
    SparseArray<int> sa(10);
    sa.set(5, 50);
    sa.set(2, 20);

    // Access elements and test less
    auto it1 = sa.begin();
    auto it2 = sa.begin();
    ++it2;

    // The less function compares by index
    if (it1->index() < it2->index()) {
        EXPECT_TRUE(SparseArray<int>::less(*it1, *it2));
        EXPECT_FALSE(SparseArray<int>::less(*it2, *it1));
    } else {
        EXPECT_TRUE(SparseArray<int>::less(*it2, *it1));
        EXPECT_FALSE(SparseArray<int>::less(*it1, *it2));
    }
}

// After clear, can re-add elements
TEST_F(SparseArrayTest_584, ReuseAfterClear_584) {
    SparseArray<int> sa(10);
    sa.set(1, 10);
    sa.set(2, 20);
    sa.clear();

    sa.set(3, 30);
    sa.set(4, 40);
    EXPECT_EQ(sa.size(), 2);
    EXPECT_FALSE(sa.has_index(1));
    EXPECT_FALSE(sa.has_index(2));
    EXPECT_TRUE(sa.has_index(3));
    EXPECT_TRUE(sa.has_index(4));
    EXPECT_EQ(sa.get_existing(3), 30);
    EXPECT_EQ(sa.get_existing(4), 40);
}

// Test with max_size of 1
TEST_F(SparseArrayTest_584, MaxSizeOne_584) {
    SparseArray<int> sa(1);
    EXPECT_EQ(sa.max_size(), 1);
    EXPECT_EQ(sa.size(), 0);

    sa.set(0, 42);
    EXPECT_EQ(sa.size(), 1);
    EXPECT_TRUE(sa.has_index(0));
    EXPECT_EQ(sa.get_existing(0), 42);
}

// Test get_existing returns modifiable reference
TEST_F(SparseArrayTest_584, GetExistingModifiable_584) {
    SparseArray<int> sa(10);
    sa.set(3, 30);
    sa.get_existing(3) = 300;
    EXPECT_EQ(sa.get_existing(3), 300);
}

// Test multiple overwrites
TEST_F(SparseArrayTest_584, MultipleOverwrites_584) {
    SparseArray<int> sa(10);
    sa.set(5, 1);
    sa.set(5, 2);
    sa.set(5, 3);
    sa.set(5, 4);
    sa.set(5, 5);
    EXPECT_EQ(sa.size(), 1);
    EXPECT_EQ(sa.get_existing(5), 5);
}

// Resize to same size
TEST_F(SparseArrayTest_584, ResizeToSameSize_584) {
    SparseArray<int> sa(10);
    sa.set(3, 30);
    sa.resize(10);
    EXPECT_EQ(sa.max_size(), 10);
    EXPECT_EQ(sa.size(), 1);
    EXPECT_TRUE(sa.has_index(3));
    EXPECT_EQ(sa.get_existing(3), 30);
}

// Copy constructor produces independent copy
TEST_F(SparseArrayTest_584, CopyIsIndependent_584) {
    SparseArray<int> sa(10);
    sa.set(3, 30);

    SparseArray<int> copy(sa);
    copy.set(3, 99);

    EXPECT_EQ(sa.get_existing(3), 30);
    EXPECT_EQ(copy.get_existing(3), 99);
}

// Copy assignment produces independent copy
TEST_F(SparseArrayTest_584, CopyAssignmentIsIndependent_584) {
    SparseArray<int> sa(10);
    sa.set(3, 30);

    SparseArray<int> other(5);
    other = sa;
    other.set(3, 99);

    EXPECT_EQ(sa.get_existing(3), 30);
    EXPECT_EQ(other.get_existing(3), 99);
}

// Test with double values
TEST_F(SparseArrayTest_584, DoubleValues_584) {
    SparseArray<double> sa(10);
    sa.set(0, 3.14);
    sa.set(9, 2.718);
    EXPECT_DOUBLE_EQ(sa.get_existing(0), 3.14);
    EXPECT_DOUBLE_EQ(sa.get_existing(9), 2.718);
}

}  // namespace re2
