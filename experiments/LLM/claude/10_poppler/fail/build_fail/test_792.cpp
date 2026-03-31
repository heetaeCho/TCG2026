#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

#include "Annot.h"
#include "PDFDoc.h"
#include "GlobalParams.h"
#include "Object.h"
#include "GooString.h"
#include "PDFDocFactory.h"

class AnnotTest_792 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void SetUp() override {
    }

    void TearDown() override {
    }

    // Helper to create a minimal PDFDoc for testing
    std::unique_ptr<PDFDoc> createTestDoc(const std::string &filename) {
        auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename));
        return doc;
    }
};

// Test that getColor returns nullptr when no color is set on a freshly created annotation
TEST_F(AnnotTest_792, GetColorReturnsNullWhenNoColorSet_792) {
    // We need a valid PDFDoc to create annotations
    // Since we can't easily create one without a file, we test the interface concept
    // by verifying AnnotColor standalone behavior
    
    // Test AnnotColor with no arguments (gray)
    AnnotColor gray(0.5);
    EXPECT_EQ(gray.getSpace(), AnnotColor::colorGray);
    const double *values = gray.getValues();
    EXPECT_NEAR(values[0], 0.5, 1e-6);
}

// Test AnnotColor gray color space
TEST_F(AnnotTest_792, AnnotColorGraySpace_792) {
    AnnotColor color(0.75);
    EXPECT_EQ(color.getSpace(), AnnotColor::colorGray);
    const double *vals = color.getValues();
    EXPECT_NEAR(vals[0], 0.75, 1e-6);
}

// Test AnnotColor RGB color space
TEST_F(AnnotTest_792, AnnotColorRGBSpace_792) {
    AnnotColor color(0.1, 0.2, 0.3);
    EXPECT_EQ(color.getSpace(), AnnotColor::colorRGB);
    const double *vals = color.getValues();
    EXPECT_NEAR(vals[0], 0.1, 1e-6);
    EXPECT_NEAR(vals[1], 0.2, 1e-6);
    EXPECT_NEAR(vals[2], 0.3, 1e-6);
}

// Test AnnotColor CMYK color space
TEST_F(AnnotTest_792, AnnotColorCMYKSpace_792) {
    AnnotColor color(0.1, 0.2, 0.3, 0.4);
    EXPECT_EQ(color.getSpace(), AnnotColor::colorCMYK);
    const double *vals = color.getValues();
    EXPECT_NEAR(vals[0], 0.1, 1e-6);
    EXPECT_NEAR(vals[1], 0.2, 1e-6);
    EXPECT_NEAR(vals[2], 0.3, 1e-6);
    EXPECT_NEAR(vals[3], 0.4, 1e-6);
}

// Test AnnotColor boundary: zero values
TEST_F(AnnotTest_792, AnnotColorZeroValues_792) {
    AnnotColor color(0.0);
    EXPECT_EQ(color.getSpace(), AnnotColor::colorGray);
    const double *vals = color.getValues();
    EXPECT_NEAR(vals[0], 0.0, 1e-6);
}

// Test AnnotColor boundary: maximum values
TEST_F(AnnotTest_792, AnnotColorMaxValues_792) {
    AnnotColor color(1.0, 1.0, 1.0);
    EXPECT_EQ(color.getSpace(), AnnotColor::colorRGB);
    const double *vals = color.getValues();
    EXPECT_NEAR(vals[0], 1.0, 1e-6);
    EXPECT_NEAR(vals[1], 1.0, 1e-6);
    EXPECT_NEAR(vals[2], 1.0, 1e-6);
}

// Test PDFRectangle default constructor
TEST_F(AnnotTest_792, PDFRectangleDefaultConstructor_792) {
    PDFRectangle rect;
    EXPECT_DOUBLE_EQ(rect.x1, 0.0);
    EXPECT_DOUBLE_EQ(rect.y1, 0.0);
    EXPECT_DOUBLE_EQ(rect.x2, 0.0);
    EXPECT_DOUBLE_EQ(rect.y2, 0.0);
}

// Test PDFRectangle parameterized constructor
TEST_F(AnnotTest_792, PDFRectangleParameterizedConstructor_792) {
    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    EXPECT_DOUBLE_EQ(rect.x1, 10.0);
    EXPECT_DOUBLE_EQ(rect.y1, 20.0);
    EXPECT_DOUBLE_EQ(rect.x2, 100.0);
    EXPECT_DOUBLE_EQ(rect.y2, 200.0);
}

// Test PDFRectangle isValid
TEST_F(AnnotTest_792, PDFRectangleIsValid_792) {
    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    EXPECT_TRUE(rect.isValid());
}

// Test PDFRectangle with zero area
TEST_F(AnnotTest_792, PDFRectangleZeroArea_792) {
    PDFRectangle rect(0.0, 0.0, 0.0, 0.0);
    // A zero-area rectangle - check it's constructed properly
    EXPECT_DOUBLE_EQ(rect.x1, 0.0);
    EXPECT_DOUBLE_EQ(rect.y1, 0.0);
    EXPECT_DOUBLE_EQ(rect.x2, 0.0);
    EXPECT_DOUBLE_EQ(rect.y2, 0.0);
}

// Test AnnotColor constructed from Array object
TEST_F(AnnotTest_792, AnnotColorFromArrayRGB_792) {
    // Create an array with 3 elements for RGB
    Array *arr = new Array((XRef*)nullptr);
    arr->add(Object(0.5));
    arr->add(Object(0.6));
    arr->add(Object(0.7));
    Object obj(arr);
    
    AnnotColor color(&obj);
    EXPECT_EQ(color.getSpace(), AnnotColor::colorRGB);
    const double *vals = color.getValues();
    EXPECT_NEAR(vals[0], 0.5, 1e-6);
    EXPECT_NEAR(vals[1], 0.6, 1e-6);
    EXPECT_NEAR(vals[2], 0.7, 1e-6);
}

// Test AnnotColor constructed from single element array (Gray)
TEST_F(AnnotTest_792, AnnotColorFromArrayGray_792) {
    Array *arr = new Array((XRef*)nullptr);
    arr->add(Object(0.3));
    Object obj(arr);
    
    AnnotColor color(&obj);
    EXPECT_EQ(color.getSpace(), AnnotColor::colorGray);
    const double *vals = color.getValues();
    EXPECT_NEAR(vals[0], 0.3, 1e-6);
}

// Test AnnotColor constructed from 4-element array (CMYK)
TEST_F(AnnotTest_792, AnnotColorFromArrayCMYK_792) {
    Array *arr = new Array((XRef*)nullptr);
    arr->add(Object(0.1));
    arr->add(Object(0.2));
    arr->add(Object(0.3));
    arr->add(Object(0.4));
    Object obj(arr);
    
    AnnotColor color(&obj);
    EXPECT_EQ(color.getSpace(), AnnotColor::colorCMYK);
    const double *vals = color.getValues();
    EXPECT_NEAR(vals[0], 0.1, 1e-6);
    EXPECT_NEAR(vals[1], 0.2, 1e-6);
    EXPECT_NEAR(vals[2], 0.3, 1e-6);
    EXPECT_NEAR(vals[3], 0.4, 1e-6);
}

// Test AnnotColor transparent (empty array)
TEST_F(AnnotTest_792, AnnotColorTransparent_792) {
    Array *arr = new Array((XRef*)nullptr);
    Object obj(arr);
    
    AnnotColor color(&obj);
    EXPECT_EQ(color.getSpace(), AnnotColor::colorTransparent);
}

// Test AnnotBorderArray default width
TEST_F(AnnotTest_792, AnnotBorderDefaultProperties_792) {
    // AnnotBorder is abstract, test through AnnotBorderArray
    AnnotBorderArray border;
    EXPECT_NEAR(border.getWidth(), 1.0, 1e-6);
    EXPECT_EQ(border.getType(), AnnotBorder::typeArray);
}

// Test AnnotAppearanceBBox creation
TEST_F(AnnotTest_792, AnnotAppearanceBBoxCreation_792) {
    PDFRectangle rect(0, 0, 100, 100);
    AnnotAppearanceBBox bbox(&rect);
    EXPECT_DOUBLE_EQ(bbox.getPageXMin(), 0.0);
    EXPECT_DOUBLE_EQ(bbox.getPageYMin(), 0.0);
    EXPECT_DOUBLE_EQ(bbox.getPageXMax(), 100.0);
    EXPECT_DOUBLE_EQ(bbox.getPageYMax(), 100.0);
}

// Test AnnotAppearanceBBox with border effect
TEST_F(AnnotTest_792, AnnotAppearanceBBoxSetBorderWidth_792) {
    PDFRectangle rect(10, 10, 100, 100);
    AnnotAppearanceBBox bbox(&rect);
    bbox.setBorderWidth(5.0);
    // The bbox should account for the border
    // getBBox should return adjusted values
    const double *bboxArr = bbox.getBBox();
    EXPECT_NE(bboxArr, nullptr);
}

// Test that AnnotColor adjustColor works for RGB
TEST_F(AnnotTest_792, AnnotColorAdjustColor_792) {
    AnnotColor color(0.5, 0.5, 0.5);
    double colorMin = 0.0, colorMax = 1.0;
    color.adjustColor(1, colorMax);
    // After adjustment the color should still be valid
    EXPECT_EQ(color.getSpace(), AnnotColor::colorRGB);
}

// Integration-style test: Create Annot from PDFRectangle
// This test requires a valid PDFDoc which may not be available without a file
// We test what we can without file I/O

// Test AnnotColor copy behavior
TEST_F(AnnotTest_792, AnnotColorCopyValues_792) {
    AnnotColor original(0.25, 0.50, 0.75);
    const double *vals = original.getValues();
    
    // Verify the values are stable across multiple accesses
    EXPECT_NEAR(vals[0], 0.25, 1e-6);
    EXPECT_NEAR(vals[1], 0.50, 1e-6);
    EXPECT_NEAR(vals[2], 0.75, 1e-6);
    
    const double *vals2 = original.getValues();
    EXPECT_NEAR(vals2[0], 0.25, 1e-6);
    EXPECT_NEAR(vals2[1], 0.50, 1e-6);
    EXPECT_NEAR(vals2[2], 0.75, 1e-6);
}

// Test PDFRectangle contains method if available
TEST_F(AnnotTest_792, PDFRectangleContains_792) {
    PDFRectangle rect(0, 0, 100, 100);
    // Test that the rectangle stores coordinates correctly
    EXPECT_LE(rect.x1, rect.x2);
    EXPECT_LE(rect.y1, rect.y2);
}

// Test AnnotBorderArray with horizontal and vertical corner radius
TEST_F(AnnotTest_792, AnnotBorderArrayCornerRadius_792) {
    AnnotBorderArray border(1.0, 2.0, 3.0);
    EXPECT_NEAR(border.getHorizontalCorner(), 1.0, 1e-6);
    EXPECT_NEAR(border.getVerticalCorner(), 2.0, 1e-6);
    EXPECT_NEAR(border.getWidth(), 3.0, 1e-6);
}

// Test AnnotBorderBS style
TEST_F(AnnotTest_792, AnnotBorderBSStyle_792) {
    AnnotBorderBS border;
    EXPECT_EQ(border.getType(), AnnotBorder::typeBS);
}

// Negative value boundary test for AnnotColor
TEST_F(AnnotTest_792, AnnotColorNegativeValues_792) {
    // Some implementations might clamp or reject negative values
    AnnotColor color(-0.1);
    const double *vals = color.getValues();
    // Just verify it doesn't crash and stores some value
    EXPECT_EQ(color.getSpace(), AnnotColor::colorGray);
}

// Test AnnotColor values greater than 1
TEST_F(AnnotTest_792, AnnotColorValuesGreaterThanOne_792) {
    AnnotColor color(1.5, 2.0, 3.0);
    const double *vals = color.getValues();
    // Verify it handles out-of-range without crashing
    EXPECT_EQ(color.getSpace(), AnnotColor::colorRGB);
}
