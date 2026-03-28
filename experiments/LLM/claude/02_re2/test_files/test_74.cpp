#include "gtest/gtest.h"
#include "re2/sparse_array.h"

namespace re2 {

// Test fixture for SparseArray tests
class SparseArrayTest_74 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// --- Constructor Tests ---

TEST_F(SparseArrayTest_74, DefaultConstructor_74) {
    SparseArray<int> sa;
    EXPECT_EQ(sa.max_size(), 0);
    EXPECT_EQ(sa.size(), 0);
    EXPECT_TRUE(sa.empty());
}

TEST_F(SparseArrayTest_74, ParameterizedConstructor_74) {
    SparseArray<int> sa(100);
    EXPECT_EQ(sa.max_size(), 100);
    EXPECT_EQ(sa.size(), 0);
    EXPECT_TRUE(sa.empty());
}

TEST_F(SparseArrayTest_74, ParameterizedConstructorZeroSize_74) {
    SparseArray<int> sa(0);
    EXPECT_EQ(sa.max_size(), 0);
    EXPECT_EQ(sa.size(), 0);
    EXPECT_TRUE(sa.empty());
}

TEST_F(SparseArrayTest_74, CopyConstructor_74) {
    SparseArray<int> sa(50);
    sa.set(10, 42);
    sa.set(20, 84);

    SparseArray<int> copy(sa);
    EXPECT_EQ(copy.max_size(), 50);
    EXPECT_EQ(copy.size(), 2);
    EXPECT_TRUE(copy.has_index(10));
    EXPECT_TRUE(copy.has_index(20));
    EXPECT_EQ(copy.get_existing(10), 42);
    EXPECT_EQ(copy.get_existing(20), 84);
}

TEST_F(SparseArrayTest_74, MoveConstructor_74) {
    SparseArray<int> sa(50);
    sa.set(10, 42);
    sa.set(20, 84);

    SparseArray<int> moved(std::move(sa));
    EXPECT_EQ(moved.max_size(), 50);
    EXPECT_EQ(moved.size(), 2);
    EXPECT_TRUE(moved.has_index(10));
    EXPECT_TRUE(moved.has_index(20));
    EXPECT_EQ(moved.get_existing(10), 42);
    EXPECT_EQ(moved.get_existing(20), 84);
}

// --- Assignment Operator Tests ---

TEST_F(SparseArrayTest_74, CopyAssignment_74) {
    SparseArray<int> sa(50);
    sa.set(5, 55);

    SparseArray<int> other(30);
    other = sa;
    EXPECT_EQ(other.max_size(), 50);
    EXPECT_EQ(other.size(), 1);
    EXPECT_TRUE(other.has_index(5));
    EXPECT_EQ(other.get_existing(5), 55);
}

TEST_F(SparseArrayTest_74, MoveAssignment_74) {
    SparseArray<int> sa(50);
    sa.set(5, 55);

    SparseArray<int> other(30);
    other = std::move(sa);
    EXPECT_EQ(other.max_size(), 50);
    EXPECT_EQ(other.size(), 1);
    EXPECT_TRUE(other.has_index(5));
    EXPECT_EQ(other.get_existing(5), 55);
}

// --- max_size Tests ---

TEST_F(SparseArrayTest_74, MaxSizeReturnsCorrectValue_74) {
    SparseArray<int> sa(200);
    EXPECT_EQ(sa.max_size(), 200);
}

TEST_F(SparseArrayTest_74, MaxSizeDefaultIsZero_74) {
    SparseArray<int> sa;
    EXPECT_EQ(sa.max_size(), 0);
}

// --- size and empty Tests ---

TEST_F(SparseArrayTest_74, SizeInitiallyZero_74) {
    SparseArray<int> sa(10);
    EXPECT_EQ(sa.size(), 0);
}

TEST_F(SparseArrayTest_74, EmptyInitiallyTrue_74) {
    SparseArray<int> sa(10);
    EXPECT_TRUE(sa.empty());
}

TEST_F(SparseArrayTest_74, SizeAfterInsertions_74) {
    SparseArray<int> sa(10);
    sa.set(0, 1);
    EXPECT_EQ(sa.size(), 1);
    EXPECT_FALSE(sa.empty());

    sa.set(5, 2);
    EXPECT_EQ(sa.size(), 2);

    sa.set(9, 3);
    EXPECT_EQ(sa.size(), 3);
}

// --- set Tests ---

TEST_F(SparseArrayTest_74, SetAddsNewElement_74) {
    SparseArray<int> sa(10);
    sa.set(3, 42);
    EXPECT_TRUE(sa.has_index(3));
    EXPECT_EQ(sa.get_existing(3), 42);
    EXPECT_EQ(sa.size(), 1);
}

TEST_F(SparseArrayTest_74, SetOverwritesExistingElement_74) {
    SparseArray<int> sa(10);
    sa.set(3, 42);
    sa.set(3, 99);
    EXPECT_TRUE(sa.has_index(3));
    EXPECT_EQ(sa.get_existing(3), 99);
    EXPECT_EQ(sa.size(), 1);
}

TEST_F(SparseArrayTest_74, SetAtBoundaryIndices_74) {
    SparseArray<int> sa(10);
    sa.set(0, 100);
    sa.set(9, 200);
    EXPECT_TRUE(sa.has_index(0));
    EXPECT_TRUE(sa.has_index(9));
    EXPECT_EQ(sa.get_existing(0), 100);
    EXPECT_EQ(sa.get_existing(9), 200);
}

// --- set_new Tests ---

TEST_F(SparseArrayTest_74, SetNewAddsNewElement_74) {
    SparseArray<int> sa(10);
    sa.set_new(7, 77);
    EXPECT_TRUE(sa.has_index(7));
    EXPECT_EQ(sa.get_existing(7), 77);
    EXPECT_EQ(sa.size(), 1);
}

// --- set_existing Tests ---

TEST_F(SparseArrayTest_74, SetExistingUpdatesValue_74) {
    SparseArray<int> sa(10);
    sa.set(4, 10);
    sa.set_existing(4, 20);
    EXPECT_EQ(sa.get_existing(4), 20);
    EXPECT_EQ(sa.size(), 1);
}

// --- has_index Tests ---

TEST_F(SparseArrayTest_74, HasIndexReturnsFalseForMissing_74) {
    SparseArray<int> sa(10);
    EXPECT_FALSE(sa.has_index(0));
    EXPECT_FALSE(sa.has_index(5));
    EXPECT_FALSE(sa.has_index(9));
}

TEST_F(SparseArrayTest_74, HasIndexReturnsTrueAfterSet_74) {
    SparseArray<int> sa(10);
    sa.set(5, 100);
    EXPECT_TRUE(sa.has_index(5));
}

TEST_F(SparseArrayTest_74, HasIndexReturnsFalseAfterClear_74) {
    SparseArray<int> sa(10);
    sa.set(5, 100);
    sa.clear();
    EXPECT_FALSE(sa.has_index(5));
}

// --- get_existing Tests ---

TEST_F(SparseArrayTest_74, GetExistingReturnsCorrectValue_74) {
    SparseArray<int> sa(10);
    sa.set(2, 222);
    EXPECT_EQ(sa.get_existing(2), 222);
}

TEST_F(SparseArrayTest_74, GetExistingReturnsMutableReference_74) {
    SparseArray<int> sa(10);
    sa.set(2, 222);
    sa.get_existing(2) = 333;
    EXPECT_EQ(sa.get_existing(2), 333);
}

// --- clear Tests ---

TEST_F(SparseArrayTest_74, ClearResetsSize_74) {
    SparseArray<int> sa(10);
    sa.set(0, 1);
    sa.set(1, 2);
    sa.set(2, 3);
    EXPECT_EQ(sa.size(), 3);

    sa.clear();
    EXPECT_EQ(sa.size(), 0);
    EXPECT_TRUE(sa.empty());
}

TEST_F(SparseArrayTest_74, ClearDoesNotChangeMaxSize_74) {
    SparseArray<int> sa(10);
    sa.set(0, 1);
    sa.clear();
    EXPECT_EQ(sa.max_size(), 10);
}

TEST_F(SparseArrayTest_74, ClearOnEmptyArray_74) {
    SparseArray<int> sa(10);
    sa.clear();
    EXPECT_EQ(sa.size(), 0);
    EXPECT_TRUE(sa.empty());
}

// --- resize Tests ---

TEST_F(SparseArrayTest_74, ResizeIncreasesMaxSize_74) {
    SparseArray<int> sa(10);
    sa.resize(20);
    EXPECT_EQ(sa.max_size(), 20);
}

TEST_F(SparseArrayTest_74, ResizeDecreasesMaxSize_74) {
    SparseArray<int> sa(20);
    sa.resize(10);
    EXPECT_EQ(sa.max_size(), 10);
}

TEST_F(SparseArrayTest_74, ResizePreservesExistingElementsWithinRange_74) {
    SparseArray<int> sa(20);
    sa.set(5, 50);
    sa.set(15, 150);
    sa.resize(30);
    EXPECT_TRUE(sa.has_index(5));
    EXPECT_EQ(sa.get_existing(5), 50);
    EXPECT_TRUE(sa.has_index(15));
    EXPECT_EQ(sa.get_existing(15), 150);
}

TEST_F(SparseArrayTest_74, ResizeToZero_74) {
    SparseArray<int> sa(10);
    sa.set(5, 50);
    sa.resize(0);
    EXPECT_EQ(sa.max_size(), 0);
    EXPECT_EQ(sa.size(), 0);
}

// --- Iterator Tests ---

TEST_F(SparseArrayTest_74, BeginEqualsEndWhenEmpty_74) {
    SparseArray<int> sa(10);
    EXPECT_EQ(sa.begin(), sa.end());
}

TEST_F(SparseArrayTest_74, IteratorTraversal_74) {
    SparseArray<int> sa(10);
    sa.set(2, 20);
    sa.set(5, 50);
    sa.set(8, 80);

    int count = 0;
    for (auto it = sa.begin(); it != sa.end(); ++it) {
        count++;
    }
    EXPECT_EQ(count, 3);
}

TEST_F(SparseArrayTest_74, IteratorContainsCorrectValues_74) {
    SparseArray<int> sa(10);
    sa.set(3, 30);

    auto it = sa.begin();
    EXPECT_NE(it, sa.end());
    EXPECT_EQ(it->index(), 3);
    EXPECT_EQ(it->value(), 30);
}

// --- less static method Tests ---

TEST_F(SparseArrayTest_74, LessComparison_74) {
    SparseArray<int> sa(10);
    sa.set(3, 30);
    sa.set(1, 10);

    // Use less to compare two IndexValue objects
    auto it1 = sa.begin();
    auto it2 = it1 + 1;
    // We can verify that less works by checking index ordering
    bool result1 = SparseArray<int>::less(*it1, *it2);
    bool result2 = SparseArray<int>::less(*it2, *it1);
    // One should be true and the other false (they have different indices)
    EXPECT_NE(result1, result2);
}

// --- Multiple types Tests ---

TEST_F(SparseArrayTest_74, WorksWithDoubleType_74) {
    SparseArray<double> sa(10);
    sa.set(3, 3.14);
    EXPECT_TRUE(sa.has_index(3));
    EXPECT_DOUBLE_EQ(sa.get_existing(3), 3.14);
}

TEST_F(SparseArrayTest_74, WorksWithStringType_74) {
    SparseArray<std::string> sa(10);
    sa.set(5, "hello");
    EXPECT_TRUE(sa.has_index(5));
    EXPECT_EQ(sa.get_existing(5), "hello");
}

// --- Fill and clear cycle Tests ---

TEST_F(SparseArrayTest_74, FillAllIndicesAndClear_74) {
    SparseArray<int> sa(5);
    for (int i = 0; i < 5; i++) {
        sa.set(i, i * 10);
    }
    EXPECT_EQ(sa.size(), 5);

    for (int i = 0; i < 5; i++) {
        EXPECT_TRUE(sa.has_index(i));
        EXPECT_EQ(sa.get_existing(i), i * 10);
    }

    sa.clear();
    EXPECT_EQ(sa.size(), 0);
    EXPECT_TRUE(sa.empty());

    for (int i = 0; i < 5; i++) {
        EXPECT_FALSE(sa.has_index(i));
    }
}

TEST_F(SparseArrayTest_74, SetAfterClear_74) {
    SparseArray<int> sa(10);
    sa.set(3, 30);
    sa.clear();
    sa.set(3, 60);
    EXPECT_TRUE(sa.has_index(3));
    EXPECT_EQ(sa.get_existing(3), 60);
    EXPECT_EQ(sa.size(), 1);
}

// --- Large array test ---

TEST_F(SparseArrayTest_74, LargeArraySparseUsage_74) {
    SparseArray<int> sa(100000);
    sa.set(0, 1);
    sa.set(99999, 2);
    sa.set(50000, 3);

    EXPECT_EQ(sa.size(), 3);
    EXPECT_TRUE(sa.has_index(0));
    EXPECT_TRUE(sa.has_index(99999));
    EXPECT_TRUE(sa.has_index(50000));
    EXPECT_FALSE(sa.has_index(1));
    EXPECT_FALSE(sa.has_index(99998));
}

// --- set returns iterator Tests ---

TEST_F(SparseArrayTest_74, SetReturnsValidIterator_74) {
    SparseArray<int> sa(10);
    auto it = sa.set(5, 55);
    EXPECT_EQ(it->index(), 5);
    EXPECT_EQ(it->value(), 55);
}

TEST_F(SparseArrayTest_74, SetNewReturnsValidIterator_74) {
    SparseArray<int> sa(10);
    auto it = sa.set_new(7, 77);
    EXPECT_EQ(it->index(), 7);
    EXPECT_EQ(it->value(), 77);
}

TEST_F(SparseArrayTest_74, SetExistingReturnsValidIterator_74) {
    SparseArray<int> sa(10);
    sa.set(7, 77);
    auto it = sa.set_existing(7, 88);
    EXPECT_EQ(it->index(), 7);
    EXPECT_EQ(it->value(), 88);
}

// --- Resize after operations ---

TEST_F(SparseArrayTest_74, ResizeAfterMultipleOperations_74) {
    SparseArray<int> sa(5);
    sa.set(0, 10);
    sa.set(1, 20);
    sa.set(2, 30);
    sa.resize(10);

    EXPECT_EQ(sa.max_size(), 10);
    EXPECT_TRUE(sa.has_index(0));
    EXPECT_TRUE(sa.has_index(1));
    EXPECT_TRUE(sa.has_index(2));
    EXPECT_EQ(sa.size(), 3);

    // Can now set at higher indices
    sa.set(8, 80);
    EXPECT_TRUE(sa.has_index(8));
    EXPECT_EQ(sa.size(), 4);
}

}  // namespace re2
