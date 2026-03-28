#include <gtest/gtest.h>
#include <glib.h>

// Forward declarations and structure definition based on the known dependencies
// We need the Layer struct and the layer_free function

struct Layer {
    gchar *label;
    void *oc; // OptionalContentGroup* - opaque for testing purposes
    GList *kids;
};

// Declaration of the function under test
// Since it's static in the source file, we need to either include the source
// or declare it. For testing static functions, we include the source.
// However, since we're treating it as a black box, we'll declare it extern
// and assume linkage is available (or use a test wrapper).

// If the function is static, we may need to include the .cc file or have a wrapper.
// For this test, we assume the function is made available for testing.
extern "C" {
    static void layer_free(Layer *layer);
}

// Include the source to get access to the static function
// This is a common pattern for testing static C functions
#define static
#include "poppler-document.cc"
#undef static

class LayerFreeTest_2239 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
    
    Layer* create_layer(const char* label, void* oc = nullptr) {
        Layer* layer = g_slice_new0(Layer);
        if (label) {
            layer->label = g_strdup(label);
        } else {
            layer->label = nullptr;
        }
        layer->oc = oc;
        layer->kids = nullptr;
        return layer;
    }
};

// Test that passing NULL does not crash
TEST_F(LayerFreeTest_2239, NullLayerDoesNotCrash_2239) {
    // Should handle NULL gracefully due to G_UNLIKELY check
    layer_free(nullptr);
    // If we reach here without crashing, the test passes
    SUCCEED();
}

// Test freeing a layer with a label and no kids
TEST_F(LayerFreeTest_2239, FreeLayerWithLabelNoKids_2239) {
    Layer* layer = create_layer("Test Label");
    // Should not crash or leak; we're testing it doesn't segfault
    layer_free(layer);
    SUCCEED();
}

// Test freeing a layer with NULL label and no kids
TEST_F(LayerFreeTest_2239, FreeLayerWithNullLabel_2239) {
    Layer* layer = create_layer(nullptr);
    layer_free(layer);
    SUCCEED();
}

// Test freeing a layer with kids (recursive free)
TEST_F(LayerFreeTest_2239, FreeLayerWithKids_2239) {
    Layer* parent = create_layer("Parent");
    Layer* child1 = create_layer("Child1");
    Layer* child2 = create_layer("Child2");
    
    parent->kids = g_list_append(parent->kids, child1);
    parent->kids = g_list_append(parent->kids, child2);
    
    layer_free(parent);
    SUCCEED();
}

// Test freeing a layer with nested kids (deep recursion)
TEST_F(LayerFreeTest_2239, FreeLayerWithNestedKids_2239) {
    Layer* grandparent = create_layer("Grandparent");
    Layer* parent = create_layer("Parent");
    Layer* child = create_layer("Child");
    
    parent->kids = g_list_append(parent->kids, child);
    grandparent->kids = g_list_append(grandparent->kids, parent);
    
    layer_free(grandparent);
    SUCCEED();
}

// Test freeing a layer with empty kids list (NULL kids)
TEST_F(LayerFreeTest_2239, FreeLayerWithNullKidsList_2239) {
    Layer* layer = create_layer("Label");
    layer->kids = nullptr;
    layer_free(layer);
    SUCCEED();
}

// Test freeing a layer where everything is NULL/zero
TEST_F(LayerFreeTest_2239, FreeLayerAllFieldsNull_2239) {
    Layer* layer = g_slice_new0(Layer);
    layer->label = nullptr;
    layer->oc = nullptr;
    layer->kids = nullptr;
    layer_free(layer);
    SUCCEED();
}

// Test freeing a layer with multiple kids but no nested kids
TEST_F(LayerFreeTest_2239, FreeLayerWithMultipleKidsNoNesting_2239) {
    Layer* parent = create_layer("Parent");
    for (int i = 0; i < 10; i++) {
        Layer* child = create_layer(g_strdup_printf("Child%d", i));
        parent->kids = g_list_append(parent->kids, child);
    }
    layer_free(parent);
    SUCCEED();
}
