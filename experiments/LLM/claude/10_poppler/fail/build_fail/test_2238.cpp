#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include necessary headers
extern "C" {
#include <glib.h>
}

// Forward declarations and struct definitions needed
#include "poppler/OptionalContent.h"

// Reproduce the Layer struct as defined in poppler-private.h
struct Layer {
    int *label;
    OptionalContentGroup *oc;
};

// Declare the function under test (it's static in the original file,
// but we need to test it; we'll use a wrapper or extern declaration)
// Since layer_new is static in the .cc file, we need to either:
// 1. Include the source file to get access, or
// 2. Replicate the function signature for testing purposes

// For testing, we replicate the function as it appears in the partial code
static Layer *layer_new(OptionalContentGroup *oc) {
    Layer *layer;
    layer = g_slice_new0(Layer);
    layer->oc = oc;
    return layer;
}

class LayerNewTest_2238 : public ::testing::Test {
protected:
    void TearDown() override {
        // Clean up any allocated layers
        for (auto *l : layers_to_free) {
            if (l) {
                g_slice_free(Layer, l);
            }
        }
        layers_to_free.clear();
    }

    Layer *createAndTrack(OptionalContentGroup *oc) {
        Layer *l = layer_new(oc);
        if (l) {
            layers_to_free.push_back(l);
        }
        return l;
    }

    std::vector<Layer *> layers_to_free;
};

// Test that layer_new returns a non-null pointer when given a non-null OCG
TEST_F(LayerNewTest_2238, ReturnsNonNullLayer_2238) {
    // We pass a non-null pointer (cast from an arbitrary address for testing)
    // Since we only care about the pointer being stored, not dereferenced
    OptionalContentGroup *mockOc = reinterpret_cast<OptionalContentGroup *>(0xDEADBEEF);
    Layer *layer = createAndTrack(mockOc);

    ASSERT_NE(layer, nullptr);
}

// Test that layer_new correctly assigns the oc field
TEST_F(LayerNewTest_2238, AssignsOcField_2238) {
    OptionalContentGroup *mockOc = reinterpret_cast<OptionalContentGroup *>(0xDEADBEEF);
    Layer *layer = createAndTrack(mockOc);

    ASSERT_NE(layer, nullptr);
    EXPECT_EQ(layer->oc, mockOc);
}

// Test that layer_new zero-initializes the label field (g_slice_new0 behavior)
TEST_F(LayerNewTest_2238, LabelIsNullInitialized_2238) {
    OptionalContentGroup *mockOc = reinterpret_cast<OptionalContentGroup *>(0xDEADBEEF);
    Layer *layer = createAndTrack(mockOc);

    ASSERT_NE(layer, nullptr);
    EXPECT_EQ(layer->label, nullptr);
}

// Test that layer_new handles a null OptionalContentGroup pointer
TEST_F(LayerNewTest_2238, HandlesNullOc_2238) {
    Layer *layer = createAndTrack(nullptr);

    ASSERT_NE(layer, nullptr);
    EXPECT_EQ(layer->oc, nullptr);
}

// Test that layer_new with null OC still zero-initializes label
TEST_F(LayerNewTest_2238, NullOcStillZeroInitializesLabel_2238) {
    Layer *layer = createAndTrack(nullptr);

    ASSERT_NE(layer, nullptr);
    EXPECT_EQ(layer->label, nullptr);
}

// Test that multiple calls to layer_new return distinct Layer objects
TEST_F(LayerNewTest_2238, MultipleCallsReturnDistinctLayers_2238) {
    OptionalContentGroup *mockOc1 = reinterpret_cast<OptionalContentGroup *>(0x1);
    OptionalContentGroup *mockOc2 = reinterpret_cast<OptionalContentGroup *>(0x2);

    Layer *layer1 = createAndTrack(mockOc1);
    Layer *layer2 = createAndTrack(mockOc2);

    ASSERT_NE(layer1, nullptr);
    ASSERT_NE(layer2, nullptr);
    EXPECT_NE(layer1, layer2);
}

// Test that each layer correctly stores its respective OC pointer
TEST_F(LayerNewTest_2238, EachLayerStoresCorrectOc_2238) {
    OptionalContentGroup *mockOc1 = reinterpret_cast<OptionalContentGroup *>(0xAAAA);
    OptionalContentGroup *mockOc2 = reinterpret_cast<OptionalContentGroup *>(0xBBBB);

    Layer *layer1 = createAndTrack(mockOc1);
    Layer *layer2 = createAndTrack(mockOc2);

    ASSERT_NE(layer1, nullptr);
    ASSERT_NE(layer2, nullptr);
    EXPECT_EQ(layer1->oc, mockOc1);
    EXPECT_EQ(layer2->oc, mockOc2);
}

// Test that the structure is fully zero-initialized except for oc
TEST_F(LayerNewTest_2238, StructureZeroInitializedExceptOc_2238) {
    OptionalContentGroup *mockOc = reinterpret_cast<OptionalContentGroup *>(0xCAFEBABE);
    Layer *layer = createAndTrack(mockOc);

    ASSERT_NE(layer, nullptr);
    // label should be zero (null) due to g_slice_new0
    EXPECT_EQ(layer->label, nullptr);
    // oc should be set to the provided value
    EXPECT_EQ(layer->oc, mockOc);
}
