#include <glib-object.h>
#include <glib.h>
#include "poppler.h"
#include "poppler-private.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

class PopplerAnnotMarkupHasPopupTest_2077 : public ::testing::Test {
protected:
    void SetUp() override {
        // We need a PDF document with annotations to test
        doc = nullptr;
        page = nullptr;
    }

    void TearDown() override {
        if (page) {
            g_object_unref(page);
        }
        if (doc) {
            g_object_unref(doc);
        }
    }

    PopplerDocument *doc;
    PopplerPage *page;
};

// Test that passing NULL returns FALSE (g_return_val_if_fail check)
TEST_F(PopplerAnnotMarkupHasPopupTest_2077, NullAnnotReturnsFalse_2077)
{
    // g_return_val_if_fail should cause FALSE to be returned for NULL
    // We need to suppress the GLib warning
    g_test_expect_message("GLib-GObject", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_ANNOT_MARKUP*");
    gboolean result = poppler_annot_markup_has_popup(nullptr);
    g_test_assert_expected_messages();
    EXPECT_FALSE(result);
}

// Test with a real PDF that has a markup annotation with a popup
TEST_F(PopplerAnnotMarkupHasPopupTest_2077, AnnotWithPopupReturnsTrue_2077)
{
    // Create a simple PDF in memory that has a text annotation with popup
    // We'll use a file-based approach if available, otherwise skip
    GError *error = nullptr;

    // Try to create a minimal PDF document with annotations programmatically
    // First, create a document from a test file if it exists
    const char *test_pdf_path = g_getenv("TEST_PDF_WITH_POPUP");
    if (test_pdf_path == nullptr) {
        GTEST_SKIP() << "TEST_PDF_WITH_POPUP environment variable not set; skipping test with real popup annotation";
        return;
    }

    gchar *uri = g_filename_to_uri(test_pdf_path, nullptr, &error);
    if (error) {
        g_error_free(error);
        GTEST_SKIP() << "Could not convert path to URI";
        return;
    }

    doc = poppler_document_new_from_file(uri, nullptr, &error);
    g_free(uri);
    if (error || !doc) {
        if (error) g_error_free(error);
        GTEST_SKIP() << "Could not open test PDF";
        return;
    }

    page = poppler_document_get_page(doc, 0);
    if (!page) {
        GTEST_SKIP() << "Could not get page from test PDF";
        return;
    }

    GList *annot_mappings = poppler_page_get_annot_mapping(page);
    gboolean found_markup_with_popup = FALSE;
    for (GList *l = annot_mappings; l != nullptr; l = l->next) {
        PopplerAnnotMapping *mapping = (PopplerAnnotMapping *)l->data;
        PopplerAnnot *annot = mapping->annot;
        if (POPPLER_IS_ANNOT_MARKUP(annot)) {
            PopplerAnnotMarkup *markup = POPPLER_ANNOT_MARKUP(annot);
            if (poppler_annot_markup_has_popup(markup)) {
                found_markup_with_popup = TRUE;
                break;
            }
        }
    }
    poppler_page_free_annot_mapping(annot_mappings);

    EXPECT_TRUE(found_markup_with_popup);
}

// Test with a real PDF that has a markup annotation without a popup
TEST_F(PopplerAnnotMarkupHasPopupTest_2077, AnnotWithoutPopupReturnsFalse_2077)
{
    GError *error = nullptr;

    const char *test_pdf_path = g_getenv("TEST_PDF_WITHOUT_POPUP");
    if (test_pdf_path == nullptr) {
        GTEST_SKIP() << "TEST_PDF_WITHOUT_POPUP environment variable not set; skipping test without popup annotation";
        return;
    }

    gchar *uri = g_filename_to_uri(test_pdf_path, nullptr, &error);
    if (error) {
        g_error_free(error);
        GTEST_SKIP() << "Could not convert path to URI";
        return;
    }

    doc = poppler_document_new_from_file(uri, nullptr, &error);
    g_free(uri);
    if (error || !doc) {
        if (error) g_error_free(error);
        GTEST_SKIP() << "Could not open test PDF";
        return;
    }

    page = poppler_document_get_page(doc, 0);
    if (!page) {
        GTEST_SKIP() << "Could not get page from test PDF";
        return;
    }

    GList *annot_mappings = poppler_page_get_annot_mapping(page);
    gboolean found_markup_without_popup = FALSE;
    for (GList *l = annot_mappings; l != nullptr; l = l->next) {
        PopplerAnnotMapping *mapping = (PopplerAnnotMapping *)l->data;
        PopplerAnnot *annot = mapping->annot;
        if (POPPLER_IS_ANNOT_MARKUP(annot)) {
            PopplerAnnotMarkup *markup = POPPLER_ANNOT_MARKUP(annot);
            if (!poppler_annot_markup_has_popup(markup)) {
                found_markup_without_popup = TRUE;
                break;
            }
        }
    }
    poppler_page_free_annot_mapping(annot_mappings);

    EXPECT_TRUE(found_markup_without_popup);
}

// Test that an invalid GObject type returns FALSE
TEST_F(PopplerAnnotMarkupHasPopupTest_2077, InvalidObjectTypeReturnsFalse_2077)
{
    // Create a random GObject that is NOT a PopplerAnnotMarkup
    GObject *random_obj = (GObject *)g_object_new(G_TYPE_OBJECT, nullptr);

    g_test_expect_message("GLib-GObject", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_ANNOT_MARKUP*");
    gboolean result = poppler_annot_markup_has_popup((PopplerAnnotMarkup *)random_obj);
    g_test_assert_expected_messages();

    EXPECT_FALSE(result);

    g_object_unref(random_obj);
}

// Test return type is gboolean (TRUE or FALSE)
TEST_F(PopplerAnnotMarkupHasPopupTest_2077, ReturnTypeIsGboolean_2077)
{
    // Verify that the function returns a proper gboolean for null input
    g_test_expect_message("GLib-GObject", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_ANNOT_MARKUP*");
    gboolean result = poppler_annot_markup_has_popup(nullptr);
    g_test_assert_expected_messages();

    // Result should be exactly FALSE (0), not some other non-TRUE value
    EXPECT_EQ(result, FALSE);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
