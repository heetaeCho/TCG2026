#include <gtest/gtest.h>

#include "PDFDoc.h"

#include "Page.h"



class PDFDocTest_958 : public ::testing::Test {

protected:

    std::unique_ptr<Page> mockPage1;

    std::unique_ptr<Page> mockPage2;



    void SetUp() override {

        // Assuming we can create Page objects with specific rotation values for testing

        mockPage1 = std::make_unique<Page>(nullptr, 1, Object(), Ref(0, 0), std::make_unique<PageAttrs>());

        mockPage2 = std::make_unique<Page>(nullptr, 2, Object(), Ref(0, 0), std::make_unique<PageAttrs>());



        // Set specific rotation values for the mock pages

        ON_CALL(*mockPage1, getRotate()).WillByDefault(::testing::Return(90));

        ON_CALL(*mockPage2, getRotate()).WillByDefault(::testing::Return(180));



        // Mock PDFDoc object and set up page cache with mock pages

        pdfDoc = std::make_unique<PDFDoc>(nullptr, std::nullopt, std::nullopt, [](){});

        pdfDoc->pageCache.push_back(std::move(mockPage1));

        pdfDoc->pageCache.push_back(std::move(mockPage2));

    }



    void TearDown() override {

        pdfDoc.reset();

    }



    std::unique_ptr<PDFDoc> pdfDoc;

};



// Normal operation

TEST_F(PDFDocTest_958, GetPageRotate_ReturnsCorrectValueForExistingPage_958) {

    EXPECT_EQ(pdfDoc->getPageRotate(1), 90);

    EXPECT_EQ(pdfDoc->getPageRotate(2), 180);

}



// Boundary conditions

TEST_F(PDFDocTest_958, GetPageRotate_ReturnsZeroForNonExistentPage_958) {

    EXPECT_EQ(pdfDoc->getPageRotate(0), 0); // Assuming page numbers start from 1

    EXPECT_EQ(pdfDoc->getPageRotate(3), 0); // Page index out of bounds

}



// Exceptional or error cases (if observable through the interface)

TEST_F(PDFDocTest_958, GetPageRotate_HandlesEmptyPDFDocument_958) {

    pdfDoc->pageCache.clear();

    EXPECT_EQ(pdfDoc->getPageRotate(1), 0);

}
