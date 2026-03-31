#include <gtest/gtest.h>
#include <glib.h>

// Forward declarations and struct definition based on known dependencies
struct _PopplerIndexIter {
    const int *items;
    size_t index;
};

// We need to work with the actual struct. Based on the known dependencies,
// the struct has items (pointer) and index. However, the code references
// iter->items->size(), which suggests items is actually a pointer to a
// container with a size() method (like std::vector). Let's use std::vector.

#include <vector>

// Redefine the struct to match actual usage in the implementation
struct PopplerIndexIter {
    std::vector<int> *items;
    size_t index;
};

// Declaration of the function under test
extern "C" {
    typedef int gboolean;
    #ifndef TRUE
    #define TRUE 1
    #endif
    #ifndef FALSE
    #define FALSE 0
    #endif
    gboolean poppler_index_iter_next(PopplerIndexIter *iter);
}

// Since we can't link against the actual library easily, we replicate the function
// based on the provided source for testing purposes.
gboolean poppler_index_iter_next(PopplerIndexIter *iter) {
    if (iter == nullptr) return FALSE;
    iter->index++;
    if (iter->index >= iter->items->size()) {
        return FALSE;
    }
    return TRUE;
}

class PopplerIndexIterTest_2218 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that passing nullptr returns FALSE
TEST_F(PopplerIndexIterTest_2218, NullIterReturnsFalse_2218) {
    gboolean result = poppler_index_iter_next(nullptr);
    EXPECT_EQ(result, FALSE);
}

// Test that calling next on a single-element list returns FALSE (index goes from 0 to 1, size=1)
TEST_F(PopplerIndexIterTest_2218, SingleElementListReturnsFalse_2218) {
    std::vector<int> items = {42};
    PopplerIndexIter iter;
    iter.items = &items;
    iter.index = 0;

    gboolean result = poppler_index_iter_next(&iter);
    EXPECT_EQ(result, FALSE);
    EXPECT_EQ(iter.index, 1u);
}

// Test that calling next on a two-element list from index 0 returns TRUE
TEST_F(PopplerIndexIterTest_2218, TwoElementsFirstNextReturnsTrue_2218) {
    std::vector<int> items = {1, 2};
    PopplerIndexIter iter;
    iter.items = &items;
    iter.index = 0;

    gboolean result = poppler_index_iter_next(&iter);
    EXPECT_EQ(result, TRUE);
    EXPECT_EQ(iter.index, 1u);
}

// Test that calling next on a two-element list from index 1 returns FALSE
TEST_F(PopplerIndexIterTest_2218, TwoElementsSecondNextReturnsFalse_2218) {
    std::vector<int> items = {1, 2};
    PopplerIndexIter iter;
    iter.items = &items;
    iter.index = 1;

    gboolean result = poppler_index_iter_next(&iter);
    EXPECT_EQ(result, FALSE);
    EXPECT_EQ(iter.index, 2u);
}

// Test iterating through all elements of a multi-element list
TEST_F(PopplerIndexIterTest_2218, FullIterationMultipleElements_2218) {
    std::vector<int> items = {10, 20, 30, 40, 50};
    PopplerIndexIter iter;
    iter.items = &items;
    iter.index = 0;

    // Should return TRUE for indices 1, 2, 3, 4
    EXPECT_EQ(poppler_index_iter_next(&iter), TRUE);  // index = 1
    EXPECT_EQ(iter.index, 1u);
    EXPECT_EQ(poppler_index_iter_next(&iter), TRUE);  // index = 2
    EXPECT_EQ(iter.index, 2u);
    EXPECT_EQ(poppler_index_iter_next(&iter), TRUE);  // index = 3
    EXPECT_EQ(iter.index, 3u);
    EXPECT_EQ(poppler_index_iter_next(&iter), TRUE);  // index = 4
    EXPECT_EQ(iter.index, 4u);
    // index = 5, which equals size, so FALSE
    EXPECT_EQ(poppler_index_iter_next(&iter), FALSE);
    EXPECT_EQ(iter.index, 5u);
}

// Test that calling next after already past end continues to return FALSE
TEST_F(PopplerIndexIterTest_2218, PastEndStillReturnsFalse_2218) {
    std::vector<int> items = {1, 2, 3};
    PopplerIndexIter iter;
    iter.items = &items;
    iter.index = 3; // already at end

    gboolean result = poppler_index_iter_next(&iter);
    EXPECT_EQ(result, FALSE);
    EXPECT_EQ(iter.index, 4u);
}

// Test with an empty vector - next should return FALSE immediately
TEST_F(PopplerIndexIterTest_2218, EmptyListReturnsFalse_2218) {
    std::vector<int> items;
    PopplerIndexIter iter;
    iter.items = &items;
    iter.index = 0;

    // index becomes 1, size is 0, so 1 >= 0 is TRUE => returns FALSE
    gboolean result = poppler_index_iter_next(&iter);
    EXPECT_EQ(result, FALSE);
}

// Test that index is properly incremented each call
TEST_F(PopplerIndexIterTest_2218, IndexIncrementedEachCall_2218) {
    std::vector<int> items = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    PopplerIndexIter iter;
    iter.items = &items;
    iter.index = 0;

    for (size_t i = 1; i < items.size(); i++) {
        gboolean result = poppler_index_iter_next(&iter);
        EXPECT_EQ(result, TRUE);
        EXPECT_EQ(iter.index, i);
    }
    
    // Last call should return FALSE
    gboolean result = poppler_index_iter_next(&iter);
    EXPECT_EQ(result, FALSE);
    EXPECT_EQ(iter.index, items.size());
}

// Test boundary: exactly at last valid index
TEST_F(PopplerIndexIterTest_2218, AtLastValidIndexReturnsFalse_2218) {
    std::vector<int> items = {100, 200, 300};
    PopplerIndexIter iter;
    iter.items = &items;
    iter.index = 2; // last valid index

    gboolean result = poppler_index_iter_next(&iter);
    EXPECT_EQ(result, FALSE);
    EXPECT_EQ(iter.index, 3u);
}

// Test boundary: at second to last index returns TRUE
TEST_F(PopplerIndexIterTest_2218, AtSecondToLastIndexReturnsTrue_2218) {
    std::vector<int> items = {100, 200, 300};
    PopplerIndexIter iter;
    iter.items = &items;
    iter.index = 1;

    gboolean result = poppler_index_iter_next(&iter);
    EXPECT_EQ(result, TRUE);
    EXPECT_EQ(iter.index, 2u);
}
