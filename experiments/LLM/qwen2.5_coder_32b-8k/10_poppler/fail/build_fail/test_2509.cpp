#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-layer.h"

#include "OptionalContent.h"



using ::testing::Return;



class PopplerLayerTest : public ::testing::Test {

protected:

    OptionalContentGroup* mock_oc_group;

    Layer* layer;

    _PopplerLayer* poppler_layer;



    void SetUp() override {

        mock_oc_group = new OptionalContentGroup(nullptr);

        layer = new Layer();

        layer->oc = mock_oc_group;

        poppler_layer = new _PopplerLayer();

        poppler_layer->layer = layer;

    }



    void TearDown() override {

        delete poppler_layer->layer->oc;

        delete poppler_layer->layer;

        delete poppler_layer;

    }

};



TEST_F(PopplerLayerTest_2509, LayerInitiallyInvisible_2509) {

    EXPECT_CALL(*mock_oc_group, getState()).WillOnce(Return(OptionalContentGroup::Off));

    EXPECT_FALSE(poppler_layer_is_visible(poppler_layer));

}



TEST_F(PopplerLayerTest_2509, LayerVisibleAfterStateChange_2509) {

    EXPECT_CALL(*mock_oc_group, getState()).WillOnce(Return(OptionalContentGroup::On));

    EXPECT_TRUE(poppler_layer_is_visible(poppler_layer));

}



TEST_F(PopplerLayerTest_2509, LayerInitiallyOff_2509) {

    EXPECT_CALL(*mock_oc_group, getState()).WillOnce(Return(OptionalContentGroup::Off));

    EXPECT_FALSE(poppler_layer_is_visible(poppler_layer));

}



TEST_F(PopplerLayerTest_2509, LayerVisibleWhenStateIsOn_2509) {

    EXPECT_CALL(*mock_oc_group, getState()).WillOnce(Return(OptionalContentGroup::On));

    EXPECT_TRUE(poppler_layer_is_visible(poppler_layer));

}



TEST_F(PopplerLayerTest_2509, LayerInvisibleWithNullOptionalContentGroup_2509) {

    poppler_layer->layer->oc = nullptr;

    EXPECT_FALSE(poppler_layer_is_visible(poppler_layer));

}
