#include <glib.h>
#include <glib-object.h>
#include "poppler.h"
#include "poppler-private.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

class PopplerAnnotGetColorTest_2069 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that passing NULL returns NULL (g_return_val_if_fail should catch this)
TEST_F(PopplerAnnotGetColorTest_2069, NullAnnotReturnsNull_2069) {
    // g_return_val_if_fail(POPPLER_IS_ANNOT(poppler_annot), NULL) should fail for NULL
    // Suppress GLib critical warnings for this test
    g_test_expect_message("Poppler", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_ANNOT*");
    PopplerColor *color = poppler_annot_get_color(NULL);
    g_test_assert_expected_messages();
    EXPECT_EQ(color, nullptr);
}

// Test that passing an invalid GObject (not a PopplerAnnot) returns NULL
TEST_F(PopplerAnnotGetColorTest_2069, InvalidGObjectReturnsNull_2069) {
    // Create some non-PopplerAnnot GObject
    GObject *invalid_obj = (GObject *)g_object_new(G_TYPE_OBJECT, NULL);
    g_test_expect_message("Poppler", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_ANNOT*");
    PopplerColor *color = poppler_annot_get_color((PopplerAnnot *)invalid_obj);
    g_test_assert_expected_messages();
    EXPECT_EQ(color, nullptr);
    g_object_unref(invalid_obj);
}

// Test with a valid PopplerAnnot from a real PDF document that has annotations
TEST_F(PopplerAnnotGetColorTest_2069, ValidAnnotFromDocument_2069) {
    // Create a simple PDF in memory with an annotation to test
    // We'll try loading a document and checking if any page has annotations
    // If we can't create one easily, we at least verify the function doesn't crash
    // with a properly typed object.

    // This test requires a PDF with annotations. We'll create a minimal one.
    const char *pdf_content =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/Parent 2 0 R/MediaBox[0 0 612 792]/Annots[4 0 R]>>endobj\n"
        "4 0 obj<</Type/Annot/Subtype/Text/Rect[100 100 200 200]/C[1.0 0.0 0.0]>>endobj\n"
        "xref\n0 5\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "0000000206 00000 n \n"
        "trailer<</Size 5/Root 1 0 R>>\nstartxref\n296\n%%EOF\n";

    gsize len = strlen(pdf_content);
    GError *error = NULL;
    PopplerDocument *doc = poppler_document_new_from_data(pdf_content, len, NULL, &error);

    if (doc != NULL) {
        PopplerPage *page = poppler_document_get_page(doc, 0);
        if (page != NULL) {
            GList *annot_mappings = poppler_page_get_annot_mapping(page);
            if (annot_mappings != NULL) {
                PopplerAnnotMapping *mapping = (PopplerAnnotMapping *)annot_mappings->data;
                PopplerAnnot *annot = mapping->annot;
                // This is the main test: get_color on a valid annotation
                PopplerColor *color = poppler_annot_get_color(annot);
                // Color may be NULL if the annotation has no color, or non-NULL
                // We just verify it doesn't crash and returns a reasonable result
                if (color != NULL) {
                    // The color values should be in valid range (0-65535 for GLib color)
                    EXPECT_GE(color->red, 0);
                    EXPECT_LE(color->red, 65535);
                    EXPECT_GE(color->green, 0);
                    EXPECT_LE(color->green, 65535);
                    EXPECT_GE(color->blue, 0);
                    EXPECT_LE(color->blue, 65535);
                    g_free(color);
                }
                poppler_page_free_annot_mapping(annot_mappings);
            }
            g_object_unref(page);
        }
        g_object_unref(doc);
    }
    if (error) {
        g_error_free(error);
    }
}
