#include "re2/sparse_array.h"
#include <gtest/gtest.h>
#include <algorithm>
#include <vector>

namespace re2 {

// Test fixture for SparseArray tests
class SparseArrayTest_86 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// --- Construction Tests ---

TEST_F(SparseArrayTest_86, DefaultConstructor_86) {
    SparseArray<int> sa;
    EXPECT_EQ(sa.size(), 0);
    EXPECT_TRUE(sa.empty());
}

TEST_F(SparseArrayTest_86, ConstructorWithMaxSize_86) {
    SparseArray<int> sa(100);
    EXPECT_EQ(sa.size(), 0);
    EXPECT_TRUE(sa.empty());
    EXPECT_EQ(sa.max_size(), 100);
}

TEST_F(SparseArrayTest_86, CopyConstructor_86) {
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

TEST_F(SparseArrayTest_86, MoveConstructor_86) {
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

// --- Assignment Tests ---

TEST_F(SparseArrayTest_86, CopyAssignment_86) {
    SparseArray<int> sa(10);
    sa.set(5, 50);

    SparseArray<int> other(20);
    other.set(1, 10);
    other = sa;

    EXPECT_EQ(other.size(), 1);
    EXPECT_TRUE(other.has_index(5));
    EXPECT_EQ(other.get_existing(5), 50);
}

TEST_F(SparseArrayTest_86, MoveAssignment_86) {
    SparseArray<int> sa(10);
    sa.set(5, 50);

    SparseArray<int> other(20);
    other = std::move(sa);

    EXPECT_EQ(other.size(), 1);
    EXPECT_TRUE(other.has_index(5));
    EXPECT_EQ(other.get_existing(5), 50);
}

// --- Basic Operations ---

TEST_F(SparseArrayTest_86, SetAndGet_86) {
    SparseArray<int> sa(10);
    sa.set(0, 100);
    EXPECT_EQ(sa.size(), 1);
    EXPECT_TRUE(sa.has_index(0));
    EXPECT_EQ(sa.get_existing(0), 100);
}

TEST_F(SparseArrayTest_86, SetMultipleElements_86) {
    SparseArray<int> sa(10);
    sa.set(1, 10);
    sa.set(3, 30);
    sa.set(5, 50);
    sa.set(9, 90);

    EXPECT_EQ(sa.size(), 4);
    EXPECT_EQ(sa.get_existing(1), 10);
    EXPECT_EQ(sa.get_existing(3), 30);
    EXPECT_EQ(sa.get_existing(5), 50);
    EXPECT_EQ(sa.get_existing(9), 90);
}

TEST_F(SparseArrayTest_86, SetOverwritesExistingValue_86) {
    SparseArray<int> sa(10);
    sa.set(3, 30);
    EXPECT_EQ(sa.get_existing(3), 30);

    sa.set(3, 300);
    EXPECT_EQ(sa.size(), 1);
    EXPECT_EQ(sa.get_existing(3), 300);
}

TEST_F(SparseArrayTest_86, SetNew_86) {
    SparseArray<int> sa(10);
    sa.set_new(4, 40);
    EXPECT_EQ(sa.size(), 1);
    EXPECT_TRUE(sa.has_index(4));
    EXPECT_EQ(sa.get_existing(4), 40);
}

TEST_F(SparseArrayTest_86, SetExisting_86) {
    SparseArray<int> sa(10);
    sa.set(4, 40);
    sa.set_existing(4, 400);
    EXPECT_EQ(sa.size(), 1);
    EXPECT_EQ(sa.get_existing(4), 400);
}

// --- has_index Tests ---

TEST_F(SparseArrayTest_86, HasIndexReturnsFalseForUnsetIndex_86) {
    SparseArray<int> sa(10);
    EXPECT_FALSE(sa.has_index(0));
    EXPECT_FALSE(sa.has_index(5));
    EXPECT_FALSE(sa.has_index(9));
}

TEST_F(SparseArrayTest_86, HasIndexReturnsTrueForSetIndex_86) {
    SparseArray<int> sa(10);
    sa.set(5, 50);
    EXPECT_TRUE(sa.has_index(5));
}

// --- Size and Empty Tests ---

TEST_F(SparseArrayTest_86, SizeIncreasesWithNewElements_86) {
    SparseArray<int> sa(10);
    EXPECT_EQ(sa.size(), 0);
    sa.set(0, 0);
    EXPECT_EQ(sa.size(), 1);
    sa.set(1, 1);
    EXPECT_EQ(sa.size(), 2);
    sa.set(2, 2);
    EXPECT_EQ(sa.size(), 3);
}

TEST_F(SparseArrayTest_86, SizeDoesNotChangeOnOverwrite_86) {
    SparseArray<int> sa(10);
    sa.set(0, 0);
    sa.set(1, 1);
    EXPECT_EQ(sa.size(), 2);
    sa.set(0, 100);
    EXPECT_EQ(sa.size(), 2);
}

TEST_F(SparseArrayTest_86, EmptyWhenNoElements_86) {
    SparseArray<int> sa(10);
    EXPECT_TRUE(sa.empty());
}

TEST_F(SparseArrayTest_86, NotEmptyAfterSet_86) {
    SparseArray<int> sa(10);
    sa.set(0, 0);
    EXPECT_FALSE(sa.empty());
}

// --- Clear Tests ---

TEST_F(SparseArrayTest_86, ClearRemovesAllElements_86) {
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

TEST_F(SparseArrayTest_86, ClearOnEmptyArray_86) {
    SparseArray<int> sa(10);
    sa.clear();
    EXPECT_EQ(sa.size(), 0);
    EXPECT_TRUE(sa.empty());
}

TEST_F(SparseArrayTest_86, SetAfterClear_86) {
    SparseArray<int> sa(10);
    sa.set(1, 10);
    sa.clear();
    sa.set(1, 20);
    EXPECT_EQ(sa.size(), 1);
    EXPECT_EQ(sa.get_existing(1), 20);
}

// --- Iterator Tests ---

TEST_F(SparseArrayTest_86, BeginEqualsEndWhenEmpty_86) {
    SparseArray<int> sa(10);
    EXPECT_EQ(sa.begin(), sa.end());
}

TEST_F(SparseArrayTest_86, IteratorCoversAllElements_86) {
    SparseArray<int> sa(10);
    sa.set(2, 20);
    sa.set(5, 50);
    sa.set(8, 80);

    int count = 0;
    std::vector<int> indices;
    std::vector<int> values;
    for (auto it = sa.begin(); it != sa.end(); ++it) {
        indices.push_back(it->index());
        values.push_back(it->value());
        count++;
    }
    EXPECT_EQ(count, 3);

    // Check that all set indices and values are found
    std::sort(indices.begin(), indices.end());
    EXPECT_EQ(indices[0], 2);
    EXPECT_EQ(indices[1], 5);
    EXPECT_EQ(indices[2], 8);
}

// --- Resize Tests ---

TEST_F(SparseArrayTest_86, ResizeIncreasesMaxSize_86) {
    SparseArray<int> sa(5);
    EXPECT_EQ(sa.max_size(), 5);
    sa.resize(20);
    EXPECT_EQ(sa.max_size(), 20);
}

TEST_F(SparseArrayTest_86, ResizePreservesExistingElements_86) {
    SparseArray<int> sa(10);
    sa.set(3, 30);
    sa.set(7, 70);
    sa.resize(20);

    EXPECT_EQ(sa.size(), 2);
    EXPECT_TRUE(sa.has_index(3));
    EXPECT_TRUE(sa.has_index(7));
    EXPECT_EQ(sa.get_existing(3), 30);
    EXPECT_EQ(sa.get_existing(7), 70);
}

TEST_F(SparseArrayTest_86, ResizeAllowsSettingNewIndices_86) {
    SparseArray<int> sa(5);
    sa.resize(20);
    sa.set(15, 150);
    EXPECT_TRUE(sa.has_index(15));
    EXPECT_EQ(sa.get_existing(15), 150);
}

// --- Boundary Conditions ---

TEST_F(SparseArrayTest_86, SetAtIndexZero_86) {
    SparseArray<int> sa(10);
    sa.set(0, 0);
    EXPECT_TRUE(sa.has_index(0));
    EXPECT_EQ(sa.get_existing(0), 0);
}

TEST_F(SparseArrayTest_86, SetAtMaxIndex_86) {
    SparseArray<int> sa(10);
    sa.set(9, 90);
    EXPECT_TRUE(sa.has_index(9));
    EXPECT_EQ(sa.get_existing(9), 90);
}

TEST_F(SparseArrayTest_86, MaxSizeOfOne_86) {
    SparseArray<int> sa(1);
    EXPECT_EQ(sa.max_size(), 1);
    sa.set(0, 42);
    EXPECT_EQ(sa.size(), 1);
    EXPECT_EQ(sa.get_existing(0), 42);
}

TEST_F(SparseArrayTest_86, FillEntireArray_86) {
    const int max_size = 20;
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

// --- less() static function test ---

TEST_F(SparseArrayTest_86, LessComparesByIndex_86) {
    SparseArray<int> sa(10);
    sa.set(5, 50);
    sa.set(2, 20);
    sa.set(8, 80);

    // Gather elements and sort using the less function
    std::vector<SparseArray<int>::IndexValue> elems(sa.begin(), sa.end());
    std::sort(elems.begin(), elems.end(), SparseArray<int>::less);

    ASSERT_EQ(elems.size(), 3u);
    EXPECT_EQ(elems[0].index(), 2);
    EXPECT_EQ(elems[1].index(), 5);
    EXPECT_EQ(elems[2].index(), 8);
}

// --- Different Value Types ---

TEST_F(SparseArrayTest_86, StringValues_86) {
    SparseArray<std::string> sa(10);
    sa.set(0, "hello");
    sa.set(5, "world");

    EXPECT_EQ(sa.size(), 2);
    EXPECT_EQ(sa.get_existing(0), "hello");
    EXPECT_EQ(sa.get_existing(5), "world");
}

TEST_F(SparseArrayTest_86, DoubleValues_86) {
    SparseArray<double> sa(10);
    sa.set(3, 3.14);
    sa.set(7, 2.718);

    EXPECT_DOUBLE_EQ(sa.get_existing(3), 3.14);
    EXPECT_DOUBLE_EQ(sa.get_existing(7), 2.718);
}

// --- Repeated Operations ---

TEST_F(SparseArrayTest_86, RepeatedClearAndSet_86) {
    SparseArray<int> sa(10);
    for (int round = 0; round < 5; round++) {
        for (int i = 0; i < 10; i++) {
            sa.set(i, round * 10 + i);
        }
        EXPECT_EQ(sa.size(), 10);
        sa.clear();
        EXPECT_EQ(sa.size(), 0);
    }
}

TEST_F(SparseArrayTest_86, SetReturnsIterator_86) {
    SparseArray<int> sa(10);
    auto it = sa.set(3, 30);
    EXPECT_EQ(it->index(), 3);
    EXPECT_EQ(it->value(), 30);
}

TEST_F(SparseArrayTest_86, SetNewReturnsIterator_86) {
    SparseArray<int> sa(10);
    auto it = sa.set_new(7, 70);
    EXPECT_EQ(it->index(), 7);
    EXPECT_EQ(it->value(), 70);
}

TEST_F(SparseArrayTest_86, SetExistingReturnsIterator_86) {
    SparseArray<int> sa(10);
    sa.set(4, 40);
    auto it = sa.set_existing(4, 400);
    EXPECT_EQ(it->index(), 4);
    EXPECT_EQ(it->value(), 400);
}

TEST_F(SparseArrayTest_86, GetExistingReturnsReference_86) {
    SparseArray<int> sa(10);
    sa.set(3, 30);
    int& ref = sa.get_existing(3);
    ref = 300;
    EXPECT_EQ(sa.get_existing(3), 300);
}

}  // namespace re2
