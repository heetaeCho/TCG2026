#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include necessary headers
#include "poppler-annot.h"
#include "poppler-document.h"
#include "poppler-private.h"
#include "poppler-page.h"

extern "C" {
#include <glib-object.h>
}

class PopplerAnnotInkNewTest_2135 : public ::testing::Test {
protected:
    PopplerDocument *doc = nullptr;

    void SetUp() override {
        // Create a minimal PDF document for testing
        // We need a valid PopplerDocument to pass to poppler_annot_ink_new
        GError *error = nullptr;
        // Create a simple PDF in memory or from a minimal file
        // Using a minimal valid PDF
        const char *minimal_pdf = 
            "%PDF-1.0\n"
            "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
            "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
            "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
            "xref\n"
            "0 4\n"
            "0000000000 65535 f \n"
            "0000000009 00000 n \n"
            "0000000058 00000 n \n"
            "0000000115 00000 n \n"
            "trailer<</Size 4/Root 1 0 R>>\n"
            "startxref\n"
            "190\n"
            "%%EOF\n";

        gsize len = strlen(minimal_pdf);
        GBytes *bytes = g_bytes_new(minimal_pdf, len);
        GInputStream *stream = g_memory_input_stream_new_from_bytes(bytes);
        
        doc = poppler_document_new_from_stream(stream, len, nullptr, nullptr, &error);
        
        if (doc == nullptr && error != nullptr) {
            // Try alternative approach - create from data
            g_clear_error(&error);
            g_object_unref(stream);
            g_bytes_unref(bytes);
            
            doc = poppler_document_new_from_data((char*)minimal_pdf, (int)len, nullptr, &error);
        } else {
            g_object_unref(stream);
            g_bytes_unref(bytes);
        }
        
        if (error) {
            g_error_free(error);
        }
    }

    void TearDown() override {
        if (doc) {
            g_object_unref(doc);
            doc = nullptr;
        }
    }
};

// Test that poppler_annot_ink_new returns a non-null annotation with valid inputs
TEST_F(PopplerAnnotInkNewTest_2135, ReturnsNonNullAnnot_2135) {
    if (!doc) GTEST_SKIP() << "Could not create test document";
    
    PopplerRectangle rect;
    rect.x1 = 10.0;
    rect.y1 = 20.0;
    rect.x2 = 100.0;
    rect.y2 = 200.0;

    PopplerAnnot *annot = poppler_annot_ink_new(doc, &rect);
    ASSERT_NE(annot, nullptr);
    
    g_object_unref(annot);
}

// Test that the returned annotation is of type INK
TEST_F(PopplerAnnotInkNewTest_2135, ReturnsInkAnnotType_2135) {
    if (!doc) GTEST_SKIP() << "Could not create test document";
    
    PopplerRectangle rect;
    rect.x1 = 10.0;
    rect.y1 = 20.0;
    rect.x2 = 100.0;
    rect.y2 = 200.0;

    PopplerAnnot *annot = poppler_annot_ink_new(doc, &rect);
    ASSERT_NE(annot, nullptr);
    
    PopplerAnnotType type = poppler_annot_get_annot_type(annot);
    EXPECT_EQ(type, POPPLER_ANNOT_INK);
    
    g_object_unref(annot);
}

// Test with zero-sized rectangle
TEST_F(PopplerAnnotInkNewTest_2135, ZeroSizedRectangle_2135) {
    if (!doc) GTEST_SKIP() << "Could not create test document";
    
    PopplerRectangle rect;
    rect.x1 = 0.0;
    rect.y1 = 0.0;
    rect.x2 = 0.0;
    rect.y2 = 0.0;

    PopplerAnnot *annot = poppler_annot_ink_new(doc, &rect);
    ASSERT_NE(annot, nullptr);
    
    g_object_unref(annot);
}

// Test with negative coordinates
TEST_F(PopplerAnnotInkNewTest_2135, NegativeCoordinates_2135) {
    if (!doc) GTEST_SKIP() << "Could not create test document";
    
    PopplerRectangle rect;
    rect.x1 = -50.0;
    rect.y1 = -50.0;
    rect.x2 = -10.0;
    rect.y2 = -10.0;

    PopplerAnnot *annot = poppler_annot_ink_new(doc, &rect);
    ASSERT_NE(annot, nullptr);
    
    g_object_unref(annot);
}

// Test with large coordinates
TEST_F(PopplerAnnotInkNewTest_2135, LargeCoordinates_2135) {
    if (!doc) GTEST_SKIP() << "Could not create test document";
    
    PopplerRectangle rect;
    rect.x1 = 0.0;
    rect.y1 = 0.0;
    rect.x2 = 100000.0;
    rect.y2 = 100000.0;

    PopplerAnnot *annot = poppler_annot_ink_new(doc, &rect);
    ASSERT_NE(annot, nullptr);
    
    g_object_unref(annot);
}

// Test with inverted rectangle (x1 > x2, y1 > y2)
TEST_F(PopplerAnnotInkNewTest_2135, InvertedRectangle_2135) {
    if (!doc) GTEST_SKIP() << "Could not create test document";
    
    PopplerRectangle rect;
    rect.x1 = 100.0;
    rect.y1 = 200.0;
    rect.x2 = 10.0;
    rect.y2 = 20.0;

    PopplerAnnot *annot = poppler_annot_ink_new(doc, &rect);
    ASSERT_NE(annot, nullptr);
    
    g_object_unref(annot);
}

// Test that the annotation is a valid GObject (can be type-checked)
TEST_F(PopplerAnnotInkNewTest_2135, IsValidGObject_2135) {
    if (!doc) GTEST_SKIP() << "Could not create test document";
    
    PopplerRectangle rect;
    rect.x1 = 10.0;
    rect.y1 = 20.0;
    rect.x2 = 100.0;
    rect.y2 = 200.0;

    PopplerAnnot *annot = poppler_annot_ink_new(doc, &rect);
    ASSERT_NE(annot, nullptr);
    
    EXPECT_TRUE(POPPLER_IS_ANNOT(annot));
    
    g_object_unref(annot);
}

// Test with fractional coordinates
TEST_F(PopplerAnnotInkNewTest_2135, FractionalCoordinates_2135) {
    if (!doc) GTEST_SKIP() << "Could not create test document";
    
    PopplerRectangle rect;
    rect.x1 = 10.5;
    rect.y1 = 20.75;
    rect.x2 = 100.25;
    rect.y2 = 200.125;

    PopplerAnnot *annot = poppler_annot_ink_new(doc, &rect);
    ASSERT_NE(annot, nullptr);
    
    PopplerAnnotType type = poppler_annot_get_annot_type(annot);
    EXPECT_EQ(type, POPPLER_ANNOT_INK);
    
    g_object_unref(annot);
}

// Test creating multiple ink annotations from same document
TEST_F(PopplerAnnotInkNewTest_2135, MultipleAnnotsFromSameDoc_2135) {
    if (!doc) GTEST_SKIP() << "Could not create test document";
    
    PopplerRectangle rect1 = {10.0, 20.0, 100.0, 200.0};
    PopplerRectangle rect2 = {50.0, 60.0, 150.0, 250.0};

    PopplerAnnot *annot1 = poppler_annot_ink_new(doc, &rect1);
    PopplerAnnot *annot2 = poppler_annot_ink_new(doc, &rect2);
    
    ASSERT_NE(annot1, nullptr);
    ASSERT_NE(annot2, nullptr);
    EXPECT_NE(annot1, annot2);
    
    g_object_unref(annot1);
    g_object_unref(annot2);
}

// Test with unit rectangle
TEST_F(PopplerAnnotInkNewTest_2135, UnitRectangle_2135) {
    if (!doc) GTEST_SKIP() << "Could not create test document";
    
    PopplerRectangle rect;
    rect.x1 = 0.0;
    rect.y1 = 0.0;
    rect.x2 = 1.0;
    rect.y2 = 1.0;

    PopplerAnnot *annot = poppler_annot_ink_new(doc, &rect);
    ASSERT_NE(annot, nullptr);
    
    PopplerAnnotType type = poppler_annot_get_annot_type(annot);
    EXPECT_EQ(type, POPPLER_ANNOT_INK);
    
    g_object_unref(annot);
}
