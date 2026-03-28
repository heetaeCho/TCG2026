#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

// Include necessary headers
#include "poppler-annot.h"
#include "poppler-private.h"
#include "Annot.h"
#include "PDFDoc.h"

// We need to include glib headers for PopplerAnnot and PopplerColor
#include <glib-object.h>

class PopplerAnnotGeometryInteriorColorTest_2113 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that getting interior color from a geometry annotation with no interior color returns nullptr
TEST_F(PopplerAnnotGeometryInteriorColorTest_2113, NullInteriorColorReturnsNull_2113)
{
    // Create a PopplerAnnot wrapping an AnnotGeometry with no interior color set
    // When interior color is not set, getInteriorColor() returns nullptr,
    // and the conversion function should return nullptr as well
    
    // We need a PDFDoc and rectangle to create AnnotGeometry
    PDFRectangle rect(0, 0, 100, 100);
    
    // Note: This test depends on being able to construct the objects.
    // If construction requires a valid PDFDoc, we may need to create one.
    // For now, we test through the public GLib API if possible.
    
    // Create a GObject-based PopplerAnnot
    PopplerAnnot *poppler_annot = static_cast<PopplerAnnot *>(g_object_new(POPPLER_TYPE_ANNOT, nullptr));
    if (poppler_annot == nullptr) {
        GTEST_SKIP() << "Cannot create PopplerAnnot without valid backing";
        return;
    }
    
    // If we can set up the annot member with a geometry annotation that has no interior color
    // This tests the null path
    auto geom_annot = std::make_shared<AnnotGeometry>(nullptr, &rect, Annot::typeSquare);
    poppler_annot->annot = geom_annot;
    
    // The interior color should be null if none was set
    PopplerColor *color = poppler_annot_geometry_get_interior_color(poppler_annot);
    
    // If no interior color was set, we expect nullptr
    EXPECT_EQ(color, nullptr);
    
    g_object_unref(poppler_annot);
}

// Test that getting interior color from a geometry annotation with a set interior color returns non-null
TEST_F(PopplerAnnotGeometryInteriorColorTest_2113, SetInteriorColorReturnsColor_2113)
{
    PDFRectangle rect(0, 0, 100, 100);
    
    PopplerAnnot *poppler_annot = static_cast<PopplerAnnot *>(g_object_new(POPPLER_TYPE_ANNOT, nullptr));
    if (poppler_annot == nullptr) {
        GTEST_SKIP() << "Cannot create PopplerAnnot without valid backing";
        return;
    }
    
    auto geom_annot = std::make_shared<AnnotGeometry>(nullptr, &rect, Annot::typeSquare);
    
    // Set an interior color - RGB red
    auto annot_color = std::make_unique<AnnotColor>(1.0, 0.0, 0.0);
    geom_annot->setInteriorColor(std::move(annot_color));
    
    poppler_annot->annot = geom_annot;
    
    PopplerColor *color = poppler_annot_geometry_get_interior_color(poppler_annot);
    
    // Color should be non-null since we set one
    EXPECT_NE(color, nullptr);
    
    if (color) {
        // Red component should be max (65535 in PopplerColor scale)
        EXPECT_EQ(color->red, 65535);
        EXPECT_EQ(color->green, 0);
        EXPECT_EQ(color->blue, 0);
        g_free(color);
    }
    
    g_object_unref(poppler_annot);
}

// Test with a circle (ellipse) subtype geometry annotation
TEST_F(PopplerAnnotGeometryInteriorColorTest_2113, CircleAnnotInteriorColor_2113)
{
    PDFRectangle rect(0, 0, 200, 200);
    
    PopplerAnnot *poppler_annot = static_cast<PopplerAnnot *>(g_object_new(POPPLER_TYPE_ANNOT, nullptr));
    if (poppler_annot == nullptr) {
        GTEST_SKIP() << "Cannot create PopplerAnnot without valid backing";
        return;
    }
    
    auto geom_annot = std::make_shared<AnnotGeometry>(nullptr, &rect, Annot::typeCircle);
    
    // Set an interior color - green
    auto annot_color = std::make_unique<AnnotColor>(0.0, 1.0, 0.0);
    geom_annot->setInteriorColor(std::move(annot_color));
    
    poppler_annot->annot = geom_annot;
    
    PopplerColor *color = poppler_annot_geometry_get_interior_color(poppler_annot);
    
    EXPECT_NE(color, nullptr);
    
    if (color) {
        EXPECT_EQ(color->red, 0);
        EXPECT_EQ(color->green, 65535);
        EXPECT_EQ(color->blue, 0);
        g_free(color);
    }
    
    g_object_unref(poppler_annot);
}

// Test with white interior color
TEST_F(PopplerAnnotGeometryInteriorColorTest_2113, WhiteInteriorColor_2113)
{
    PDFRectangle rect(0, 0, 50, 50);
    
    PopplerAnnot *poppler_annot = static_cast<PopplerAnnot *>(g_object_new(POPPLER_TYPE_ANNOT, nullptr));
    if (poppler_annot == nullptr) {
        GTEST_SKIP() << "Cannot create PopplerAnnot without valid backing";
        return;
    }
    
    auto geom_annot = std::make_shared<AnnotGeometry>(nullptr, &rect, Annot::typeSquare);
    
    auto annot_color = std::make_unique<AnnotColor>(1.0, 1.0, 1.0);
    geom_annot->setInteriorColor(std::move(annot_color));
    
    poppler_annot->annot = geom_annot;
    
    PopplerColor *color = poppler_annot_geometry_get_interior_color(poppler_annot);
    
    EXPECT_NE(color, nullptr);
    
    if (color) {
        EXPECT_EQ(color->red, 65535);
        EXPECT_EQ(color->green, 65535);
        EXPECT_EQ(color->blue, 65535);
        g_free(color);
    }
    
    g_object_unref(poppler_annot);
}

// Test with black interior color (boundary: all zeros)
TEST_F(PopplerAnnotGeometryInteriorColorTest_2113, BlackInteriorColor_2113)
{
    PDFRectangle rect(0, 0, 50, 50);
    
    PopplerAnnot *poppler_annot = static_cast<PopplerAnnot *>(g_object_new(POPPLER_TYPE_ANNOT, nullptr));
    if (poppler_annot == nullptr) {
        GTEST_SKIP() << "Cannot create PopplerAnnot without valid backing";
        return;
    }
    
    auto geom_annot = std::make_shared<AnnotGeometry>(nullptr, &rect, Annot::typeSquare);
    
    auto annot_color = std::make_unique<AnnotColor>(0.0, 0.0, 0.0);
    geom_annot->setInteriorColor(std::move(annot_color));
    
    poppler_annot->annot = geom_annot;
    
    PopplerColor *color = poppler_annot_geometry_get_interior_color(poppler_annot);
    
    EXPECT_NE(color, nullptr);
    
    if (color) {
        EXPECT_EQ(color->red, 0);
        EXPECT_EQ(color->green, 0);
        EXPECT_EQ(color->blue, 0);
        g_free(color);
    }
    
    g_object_unref(poppler_annot);
}

// Test with mid-range color values
TEST_F(PopplerAnnotGeometryInteriorColorTest_2113, MidRangeInteriorColor_2113)
{
    PDFRectangle rect(0, 0, 50, 50);
    
    PopplerAnnot *poppler_annot = static_cast<PopplerAnnot *>(g_object_new(POPPLER_TYPE_ANNOT, nullptr));
    if (poppler_annot == nullptr) {
        GTEST_SKIP() << "Cannot create PopplerAnnot without valid backing";
        return;
    }
    
    auto geom_annot = std::make_shared<AnnotGeometry>(nullptr, &rect, Annot::typeSquare);
    
    // 0.5 should map to approximately 32767-32768 in 16-bit range
    auto annot_color = std::make_unique<AnnotColor>(0.5, 0.5, 0.5);
    geom_annot->setInteriorColor(std::move(annot_color));
    
    poppler_annot->annot = geom_annot;
    
    PopplerColor *color = poppler_annot_geometry_get_interior_color(poppler_annot);
    
    EXPECT_NE(color, nullptr);
    
    if (color) {
        // 0.5 * 65535 = 32767 or 32768 depending on rounding
        EXPECT_NEAR(color->red, 32767, 1);
        EXPECT_NEAR(color->green, 32767, 1);
        EXPECT_NEAR(color->blue, 32767, 1);
        g_free(color);
    }
    
    g_object_unref(poppler_annot);
}
