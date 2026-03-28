// File: poppler-layers-iter-next-test_2252.cc
#include <gtest/gtest.h>

#include <glib.h>

// Minimal surface needed to exercise poppler_layers_iter_next() as provided.
// We avoid depending on private Poppler headers by declaring only what we need
// for constructing an iterator instance in tests.
typedef struct _PopplerLayersIter PopplerLayersIter;

struct _PopplerLayersIter {
  gint index;
  GList* items;
};

extern "C" {
gboolean poppler_layers_iter_next(PopplerLayersIter* iter);
}

namespace {

class PopplerLayersIterNextTest_2252 : public ::testing::Test {
 protected:
  static PopplerLayersIter MakeIterWithNItems(int n_items, int start_index) {
    PopplerLayersIter iter{};
    iter.index = start_index;
    iter.items = nullptr;
    for (int i = 0; i < n_items; ++i) {
      // Store unique dummy pointers; list length is what matters for these tests.
      iter.items = g_list_append(iter.items, GINT_TO_POINTER(i + 1));
    }
    return iter;
  }

  static void FreeIter(PopplerLayersIter* iter) {
    if (!iter) return;
    g_list_free(iter->items);
    iter->items = nullptr;
  }
};

TEST_F(PopplerLayersIterNextTest_2252, NullIterReturnsFalse_2252) {
  EXPECT_EQ(poppler_layers_iter_next(nullptr), FALSE);
}

TEST_F(PopplerLayersIterNextTest_2252, EmptyItemsAlwaysReturnsFalse_2252) {
  PopplerLayersIter iter = MakeIterWithNItems(/*n_items=*/0, /*start_index=*/-1);

  EXPECT_EQ(poppler_layers_iter_next(&iter), FALSE);
  // Call again to ensure consistent behavior on repeated calls.
  EXPECT_EQ(poppler_layers_iter_next(&iter), FALSE);

  FreeIter(&iter);
}

TEST_F(PopplerLayersIterNextTest_2252, SingleItemFromMinusOneTrueThenFalse_2252) {
  PopplerLayersIter iter = MakeIterWithNItems(/*n_items=*/1, /*start_index=*/-1);

  EXPECT_EQ(poppler_layers_iter_next(&iter), TRUE);
  EXPECT_EQ(poppler_layers_iter_next(&iter), FALSE);
  // Further calls remain FALSE once iteration is past the end.
  EXPECT_EQ(poppler_layers_iter_next(&iter), FALSE);

  FreeIter(&iter);
}

TEST_F(PopplerLayersIterNextTest_2252, TwoItemsFromMinusOneTwoTruesThenFalse_2252) {
  PopplerLayersIter iter = MakeIterWithNItems(/*n_items=*/2, /*start_index=*/-1);

  EXPECT_EQ(poppler_layers_iter_next(&iter), TRUE);
  EXPECT_EQ(poppler_layers_iter_next(&iter), TRUE);
  EXPECT_EQ(poppler_layers_iter_next(&iter), FALSE);

  FreeIter(&iter);
}

TEST_F(PopplerLayersIterNextTest_2252, StartingAtZeroWithSingleItemReturnsFalse_2252) {
  // Boundary: if index starts at 0 and there is 1 item, the next() call advances
  // and should report end-of-list.
  PopplerLayersIter iter = MakeIterWithNItems(/*n_items=*/1, /*start_index=*/0);

  EXPECT_EQ(poppler_layers_iter_next(&iter), FALSE);
  // Repeated calls continue to return FALSE.
  EXPECT_EQ(poppler_layers_iter_next(&iter), FALSE);

  FreeIter(&iter);
}

TEST_F(PopplerLayersIterNextTest_2252, StartingPastEndReturnsFalse_2252) {
  // Boundary: starting already past the end should still return FALSE.
  PopplerLayersIter iter = MakeIterWithNItems(/*n_items=*/2, /*start_index=*/10);

  EXPECT_EQ(poppler_layers_iter_next(&iter), FALSE);

  FreeIter(&iter);
}

TEST_F(PopplerLayersIterNextTest_2252, VeryLargeIndexReturnsFalse_2252) {
  // Boundary: extremely large index should not produce TRUE when list is small.
  PopplerLayersIter iter = MakeIterWithNItems(/*n_items=*/1, /*start_index=*/G_MAXINT - 1);

  EXPECT_EQ(poppler_layers_iter_next(&iter), FALSE);

  FreeIter(&iter);
}

}  // namespace