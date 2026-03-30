#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-document.h"



// Mocking external dependencies if necessary

class MockPopplerDocument : public PopplerDocument {

public:

    MOCK_METHOD(GList*, _get_layers, (), (const));

};



TEST(PopplerLayersIterTest_2248, NewReturnsNullptrWhenNoLayers_2248) {

    // Arrange

    MockPopplerDocument mock_document;

    EXPECT_CALL(mock_document, _get_layers()).WillOnce(testing::Return(nullptr));



    // Act

    PopplerLayersIter* iter = poppler_layers_iter_new(&mock_document);



    // Assert

    EXPECT_EQ(iter, nullptr);

}



TEST(PopplerLayersIterTest_2248, NewCreatesIteratorWhenLayersExist_2248) {

    // Arrange

    MockPopplerDocument mock_document;

    GList* mock_items = g_list_prepend(nullptr, reinterpret_cast<gpointer>(1));

    EXPECT_CALL(mock_document, _get_layers()).WillOnce(testing::Return(mock_items));



    // Act

    PopplerLayersIter* iter = poppler_layers_iter_new(&mock_document);



    // Assert

    EXPECT_NE(iter, nullptr);

    g_list_free(mock_items);

    g_slice_free(PopplerLayersIter, iter);

}



TEST(PopplerLayersIterTest_2248, NewIncreasesDocumentReferenceCount_2248) {

    // Arrange

    MockPopplerDocument mock_document;

    GList* mock_items = g_list_prepend(nullptr, reinterpret_cast<gpointer>(1));

    EXPECT_CALL(mock_document, _get_layers()).WillOnce(testing::Return(mock_items));



    // Act

    PopplerLayersIter* iter = poppler_layers_iter_new(&mock_document);



    // Assert

    EXPECT_EQ(G_OBJECT_REF_COUNT(&mock_document), 2);

    g_list_free(mock_items);

    g_slice_free(PopplerLayersIter, iter);

}



TEST(PopplerLayersIterTest_2248, NewHandlesEmptyListCorrectly_2248) {

    // Arrange

    MockPopplerDocument mock_document;

    GList* mock_items = nullptr; // empty list

    EXPECT_CALL(mock_document, _get_layers()).WillOnce(testing::Return(mock_items));



    // Act

    PopplerLayersIter* iter = poppler_layers_iter_new(&mock_document);



    // Assert

    EXPECT_EQ(iter, nullptr);

}
