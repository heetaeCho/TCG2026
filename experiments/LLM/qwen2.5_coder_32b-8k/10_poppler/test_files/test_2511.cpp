#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler/glib/poppler-layer.h"

#include "poppler/poppler/OptionalContent.h"



using ::testing::Return;



// Mock class for OptionalContentGroup to simulate its behavior

class MockOptionalContentGroup : public OptionalContentGroup {

public:

    MOCK_METHOD(State, getState, (), (const));

    MOCK_METHOD(void, setState, (State state), ());

};



// Test fixture for PopplerLayer tests

class PopplerLayerTest_2511 : public ::testing::Test {

protected:

    void SetUp() override {

        mock_ocg = new MockOptionalContentGroup();

        layer = new Layer{nullptr, mock_ocg};

        poppler_layer = reinterpret_cast<PopplerLayer*>(layer);

    }



    void TearDown() override {

        delete poppler_layer;

        delete mock_ocg;

    }



    MockOptionalContentGroup* mock_ocg;

    Layer* layer;

    PopplerLayer* poppler_layer;

};



// Test that hide does nothing when state is already Off

TEST_F(PopplerLayerTest_2511, HideDoesNothingWhenAlreadyOff_2511) {

    EXPECT_CALL(*mock_ocg, getState()).WillOnce(Return(OptionalContentGroup::Off));

    EXPECT_CALL(*mock_ocg, setState(_)).Times(0);



    poppler_layer_hide(poppler_layer);

}



// Test that hide sets state to Off when state is On

TEST_F(PopplerLayerTest_2511, HideSetsStateToOffWhenOn_2511) {

    EXPECT_CALL(*mock_ocg, getState()).WillOnce(Return(OptionalContentGroup::On));

    EXPECT_CALL(*mock_ocg, setState(OptionalContentGroup::Off)).Times(1);



    poppler_layer_hide(poppler_layer);

}



// Test that hide sets state to Off when state is Toggle

TEST_F(PopplerLayerTest_2511, HideSetsStateToOffWhenToggle_2511) {

    EXPECT_CALL(*mock_ocg, getState()).WillOnce(Return(OptionalContentGroup::Toggle));

    EXPECT_CALL(*mock_ocg, setState(OptionalContentGroup::Off)).Times(1);



    poppler_layer_hide(poppler_layer);

}
