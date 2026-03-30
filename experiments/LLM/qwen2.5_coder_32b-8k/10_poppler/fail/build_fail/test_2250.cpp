#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-document.h"



class PopplerLayersIterTest_2250 : public ::testing::Test {

protected:

    PopplerLayersIter *iter;



    void SetUp() override {

        iter = static_cast<PopplerLayersIter*>(malloc(sizeof(PopplerLayersIter)));

        memset(iter, 0, sizeof(PopplerLayersIter));

    }



    void TearDown() override {

        free(iter);

    }

};



TEST_F(PopplerLayersIterTest_2250, GetTitle_ReturnsNullWhenIterIsNull_2250) {

    gchar *title = poppler_layers_iter_get_title(nullptr);

    EXPECT_EQ(title, nullptr);

}



TEST_F(PopplerLayersIterTest_2250, GetTitle_ReturnsNullWhenNoLayerAtCurrentIndex_2250) {

    iter->items = nullptr;

    iter->index = 0;



    gchar *title = poppler_layers_iter_get_title(iter);

    EXPECT_EQ(title, nullptr);

}



TEST_F(PopplerLayersIterTest_2250, GetTitle_ReturnsCopiedLabelWhenLayerHasLabel_2250) {

    Layer layer;

    layer.label = const_cast<gchar*>("Sample Layer");



    iter->items = g_list_append(nullptr, &layer);

    iter->index = 0;



    gchar *title = poppler_layers_iter_get_title(iter);

    EXPECT_STREQ(title, "Sample Layer");

    g_free(title);

}



TEST_F(PopplerLayersIterTest_2250, GetTitle_ReturnsNullWhenLayerHasNoLabel_2250) {

    Layer layer;

    layer.label = nullptr;



    iter->items = g_list_append(nullptr, &layer);

    iter->index = 0;



    gchar *title = poppler_layers_iter_get_title(iter);

    EXPECT_EQ(title, nullptr);

}



TEST_F(PopplerLayersIterTest_2250, GetTitle_ReturnsNullWhenIndexIsOutOfRange_2250) {

    Layer layer;

    layer.label = const_cast<gchar*>("Sample Layer");



    iter->items = g_list_append(nullptr, &layer);

    iter->index = 1;



    gchar *title = poppler_layers_iter_get_title(iter);

    EXPECT_EQ(title, nullptr);

}
