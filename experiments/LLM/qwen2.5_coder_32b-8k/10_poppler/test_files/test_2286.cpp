#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-action.h"



// Assuming GList and g_object_ref are available in the testing environment



TEST(poppler_action_layer_copy_Test_2286, NormalOperation_2286) {

    // Arrange

    PopplerActionLayer original;

    original.action = POPPLER_ACTION_LAYER_ACTION_ADD;

    int layerData[] = {1, 2, 3};

    GList* layers = g_list_append(nullptr, &layerData[0]);

    layers = g_list_append(layers, &layerData[1]);

    layers = g_list_append(layers, &layerData[2]);

    original.layers = layers;



    // Act

    PopplerActionLayer* copy = poppler_action_layer_copy(&original);



    // Assert

    EXPECT_EQ(copy->action, original.action);

    EXPECT_EQ(g_list_length(copy->layers), g_list_length(original.layers));

    

    GList* origNode = original.layers;

    GList* copyNode = copy->layers;

    while (origNode != nullptr) {

        EXPECT_EQ(origNode->data, copyNode->data);

        origNode = origNode->next;

        copyNode = copyNode->next;

    }



    // Cleanup

    g_list_free_full(original.layers, g_object_unref);

    g_list_free_full(copy->layers, g_object_unref);

    g_slice_free(PopplerActionLayer, copy);

}



TEST(poppler_action_layer_copy_Test_2286, BoundaryConditions_EmptyLayers_2286) {

    // Arrange

    PopplerActionLayer original;

    original.action = POPPLER_ACTION_LAYER_ACTION_REMOVE;

    original.layers = nullptr;



    // Act

    PopplerActionLayer* copy = poppler_action_layer_copy(&original);



    // Assert

    EXPECT_EQ(copy->action, original.action);

    EXPECT_EQ(copy->layers, original.layers);  // Should be nullptr



    // Cleanup

    g_list_free_full(copy->layers, g_object_unref);

    g_slice_free(PopplerActionLayer, copy);

}



TEST(poppler_action_layer_copy_Test_2286, BoundaryConditions_SingleLayer_2286) {

    // Arrange

    PopplerActionLayer original;

    original.action = POPPLER_ACTION_LAYER_ACTION_TOGGLE;

    int layerData = 42;

    GList* layers = g_list_append(nullptr, &layerData);

    original.layers = layers;



    // Act

    PopplerActionLayer* copy = poppler_action_layer_copy(&original);



    // Assert

    EXPECT_EQ(copy->action, original.action);

    EXPECT_EQ(g_list_length(copy->layers), 1);

    EXPECT_EQ(copy->layers->data, original.layers->data);



    // Cleanup

    g_list_free_full(original.layers, g_object_unref);

    g_list_free_full(copy->layers, g_object_unref);

    g_slice_free(PopplerActionLayer, copy);

}
