#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-page.h"

#include "poppler-private.h"

#include "TextOutputDev.h"

#include <cairo.h>



using namespace testing;



// Mock CairoOutputDev class to verify interactions

class MockCairoOutputDev : public CairoOutputDev {

public:

    MOCK_METHOD(void, setCairo, (cairo_t*), (override));

};



// Mock TextPage class to verify interactions

class MockTextPage : public TextPage {

public:

    MOCK_METHOD(void, drawSelection, (CairoOutputDev*, double, int, const PDFRectangle&, SelectionStyle, const GfxColor*, const GfxColor*, double, bool), (override));

};



class PopplerPageTest_2439 : public Test {

protected:

    void SetUp() override {

        document = new _PopplerDocument();

        document->output_dev = new MockCairoOutputDev();



        page = new _PopplerPage();

        page->document = document;

        page->text = std::make_shared<MockTextPage>();

    }



    void TearDown() override {

        delete page->document->output_dev;

        delete document;

        delete page;

    }



    _PopplerDocument* document;

    _PopplerPage* page;

};



TEST_F(PopplerPageTest_2439, RenderSelectionValidInput_2439) {

    PopplerRectangle selection = {10, 10, 20, 20};

    PopplerColor glyph_color = {255, 0, 0};

    PopplerColor background_color = {0, 255, 0};

    double background_opacity = 0.5;

    bool draw_glyphs = true;



    EXPECT_CALL(*static_cast<MockCairoOutputDev*>(page->document->output_dev), setCairo(_)).Times(2);

    EXPECT_CALL(*std::dynamic_pointer_cast<MockTextPage>(page->text), 

        drawSelection(static_cast<CairoOutputDev*>(page->document->output_dev), 1.0, 0, _, selectionStyleGlyph, _, _, background_opacity, draw_glyphs))

        .Times(1);



    render_selection(page, nullptr, &selection, POPPLER_SELECTION_GLYPH, &glyph_color, &background_color, background_opacity, draw_glyphs);

}



TEST_F(PopplerPageTest_2439, RenderSelectionBoundaryConditions_2439) {

    PopplerRectangle selection = {0, 0, 0, 0};

    PopplerColor glyph_color = {0, 0, 0};

    PopplerColor background_color = {0, 0, 0};

    double background_opacity = 1.0;

    bool draw_glyphs = false;



    EXPECT_CALL(*static_cast<MockCairoOutputDev*>(page->document->output_dev), setCairo(_)).Times(2);

    EXPECT_CALL(*std::dynamic_pointer_cast<MockTextPage>(page->text), 

        drawSelection(static_cast<CairoOutputDev*>(page->document->output_dev), 1.0, 0, _, selectionStyleGlyph, _, _, background_opacity, draw_glyphs))

        .Times(1);



    render_selection(page, nullptr, &selection, POPPLER_SELECTION_GLYPH, &glyph_color, &background_color, background_opacity, draw_glyphs);

}



TEST_F(PopplerPageTest_2439, RenderSelectionInvalidRectangle_2439) {

    PopplerRectangle selection = {20, 20, 10, 10}; // Invalid rectangle where x2 < x1 and y2 < y1

    PopplerColor glyph_color = {255, 0, 0};

    PopplerColor background_color = {0, 255, 0};

    double background_opacity = 0.5;

    bool draw_glyphs = true;



    EXPECT_CALL(*static_cast<MockCairoOutputDev*>(page->document->output_dev), setCairo(_)).Times(2);

    EXPECT_CALL(*std::dynamic_pointer_cast<MockTextPage>(page->text), 

        drawSelection(static_cast<CairoOutputDev*>(page->document->output_dev), 1.0, 0, _, selectionStyleGlyph, _, _, background_opacity, draw_glyphs))

        .Times(1);



    render_selection(page, nullptr, &selection, POPPLER_SELECTION_GLYPH, &glyph_color, &background_color, background_opacity, draw_glyphs);

}



TEST_F(PopplerPageTest_2439, RenderSelectionDifferentStyles_2439) {

    PopplerRectangle selection = {10, 10, 20, 20};

    PopplerColor glyph_color = {255, 0, 0};

    PopplerColor background_color = {0, 255, 0};

    double background_opacity = 0.5;

    bool draw_glyphs = true;



    EXPECT_CALL(*static_cast<MockCairoOutputDev*>(page->document->output_dev), setCairo(_)).Times(6);

    EXPECT_CALL(*std::dynamic_pointer_cast<MockTextPage>(page->text), 

        drawSelection(static_cast<CairoOutputDev*>(page->document->output_dev), 1.0, 0, _, selectionStyleGlyph, _, _, background_opacity, draw_glyphs))

        .Times(1);



    render_selection(page, nullptr, &selection, POPPLER_SELECTION_GLYPH, &glyph_color, &background_color, background_opacity, draw_glyphs);



    EXPECT_CALL(*std::dynamic_pointer_cast<MockTextPage>(page->text), 

        drawSelection(static_cast<CairoOutputDev*>(page->document->output_dev), 1.0, 0, _, selectionStyleWord, _, _, background_opacity, draw_glyphs))

        .Times(1);



    render_selection(page, nullptr, &selection, POPPLER_SELECTION_WORD, &glyph_color, &background_color, background_opacity, draw_glyphs);



    EXPECT_CALL(*std::dynamic_pointer_cast<MockTextPage>(page->text), 

        drawSelection(static_cast<CairoOutputDev*>(page->document->output_dev), 1.0, 0, _, selectionStyleLine, _, _, background_opacity, draw_glyphs))

        .Times(1);



    render_selection(page, nullptr, &selection, POPPLER_SELECTION_LINE, &glyph_color, &background_color, background_opacity, draw_glyphs);

}
