#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Poppler GLib headers
extern "C" {
#include "poppler.h"
#include "poppler-document.h"
#include "poppler-page.h"
}

#include <cstring>
#include <cstdlib>

class PopplerAnnotSquareNewTest_2058 : public ::testing::Test {
protected:
    PopplerDocument *doc = nullptr;

    void SetUp() override {
        // Create a minimal PDF in memory to get a valid PopplerDocument
        // We need a valid document to test annotation creation
        GError *error = nullptr;
        
        // Try to create a document from a minimal PDF buffer
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
        doc = poppler_document_new_from_data(minimal_pdf, (int)len, nullptr, &error);
        if (error) {
            g_error_free(error);
            error = nullptr;
        }
    }

    void TearDown() override {
        if (doc) {
            g_object_unref(doc);
            doc = nullptr;
        }
    }
};

// Test that creating a square annotation with valid parameters returns non-null
TEST_F(PopplerAnnotSquareNewTest_2058, ValidCreation_2058) {
    if (!doc) {
        GTEST_SKIP() << "Could not create test document";
    }
    
    PopplerRectangle rect;
    rect.x1 = 100.0;
    rect.y1 = 100.0;
    rect.x2 = 200.0;
    rect.y2 = 200.0;
    
    PopplerAnnot *annot = poppler_annot_square_new(doc, &rect);
    ASSERT_NE(annot, nullptr);
    
    // Verify the annotation type is square
    PopplerAnnotType type = poppler_annot_get_annot_type(annot);
    EXPECT_EQ(type, POPPLER_ANNOT_SQUARE);
    
    g_object_unref(annot);
}

// Test with zero-size rectangle
TEST_F(PopplerAnnotSquareNewTest_2058, ZeroSizeRectangle_2058) {
    if (!doc) {
        GTEST_SKIP() << "Could not create test document";
    }
    
    PopplerRectangle rect;
    rect.x1 = 100.0;
    rect.y1 = 100.0;
    rect.x2 = 100.0;
    rect.y2 = 100.0;
    
    PopplerAnnot *annot = poppler_annot_square_new(doc, &rect);
    ASSERT_NE(annot, nullptr);
    
    PopplerAnnotType type = poppler_annot_get_annot_type(annot);
    EXPECT_EQ(type, POPPLER_ANNOT_SQUARE);
    
    g_object_unref(annot);
}

// Test with negative coordinates
TEST_F(PopplerAnnotSquareNewTest_2058, NegativeCoordinates_2058) {
    if (!doc) {
        GTEST_SKIP() << "Could not create test document";
    }
    
    PopplerRectangle rect;
    rect.x1 = -50.0;
    rect.y1 = -50.0;
    rect.x2 = 50.0;
    rect.y2 = 50.0;
    
    PopplerAnnot *annot = poppler_annot_square_new(doc, &rect);
    ASSERT_NE(annot, nullptr);
    
    PopplerAnnotType type = poppler_annot_get_annot_type(annot);
    EXPECT_EQ(type, POPPLER_ANNOT_SQUARE);
    
    g_object_unref(annot);
}

// Test with large coordinates
TEST_F(PopplerAnnotSquareNewTest_2058, LargeCoordinates_2058) {
    if (!doc) {
        GTEST_SKIP() << "Could not create test document";
    }
    
    PopplerRectangle rect;
    rect.x1 = 0.0;
    rect.y1 = 0.0;
    rect.x2 = 100000.0;
    rect.y2 = 100000.0;
    
    PopplerAnnot *annot = poppler_annot_square_new(doc, &rect);
    ASSERT_NE(annot, nullptr);
    
    PopplerAnnotType type = poppler_annot_get_annot_type(annot);
    EXPECT_EQ(type, POPPLER_ANNOT_SQUARE);
    
    g_object_unref(annot);
}

// Test with inverted rectangle (x1 > x2, y1 > y2)
TEST_F(PopplerAnnotSquareNewTest_2058, InvertedRectangle_2058) {
    if (!doc) {
        GTEST_SKIP() << "Could not create test document";
    }
    
    PopplerRectangle rect;
    rect.x1 = 200.0;
    rect.y1 = 200.0;
    rect.x2 = 100.0;
    rect.y2 = 100.0;
    
    PopplerAnnot *annot = poppler_annot_square_new(doc, &rect);
    ASSERT_NE(annot, nullptr);
    
    PopplerAnnotType type = poppler_annot_get_annot_type(annot);
    EXPECT_EQ(type, POPPLER_ANNOT_SQUARE);
    
    g_object_unref(annot);
}

// Test that the returned annotation is a GObject and can be ref/unref'd
TEST_F(PopplerAnnotSquareNewTest_2058, IsGObject_2058) {
    if (!doc) {
        GTEST_SKIP() << "Could not create test document";
    }
    
    PopplerRectangle rect;
    rect.x1 = 10.0;
    rect.y1 = 10.0;
    rect.x2 = 50.0;
    rect.y2 = 50.0;
    
    PopplerAnnot *annot = poppler_annot_square_new(doc, &rect);
    ASSERT_NE(annot, nullptr);
    EXPECT_TRUE(G_IS_OBJECT(annot));
    
    g_object_unref(annot);
}

// Test with fractional coordinates
TEST_F(PopplerAnnotSquareNewTest_2058, FractionalCoordinates_2058) {
    if (!doc) {
        GTEST_SKIP() << "Could not create test document";
    }
    
    PopplerRectangle rect;
    rect.x1 = 10.5;
    rect.y1 = 20.75;
    rect.x2 = 30.25;
    rect.y2 = 40.125;
    
    PopplerAnnot *annot = poppler_annot_square_new(doc, &rect);
    ASSERT_NE(annot, nullptr);
    
    PopplerAnnotType type = poppler_annot_get_annot_type(annot);
    EXPECT_EQ(type, POPPLER_ANNOT_SQUARE);
    
    g_object_unref(annot);
}

// Test creating multiple square annotations from the same document
TEST_F(PopplerAnnotSquareNewTest_2058, MultipleAnnotations_2058) {
    if (!doc) {
        GTEST_SKIP() << "Could not create test document";
    }
    
    PopplerRectangle rect1 = {10.0, 10.0, 50.0, 50.0};
    PopplerRectangle rect2 = {60.0, 60.0, 100.0, 100.0};
    
    PopplerAnnot *annot1 = poppler_annot_square_new(doc, &rect1);
    PopplerAnnot *annot2 = poppler_annot_square_new(doc, &rect2);
    
    ASSERT_NE(annot1, nullptr);
    ASSERT_NE(annot2, nullptr);
    EXPECT_NE(annot1, annot2);
    
    EXPECT_EQ(poppler_annot_get_annot_type(annot1), POPPLER_ANNOT_SQUARE);
    EXPECT_EQ(poppler_annot_get_annot_type(annot2), POPPLER_ANNOT_SQUARE);
    
    g_object_unref(annot1);
    g_object_unref(annot2);
}
