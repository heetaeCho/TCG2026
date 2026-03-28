#include <gtest/gtest.h>

#include "Catalog.h"

#include <memory>



class CatalogTest : public ::testing::Test {

protected:

    class MockPDFDoc {};

    std::unique_ptr<MockPDFDoc> mockPdfDoc;

    Catalog catalog;



    CatalogTest() : mockPdfDoc(std::make_unique<MockPDFDoc>()), catalog(mockPdfDoc.get()) {}

};



TEST_F(CatalogTest_677, GetAcroForm_ReturnsNonNullPointer_677) {

    EXPECT_NE(catalog.getAcroForm(), nullptr);

}



TEST_F(CatalogTest_677, GetAcroForm_ReturnsSameObjectOnRepeatedCalls_677) {

    Object* firstCall = catalog.getAcroForm();

    Object* secondCall = catalog.getAcroForm();

    EXPECT_EQ(firstCall, secondCall);

}
