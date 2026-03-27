#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-document.cc"

#include "poppler-private.h"



using namespace testing;



class PopplerDocumentTest : public ::testing::Test {

protected:

    void SetUp() override {

        document = new PopplerDocument();

        layer = new Layer();

        group1 = g_list_alloc();

        group2 = g_list_alloc();

        otherLayerOC = (OptionalContentGroup*)0x1; // Just a dummy pointer for testing

    }



    void TearDown() override {

        g_list_free(group1);

        g_list_free(group2);

        delete layer;

        delete document;

    }



    PopplerDocument* document;

    Layer* layer;

    GList* group1;

    GList* group2;

    OptionalContentGroup* otherLayerOC;

};



TEST_F(PopplerDocumentTest_2241, LayerInFirstGroup_2241) {

    layer->oc = (OptionalContentGroup*)0x2; // Dummy pointer for testing

    group1->data = g_list_append(nullptr, layer->oc);

    document->layers_rbgroups = g_list_prepend(nullptr, group1);



    EXPECT_EQ(_poppler_document_get_layer_rbgroup(document, layer), group1);

}



TEST_F(PopplerDocumentTest_2241, LayerInSecondGroup_2241) {

    layer->oc = (OptionalContentGroup*)0x3; // Dummy pointer for testing

    group1->data = g_list_append(nullptr, otherLayerOC);

    group2->data = g_list_append(nullptr, layer->oc);

    document->layers_rbgroups = g_list_prepend(document->layers_rbgroups, group2);

    document->layers_rbgroups = g_list_prepend(document->layers_rbgroups, group1);



    EXPECT_EQ(_poppler_document_get_layer_rbgroup(document, layer), group2);

}



TEST_F(PopplerDocumentTest_2241, LayerNotInAnyGroup_2241) {

    layer->oc = (OptionalContentGroup*)0x4; // Dummy pointer for testing

    group1->data = g_list_append(nullptr, otherLayerOC);

    document->layers_rbgroups = g_list_prepend(document->layers_rbgroups, group1);



    EXPECT_EQ(_poppler_document_get_layer_rbgroup(document, layer), nullptr);

}



TEST_F(PopplerDocumentTest_2241, EmptyGroupsList_2241) {

    layer->oc = (OptionalContentGroup*)0x5; // Dummy pointer for testing

    document->layers_rbgroups = nullptr;



    EXPECT_EQ(_poppler_document_get_layer_rbgroup(document, layer), nullptr);

}



TEST_F(PopplerDocumentTest_2241, LayerInEmptyGroup_2241) {

    layer->oc = (OptionalContentGroup*)0x6; // Dummy pointer for testing

    group1->data = nullptr;

    document->layers_rbgroups = g_list_prepend(document->layers_rbgroups, group1);



    EXPECT_EQ(_poppler_document_get_layer_rbgroup(document, layer), nullptr);

}
