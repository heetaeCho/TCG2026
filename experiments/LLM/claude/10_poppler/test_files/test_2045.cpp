#include <gtest/gtest.h>
#include <gmock/gmock.h>

extern "C" {
#include "poppler-document.h"
#include "poppler-annot.h"
#include "poppler-page.h"
}

#include "poppler-private.h"
#include "PDFDoc.h"

#include <memory>
#include <cstring>

class PopplerAnnotFreeTextTest_2045 : public ::testing::Test {
protected:
    PopplerDocument *doc = nullptr;
    
    void SetUp() override {
        // Create a minimal PDF document for testing
        // We use poppler's API to load a simple PDF if available
        GError *error = nullptr;
        
        // Create a minimal in-memory PDF
        const char *minimal_pdf = 
            "%PDF-1.4\n"
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
        
        if (error) {
            g_error_free(error);
            error = nullptr;
        }
        
        if (stream) {
            g_object_unref(stream);
        }
        g_bytes_unref(bytes);
    }
    
    void TearDown() override {
        if (doc) {
            g_object_unref(doc);
            doc = nullptr;
        }
    }
};

// Test that creating a free text annotation with valid parameters returns non-null
TEST_F(PopplerAnnotFreeTextTest_2045, CreateWithValidParams_2045) {
    if (!doc) {
        GTEST_SKIP() << "Could not create test document";
    }
    
    PopplerRectangle rect;
    rect.x1 = 100.0;
    rect.y1 = 100.0;
    rect.x2 = 200.0;
    rect.y2 = 200.0;
    
    PopplerAnnot *annot = poppler_annot_free_text_new(doc, &rect);
    ASSERT_NE(annot, nullptr);
    
    // Verify the annotation type is free text
    PopplerAnnotType type = poppler_annot_get_annot_type(annot);
    EXPECT_EQ(type, POPPLER_ANNOT_FREE_TEXT);
    
    g_object_unref(annot);
}

// Test with zero-area rectangle
TEST_F(PopplerAnnotFreeTextTest_2045, CreateWithZeroAreaRect_2045) {
    if (!doc) {
        GTEST_SKIP() << "Could not create test document";
    }
    
    PopplerRectangle rect;
    rect.x1 = 100.0;
    rect.y1 = 100.0;
    rect.x2 = 100.0;
    rect.y2 = 100.0;
    
    PopplerAnnot *annot = poppler_annot_free_text_new(doc, &rect);
    ASSERT_NE(annot, nullptr);
    
    PopplerAnnotType type = poppler_annot_get_annot_type(annot);
    EXPECT_EQ(type, POPPLER_ANNOT_FREE_TEXT);
    
    g_object_unref(annot);
}

// Test with negative coordinates
TEST_F(PopplerAnnotFreeTextTest_2045, CreateWithNegativeCoordinates_2045) {
    if (!doc) {
        GTEST_SKIP() << "Could not create test document";
    }
    
    PopplerRectangle rect;
    rect.x1 = -50.0;
    rect.y1 = -50.0;
    rect.x2 = 50.0;
    rect.y2 = 50.0;
    
    PopplerAnnot *annot = poppler_annot_free_text_new(doc, &rect);
    ASSERT_NE(annot, nullptr);
    
    PopplerAnnotType type = poppler_annot_get_annot_type(annot);
    EXPECT_EQ(type, POPPLER_ANNOT_FREE_TEXT);
    
    g_object_unref(annot);
}

// Test with large coordinates
TEST_F(PopplerAnnotFreeTextTest_2045, CreateWithLargeCoordinates_2045) {
    if (!doc) {
        GTEST_SKIP() << "Could not create test document";
    }
    
    PopplerRectangle rect;
    rect.x1 = 0.0;
    rect.y1 = 0.0;
    rect.x2 = 10000.0;
    rect.y2 = 10000.0;
    
    PopplerAnnot *annot = poppler_annot_free_text_new(doc, &rect);
    ASSERT_NE(annot, nullptr);
    
    PopplerAnnotType type = poppler_annot_get_annot_type(annot);
    EXPECT_EQ(type, POPPLER_ANNOT_FREE_TEXT);
    
    g_object_unref(annot);
}

// Test with inverted rectangle (x1 > x2, y1 > y2)
TEST_F(PopplerAnnotFreeTextTest_2045, CreateWithInvertedRect_2045) {
    if (!doc) {
        GTEST_SKIP() << "Could not create test document";
    }
    
    PopplerRectangle rect;
    rect.x1 = 200.0;
    rect.y1 = 200.0;
    rect.x2 = 100.0;
    rect.y2 = 100.0;
    
    PopplerAnnot *annot = poppler_annot_free_text_new(doc, &rect);
    ASSERT_NE(annot, nullptr);
    
    g_object_unref(annot);
}

// Test creating multiple annotations from the same document
TEST_F(PopplerAnnotFreeTextTest_2045, CreateMultipleAnnotations_2045) {
    if (!doc) {
        GTEST_SKIP() << "Could not create test document";
    }
    
    PopplerRectangle rect1 = {10.0, 10.0, 50.0, 50.0};
    PopplerRectangle rect2 = {60.0, 60.0, 100.0, 100.0};
    
    PopplerAnnot *annot1 = poppler_annot_free_text_new(doc, &rect1);
    PopplerAnnot *annot2 = poppler_annot_free_text_new(doc, &rect2);
    
    ASSERT_NE(annot1, nullptr);
    ASSERT_NE(annot2, nullptr);
    EXPECT_NE(annot1, annot2);
    
    EXPECT_EQ(poppler_annot_get_annot_type(annot1), POPPLER_ANNOT_FREE_TEXT);
    EXPECT_EQ(poppler_annot_get_annot_type(annot2), POPPLER_ANNOT_FREE_TEXT);
    
    g_object_unref(annot1);
    g_object_unref(annot2);
}

// Test with fractional coordinates
TEST_F(PopplerAnnotFreeTextTest_2045, CreateWithFractionalCoordinates_2045) {
    if (!doc) {
        GTEST_SKIP() << "Could not create test document";
    }
    
    PopplerRectangle rect;
    rect.x1 = 10.5;
    rect.y1 = 20.7;
    rect.x2 = 30.3;
    rect.y2 = 40.9;
    
    PopplerAnnot *annot = poppler_annot_free_text_new(doc, &rect);
    ASSERT_NE(annot, nullptr);
    
    PopplerAnnotType type = poppler_annot_get_annot_type(annot);
    EXPECT_EQ(type, POPPLER_ANNOT_FREE_TEXT);
    
    g_object_unref(annot);
}
