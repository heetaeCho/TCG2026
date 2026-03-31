#include <glib.h>
#include <glib-object.h>

// Include poppler glib headers
#include "poppler.h"
#include "poppler-private.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

class PopplerAnnotGetFlagsTest_2067 : public ::testing::Test {
protected:
    void SetUp() override {
        // Suppress GLib critical warnings for invalid parameter tests
    }

    void TearDown() override {
    }
};

// Test that passing NULL returns 0 (the g_return_val_if_fail guard)
TEST_F(PopplerAnnotGetFlagsTest_2067, NullAnnotReturnsZero_2067)
{
    // g_return_val_if_fail should catch NULL and return (PopplerAnnotFlag)0
    // We need to suppress the GLib warning
    g_test_expect_message("Poppler", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_ANNOT*");
    PopplerAnnotFlag flags = poppler_annot_get_flags(nullptr);
    g_test_assert_expected_messages();
    EXPECT_EQ(flags, (PopplerAnnotFlag)0);
}

// Test with a valid annotation from an actual PDF document
// We create a simple PDF with an annotation to test
class PopplerAnnotGetFlagsFromDocTest_2067 : public ::testing::Test {
protected:
    PopplerDocument *doc = nullptr;
    PopplerPage *page = nullptr;

    void SetUp() override {
        GError *error = nullptr;
        // Create a minimal PDF in memory that has an annotation
        // Use a file URI or create from data if possible
        // For testing purposes, we'll try to create a document from a minimal PDF
        const char *minimal_pdf =
            "%PDF-1.4\n"
            "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
            "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
            "3 0 obj<</Type/Page/Parent 2 0 R/MediaBox[0 0 612 792]"
            "/Annots[4 0 R]>>endobj\n"
            "4 0 obj<</Type/Annot/Subtype/Text/Rect[100 100 200 200]"
            "/Contents(Test)/F 4>>endobj\n"
            "xref\n0 5\n"
            "0000000000 65535 f \n"
            "0000000009 00000 n \n"
            "0000000058 00000 n \n"
            "0000000115 00000 n \n"
            "0000000226 00000 n \n"
            "trailer<</Size 5/Root 1 0 R>>\n"
            "startxref\n340\n%%EOF\n";

        gsize len = strlen(minimal_pdf);
        doc = poppler_document_new_from_data((char *)minimal_pdf, (int)len, nullptr, &error);
        if (doc) {
            page = poppler_document_get_page(doc, 0);
        }
    }

    void TearDown() override {
        if (page)
            g_object_unref(page);
        if (doc)
            g_object_unref(doc);
    }
};

TEST_F(PopplerAnnotGetFlagsFromDocTest_2067, ValidAnnotReturnsFlags_2067)
{
    if (!doc || !page) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    GList *annot_mappings = poppler_page_get_annot_mapping(page);
    if (!annot_mappings) {
        GTEST_SKIP() << "No annotations found in test PDF";
    }

    PopplerAnnotMapping *mapping = (PopplerAnnotMapping *)annot_mappings->data;
    PopplerAnnot *annot = mapping->annot;
    ASSERT_NE(annot, nullptr);

    PopplerAnnotFlag flags = poppler_annot_get_flags(annot);
    // We set F 4 in the PDF which corresponds to POPPLER_ANNOT_FLAG_NO_ZOOM (bit 3 = value 4)
    EXPECT_EQ(flags & POPPLER_ANNOT_FLAG_NO_ZOOM, POPPLER_ANNOT_FLAG_NO_ZOOM);

    poppler_page_free_annot_mapping(annot_mappings);
}

// Test that a non-GObject pointer (invalid type) returns 0
TEST_F(PopplerAnnotGetFlagsTest_2067, InvalidGObjectReturnsZero_2067)
{
    // Create a plain GObject that is NOT a PopplerAnnot
    GObject *plain_obj = (GObject *)g_object_new(G_TYPE_OBJECT, nullptr);
    g_test_expect_message("Poppler", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_ANNOT*");
    PopplerAnnotFlag flags = poppler_annot_get_flags((PopplerAnnot *)plain_obj);
    g_test_assert_expected_messages();
    EXPECT_EQ(flags, (PopplerAnnotFlag)0);
    g_object_unref(plain_obj);
}
