#include <glib.h>
#include <glib-object.h>
#include <gtest/gtest.h>

// Include poppler headers
#include "poppler-action.h"

// Since poppler_action_layer_free is static in the .cc file, we need to include it
// or have it accessible. For testing purposes, we include the source.
#include "poppler-action.cc"

class PopplerActionLayerFreeTest_2285 : public ::testing::Test {
protected:
    void SetUp() override {
        // Ensure GObject type system is initialized
        g_type_ensure(G_TYPE_OBJECT);
    }
};

// Test that passing NULL does not crash
TEST_F(PopplerActionLayerFreeTest_2285, FreeNullPointerDoesNotCrash_2285) {
    // Should handle nullptr gracefully without crashing
    poppler_action_layer_free(nullptr);
    SUCCEED();
}

// Test freeing an action_layer with NULL layers list
TEST_F(PopplerActionLayerFreeTest_2285, FreeWithNullLayersList_2285) {
    PopplerActionLayer *action_layer = g_slice_new0(PopplerActionLayer);
    action_layer->layers = nullptr;

    // Should free the struct without issues when layers is NULL
    poppler_action_layer_free(action_layer);
    SUCCEED();
}

// Test freeing an action_layer with a non-empty layers list containing GObjects
TEST_F(PopplerActionLayerFreeTest_2285, FreeWithNonEmptyLayersList_2285) {
    PopplerActionLayer *action_layer = g_slice_new0(PopplerActionLayer);

    // Create GObject instances and add them to the list
    // We use g_object_new to create basic GObjects that can be unrefed
    GObject *obj1 = (GObject *)g_object_new(G_TYPE_OBJECT, nullptr);
    GObject *obj2 = (GObject *)g_object_new(G_TYPE_OBJECT, nullptr);

    action_layer->layers = nullptr;
    action_layer->layers = g_list_append(action_layer->layers, obj1);
    action_layer->layers = g_list_append(action_layer->layers, obj2);

    // Should free the list and all objects without issues
    poppler_action_layer_free(action_layer);
    SUCCEED();
}

// Test freeing an action_layer with a single element in layers list
TEST_F(PopplerActionLayerFreeTest_2285, FreeWithSingleElementLayersList_2285) {
    PopplerActionLayer *action_layer = g_slice_new0(PopplerActionLayer);

    GObject *obj = (GObject *)g_object_new(G_TYPE_OBJECT, nullptr);
    action_layer->layers = nullptr;
    action_layer->layers = g_list_append(action_layer->layers, obj);

    poppler_action_layer_free(action_layer);
    SUCCEED();
}

// Test freeing an action_layer with an empty GList (edge case)
TEST_F(PopplerActionLayerFreeTest_2285, FreeWithEmptyGList_2285) {
    PopplerActionLayer *action_layer = g_slice_new0(PopplerActionLayer);
    // layers is NULL (empty list in GList terms)
    action_layer->layers = nullptr;

    poppler_action_layer_free(action_layer);
    SUCCEED();
}

// Test that objects in the layers list are properly unreffed
TEST_F(PopplerActionLayerFreeTest_2285, ObjectsInLayersAreUnreffed_2285) {
    PopplerActionLayer *action_layer = g_slice_new0(PopplerActionLayer);

    GObject *obj = (GObject *)g_object_new(G_TYPE_OBJECT, nullptr);
    // Add an extra ref so we can check if unref was called
    g_object_ref(obj);
    // Now refcount is 2

    action_layer->layers = nullptr;
    action_layer->layers = g_list_append(action_layer->layers, obj);

    poppler_action_layer_free(action_layer);

    // After free, one unref should have been called, leaving refcount at 1
    // We should be able to unref it one more time without issues
    EXPECT_EQ(G_OBJECT(obj)->ref_count, 1u);
    g_object_unref(obj);
    SUCCEED();
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
