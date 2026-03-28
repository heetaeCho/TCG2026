// poppler-document-layers-free-test_2245.cc
//
// Unit tests for poppler_document_layers_free() (black-box behavioral checks).
// We only assert observable effects via the PopplerDocument fields that the
// function itself mutates (layers / layers_rbgroups) and ensure it is safe
// across boundary scenarios.
//
// NOTE: The function under test is `static` inside poppler-document.cc.
// To test it without re-implementing logic, we include the implementation TU.

#include <gtest/gtest.h>

#include <glib.h>

extern "C" {
// Prefer the real PopplerDocument definition if available in the codebase.
#include "poppler-private.h"
}

// Include the implementation file to access the `static` function.
#include "poppler-document.cc"

namespace {

class PopplerDocumentLayersFreeTest_2245 : public ::testing::Test {
protected:
  void SetUp() override {
    // Ensure GLib is initialized if needed; most GLib APIs used here do not
    // require explicit init, but keep tests robust.
  }

  static GList* MakeDummyLayersList(int n) {
    GList* list = nullptr;
    for (int i = 0; i < n; ++i) {
      // Allocate a unique pointer per element; content is opaque to the free fn.
      gpointer p = g_malloc0(8);
      list = g_list_append(list, p);
    }
    return list;
  }

  static GList* MakeNestedList(int n_items) {
    GList* inner = nullptr;
    for (int i = 0; i < n_items; ++i) {
      // Inner list elements can be arbitrary pointers.
      inner = g_list_append(inner, GINT_TO_POINTER(i + 1));
    }
    return inner;
  }

  static GList* MakeLayersRbGroupsList(int n_groups, int inner_items_each) {
    GList* outer = nullptr;
    for (int i = 0; i < n_groups; ++i) {
      GList* inner = MakeNestedList(inner_items_each);
      outer = g_list_append(outer, inner);
    }
    return outer;
  }
};

TEST_F(PopplerDocumentLayersFreeTest_2245, NoLayersEarlyReturnDoesNotTouchRbGroups_2245) {
  PopplerDocument doc{};
  // If there are no layers, the function returns early per the interface snippet.
  doc.layers = nullptr;

  // Set layers_rbgroups to a sentinel non-null value to verify it is unchanged.
  // We allocate a real GList so we can safely free it ourselves afterward.
  doc.layers_rbgroups = MakeLayersRbGroupsList(2, 3);
  ASSERT_NE(doc.layers_rbgroups, nullptr);

  poppler_document_layers_free(&doc);

  EXPECT_EQ(doc.layers, nullptr);
  // Must remain unchanged due to early return when layers is NULL.
  EXPECT_NE(doc.layers_rbgroups, nullptr);

  // Cleanup (since the function should not have freed it in this case).
  g_list_free_full(doc.layers_rbgroups, (GDestroyNotify)g_list_free);
  doc.layers_rbgroups = nullptr;
}

TEST_F(PopplerDocumentLayersFreeTest_2245, FreesLayersAndNullsPointersWhenLayersPresent_2245) {
  PopplerDocument doc{};
  doc.layers = MakeDummyLayersList(1);
  ASSERT_NE(doc.layers, nullptr);

  // Boundary: layers present but rbgroups absent.
  doc.layers_rbgroups = nullptr;

  poppler_document_layers_free(&doc);

  EXPECT_EQ(doc.layers, nullptr);
  EXPECT_EQ(doc.layers_rbgroups, nullptr);
}

TEST_F(PopplerDocumentLayersFreeTest_2245, FreesLayersAndRbGroupsAndNullsPointers_2245) {
  PopplerDocument doc{};
  doc.layers = MakeDummyLayersList(3);
  doc.layers_rbgroups = MakeLayersRbGroupsList(3, 2);

  ASSERT_NE(doc.layers, nullptr);
  ASSERT_NE(doc.layers_rbgroups, nullptr);

  poppler_document_layers_free(&doc);

  EXPECT_EQ(doc.layers, nullptr);
  EXPECT_EQ(doc.layers_rbgroups, nullptr);
}

TEST_F(PopplerDocumentLayersFreeTest_2245, IdempotentSecondCallAfterFreeIsSafe_2245) {
  PopplerDocument doc{};
  doc.layers = MakeDummyLayersList(2);
  doc.layers_rbgroups = MakeLayersRbGroupsList(1, 1);

  poppler_document_layers_free(&doc);
  ASSERT_EQ(doc.layers, nullptr);
  ASSERT_EQ(doc.layers_rbgroups, nullptr);

  // Boundary: calling again should be a no-op (early return).
  poppler_document_layers_free(&doc);

  EXPECT_EQ(doc.layers, nullptr);
  EXPECT_EQ(doc.layers_rbgroups, nullptr);
}

#if GTEST_HAS_DEATH_TEST
TEST_F(PopplerDocumentLayersFreeTest_2245, NullDocumentPointerDeath_2245) {
  // Error case: function does not guard against nullptr `document` in the snippet.
  // Death tests validate the observable crash behavior without relying on internals.
  EXPECT_DEATH({ poppler_document_layers_free(nullptr); }, "");
}
#endif

}  // namespace