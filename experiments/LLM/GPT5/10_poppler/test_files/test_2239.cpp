// layer_free_test_2239.cc
//
// Unit tests for static layer_free() in poppler-document.cc
// Constraints: treat implementation as black box; test only observable behavior.
// We can only reliably test "does not crash" for various inputs, since the
// function is void and only performs frees.

#include <gtest/gtest.h>

#include <glib.h>

// Include the implementation file to access the TU-local static function.
// This is a common pattern for testing static functions.
#include "poppler-document.cc"

namespace {

class LayerFreeTest_2239 : public ::testing::Test {
protected:
  // Helper to allocate a Layer in the same way the implementation expects.
  static Layer* NewLayer() { return g_slice_new0(Layer); }

  static void SetLabel(Layer* layer, const char* text) {
    // layer_free() uses g_free(layer->label), so allocate with GLib.
    // The actual field type in the production code is expected to be compatible
    // with g_free (typically gchar* / char*).
    layer->label = reinterpret_cast<decltype(layer->label)>(g_strdup(text));
  }

  static void AddChild(Layer* parent, Layer* child) {
    parent->kids = g_list_append(parent->kids, child);
  }
};

TEST_F(LayerFreeTest_2239, NullLayerDoesNotCrash_2239) {
  // Boundary / error-tolerance: nullptr should be handled safely.
  layer_free(nullptr);
  SUCCEED();
}

TEST_F(LayerFreeTest_2239, EmptyLayerNoKidsNoLabelDoesNotCrash_2239) {
  // Normal: a minimal Layer with default-initialized fields.
  Layer* layer = NewLayer();
  ASSERT_NE(layer, nullptr);

  layer_free(layer);
  SUCCEED();
}

TEST_F(LayerFreeTest_2239, LayerWithLabelDoesNotCrash_2239) {
  // Normal: label set (freed by g_free).
  Layer* layer = NewLayer();
  ASSERT_NE(layer, nullptr);

  SetLabel(layer, "Layer Label");

  layer_free(layer);
  SUCCEED();
}

TEST_F(LayerFreeTest_2239, LayerWithSingleChildDoesNotCrash_2239) {
  // Normal: parent has one child in kids list.
  Layer* parent = NewLayer();
  Layer* child = NewLayer();
  ASSERT_NE(parent, nullptr);
  ASSERT_NE(child, nullptr);

  SetLabel(parent, "Parent");
  SetLabel(child, "Child");

  AddChild(parent, child);

  layer_free(parent);
  SUCCEED();
}

TEST_F(LayerFreeTest_2239, LayerWithMultipleChildrenDoesNotCrash_2239) {
  // Boundary: multiple kids in list.
  Layer* parent = NewLayer();
  Layer* child1 = NewLayer();
  Layer* child2 = NewLayer();
  ASSERT_NE(parent, nullptr);
  ASSERT_NE(child1, nullptr);
  ASSERT_NE(child2, nullptr);

  SetLabel(parent, "Parent");
  SetLabel(child1, "Child1");
  SetLabel(child2, "Child2");

  AddChild(parent, child1);
  AddChild(parent, child2);

  layer_free(parent);
  SUCCEED();
}

TEST_F(LayerFreeTest_2239, DeeplyNestedKidsDoesNotCrash_2239) {
  // Boundary: nested list depth > 1.
  Layer* root = NewLayer();
  Layer* mid = NewLayer();
  Layer* leaf1 = NewLayer();
  Layer* leaf2 = NewLayer();
  ASSERT_NE(root, nullptr);
  ASSERT_NE(mid, nullptr);
  ASSERT_NE(leaf1, nullptr);
  ASSERT_NE(leaf2, nullptr);

  SetLabel(root, "Root");
  SetLabel(mid, "Mid");
  SetLabel(leaf1, "Leaf1");
  SetLabel(leaf2, "Leaf2");

  AddChild(root, mid);
  AddChild(mid, leaf1);
  AddChild(mid, leaf2);

  layer_free(root);
  SUCCEED();
}

TEST_F(LayerFreeTest_2239, LayerWithKidsButNoLabelsDoesNotCrash_2239) {
  // Boundary: kids present, labels left null.
  Layer* parent = NewLayer();
  Layer* child = NewLayer();
  ASSERT_NE(parent, nullptr);
  ASSERT_NE(child, nullptr);

  AddChild(parent, child);

  layer_free(parent);
  SUCCEED();
}

}  // namespace