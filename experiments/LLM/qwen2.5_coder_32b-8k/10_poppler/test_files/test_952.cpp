#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler/PDFDoc.h"

#include "poppler/Catalog.h"



using namespace testing;



class PDFDocTest : public ::testing::Test {

protected:

    MockCatalog* mockCatalog;

    std::unique_ptr<PDFDoc> pdfDoc;



    class MockCatalog : public Catalog {

    public:

        MOCK_CONST_METHOD0(getOptContentConfig, const OCGs*());

    };



    PDFDocTest() {

        mockCatalog = new MockCatalog(nullptr);

        pdfDoc = std::make_unique<PDFDoc>();

        pdfDoc->catalog = mockCatalog;

    }



    ~PDFDocTest() override {

        delete mockCatalog;

    }

};



TEST_F(PDFDocTest_952, GetOptContentConfig_ReturnsNonnullptr_952) {

    const OCGs* expectedOCGs = new OCGs();

    EXPECT_CALL(*mockCatalog, getOptContentConfig()).WillOnce(Return(expectedOCGs));



    const OCGs* result = pdfDoc->getOptContentConfig();



    EXPECT_EQ(result, expectedOCGs);

    delete expectedOCGs;

}



TEST_F(PDFDocTest_952, GetOptContentConfig_ReturnsNullptr_952) {

    EXPECT_CALL(*mockCatalog, getOptContentConfig()).WillOnce(Return(nullptr));



    const OCGs* result = pdfDoc->getOptContentConfig();



    EXPECT_EQ(result, nullptr);

}
