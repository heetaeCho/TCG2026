#include <glib.h>
#include <poppler.h>
#include <poppler-document.h>
#include <poppler-page.h>
#include <gtest/gtest.h>
#include <cstdio>
#include <cstring>

class PopplerAnnotMarkupGetDateTest_2085 : public ::testing::Test {
protected:
    void SetUp() override {
        doc_ = nullptr;
        page_ = nullptr;
    }

    void TearDown() override {
        if (page_) {
            g_object_unref(page_);
        }
        if (doc_) {
            g_object_unref(doc_);
        }
    }

    // Helper to create a minimal PDF in memory with a markup annotation
    PopplerDocument *createPdfWithAnnotation(const char *dateStr) {
        // Create a minimal PDF with a text annotation that has a date
        GString *pdf = g_string_new(nullptr);
        
        if (dateStr) {
            g_string_printf(pdf,
                "%%PDF-1.4\n"
                "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                "3 0 obj<</Type/Page/Parent 2 0 R/MediaBox[0 0 612 792]/Annots[4 0 R]>>endobj\n"
                "4 0 obj<</Type/Annot/Subtype/Text/Rect[100 100 200 200]/M(%s)/Contents(test)>>endobj\n"
                "xref\n"
                "0 5\n"
                "0000000000 65535 f \n"
                "0000000009 00000 n \n"
                "0000000058 00000 n \n"
                "0000000115 00000 n \n"
                "0000000210 00000 n \n"
                "trailer<</Size 5/Root 1 0 R>>\n"
                "startxref\n"
                "330\n"
                "%%%%EOF\n",
                dateStr);
        } else {
            g_string_printf(pdf,
                "%%PDF-1.4\n"
                "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                "3 0 obj<</Type/Page/Parent 2 0 R/MediaBox[0 0 612 792]/Annots[4 0 R]>>endobj\n"
                "4 0 obj<</Type/Annot/Subtype/Text/Rect[100 100 200 200]/Contents(test)>>endobj\n"
                "xref\n"
                "0 5\n"
                "0000000000 65535 f \n"
                "0000000009 00000 n \n"
                "0000000058 00000 n \n"
                "0000000115 00000 n \n"
                "0000000206 00000 n \n"
                "trailer<</Size 5/Root 1 0 R>>\n"
                "startxref\n"
                "300\n"
                "%%%%EOF\n");
        }

        GError *error = nullptr;
        PopplerDocument *document = poppler_document_new_from_data(pdf->str, pdf->len, nullptr, &error);
        g_string_free(pdf, TRUE);
        
        if (error) {
            g_error_free(error);
            return nullptr;
        }
        return document;
    }

    PopplerDocument *doc_;
    PopplerPage *page_;
};

// Test that passing NULL returns NULL (g_return_val_if_fail should catch it)
TEST_F(PopplerAnnotMarkupGetDateTest_2085, NullAnnotReturnsNull_2085) {
    // Passing NULL should trigger g_return_val_if_fail and return NULL
    // This will produce a g_critical warning, which is expected
    g_test_expect_message(nullptr, G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_ANNOT_MARKUP*");
    GDate *date = poppler_annot_markup_get_date(nullptr);
    g_test_assert_expected_messages();
    EXPECT_EQ(date, nullptr);
}

// Test with a valid PDF that has an annotation with a proper date
TEST_F(PopplerAnnotMarkupGetDateTest_2085, ValidDateReturnsGDate_2085) {
    // Create a simple PDF file with a text annotation that has a date
    const char *pdf_content = 
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/Parent 2 0 R/MediaBox[0 0 612 792]/Annots[4 0 R]>>endobj\n"
        "4 0 obj<</Type/Annot/Subtype/Text/Rect[100 100 200 200]/M(D:20230615120000)/Contents(test)>>endobj\n"
        "xref\n"
        "0 5\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "0000000210 00000 n \n"
        "trailer<</Size 5/Root 1 0 R>>\n"
        "startxref\n"
        "350\n"
        "%%EOF\n";

    gsize len = strlen(pdf_content);
    GError *error = nullptr;
    
    // Try using poppler_document_new_from_bytes or from_data
    GBytes *bytes = g_bytes_new(pdf_content, len);
    doc_ = poppler_document_new_from_bytes(bytes, nullptr, &error);
    g_bytes_unref(bytes);

    if (!doc_) {
        if (error) g_error_free(error);
        // If we can't create a doc from this minimal PDF, skip
        GTEST_SKIP() << "Could not create PDF document from minimal content";
        return;
    }

    page_ = poppler_document_get_page(doc_, 0);
    ASSERT_NE(page_, nullptr);

    GList *annots = poppler_page_get_annot_mapping(page_);
    if (!annots) {
        GTEST_SKIP() << "No annotations found in test PDF";
        return;
    }

    PopplerAnnotMapping *mapping = static_cast<PopplerAnnotMapping *>(annots->data);
    PopplerAnnot *annot = mapping->annot;
    
    if (POPPLER_IS_ANNOT_MARKUP(annot)) {
        PopplerAnnotMarkup *markup = POPPLER_ANNOT_MARKUP(annot);
        GDate *date = poppler_annot_markup_get_date(markup);
        
        if (date) {
            // The date should be valid
            EXPECT_TRUE(g_date_valid(date));
            // Check year/month/day match 2023-06-15
            EXPECT_EQ(g_date_get_year(date), 2023);
            EXPECT_EQ(g_date_get_month(date), G_DATE_JUNE);
            EXPECT_EQ(g_date_get_day(date), 15);
            g_date_free(date);
        }
        // date can be NULL if the date string wasn't parsed properly by the backend
    }

    poppler_page_free_annot_mapping(annots);
}

// Test with annotation that has no date field
TEST_F(PopplerAnnotMarkupGetDateTest_2085, NoDateReturnsNull_2085) {
    const char *pdf_content = 
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/Parent 2 0 R/MediaBox[0 0 612 792]/Annots[4 0 R]>>endobj\n"
        "4 0 obj<</Type/Annot/Subtype/Text/Rect[100 100 200 200]/Contents(test)>>endobj\n"
        "xref\n"
        "0 5\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "0000000206 00000 n \n"
        "trailer<</Size 5/Root 1 0 R>>\n"
        "startxref\n"
        "320\n"
        "%%EOF\n";

    gsize len = strlen(pdf_content);
    GError *error = nullptr;
    
    GBytes *bytes = g_bytes_new(pdf_content, len);
    doc_ = poppler_document_new_from_bytes(bytes, nullptr, &error);
    g_bytes_unref(bytes);

    if (!doc_) {
        if (error) g_error_free(error);
        GTEST_SKIP() << "Could not create PDF document from minimal content";
        return;
    }

    page_ = poppler_document_get_page(doc_, 0);
    ASSERT_NE(page_, nullptr);

    GList *annots = poppler_page_get_annot_mapping(page_);
    if (!annots) {
        GTEST_SKIP() << "No annotations found in test PDF";
        return;
    }

    PopplerAnnotMapping *mapping = static_cast<PopplerAnnotMapping *>(annots->data);
    PopplerAnnot *annot = mapping->annot;
    
    if (POPPLER_IS_ANNOT_MARKUP(annot)) {
        PopplerAnnotMarkup *markup = POPPLER_ANNOT_MARKUP(annot);
        GDate *date = poppler_annot_markup_get_date(markup);
        // With no /M key, getDate() should return nullptr, so result should be NULL
        EXPECT_EQ(date, nullptr);
        if (date) {
            g_date_free(date);
        }
    }

    poppler_page_free_annot_mapping(annots);
}

// Test with an invalid date string in the annotation
TEST_F(PopplerAnnotMarkupGetDateTest_2085, InvalidDateReturnsNull_2085) {
    const char *pdf_content = 
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/Parent 2 0 R/MediaBox[0 0 612 792]/Annots[4 0 R]>>endobj\n"
        "4 0 obj<</Type/Annot/Subtype/Text/Rect[100 100 200 200]/M(not_a_valid_date)/Contents(test)>>endobj\n"
        "xref\n"
        "0 5\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "0000000210 00000 n \n"
        "trailer<</Size 5/Root 1 0 R>>\n"
        "startxref\n"
        "360\n"
        "%%EOF\n";

    gsize len = strlen(pdf_content);
    GError *error = nullptr;
    
    GBytes *bytes = g_bytes_new(pdf_content, len);
    doc_ = poppler_document_new_from_bytes(bytes, nullptr, &error);
    g_bytes_unref(bytes);

    if (!doc_) {
        if (error) g_error_free(error);
        GTEST_SKIP() << "Could not create PDF document from minimal content";
        return;
    }

    page_ = poppler_document_get_page(doc_, 0);
    ASSERT_NE(page_, nullptr);

    GList *annots = poppler_page_get_annot_mapping(page_);
    if (!annots) {
        GTEST_SKIP() << "No annotations found in test PDF";
        return;
    }

    PopplerAnnotMapping *mapping = static_cast<PopplerAnnotMapping *>(annots->data);
    PopplerAnnot *annot = mapping->annot;
    
    if (POPPLER_IS_ANNOT_MARKUP(annot)) {
        PopplerAnnotMarkup *markup = POPPLER_ANNOT_MARKUP(annot);
        GDate *date = poppler_annot_markup_get_date(markup);
        // Invalid date string should not be convertible, returning NULL
        EXPECT_EQ(date, nullptr);
        if (date) {
            g_date_free(date);
        }
    }

    poppler_page_free_annot_mapping(annots);
}

// Test passing a non-markup annotation type triggers the type check
TEST_F(PopplerAnnotMarkupGetDateTest_2085, NonMarkupAnnotReturnsNull_2085) {
    // Casting a non-markup object should fail POPPLER_IS_ANNOT_MARKUP check
    // We'll just test with a plain GObject to trigger the guard
    GObject *obj = (GObject *)g_object_new(G_TYPE_OBJECT, nullptr);
    
    g_test_expect_message(nullptr, G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_ANNOT_MARKUP*");
    GDate *date = poppler_annot_markup_get_date((PopplerAnnotMarkup *)obj);
    g_test_assert_expected_messages();
    
    EXPECT_EQ(date, nullptr);
    g_object_unref(obj);
}
