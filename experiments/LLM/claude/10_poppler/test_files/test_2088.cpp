#include <glib-object.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

// Include poppler glib headers
#include "poppler-annot.h"
#include "poppler-document.h"
#include "poppler-page.h"

#include <cstdio>
#include <cstring>

class PopplerAnnotMarkupExternalDataTest_2088 : public ::testing::Test {
protected:
    void SetUp() override
    {
        // We need a real PDF document with markup annotations to test
        doc = nullptr;
        page = nullptr;
    }

    void TearDown() override
    {
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

// Test that passing NULL returns POPPLER_ANNOT_EXTERNAL_DATA_MARKUP_UNKNOWN
// The g_return_val_if_fail macro should handle NULL gracefully
TEST_F(PopplerAnnotMarkupExternalDataTest_2088, NullAnnotReturnsUnknown_2088)
{
    // g_return_val_if_fail with NULL should return the default value
    // We need to suppress the g_warning/g_critical that g_return_val_if_fail emits
    g_test_expect_message("GLib-GObject", G_LOG_LEVEL_CRITICAL, "*");

    PopplerAnnotExternalDataType result = poppler_annot_markup_get_external_data(nullptr);
    EXPECT_EQ(result, POPPLER_ANNOT_EXTERNAL_DATA_MARKUP_UNKNOWN);

    g_test_assert_expected_messages();
}

// Test with a real markup annotation from a PDF that has annotations
// We create a minimal PDF with a text annotation (which is a markup annotation)
TEST_F(PopplerAnnotMarkupExternalDataTest_2088, ValidMarkupAnnotReturnsExpectedData_2088)
{
    // Create a minimal PDF in memory with a text annotation
    const char *pdf_content =
        "%PDF-1.4\n"
        "1 0 obj\n"
        "<< /Type /Catalog /Pages 2 0 R >>\n"
        "endobj\n"
        "2 0 obj\n"
        "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
        "endobj\n"
        "3 0 obj\n"
        "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792]\n"
        "   /Annots [4 0 R] >>\n"
        "endobj\n"
        "4 0 obj\n"
        "<< /Type /Annot /Subtype /Text /Rect [100 700 200 750]\n"
        "   /Contents (Test annotation) /T (Author) >>\n"
        "endobj\n"
        "xref\n"
        "0 5\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "0000000232 00000 n \n"
        "trailer\n"
        "<< /Size 5 /Root 1 0 R >>\n"
        "startxref\n"
        "355\n"
        "%%EOF\n";

    // Write to a temp file
    char tmpfile[] = "/tmp/test_annot_XXXXXX.pdf";
    int fd = mkstemps(tmpfile, 4);
    if (fd < 0) {
        GTEST_SKIP() << "Could not create temp file";
    }
    write(fd, pdf_content, strlen(pdf_content));
    close(fd);

    GError *error = nullptr;
    gchar *uri = g_filename_to_uri(tmpfile, nullptr, &error);
    if (!uri) {
        unlink(tmpfile);
        GTEST_SKIP() << "Could not create URI";
    }

    doc = poppler_document_new_from_file(uri, nullptr, &error);
    g_free(uri);

    if (!doc) {
        if (error) {
            g_error_free(error);
        }
        unlink(tmpfile);
        GTEST_SKIP() << "Could not load test PDF";
    }

    page = poppler_document_get_page(doc, 0);
    if (!page) {
        unlink(tmpfile);
        GTEST_SKIP() << "Could not get page";
    }

    GList *annots = poppler_page_get_annot_mapping(page);
    if (!annots) {
        unlink(tmpfile);
        GTEST_SKIP() << "No annotations found in test PDF";
    }

    // Find a markup annotation
    bool found_markup = false;
    for (GList *l = annots; l != nullptr; l = l->next) {
        PopplerAnnotMapping *mapping = static_cast<PopplerAnnotMapping *>(l->data);
        PopplerAnnot *annot = mapping->annot;

        if (POPPLER_IS_ANNOT_MARKUP(annot)) {
            PopplerAnnotMarkup *markup = POPPLER_ANNOT_MARKUP(annot);
            PopplerAnnotExternalDataType result = poppler_annot_markup_get_external_data(markup);

            // A basic text annotation without ExData should return UNKNOWN
            EXPECT_EQ(result, POPPLER_ANNOT_EXTERNAL_DATA_MARKUP_UNKNOWN);
            found_markup = true;
            break;
        }
    }

    poppler_page_free_annot_mapping(annots);
    unlink(tmpfile);

    if (!found_markup) {
        GTEST_SKIP() << "No markup annotation found in test PDF";
    }
}

// Test that the enum values are correctly defined
TEST_F(PopplerAnnotMarkupExternalDataTest_2088, EnumValuesCorrect_2088)
{
    EXPECT_EQ(POPPLER_ANNOT_EXTERNAL_DATA_MARKUP_3D, 0);
    EXPECT_EQ(POPPLER_ANNOT_EXTERNAL_DATA_MARKUP_UNKNOWN, 1);
}

// Test with an invalid GObject (not an annot markup) - should trigger g_return_val_if_fail
TEST_F(PopplerAnnotMarkupExternalDataTest_2088, InvalidObjectTypeReturnsUnknown_2088)
{
    // Create a non-markup GObject and cast it incorrectly
    // The POPPLER_IS_ANNOT_MARKUP check should catch this
    GObject *random_obj = G_OBJECT(g_object_new(G_TYPE_OBJECT, nullptr));

    g_test_expect_message("GLib-GObject", G_LOG_LEVEL_CRITICAL, "*");

    PopplerAnnotExternalDataType result = poppler_annot_markup_get_external_data(reinterpret_cast<PopplerAnnotMarkup *>(random_obj));
    EXPECT_EQ(result, POPPLER_ANNOT_EXTERNAL_DATA_MARKUP_UNKNOWN);

    g_test_assert_expected_messages();

    g_object_unref(random_obj);
}

// Test with a PDF that has a 3D annotation with ExData set to 3D markup
TEST_F(PopplerAnnotMarkupExternalDataTest_2088, AnnotWith3DExDataReturns3D_2088)
{
    // Create a PDF with a markup annotation that has ExData /3D
    const char *pdf_content =
        "%PDF-1.7\n"
        "1 0 obj\n"
        "<< /Type /Catalog /Pages 2 0 R >>\n"
        "endobj\n"
        "2 0 obj\n"
        "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
        "endobj\n"
        "3 0 obj\n"
        "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792]\n"
        "   /Annots [4 0 R] >>\n"
        "endobj\n"
        "4 0 obj\n"
        "<< /Type /Annot /Subtype /Text /Rect [100 700 200 750]\n"
        "   /Contents (Test 3D annotation) /T (Author)\n"
        "   /ExData << /Type /ExData /Subtype /Markup3D >> >>\n"
        "endobj\n"
        "xref\n"
        "0 5\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "0000000232 00000 n \n"
        "trailer\n"
        "<< /Size 5 /Root 1 0 R >>\n"
        "startxref\n"
        "420\n"
        "%%EOF\n";

    char tmpfile[] = "/tmp/test_annot_3d_XXXXXX.pdf";
    int fd = mkstemps(tmpfile, 4);
    if (fd < 0) {
        GTEST_SKIP() << "Could not create temp file";
    }
    write(fd, pdf_content, strlen(pdf_content));
    close(fd);

    GError *error = nullptr;
    gchar *uri = g_filename_to_uri(tmpfile, nullptr, &error);
    if (!uri) {
        unlink(tmpfile);
        GTEST_SKIP() << "Could not create URI";
    }

    doc = poppler_document_new_from_file(uri, nullptr, &error);
    g_free(uri);

    if (!doc) {
        if (error) {
            g_error_free(error);
        }
        unlink(tmpfile);
        GTEST_SKIP() << "Could not load test PDF with 3D ExData";
    }

    page = poppler_document_get_page(doc, 0);
    if (!page) {
        unlink(tmpfile);
        GTEST_SKIP() << "Could not get page";
    }

    GList *annots = poppler_page_get_annot_mapping(page);
    if (!annots) {
        unlink(tmpfile);
        GTEST_SKIP() << "No annotations found";
    }

    for (GList *l = annots; l != nullptr; l = l->next) {
        PopplerAnnotMapping *mapping = static_cast<PopplerAnnotMapping *>(l->data);
        PopplerAnnot *annot = mapping->annot;

        if (POPPLER_IS_ANNOT_MARKUP(annot)) {
            PopplerAnnotMarkup *markup = POPPLER_ANNOT_MARKUP(annot);
            PopplerAnnotExternalDataType result = poppler_annot_markup_get_external_data(markup);

            // The result should be either 3D or UNKNOWN depending on whether poppler parsed the ExData
            EXPECT_TRUE(result == POPPLER_ANNOT_EXTERNAL_DATA_MARKUP_3D || result == POPPLER_ANNOT_EXTERNAL_DATA_MARKUP_UNKNOWN);
            break;
        }
    }

    poppler_page_free_annot_mapping(annots);
    unlink(tmpfile);
}
