#include "gtest/gtest.h"
#include "re2/sparse_array.h"

using re2::SparseArray;

// Test fixture for SparseArray tests
class SparseArrayTest_85 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test default constructor creates empty array
TEST_F(SparseArrayTest_85, DefaultConstructor_85) {
    SparseArray<int> sa;
    EXPECT_EQ(sa.size(), 0);
    EXPECT_TRUE(sa.empty());
}

// Test constructor with max_size
TEST_F(SparseArrayTest_85, ConstructorWithMaxSize_85) {
    SparseArray<int> sa(100);
    EXPECT_EQ(sa.size(), 0);
    EXPECT_EQ(sa.max_size(), 100);
    EXPECT_TRUE(sa.empty());
}

// Test has_index returns false on empty array
TEST_F(SparseArrayTest_85, HasIndexReturnsFalseOnEmpty_85) {
    SparseArray<int> sa(10);
    EXPECT_FALSE(sa.has_index(0));
    EXPECT_FALSE(sa.has_index(5));
    EXPECT_FALSE(sa.has_index(9));
}

// Test has_index returns true after set
TEST_F(SparseArrayTest_85, HasIndexReturnsTrueAfterSet_85) {
    SparseArray<int> sa(10);
    sa.set(3, 42);
    EXPECT_TRUE(sa.has_index(3));
}

// Test has_index returns false for unset index after some sets
TEST_F(SparseArrayTest_85, HasIndexReturnsFalseForUnsetIndex_85) {
    SparseArray<int> sa(10);
    sa.set(3, 42);
    sa.set(7, 99);
    EXPECT_FALSE(sa.has_index(0));
    EXPECT_FALSE(sa.has_index(1));
    EXPECT_FALSE(sa.has_index(5));
}

// Test set and get_existing
TEST_F(SparseArrayTest_85, SetAndGetExisting_85) {
    SparseArray<int> sa(10);
    sa.set(5, 123);
    EXPECT_TRUE(sa.has_index(5));
    EXPECT_EQ(sa.get_existing(5), 123);
}

// Test set overwrites existing value
TEST_F(SparseArrayTest_85, SetOverwritesExistingValue_85) {
    SparseArray<int> sa(10);
    sa.set(5, 123);
    sa.set(5, 456);
    EXPECT_TRUE(sa.has_index(5));
    EXPECT_EQ(sa.get_existing(5), 456);
    EXPECT_EQ(sa.size(), 1);
}

// Test set_new adds new entry
TEST_F(SparseArrayTest_85, SetNewAddsNewEntry_85) {
    SparseArray<int> sa(10);
    sa.set_new(2, 200);
    EXPECT_TRUE(sa.has_index(2));
    EXPECT_EQ(sa.get_existing(2), 200);
    EXPECT_EQ(sa.size(), 1);
}

// Test set_existing modifies existing entry
TEST_F(SparseArrayTest_85, SetExistingModifiesEntry_85) {
    SparseArray<int> sa(10);
    sa.set(4, 100);
    sa.set_existing(4, 200);
    EXPECT_EQ(sa.get_existing(4), 200);
    EXPECT_EQ(sa.size(), 1);
}

// Test size increases with new elements
TEST_F(SparseArrayTest_85, SizeIncreasesWithNewElements_85) {
    SparseArray<int> sa(10);
    EXPECT_EQ(sa.size(), 0);
    sa.set(0, 10);
    EXPECT_EQ(sa.size(), 1);
    sa.set(1, 20);
    EXPECT_EQ(sa.size(), 2);
    sa.set(5, 50);
    EXPECT_EQ(sa.size(), 3);
}

// Test size does not increase when setting existing index
TEST_F(SparseArrayTest_85, SizeDoesNotIncreaseForExistingIndex_85) {
    SparseArray<int> sa(10);
    sa.set(3, 30);
    EXPECT_EQ(sa.size(), 1);
    sa.set(3, 60);
    EXPECT_EQ(sa.size(), 1);
}

// Test clear resets the array
TEST_F(SparseArrayTest_85, ClearResetsArray_85) {
    SparseArray<int> sa(10);
    sa.set(0, 10);
    sa.set(5, 50);
    sa.set(9, 90);
    EXPECT_EQ(sa.size(), 3);
    sa.clear();
    EXPECT_EQ(sa.size(), 0);
    EXPECT_TRUE(sa.empty());
    EXPECT_FALSE(sa.has_index(0));
    EXPECT_FALSE(sa.has_index(5));
    EXPECT_FALSE(sa.has_index(9));
}

// Test empty returns correct value
TEST_F(SparseArrayTest_85, EmptyReturnsCorrectValue_85) {
    SparseArray<int> sa(10);
    EXPECT_TRUE(sa.empty());
    sa.set(0, 1);
    EXPECT_FALSE(sa.empty());
    sa.clear();
    EXPECT_TRUE(sa.empty());
}

// Test begin and end iterators
TEST_F(SparseArrayTest_85, BeginEndIterators_85) {
    SparseArray<int> sa(10);
    EXPECT_EQ(sa.begin(), sa.end());
    sa.set(3, 30);
    EXPECT_NE(sa.begin(), sa.end());
    EXPECT_EQ(sa.begin() + 1, sa.end());
}

// Test iteration over elements
TEST_F(SparseArrayTest_85, IterationOverElements_85) {
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

// Test copy constructor
TEST_F(SparseArrayTest_85, CopyConstructor_85) {
    SparseArray<int> sa(10);
    sa.set(3, 30);
    sa.set(7, 70);

    SparseArray<int> copy(sa);
    EXPECT_EQ(copy.size(), 2);
    EXPECT_EQ(copy.max_size(), 10);
    EXPECT_TRUE(copy.has_index(3));
    EXPECT_TRUE(copy.has_index(7));
    EXPECT_EQ(copy.get_existing(3), 30);
    EXPECT_EQ(copy.get_existing(7), 70);
}

// Test copy assignment
TEST_F(SparseArrayTest_85, CopyAssignment_85) {
    SparseArray<int> sa(10);
    sa.set(1, 10);
    sa.set(4, 40);

    SparseArray<int> other(5);
    other = sa;
    EXPECT_EQ(other.size(), 2);
    EXPECT_EQ(other.max_size(), 10);
    EXPECT_TRUE(other.has_index(1));
    EXPECT_TRUE(other.has_index(4));
    EXPECT_EQ(other.get_existing(1), 10);
    EXPECT_EQ(other.get_existing(4), 40);
}

// Test move constructor
TEST_F(SparseArrayTest_85, MoveConstructor_85) {
    SparseArray<int> sa(10);
    sa.set(2, 20);
    sa.set(6, 60);

    SparseArray<int> moved(std::move(sa));
    EXPECT_EQ(moved.size(), 2);
    EXPECT_TRUE(moved.has_index(2));
    EXPECT_TRUE(moved.has_index(6));
    EXPECT_EQ(moved.get_existing(2), 20);
    EXPECT_EQ(moved.get_existing(6), 60);
}

// Test move assignment
TEST_F(SparseArrayTest_85, MoveAssignment_85) {
    SparseArray<int> sa(10);
    sa.set(0, 100);
    sa.set(9, 900);

    SparseArray<int> other(5);
    other = std::move(sa);
    EXPECT_EQ(other.size(), 2);
    EXPECT_TRUE(other.has_index(0));
    EXPECT_TRUE(other.has_index(9));
    EXPECT_EQ(other.get_existing(0), 100);
    EXPECT_EQ(other.get_existing(9), 900);
}

// Test resize to larger size preserves elements
TEST_F(SparseArrayTest_85, ResizeToLargerPreservesElements_85) {
    SparseArray<int> sa(10);
    sa.set(3, 30);
    sa.set(7, 70);

    sa.resize(20);
    EXPECT_EQ(sa.max_size(), 20);
    EXPECT_EQ(sa.size(), 2);
    EXPECT_TRUE(sa.has_index(3));
    EXPECT_TRUE(sa.has_index(7));
    EXPECT_EQ(sa.get_existing(3), 30);
    EXPECT_EQ(sa.get_existing(7), 70);
}

// Test resize allows using new indices
TEST_F(SparseArrayTest_85, ResizeAllowsNewIndices_85) {
    SparseArray<int> sa(5);
    sa.set(2, 20);
    sa.resize(15);
    sa.set(10, 100);
    EXPECT_TRUE(sa.has_index(10));
    EXPECT_EQ(sa.get_existing(10), 100);
}

// Test boundary: index 0
TEST_F(SparseArrayTest_85, BoundaryIndexZero_85) {
    SparseArray<int> sa(5);
    sa.set(0, 999);
    EXPECT_TRUE(sa.has_index(0));
    EXPECT_EQ(sa.get_existing(0), 999);
}

// Test boundary: last valid index
TEST_F(SparseArrayTest_85, BoundaryLastValidIndex_85) {
    SparseArray<int> sa(5);
    sa.set(4, 444);
    EXPECT_TRUE(sa.has_index(4));
    EXPECT_EQ(sa.get_existing(4), 444);
}

// Test max_size returns correct value
TEST_F(SparseArrayTest_85, MaxSizeReturnsCorrectValue_85) {
    SparseArray<int> sa(42);
    EXPECT_EQ(sa.max_size(), 42);
}

// Test less static function
TEST_F(SparseArrayTest_85, LessFunction_85) {
    SparseArray<int> sa(10);
    sa.set(5, 50);
    sa.set(2, 20);

    // Access elements through iterators to test less
    auto it1 = sa.begin();
    auto it2 = sa.begin() + 1;
    
    // less compares by index
    bool result1 = SparseArray<int>::less(*it1, *it2);
    bool result2 = SparseArray<int>::less(*it2, *it1);
    // One should be true and the other false (they can't be equal since different indices)
    EXPECT_NE(result1, result2);
}

// Test with string values
TEST_F(SparseArrayTest_85, StringValues_85) {
    SparseArray<std::string> sa(10);
    sa.set(3, "hello");
    sa.set(7, "world");
    EXPECT_TRUE(sa.has_index(3));
    EXPECT_TRUE(sa.has_index(7));
    EXPECT_EQ(sa.get_existing(3), "hello");
    EXPECT_EQ(sa.get_existing(7), "world");
}

// Test multiple sets and clears
TEST_F(SparseArrayTest_85, MultipleSetAndClearCycles_85) {
    SparseArray<int> sa(10);
    for (int cycle = 0; cycle < 3; cycle++) {
        for (int i = 0; i < 10; i++) {
            sa.set(i, i * 10 + cycle);
        }
        EXPECT_EQ(sa.size(), 10);
        for (int i = 0; i < 10; i++) {
            EXPECT_TRUE(sa.has_index(i));
            EXPECT_EQ(sa.get_existing(i), i * 10 + cycle);
        }
        sa.clear();
        EXPECT_EQ(sa.size(), 0);
        for (int i = 0; i < 10; i++) {
            EXPECT_FALSE(sa.has_index(i));
        }
    }
}

// Test filling array to max capacity
TEST_F(SparseArrayTest_85, FillToMaxCapacity_85) {
    const int max = 100;
    SparseArray<int> sa(max);
    for (int i = 0; i < max; i++) {
        sa.set(i, i * 2);
    }
    EXPECT_EQ(sa.size(), max);
    for (int i = 0; i < max; i++) {
        EXPECT_TRUE(sa.has_index(i));
        EXPECT_EQ(sa.get_existing(i), i * 2);
    }
}

// Test copy is independent from original
TEST_F(SparseArrayTest_85, CopyIsIndependent_85) {
    SparseArray<int> sa(10);
    sa.set(3, 30);

    SparseArray<int> copy(sa);
    sa.set(3, 999);
    sa.set(5, 50);

    EXPECT_EQ(copy.get_existing(3), 30);
    EXPECT_FALSE(copy.has_index(5));
    EXPECT_EQ(copy.size(), 1);
}

// Test set returns iterator pointing to set element
TEST_F(SparseArrayTest_85, SetReturnsValidIterator_85) {
    SparseArray<int> sa(10);
    auto it = sa.set(4, 40);
    EXPECT_EQ(it->index_, 4);
    EXPECT_EQ(it->value_, 40);
}

// Test set_new returns valid iterator
TEST_F(SparseArrayTest_85, SetNewReturnsValidIterator_85) {
    SparseArray<int> sa(10);
    auto it = sa.set_new(7, 70);
    EXPECT_EQ(it->index_, 7);
    EXPECT_EQ(it->value_, 70);
}

// Test set_existing returns valid iterator
TEST_F(SparseArrayTest_85, SetExistingReturnsValidIterator_85) {
    SparseArray<int> sa(10);
    sa.set(2, 20);
    auto it = sa.set_existing(2, 200);
    EXPECT_EQ(it->index_, 2);
    EXPECT_EQ(it->value_, 200);
}

// Test with max_size of 1
TEST_F(SparseArrayTest_85, MaxSizeOne_85) {
    SparseArray<int> sa(1);
    EXPECT_EQ(sa.max_size(), 1);
    EXPECT_FALSE(sa.has_index(0));
    sa.set(0, 42);
    EXPECT_TRUE(sa.has_index(0));
    EXPECT_EQ(sa.get_existing(0), 42);
    EXPECT_EQ(sa.size(), 1);
}

// Test clear on already empty array
TEST_F(SparseArrayTest_85, ClearOnEmptyArray_85) {
    SparseArray<int> sa(10);
    sa.clear();
    EXPECT_EQ(sa.size(), 0);
    EXPECT_TRUE(sa.empty());
}

// Test resize to same size
TEST_F(SparseArrayTest_85, ResizeToSameSize_85) {
    SparseArray<int> sa(10);
    sa.set(3, 30);
    sa.resize(10);
    EXPECT_EQ(sa.max_size(), 10);
    EXPECT_TRUE(sa.has_index(3));
    EXPECT_EQ(sa.get_existing(3), 30);
}
