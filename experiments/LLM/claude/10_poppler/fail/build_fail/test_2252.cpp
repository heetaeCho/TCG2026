#include <gtest/gtest.h>
#include <glib.h>

// Forward declarations and struct definition based on the known dependencies
struct _PopplerLayersIter {
    GList *items;
    int index;
};

typedef struct _PopplerLayersIter PopplerLayersIter;

// Declaration of the function under test
extern "C" {
gboolean poppler_layers_iter_next(PopplerLayersIter *iter);
}

class PopplerLayersIterTest_2252 : public ::testing::Test {
protected:
    void SetUp() override {
        iter = nullptr;
    }

    void TearDown() override {
        if (iter) {
            if (iter->items) {
                g_list_free(iter->items);
            }
            g_free(iter);
        }
    }

    PopplerLayersIter *createIter(int numItems, int startIndex) {
        PopplerLayersIter *it = g_new0(PopplerLayersIter, 1);
        it->items = nullptr;
        for (int i = 0; i < numItems; i++) {
            it->items = g_list_append(it->items, GINT_TO_POINTER(i));
        }
        it->index = startIndex;
        return it;
    }

    PopplerLayersIter *iter;
};

// Test that passing NULL returns FALSE
TEST_F(PopplerLayersIterTest_2252, NullIterReturnsFalse_2252) {
    gboolean result = poppler_layers_iter_next(nullptr);
    EXPECT_FALSE(result);
}

// Test advancing when there are more items remaining
TEST_F(PopplerLayersIterTest_2252, NextReturnsTrueWhenMoreItems_2252) {
    iter = createIter(3, 0);  // 3 items, starting at index 0
    // After next, index becomes 1, which is < 3
    gboolean result = poppler_layers_iter_next(iter);
    EXPECT_TRUE(result);
}

// Test that index is incremented after calling next
TEST_F(PopplerLayersIterTest_2252, IndexIncrementedAfterNext_2252) {
    iter = createIter(5, 0);
    poppler_layers_iter_next(iter);
    EXPECT_EQ(iter->index, 1);
}

// Test advancing to the last valid item returns TRUE
TEST_F(PopplerLayersIterTest_2252, NextReturnsTrueAtSecondToLastItem_2252) {
    iter = createIter(3, 1);  // 3 items, starting at index 1
    // After next, index becomes 2, which is < 3
    gboolean result = poppler_layers_iter_next(iter);
    EXPECT_TRUE(result);
}

// Test advancing past the last item returns FALSE
TEST_F(PopplerLayersIterTest_2252, NextReturnsFalseAtLastItem_2252) {
    iter = createIter(3, 2);  // 3 items, starting at index 2
    // After next, index becomes 3, which is >= 3
    gboolean result = poppler_layers_iter_next(iter);
    EXPECT_FALSE(result);
}

// Test with a single item list starting at index 0
TEST_F(PopplerLayersIterTest_2252, SingleItemListReturnsFalse_2252) {
    iter = createIter(1, 0);  // 1 item, starting at index 0
    // After next, index becomes 1, which is >= 1
    gboolean result = poppler_layers_iter_next(iter);
    EXPECT_FALSE(result);
}

// Test with empty list (0 items)
TEST_F(PopplerLayersIterTest_2252, EmptyListReturnsFalse_2252) {
    iter = createIter(0, 0);  // 0 items, starting at index 0
    // After next, index becomes 1, which is >= 0
    gboolean result = poppler_layers_iter_next(iter);
    EXPECT_FALSE(result);
}

// Test multiple successive calls to next
TEST_F(PopplerLayersIterTest_2252, MultipleNextCalls_2252) {
    iter = createIter(4, 0);  // 4 items

    EXPECT_TRUE(poppler_layers_iter_next(iter));   // index -> 1
    EXPECT_TRUE(poppler_layers_iter_next(iter));   // index -> 2
    EXPECT_TRUE(poppler_layers_iter_next(iter));   // index -> 3
    EXPECT_FALSE(poppler_layers_iter_next(iter));  // index -> 4, >= 4
}

// Test calling next after it already returned FALSE
TEST_F(PopplerLayersIterTest_2252, NextAfterEndReturnsFalse_2252) {
    iter = createIter(2, 1);  // 2 items, at last valid position

    EXPECT_FALSE(poppler_layers_iter_next(iter));  // index -> 2, >= 2
    EXPECT_FALSE(poppler_layers_iter_next(iter));  // index -> 3, >= 2
}

// Test with two items, starting from index 0
TEST_F(PopplerLayersIterTest_2252, TwoItemsIteration_2252) {
    iter = createIter(2, 0);

    EXPECT_TRUE(poppler_layers_iter_next(iter));   // index -> 1
    EXPECT_FALSE(poppler_layers_iter_next(iter));  // index -> 2, >= 2
}

// Test that index value is correctly maintained through iteration
TEST_F(PopplerLayersIterTest_2252, IndexTrackingThroughIteration_2252) {
    iter = createIter(3, 0);

    EXPECT_EQ(iter->index, 0);
    poppler_layers_iter_next(iter);
    EXPECT_EQ(iter->index, 1);
    poppler_layers_iter_next(iter);
    EXPECT_EQ(iter->index, 2);
    poppler_layers_iter_next(iter);
    EXPECT_EQ(iter->index, 3);
}
