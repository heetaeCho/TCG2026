#include "gtest/gtest.h"
#include "re2/sparse_array.h"

namespace re2 {

// Test fixture for SparseArray tests
class SparseArrayTest_84 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ===================== Construction Tests =====================

TEST_F(SparseArrayTest_84, DefaultConstructor_84) {
    SparseArray<int> sa;
    EXPECT_EQ(sa.size(), 0);
    EXPECT_EQ(sa.max_size(), 0);
    EXPECT_TRUE(sa.empty());
}

TEST_F(SparseArrayTest_84, ConstructorWithMaxSize_84) {
    SparseArray<int> sa(100);
    EXPECT_EQ(sa.size(), 0);
    EXPECT_EQ(sa.max_size(), 100);
    EXPECT_TRUE(sa.empty());
}

TEST_F(SparseArrayTest_84, ConstructorWithZeroMaxSize_84) {
    SparseArray<int> sa(0);
    EXPECT_EQ(sa.size(), 0);
    EXPECT_EQ(sa.max_size(), 0);
}

// ===================== Copy Constructor Tests =====================

TEST_F(SparseArrayTest_84, CopyConstructorEmpty_84) {
    SparseArray<int> sa(10);
    SparseArray<int> copy(sa);
    EXPECT_EQ(copy.size(), 0);
    EXPECT_EQ(copy.max_size(), 10);
}

TEST_F(SparseArrayTest_84, CopyConstructorWithElements_84) {
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

// ===================== Move Constructor Tests =====================

TEST_F(SparseArrayTest_84, MoveConstructor_84) {
    SparseArray<int> sa(10);
    sa.set(5, 50);
    SparseArray<int> moved(std::move(sa));
    EXPECT_EQ(moved.size(), 1);
    EXPECT_TRUE(moved.has_index(5));
    EXPECT_EQ(moved.get_existing(5), 50);
}

// ===================== Copy Assignment Tests =====================

TEST_F(SparseArrayTest_84, CopyAssignment_84) {
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

// ===================== Move Assignment Tests =====================

TEST_F(SparseArrayTest_84, MoveAssignment_84) {
    SparseArray<int> sa(10);
    sa.set(1, 10);
    SparseArray<int> other(5);
    other = std::move(sa);
    EXPECT_EQ(other.size(), 1);
    EXPECT_TRUE(other.has_index(1));
    EXPECT_EQ(other.get_existing(1), 10);
}

// ===================== Resize Tests =====================

TEST_F(SparseArrayTest_84, ResizeIncreasesMaxSize_84) {
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

TEST_F(SparseArrayTest_84, ResizeToSameSize_84) {
    SparseArray<int> sa(10);
    sa.set(5, 50);
    sa.resize(10);
    EXPECT_EQ(sa.max_size(), 10);
    EXPECT_EQ(sa.size(), 1);
    EXPECT_TRUE(sa.has_index(5));
    EXPECT_EQ(sa.get_existing(5), 50);
}

TEST_F(SparseArrayTest_84, ResizeDecreasesToSmallerThanSize_84) {
    SparseArray<int> sa(10);
    sa.set(0, 0);
    sa.set(1, 10);
    sa.set(2, 20);
    sa.set(3, 30);
    // size is 4 now, resize to 2 should truncate size to 2
    sa.resize(2);
    EXPECT_EQ(sa.size(), 2);
}

TEST_F(SparseArrayTest_84, ResizeFromZero_84) {
    SparseArray<int> sa(0);
    sa.resize(10);
    EXPECT_EQ(sa.max_size(), 10);
    EXPECT_EQ(sa.size(), 0);
    sa.set(5, 50);
    EXPECT_EQ(sa.size(), 1);
    EXPECT_TRUE(sa.has_index(5));
}

TEST_F(SparseArrayTest_84, ResizePreservesDataAfterGrowing_84) {
    SparseArray<int> sa(5);
    sa.set(0, 100);
    sa.set(1, 200);
    sa.set(4, 500);
    sa.resize(50);
    EXPECT_EQ(sa.get_existing(0), 100);
    EXPECT_EQ(sa.get_existing(1), 200);
    EXPECT_EQ(sa.get_existing(4), 500);
    // Can now use indices up to 49
    sa.set(49, 999);
    EXPECT_TRUE(sa.has_index(49));
    EXPECT_EQ(sa.get_existing(49), 999);
}

TEST_F(SparseArrayTest_84, ResizeMultipleTimes_84) {
    SparseArray<int> sa(2);
    sa.set(0, 10);
    sa.set(1, 20);
    sa.resize(5);
    sa.set(3, 30);
    sa.resize(10);
    sa.set(9, 90);
    EXPECT_EQ(sa.size(), 4);
    EXPECT_EQ(sa.get_existing(0), 10);
    EXPECT_EQ(sa.get_existing(1), 20);
    EXPECT_EQ(sa.get_existing(3), 30);
    EXPECT_EQ(sa.get_existing(9), 90);
}

TEST_F(SparseArrayTest_84, ResizeDecreaseDoesNotChangeMaxSizeIfSmaller_84) {
    SparseArray<int> sa(10);
    sa.set(0, 1);
    sa.resize(5);
    // max_size should remain 10 since we only decrease when new_max_size > max_size
    // Actually, looking at the implementation, resize only copies if new_max_size > max_size()
    // and only truncates size_ if size_ > new_max_size
    EXPECT_EQ(sa.max_size(), 10);
    EXPECT_EQ(sa.size(), 1);
}

// ===================== Set/Get Tests =====================

TEST_F(SparseArrayTest_84, SetAndGet_84) {
    SparseArray<int> sa(10);
    sa.set(5, 42);
    EXPECT_TRUE(sa.has_index(5));
    EXPECT_EQ(sa.get_existing(5), 42);
}

TEST_F(SparseArrayTest_84, SetOverwritesExisting_84) {
    SparseArray<int> sa(10);
    sa.set(5, 42);
    sa.set(5, 99);
    EXPECT_EQ(sa.size(), 1);
    EXPECT_EQ(sa.get_existing(5), 99);
}

TEST_F(SparseArrayTest_84, SetNew_84) {
    SparseArray<int> sa(10);
    sa.set_new(3, 33);
    EXPECT_TRUE(sa.has_index(3));
    EXPECT_EQ(sa.get_existing(3), 33);
    EXPECT_EQ(sa.size(), 1);
}

TEST_F(SparseArrayTest_84, SetExisting_84) {
    SparseArray<int> sa(10);
    sa.set(7, 70);
    sa.set_existing(7, 77);
    EXPECT_EQ(sa.get_existing(7), 77);
    EXPECT_EQ(sa.size(), 1);
}

// ===================== has_index Tests =====================

TEST_F(SparseArrayTest_84, HasIndexReturnsFalseForUnset_84) {
    SparseArray<int> sa(10);
    EXPECT_FALSE(sa.has_index(0));
    EXPECT_FALSE(sa.has_index(5));
    EXPECT_FALSE(sa.has_index(9));
}

TEST_F(SparseArrayTest_84, HasIndexReturnsTrueForSet_84) {
    SparseArray<int> sa(10);
    sa.set(3, 30);
    EXPECT_TRUE(sa.has_index(3));
}

TEST_F(SparseArrayTest_84, HasIndexAfterClear_84) {
    SparseArray<int> sa(10);
    sa.set(3, 30);
    sa.clear();
    EXPECT_FALSE(sa.has_index(3));
}

// ===================== Clear Tests =====================

TEST_F(SparseArrayTest_84, ClearEmptiesArray_84) {
    SparseArray<int> sa(10);
    sa.set(0, 1);
    sa.set(5, 2);
    sa.set(9, 3);
    EXPECT_EQ(sa.size(), 3);
    sa.clear();
    EXPECT_EQ(sa.size(), 0);
    EXPECT_TRUE(sa.empty());
    EXPECT_EQ(sa.max_size(), 10);
}

TEST_F(SparseArrayTest_84, ClearOnEmpty_84) {
    SparseArray<int> sa(10);
    sa.clear();
    EXPECT_EQ(sa.size(), 0);
    EXPECT_TRUE(sa.empty());
}

// ===================== Size/Empty Tests =====================

TEST_F(SparseArrayTest_84, SizeIncreasesWithSet_84) {
    SparseArray<int> sa(10);
    EXPECT_EQ(sa.size(), 0);
    sa.set(0, 1);
    EXPECT_EQ(sa.size(), 1);
    sa.set(1, 2);
    EXPECT_EQ(sa.size(), 2);
}

TEST_F(SparseArrayTest_84, EmptyReturnsTrueWhenEmpty_84) {
    SparseArray<int> sa(10);
    EXPECT_TRUE(sa.empty());
}

TEST_F(SparseArrayTest_84, EmptyReturnsFalseWhenNotEmpty_84) {
    SparseArray<int> sa(10);
    sa.set(0, 1);
    EXPECT_FALSE(sa.empty());
}

// ===================== Iterator Tests =====================

TEST_F(SparseArrayTest_84, BeginEqualsEndWhenEmpty_84) {
    SparseArray<int> sa(10);
    EXPECT_EQ(sa.begin(), sa.end());
}

TEST_F(SparseArrayTest_84, IteratorTraversal_84) {
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

// ===================== less() Tests =====================

TEST_F(SparseArrayTest_84, LessComparison_84) {
    // The less function compares IndexValues, presumably by index
    SparseArray<int> sa(10);
    sa.set(2, 20);
    sa.set(5, 50);
    auto it1 = sa.begin();
    auto it2 = it1 + 1;
    // We can test that less works on IndexValues
    // Note: we don't know exact ordering but we can test the function exists
    // and returns a bool
    bool result = SparseArray<int>::less(*it1, *it2);
    // The result depends on the indices of the two elements
    (void)result; // Just verify it compiles and runs
}

// ===================== String Value Type Tests =====================

TEST_F(SparseArrayTest_84, StringValueType_84) {
    SparseArray<std::string> sa(10);
    sa.set(3, "hello");
    sa.set(7, "world");
    EXPECT_TRUE(sa.has_index(3));
    EXPECT_TRUE(sa.has_index(7));
    EXPECT_EQ(sa.get_existing(3), "hello");
    EXPECT_EQ(sa.get_existing(7), "world");
}

TEST_F(SparseArrayTest_84, StringValueResize_84) {
    SparseArray<std::string> sa(5);
    sa.set(2, "test");
    sa.resize(20);
    EXPECT_EQ(sa.get_existing(2), "test");
    sa.set(15, "resized");
    EXPECT_EQ(sa.get_existing(15), "resized");
}

// ===================== Boundary Tests =====================

TEST_F(SparseArrayTest_84, SetAtIndexZero_84) {
    SparseArray<int> sa(10);
    sa.set(0, 42);
    EXPECT_TRUE(sa.has_index(0));
    EXPECT_EQ(sa.get_existing(0), 42);
}

TEST_F(SparseArrayTest_84, SetAtMaxIndex_84) {
    SparseArray<int> sa(10);
    sa.set(9, 99);
    EXPECT_TRUE(sa.has_index(9));
    EXPECT_EQ(sa.get_existing(9), 99);
}

TEST_F(SparseArrayTest_84, FillAllIndices_84) {
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

TEST_F(SparseArrayTest_84, ResizeThenFillNewIndices_84) {
    SparseArray<int> sa(5);
    for (int i = 0; i < 5; i++) {
        sa.set(i, i);
    }
    sa.resize(10);
    for (int i = 5; i < 10; i++) {
        sa.set(i, i);
    }
    EXPECT_EQ(sa.size(), 10);
    for (int i = 0; i < 10; i++) {
        EXPECT_TRUE(sa.has_index(i));
        EXPECT_EQ(sa.get_existing(i), i);
    }
}

TEST_F(SparseArrayTest_84, ResizeSmallerTruncatesSize_84) {
    SparseArray<int> sa(10);
    for (int i = 0; i < 10; i++) {
        sa.set(i, i * 10);
    }
    EXPECT_EQ(sa.size(), 10);
    sa.resize(3);
    EXPECT_EQ(sa.size(), 3);
}

TEST_F(SparseArrayTest_84, ClearThenReuse_84) {
    SparseArray<int> sa(10);
    sa.set(5, 50);
    sa.clear();
    sa.set(5, 500);
    EXPECT_EQ(sa.size(), 1);
    EXPECT_EQ(sa.get_existing(5), 500);
}

// ===================== Double Value Type Tests =====================

TEST_F(SparseArrayTest_84, DoubleValueType_84) {
    SparseArray<double> sa(10);
    sa.set(3, 3.14);
    sa.set(7, 2.718);
    EXPECT_TRUE(sa.has_index(3));
    EXPECT_TRUE(sa.has_index(7));
    EXPECT_DOUBLE_EQ(sa.get_existing(3), 3.14);
    EXPECT_DOUBLE_EQ(sa.get_existing(7), 2.718);
}

// ===================== Large Resize Tests =====================

TEST_F(SparseArrayTest_84, LargeResize_84) {
    SparseArray<int> sa(10);
    sa.set(5, 50);
    sa.resize(10000);
    EXPECT_EQ(sa.max_size(), 10000);
    EXPECT_TRUE(sa.has_index(5));
    EXPECT_EQ(sa.get_existing(5), 50);
    sa.set(9999, 99990);
    EXPECT_TRUE(sa.has_index(9999));
    EXPECT_EQ(sa.get_existing(9999), 99990);
}

// ===================== MaxSize Tests =====================

TEST_F(SparseArrayTest_84, MaxSizeUnchangedAfterOperations_84) {
    SparseArray<int> sa(10);
    sa.set(0, 1);
    sa.set(9, 9);
    sa.clear();
    EXPECT_EQ(sa.max_size(), 10);
}

// ===================== set returns iterator Tests =====================

TEST_F(SparseArrayTest_84, SetReturnsValidIterator_84) {
    SparseArray<int> sa(10);
    auto it = sa.set(5, 50);
    EXPECT_NE(it, sa.end());
}

TEST_F(SparseArrayTest_84, SetNewReturnsValidIterator_84) {
    SparseArray<int> sa(10);
    auto it = sa.set_new(3, 30);
    EXPECT_NE(it, sa.end());
}

TEST_F(SparseArrayTest_84, SetExistingReturnsValidIterator_84) {
    SparseArray<int> sa(10);
    sa.set(3, 30);
    auto it = sa.set_existing(3, 300);
    EXPECT_NE(it, sa.end());
}

}  // namespace re2
