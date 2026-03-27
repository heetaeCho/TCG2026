#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler/PDFDoc.h"

#include "poppler/Page.h"



using namespace testing;



class PDFDocTest : public Test {

protected:

    std::unique_ptr<MockPage> mockPage1;

    std::unique_ptr<MockPage> mockPage2;

    NiceMock<MockPage>* mockPages[2];

    MockPDFDoc pdfDoc;



    class MockPage : public Page {

    public:

        MOCK_METHOD(double, getMediaHeight, (), (const, override));

    };



    class MockPDFDoc : public PDFDoc {

    public:

        using PDFDoc::getPage;

        MOCK_METHOD(int, getNumPages, (), (const, override));



        MockPDFDoc() {

            mockPage1 = std::make_unique<MockPage>();

            mockPage2 = std::make_unique<MockPage>();

            mockPages[0] = mockPage1.get();

            mockPages[1] = mockPage2.get();



            EXPECT_CALL(*this, getNumPages()).WillRepeatedly(Return(2));

        }



        Page* getPage(int page) override {

            if (page >= 0 && page < 2) {

                return mockPages[page];

            }

            return nullptr;

        }

    };



    void SetUp() override {

        ON_CALL(*mockPage1, getMediaHeight()).WillByDefault(Return(792.0));

        ON_CALL(*mockPage2, getMediaHeight()).WillByDefault(Return(1123.0));

    }

};



TEST_F(PDFDocTest_955, getPageMediaHeight_ReturnsCorrectHeightForValidPages_955) {

    EXPECT_DOUBLE_EQ(pdfDoc.getPageMediaHeight(0), 792.0);

    EXPECT_DOUBLE_EQ(pdfDoc.getPageMediaHeight(1), 1123.0);

}



TEST_F(PDFDocTest_955, getPageMediaHeight_ReturnsZeroForInvalidPages_955) {

    EXPECT_DOUBLE_EQ(pdfDoc.getPageMediaHeight(-1), 0.0);

    EXPECT_DOUBLE_EQ(pdfDoc.getPageMediaHeight(2), 0.0);

}



TEST_F(PDFDocTest_955, getPageMediaHeight_CallsGetMediaHeightOnPage_955) {

    EXPECT_CALL(*mockPage1, getMediaHeight()).Times(1).WillOnce(Return(792.0));

    pdfDoc.getPageMediaHeight(0);



    EXPECT_CALL(*mockPage2, getMediaHeight()).Times(1).WillOnce(Return(1123.0));

    pdfDoc.getPageMediaHeight(1);

}
