#include <glib-object.h>
#include <glib.h>
#include <memory>
#include <cmath>

// Include poppler glib headers
#include "poppler.h"
#include "poppler-private.h"
#include "poppler-annot.h"

// Include poppler core headers for creating test objects
#include "Annot.h"
#include "PDFDoc.h"
#include "GlobalParams.h"
#include "GooString.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

class PopplerAnnotMarkupOpacityTest_2083 : public ::testing::Test {
protected:
    void SetUp() override {
        // Initialize globalParams if needed
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void TearDown() override {
    }

    // Helper to create a PopplerDocument from a minimal PDF with an annotation
    PopplerDocument *createDocWithAnnot(PopplerPage **outPage) {
        // We need a real PDF to work with annotations through the glib API
        // Try to create a minimal in-memory PDF
        return nullptr;
    }
};

// Test that passing NULL returns 0 (the g_return_val_if_fail guard)
TEST_F(PopplerAnnotMarkupOpacityTest_2083, ReturnsZeroForNull_2083) {
    // The function has g_return_val_if_fail which should return 0 for NULL
    // We need to suppress the g_return_val_if_fail warning
    g_test_expect_message("Poppler", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_ANNOT_MARKUP*");
    gdouble result = poppler_annot_markup_get_opacity(NULL);
    g_test_assert_expected_messages();
    EXPECT_DOUBLE_EQ(result, 0.0);
}

// Test with a real PDF file that has markup annotations
// This test creates a PDF document from a file if available
class PopplerAnnotMarkupFromFileTest_2083 : public ::testing::Test {
protected:
    PopplerDocument *doc = nullptr;
    
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void TearDown() override {
        if (doc) {
            g_object_unref(doc);
        }
    }

    // Create a simple in-memory PDF with a text annotation
    PopplerDocument* createMinimalPDFWithAnnotation() {
        // Minimal PDF with a text annotation (markup type)
        const char *pdf_content =
            "%PDF-1.4\n"
            "1 0 obj\n"
            "<< /Type /Catalog /Pages 2 0 R >>\n"
            "endobj\n"
            "2 0 obj\n"
            "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
            "endobj\n"
            "3 0 obj\n"
            "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] "
            "/Annots [4 0 R] >>\n"
            "endobj\n"
            "4 0 obj\n"
            "<< /Type /Annot /Subtype /Text /Rect [100 700 200 750] "
            "/Contents (Test) /CA 0.75 >>\n"
            "endobj\n"
            "xref\n"
            "0 5\n"
            "0000000000 65535 f \n"
            "0000000009 00000 n \n"
            "0000000058 00000 n \n"
            "0000000115 00000 n \n"
            "0000000228 00000 n \n"
            "trailer\n"
            "<< /Size 5 /Root 1 0 R >>\n"
            "startxref\n"
            "354\n"
            "%%EOF\n";

        gsize len = strlen(pdf_content);
        GError *error = nullptr;

        // Write to a temp file since poppler_document_new_from_data may need proper PDF
        gchar *tmpfile = nullptr;
        gint fd = g_file_open_tmp("test_pdf_XXXXXX.pdf", &tmpfile, &error);
        if (fd < 0) {
            return nullptr;
        }
        
        write(fd, pdf_content, len);
        close(fd);

        gchar *uri = g_filename_to_uri(tmpfile, nullptr, &error);
        if (!uri) {
            g_free(tmpfile);
            return nullptr;
        }

        PopplerDocument *document = poppler_document_new_from_file(uri, nullptr, &error);
        
        g_free(uri);
        g_unlink(tmpfile);
        g_free(tmpfile);

        if (error) {
            g_error_free(error);
            return nullptr;
        }

        return document;
    }
};

// Test opacity retrieval from a PDF annotation with CA=0.75
TEST_F(PopplerAnnotMarkupFromFileTest_2083, GetOpacityFromAnnotation_2083) {
    doc = createMinimalPDFWithAnnotation();
    if (!doc) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PopplerPage *page = poppler_document_get_page(doc, 0);
    ASSERT_NE(page, nullptr);

    GList *annot_mappings = poppler_page_get_annot_mapping(page);
    
    bool found_markup = false;
    for (GList *l = annot_mappings; l != nullptr; l = l->next) {
        PopplerAnnotMapping *mapping = (PopplerAnnotMapping *)l->data;
        PopplerAnnot *annot = mapping->annot;
        
        if (POPPLER_IS_ANNOT_MARKUP(annot)) {
            PopplerAnnotMarkup *markup = POPPLER_ANNOT_MARKUP(annot);
            gdouble opacity = poppler_annot_markup_get_opacity(markup);
            // CA was set to 0.75 in our test PDF
            EXPECT_NEAR(opacity, 0.75, 0.01);
            found_markup = true;
        }
    }

    poppler_page_free_annot_mapping(annot_mappings);
    g_object_unref(page);

    if (!found_markup) {
        GTEST_SKIP() << "No markup annotation found in test PDF";
    }
}

// Test with a PDF that has default opacity (no CA entry, should default to 1.0)
TEST_F(PopplerAnnotMarkupFromFileTest_2083, GetDefaultOpacity_2083) {
    const char *pdf_content =
        "%PDF-1.4\n"
        "1 0 obj\n"
        "<< /Type /Catalog /Pages 2 0 R >>\n"
        "endobj\n"
        "2 0 obj\n"
        "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
        "endobj\n"
        "3 0 obj\n"
        "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] "
        "/Annots [4 0 R] >>\n"
        "endobj\n"
        "4 0 obj\n"
        "<< /Type /Annot /Subtype /Text /Rect [100 700 200 750] "
        "/Contents (Test) >>\n"
        "endobj\n"
        "xref\n"
        "0 5\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "0000000228 00000 n \n"
        "trailer\n"
        "<< /Size 5 /Root 1 0 R >>\n"
        "startxref\n"
        "340\n"
        "%%EOF\n";

    gsize len = strlen(pdf_content);
    GError *error = nullptr;

    gchar *tmpfile = nullptr;
    gint fd = g_file_open_tmp("test_pdf_default_XXXXXX.pdf", &tmpfile, &error);
    if (fd < 0) {
        GTEST_SKIP() << "Could not create temp file";
    }
    
    write(fd, pdf_content, len);
    close(fd);

    gchar *uri = g_filename_to_uri(tmpfile, nullptr, &error);
    if (!uri) {
        g_free(tmpfile);
        GTEST_SKIP() << "Could not create URI";
    }

    doc = poppler_document_new_from_file(uri, nullptr, &error);
    g_free(uri);
    g_unlink(tmpfile);
    g_free(tmpfile);

    if (!doc) {
        if (error) g_error_free(error);
        GTEST_SKIP() << "Could not open test PDF";
    }

    PopplerPage *page = poppler_document_get_page(doc, 0);
    if (!page) {
        GTEST_SKIP() << "Could not get page";
    }

    GList *annot_mappings = poppler_page_get_annot_mapping(page);
    
    bool found_markup = false;
    for (GList *l = annot_mappings; l != nullptr; l = l->next) {
        PopplerAnnotMapping *mapping = (PopplerAnnotMapping *)l->data;
        PopplerAnnot *annot = mapping->annot;
        
        if (POPPLER_IS_ANNOT_MARKUP(annot)) {
            PopplerAnnotMarkup *markup = POPPLER_ANNOT_MARKUP(annot);
            gdouble opacity = poppler_annot_markup_get_opacity(markup);
            // Default opacity should be 1.0 when CA is not specified
            EXPECT_NEAR(opacity, 1.0, 0.01);
            found_markup = true;
        }
    }

    poppler_page_free_annot_mapping(annot_mappings);
    g_object_unref(page);

    if (!found_markup) {
        GTEST_SKIP() << "No markup annotation found in test PDF";
    }
}

// Test that passing a non-markup annot type triggers the type check guard
TEST_F(PopplerAnnotMarkupOpacityTest_2083, ReturnsZeroForInvalidType_2083) {
    // Cast an arbitrary non-NULL invalid pointer - this should fail the IS_ANNOT_MARKUP check
    // We use a GObject that is not a PopplerAnnotMarkup
    GObject *obj = (GObject *)g_object_new(G_TYPE_OBJECT, nullptr);
    
    g_test_expect_message("Poppler", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_ANNOT_MARKUP*");
    gdouble result = poppler_annot_markup_get_opacity((PopplerAnnotMarkup *)obj);
    g_test_assert_expected_messages();
    
    EXPECT_DOUBLE_EQ(result, 0.0);
    
    g_object_unref(obj);
}

// Test with CA=0.0 (fully transparent)
TEST_F(PopplerAnnotMarkupFromFileTest_2083, GetZeroOpacity_2083) {
    const char *pdf_content =
        "%PDF-1.4\n"
        "1 0 obj\n"
        "<< /Type /Catalog /Pages 2 0 R >>\n"
        "endobj\n"
        "2 0 obj\n"
        "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
        "endobj\n"
        "3 0 obj\n"
        "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] "
        "/Annots [4 0 R] >>\n"
        "endobj\n"
        "4 0 obj\n"
        "<< /Type /Annot /Subtype /Text /Rect [100 700 200 750] "
        "/Contents (Test) /CA 0.0 >>\n"
        "endobj\n"
        "xref\n"
        "0 5\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "0000000228 00000 n \n"
        "trailer\n"
        "<< /Size 5 /Root 1 0 R >>\n"
        "startxref\n"
        "351\n"
        "%%EOF\n";

    gsize len = strlen(pdf_content);
    GError *error = nullptr;

    gchar *tmpfile = nullptr;
    gint fd = g_file_open_tmp("test_pdf_zero_XXXXXX.pdf", &tmpfile, &error);
    if (fd < 0) {
        GTEST_SKIP() << "Could not create temp file";
    }
    
    write(fd, pdf_content, len);
    close(fd);

    gchar *uri = g_filename_to_uri(tmpfile, nullptr, &error);
    if (!uri) {
        g_free(tmpfile);
        GTEST_SKIP() << "Could not create URI";
    }

    doc = poppler_document_new_from_file(uri, nullptr, &error);
    g_free(uri);
    g_unlink(tmpfile);
    g_free(tmpfile);

    if (!doc) {
        if (error) g_error_free(error);
        GTEST_SKIP() << "Could not open test PDF";
    }

    PopplerPage *page = poppler_document_get_page(doc, 0);
    if (!page) {
        GTEST_SKIP() << "Could not get page";
    }

    GList *annot_mappings = poppler_page_get_annot_mapping(page);
    
    bool found_markup = false;
    for (GList *l = annot_mappings; l != nullptr; l = l->next) {
        PopplerAnnotMapping *mapping = (PopplerAnnotMapping *)l->data;
        PopplerAnnot *annot = mapping->annot;
        
        if (POPPLER_IS_ANNOT_MARKUP(annot)) {
            PopplerAnnotMarkup *markup = POPPLER_ANNOT_MARKUP(annot);
            gdouble opacity = poppler_annot_markup_get_opacity(markup);
            EXPECT_NEAR(opacity, 0.0, 0.01);
            found_markup = true;
        }
    }

    poppler_page_free_annot_mapping(annot_mappings);
    g_object_unref(page);

    if (!found_markup) {
        GTEST_SKIP() << "No markup annotation found in test PDF";
    }
}

// Test with CA=1.0 (fully opaque)
TEST_F(PopplerAnnotMarkupFromFileTest_2083, GetFullOpacity_2083) {
    const char *pdf_content =
        "%PDF-1.4\n"
        "1 0 obj\n"
        "<< /Type /Catalog /Pages 2 0 R >>\n"
        "endobj\n"
        "2 0 obj\n"
        "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
        "endobj\n"
        "3 0 obj\n"
        "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] "
        "/Annots [4 0 R] >>\n"
        "endobj\n"
        "4 0 obj\n"
        "<< /Type /Annot /Subtype /Text /Rect [100 700 200 750] "
        "/Contents (Test) /CA 1.0 >>\n"
        "endobj\n"
        "xref\n"
        "0 5\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "0000000228 00000 n \n"
        "trailer\n"
        "<< /Size 5 /Root 1 0 R >>\n"
        "startxref\n"
        "351\n"
        "%%EOF\n";

    gsize len = strlen(pdf_content);
    GError *error = nullptr;

    gchar *tmpfile = nullptr;
    gint fd = g_file_open_tmp("test_pdf_full_XXXXXX.pdf", &tmpfile, &error);
    if (fd < 0) {
        GTEST_SKIP() << "Could not create temp file";
    }
    
    write(fd, pdf_content, len);
    close(fd);

    gchar *uri = g_filename_to_uri(tmpfile, nullptr, &error);
    if (!uri) {
        g_free(tmpfile);
        GTEST_SKIP() << "Could not create URI";
    }

    doc = poppler_document_new_from_file(uri, nullptr, &error);
    g_free(uri);
    g_unlink(tmpfile);
    g_free(tmpfile);

    if (!doc) {
        if (error) g_error_free(error);
        GTEST_SKIP() << "Could not open test PDF";
    }

    PopplerPage *page = poppler_document_get_page(doc, 0);
    if (!page) {
        GTEST_SKIP() << "Could not get page";
    }

    GList *annot_mappings = poppler_page_get_annot_mapping(page);
    
    bool found_markup = false;
    for (GList *l = annot_mappings; l != nullptr; l = l->next) {
        PopplerAnnotMapping *mapping = (PopplerAnnotMapping *)l->data;
        PopplerAnnot *annot = mapping->annot;
        
        if (POPPLER_IS_ANNOT_MARKUP(annot)) {
            PopplerAnnotMarkup *markup = POPPLER_ANNOT_MARKUP(annot);
            gdouble opacity = poppler_annot_markup_get_opacity(markup);
            EXPECT_NEAR(opacity, 1.0, 0.01);
            found_markup = true;
        }
    }

    poppler_page_free_annot_mapping(annot_mappings);
    g_object_unref(page);

    if (!found_markup) {
        GTEST_SKIP() << "No markup annotation found in test PDF";
    }
}

// Test with CA=0.5 (half transparent)
TEST_F(PopplerAnnotMarkupFromFileTest_2083, GetHalfOpacity_2083) {
    const char *pdf_content =
        "%PDF-1.4\n"
        "1 0 obj\n"
        "<< /Type /Catalog /Pages 2 0 R >>\n"
        "endobj\n"
        "2 0 obj\n"
        "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
        "endobj\n"
        "3 0 obj\n"
        "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] "
        "/Annots [4 0 R] >>\n"
        "endobj\n"
        "4 0 obj\n"
        "<< /Type /Annot /Subtype /Text /Rect [100 700 200 750] "
        "/Contents (Test) /CA 0.5 >>\n"
        "endobj\n"
        "xref\n"
        "0 5\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "0000000228 00000 n \n"
        "trailer\n"
        "<< /Size 5 /Root 1 0 R >>\n"
        "startxref\n"
        "351\n"
        "%%EOF\n";

    gsize len = strlen(pdf_content);
    GError *error = nullptr;

    gchar *tmpfile = nullptr;
    gint fd = g_file_open_tmp("test_pdf_half_XXXXXX.pdf", &tmpfile, &error);
    if (fd < 0) {
        GTEST_SKIP() << "Could not create temp file";
    }
    
    write(fd, pdf_content, len);
    close(fd);

    gchar *uri = g_filename_to_uri(tmpfile, nullptr, &error);
    if (!uri) {
        g_free(tmpfile);
        GTEST_SKIP() << "Could not create URI";
    }

    doc = poppler_document_new_from_file(uri, nullptr, &error);
    g_free(uri);
    g_unlink(tmpfile);
    g_free(tmpfile);

    if (!doc) {
        if (error) g_error_free(error);
        GTEST_SKIP() << "Could not open test PDF";
    }

    PopplerPage *page = poppler_document_get_page(doc, 0);
    if (!page) {
        GTEST_SKIP() << "Could not get page";
    }

    GList *annot_mappings = poppler_page_get_annot_mapping(page);
    
    bool found_markup = false;
    for (GList *l = annot_mappings; l != nullptr; l = l->next) {
        PopplerAnnotMapping *mapping = (PopplerAnnotMapping *)l->data;
        PopplerAnnot *annot = mapping->annot;
        
        if (POPPLER_IS_ANNOT_MARKUP(annot)) {
            PopplerAnnotMarkup *markup = POPPLER_ANNOT_MARKUP(annot);
            gdouble opacity = poppler_annot_markup_get_opacity(markup);
            EXPECT_NEAR(opacity, 0.5, 0.01);
            found_markup = true;
        }
    }

    poppler_page_free_annot_mapping(annot_mappings);
    g_object_unref(page);

    if (!found_markup) {
        GTEST_SKIP() << "No markup annotation found in test PDF";
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
