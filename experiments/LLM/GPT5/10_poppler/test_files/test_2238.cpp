// File: test-poppler-document-layer-new-2238.cc

#include <gtest/gtest.h>

extern "C" {
#include <glib.h>
}

// Forward declaration is sufficient: layer_new only stores the pointer.
class OptionalContentGroup;

#include "poppler-private.h"

// The function under test is `static` inside this .cc file. To test it as a black box,
// we compile it into this test translation unit.
#include "poppler-document.cc"

namespace {

class LayerNewTest_2238 : public ::testing::Test {
protected:
  static void FreeLayer(Layer* layer) {
    if (layer) {
      g_slice_free(Layer, layer);
    }
  }
};

TEST_F(LayerNewTest_2238, CreatesLayerAndStoresOcPointer_2238) {
  auto* oc = reinterpret_cast<OptionalContentGroup*>(0x1234);

  Layer* layer = layer_new(oc);
  ASSERT_NE(layer, nullptr);

  EXPECT_EQ(layer->oc, oc);
  EXPECT_EQ(layer->label, nullptr);

  FreeLayer(layer);
}

TEST_F(LayerNewTest_2238, AllowsNullOcPointer_2238) {
  Layer* layer = layer_new(nullptr);
  ASSERT_NE(layer, nullptr);

  EXPECT_EQ(layer->oc, nullptr);
  EXPECT_EQ(layer->label, nullptr);

  FreeLayer(layer);
}

TEST_F(LayerNewTest_2238, MultipleCallsReturnDistinctLayers_2238) {
  auto* oc1 = reinterpret_cast<OptionalContentGroup*>(0x1111);
  auto* oc2 = reinterpret_cast<OptionalContentGroup*>(0x2222);

  Layer* layer1 = layer_new(oc1);
  Layer* layer2 = layer_new(oc2);

  ASSERT_NE(layer1, nullptr);
  ASSERT_NE(layer2, nullptr);

  EXPECT_NE(layer1, layer2);
  EXPECT_EQ(layer1->oc, oc1);
  EXPECT_EQ(layer2->oc, oc2);

  EXPECT_EQ(layer1->label, nullptr);
  EXPECT_EQ(layer2->label, nullptr);

  FreeLayer(layer1);
  FreeLayer(layer2);
}

TEST_F(LayerNewTest_2238, CanFreeLayerAllocatedByLayerNew_2238) {
  auto* oc = reinterpret_cast<OptionalContentGroup*>(0xABCD);

  Layer* layer = layer_new(oc);
  ASSERT_NE(layer, nullptr);

  // Observable contract here: freeing should not crash.
  FreeLayer(layer);
}

} // namespace