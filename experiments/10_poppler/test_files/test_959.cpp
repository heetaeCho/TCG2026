#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/PDFDoc.h"

#include "TestProjects/poppler/poppler/Catalog.h"

#include <memory>



using namespace std;



class PDFDocTest_959 : public ::testing::Test {

protected:

    PDFDocTest_959() {

        // Mock Catalog and set it to PDFDoc

        catalogMock = make_unique<testing::StrictMock<Catalog>>(nullptr);

        pdfDoc.catalog = catalogMock.get();

    }



    ~PDFDocTest_959() override {

        pdfDoc.catalog = nullptr;

    }



    PDFDoc pdfDoc;

    unique_ptr<Catalog> catalogMock;

};



TEST_F(PDFDocTest_959, ReadMetadata_ReturnsNonNullPtr_959) {

    EXPECT_CALL(*catalogMock, readMetadata()).WillOnce(testing::Return(make_unique<GooString>("Sample Metadata")));

    auto result = pdfDoc.readMetadata();

    ASSERT_NE(result.get(), nullptr);

}



TEST_F(PDFDocTest_959, ReadMetadata_ReturnsEmptyGooString_959) {

    EXPECT_CALL(*catalogMock, readMetadata()).WillOnce(testing::Return(make_unique<GooString>("")));

    auto result = pdfDoc.readMetadata();

    ASSERT_EQ(result->getCString(), "");

}



TEST_F(PDFDocTest_959, ReadMetadata_ReturnsValidGooString_959) {

    EXPECT_CALL(*catalogMock, readMetadata()).WillOnce(testing::Return(make_unique<GooString>("Valid Metadata")));

    auto result = pdfDoc.readMetadata();

    ASSERT_STREQ(result->getCString(), "Valid Metadata");

}
