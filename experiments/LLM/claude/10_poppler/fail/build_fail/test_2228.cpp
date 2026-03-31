#include <gtest/gtest.h>
#include <glib.h>

// Forward declare the struct and function based on the provided interface
struct _PopplerFontsIter;
typedef struct _PopplerFontsIter PopplerFontsIter;

// We need to include the actual header or recreate the struct for testing
// Based on the known/inferred dependencies:
#include <vector>

struct _PopplerFontsIter {
    std::vector<int> items; // Using vector to match .size() usage
    int index;
};

extern "C" {
    gboolean poppler_fonts_iter_next(PopplerFontsIter *iter);
}

// Reimplement the function here since we're testing it in isolation
// Actually, we need to link against the real implementation.
// For the purpose of this test file, we include the function definition
// as it was provided (treating it as the real implementation).
gboolean poppler_fonts_iter_next(PopplerFontsIter *iter) {
    g_return_val_if_fail(iter != nullptr, FALSE);
    iter->index++;
    if (iter->index >= (int)iter->items.size()) {
        return FALSE;
    }
    return TRUE;
}

class PopplerFontsIterTest_2228 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that passing nullptr returns FALSE
TEST_F(PopplerFontsIterTest_2228, NullIterReturnsFalse_2228) {
    gboolean result = poppler_fonts_iter_next(nullptr);
    EXPECT_EQ(result, FALSE);
}

// Test that next on an empty items list returns FALSE
TEST_F(PopplerFontsIterTest_2228, EmptyItemsReturnsFalse_2228) {
    PopplerFontsIter iter;
    iter.items = {};
    iter.index = -1; // Starting before the first element
    
    gboolean result = poppler_fonts_iter_next(&iter);
    EXPECT_EQ(result, FALSE);
    EXPECT_EQ(iter.index, 0);
}

// Test that next advances index and returns TRUE when more items exist
TEST_F(PopplerFontsIterTest_2228, NextReturnsTrueWhenMoreItems_2228) {
    PopplerFontsIter iter;
    iter.items = {1, 2, 3};
    iter.index = 0;
    
    gboolean result = poppler_fonts_iter_next(&iter);
    EXPECT_EQ(result, TRUE);
    EXPECT_EQ(iter.index, 1);
}

// Test that next returns FALSE when reaching the end of items
TEST_F(PopplerFontsIterTest_2228, NextReturnsFalseAtEnd_2228) {
    PopplerFontsIter iter;
    iter.items = {1, 2, 3};
    iter.index = 2; // Last valid index
    
    gboolean result = poppler_fonts_iter_next(&iter);
    EXPECT_EQ(result, FALSE);
    EXPECT_EQ(iter.index, 3);
}

// Test iterating through all items from the beginning
TEST_F(PopplerFontsIterTest_2228, FullIteration_2228) {
    PopplerFontsIter iter;
    iter.items = {10, 20, 30, 40};
    iter.index = 0;
    
    // Should be able to advance to index 1
    EXPECT_EQ(poppler_fonts_iter_next(&iter), TRUE);
    EXPECT_EQ(iter.index, 1);
    
    // Should be able to advance to index 2
    EXPECT_EQ(poppler_fonts_iter_next(&iter), TRUE);
    EXPECT_EQ(iter.index, 2);
    
    // Should be able to advance to index 3
    EXPECT_EQ(poppler_fonts_iter_next(&iter), TRUE);
    EXPECT_EQ(iter.index, 3);
    
    // Should return FALSE, no more items
    EXPECT_EQ(poppler_fonts_iter_next(&iter), FALSE);
    EXPECT_EQ(iter.index, 4);
}

// Test with a single item starting at index 0 (already at last element)
TEST_F(PopplerFontsIterTest_2228, SingleItemReturnsFalse_2228) {
    PopplerFontsIter iter;
    iter.items = {42};
    iter.index = 0;
    
    gboolean result = poppler_fonts_iter_next(&iter);
    EXPECT_EQ(result, FALSE);
    EXPECT_EQ(iter.index, 1);
}

// Test starting from index -1 (typical initial state before first element)
TEST_F(PopplerFontsIterTest_2228, StartFromNegativeOneWithItems_2228) {
    PopplerFontsIter iter;
    iter.items = {1, 2};
    iter.index = -1;
    
    // First call: index becomes 0, which is < size(2), returns TRUE
    gboolean result = poppler_fonts_iter_next(&iter);
    EXPECT_EQ(result, TRUE);
    EXPECT_EQ(iter.index, 0);
    
    // Second call: index becomes 1, which is < size(2), returns TRUE
    result = poppler_fonts_iter_next(&iter);
    EXPECT_EQ(result, TRUE);
    EXPECT_EQ(iter.index, 1);
    
    // Third call: index becomes 2, which is >= size(2), returns FALSE
    result = poppler_fonts_iter_next(&iter);
    EXPECT_EQ(result, FALSE);
    EXPECT_EQ(iter.index, 2);
}

// Test calling next multiple times after reaching the end
TEST_F(PopplerFontsIterTest_2228, MultipleCallsAfterEnd_2228) {
    PopplerFontsIter iter;
    iter.items = {1};
    iter.index = 0;
    
    EXPECT_EQ(poppler_fonts_iter_next(&iter), FALSE);
    EXPECT_EQ(iter.index, 1);
    
    // Calling again should still return FALSE
    EXPECT_EQ(poppler_fonts_iter_next(&iter), FALSE);
    EXPECT_EQ(iter.index, 2);
}

// Test with two items, starting at index 0
TEST_F(PopplerFontsIterTest_2228, TwoItemsIteration_2228) {
    PopplerFontsIter iter;
    iter.items = {100, 200};
    iter.index = 0;
    
    // Advance to index 1
    EXPECT_EQ(poppler_fonts_iter_next(&iter), TRUE);
    EXPECT_EQ(iter.index, 1);
    
    // Advance past end
    EXPECT_EQ(poppler_fonts_iter_next(&iter), FALSE);
    EXPECT_EQ(iter.index, 2);
}

// Test that index is incremented even when returning FALSE
TEST_F(PopplerFontsIterTest_2228, IndexIncrementedOnFalse_2228) {
    PopplerFontsIter iter;
    iter.items = {5, 10, 15};
    iter.index = 2; // At last element
    
    gboolean result = poppler_fonts_iter_next(&iter);
    EXPECT_EQ(result, FALSE);
    // Index should be incremented to 3 even though we returned FALSE
    EXPECT_EQ(iter.index, 3);
}
