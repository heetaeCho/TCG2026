#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cairo.h>
#include "GooString.h"
#include "CairoOutputDev.h"

// We need access to the static function and global variables from pdftocairo.cc
// These are defined in the translation unit under test

// External declarations for globals used by endPage
extern bool printing;
extern cairo_surface_t *surface;

// Forward declaration of the function under test
static void endPage(GooString *imageFileName, CairoOutputDev *cairoOut, bool isLastPage);

// Since endPage is a static function in pdftocairo.cc, we need to include it
// or link against the object file. For testing purposes, we include the source.
// In a real build system, we'd handle this differently.

// Mock for CairoOutputDev to observe interactions
class MockCairoOutputDev : public CairoOutputDev {
public:
    MOCK_METHOD(void, setCairo, (int *cr), ());
    MOCK_METHOD(void, setPrinting, (bool printingA), ());
    MOCK_METHOD(void, emitStructTree, (), ());
};

class EndPageTest_2694 : public ::testing::Test {
protected:
    void SetUp() override {
        // Create a minimal image surface for testing
        surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 100, 100);
        ASSERT_EQ(cairo_surface_status(surface), CAIRO_STATUS_SUCCESS);
    }

    void TearDown() override {
        if (surface) {
            cairo_surface_destroy(surface);
            surface = nullptr;
        }
    }
};

// Test: Printing mode, last page - should call setCairo, setPrinting, emitStructTree, setCairo(nullptr)
TEST_F(EndPageTest_2694, PrintingLastPage_CallsEmitStructTree_2694) {
    printing = true;
    MockCairoOutputDev mockCairoOut;
    GooString imageFileName("test_output");

    {
        ::testing::InSequence seq;
        EXPECT_CALL(mockCairoOut, setCairo(::testing::NotNull())).Times(1);
        EXPECT_CALL(mockCairoOut, setPrinting(true)).Times(1);
        EXPECT_CALL(mockCairoOut, emitStructTree()).Times(1);
        EXPECT_CALL(mockCairoOut, setCairo(nullptr)).Times(1);
    }

    endPage(&imageFileName, &mockCairoOut, true);
}

// Test: Printing mode, not last page - should NOT call emitStructTree
TEST_F(EndPageTest_2694, PrintingNotLastPage_NoEmitStructTree_2694) {
    printing = true;
    MockCairoOutputDev mockCairoOut;
    GooString imageFileName("test_output");

    EXPECT_CALL(mockCairoOut, setCairo(::testing::_)).Times(0);
    EXPECT_CALL(mockCairoOut, setPrinting(::testing::_)).Times(0);
    EXPECT_CALL(mockCairoOut, emitStructTree()).Times(0);

    endPage(&imageFileName, &mockCairoOut, false);
}

// Test: Non-printing mode - should destroy surface
TEST_F(EndPageTest_2694, NonPrintingMode_DestroySurface_2694) {
    printing = false;
    MockCairoOutputDev mockCairoOut;
    GooString imageFileName("test_output");

    // In non-printing mode, no calls to CairoOutputDev printing methods
    EXPECT_CALL(mockCairoOut, setCairo(::testing::_)).Times(0);
    EXPECT_CALL(mockCairoOut, setPrinting(::testing::_)).Times(0);
    EXPECT_CALL(mockCairoOut, emitStructTree()).Times(0);

    endPage(&imageFileName, &mockCairoOut, false);
    // Surface is destroyed inside endPage in non-printing mode
    surface = nullptr; // Prevent double-free in TearDown
}

// Test: Non-printing mode with last page flag true - still uses non-printing path
TEST_F(EndPageTest_2694, NonPrintingModeLastPageTrue_StillNonPrintingPath_2694) {
    printing = false;
    MockCairoOutputDev mockCairoOut;
    GooString imageFileName("test_output");

    EXPECT_CALL(mockCairoOut, setCairo(::testing::_)).Times(0);
    EXPECT_CALL(mockCairoOut, emitStructTree()).Times(0);

    endPage(&imageFileName, &mockCairoOut, true);
    surface = nullptr;
}

// Test: Null imageFileName in printing mode
TEST_F(EndPageTest_2694, PrintingNullFileName_2694) {
    printing = true;
    MockCairoOutputDev mockCairoOut;

    EXPECT_CALL(mockCairoOut, setCairo(::testing::_)).Times(0);
    EXPECT_CALL(mockCairoOut, emitStructTree()).Times(0);

    endPage(nullptr, &mockCairoOut, false);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
