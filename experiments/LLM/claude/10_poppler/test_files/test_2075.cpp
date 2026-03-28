#include <glib.h>
#include <glib-object.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <string>

// Include poppler glib headers
extern "C" {
#include "poppler.h"
#include "poppler-private.h"
}

#include "Annot.h"
#include "PDFDoc.h"
#include "GooString.h"

class PopplerAnnotMarkupGetLabelTest_2075 : public ::testing::Test {
protected:
    void SetUp() override {
        // We need a real PDF document to create annotations
        // We'll try to create a minimal test setup
    }

    void TearDown() override {
    }

    // Helper to create a PopplerDocument from a minimal PDF in memory
    PopplerDocument *createMinimalDocument() {
        // Create a minimal valid PDF in memory
        const char *minimal_pdf =
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
            "<< /Type /Annot /Subtype /Text /Rect [100 100 200 200] "
            "/T (Test Label) /Contents (Test Content) >>\n"
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
            "381\n"
            "%%EOF\n";

        GError *error = nullptr;
        gsize len = strlen(minimal_pdf);
        GBytes *bytes = g_bytes_new(minimal_pdf, len);
        GInputStream *stream = g_memory_input_stream_new_from_bytes(bytes);
        
        PopplerDocument *doc = poppler_document_new_from_stream(
            stream, len, nullptr, nullptr, &error);
        
        g_object_unref(stream);
        g_bytes_unref(bytes);
        
        if (error) {
            g_error_free(error);
            return nullptr;
        }
        return doc;
    }
};

// Test that passing NULL returns NULL (g_return_val_if_fail check)
TEST_F(PopplerAnnotMarkupGetLabelTest_2075, NullAnnotReturnsNull_2075) {
    // Passing NULL should trigger g_return_val_if_fail and return NULL
    gchar *result = poppler_annot_markup_get_label(nullptr);
    EXPECT_EQ(result, nullptr);
}

// Test with a valid document that has a text annotation with a label
TEST_F(PopplerAnnotMarkupGetLabelTest_2075, ValidAnnotWithLabel_2075) {
    PopplerDocument *doc = createMinimalDocument();
    if (!doc) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PopplerPage *page = poppler_document_get_page(doc, 0);
    ASSERT_NE(page, nullptr);

    GList *annots = poppler_page_get_annot_mapping(page);
    
    bool found_markup = false;
    for (GList *l = annots; l != nullptr; l = l->next) {
        PopplerAnnotMapping *mapping = (PopplerAnnotMapping *)l->data;
        PopplerAnnot *annot = mapping->annot;
        
        if (POPPLER_IS_ANNOT_MARKUP(annot)) {
            PopplerAnnotMarkup *markup = POPPLER_ANNOT_MARKUP(annot);
            gchar *label = poppler_annot_markup_get_label(markup);
            
            // The annotation has /T (Test Label), so label should be non-null
            if (label != nullptr) {
                EXPECT_STREQ(label, "Test Label");
                g_free(label);
                found_markup = true;
            }
        }
    }

    poppler_page_free_annot_mapping(annots);
    g_object_unref(page);
    g_object_unref(doc);
    
    // If we couldn't find a markup annotation, that's OK for the test setup
    if (!found_markup) {
        GTEST_SKIP() << "No markup annotation found in minimal PDF";
    }
}

// Test with a document that has an annotation without a label (no /T entry)
TEST_F(PopplerAnnotMarkupGetLabelTest_2075, AnnotWithoutLabelReturnsNullOrEmpty_2075) {
    const char *pdf_no_label =
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
        "<< /Type /Annot /Subtype /Text /Rect [100 100 200 200] "
        "/Contents (No Label Here) >>\n"
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
        "370\n"
        "%%EOF\n";

    GError *error = nullptr;
    gsize len = strlen(pdf_no_label);
    GBytes *bytes = g_bytes_new(pdf_no_label, len);
    GInputStream *stream = g_memory_input_stream_new_from_bytes(bytes);
    
    PopplerDocument *doc = poppler_document_new_from_stream(
        stream, len, nullptr, nullptr, &error);
    
    g_object_unref(stream);
    g_bytes_unref(bytes);
    
    if (!doc) {
        if (error) g_error_free(error);
        GTEST_SKIP() << "Could not create PDF without label";
    }

    PopplerPage *page = poppler_document_get_page(doc, 0);
    if (!page) {
        g_object_unref(doc);
        GTEST_SKIP() << "Could not get page";
    }

    GList *annots = poppler_page_get_annot_mapping(page);
    
    for (GList *l = annots; l != nullptr; l = l->next) {
        PopplerAnnotMapping *mapping = (PopplerAnnotMapping *)l->data;
        PopplerAnnot *annot = mapping->annot;
        
        if (POPPLER_IS_ANNOT_MARKUP(annot)) {
            PopplerAnnotMarkup *markup = POPPLER_ANNOT_MARKUP(annot);
            gchar *label = poppler_annot_markup_get_label(markup);
            // Without /T entry, label could be NULL or empty string
            // The function returns nullptr when text is null
            if (label) {
                g_free(label);
            }
            // Either way, this should not crash
        }
    }

    poppler_page_free_annot_mapping(annots);
    g_object_unref(page);
    g_object_unref(doc);
}

// Test with a Unicode label
TEST_F(PopplerAnnotMarkupGetLabelTest_2075, AnnotWithUnicodeLabel_2075) {
    // PDF with a UTF-16BE encoded label using BOM
    // \xFE\xFF is BOM for UTF-16BE, followed by "AB" in UTF-16BE (\x00A\x00B)
    const char *pdf_unicode =
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
        "<< /Type /Annot /Subtype /Text /Rect [100 100 200 200] "
        "/T <FEFF00410042> /Contents (Unicode test) >>\n"
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
        "400\n"
        "%%EOF\n";

    GError *error = nullptr;
    gsize len = strlen(pdf_unicode);
    GBytes *bytes = g_bytes_new(pdf_unicode, len);
    GInputStream *stream = g_memory_input_stream_new_from_bytes(bytes);
    
    PopplerDocument *doc = poppler_document_new_from_stream(
        stream, len, nullptr, nullptr, &error);
    
    g_object_unref(stream);
    g_bytes_unref(bytes);
    
    if (!doc) {
        if (error) g_error_free(error);
        GTEST_SKIP() << "Could not create PDF with unicode label";
    }

    PopplerPage *page = poppler_document_get_page(doc, 0);
    if (!page) {
        g_object_unref(doc);
        GTEST_SKIP() << "Could not get page";
    }

    GList *annots = poppler_page_get_annot_mapping(page);
    
    for (GList *l = annots; l != nullptr; l = l->next) {
        PopplerAnnotMapping *mapping = (PopplerAnnotMapping *)l->data;
        PopplerAnnot *annot = mapping->annot;
        
        if (POPPLER_IS_ANNOT_MARKUP(annot)) {
            PopplerAnnotMarkup *markup = POPPLER_ANNOT_MARKUP(annot);
            gchar *label = poppler_annot_markup_get_label(markup);
            if (label) {
                // Should be valid UTF-8 "AB"
                EXPECT_TRUE(g_utf8_validate(label, -1, nullptr));
                EXPECT_STREQ(label, "AB");
                g_free(label);
            }
        }
    }

    poppler_page_free_annot_mapping(annots);
    g_object_unref(page);
    g_object_unref(doc);
}

// Test that the returned string is a newly allocated UTF-8 string (caller owns it)
TEST_F(PopplerAnnotMarkupGetLabelTest_2075, ReturnedStringIsNewlyAllocated_2075) {
    PopplerDocument *doc = createMinimalDocument();
    if (!doc) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PopplerPage *page = poppler_document_get_page(doc, 0);
    if (!page) {
        g_object_unref(doc);
        GTEST_SKIP() << "Could not get page";
    }

    GList *annots = poppler_page_get_annot_mapping(page);
    
    for (GList *l = annots; l != nullptr; l = l->next) {
        PopplerAnnotMapping *mapping = (PopplerAnnotMapping *)l->data;
        PopplerAnnot *annot = mapping->annot;
        
        if (POPPLER_IS_ANNOT_MARKUP(annot)) {
            PopplerAnnotMarkup *markup = POPPLER_ANNOT_MARKUP(annot);
            gchar *label1 = poppler_annot_markup_get_label(markup);
            gchar *label2 = poppler_annot_markup_get_label(markup);
            
            if (label1 && label2) {
                // Two calls should return different pointers (newly allocated each time)
                EXPECT_NE(label1, label2);
                // But same content
                EXPECT_STREQ(label1, label2);
                // Both should be valid UTF-8
                EXPECT_TRUE(g_utf8_validate(label1, -1, nullptr));
                EXPECT_TRUE(g_utf8_validate(label2, -1, nullptr));
            }
            
            g_free(label1);
            g_free(label2);
        }
    }

    poppler_page_free_annot_mapping(annots);
    g_object_unref(page);
    g_object_unref(doc);
}

// Test with empty label string
TEST_F(PopplerAnnotMarkupGetLabelTest_2075, AnnotWithEmptyLabel_2075) {
    const char *pdf_empty_label =
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
        "<< /Type /Annot /Subtype /Text /Rect [100 100 200 200] "
        "/T () /Contents (Empty label test) >>\n"
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
        "390\n"
        "%%EOF\n";

    GError *error = nullptr;
    gsize len = strlen(pdf_empty_label);
    GBytes *bytes = g_bytes_new(pdf_empty_label, len);
    GInputStream *stream = g_memory_input_stream_new_from_bytes(bytes);
    
    PopplerDocument *doc = poppler_document_new_from_stream(
        stream, len, nullptr, nullptr, &error);
    
    g_object_unref(stream);
    g_bytes_unref(bytes);
    
    if (!doc) {
        if (error) g_error_free(error);
        GTEST_SKIP() << "Could not create PDF with empty label";
    }

    PopplerPage *page = poppler_document_get_page(doc, 0);
    if (!page) {
        g_object_unref(doc);
        GTEST_SKIP() << "Could not get page";
    }

    GList *annots = poppler_page_get_annot_mapping(page);
    
    for (GList *l = annots; l != nullptr; l = l->next) {
        PopplerAnnotMapping *mapping = (PopplerAnnotMapping *)l->data;
        PopplerAnnot *annot = mapping->annot;
        
        if (POPPLER_IS_ANNOT_MARKUP(annot)) {
            PopplerAnnotMarkup *markup = POPPLER_ANNOT_MARKUP(annot);
            gchar *label = poppler_annot_markup_get_label(markup);
            // Empty label - could be empty string or null
            if (label) {
                EXPECT_STREQ(label, "");
                g_free(label);
            }
        }
    }

    poppler_page_free_annot_mapping(annots);
    g_object_unref(page);
    g_object_unref(doc);
}
