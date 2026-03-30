#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-document.cc"

#include "OptionalContent.h"



// Mock class for OptionalContentGroup

class MockOptionalContentGroup : public OptionalContentGroup {

public:

    using OptionalContentGroup::OptionalContentGroup;

    MOCK_METHOD(const GooString*, getName, (), (const, override));

    MOCK_METHOD(Ref, getRef, (), (const, override));

    MOCK_METHOD(void, setRef, (Ref ref), (override));

    MOCK_METHOD(State, getState, (), (const, override));

    MOCK_METHOD(void, setState, (State state), (override));

    MOCK_METHOD(UsageState, getViewState, (), (const, override));

    MOCK_METHOD(UsageState, getPrintState, (), (const, override));

};



class LayerTest_2238 : public ::testing::Test {

protected:

    MockOptionalContentGroup mockOc;

    Layer* layer;



    void SetUp() override {

        layer = layer_new(&mockOc);

    }



    void TearDown() override {

        g_slice_free(Layer, layer);

    }

};



TEST_F(LayerTest_2238, LayerCreationWithNullPtr_2238) {

    Layer* nullLayer = layer_new(nullptr);

    EXPECT_EQ(nullLayer->oc, nullptr);

    g_slice_free(Layer, nullLayer);

}



TEST_F(LayerTest_2238, LayerCreationWithValidOptionalContentGroup_2238) {

    EXPECT_NE(layer->oc, nullptr);

    EXPECT_EQ(layer->oc, &mockOc);

}



TEST_F(LayerTest_2238, LayerLabelInitialization_2238) {

    EXPECT_EQ(layer->label, nullptr);

}
