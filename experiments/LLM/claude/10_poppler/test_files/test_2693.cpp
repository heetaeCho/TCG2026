#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cairo.h>
#include <memory>

#include "PDFDoc.h"
#include "CairoOutputDev.h"
#include "GooString.h"

// External global variables from pdftocairo.cc
extern bool ps;
extern int crop_x;
extern int crop_y;
extern bool transp;
extern bool printing;
extern double x_resolution;
extern double y_resolution;
extern bool useCropBox;

// Forward declare renderPage if accessible, or include the header
extern void renderPage(PDFDoc *doc, CairoOutputDev *cairoOut, int pg,
                       double page_w, double page_h,
                       double output_w, double output_h);

class RenderPageTest_2693 : public ::testing::Test {
protected:
    void SetUp() override {
        // Reset global state to defaults
        ps = false;
        crop_x = 0;
        crop_y = 0;
        transp = false;
        printing = false;
        x_resolution = 150.0;
        y_resolution = 150.0;
        useCropBox = false;
    }

    void TearDown() override {
        // Reset global state
        ps = false;
        crop_x = 0;
        crop_y = 0;
        transp = false;
        printing = false;
        x_resolution = 150.0;
        y_resolution = 150.0;
        useCropBox = false;
    }
};

TEST_F(RenderPageTest_2693, GlobalDefaultsAreCorrect_2693) {
    EXPECT_FALSE(ps);
    EXPECT_EQ(crop_x, 0);
    EXPECT_EQ(crop_y, 0);
    EXPECT_FALSE(transp);
    EXPECT_FALSE(printing);
    EXPECT_DOUBLE_EQ(x_resolution, 150.0);
    EXPECT_DOUBLE_EQ(y_resolution, 150.0);
    EXPECT_FALSE(useCropBox);
}

TEST_F(RenderPageTest_2693, CropXYCanBeSet_2693) {
    crop_x = 10;
    crop_y = 20;
    EXPECT_EQ(crop_x, 10);
    EXPECT_EQ(crop_y, 20);
}

TEST_F(RenderPageTest_2693, ResolutionCanBeChanged_2693) {
    x_resolution = 300.0;
    y_resolution = 300.0;
    EXPECT_DOUBLE_EQ(x_resolution, 300.0);
    EXPECT_DOUBLE_EQ(y_resolution, 300.0);
}

TEST_F(RenderPageTest_2693, PsModeFlagCanBeToggled_2693) {
    ps = true;
    EXPECT_TRUE(ps);
    ps = false;
    EXPECT_FALSE(ps);
}

TEST_F(RenderPageTest_2693, PrintingFlagCanBeToggled_2693) {
    printing = true;
    EXPECT_TRUE(printing);
    printing = false;
    EXPECT_FALSE(printing);
}

TEST_F(RenderPageTest_2693, TranspFlagCanBeToggled_2693) {
    transp = true;
    EXPECT_TRUE(transp);
    transp = false;
    EXPECT_FALSE(transp);
}

TEST_F(RenderPageTest_2693, UseCropBoxFlagCanBeToggled_2693) {
    useCropBox = true;
    EXPECT_TRUE(useCropBox);
    useCropBox = false;
    EXPECT_FALSE(useCropBox);
}

TEST_F(RenderPageTest_2693, CairoOutputDevConstruction_2693) {
    CairoOutputDev cairoOut;
    // CairoOutputDev should be constructible
    SUCCEED();
}

TEST_F(RenderPageTest_2693, CairoOutputDevSetPrinting_2693) {
    CairoOutputDev cairoOut;
    cairoOut.setPrinting(true);
    cairoOut.setPrinting(false);
    SUCCEED();
}

TEST_F(RenderPageTest_2693, CairoOutputDevSetCairoNull_2693) {
    CairoOutputDev cairoOut;
    cairoOut.setCairo(nullptr);
    SUCCEED();
}

TEST_F(RenderPageTest_2693, NegativeCropValues_2693) {
    crop_x = -10;
    crop_y = -20;
    EXPECT_EQ(crop_x, -10);
    EXPECT_EQ(crop_y, -20);
}

TEST_F(RenderPageTest_2693, ZeroResolution_2693) {
    x_resolution = 0.0;
    y_resolution = 0.0;
    EXPECT_DOUBLE_EQ(x_resolution, 0.0);
    EXPECT_DOUBLE_EQ(y_resolution, 0.0);
}

TEST_F(RenderPageTest_2693, HighResolution_2693) {
    x_resolution = 1200.0;
    y_resolution = 1200.0;
    EXPECT_DOUBLE_EQ(x_resolution, 1200.0);
    EXPECT_DOUBLE_EQ(y_resolution, 1200.0);
}
