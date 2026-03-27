#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-layer.h"

#include "OptionalContent.h"

#include "poppler-private.h"



using namespace testing;



class PopplerLayerTest_2507 : public ::testing::Test {

protected:

    void SetUp() override {

        document = POPPLER_DOCUMENT(g_object_new(POPPLER_TYPE_DOCUMENT, nullptr));

        gooStringMock = new GooString("test_layer_name");

        layer = new Layer();

        layer->oc = new OptionalContentGroup(nullptr);

        ON_CALL(*layer->oc, getName()).WillByDefault(Return(gooStringMock));



        EXPECT_CALL(*layer->oc, getName()).Times(AtLeast(1));

    }



    void TearDown() override {

        g_object_unref(document);

        delete layer->oc;

        delete layer;

        delete gooStringMock;

    }



    PopplerDocument *document;

    Layer *layer;

    GooString *gooStringMock;

};



TEST_F(PopplerLayerTest_2507, CreatePopplerLayerWithValidParameters_2507) {

    GList *rbgroup = nullptr; // Assuming rbgroup can be null

    PopplerLayer *poppler_layer = _poppler_layer_new(document, layer, rbgroup);

    EXPECT_NE(poppler_layer, nullptr);

    EXPECT_EQ(poppler_layer->document, document);

    EXPECT_EQ(poppler_layer->layer, layer);

    EXPECT_STREQ(poppler_layer->title, "test_layer_name");

    g_object_unref(poppler_layer);

}



TEST_F(PopplerLayerTest_2507, CreatePopplerLayerWithNullDocument_2507) {

    GList *rbgroup = nullptr; // Assuming rbgroup can be null

    PopplerLayer *poppler_layer = _poppler_layer_new(nullptr, layer, rbgroup);

    EXPECT_EQ(poppler_layer, nullptr);

}



TEST_F(PopplerLayerTest_2507, CreatePopplerLayerWithNullLayer_2507) {

    GList *rbgroup = nullptr; // Assuming rbgroup can be null

    PopplerLayer *poppler_layer = _poppler_layer_new(document, nullptr, rbgroup);

    EXPECT_EQ(poppler_layer, nullptr);

}



TEST_F(PopplerLayerTest_2507, CreatePopplerLayerWithNullLayerName_2507) {

    GList *rbgroup = nullptr; // Assuming rbgroup can be null

    ON_CALL(*layer->oc, getName()).WillByDefault(Return(nullptr));

    PopplerLayer *poppler_layer = _poppler_layer_new(document, layer, rbgroup);

    EXPECT_NE(poppler_layer, nullptr);

    EXPECT_EQ(poppler_layer->document, document);

    EXPECT_EQ(poppler_layer->layer, layer);

    EXPECT_EQ(poppler_layer->title, nullptr);

    g_object_unref(poppler_layer);

}



TEST_F(PopplerLayerTest_2507, CreatePopplerLayerWithNonEmptyRBGroup_2507) {

    GList *rbgroup = (GList *)g_slist_append(nullptr, "test_rbgroup");

    PopplerLayer *poppler_layer = _poppler_layer_new(document, layer, rbgroup);

    EXPECT_NE(poppler_layer, nullptr);

    EXPECT_EQ(poppler_layer->document, document);

    EXPECT_EQ(poppler_layer->layer, layer);

    EXPECT_STREQ(poppler_layer->title, "test_layer_name");

    g_object_unref(poppler_layer);

    g_slist_free_full(rbgroup, g_free);

}
