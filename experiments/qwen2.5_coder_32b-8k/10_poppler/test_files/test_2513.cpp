#include <gtest/gtest.h>

#include "poppler-layer.h"

#include "poppler-private.h"



// Mocking external collaborators if needed (not required in this case)



class PopplerLayerTest_2513 : public ::testing::Test {

protected:

    void SetUp() override {

        poppler_layer = static_cast<PopplerLayer*>(g_slice_alloc(sizeof(PopplerLayer)));

        // Initialize rbgroup to a default value

        poppler_layer->rbgroup = reinterpret_cast<int*>(42);  // Example group ID

    }



    void TearDown() override {

        g_slice_free1(sizeof(PopplerLayer), poppler_layer);

    }



    PopplerLayer* poppler_layer;

};



TEST_F(PopplerLayerTest_2513, GetRadioButtonGroupId_ReturnsCorrectId_2513) {

    EXPECT_EQ(poppler_layer_get_radio_button_group_id(poppler_layer), 42);

}



TEST_F(PopplerLayerTest_2513, GetRadioButtonGroupId_NullPointer_ReturnsFalse_2513) {

    EXPECT_EQ(poppler_layer_get_radio_button_group_id(nullptr), FALSE);

}



TEST_F(PopplerLayerTest_2513, GetRadioButtonGroupId_ZeroRbgroup_ReturnsZero_2513) {

    poppler_layer->rbgroup = reinterpret_cast<int*>(0);

    EXPECT_EQ(poppler_layer_get_radio_button_group_id(poppler_layer), 0);

}



TEST_F(PopplerLayerTest_2513, GetRadioButtonGroupId_NegativeRbgroup_ReturnsNegativeValue_2513) {

    poppler_layer->rbgroup = reinterpret_cast<int*>(-1);

    EXPECT_EQ(poppler_layer_get_radio_button_group_id(poppler_layer), -1);

}
