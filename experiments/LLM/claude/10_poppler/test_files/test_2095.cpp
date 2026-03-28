#include <glib.h>
#include <glib-object.h>
#include "poppler.h"
#include "poppler-private.h"
#include "poppler-annot.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

class PopplerAnnotTextMarkupTest_2095 : public ::testing::Test {
protected:
    PopplerDocument *doc = nullptr;
    PopplerPage *page = nullptr;

    void SetUp() override {
        // Try to load a simple PDF for testing
        GError *error = nullptr;
        // We create a minimal test by trying to find a test PDF or creating annotations programmatically
    }

    void TearDown() override {
        if (page)
            g_object_unref(page);
        if (doc)
            g_object_unref(doc);
    }
};

// Test that passing NULL returns NULL
TEST_F(PopplerAnnotTextMarkupTest_2095, NullAnnotReturnsNull_2095)
{
    // Passing NULL should trigger g_return_val_if_fail and return NULL
    // We suppress the GLib warning for this test
    g_test_expect_message("GLib-GObject", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_ANNOT_TEXT_MARKUP*");
    GArray *result = poppler_annot_text_markup_get_quadrilaterals(NULL);
    g_test_assert_expected_messages();
    EXPECT_EQ(result, nullptr);
}

// Test that passing an invalid (non-PopplerAnnotTextMarkup) GObject returns NULL
TEST_F(PopplerAnnotTextMarkupTest_2095, InvalidAnnotTypeReturnsNull_2095)
{
    // Create some other GObject that is NOT a PopplerAnnotTextMarkup
    // Using a generic GObject as a wrong type
    GObject *wrong_type = (GObject *)g_object_new(G_TYPE_OBJECT, NULL);
    
    g_test_expect_message("GLib-GObject", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_ANNOT_TEXT_MARKUP*");
    GArray *result = poppler_annot_text_markup_get_quadrilaterals((PopplerAnnotTextMarkup *)wrong_type);
    g_test_assert_expected_messages();
    EXPECT_EQ(result, nullptr);
    
    g_object_unref(wrong_type);
}

// Test with a real document that has a text markup annotation
TEST_F(PopplerAnnotTextMarkupTest_2095, GetQuadrilateralsFromRealAnnotation_2095)
{
    GError *error = nullptr;
    
    // Try to load a test PDF file - adjust path as needed
    const char *test_pdf_path = "./test_annot.pdf";
    gchar *uri = g_filename_to_uri(test_pdf_path, NULL, &error);
    
    if (uri == nullptr || error != nullptr) {
        // If no test file available, skip this test
        if (error) g_error_free(error);
        GTEST_SKIP() << "Test PDF not available";
        return;
    }
    
    doc = poppler_document_new_from_file(uri, NULL, &error);
    g_free(uri);
    
    if (doc == nullptr) {
        if (error) g_error_free(error);
        GTEST_SKIP() << "Could not load test PDF";
        return;
    }
    
    page = poppler_document_get_page(doc, 0);
    if (page == nullptr) {
        GTEST_SKIP() << "Could not get page from test PDF";
        return;
    }
    
    GList *annot_mapping = poppler_page_get_annot_mapping(page);
    
    PopplerAnnotTextMarkup *text_markup = nullptr;
    for (GList *l = annot_mapping; l != nullptr; l = l->next) {
        PopplerAnnotMapping *mapping = (PopplerAnnotMapping *)l->data;
        PopplerAnnot *annot = mapping->annot;
        PopplerAnnotType type = poppler_annot_get_annot_type(annot);
        if (type == POPPLER_ANNOT_HIGHLIGHT || type == POPPLER_ANNOT_UNDERLINE ||
            type == POPPLER_ANNOT_SQUIGGLY || type == POPPLER_ANNOT_STRIKE_OUT) {
            text_markup = POPPLER_ANNOT_TEXT_MARKUP(annot);
            break;
        }
    }
    
    if (text_markup != nullptr) {
        GArray *quads = poppler_annot_text_markup_get_quadrilaterals(text_markup);
        EXPECT_NE(quads, nullptr);
        if (quads) {
            EXPECT_GT(quads->len, 0u);
            g_array_free(quads, TRUE);
        }
    } else {
        GTEST_SKIP() << "No text markup annotation found in test PDF";
    }
    
    poppler_page_free_annot_mapping(annot_mapping);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
