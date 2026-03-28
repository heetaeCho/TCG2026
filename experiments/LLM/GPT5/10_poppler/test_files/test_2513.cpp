// poppler_layer_get_radio_button_group_id_test_2513.cc
#include <gtest/gtest.h>

#include <glib-object.h>

#include "poppler.h"          // For PopplerLayer, POPPLER_TYPE_LAYER (public API)
#include "poppler-private.h"  // For struct _PopplerLayer (test-only / internal access)

// Unit under test (declared in poppler-layer.cc)
extern "C" gint poppler_layer_get_radio_button_group_id(PopplerLayer *poppler_layer);

namespace {

class PopplerLayerTest_2513 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Ensure GLib type system is ready. (No-op on modern GLib, but harmless.)
#if !GLIB_CHECK_VERSION(2, 36, 0)
    g_type_init();
#endif
  }
};

TEST_F(PopplerLayerTest_2513, NullLayerReturnsFalse_2513) {
  // Exceptional / error case: NULL should trigger g_return_val_if_fail and return FALSE (0).
  EXPECT_EQ(poppler_layer_get_radio_button_group_id(nullptr), 0);
}

TEST_F(PopplerLayerTest_2513, NonLayerInstanceReturnsFalse_2513) {
  // Exceptional / error case: wrong GType instance should fail POPPLER_IS_LAYER and return FALSE (0).
  GObject* obj = g_object_new(G_TYPE_OBJECT, nullptr);
  ASSERT_NE(obj, nullptr);

  EXPECT_EQ(poppler_layer_get_radio_button_group_id(reinterpret_cast<PopplerLayer*>(obj)), 0);

  g_object_unref(obj);
}

TEST_F(PopplerLayerTest_2513, ReturnsEncodedGroupId_Normal_2513) {
  // Normal operation: when rbgroup is set to an encoded pointer, the getter should return it.
  PopplerLayer* layer = POPPLER_LAYER(g_object_new(POPPLER_TYPE_LAYER, nullptr));
  ASSERT_NE(layer, nullptr);

  // rbgroup is stored as a pointer-encoded integer (as implied by GPOINTER_TO_INT usage).
  const gint kGroupId = 123;
  layer->rbgroup = reinterpret_cast<int*>(GINT_TO_POINTER(kGroupId));

  EXPECT_EQ(poppler_layer_get_radio_button_group_id(layer), kGroupId);

  g_object_unref(layer);
}

TEST_F(PopplerLayerTest_2513, BoundaryGroupIdZero_2513) {
  PopplerLayer* layer = POPPLER_LAYER(g_object_new(POPPLER_TYPE_LAYER, nullptr));
  ASSERT_NE(layer, nullptr);

  const gint kGroupId = 0;
  layer->rbgroup = reinterpret_cast<int*>(GINT_TO_POINTER(kGroupId));

  EXPECT_EQ(poppler_layer_get_radio_button_group_id(layer), kGroupId);

  g_object_unref(layer);
}

TEST_F(PopplerLayerTest_2513, BoundaryNegativeGroupId_2513) {
  PopplerLayer* layer = POPPLER_LAYER(g_object_new(POPPLER_TYPE_LAYER, nullptr));
  ASSERT_NE(layer, nullptr);

  const gint kGroupId = -7;
  layer->rbgroup = reinterpret_cast<int*>(GINT_TO_POINTER(kGroupId));

  EXPECT_EQ(poppler_layer_get_radio_button_group_id(layer), kGroupId);

  g_object_unref(layer);
}

TEST_F(PopplerLayerTest_2513, BoundaryMaxIntGroupId_2513) {
  PopplerLayer* layer = POPPLER_LAYER(g_object_new(POPPLER_TYPE_LAYER, nullptr));
  ASSERT_NE(layer, nullptr);

  // Use G_MAXINT to stay within gint range.
  const gint kGroupId = G_MAXINT;
  layer->rbgroup = reinterpret_cast<int*>(GINT_TO_POINTER(kGroupId));

  EXPECT_EQ(poppler_layer_get_radio_button_group_id(layer), kGroupId);

  g_object_unref(layer);
}

}  // namespace