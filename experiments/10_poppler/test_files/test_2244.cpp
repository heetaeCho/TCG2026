#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-document.cc"

#include "Catalog.h"



using namespace testing;



class MockPDFDoc : public PDFDoc {

public:

    MOCK_METHOD(Catalog*, getCatalog, (), (const));

};



class MockCatalog : public Catalog {

public:

    using Catalog::Catalog;

    MOCK_METHOD(const OCGs *, getOptContentConfig, (), (const));

};



class PopplerDocumentTest_2244 : public ::testing::Test {

protected:

    void SetUp() override {

        document = new PopplerDocument();

        mock_pdf_doc = std::make_unique<MockPDFDoc>();

        mock_catalog = std::make_unique<MockCatalog>(mock_pdf_doc.get());

        document->doc = mock_pdf_doc.get();



        EXPECT_CALL(*mock_pdf_doc, getCatalog())

            .WillRepeatedly(Return(mock_catalog.get()));

    }



    void TearDown() override {

        delete document;

    }



    PopplerDocument *document;

    std::unique_ptr<MockPDFDoc> mock_pdf_doc;

    std::unique_ptr<MockCatalog> mock_catalog;

};



TEST_F(PopplerDocumentTest_2244, LayersNullWhenOCGIsNull_2244) {

    EXPECT_CALL(*mock_catalog, getOptContentConfig())

        .WillOnce(Return(nullptr));



    GList *layers = _poppler_document_get_layers(document);

    ASSERT_EQ(layers, nullptr);

}



TEST_F(PopplerDocumentTest_2244, LayersNotNullWhenOCGIsNotNull_2244) {

    const OCGs *mock_ocgs = new OCGs();

    EXPECT_CALL(*mock_catalog, getOptContentConfig())

        .WillOnce(Return(mock_ocgs));



    GList *layers = _poppler_document_get_layers(document);

    ASSERT_NE(layers, nullptr);



    g_list_free(layers); // Clean up the list

}



TEST_F(PopplerDocumentTest_2244, LayersMemoizedAfterFirstCall_2244) {

    const OCGs *mock_ocgs = new OCGs();

    EXPECT_CALL(*mock_catalog, getOptContentConfig())

        .WillOnce(Return(mock_ocgs));



    GList *layers_first_call = _poppler_document_get_layers(document);

    GList *layers_second_call = _poppler_document_get_layers(document);



    ASSERT_EQ(layers_first_call, layers_second_call);



    g_list_free(layers_first_call); // Clean up the list

}



TEST_F(PopplerDocumentTest_2244, LayersRBGroupsInitializedWhenOCGIsNotNull_2244) {

    const OCGs *mock_ocgs = new OCGs();

    EXPECT_CALL(*mock_catalog, getOptContentConfig())

        .WillOnce(Return(mock_ocgs));



    _poppler_document_get_layers(document);

    ASSERT_NE(document->layers_rbgroups, nullptr);



    delete[] document->layers_rbgroups; // Clean up the array

}



TEST_F(PopplerDocumentTest_2244, LayersRBGroupsNotReinitializedOnSubsequentCalls_2244) {

    const OCGs *mock_ocgs = new OCGs();

    EXPECT_CALL(*mock_catalog, getOptContentConfig())

        .WillOnce(Return(mock_ocgs));



    _poppler_document_get_layers(document);

    int *first_call_rbgroups = document->layers_rbgroups;



    _poppler_document_get_layers(document);

    int *second_call_rbgroups = document->layers_rbgroups;



    ASSERT_EQ(first_call_rbgroups, second_call_rbgroups);



    delete[] first_call_rbgroups; // Clean up the array

}
