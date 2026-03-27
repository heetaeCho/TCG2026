#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "PDFDoc.h"

#include "Catalog.h"



using namespace testing;



class PDFDocTest : public ::testing::Test {

protected:

    MockCatalog* mock_catalog;

    PDFDoc pdf_doc;



    class MockCatalog : public Catalog {

    public:

        MOCK_CONST_METHOD0(getPDFMajorVersion, int());

        MOCK_CONST_METHOD0(getPDFMinorVersion, int());



        MockCatalog(PDFDoc* doc) : Catalog(doc) {}

    };



    PDFDocTest() : mock_catalog(new MockCatalog(nullptr)), pdf_doc(*mock_catalog) {

        pdf_doc.catalog = mock_catalog;

    }



    ~PDFDocTest() override {

        delete mock_catalog;

    }

};



TEST_F(PDFDocTest_995, GetPDFMinorVersion_NormalOperation_995) {

    EXPECT_CALL(*mock_catalog, getPDFMajorVersion()).WillOnce(Return(1));

    EXPECT_CALL(*mock_catalog, getPDFMinorVersion()).WillOnce(Return(7));



    pdf_doc.headerPdfMajorVersion = 1;

    pdf_doc.headerPdfMinorVersion = 4;



    int result = pdf_doc.getPDFMinorVersion();

    EXPECT_EQ(result, 7);

}



TEST_F(PDFDocTest_995, GetPDFMinorVersion_HeaderGreater_995) {

    EXPECT_CALL(*mock_catalog, getPDFMajorVersion()).WillOnce(Return(1));

    EXPECT_CALL(*mock_catalog, getPDFMinorVersion()).WillOnce(Return(4));



    pdf_doc.headerPdfMajorVersion = 2;

    pdf_doc.headerPdfMinorVersion = 3;



    int result = pdf_doc.getPDFMinorVersion();

    EXPECT_EQ(result, 3);

}



TEST_F(PDFDocTest_995, GetPDFMinorVersion_EqualVersions_995) {

    EXPECT_CALL(*mock_catalog, getPDFMajorVersion()).WillOnce(Return(1));

    EXPECT_CALL(*mock_catalog, getPDFMinorVersion()).WillOnce(Return(7));



    pdf_doc.headerPdfMajorVersion = 1;

    pdf_doc.headerPdfMinorVersion = 7;



    int result = pdf_doc.getPDFMinorVersion();

    EXPECT_EQ(result, 7);

}



TEST_F(PDFDocTest_995, GetPDFMinorVersion_HeaderMinorGreater_995) {

    EXPECT_CALL(*mock_catalog, getPDFMajorVersion()).WillOnce(Return(1));

    EXPECT_CALL(*mock_catalog, getPDFMinorVersion()).WillOnce(Return(4));



    pdf_doc.headerPdfMajorVersion = 1;

    pdf_doc.headerPdfMinorVersion = 8;



    int result = pdf_doc.getPDFMinorVersion();

    EXPECT_EQ(result, 8);

}



TEST_F(PDFDocTest_995, GetPDFMinorVersion_CatalogGreaterHeader_995) {

    EXPECT_CALL(*mock_catalog, getPDFMajorVersion()).WillOnce(Return(2));

    EXPECT_CALL(*mock_catalog, getPDFMinorVersion()).WillOnce(Return(3));



    pdf_doc.headerPdfMajorVersion = 1;

    pdf_doc.headerPdfMinorVersion = 4;



    int result = pdf_doc.getPDFMinorVersion();

    EXPECT_EQ(result, 3);

}
