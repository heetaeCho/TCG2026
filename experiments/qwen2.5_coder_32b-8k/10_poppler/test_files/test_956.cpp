#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler/PDFDoc.h"

#include "poppler/Page.h"



using namespace testing;



class PDFDocTest : public ::testing::Test {

protected:

    // Mock Page class to control its behavior for tests

    class MockPage : public Page {

    public:

        MOCK_CONST_METHOD0(getCropWidth, double());

        MOCK_CONST_METHOD0(isOk, bool());



        MockPage(PDFDoc* docA, int numA, Object&& pageDict, Ref pageRefA, std::unique_ptr<PageAttrs> attrsA)

            : Page(docA, numA, std::move(pageDict), pageRefA, std::move(attrsA)) {}

    };



    // Helper function to create a PDFDoc with mocked pages

    std::unique_ptr<PDFDoc> createPDFDocWithMockPages(int pageCount) {

        auto pdfDoc = std::make_unique<testing::StrictMock<MockPDFDoc>>();

        for (int i = 0; i < pageCount; ++i) {

            auto mockPage = std::make_unique<NiceMock<MockPage>>(pdfDoc.get(), i, Object(), Ref(1, i), nullptr);

            ON_CALL(*mockPage, isOk()).WillByDefault(Return(true));

            pdfDoc->pageCache.push_back(std::move(mockPage));

        }

        return pdfDoc;

    }



    class MockPDFDoc : public PDFDoc {

    public:

        MockPDFDoc() : PDFDoc(nullptr, std::nullopt, std::nullopt, nullptr) {}



        MOCK_METHOD1(getPage, Page*(int page));



        std::vector<std::unique_ptr<Page>> pageCache;



        Page* getPage(int page) override {

            if (page >= 0 && page < static_cast<int>(pageCache.size())) {

                return pageCache[page].get();

            }

            return nullptr;

        }

    };

};



TEST_F(PDFDocTest, GetPageCropWidth_NormalOperation_956) {

    auto pdfDoc = createPDFDocWithMockPages(1);

    EXPECT_CALL(*pdfDoc->pageCache[0], getCropWidth()).WillOnce(Return(595.0));



    double cropWidth = pdfDoc->getPageCropWidth(0);



    EXPECT_EQ(cropWidth, 595.0);

}



TEST_F(PDFDocTest, GetPageCropWidth_PageNotFound_956) {

    auto pdfDoc = createPDFDocWithMockPages(1);



    double cropWidth = pdfDoc->getPageCropWidth(1); // Page index out of range



    EXPECT_EQ(cropWidth, 0.0);

}



TEST_F(PDFDocTest, GetPageCropWidth_PageNotOk_956) {

    auto pdfDoc = createPDFDocWithMockPages(1);

    EXPECT_CALL(*pdfDoc->pageCache[0], isOk()).WillOnce(Return(false));



    double cropWidth = pdfDoc->getPageCropWidth(0);



    EXPECT_EQ(cropWidth, 0.0);

}



TEST_F(PDFDocTest, GetPageCropWidth_ZeroPages_956) {

    auto pdfDoc = createPDFDocWithMockPages(0); // No pages in the document



    double cropWidth = pdfDoc->getPageCropWidth(0);



    EXPECT_EQ(cropWidth, 0.0);

}



TEST_F(PDFDocTest, GetPageCropWidth_NegativePageIndex_956) {

    auto pdfDoc = createPDFDocWithMockPages(1); // Negative page index



    double cropWidth = pdfDoc->getPageCropWidth(-1);



    EXPECT_EQ(cropWidth, 0.0);

}
