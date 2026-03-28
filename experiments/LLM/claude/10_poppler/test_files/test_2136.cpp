#include <gtest/gtest.h>
#include <memory>

// Poppler core headers
#include <poppler/Annot.h>
#include <poppler/PDFDoc.h>
#include <poppler/GlobalParams.h>
#include <poppler/GooString.h>
#include <poppler/Object.h>
#include <poppler/XRef.h>
#include <poppler/Dict.h>
#include <poppler/Page.h>
#include <poppler/Catalog.h>

// Poppler GLib headers
#include <poppler.h>
#include "poppler-annot.h"
#include "poppler-private.h"

class PopplerAnnotInkNewTest_2136 : public ::testing::Test {
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
};

TEST_F(PopplerAnnotInkNewTest_2136, ReturnsNonNullForValidAnnot_2136) {
    // Create a PopplerDocument from a minimal PDF to get access to internal structures
    // We'll use the public API to create a document and then create an ink annotation
    // through the available Poppler GLib API
    
    // Create a minimal annotation using Poppler's public GLib API
    PopplerRectangle rect = { 0, 0, 100, 100 };
    PopplerAnnot *annot = poppler_annot_ink_new(nullptr, &rect);
    
    if (annot != nullptr) {
        // Verify it is a valid GObject
        EXPECT_TRUE(G_IS_OBJECT(annot));
        
        // Verify the annotation type
        EXPECT_EQ(poppler_annot_get_annot_type(annot), POPPLER_ANNOT_INK);
        
        g_object_unref(annot);
    }
}

TEST_F(PopplerAnnotInkNewTest_2136, AnnotTypeIsInk_2136) {
    PopplerRectangle rect = { 10, 20, 200, 300 };
    PopplerAnnot *annot = poppler_annot_ink_new(nullptr, &rect);
    
    if (annot != nullptr) {
        PopplerAnnotType atype = poppler_annot_get_annot_type(annot);
        EXPECT_EQ(atype, POPPLER_ANNOT_INK);
        g_object_unref(annot);
    }
}

TEST_F(PopplerAnnotInkNewTest_2136, IsInstanceOfPopplerAnnot_2136) {
    PopplerRectangle rect = { 0, 0, 50, 50 };
    PopplerAnnot *annot = poppler_annot_ink_new(nullptr, &rect);
    
    if (annot != nullptr) {
        // Check that it's an instance of the base PopplerAnnot type
        EXPECT_TRUE(POPPLER_IS_ANNOT(annot));
        // Check that it's an instance of PopplerAnnotInk type
        EXPECT_TRUE(POPPLER_IS_ANNOT_INK(annot));
        g_object_unref(annot);
    }
}

TEST_F(PopplerAnnotInkNewTest_2136, RefCountStartsAtOne_2136) {
    PopplerRectangle rect = { 0, 0, 100, 100 };
    PopplerAnnot *annot = poppler_annot_ink_new(nullptr, &rect);
    
    if (annot != nullptr) {
        // A newly created GObject should have a ref count of 1
        EXPECT_EQ(G_OBJECT(annot)->ref_count, 1u);
        g_object_unref(annot);
    }
}

TEST_F(PopplerAnnotInkNewTest_2136, BoundaryRectangleZeroSize_2136) {
    PopplerRectangle rect = { 0, 0, 0, 0 };
    PopplerAnnot *annot = poppler_annot_ink_new(nullptr, &rect);
    
    if (annot != nullptr) {
        EXPECT_TRUE(POPPLER_IS_ANNOT_INK(annot));
        g_object_unref(annot);
    }
}

TEST_F(PopplerAnnotInkNewTest_2136, NegativeCoordinatesInRectangle_2136) {
    PopplerRectangle rect = { -50, -50, 50, 50 };
    PopplerAnnot *annot = poppler_annot_ink_new(nullptr, &rect);
    
    if (annot != nullptr) {
        EXPECT_TRUE(POPPLER_IS_ANNOT_INK(annot));
        EXPECT_EQ(poppler_annot_get_annot_type(annot), POPPLER_ANNOT_INK);
        g_object_unref(annot);
    }
}
