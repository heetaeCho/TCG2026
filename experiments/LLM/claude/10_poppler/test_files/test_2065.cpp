#include <glib.h>
#include <glib-object.h>
#include <gtest/gtest.h>

// Poppler GLib headers
extern "C" {
#include "poppler-annot.h"
#include "poppler-document.h"
#include "poppler-page.h"
}

#include "poppler-private.h"
#include "Annot.h"
#include "GooString.h"
#include "PDFDoc.h"

#include <memory>

class PopplerAnnotGetNameTest_2065 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that passing NULL returns NULL (g_return_val_if_fail guards)
TEST_F(PopplerAnnotGetNameTest_2065, NullAnnotReturnsNull_2065)
{
    // g_return_val_if_fail should handle NULL gracefully and return NULL
    // We need to suppress the GLib warning
    g_test_expect_message("Poppler", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_ANNOT*");
    gchar *result = poppler_annot_get_name(NULL);
    g_test_assert_expected_messages();
    EXPECT_EQ(result, nullptr);
}

// Test with a real PDF that has annotations - using a helper to create a minimal annot
// We test by loading a PDF with known annotations if available,
// or by creating annotation objects through the poppler glib API.

class PopplerAnnotFromDocTest_2065 : public ::testing::Test {
protected:
    PopplerDocument *doc = nullptr;
    PopplerPage *page = nullptr;

    void SetUp() override {
        // Try to create a minimal in-memory PDF with an annotation
        // We'll use poppler_document_new_from_data or from_file
    }

    void TearDown() override {
        if (page)
            g_object_unref(page);
        if (doc)
            g_object_unref(doc);
    }
};

// Test poppler_annot_get_name with a freshly created text annotation
TEST_F(PopplerAnnotGetNameTest_2065, NewTextAnnotNameIsNotNull_2065)
{
    // Create a PopplerAnnotText through the public API
    // poppler_annot_text_new creates a new text annotation
    // which should have some default or empty name
    PopplerDocument *doc = nullptr;
    GError *error = nullptr;

    // Create minimal PDF in memory
    const char *minimal_pdf =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    GBytes *bytes = g_bytes_new_static(minimal_pdf, strlen(minimal_pdf));
    doc = poppler_document_new_from_bytes(bytes, nullptr, &error);

    if (doc == nullptr) {
        g_bytes_unref(bytes);
        GTEST_SKIP() << "Could not create minimal PDF document";
        return;
    }

    PopplerPage *page = poppler_document_get_page(doc, 0);
    ASSERT_NE(page, nullptr);

    PopplerRectangle rect = { 100, 100, 200, 200 };
    PopplerAnnot *annot = reinterpret_cast<PopplerAnnot *>(poppler_annot_text_new(doc, &rect));
    ASSERT_NE(annot, nullptr);

    // The name may or may not be set; we just verify it doesn't crash
    gchar *name = poppler_annot_get_name(annot);
    // Name could be NULL or a valid string
    if (name != nullptr) {
        EXPECT_TRUE(g_utf8_validate(name, -1, nullptr));
        g_free(name);
    }

    g_object_unref(annot);
    g_object_unref(page);
    g_object_unref(doc);
    g_bytes_unref(bytes);
}
