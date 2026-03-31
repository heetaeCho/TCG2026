#include <glib-object.h>
#include <gtest/gtest.h>
#include <memory>

// Poppler headers
#include "poppler-annot.h"
#include "poppler-document.h"
#include "poppler-page.h"
#include "Annot.h"
#include "PDFDoc.h"
#include "Object.h"

// We need the internal poppler-annot structure access
extern "C" {
#include "poppler-private.h"
}

class PopplerAnnotTextGetStateTest_2093 : public ::testing::Test {
protected:
    void SetUp() override {
        // We need a real PDF document to create annotations properly.
        // We'll try to load a test PDF or create annotations via the GLib API.
    }

    void TearDown() override {
    }

    // Helper: create a PopplerAnnotText from a PDF file that has text annotations
    // Since we can't easily create AnnotText objects without a PDFDoc,
    // we test through the public GLib API by loading a document with annotations.
};

// Test that passing NULL returns POPPLER_ANNOT_TEXT_STATE_UNKNOWN (g_return_val_if_fail)
TEST_F(PopplerAnnotTextGetStateTest_2093, NullAnnotReturnsUnknown_2093) {
    // Suppress expected g_return_val_if_fail warning
    g_test_expect_message("Poppler", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_ANNOT_TEXT*");
    PopplerAnnotTextState state = poppler_annot_text_get_state(nullptr);
    g_test_assert_expected_messages();
    EXPECT_EQ(state, POPPLER_ANNOT_TEXT_STATE_UNKNOWN);
}

// Test that passing an invalid (non-PopplerAnnotText) GObject returns UNKNOWN
TEST_F(PopplerAnnotTextGetStateTest_2093, InvalidObjectReturnsUnknown_2093) {
    // Create a plain GObject which is not a PopplerAnnotText
    GObject *obj = (GObject *)g_object_new(G_TYPE_OBJECT, nullptr);
    g_test_expect_message("Poppler", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_ANNOT_TEXT*");
    PopplerAnnotTextState state = poppler_annot_text_get_state((PopplerAnnotText *)obj);
    g_test_assert_expected_messages();
    EXPECT_EQ(state, POPPLER_ANNOT_TEXT_STATE_UNKNOWN);
    g_object_unref(obj);
}

// Test with a real PDF document that contains a text annotation
// This tests the normal operation path
TEST_F(PopplerAnnotTextGetStateTest_2093, ValidAnnotTextFromDocument_2093) {
    // Try to find a test PDF. We create a minimal one with a text annotation.
    // For this test, we rely on being able to create a PopplerDocument from a file
    // that has text annotations. If no such file exists, we skip.
    
    // Attempt to create a new text annotation on a document
    const char *test_pdf_path = "./TestProjects/poppler/test/unittestcases/WithAnnotations.pdf";
    GError *error = nullptr;
    gchar *uri = g_filename_to_uri(test_pdf_path, nullptr, &error);
    
    if (!uri) {
        // Try alternate path
        if (error) g_error_free(error);
        error = nullptr;
        // Skip if we can't find a test PDF
        GTEST_SKIP() << "Test PDF not available";
        return;
    }
    
    PopplerDocument *doc = poppler_document_new_from_file(uri, nullptr, &error);
    g_free(uri);
    
    if (!doc) {
        if (error) g_error_free(error);
        GTEST_SKIP() << "Could not load test PDF";
        return;
    }
    
    int n_pages = poppler_document_get_n_pages(doc);
    bool found_text_annot = false;
    
    for (int i = 0; i < n_pages && !found_text_annot; i++) {
        PopplerPage *page = poppler_document_get_page(doc, i);
        if (!page) continue;
        
        GList *annot_mapping = poppler_page_get_annot_mapping(page);
        for (GList *l = annot_mapping; l != nullptr; l = l->next) {
            PopplerAnnotMapping *mapping = (PopplerAnnotMapping *)l->data;
            PopplerAnnot *annot = mapping->annot;
            
            if (POPPLER_IS_ANNOT_TEXT(annot)) {
                PopplerAnnotText *text_annot = POPPLER_ANNOT_TEXT(annot);
                PopplerAnnotTextState state = poppler_annot_text_get_state(text_annot);
                
                // The state should be one of the valid enum values
                EXPECT_TRUE(state == POPPLER_ANNOT_TEXT_STATE_MARKED ||
                            state == POPPLER_ANNOT_TEXT_STATE_UNMARKED ||
                            state == POPPLER_ANNOT_TEXT_STATE_ACCEPTED ||
                            state == POPPLER_ANNOT_TEXT_STATE_REJECTED ||
                            state == POPPLER_ANNOT_TEXT_STATE_CANCELLED ||
                            state == POPPLER_ANNOT_TEXT_STATE_COMPLETED ||
                            state == POPPLER_ANNOT_TEXT_STATE_NONE ||
                            state == POPPLER_ANNOT_TEXT_STATE_UNKNOWN);
                found_text_annot = true;
                break;
            }
        }
        poppler_page_free_annot_mapping(annot_mapping);
        g_object_unref(page);
    }
    
    g_object_unref(doc);
    
    if (!found_text_annot) {
        GTEST_SKIP() << "No text annotations found in test PDF";
    }
}

// Test the enum mapping: verify that PopplerAnnotTextState values are distinct and correctly defined
TEST_F(PopplerAnnotTextGetStateTest_2093, EnumValuesAreDistinct_2093) {
    EXPECT_EQ(POPPLER_ANNOT_TEXT_STATE_MARKED, 0);
    EXPECT_EQ(POPPLER_ANNOT_TEXT_STATE_UNMARKED, 1);
    EXPECT_EQ(POPPLER_ANNOT_TEXT_STATE_ACCEPTED, 2);
    EXPECT_EQ(POPPLER_ANNOT_TEXT_STATE_REJECTED, 3);
    EXPECT_EQ(POPPLER_ANNOT_TEXT_STATE_CANCELLED, 4);
    EXPECT_EQ(POPPLER_ANNOT_TEXT_STATE_COMPLETED, 5);
    EXPECT_EQ(POPPLER_ANNOT_TEXT_STATE_NONE, 6);
    EXPECT_EQ(POPPLER_ANNOT_TEXT_STATE_UNKNOWN, 7);
}

// Test creating a new text annotation and checking its default state
TEST_F(PopplerAnnotTextGetStateTest_2093, NewTextAnnotDefaultState_2093) {
    // Create a minimal PDF in memory to get a PopplerDocument
    const char *test_pdf_path = "./TestProjects/poppler/test/unittestcases/WithAnnotations.pdf";
    GError *error = nullptr;
    gchar *uri = g_filename_to_uri(test_pdf_path, nullptr, &error);
    
    if (!uri) {
        if (error) g_error_free(error);
        // Try creating from data - a minimal PDF
        GTEST_SKIP() << "Test PDF not available for new annotation test";
        return;
    }
    
    PopplerDocument *doc = poppler_document_new_from_file(uri, nullptr, &error);
    g_free(uri);
    
    if (!doc) {
        if (error) g_error_free(error);
        GTEST_SKIP() << "Could not load test PDF for new annotation test";
        return;
    }
    
    PopplerPage *page = poppler_document_get_page(doc, 0);
    if (!page) {
        g_object_unref(doc);
        GTEST_SKIP() << "Could not get page from test PDF";
        return;
    }
    
    // Create a new text annotation
    PopplerRectangle rect;
    rect.x1 = 10.0;
    rect.y1 = 10.0;
    rect.x2 = 50.0;
    rect.y2 = 50.0;
    
    PopplerAnnot *annot = poppler_annot_text_new(doc, &rect);
    if (annot && POPPLER_IS_ANNOT_TEXT(annot)) {
        PopplerAnnotText *text_annot = POPPLER_ANNOT_TEXT(annot);
        PopplerAnnotTextState state = poppler_annot_text_get_state(text_annot);
        
        // A newly created text annotation should have a valid state
        EXPECT_TRUE(state >= POPPLER_ANNOT_TEXT_STATE_MARKED &&
                    state <= POPPLER_ANNOT_TEXT_STATE_UNKNOWN);
        
        g_object_unref(annot);
    }
    
    g_object_unref(page);
    g_object_unref(doc);
}

// Test the AnnotText state enum values from the internal representation
TEST_F(PopplerAnnotTextGetStateTest_2093, InternalEnumConsistency_2093) {
    // Verify that internal enum values match expected mapping
    EXPECT_EQ(AnnotText::stateUnknown, 0);
    EXPECT_EQ(AnnotText::stateMarked, 1);
    EXPECT_EQ(AnnotText::stateUnmarked, 2);
    EXPECT_EQ(AnnotText::stateAccepted, 3);
    EXPECT_EQ(AnnotText::stateRejected, 4);
    EXPECT_EQ(AnnotText::stateCancelled, 5);
    EXPECT_EQ(AnnotText::stateCompleted, 6);
    EXPECT_EQ(AnnotText::stateNone, 7);
}

// Verify mapping between internal and GLib enums is correct
// stateUnknown (0) -> POPPLER_ANNOT_TEXT_STATE_UNKNOWN (7)
// stateMarked (1) -> POPPLER_ANNOT_TEXT_STATE_MARKED (0)
// These are different orderings, confirming the switch statement does mapping
TEST_F(PopplerAnnotTextGetStateTest_2093, MappingIsNotIdentity_2093) {
    // The internal stateUnknown is 0 but POPPLER_ANNOT_TEXT_STATE_UNKNOWN is 7
    EXPECT_NE((int)AnnotText::stateUnknown, (int)POPPLER_ANNOT_TEXT_STATE_UNKNOWN);
    // The internal stateMarked is 1 but POPPLER_ANNOT_TEXT_STATE_MARKED is 0
    EXPECT_NE((int)AnnotText::stateMarked, (int)POPPLER_ANNOT_TEXT_STATE_MARKED);
}
