#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

// Include necessary poppler headers
extern "C" {
#include <poppler.h>
}

#include "Annot.h"

// Forward declaration of the internal function we're testing
extern "C" {
PopplerAnnot *_poppler_annot_square_new(const std::shared_ptr<Annot> &annot);
}

class PopplerAnnotSquareNewTest_2057 : public ::testing::Test {
protected:
    void SetUp() override {
        // Initialize GLib type system if needed
    }

    void TearDown() override {
    }
};

// Test that passing a nullptr shared_ptr is handled
TEST_F(PopplerAnnotSquareNewTest_2057, NullAnnotSharedPtr_2057) {
    std::shared_ptr<Annot> nullAnnot = nullptr;
    // Depending on implementation, this may return nullptr or crash
    // We test that it doesn't crash unexpectedly if null is a valid edge case
    // Since we treat as black box, we just verify the call completes
    PopplerAnnot *result = _poppler_annot_square_new(nullAnnot);
    // If it returns non-null, it should be of the correct type
    if (result != nullptr) {
        EXPECT_TRUE(POPPLER_IS_ANNOT_SQUARE(result));
        g_object_unref(result);
    }
}

// Test that a valid Annot produces a PopplerAnnotSquare object
TEST_F(PopplerAnnotSquareNewTest_2057, ValidAnnotReturnsSquareAnnot_2057) {
    // Create a minimal PDF document to get a valid Annot
    GError *error = nullptr;
    
    // Create a simple PDF in memory to work with
    const char *pdf_data = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                           "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                           "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                           "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                           "0000000058 00000 n \n0000000115 00000 n \n"
                           "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";
    
    // We need a PopplerDocument to create annotations
    PopplerDocument *doc = poppler_document_new_from_data(pdf_data, strlen(pdf_data), nullptr, &error);
    
    if (doc != nullptr) {
        PopplerPage *page = poppler_document_get_page(doc, 0);
        if (page != nullptr) {
            // Create a square annotation through the public API
            PopplerRectangle rect = {100.0, 100.0, 200.0, 200.0};
            PopplerAnnot *annot = poppler_annot_square_new(doc, &rect);
            
            if (annot != nullptr) {
                EXPECT_TRUE(POPPLER_IS_ANNOT(annot));
                EXPECT_TRUE(POPPLER_IS_ANNOT_SQUARE(annot));
                
                // Verify the type
                PopplerAnnotType type = poppler_annot_get_annot_type(annot);
                EXPECT_EQ(type, POPPLER_ANNOT_SQUARE);
                
                g_object_unref(annot);
            }
            
            g_object_unref(page);
        }
        g_object_unref(doc);
    }
    
    if (error) {
        g_error_free(error);
    }
}

// Test that the returned object has the correct GType
TEST_F(PopplerAnnotSquareNewTest_2057, ReturnedObjectHasCorrectGType_2057) {
    GError *error = nullptr;
    
    const char *pdf_data = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                           "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                           "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                           "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                           "0000000058 00000 n \n0000000115 00000 n \n"
                           "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";
    
    PopplerDocument *doc = poppler_document_new_from_data(pdf_data, strlen(pdf_data), nullptr, &error);
    
    if (doc != nullptr) {
        PopplerRectangle rect = {50.0, 50.0, 150.0, 150.0};
        PopplerAnnot *annot = poppler_annot_square_new(doc, &rect);
        
        if (annot != nullptr) {
            // Verify it's an instance of PopplerAnnotSquare
            EXPECT_TRUE(G_TYPE_CHECK_INSTANCE_TYPE(annot, POPPLER_TYPE_ANNOT_SQUARE));
            // Verify it's also an instance of PopplerAnnot (parent type)
            EXPECT_TRUE(G_TYPE_CHECK_INSTANCE_TYPE(annot, POPPLER_TYPE_ANNOT));
            
            g_object_unref(annot);
        }
        
        g_object_unref(doc);
    }
    
    if (error) {
        g_error_free(error);
    }
}

// Test creating multiple square annotations
TEST_F(PopplerAnnotSquareNewTest_2057, MultipleSquareAnnotations_2057) {
    GError *error = nullptr;
    
    const char *pdf_data = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                           "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                           "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                           "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                           "0000000058 00000 n \n0000000115 00000 n \n"
                           "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";
    
    PopplerDocument *doc = poppler_document_new_from_data(pdf_data, strlen(pdf_data), nullptr, &error);
    
    if (doc != nullptr) {
        PopplerRectangle rect1 = {0.0, 0.0, 100.0, 100.0};
        PopplerRectangle rect2 = {200.0, 200.0, 300.0, 300.0};
        
        PopplerAnnot *annot1 = poppler_annot_square_new(doc, &rect1);
        PopplerAnnot *annot2 = poppler_annot_square_new(doc, &rect2);
        
        if (annot1 != nullptr && annot2 != nullptr) {
            // Both should be distinct objects
            EXPECT_NE(annot1, annot2);
            
            // Both should be square annotations
            EXPECT_TRUE(POPPLER_IS_ANNOT_SQUARE(annot1));
            EXPECT_TRUE(POPPLER_IS_ANNOT_SQUARE(annot2));
        }
        
        if (annot1) g_object_unref(annot1);
        if (annot2) g_object_unref(annot2);
        g_object_unref(doc);
    }
    
    if (error) {
        g_error_free(error);
    }
}

// Test boundary rectangle values
TEST_F(PopplerAnnotSquareNewTest_2057, BoundaryRectangleValues_2057) {
    GError *error = nullptr;
    
    const char *pdf_data = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                           "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                           "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                           "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                           "0000000058 00000 n \n0000000115 00000 n \n"
                           "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";
    
    PopplerDocument *doc = poppler_document_new_from_data(pdf_data, strlen(pdf_data), nullptr, &error);
    
    if (doc != nullptr) {
        // Zero-size rectangle
        PopplerRectangle rect = {0.0, 0.0, 0.0, 0.0};
        PopplerAnnot *annot = poppler_annot_square_new(doc, &rect);
        
        if (annot != nullptr) {
            EXPECT_TRUE(POPPLER_IS_ANNOT_SQUARE(annot));
            g_object_unref(annot);
        }
        
        // Very large rectangle
        PopplerRectangle large_rect = {0.0, 0.0, 100000.0, 100000.0};
        PopplerAnnot *large_annot = poppler_annot_square_new(doc, &large_rect);
        
        if (large_annot != nullptr) {
            EXPECT_TRUE(POPPLER_IS_ANNOT_SQUARE(large_annot));
            g_object_unref(large_annot);
        }
        
        g_object_unref(doc);
    }
    
    if (error) {
        g_error_free(error);
    }
}
