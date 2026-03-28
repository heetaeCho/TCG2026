#include "re2/sparse_array.h"
#include <gtest/gtest.h>
#include <vector>
#include <algorithm>

namespace re2 {

// Test fixture for SparseArray tests
class SparseArrayTest_71 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// --- Constructor Tests ---

TEST_F(SparseArrayTest_71, DefaultConstructor_71) {
    SparseArray<int> sa;
    EXPECT_TRUE(sa.empty());
    EXPECT_EQ(sa.size(), 0);
}

TEST_F(SparseArrayTest_71, ConstructorWithMaxSize_71) {
    SparseArray<int> sa(100);
    EXPECT_TRUE(sa.empty());
    EXPECT_EQ(sa.size(), 0);
    EXPECT_EQ(sa.max_size(), 100);
}

TEST_F(SparseArrayTest_71, CopyConstructor_71) {
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

TEST_F(SparseArrayTest_71, MoveConstructor_71) {
    SparseArray<int> sa(10);
    sa.set(5, 50);
    sa.set(9, 90);

    SparseArray<int> moved(std::move(sa));
    EXPECT_EQ(moved.size(), 2);
    EXPECT_TRUE(moved.has_index(5));
    EXPECT_TRUE(moved.has_index(9));
    EXPECT_EQ(moved.get_existing(5), 50);
    EXPECT_EQ(moved.get_existing(9), 90);
}

// --- Assignment Operator Tests ---

TEST_F(SparseArrayTest_71, CopyAssignment_71) {
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

TEST_F(SparseArrayTest_71, MoveAssignment_71) {
    SparseArray<int> sa(10);
    sa.set(1, 10);
    sa.set(8, 80);

    SparseArray<int> other(5);
    other = std::move(sa);
    EXPECT_EQ(other.size(), 2);
    EXPECT_TRUE(other.has_index(1));
    EXPECT_TRUE(other.has_index(8));
    EXPECT_EQ(other.get_existing(1), 10);
    EXPECT_EQ(other.get_existing(8), 80);
}

// --- Empty and Size Tests ---

TEST_F(SparseArrayTest_71, EmptyOnNewArray_71) {
    SparseArray<int> sa(10);
    EXPECT_TRUE(sa.empty());
    EXPECT_EQ(sa.size(), 0);
}

TEST_F(SparseArrayTest_71, NotEmptyAfterSet_71) {
    SparseArray<int> sa(10);
    sa.set(0, 100);
    EXPECT_FALSE(sa.empty());
    EXPECT_EQ(sa.size(), 1);
}

TEST_F(SparseArrayTest_71, EmptyAfterClear_71) {
    SparseArray<int> sa(10);
    sa.set(0, 100);
    sa.set(5, 500);
    sa.clear();
    EXPECT_TRUE(sa.empty());
    EXPECT_EQ(sa.size(), 0);
}

// --- Set and Get Tests ---

TEST_F(SparseArrayTest_71, SetAndGetExisting_71) {
    SparseArray<int> sa(10);
    sa.set(3, 30);
    EXPECT_TRUE(sa.has_index(3));
    EXPECT_EQ(sa.get_existing(3), 30);
}

TEST_F(SparseArrayTest_71, SetOverwritesExistingValue_71) {
    SparseArray<int> sa(10);
    sa.set(3, 30);
    sa.set(3, 300);
    EXPECT_EQ(sa.size(), 1);
    EXPECT_EQ(sa.get_existing(3), 300);
}

TEST_F(SparseArrayTest_71, SetNewAddsNewEntry_71) {
    SparseArray<int> sa(10);
    sa.set_new(5, 50);
    EXPECT_TRUE(sa.has_index(5));
    EXPECT_EQ(sa.get_existing(5), 50);
    EXPECT_EQ(sa.size(), 1);
}

TEST_F(SparseArrayTest_71, SetExistingUpdatesValue_71) {
    SparseArray<int> sa(10);
    sa.set(7, 70);
    sa.set_existing(7, 700);
    EXPECT_EQ(sa.get_existing(7), 700);
    EXPECT_EQ(sa.size(), 1);
}

TEST_F(SparseArrayTest_71, SetMultipleValues_71) {
    SparseArray<int> sa(10);
    for (int i = 0; i < 10; ++i) {
        sa.set(i, i * 10);
    }
    EXPECT_EQ(sa.size(), 10);
    for (int i = 0; i < 10; ++i) {
        EXPECT_TRUE(sa.has_index(i));
        EXPECT_EQ(sa.get_existing(i), i * 10);
    }
}

// --- has_index Tests ---

TEST_F(SparseArrayTest_71, HasIndexReturnsFalseForUnsetIndex_71) {
    SparseArray<int> sa(10);
    EXPECT_FALSE(sa.has_index(0));
    EXPECT_FALSE(sa.has_index(5));
    EXPECT_FALSE(sa.has_index(9));
}

TEST_F(SparseArrayTest_71, HasIndexReturnsTrueForSetIndex_71) {
    SparseArray<int> sa(10);
    sa.set(5, 50);
    EXPECT_TRUE(sa.has_index(5));
}

TEST_F(SparseArrayTest_71, HasIndexReturnsFalseAfterClear_71) {
    SparseArray<int> sa(10);
    sa.set(5, 50);
    sa.clear();
    EXPECT_FALSE(sa.has_index(5));
}

// --- Clear Tests ---

TEST_F(SparseArrayTest_71, ClearResetsSize_71) {
    SparseArray<int> sa(10);
    sa.set(0, 1);
    sa.set(1, 2);
    sa.set(2, 3);
    EXPECT_EQ(sa.size(), 3);
    sa.clear();
    EXPECT_EQ(sa.size(), 0);
    EXPECT_TRUE(sa.empty());
}

TEST_F(SparseArrayTest_71, ClearOnEmptyArray_71) {
    SparseArray<int> sa(10);
    sa.clear();
    EXPECT_TRUE(sa.empty());
    EXPECT_EQ(sa.size(), 0);
}

// --- max_size Tests ---

TEST_F(SparseArrayTest_71, MaxSizeReturnsCorrectValue_71) {
    SparseArray<int> sa(42);
    EXPECT_EQ(sa.max_size(), 42);
}

// --- Resize Tests ---

TEST_F(SparseArrayTest_71, ResizeIncreasesMaxSize_71) {
    SparseArray<int> sa(10);
    sa.set(3, 30);
    sa.resize(20);
    EXPECT_EQ(sa.max_size(), 20);
    // Existing data should still be accessible
    EXPECT_TRUE(sa.has_index(3));
    EXPECT_EQ(sa.get_existing(3), 30);
}

TEST_F(SparseArrayTest_71, ResizeDecreasesMaxSize_71) {
    SparseArray<int> sa(10);
    sa.set(3, 30);
    sa.resize(5);
    EXPECT_EQ(sa.max_size(), 5);
    EXPECT_TRUE(sa.has_index(3));
    EXPECT_EQ(sa.get_existing(3), 30);
}

TEST_F(SparseArrayTest_71, ResizeToSameSize_71) {
    SparseArray<int> sa(10);
    sa.set(5, 50);
    sa.resize(10);
    EXPECT_EQ(sa.max_size(), 10);
    EXPECT_TRUE(sa.has_index(5));
}

// --- Iterator Tests ---

TEST_F(SparseArrayTest_71, BeginEqualsEndWhenEmpty_71) {
    SparseArray<int> sa(10);
    EXPECT_EQ(sa.begin(), sa.end());
}

TEST_F(SparseArrayTest_71, IteratorTraversal_71) {
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

    // All set indices should appear
    EXPECT_NE(std::find(indices.begin(), indices.end(), 2), indices.end());
    EXPECT_NE(std::find(indices.begin(), indices.end(), 5), indices.end());
    EXPECT_NE(std::find(indices.begin(), indices.end(), 8), indices.end());
}

TEST_F(SparseArrayTest_71, IteratorCountMatchesSize_71) {
    SparseArray<int> sa(20);
    sa.set(0, 0);
    sa.set(10, 100);
    sa.set(19, 190);

    int count = 0;
    for (auto it = sa.begin(); it != sa.end(); ++it) {
        count++;
    }
    EXPECT_EQ(count, sa.size());
}

// --- less static function Tests ---

TEST_F(SparseArrayTest_71, LessComparison_71) {
    SparseArray<int> sa(10);
    sa.set(3, 30);
    sa.set(1, 10);
    sa.set(7, 70);

    // Collect elements
    std::vector<SparseArray<int>::IndexValue> elements(sa.begin(), sa.end());

    // Sort using the less function
    std::sort(elements.begin(), elements.end(), SparseArray<int>::less);

    // After sorting, indices should be in ascending order
    for (size_t i = 1; i < elements.size(); ++i) {
        EXPECT_LT(elements[i - 1].index(), elements[i].index());
    }
}

// --- Boundary Tests ---

TEST_F(SparseArrayTest_71, SetAtIndexZero_71) {
    SparseArray<int> sa(10);
    sa.set(0, 42);
    EXPECT_TRUE(sa.has_index(0));
    EXPECT_EQ(sa.get_existing(0), 42);
}

TEST_F(SparseArrayTest_71, SetAtMaxIndex_71) {
    SparseArray<int> sa(10);
    sa.set(9, 99);
    EXPECT_TRUE(sa.has_index(9));
    EXPECT_EQ(sa.get_existing(9), 99);
}

TEST_F(SparseArrayTest_71, SingleElementArray_71) {
    SparseArray<int> sa(1);
    EXPECT_EQ(sa.max_size(), 1);
    sa.set(0, 100);
    EXPECT_EQ(sa.size(), 1);
    EXPECT_TRUE(sa.has_index(0));
    EXPECT_EQ(sa.get_existing(0), 100);
}

TEST_F(SparseArrayTest_71, FillEntireArray_71) {
    const int max_size = 100;
    SparseArray<int> sa(max_size);
    for (int i = 0; i < max_size; ++i) {
        sa.set(i, i * 2);
    }
    EXPECT_EQ(sa.size(), max_size);
    for (int i = 0; i < max_size; ++i) {
        EXPECT_TRUE(sa.has_index(i));
        EXPECT_EQ(sa.get_existing(i), i * 2);
    }
}

// --- Value Type Tests ---

TEST_F(SparseArrayTest_71, StringValueType_71) {
    SparseArray<std::string> sa(10);
    sa.set(3, "hello");
    sa.set(7, "world");
    EXPECT_EQ(sa.size(), 2);
    EXPECT_EQ(sa.get_existing(3), "hello");
    EXPECT_EQ(sa.get_existing(7), "world");
}

TEST_F(SparseArrayTest_71, DoubleValueType_71) {
    SparseArray<double> sa(5);
    sa.set(0, 3.14);
    sa.set(4, 2.71);
    EXPECT_TRUE(sa.has_index(0));
    EXPECT_DOUBLE_EQ(sa.get_existing(0), 3.14);
    EXPECT_DOUBLE_EQ(sa.get_existing(4), 2.71);
}

// --- Set then Clear then Set again ---

TEST_F(SparseArrayTest_71, SetClearSetAgain_71) {
    SparseArray<int> sa(10);
    sa.set(5, 50);
    sa.clear();
    EXPECT_FALSE(sa.has_index(5));

    sa.set(5, 500);
    EXPECT_TRUE(sa.has_index(5));
    EXPECT_EQ(sa.get_existing(5), 500);
    EXPECT_EQ(sa.size(), 1);
}

// --- set_new multiple entries ---

TEST_F(SparseArrayTest_71, SetNewMultipleEntries_71) {
    SparseArray<int> sa(10);
    sa.set_new(0, 0);
    sa.set_new(1, 10);
    sa.set_new(2, 20);
    EXPECT_EQ(sa.size(), 3);
    EXPECT_EQ(sa.get_existing(0), 0);
    EXPECT_EQ(sa.get_existing(1), 10);
    EXPECT_EQ(sa.get_existing(2), 20);
}

// --- Copy independence ---

TEST_F(SparseArrayTest_71, CopyIsIndependent_71) {
    SparseArray<int> sa(10);
    sa.set(3, 30);

    SparseArray<int> copy(sa);
    copy.set(3, 300);
    copy.set(5, 500);

    // Original should be unchanged
    EXPECT_EQ(sa.size(), 1);
    EXPECT_EQ(sa.get_existing(3), 30);
    EXPECT_FALSE(sa.has_index(5));

    // Copy should have modifications
    EXPECT_EQ(copy.size(), 2);
    EXPECT_EQ(copy.get_existing(3), 300);
    EXPECT_EQ(copy.get_existing(5), 500);
}

// --- Resize preserves existing data within bounds ---

TEST_F(SparseArrayTest_71, ResizeAndAddNewElements_71) {
    SparseArray<int> sa(5);
    sa.set(2, 20);
    sa.resize(20);
    sa.set(15, 150);
    EXPECT_EQ(sa.size(), 2);
    EXPECT_TRUE(sa.has_index(2));
    EXPECT_TRUE(sa.has_index(15));
    EXPECT_EQ(sa.get_existing(2), 20);
    EXPECT_EQ(sa.get_existing(15), 150);
}

}  // namespace re2
