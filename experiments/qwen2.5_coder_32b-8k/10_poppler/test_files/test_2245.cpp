#include <gtest/gtest.h>

#include "poppler-document.cc"

#include "poppler-private.h"



class PopplerDocumentLayersTest : public ::testing::Test {

protected:

    void SetUp() override {

        document = new PopplerDocument();

        document->layers = nullptr;

        document->layers_rbgroups = nullptr;

    }



    void TearDown() override {

        poppler_document_layers_free(document);

        delete document;

    }



    PopplerDocument* document;

};



TEST_F(PopplerDocumentLayersTest_NormalOperation_2245, FreeNullLayers_2245) {

    // Given: layers and layers_rbgroups are nullptr

    // When: calling poppler_document_layers_free

    poppler_document_layers_free(document);

    // Then: no crash should occur, and pointers remain nullptr

    EXPECT_EQ(document->layers, nullptr);

    EXPECT_EQ(document->layers_rbgroups, nullptr);

}



TEST_F(PopplerDocumentLayersTest_NormalOperation_2245, FreeNonEmptyLayers_2245) {

    // Given: layers and layers_rbgroups are non-empty

    document->layers = g_list_append(document->layers, new int(1));

    document->layers_rbgroups = g_list_append(document->layers_rbgroups, new GList());



    // When: calling poppler_document_layers_free

    poppler_document_layers_free(document);



    // Then: layers and layers_rbgroups should be freed and set to nullptr

    EXPECT_EQ(document->layers, nullptr);

    EXPECT_EQ(document->layers_rbgroups, nullptr);

}



TEST_F(PopplerDocumentLayersTest_BoundaryConditions_2245, FreeSingleLayer_2245) {

    // Given: a single layer in layers list

    document->layers = g_list_append(document->layers, new int(1));



    // When: calling poppler_document_layers_free

    poppler_document_layers_free(document);



    // Then: the layer should be freed and set to nullptr

    EXPECT_EQ(document->layers, nullptr);

}



TEST_F(PopplerDocumentLayersTest_BoundaryConditions_2245, FreeSingleRBGroup_2245) {

    // Given: a single rbgroup in layers_rbgroups list

    document->layers_rbgroups = g_list_append(document->layers_rbgroups, new GList());



    // When: calling poppler_document_layers_free

    poppler_document_layers_free(document);



    // Then: the rbgroup should be freed and set to nullptr

    EXPECT_EQ(document->layers_rbgroups, nullptr);

}
