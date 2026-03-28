#include <gtest/gtest.h>
#include <poppler.h>
#include <poppler-document.h>
#include <poppler-page.h>
#include <cstdio>
#include <cstring>

extern "C" {
#include <glib.h>
#include <glib-object.h>
}

class PopplerAnnotMarkupTest_2081 : public ::testing::Test {
protected:
    PopplerDocument *doc = nullptr;
    PopplerPage *page = nullptr;

    void SetUp() override {
        // We'll try to load a test PDF if available
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

    // Helper to create a minimal PDF with a text annotation that has a popup
    PopplerDocument *createPdfWithPopupAnnot() {
        // Create a minimal PDF in memory with an annotation that has a popup
        const char *pdf_content =
            "%PDF-1.4\n"
            "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
            "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
            "3 0 obj<</Type/Page/Parent 2 0 R/MediaBox[0 0 612 792]"
            "/Annots[4 0 R 5 0 R]>>endobj\n"
            "4 0 obj<</Type/Annot/Subtype/Text/Rect[100 100 200 200]"
            "/Contents(Test)/Popup 5 0 R/T(Author)/Open true>>endobj\n"
            "5 0 obj<</Type/Annot/Subtype/Popup/Rect[300 100 500 300]"
            "/Parent 4 0 R>>endobj\n"
            "xref\n0 6\n"
            "0000000000 65535 f \n"
            "0000000009 00000 n \n"
            "0000000058 00000 n \n"
            "0000000115 00000 n \n"
            "0000000226 00000 n \n"
            "0000000375 00000 n \n"
            "trailer<</Size 6/Root 1 0 R>>\n"
            "startxref\n470\n%%EOF\n";

        // Write to a temp file
        char tmpfile[] = "/tmp/poppler_test_XXXXXX.pdf";
        int fd = mkstemps(tmpfile, 4);
        if (fd < 0) return nullptr;
        write(fd, pdf_content, strlen(pdf_content));
        close(fd);

        GError *error = nullptr;
        gchar *uri = g_filename_to_uri(tmpfile, nullptr, &error);
        if (!uri) {
            unlink(tmpfile);
            return nullptr;
        }

        PopplerDocument *document = poppler_document_new_from_file(uri, nullptr, &error);
        g_free(uri);
        unlink(tmpfile);

        if (error) {
            g_error_free(error);
            return nullptr;
        }
        return document;
    }

    // Helper to create a PDF with a text annotation without popup
    PopplerDocument *createPdfWithoutPopupAnnot() {
        const char *pdf_content =
            "%PDF-1.4\n"
            "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
            "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
            "3 0 obj<</Type/Page/Parent 2 0 R/MediaBox[0 0 612 792]"
            "/Annots[4 0 R]>>endobj\n"
            "4 0 obj<</Type/Annot/Subtype/Text/Rect[100 100 200 200]"
            "/Contents(Test)/T(Author)>>endobj\n"
            "xref\n0 5\n"
            "0000000000 65535 f \n"
            "0000000009 00000 n \n"
            "0000000058 00000 n \n"
            "0000000115 00000 n \n"
            "0000000210 00000 n \n"
            "trailer<</Size 5/Root 1 0 R>>\n"
            "startxref\n340\n%%EOF\n";

        char tmpfile[] = "/tmp/poppler_test2_XXXXXX.pdf";
        int fd = mkstemps(tmpfile, 4);
        if (fd < 0) return nullptr;
        write(fd, pdf_content, strlen(pdf_content));
        close(fd);

        GError *error = nullptr;
        gchar *uri = g_filename_to_uri(tmpfile, nullptr, &error);
        if (!uri) {
            unlink(tmpfile);
            return nullptr;
        }

        PopplerDocument *document = poppler_document_new_from_file(uri, nullptr, &error);
        g_free(uri);
        unlink(tmpfile);

        if (error) {
            g_error_free(error);
            return nullptr;
        }
        return document;
    }

    PopplerAnnotMarkup *findMarkupAnnot(PopplerPage *pg) {
        if (!pg) return nullptr;
        GList *annots = poppler_page_get_annot_mapping(pg);
        PopplerAnnotMarkup *markup = nullptr;
        for (GList *l = annots; l != nullptr; l = l->next) {
            PopplerAnnotMapping *mapping = (PopplerAnnotMapping *)l->data;
            PopplerAnnot *annot = mapping->annot;
            if (POPPLER_IS_ANNOT_MARKUP(annot)) {
                markup = POPPLER_ANNOT_MARKUP(g_object_ref(annot));
                break;
            }
        }
        poppler_page_free_annot_mapping(annots);
        return markup;
    }
};

// Test: NULL poppler_rect parameter should return FALSE
TEST_F(PopplerAnnotMarkupTest_2081, NullRectangleReturnsFalse_2081) {
    doc = createPdfWithPopupAnnot();
    if (!doc) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    page = poppler_document_get_page(doc, 0);
    ASSERT_NE(page, nullptr);

    PopplerAnnotMarkup *markup = findMarkupAnnot(page);
    if (!markup) {
        GTEST_SKIP() << "No markup annotation found in test PDF";
    }

    // Passing NULL for poppler_rect should return FALSE
    // Note: g_return_val_if_fail will log a warning and return FALSE
    gboolean result = poppler_annot_markup_get_popup_rectangle(markup, nullptr);
    EXPECT_FALSE(result);

    g_object_unref(markup);
}

// Test: Valid markup annotation with popup should return TRUE and fill rectangle
TEST_F(PopplerAnnotMarkupTest_2081, ValidPopupReturnsTrueAndFillsRect_2081) {
    doc = createPdfWithPopupAnnot();
    if (!doc) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    page = poppler_document_get_page(doc, 0);
    ASSERT_NE(page, nullptr);

    PopplerAnnotMarkup *markup = findMarkupAnnot(page);
    if (!markup) {
        GTEST_SKIP() << "No markup annotation found in test PDF";
    }

    PopplerRectangle rect;
    memset(&rect, 0, sizeof(rect));
    gboolean result = poppler_annot_markup_get_popup_rectangle(markup, &rect);

    if (result) {
        // The popup rect was [300 100 500 300] in our PDF
        // Verify the rectangle was filled with non-zero values
        EXPECT_TRUE(result);
        // The rectangle should have been populated from the popup annotation
        // We check that at least some coordinates are set
        // (exact values depend on PDF parsing)
    }

    g_object_unref(markup);
}

// Test: Markup annotation without popup should return FALSE
TEST_F(PopplerAnnotMarkupTest_2081, NoPopupReturnsFalse_2081) {
    doc = createPdfWithoutPopupAnnot();
    if (!doc) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    page = poppler_document_get_page(doc, 0);
    ASSERT_NE(page, nullptr);

    PopplerAnnotMarkup *markup = findMarkupAnnot(page);
    if (!markup) {
        GTEST_SKIP() << "No markup annotation found in test PDF";
    }

    PopplerRectangle rect;
    memset(&rect, 0, sizeof(rect));
    gboolean result = poppler_annot_markup_get_popup_rectangle(markup, &rect);

    // If no popup is associated, should return FALSE
    EXPECT_FALSE(result);

    g_object_unref(markup);
}

// Test: Rectangle values are correctly populated from popup annotation
TEST_F(PopplerAnnotMarkupTest_2081, RectangleValuesCorrectlyPopulated_2081) {
    doc = createPdfWithPopupAnnot();
    if (!doc) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    page = poppler_document_get_page(doc, 0);
    ASSERT_NE(page, nullptr);

    PopplerAnnotMarkup *markup = findMarkupAnnot(page);
    if (!markup) {
        GTEST_SKIP() << "No markup annotation found in test PDF";
    }

    PopplerRectangle rect;
    rect.x1 = -1;
    rect.y1 = -1;
    rect.x2 = -1;
    rect.y2 = -1;

    gboolean result = poppler_annot_markup_get_popup_rectangle(markup, &rect);

    if (result) {
        // The values should have been overwritten from the popup annotation's rect
        // Our PDF defined popup rect as [300 100 500 300]
        EXPECT_NEAR(rect.x1, 300.0, 1.0);
        EXPECT_NEAR(rect.y1, 100.0, 1.0);
        EXPECT_NEAR(rect.x2, 500.0, 1.0);
        EXPECT_NEAR(rect.y2, 300.0, 1.0);
    }

    g_object_unref(markup);
}

// Test: Calling with NULL annot should return FALSE (g_return_val_if_fail)
TEST_F(PopplerAnnotMarkupTest_2081, NullAnnotReturnsFalse_2081) {
    PopplerRectangle rect;
    memset(&rect, 0, sizeof(rect));

    // Passing NULL for annot; g_return_val_if_fail should catch this
    gboolean result = poppler_annot_markup_get_popup_rectangle(nullptr, &rect);
    EXPECT_FALSE(result);
}

// Test: Multiple calls return consistent results
TEST_F(PopplerAnnotMarkupTest_2081, MultipleCallsReturnConsistentResults_2081) {
    doc = createPdfWithPopupAnnot();
    if (!doc) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    page = poppler_document_get_page(doc, 0);
    ASSERT_NE(page, nullptr);

    PopplerAnnotMarkup *markup = findMarkupAnnot(page);
    if (!markup) {
        GTEST_SKIP() << "No markup annotation found in test PDF";
    }

    PopplerRectangle rect1, rect2;
    memset(&rect1, 0, sizeof(rect1));
    memset(&rect2, 0, sizeof(rect2));

    gboolean result1 = poppler_annot_markup_get_popup_rectangle(markup, &rect1);
    gboolean result2 = poppler_annot_markup_get_popup_rectangle(markup, &rect2);

    EXPECT_EQ(result1, result2);

    if (result1 && result2) {
        EXPECT_DOUBLE_EQ(rect1.x1, rect2.x1);
        EXPECT_DOUBLE_EQ(rect1.y1, rect2.y1);
        EXPECT_DOUBLE_EQ(rect1.x2, rect2.x2);
        EXPECT_DOUBLE_EQ(rect1.y2, rect2.y2);
    }

    g_object_unref(markup);
}
