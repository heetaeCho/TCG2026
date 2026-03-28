#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cairo.h>
#include <cairo-ft.h>
#include <memory>

// Include the header for CairoFontEngine
#include "CairoFontEngine.h"
#include "GfxFont.h"
#include "PDFDoc.h"
#include "GlobalParams.h"

class CairoFontEngineTest_1752 : public ::testing::Test {
protected:
    void SetUp() override
    {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
        surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 100, 100);
        cr = cairo_create(surface);
    }

    void TearDown() override
    {
        if (cr) {
            cairo_destroy(cr);
            cr = nullptr;
        }
        if (surface) {
            cairo_surface_destroy(surface);
            surface = nullptr;
        }
    }

    cairo_surface_t *surface = nullptr;
    cairo_t *cr = nullptr;
};

// Test that CairoFontEngine can be constructed with valid parameters
TEST_F(CairoFontEngineTest_1752, ConstructionWithValidFontMap_1752)
{
    FT_Library lib;
    FT_Error err = FT_Init_FreeType(&lib);
    ASSERT_EQ(err, 0);

    CairoFontEngine engine(lib);
    // Engine should be constructible without crash
    FT_Done_FreeType(lib);
}

// Test that getFont returns nullptr for nullptr GfxFont
TEST_F(CairoFontEngineTest_1752, GetFontWithNullReturnsNull_1752)
{
    FT_Library lib;
    FT_Error err = FT_Init_FreeType(&lib);
    ASSERT_EQ(err, 0);

    CairoFontEngine engine(lib);

    // Passing nullptr font should not crash and should return nullptr or handle gracefully
    std::shared_ptr<CairoFont> cairoFont = engine.getFont(nullptr, nullptr, nullptr, 1.0, 1.0);
    EXPECT_EQ(cairoFont, nullptr);

    FT_Done_FreeType(lib);
}

// Test CairoFont face retrieval - a null CairoFont scenario
TEST_F(CairoFontEngineTest_1752, CairoFontEngineMultipleInitialization_1752)
{
    FT_Library lib1;
    FT_Error err1 = FT_Init_FreeType(&lib1);
    ASSERT_EQ(err1, 0);

    FT_Library lib2;
    FT_Error err2 = FT_Init_FreeType(&lib2);
    ASSERT_EQ(err2, 0);

    // Multiple engines should be independently constructible
    CairoFontEngine engine1(lib1);
    CairoFontEngine engine2(lib2);

    FT_Done_FreeType(lib1);
    FT_Done_FreeType(lib2);
}

// Test that the engine handles repeated getFont calls gracefully
TEST_F(CairoFontEngineTest_1752, RepeatedGetFontCallsWithNull_1752)
{
    FT_Library lib;
    FT_Error err = FT_Init_FreeType(&lib);
    ASSERT_EQ(err, 0);

    CairoFontEngine engine(lib);

    for (int i = 0; i < 10; i++) {
        std::shared_ptr<CairoFont> cairoFont = engine.getFont(nullptr, nullptr, nullptr, 1.0, 1.0);
        EXPECT_EQ(cairoFont, nullptr);
    }

    FT_Done_FreeType(lib);
}

// Test boundary: zero scaling factors
TEST_F(CairoFontEngineTest_1752, GetFontWithZeroScale_1752)
{
    FT_Library lib;
    FT_Error err = FT_Init_FreeType(&lib);
    ASSERT_EQ(err, 0);

    CairoFontEngine engine(lib);
    std::shared_ptr<CairoFont> cairoFont = engine.getFont(nullptr, nullptr, nullptr, 0.0, 0.0);
    EXPECT_EQ(cairoFont, nullptr);

    FT_Done_FreeType(lib);
}

// Test boundary: negative scaling factors
TEST_F(CairoFontEngineTest_1752, GetFontWithNegativeScale_1752)
{
    FT_Library lib;
    FT_Error err = FT_Init_FreeType(&lib);
    ASSERT_EQ(err, 0);

    CairoFontEngine engine(lib);
    std::shared_ptr<CairoFont> cairoFont = engine.getFont(nullptr, nullptr, nullptr, -1.0, -1.0);
    EXPECT_EQ(cairoFont, nullptr);

    FT_Done_FreeType(lib);
}
