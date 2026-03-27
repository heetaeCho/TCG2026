#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-page.h"

#include "CairoOutputDev.h"



using namespace testing;



class PopplerPageTest : public ::testing::Test {

protected:

    PopplerDocument* document;

    PopplerPage* page;

    cairo_t* mock_cairo;

    CairoOutputDev* mock_output_dev;



    void SetUp() override {

        document = new PopplerDocument();

        document->output_dev = new CairoOutputDev();

        page = new PopplerPage();

        page->document = document;

        mock_cairo = reinterpret_cast<cairo_t*>(malloc(sizeof(cairo_t)));

        mock_output_dev = document->output_dev;



        ON_CALL(*mock_output_dev, setCairo(_)).WillByDefault(ACTION_TEMPLATE(return_arg));

        ON_CALL(*mock_output_dev, setTextPage(_)).WillByDefault(ACTION_TEMPLATE(return_arg));

    }



    void TearDown() override {

        delete page;

        delete document->output_dev;

        free(mock_cairo);

        delete document;

    }

};



TEST_F(PopplerPageTest_2433, RenderFull_NormalOperation_2433) {

    EXPECT_CALL(*mock_output_dev, setCairo(_));

    EXPECT_CALL(*mock_output_dev, setPrinting(false));

    EXPECT_CALL(*mock_output_dev, setTextPage(_));



    poppler_page_render_full(page, mock_cairo, FALSE, POPPLER_RENDER_NO_ANNOTS);



    EXPECT_TRUE(page->text != nullptr);

}



TEST_F(PopplerPageTest_2433, RenderFull_PrintingEnabled_2433) {

    page->text = std::make_shared<TextPage>(false);



    EXPECT_CALL(*mock_output_dev, setCairo(_));

    EXPECT_CALL(*mock_output_dev, setPrinting(true));

    EXPECT_CALL(*mock_output_dev, setTextPage(_)).Times(0);



    poppler_page_render_full(page, mock_cairo, TRUE, POPPLER_RENDER_NO_ANNOTS);

}



TEST_F(PopplerPageTest_2433, RenderFull_RenderAnnotations_2433) {

    page->text = std::make_shared<TextPage>(false);



    EXPECT_CALL(*mock_output_dev, setCairo(_));

    EXPECT_CALL(*mock_output_dev, setPrinting(false));

    EXPECT_CALL(*mock_output_dev, setTextPage(_));



    poppler_page_render_full(page, mock_cairo, FALSE, POPPLER_RENDER_WITH_ANNOTS);

}



TEST_F(PopplerPageTest_2433, RenderFull_NullCairoContext_2433) {

    page->text = std::make_shared<TextPage>(false);



    EXPECT_DEBUG_DEATH(poppler_page_render_full(page, nullptr, FALSE, POPPLER_RENDER_NO_ANNOTS), "");

}



TEST_F(PopplerPageTest_2433, RenderFull_NullPopplerPage_2433) {

    page->text = std::make_shared<TextPage>(false);



    EXPECT_DEBUG_DEATH(poppler_page_render_full(nullptr, mock_cairo, FALSE, POPPLER_RENDER_NO_ANNOTS), "");

}
