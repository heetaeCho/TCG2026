#include "re2/sparse_array.h"
#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <algorithm>

namespace re2 {

// Test fixture
class SparseArrayTest_70 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// --- Construction Tests ---

TEST_F(SparseArrayTest_70, DefaultConstructor_70) {
    SparseArray<int> sa;
    EXPECT_EQ(sa.size(), 0);
    EXPECT_TRUE(sa.empty());
}

TEST_F(SparseArrayTest_70, ConstructorWithMaxSize_70) {
    SparseArray<int> sa(100);
    EXPECT_EQ(sa.size(), 0);
    EXPECT_EQ(sa.max_size(), 100);
    EXPECT_TRUE(sa.empty());
}

TEST_F(SparseArrayTest_70, CopyConstructor_70) {
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

TEST_F(SparseArrayTest_70, MoveConstructor_70) {
    SparseArray<int> sa(10);
    sa.set(5, 50);

    SparseArray<int> moved(std::move(sa));
    EXPECT_EQ(moved.size(), 1);
    EXPECT_TRUE(moved.has_index(5));
    EXPECT_EQ(moved.get_existing(5), 50);
}

// --- Assignment Tests ---

TEST_F(SparseArrayTest_70, CopyAssignment_70) {
    SparseArray<int> sa(10);
    sa.set(2, 20);
    sa.set(4, 40);

    SparseArray<int> other(5);
    other = sa;

    EXPECT_EQ(other.size(), 2);
    EXPECT_TRUE(other.has_index(2));
    EXPECT_TRUE(other.has_index(4));
    EXPECT_EQ(other.get_existing(2), 20);
    EXPECT_EQ(other.get_existing(4), 40);
}

TEST_F(SparseArrayTest_70, MoveAssignment_70) {
    SparseArray<int> sa(10);
    sa.set(1, 10);

    SparseArray<int> other(5);
    other = std::move(sa);

    EXPECT_EQ(other.size(), 1);
    EXPECT_TRUE(other.has_index(1));
    EXPECT_EQ(other.get_existing(1), 10);
}

// --- Size and Empty Tests ---

TEST_F(SparseArrayTest_70, SizeAfterInsertions_70) {
    SparseArray<int> sa(10);
    EXPECT_EQ(sa.size(), 0);
    sa.set(0, 100);
    EXPECT_EQ(sa.size(), 1);
    sa.set(5, 500);
    EXPECT_EQ(sa.size(), 2);
    sa.set(9, 900);
    EXPECT_EQ(sa.size(), 3);
}

TEST_F(SparseArrayTest_70, EmptyReturnsTrueWhenEmpty_70) {
    SparseArray<int> sa(10);
    EXPECT_TRUE(sa.empty());
}

TEST_F(SparseArrayTest_70, EmptyReturnsFalseWhenNotEmpty_70) {
    SparseArray<int> sa(10);
    sa.set(0, 42);
    EXPECT_FALSE(sa.empty());
}

// --- MaxSize Tests ---

TEST_F(SparseArrayTest_70, MaxSizeReturnsCorrectValue_70) {
    SparseArray<int> sa(50);
    EXPECT_EQ(sa.max_size(), 50);
}

// --- Set and HasIndex Tests ---

TEST_F(SparseArrayTest_70, SetAndHasIndex_70) {
    SparseArray<int> sa(10);
    EXPECT_FALSE(sa.has_index(3));
    sa.set(3, 30);
    EXPECT_TRUE(sa.has_index(3));
}

TEST_F(SparseArrayTest_70, SetOverwritesExistingValue_70) {
    SparseArray<int> sa(10);
    sa.set(3, 30);
    EXPECT_EQ(sa.get_existing(3), 30);
    sa.set(3, 300);
    EXPECT_EQ(sa.get_existing(3), 300);
    EXPECT_EQ(sa.size(), 1);  // Size should not increase
}

TEST_F(SparseArrayTest_70, SetNewAddsNewEntry_70) {
    SparseArray<int> sa(10);
    sa.set_new(5, 50);
    EXPECT_TRUE(sa.has_index(5));
    EXPECT_EQ(sa.get_existing(5), 50);
    EXPECT_EQ(sa.size(), 1);
}

TEST_F(SparseArrayTest_70, SetExistingUpdatesValue_70) {
    SparseArray<int> sa(10);
    sa.set(3, 30);
    sa.set_existing(3, 300);
    EXPECT_EQ(sa.get_existing(3), 300);
    EXPECT_EQ(sa.size(), 1);
}

// --- GetExisting Tests ---

TEST_F(SparseArrayTest_70, GetExistingReturnsCorrectValue_70) {
    SparseArray<int> sa(10);
    sa.set(7, 77);
    EXPECT_EQ(sa.get_existing(7), 77);
}

TEST_F(SparseArrayTest_70, GetExistingReturnsMutableReference_70) {
    SparseArray<int> sa(10);
    sa.set(4, 40);
    sa.get_existing(4) = 400;
    EXPECT_EQ(sa.get_existing(4), 400);
}

// --- Clear Tests ---

TEST_F(SparseArrayTest_70, ClearRemovesAllEntries_70) {
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

TEST_F(SparseArrayTest_70, ClearOnEmptyArray_70) {
    SparseArray<int> sa(10);
    sa.clear();
    EXPECT_EQ(sa.size(), 0);
    EXPECT_TRUE(sa.empty());
}

// --- Resize Tests ---

TEST_F(SparseArrayTest_70, ResizeIncreasesMaxSize_70) {
    SparseArray<int> sa(5);
    sa.set(2, 20);
    sa.resize(20);
    EXPECT_EQ(sa.max_size(), 20);
    // Existing entries should be cleared after resize
}

TEST_F(SparseArrayTest_70, ResizeDecreasesMaxSize_70) {
    SparseArray<int> sa(20);
    sa.resize(5);
    EXPECT_EQ(sa.max_size(), 5);
}

// --- Iterator Tests ---

TEST_F(SparseArrayTest_70, BeginEndOnEmptyArray_70) {
    SparseArray<int> sa(10);
    EXPECT_EQ(sa.begin(), sa.end());
}

TEST_F(SparseArrayTest_70, IteratorTraversesAllElements_70) {
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

TEST_F(SparseArrayTest_70, IteratorContainsCorrectIndicesAndValues_70) {
    SparseArray<int> sa(10);
    sa.set(2, 20);
    sa.set(7, 70);

    std::vector<std::pair<int, int>> entries;
    for (auto it = sa.begin(); it != sa.end(); ++it) {
        entries.push_back({it->index(), it->value()});
    }

    EXPECT_EQ(entries.size(), 2u);
    // Check that both entries exist (order may vary)
    bool found2 = false, found7 = false;
    for (const auto& e : entries) {
        if (e.first == 2 && e.second == 20) found2 = true;
        if (e.first == 7 && e.second == 70) found7 = true;
    }
    EXPECT_TRUE(found2);
    EXPECT_TRUE(found7);
}

// --- HasIndex Boundary Tests ---

TEST_F(SparseArrayTest_70, HasIndexAtZero_70) {
    SparseArray<int> sa(10);
    sa.set(0, 0);
    EXPECT_TRUE(sa.has_index(0));
}

TEST_F(SparseArrayTest_70, HasIndexAtMaxSizeMinusOne_70) {
    SparseArray<int> sa(10);
    sa.set(9, 90);
    EXPECT_TRUE(sa.has_index(9));
}

TEST_F(SparseArrayTest_70, HasIndexReturnsFalseForUnsetIndex_70) {
    SparseArray<int> sa(10);
    sa.set(3, 30);
    EXPECT_FALSE(sa.has_index(4));
    EXPECT_FALSE(sa.has_index(0));
    EXPECT_FALSE(sa.has_index(9));
}

// --- Less Function Tests ---

TEST_F(SparseArrayTest_70, LessComparesCorrectly_70) {
    // We need to create IndexValues to test this
    SparseArray<int> sa(10);
    sa.set(3, 30);
    sa.set(1, 10);

    // We can verify less through sorting
    auto begin = sa.begin();
    auto end = sa.end();
    std::sort(begin, end, SparseArray<int>::less);

    // After sort, indices should be in ascending order
    EXPECT_LT(sa.begin()->index(), (sa.begin() + 1)->index());
}

// --- Multiple Operations Tests ---

TEST_F(SparseArrayTest_70, SetThenClearThenSetAgain_70) {
    SparseArray<int> sa(10);
    sa.set(5, 50);
    EXPECT_EQ(sa.size(), 1);

    sa.clear();
    EXPECT_EQ(sa.size(), 0);
    EXPECT_FALSE(sa.has_index(5));

    sa.set(5, 500);
    EXPECT_EQ(sa.size(), 1);
    EXPECT_TRUE(sa.has_index(5));
    EXPECT_EQ(sa.get_existing(5), 500);
}

TEST_F(SparseArrayTest_70, FillEntireArray_70) {
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

// --- String Value Tests ---

TEST_F(SparseArrayTest_70, WorksWithStringValues_70) {
    SparseArray<std::string> sa(10);
    sa.set(0, "hello");
    sa.set(5, "world");

    EXPECT_EQ(sa.size(), 2);
    EXPECT_TRUE(sa.has_index(0));
    EXPECT_TRUE(sa.has_index(5));
    EXPECT_EQ(sa.get_existing(0), "hello");
    EXPECT_EQ(sa.get_existing(5), "world");
}

// --- Set Returns Iterator Tests ---

TEST_F(SparseArrayTest_70, SetReturnsValidIterator_70) {
    SparseArray<int> sa(10);
    auto it = sa.set(3, 30);
    EXPECT_EQ(it->index(), 3);
    EXPECT_EQ(it->value(), 30);
}

TEST_F(SparseArrayTest_70, SetNewReturnsValidIterator_70) {
    SparseArray<int> sa(10);
    auto it = sa.set_new(7, 70);
    EXPECT_EQ(it->index(), 7);
    EXPECT_EQ(it->value(), 70);
}

TEST_F(SparseArrayTest_70, SetExistingReturnsValidIterator_70) {
    SparseArray<int> sa(10);
    sa.set(4, 40);
    auto it = sa.set_existing(4, 400);
    EXPECT_EQ(it->index(), 4);
    EXPECT_EQ(it->value(), 400);
}

// --- MaxSize of 1 Boundary ---

TEST_F(SparseArrayTest_70, MaxSizeOne_70) {
    SparseArray<int> sa(1);
    EXPECT_EQ(sa.max_size(), 1);
    EXPECT_EQ(sa.size(), 0);

    sa.set(0, 42);
    EXPECT_EQ(sa.size(), 1);
    EXPECT_TRUE(sa.has_index(0));
    EXPECT_EQ(sa.get_existing(0), 42);

    sa.clear();
    EXPECT_EQ(sa.size(), 0);
    EXPECT_FALSE(sa.has_index(0));
}

// --- Copy preserves independence ---

TEST_F(SparseArrayTest_70, CopyIsIndependent_70) {
    SparseArray<int> sa(10);
    sa.set(3, 30);

    SparseArray<int> copy(sa);
    copy.set(3, 300);

    // Original should be unchanged
    EXPECT_EQ(sa.get_existing(3), 30);
    EXPECT_EQ(copy.get_existing(3), 300);
}

TEST_F(SparseArrayTest_70, CopyAssignmentIsIndependent_70) {
    SparseArray<int> sa(10);
    sa.set(5, 50);

    SparseArray<int> other(10);
    other = sa;
    other.set(5, 500);
    other.set(7, 700);

    EXPECT_EQ(sa.size(), 1);
    EXPECT_EQ(sa.get_existing(5), 50);
    EXPECT_FALSE(sa.has_index(7));
}

}  // namespace re2
