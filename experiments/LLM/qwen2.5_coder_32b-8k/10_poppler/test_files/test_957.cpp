#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "PDFDoc.h"

#include "Page.h"



using namespace testing;



class PDFDocTest_957 : public Test {

protected:

    std::unique_ptr<MockPage> mockPage1;

    std::unique_ptr<MockPage> mockPage2;

    std::vector<std::unique_ptr<Page>> pageCache;

    MockPDFDoc* pdfDoc;



    class MockPage : public Page {

    public:

        MOCK_METHOD(double, getCropHeight, (), (const));

        MOCK_METHOD(bool, isOk, (), (const));

    };



    class MockPDFDoc : public PDFDoc {

    public:

        explicit MockPDFDoc(std::vector<std::unique_ptr<Page>>& pages) : pages(pages) {}



        Page* getPage(int page) override {

            if (page >= 0 && page < static_cast<int>(pages.size())) {

                return pages[page].get();

            }

            return nullptr;

        }



    private:

        std::vector<std::unique_ptr<Page>>& pages;

    };



    void SetUp() override {

        mockPage1 = std::make_unique<MockPage>();

        mockPage2 = std::make_unique<MockPage>();



        pageCache.push_back(std::move(mockPage1));

        pageCache.push_back(std::move(mockPage2));



        pdfDoc = new MockPDFDoc(pageCache);

    }



    void TearDown() override {

        delete pdfDoc;

    }

};



TEST_F(PDFDocTest_957, GetPageCropHeight_ValidPage_NormalOperation_957) {

    EXPECT_CALL(*mockPage1, isOk()).WillOnce(Return(true));

    EXPECT_CALL(*mockPage1, getCropHeight()).WillOnce(Return(500.0));



    double cropHeight = pdfDoc->getPageCropHeight(0);

    EXPECT_EQ(cropHeight, 500.0);

}



TEST_F(PDFDocTest_957, GetPageCropHeight_ValidPage_ZeroCropHeight_957) {

    EXPECT_CALL(*mockPage1, isOk()).WillOnce(Return(true));

    EXPECT_CALL(*mockPage1, getCropHeight()).WillOnce(Return(0.0));



    double cropHeight = pdfDoc->getPageCropHeight(0);

    EXPECT_EQ(cropHeight, 0.0);

}



TEST_F(PDFDocTest_957, GetPageCropHeight_PageNotFound_ReturnsZero_957) {

    EXPECT_CALL(*mockPage1, isOk()).WillOnce(Return(false));



    double cropHeight = pdfDoc->getPageCropHeight(0);

    EXPECT_EQ(cropHeight, 0.0);

}



TEST_F(PDFDocTest_957, GetPageCropHeight_OutOfBounds_ReturnsZero_957) {

    double cropHeight = pdfDoc->getPageCropHeight(-1);

    EXPECT_EQ(cropHeight, 0.0);



    cropHeight = pdfDoc->getPageCropHeight(2); // assuming only 2 pages

    EXPECT_EQ(cropHeight, 0.0);

}
