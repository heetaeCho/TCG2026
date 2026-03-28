#include <gtest/gtest.h>

#include "poppler/glib/poppler-layer.h"

#include "poppler/OptionalContent.h"



// Mock OptionalContentGroup to verify state changes without modifying internal logic

class MockOptionalContentGroup : public OptionalContentGroup {

public:

    using OptionalContentGroup::OptionalContentGroup;

    MOCK_METHOD(void, setState, (State state), (override));

    MOCK_CONST_METHOD0(getState, State());

};



class PopplerLayerTest_2510 : public ::testing::Test {

protected:

    void SetUp() override {

        layer = new Layer();

        poppler_layer = new _PopplerLayer();

        mock_ocg_on = new MockOptionalContentGroup(nullptr);

        mock_ocg_off = new MockOptionalContentGroup(nullptr);



        layer->oc = mock_ocg_on;

        poppler_layer->layer = layer;



        // Simulate rbgroup with one other OCG

        GList* l1 = g_list_alloc();

        l1->data = mock_ocg_off;

        poppler_layer->rbgroup = l1;

    }



    void TearDown() override {

        g_list_free(poppler_layer->rbgroup);

        delete layer;

        delete poppler_layer;

        delete mock_ocg_on;

        delete mock_ocg_off;

    }



    Layer* layer;

    _PopplerLayer* poppler_layer;

    MockOptionalContentGroup* mock_ocg_on;

    MockOptionalContentGroup* mock_ocg_off;

};



TEST_F(PopplerLayerTest_2510, LayerAlreadyShown_2510) {

    EXPECT_CALL(*mock_ocg_on, getState()).WillOnce(testing::Return(OptionalContentGroup::On));

    EXPECT_CALL(*mock_ocg_on, setState(_)).Times(0);

    EXPECT_CALL(*mock_ocg_off, setState(_)).Times(0);



    poppler_layer_show(poppler_layer);

}



TEST_F(PopplerLayerTest_2510, LayerShownFromOff_2510) {

    EXPECT_CALL(*mock_ocg_on, getState()).WillOnce(testing::Return(OptionalContentGroup::Off));

    EXPECT_CALL(*mock_ocg_on, setState(OptionalContentGroup::On)).Times(1);

    EXPECT_CALL(*mock_ocg_off, setState(OptionalContentGroup::Off)).Times(1);



    poppler_layer_show(poppler_layer);

}



TEST_F(PopplerLayerTest_2510, LayerShownFromOtherState_2510) {

    EXPECT_CALL(*mock_ocg_on, getState()).WillOnce(testing::Return(OptionalContentGroup::ToggleOnAll));

    EXPECT_CALL(*mock_ocg_on, setState(OptionalContentGroup::On)).Times(1);

    EXPECT_CALL(*mock_ocg_off, setState(OptionalContentGroup::Off)).Times(1);



    poppler_layer_show(poppler_layer);

}



TEST_F(PopplerLayerTest_2510, MultipleOCGInRbgroup_2510) {

    MockOptionalContentGroup* mock_ocg_extra = new MockOptionalContentGroup(nullptr);

    GList* l2 = g_list_alloc();

    l2->data = mock_ocg_extra;

    poppler_layer->rbgroup = g_list_prepend(poppler_layer->rbgroup, l2);



    EXPECT_CALL(*mock_ocg_on, getState()).WillOnce(testing::Return(OptionalContentGroup::Off));

    EXPECT_CALL(*mock_ocg_on, setState(OptionalContentGroup::On)).Times(1);

    EXPECT_CALL(*mock_ocg_off, setState(OptionalContentGroup::Off)).Times(1);

    EXPECT_CALL(*mock_ocg_extra, setState(OptionalContentGroup::Off)).Times(1);



    poppler_layer_show(poppler_layer);



    g_list_free(poppler_layer->rbgroup);

    delete mock_ocg_extra;

}



TEST_F(PopplerLayerTest_2510, NullPointerHandling_2510) {

    layer->oc = nullptr;



    EXPECT_NO_THROW(poppler_layer_show(poppler_layer));

}
