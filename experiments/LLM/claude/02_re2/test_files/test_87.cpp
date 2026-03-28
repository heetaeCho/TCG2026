#include "re2/sparse_array.h"
#include <gtest/gtest.h>
#include <algorithm>
#include <vector>

namespace re2 {

// Test fixture for SparseArray with int values
class SparseArrayTest_87 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// --- Constructor Tests ---

TEST_F(SparseArrayTest_87, DefaultConstructor_87) {
    SparseArray<int> sa;
    EXPECT_EQ(sa.size(), 0);
    EXPECT_TRUE(sa.empty());
}

TEST_F(SparseArrayTest_87, ConstructorWithMaxSize_87) {
    SparseArray<int> sa(100);
    EXPECT_EQ(sa.size(), 0);
    EXPECT_TRUE(sa.empty());
    EXPECT_EQ(sa.max_size(), 100);
}

TEST_F(SparseArrayTest_87, CopyConstructor_87) {
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

TEST_F(SparseArrayTest_87, MoveConstructor_87) {
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

// --- Assignment Tests ---

TEST_F(SparseArrayTest_87, CopyAssignment_87) {
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

TEST_F(SparseArrayTest_87, MoveAssignment_87) {
    SparseArray<int> sa(10);
    sa.set(1, 10);
    sa.set(6, 60);

    SparseArray<int> other(5);
    other = std::move(sa);
    EXPECT_EQ(other.size(), 2);
    EXPECT_TRUE(other.has_index(1));
    EXPECT_TRUE(other.has_index(6));
    EXPECT_EQ(other.get_existing(1), 10);
    EXPECT_EQ(other.get_existing(6), 60);
}

// --- Set and Get Tests ---

TEST_F(SparseArrayTest_87, SetAndGetExisting_87) {
    SparseArray<int> sa(10);
    sa.set(0, 100);
    EXPECT_EQ(sa.size(), 1);
    EXPECT_TRUE(sa.has_index(0));
    EXPECT_EQ(sa.get_existing(0), 100);
}

TEST_F(SparseArrayTest_87, SetMultipleValues_87) {
    SparseArray<int> sa(20);
    for (int i = 0; i < 20; i++) {
        sa.set(i, i * 10);
    }
    EXPECT_EQ(sa.size(), 20);
    for (int i = 0; i < 20; i++) {
        EXPECT_TRUE(sa.has_index(i));
        EXPECT_EQ(sa.get_existing(i), i * 10);
    }
}

TEST_F(SparseArrayTest_87, SetOverwritesValue_87) {
    SparseArray<int> sa(10);
    sa.set(5, 50);
    EXPECT_EQ(sa.get_existing(5), 50);
    sa.set(5, 500);
    EXPECT_EQ(sa.get_existing(5), 500);
    EXPECT_EQ(sa.size(), 1);
}

TEST_F(SparseArrayTest_87, SetNew_87) {
    SparseArray<int> sa(10);
    sa.set_new(3, 30);
    EXPECT_EQ(sa.size(), 1);
    EXPECT_TRUE(sa.has_index(3));
    EXPECT_EQ(sa.get_existing(3), 30);
}

TEST_F(SparseArrayTest_87, SetExisting_87) {
    SparseArray<int> sa(10);
    sa.set(7, 70);
    sa.set_existing(7, 700);
    EXPECT_EQ(sa.size(), 1);
    EXPECT_EQ(sa.get_existing(7), 700);
}

// --- has_index Tests ---

TEST_F(SparseArrayTest_87, HasIndexReturnsFalseForEmpty_87) {
    SparseArray<int> sa(10);
    EXPECT_FALSE(sa.has_index(0));
    EXPECT_FALSE(sa.has_index(5));
    EXPECT_FALSE(sa.has_index(9));
}

TEST_F(SparseArrayTest_87, HasIndexReturnsTrueForSetIndex_87) {
    SparseArray<int> sa(10);
    sa.set(5, 50);
    EXPECT_TRUE(sa.has_index(5));
    EXPECT_FALSE(sa.has_index(4));
    EXPECT_FALSE(sa.has_index(6));
}

// --- Size and Empty Tests ---

TEST_F(SparseArrayTest_87, SizeIncreasesWithNewElements_87) {
    SparseArray<int> sa(10);
    EXPECT_EQ(sa.size(), 0);
    sa.set(0, 0);
    EXPECT_EQ(sa.size(), 1);
    sa.set(1, 1);
    EXPECT_EQ(sa.size(), 2);
    sa.set(2, 2);
    EXPECT_EQ(sa.size(), 3);
}

TEST_F(SparseArrayTest_87, SizeDoesNotIncreaseOnOverwrite_87) {
    SparseArray<int> sa(10);
    sa.set(5, 50);
    EXPECT_EQ(sa.size(), 1);
    sa.set(5, 500);
    EXPECT_EQ(sa.size(), 1);
}

TEST_F(SparseArrayTest_87, EmptyReturnsTrueWhenEmpty_87) {
    SparseArray<int> sa(10);
    EXPECT_TRUE(sa.empty());
}

TEST_F(SparseArrayTest_87, EmptyReturnsFalseWhenNotEmpty_87) {
    SparseArray<int> sa(10);
    sa.set(0, 0);
    EXPECT_FALSE(sa.empty());
}

// --- Clear Tests ---

TEST_F(SparseArrayTest_87, ClearMakesArrayEmpty_87) {
    SparseArray<int> sa(10);
    sa.set(0, 0);
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

TEST_F(SparseArrayTest_87, ClearOnAlreadyEmpty_87) {
    SparseArray<int> sa(10);
    sa.clear();
    EXPECT_EQ(sa.size(), 0);
    EXPECT_TRUE(sa.empty());
}

// --- Iterator Tests ---

TEST_F(SparseArrayTest_87, BeginEqualsEndWhenEmpty_87) {
    SparseArray<int> sa(10);
    EXPECT_EQ(sa.begin(), sa.end());
}

TEST_F(SparseArrayTest_87, IteratorCoversAllElements_87) {
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

    // Check all expected indices and values are present
    EXPECT_NE(std::find(indices.begin(), indices.end(), 2), indices.end());
    EXPECT_NE(std::find(indices.begin(), indices.end(), 5), indices.end());
    EXPECT_NE(std::find(indices.begin(), indices.end(), 8), indices.end());
}

// --- Resize Tests ---

TEST_F(SparseArrayTest_87, ResizeIncreasesMaxSize_87) {
    SparseArray<int> sa(5);
    EXPECT_EQ(sa.max_size(), 5);
    sa.resize(20);
    EXPECT_EQ(sa.max_size(), 20);
    EXPECT_EQ(sa.size(), 0);
}

TEST_F(SparseArrayTest_87, ResizePreservesElements_87) {
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

TEST_F(SparseArrayTest_87, ResizeAllowsSettingNewHigherIndices_87) {
    SparseArray<int> sa(5);
    sa.set(2, 20);
    sa.resize(15);
    sa.set(12, 120);
    EXPECT_EQ(sa.size(), 2);
    EXPECT_TRUE(sa.has_index(12));
    EXPECT_EQ(sa.get_existing(12), 120);
}

// --- max_size Tests ---

TEST_F(SparseArrayTest_87, MaxSizeReturnsCorrectValue_87) {
    SparseArray<int> sa(42);
    EXPECT_EQ(sa.max_size(), 42);
}

// --- less function Tests ---

TEST_F(SparseArrayTest_87, LessReturnsTrueWhenFirstIndexSmaller_87) {
    SparseArray<int> sa(10);
    sa.set(2, 20);
    sa.set(5, 50);

    // We can test less by looking at the iterator elements
    auto it1 = sa.begin();
    auto it2 = sa.begin();

    // Find the elements with index 2 and 5
    bool found_less = false;
    for (auto a = sa.begin(); a != sa.end(); ++a) {
        for (auto b = sa.begin(); b != sa.end(); ++b) {
            if (a->index() < b->index()) {
                EXPECT_TRUE(SparseArray<int>::less(*a, *b));
                found_less = true;
            }
        }
    }
    EXPECT_TRUE(found_less);
}

TEST_F(SparseArrayTest_87, LessReturnsFalseWhenFirstIndexLarger_87) {
    SparseArray<int> sa(10);
    sa.set(2, 20);
    sa.set(5, 50);

    for (auto a = sa.begin(); a != sa.end(); ++a) {
        for (auto b = sa.begin(); b != sa.end(); ++b) {
            if (a->index() > b->index()) {
                EXPECT_FALSE(SparseArray<int>::less(*a, *b));
            }
        }
    }
}

TEST_F(SparseArrayTest_87, LessReturnsFalseForEqualIndices_87) {
    SparseArray<int> sa(10);
    sa.set(3, 30);

    auto it = sa.begin();
    EXPECT_FALSE(SparseArray<int>::less(*it, *it));
}

// --- Boundary Tests ---

TEST_F(SparseArrayTest_87, SetAtIndexZero_87) {
    SparseArray<int> sa(10);
    sa.set(0, 0);
    EXPECT_TRUE(sa.has_index(0));
    EXPECT_EQ(sa.get_existing(0), 0);
}

TEST_F(SparseArrayTest_87, SetAtMaxIndex_87) {
    SparseArray<int> sa(10);
    sa.set(9, 90);
    EXPECT_TRUE(sa.has_index(9));
    EXPECT_EQ(sa.get_existing(9), 90);
}

TEST_F(SparseArrayTest_87, FillEntireArray_87) {
    const int max_size = 50;
    SparseArray<int> sa(max_size);
    for (int i = 0; i < max_size; i++) {
        sa.set(i, i * 2);
    }
    EXPECT_EQ(sa.size(), max_size);
    for (int i = 0; i < max_size; i++) {
        EXPECT_TRUE(sa.has_index(i));
        EXPECT_EQ(sa.get_existing(i), i * 2);
    }
}

TEST_F(SparseArrayTest_87, SetClearSet_87) {
    SparseArray<int> sa(10);
    sa.set(5, 50);
    sa.clear();
    EXPECT_FALSE(sa.has_index(5));
    sa.set(5, 500);
    EXPECT_TRUE(sa.has_index(5));
    EXPECT_EQ(sa.get_existing(5), 500);
    EXPECT_EQ(sa.size(), 1);
}

// --- String Value Type Tests ---

TEST_F(SparseArrayTest_87, WorksWithStringValues_87) {
    SparseArray<std::string> sa(10);
    sa.set(3, "hello");
    sa.set(7, "world");
    EXPECT_EQ(sa.size(), 2);
    EXPECT_TRUE(sa.has_index(3));
    EXPECT_TRUE(sa.has_index(7));
    EXPECT_EQ(sa.get_existing(3), "hello");
    EXPECT_EQ(sa.get_existing(7), "world");
}

// --- Set returns iterator Tests ---

TEST_F(SparseArrayTest_87, SetReturnsValidIterator_87) {
    SparseArray<int> sa(10);
    auto it = sa.set(4, 40);
    EXPECT_EQ(it->index(), 4);
    EXPECT_EQ(it->value(), 40);
}

TEST_F(SparseArrayTest_87, SetNewReturnsValidIterator_87) {
    SparseArray<int> sa(10);
    auto it = sa.set_new(6, 60);
    EXPECT_EQ(it->index(), 6);
    EXPECT_EQ(it->value(), 60);
}

TEST_F(SparseArrayTest_87, SetExistingReturnsValidIterator_87) {
    SparseArray<int> sa(10);
    sa.set(8, 80);
    auto it = sa.set_existing(8, 800);
    EXPECT_EQ(it->index(), 8);
    EXPECT_EQ(it->value(), 800);
}

// --- Multiple operations sequence test ---

TEST_F(SparseArrayTest_87, MultipleOperationsSequence_87) {
    SparseArray<int> sa(20);

    // Add some elements
    sa.set(1, 10);
    sa.set(5, 50);
    sa.set(15, 150);
    EXPECT_EQ(sa.size(), 3);

    // Overwrite one
    sa.set(5, 55);
    EXPECT_EQ(sa.size(), 3);
    EXPECT_EQ(sa.get_existing(5), 55);

    // Clear
    sa.clear();
    EXPECT_EQ(sa.size(), 0);
    EXPECT_FALSE(sa.has_index(1));

    // Add again
    sa.set(10, 100);
    EXPECT_EQ(sa.size(), 1);
    EXPECT_TRUE(sa.has_index(10));

    // Resize
    sa.resize(30);
    EXPECT_TRUE(sa.has_index(10));
    sa.set(25, 250);
    EXPECT_EQ(sa.size(), 2);
    EXPECT_EQ(sa.get_existing(25), 250);
}

// --- Copy independence test ---

TEST_F(SparseArrayTest_87, CopyIsIndependent_87) {
    SparseArray<int> sa(10);
    sa.set(3, 30);

    SparseArray<int> copy(sa);
    copy.set(3, 300);

    // Original should not be affected
    EXPECT_EQ(sa.get_existing(3), 30);
    EXPECT_EQ(copy.get_existing(3), 300);
}

TEST_F(SparseArrayTest_87, CopyAssignmentIsIndependent_87) {
    SparseArray<int> sa(10);
    sa.set(7, 70);

    SparseArray<int> other(10);
    other = sa;
    other.set(7, 700);
    other.set(2, 20);

    EXPECT_EQ(sa.get_existing(7), 70);
    EXPECT_EQ(sa.size(), 1);
    EXPECT_EQ(other.get_existing(7), 700);
    EXPECT_EQ(other.size(), 2);
}

// --- SparseArray with max_size 1 ---

TEST_F(SparseArrayTest_87, MaxSizeOne_87) {
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

// --- Value modification through get_existing ---

TEST_F(SparseArrayTest_87, GetExistingReturnsModifiableReference_87) {
    SparseArray<int> sa(10);
    sa.set(4, 40);
    sa.get_existing(4) = 400;
    EXPECT_EQ(sa.get_existing(4), 400);
}

// --- Double value type ---

TEST_F(SparseArrayTest_87, WorksWithDoubleValues_87) {
    SparseArray<double> sa(10);
    sa.set(0, 3.14);
    sa.set(9, 2.718);
    EXPECT_DOUBLE_EQ(sa.get_existing(0), 3.14);
    EXPECT_DOUBLE_EQ(sa.get_existing(9), 2.718);
}

}  // namespace re2
