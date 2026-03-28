// poppler-action-layer-free-test-2285.cc
#include <gtest/gtest.h>

#include <glib-object.h>
#include <glib.h>

#include "poppler-action.h"

// Include the implementation unit so we can test the static helper directly.
// Assumption in this test harness: this TU is built for tests (and the file is
// not also linked separately), so including it will not cause duplicate symbols.
#include "poppler-action.cc"

namespace {

class PopplerActionLayerFreeTest_2285 : public ::testing::Test {
protected:
  static void SetUpTestSuite() {
    // Ensure GType system is initialized (safe to call multiple times on GLib >= 2.36).
#if !GLIB_CHECK_VERSION(2, 36, 0)
    g_type_init();
#endif
  }
};

static void WeakNotifyIncrement(gpointer data, GObject * /*where_object_was*/) {
  auto *counter = static_cast<gint *>(data);
  g_atomic_int_inc(counter);
}

static PopplerActionLayer *NewActionLayerWithLayers_2285(GList *layers_list) {
  PopplerActionLayer *layer = g_slice_new0(PopplerActionLayer);
  // The provided "dependency" snippet shows `int* layers`, but the implementation
  // treats it like a GList*. We avoid assuming the exact declared type here and
  // store the pointer value in a type-agnostic way.
  using LayersMemberT = decltype(layer->layers);
  layer->layers = reinterpret_cast<LayersMemberT>(layers_list);
  return layer;
}

}  // namespace

TEST_F(PopplerActionLayerFreeTest_2285, NullActionLayerDoesNotCrash_2285) {
  // Should be a no-op.
  poppler_action_layer_free(nullptr);
}

TEST_F(PopplerActionLayerFreeTest_2285, FreesAndUnrefsAllLayers_2285) {
  // Create a couple of plain GObjects; they start with refcount=1.
  GObject *obj1 = G_OBJECT(g_object_new(G_TYPE_OBJECT, nullptr));
  GObject *obj2 = G_OBJECT(g_object_new(G_TYPE_OBJECT, nullptr));

  // Track finalization via weak refs (called when object is finalized).
  gint finalized_count = 0;
  g_object_weak_ref(obj1, WeakNotifyIncrement, &finalized_count);
  g_object_weak_ref(obj2, WeakNotifyIncrement, &finalized_count);

  // Put them into a GList. Note: appending does not add refs.
  GList *layers = nullptr;
  layers = g_list_append(layers, obj1);
  layers = g_list_append(layers, obj2);

  PopplerActionLayer *action_layer = NewActionLayerWithLayers_2285(layers);

  // This should free the list, unref both objects, and free the action_layer.
  poppler_action_layer_free(action_layer);

  // Both objects should have been unref'd to zero and finalized.
  EXPECT_EQ(g_atomic_int_get(&finalized_count), 2);
}

TEST_F(PopplerActionLayerFreeTest_2285, NullLayersListDoesNotCrash_2285) {
  PopplerActionLayer *action_layer = NewActionLayerWithLayers_2285(nullptr);
  // Should safely free the action_layer even when layers is null.
  poppler_action_layer_free(action_layer);
}