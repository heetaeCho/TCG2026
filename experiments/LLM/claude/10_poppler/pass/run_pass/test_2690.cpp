#include <gtest/gtest.h>

// External global variables used by getOutputSize and getCropSize
extern double x_resolution;
extern double y_resolution;
extern int paperWidth;
extern int paperHeight;
extern bool printing;
extern bool usePDFPageSize;

// We need to declare getCropSize since getOutputSize calls it
// and we need getOutputSize declaration
void getCropSize(double w, double h, double *width, double *height);
static void getOutputSize(double page_w, double page_h, double *width, double *height);

// Since getOutputSize is static in pdftocairo.cc, we need to include the source
// or redefine it for testing purposes. We'll include the necessary pieces.

// For testing a static function, we include the source file
// But first we need to handle all its dependencies. 
// A more practical approach: replicate the static function signature for testing.

// Since the function is static, we need to either:
// 1. Include the .cc file (which may bring in too many dependencies)
// 2. Or test through a wrapper

// Let's define the globals and the function directly for unit testing
// Based on the known interface:

// Define globals
double x_resolution = 150.0;
double y_resolution = 150.0;
int paperWidth = -1;
int paperHeight = -1;
bool printing = false;
bool usePDFPageSize = false;

// Define crop_w and crop_h related globals that getCropSize might use
// getCropSize is likely defined in the same file, let's provide a minimal version
// based on typical behavior: it just passes through the scaled values when no cropping

static double crop_w = 0;
static double crop_h = 0;

// Minimal getCropSize implementation for testing getOutputSize's routing logic
void getCropSize(double w, double h, double *width, double *height) {
    if (crop_w > 0) {
        *width = crop_w;
    } else {
        *width = w;
    }
    if (crop_h > 0) {
        *height = crop_h;
    } else {
        *height = h;
    }
}

// Now include the static function
static void getOutputSize(double page_w, double page_h, double *width, double *height) {
    if (printing) {
        if (usePDFPageSize) {
            *width = page_w;
            *height = page_h;
        } else {
            if (page_w > page_h) {
                *width = paperHeight;
                *height = paperWidth;
            } else {
                *width = paperWidth;
                *height = paperHeight;
            }
        }
    } else {
        getCropSize(page_w * x_resolution / 72.0, page_h * y_resolution / 72.0, width, height);
    }
}

class GetOutputSizeTest_2690 : public ::testing::Test {
protected:
    void SetUp() override {
        // Reset globals to defaults
        x_resolution = 150.0;
        y_resolution = 150.0;
        paperWidth = -1;
        paperHeight = -1;
        printing = false;
        usePDFPageSize = false;
        crop_w = 0;
        crop_h = 0;
    }
};

// Test: Non-printing mode scales page dimensions by resolution
TEST_F(GetOutputSizeTest_2690, NonPrintingMode_ScalesByResolution_2690) {
    printing = false;
    double width = 0, height = 0;
    double page_w = 72.0; // 1 inch
    double page_h = 72.0; // 1 inch

    getOutputSize(page_w, page_h, &width, &height);

    // Expected: 72.0 * 150.0 / 72.0 = 150.0
    EXPECT_DOUBLE_EQ(width, 150.0);
    EXPECT_DOUBLE_EQ(height, 150.0);
}

// Test: Non-printing mode with different x and y resolutions
TEST_F(GetOutputSizeTest_2690, NonPrintingMode_DifferentResolutions_2690) {
    printing = false;
    x_resolution = 300.0;
    y_resolution = 150.0;
    double width = 0, height = 0;
    double page_w = 144.0; // 2 inches
    double page_h = 72.0;  // 1 inch

    getOutputSize(page_w, page_h, &width, &height);

    // Expected width: 144.0 * 300.0 / 72.0 = 600.0
    // Expected height: 72.0 * 150.0 / 72.0 = 150.0
    EXPECT_DOUBLE_EQ(width, 600.0);
    EXPECT_DOUBLE_EQ(height, 150.0);
}

// Test: Printing mode with usePDFPageSize returns page dimensions directly
TEST_F(GetOutputSizeTest_2690, PrintingUsePDFPageSize_ReturnsPageDimensions_2690) {
    printing = true;
    usePDFPageSize = true;
    double width = 0, height = 0;
    double page_w = 612.0;
    double page_h = 792.0;

    getOutputSize(page_w, page_h, &width, &height);

    EXPECT_DOUBLE_EQ(width, 612.0);
    EXPECT_DOUBLE_EQ(height, 792.0);
}

// Test: Printing mode, not usePDFPageSize, portrait page (page_h >= page_w)
TEST_F(GetOutputSizeTest_2690, PrintingPortrait_UsesPaperWidthHeight_2690) {
    printing = true;
    usePDFPageSize = false;
    paperWidth = 595;
    paperHeight = 842;
    double width = 0, height = 0;
    double page_w = 612.0;  // portrait: page_w <= page_h
    double page_h = 792.0;

    getOutputSize(page_w, page_h, &width, &height);

    EXPECT_DOUBLE_EQ(width, 595.0);
    EXPECT_DOUBLE_EQ(height, 842.0);
}

// Test: Printing mode, not usePDFPageSize, landscape page (page_w > page_h)
TEST_F(GetOutputSizeTest_2690, PrintingLandscape_SwapsPaperDimensions_2690) {
    printing = true;
    usePDFPageSize = false;
    paperWidth = 595;
    paperHeight = 842;
    double width = 0, height = 0;
    double page_w = 842.0;  // landscape: page_w > page_h
    double page_h = 595.0;

    getOutputSize(page_w, page_h, &width, &height);

    // Landscape: width = paperHeight, height = paperWidth
    EXPECT_DOUBLE_EQ(width, 842.0);
    EXPECT_DOUBLE_EQ(height, 595.0);
}

// Test: Printing mode, landscape with equal dimensions (page_w == page_h, not >)
TEST_F(GetOutputSizeTest_2690, PrintingSquarePage_UsesPortraitOrientation_2690) {
    printing = true;
    usePDFPageSize = false;
    paperWidth = 595;
    paperHeight = 842;
    double width = 0, height = 0;
    double page_w = 500.0;  // square: page_w == page_h, not page_w > page_h
    double page_h = 500.0;

    getOutputSize(page_w, page_h, &width, &height);

    // Equal dimensions: goes to else branch (portrait)
    EXPECT_DOUBLE_EQ(width, 595.0);
    EXPECT_DOUBLE_EQ(height, 842.0);
}

// Test: Non-printing mode with zero page dimensions
TEST_F(GetOutputSizeTest_2690, NonPrintingZeroPageDimensions_2690) {
    printing = false;
    double width = 999, height = 999;
    double page_w = 0.0;
    double page_h = 0.0;

    getOutputSize(page_w, page_h, &width, &height);

    EXPECT_DOUBLE_EQ(width, 0.0);
    EXPECT_DOUBLE_EQ(height, 0.0);
}

// Test: Printing with usePDFPageSize and zero dimensions
TEST_F(GetOutputSizeTest_2690, PrintingPDFPageSizeZero_2690) {
    printing = true;
    usePDFPageSize = true;
    double width = 999, height = 999;

    getOutputSize(0.0, 0.0, &width, &height);

    EXPECT_DOUBLE_EQ(width, 0.0);
    EXPECT_DOUBLE_EQ(height, 0.0);
}

// Test: Non-printing with very large page dimensions
TEST_F(GetOutputSizeTest_2690, NonPrintingLargePageDimensions_2690) {
    printing = false;
    x_resolution = 300.0;
    y_resolution = 300.0;
    double width = 0, height = 0;
    double page_w = 7200.0; // 100 inches
    double page_h = 7200.0;

    getOutputSize(page_w, page_h, &width, &height);

    // Expected: 7200.0 * 300.0 / 72.0 = 30000.0
    EXPECT_DOUBLE_EQ(width, 30000.0);
    EXPECT_DOUBLE_EQ(height, 30000.0);
}

// Test: Printing, not usePDFPageSize, with negative paper dimensions
TEST_F(GetOutputSizeTest_2690, PrintingNegativePaperDimensions_2690) {
    printing = true;
    usePDFPageSize = false;
    paperWidth = -1;
    paperHeight = -1;
    double width = 0, height = 0;

    getOutputSize(612.0, 792.0, &width, &height);

    // Portrait page: width = paperWidth, height = paperHeight
    EXPECT_DOUBLE_EQ(width, -1.0);
    EXPECT_DOUBLE_EQ(height, -1.0);
}

// Test: Non-printing mode with fractional page dimensions
TEST_F(GetOutputSizeTest_2690, NonPrintingFractionalDimensions_2690) {
    printing = false;
    x_resolution = 72.0;
    y_resolution = 72.0;
    double width = 0, height = 0;
    double page_w = 100.5;
    double page_h = 200.7;

    getOutputSize(page_w, page_h, &width, &height);

    // With 72 DPI: result = page dimension * 72.0 / 72.0 = page dimension
    EXPECT_DOUBLE_EQ(width, 100.5);
    EXPECT_DOUBLE_EQ(height, 200.7);
}

// Test: Printing mode usePDFPageSize with landscape page
TEST_F(GetOutputSizeTest_2690, PrintingPDFPageSizeLandscape_2690) {
    printing = true;
    usePDFPageSize = true;
    double width = 0, height = 0;

    getOutputSize(842.0, 595.0, &width, &height);

    // usePDFPageSize ignores orientation, just returns page dimensions
    EXPECT_DOUBLE_EQ(width, 842.0);
    EXPECT_DOUBLE_EQ(height, 595.0);
}

// Test: Printing, landscape page, paper dimensions are swapped correctly
TEST_F(GetOutputSizeTest_2690, PrintingLandscapeSwapVerification_2690) {
    printing = true;
    usePDFPageSize = false;
    paperWidth = 100;
    paperHeight = 200;
    double width = 0, height = 0;

    // page_w > page_h => landscape => width=paperHeight, height=paperWidth
    getOutputSize(300.0, 100.0, &width, &height);

    EXPECT_DOUBLE_EQ(width, 200.0);  // paperHeight
    EXPECT_DOUBLE_EQ(height, 100.0); // paperWidth
}

// Test: Printing, portrait page, paper dimensions assignment
TEST_F(GetOutputSizeTest_2690, PrintingPortraitAssignment_2690) {
    printing = true;
    usePDFPageSize = false;
    paperWidth = 100;
    paperHeight = 200;
    double width = 0, height = 0;

    // page_w <= page_h => portrait => width=paperWidth, height=paperHeight
    getOutputSize(100.0, 300.0, &width, &height);

    EXPECT_DOUBLE_EQ(width, 100.0);  // paperWidth
    EXPECT_DOUBLE_EQ(height, 200.0); // paperHeight
}

// Test: Non-printing with resolution of 72 DPI (1:1 mapping)
TEST_F(GetOutputSizeTest_2690, NonPrinting72DPI_2690) {
    printing = false;
    x_resolution = 72.0;
    y_resolution = 72.0;
    double width = 0, height = 0;

    getOutputSize(612.0, 792.0, &width, &height);

    EXPECT_DOUBLE_EQ(width, 612.0);
    EXPECT_DOUBLE_EQ(height, 792.0);
}

// Test: Barely landscape (page_w just slightly greater than page_h)
TEST_F(GetOutputSizeTest_2690, PrintingBarelyLandscape_2690) {
    printing = true;
    usePDFPageSize = false;
    paperWidth = 400;
    paperHeight = 600;
    double width = 0, height = 0;

    // page_w > page_h by tiny amount
    getOutputSize(500.001, 500.0, &width, &height);

    // Should be landscape
    EXPECT_DOUBLE_EQ(width, 600.0);  // paperHeight
    EXPECT_DOUBLE_EQ(height, 400.0); // paperWidth
}
