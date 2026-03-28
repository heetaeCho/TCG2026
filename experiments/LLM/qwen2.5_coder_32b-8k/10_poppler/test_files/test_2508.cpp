#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/poppler/glib/poppler-layer.h"

#include "./TestProjects/poppler/glib/poppler-private.h"



class PopplerLayerTest_2508 : public ::testing::Test {

protected:

    Layer mock_layer;

    int mock_rbgroup;

    _PopplerLayer poppler_layer;



    void SetUp() override {

        poppler_layer.layer = &mock_layer;

        poppler_layer.rbgroup = &mock_rbgroup;

        poppler_layer.title = "Sample Title";

    }

};



TEST_F(PopplerLayerTest_2508, GetTitleReturnsCorrectTitle_2508) {

    const gchar* result = poppler_layer_get_title(reinterpret_cast<PopplerLayer*>(&poppler_layer));

    EXPECT_STREQ(result, "Sample Title");

}



TEST_F(PopplerLayerTest_2508, GetTitleNullWhenInvalidLayer_2508) {

    PopplerLayer* invalid_poppler_layer = nullptr;

    const gchar* result = poppler_layer_get_title(invalid_poppler_layer);

    EXPECT_EQ(result, nullptr);

}
