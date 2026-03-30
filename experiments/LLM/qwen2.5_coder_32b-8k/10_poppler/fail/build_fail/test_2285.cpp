#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-action.h"



// Mocking g_list_free_full and g_object_unref for external interactions

using ::testing::_;

using ::testing::InvokeWithoutArgs;



extern "C" {

    GList* g_list_free_full(GList* list, GDestroyNotify free_func) {

        // Simulate freeing the list

        return nullptr;

    }



    void g_object_unref(gpointer object) {

        // Simulate unrefing the object

    }

}



class PopplerActionLayerTest_2285 : public ::testing::Test {

protected:

    void SetUp() override {

        action_layer = static_cast<PopplerActionLayer*>(g_slice_alloc(sizeof(PopplerActionLayer)));

        action_layer->layers = nullptr;

    }



    void TearDown() override {

        poppler_action_layer_free(action_layer);

    }



    PopplerActionLayer* action_layer;

};



TEST_F(PopplerActionLayerTest_2285, FreeNullPointer_2285) {

    // Test freeing a null pointer

    poppler_action_layer_free(nullptr);

}



TEST_F(PopplerActionLayerTest_2285, FreeWithoutLayers_2285) {

    // Test freeing an action layer without layers

    poppler_action_layer_free(action_layer);

}



TEST_F(PopplerActionLayerTest_2285, FreeWithLayers_2285) {

    // Test freeing an action layer with layers

    action_layer->layers = reinterpret_cast<int*>(g_list_append(nullptr, GINT_TO_POINTER(1)));

    poppler_action_layer_free(action_layer);

}
