#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-layer.h"

#include "poppler-private.h"



class PopplerLayerTest_2512 : public ::testing::Test {

protected:

    void SetUp() override {

        // Create a mock layer for testing

        poppler_layer = static_cast<PopplerLayer*>(g_malloc0(sizeof(PopplerLayer)));

        poppler_layer->layer = new Layer();

    }



    void TearDown() override {

        delete poppler_layer->layer;

        g_free(poppler_layer);

    }



    PopplerLayer* poppler_layer;

};



TEST_F(PopplerLayerTest_2512, IsParent_ReturnsFalse_WhenNoKids_2512) {

    // Arrange

    poppler_layer->layer->kids = nullptr;



    // Act & Assert

    EXPECT_FALSE(poppler_layer_is_parent(poppler_layer));

}



TEST_F(PopplerLayerTest_2512, IsParent_ReturnsTrue_WhenKidsExist_2512) {

    // Arrange

    poppler_layer->layer->kids = new std::vector<Layer*>();



    // Act & Assert

    EXPECT_TRUE(poppler_layer_is_parent(poppler_layer));



    // Cleanup

    delete poppler_layer->layer->kids;

}



TEST_F(PopplerLayerTest_2512, IsParent_ReturnsFalse_WhenNullPointerPassed_2512) {

    // Arrange & Act & Assert

    EXPECT_FALSE(poppler_layer_is_parent(nullptr));

}
