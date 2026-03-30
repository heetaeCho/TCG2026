#include <gtest/gtest.h>

#include "PDFDoc.h"

#include "Catalog.h"



class PDFDocTest_994 : public ::testing::Test {

protected:

    std::unique_ptr<MockCatalog> mockCatalog;

    std::unique_ptr<PDFDoc> pdfDoc;



    class MockCatalog : public Catalog {

    public:

        MOCK_CONST_METHOD0(getPDFMajorVersion, int());

    };



    PDFDocTest_994() : mockCatalog(new MockCatalog(nullptr)), pdfDoc(new PDFDoc()) {

        pdfDoc->catalog = mockCatalog.get();

    }

};



TEST_F(PDFDocTest_994, GetPDFMajorVersion_NormalOperation_994) {

    EXPECT_CALL(*mockCatalog, getPDFMajorVersion()).WillOnce(testing::Return(1));

    EXPECT_EQ(pdfDoc->getPDFMajorVersion(), 1);

}



TEST_F(PDFDocTest_994, GetPDFMajorVersion_HeaderVersionGreater_CatalogVersionLess_994) {

    pdfDoc->headerPdfMajorVersion = 2;

    EXPECT_CALL(*mockCatalog, getPDFMajorVersion()).WillOnce(testing::Return(1));

    EXPECT_EQ(pdfDoc->getPDFMajorVersion(), 2);

}



TEST_F(PDFDocTest_994, GetPDFMajorVersion_HeaderVersionLess_CatalogVersionGreater_994) {

    pdfDoc->headerPdfMajorVersion = 1;

    EXPECT_CALL(*mockCatalog, getPDFMajorVersion()).WillOnce(testing::Return(2));

    EXPECT_EQ(pdfDoc->getPDFMajorVersion(), 2);

}



TEST_F(PDFDocTest_994, GetPDFMajorVersion_HeaderVersionEqual_CatalogVersionEqual_994) {

    pdfDoc->headerPdfMajorVersion = 1;

    EXPECT_CALL(*mockCatalog, getPDFMajorVersion()).WillOnce(testing::Return(1));

    EXPECT_EQ(pdfDoc->getPDFMajorVersion(), 1);

}



TEST_F(PDFDocTest_994, GetPDFMajorVersion_HeaderVersionNegative_CatalogVersionPositive_994) {

    pdfDoc->headerPdfMajorVersion = -1;

    EXPECT_CALL(*mockCatalog, getPDFMajorVersion()).WillOnce(testing::Return(1));

    EXPECT_EQ(pdfDoc->getPDFMajorVersion(), 1);

}



TEST_F(PDFDocTest_994, GetPDFMajorVersion_HeaderVersionPositive_CatalogVersionNegative_994) {

    pdfDoc->headerPdfMajorVersion = 1;

    EXPECT_CALL(*mockCatalog, getPDFMajorVersion()).WillOnce(testing::Return(-1));

    EXPECT_EQ(pdfDoc->getPDFMajorVersion(), 1);

}



TEST_F(PDFDocTest_994, GetPDFMajorVersion_HeaderVersionNegative_CatalogVersionNegative_994) {

    pdfDoc->headerPdfMajorVersion = -1;

    EXPECT_CALL(*mockCatalog, getPDFMajorVersion()).WillOnce(testing::Return(-1));

    EXPECT_EQ(pdfDoc->getPDFMajorVersion(), -1);

}
