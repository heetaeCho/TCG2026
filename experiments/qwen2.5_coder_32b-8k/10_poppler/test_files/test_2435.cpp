#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-page.h"

#include <cairo.h>



using namespace testing;



class PopplerPageTest_2435 : public Test {

protected:

    MockFunction<void(PopplerPage*, cairo_t*, bool, PopplerRenderAnnotsFlags)> mock_poppler_page_render_full;



    void SetUp() override {

        // Redirect the call to poppler_page_render_full to our mock

        EXPECT_CALL(mock_poppler_page_render_full,

                    Call(_, _, true, _))

            .WillRepeatedly(Invoke([](PopplerPage* page, cairo_t* cr, bool forPrinting, PopplerRenderAnnotsFlags flags) {

                // Simulate the call to avoid actual rendering

            }));

    }



    void TearDown() override {

        // Reset any expectations or state here if necessary

    }

};



TEST_F(PopplerPageTest_2435, RenderWithNoOptions_2435) {

    PopplerPage* page = new PopplerPage();

    cairo_t* cr = cairo_create(cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 100, 100));



    poppler_page_render_for_printing_with_options(page, cr, (PopplerPrintFlags)0);



    EXPECT_CALL(mock_poppler_page_render_full,

                Call(page, cr, true, POPPLER_RENDER_ANNOTS_PRINT_DOCUMENT))

        .Times(1);



    cairo_destroy(cr);

    delete page;

}



TEST_F(PopplerPageTest_2435, RenderWithStampAnnotsOnly_2435) {

    PopplerPage* page = new PopplerPage();

    cairo_t* cr = cairo_create(cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 100, 100));



    poppler_page_render_for_printing_with_options(page, cr, POPPLER_PRINT_STAMP_ANNOTS_ONLY);



    EXPECT_CALL(mock_poppler_page_render_full,

                Call(page, cr, true, POPPLER_RENDER_ANNOTS_PRINT_DOCUMENT | POPPLER_RENDER_ANNOTS_PRINT_STAMP))

        .Times(1);



    cairo_destroy(cr);

    delete page;

}



TEST_F(PopplerPageTest_2435, RenderWithMarkupAnnots_2435) {

    PopplerPage* page = new PopplerPage();

    cairo_t* cr = cairo_create(cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 100, 100));



    poppler_page_render_for_printing_with_options(page, cr, POPPLER_PRINT_MARKUP_ANNOTS);



    EXPECT_CALL(mock_poppler_page_render_full,

                Call(page, cr, true, POPPLER_RENDER_ANNOTS_PRINT_DOCUMENT | POPPLER_RENDER_ANNOTS_PRINT_MARKUP))

        .Times(1);



    cairo_destroy(cr);

    delete page;

}



TEST_F(PopplerPageTest_2435, RenderWithStampAndMarkupAnnots_2435) {

    PopplerPage* page = new PopplerPage();

    cairo_t* cr = cairo_create(cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 100, 100));



    poppler_page_render_for_printing_with_options(page, cr, POPPLER_PRINT_STAMP_ANNOTS_ONLY | POPPLER_PRINT_MARKUP_ANNOTS);



    EXPECT_CALL(mock_poppler_page_render_full,

                Call(page, cr, true, POPPLER_RENDER_ANNOTS_PRINT_DOCUMENT | POPPLER_RENDER_ANNOTS_PRINT_STAMP | POPPLER_RENDER_ANNOTS_PRINT_MARKUP))

        .Times(1);



    cairo_destroy(cr);

    delete page;

}



TEST_F(PopplerPageTest_2435, RenderWithNullPage_2435) {

    PopplerPage* page = nullptr;

    cairo_t* cr = cairo_create(cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 100, 100));



    // Assuming the function handles null gracefully

    poppler_page_render_for_printing_with_options(page, cr, (PopplerPrintFlags)0);



    EXPECT_CALL(mock_poppler_page_render_full,

                Call(page, cr, true, POPPLER_RENDER_ANNOTS_PRINT_DOCUMENT))

        .Times(0); // No call should be made if the page is null



    cairo_destroy(cr);

}



TEST_F(PopplerPageTest_2435, RenderWithNullCairoContext_2435) {

    PopplerPage* page = new PopplerPage();

    cairo_t* cr = nullptr;



    // Assuming the function handles null gracefully

    poppler_page_render_for_printing_with_options(page, cr, (PopplerPrintFlags)0);



    EXPECT_CALL(mock_poppler_page_render_full,

                Call(page, cr, true, POPPLER_RENDER_ANNOTS_PRINT_DOCUMENT))

        .Times(0); // No call should be made if the cairo context is null



    delete page;

}
