#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/poppler/glib/poppler-page.cc"

#include "TestProjects/poppler/poppler/Page.h"

#include "TestProjects/poppler/glib/poppler-private.h"



using ::testing::NiceMock;

using ::testing::_;



class MockTextOutputDev : public TextOutputDev {

public:

    MOCK_METHOD(void, endPage, (), (override));

    MOCK_METHOD(std::unique_ptr<TextPage>, takeText, (), (override));

};



class MockGfx : public Gfx {

public:

    MockGfx(OutputDev *out, double hDPI, double vDPI, int rotate, bool useMediaBox, bool crop,

            int sliceX, int sliceY, int sliceW, int sliceH, _Bool (*abortCheckCbk)(void *),

            void *abortCheckCbkData)

        : Gfx(out, hDPI, vDPI, rotate, useMediaBox, crop, sliceX, sliceY, sliceW, sliceH,

              abortCheckCbk, abortCheckCbkData) {}



    MOCK_METHOD(void, display, (), (override));

};



class MockPage : public Page {

public:

    MockPage(PDFDoc *docA, int numA, Object &&pageDict, Ref pageRefA, std::unique_ptr<PageAttrs> attrsA)

        : Page(docA, numA, std::move(pageDict), pageRefA, std::move(attrsA)) {}



    MOCK_METHOD(std::unique_ptr<Gfx>, createGfx, (OutputDev * out, double hDPI, double vDPI, int rotate,

                                                  bool useMediaBox, bool crop, int sliceX, int sliceY,

                                                  int sliceW, int sliceH, _Bool (*)(void *) abortCheckCbk,

                                                  void *abortCheckCbkData), (override));

    MOCK_METHOD(void, display, (Gfx * gfx), (override));

};



class PopplerPageTest_2431 : public ::testing::Test {

protected:

    NiceMock<MockTextOutputDev> mock_text_dev;

    std::shared_ptr<MockPage> mock_page;

    PopplerPage poppler_page;



    void SetUp() override {

        mock_page = std::make_shared<NiceMock<MockPage>>(nullptr, 0, Object(), Ref(), nullptr);

        poppler_page.page = mock_page;

    }

};



TEST_F(PopplerPageTest_2431, GetTextPage_CreatesTextPage_IfNotExists_2431) {

    auto text_dev_ptr = &mock_text_dev;

    std::unique_ptr<MockGfx> mock_gfx = std::make_unique<NiceMock<MockGfx>>(text_dev_ptr, 72.0, 72.0, 0,

                                                                          true, false, -1, -1, -1, -1, nullptr, nullptr);



    EXPECT_CALL(mock_text_dev, endPage()).Times(1);

    EXPECT_CALL(*mock_page, createGfx(text_dev_ptr, 72.0, 72.0, 0, true, /* useMediaBox */ true,

                                      /* Crop */ -1, -1, -1, -1, nullptr, nullptr))

        .WillOnce(testing::Return(std::move(mock_gfx)));

    EXPECT_CALL(*mock_page, display(_)).Times(1);

    EXPECT_CALL(mock_text_dev, takeText()).WillOnce(testing::Return(std::make_unique<TextPage>()));



    TextPage *result = poppler_page_get_text_page(&poppler_page);



    ASSERT_NE(result, nullptr);

}



TEST_F(PopplerPageTest_2431, GetTextPage_ReturnsExistingTextPage_IfExists_2431) {

    auto existing_text_page = std::make_shared<TextPage>();

    poppler_page.text = existing_text_page;



    TextPage *result = poppler_page_get_text_page(&poppler_page);



    ASSERT_EQ(result, existing_text_page.get());

}



TEST_F(PopplerPageTest_2431, GetTextPage_HandlesCreateGfxFailure_IfNullReturned_2431) {

    auto text_dev_ptr = &mock_text_dev;



    EXPECT_CALL(mock_text_dev, endPage()).Times(0);

    EXPECT_CALL(*mock_page, createGfx(text_dev_ptr, 72.0, 72.0, 0, true, /* useMediaBox */ true,

                                      /* Crop */ -1, -1, -1, -1, nullptr, nullptr))

        .WillOnce(testing::Return(nullptr));



    TextPage *result = poppler_page_get_text_page(&poppler_page);



    ASSERT_EQ(result, nullptr);

}



TEST_F(PopplerPageTest_2431, GetTextPage_HandlesTakeTextFailure_IfNullReturned_2431) {

    auto text_dev_ptr = &mock_text_dev;

    std::unique_ptr<MockGfx> mock_gfx = std::make_unique<NiceMock<MockGfx>>(text_dev_ptr, 72.0, 72.0, 0,

                                                                          true, false, -1, -1, -1, -1, nullptr, nullptr);



    EXPECT_CALL(mock_text_dev, endPage()).Times(1);

    EXPECT_CALL(*mock_page, createGfx(text_dev_ptr, 72.0, 72.0, 0, true, /* useMediaBox */ true,

                                      /* Crop */ -1, -1, -1, -1, nullptr, nullptr))

        .WillOnce(testing::Return(std::move(mock_gfx)));

    EXPECT_CALL(*mock_page, display(_)).Times(1);

    EXPECT_CALL(mock_text_dev, takeText()).WillOnce(testing::Return(nullptr));



    TextPage *result = poppler_page_get_text_page(&poppler_page);



    ASSERT_EQ(result, nullptr);

}
