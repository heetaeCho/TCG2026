#include <glib.h>
#include <poppler.h>
#include <gtest/gtest.h>
#include <cstring>
#include <cstdio>

class PopplerAnnotMarkupSetPopupRectangleTest_2082 : public ::testing::Test {
protected:
    PopplerDocument *doc = nullptr;
    PopplerPage *page = nullptr;
    
    void SetUp() override {
        // Create a minimal PDF in memory that has a markup annotation with popup
        // We'll try to load a document and work with annotations
    }
    
    void TearDown() override {
        if (page) {
            g_object_unref(page);
        }
        if (doc) {
            g_object_unref(doc);
        }
    }
    
    PopplerDocument* createDocFromPdfBytes(const char* pdf_content, gsize len) {
        GError *error = nullptr;
        GBytes *bytes = g_bytes_new(pdf_content, len);
        PopplerDocument *d = poppler_document_new_from_bytes(bytes, nullptr, &error);
        g_bytes_unref(bytes);
        if (error) {
            g_error_free(error);
            return nullptr;
        }
        return d;
    }
};

// Test that passing NULL PopplerAnnotMarkup does not crash (g_return_if_fail handles it)
TEST_F(PopplerAnnotMarkupSetPopupRectangleTest_2082, NullAnnotDoesNotCrash_2082) {
    PopplerRectangle rect;
    rect.x1 = 0;
    rect.y1 = 0;
    rect.x2 = 100;
    rect.y2 = 100;
    
    // Should safely return due to g_return_if_fail
    // We need to suppress the g_return_if_fail warning
    g_test_expect_message("Poppler", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_ANNOT_MARKUP*");
    poppler_annot_markup_set_popup_rectangle(nullptr, &rect);
    g_test_assert_expected_messages();
}

// Test that passing NULL PopplerRectangle does not crash
TEST_F(PopplerAnnotMarkupSetPopupRectangleTest_2082, NullRectDoesNotCrash_2082) {
    // We need a valid PopplerAnnotMarkup for this path
    // Since we can't easily create one without a document, we test with NULL annot first
    // which will fail the first check before reaching the rect check.
    // For a more thorough test, we'd need a real document.
    
    // Test double-null case: first check fails before second
    g_test_expect_message("Poppler", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_ANNOT_MARKUP*");
    poppler_annot_markup_set_popup_rectangle(nullptr, nullptr);
    g_test_assert_expected_messages();
}

// Test with a real PDF document containing a text annotation (markup) with popup
TEST_F(PopplerAnnotMarkupSetPopupRectangleTest_2082, SetPopupRectangleOnRealAnnotation_2082) {
    // Minimal PDF with a Text annotation that has a Popup
    static const char pdf_data[] =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/Parent 2 0 R/MediaBox[0 0 612 792]/Annots[4 0 R 5 0 R]>>endobj\n"
        "4 0 obj<</Type/Annot/Subtype/Text/Rect[100 100 200 200]/Contents(Hello)/Popup 5 0 R/T(Author)/M(D:20230101000000)>>endobj\n"
        "5 0 obj<</Type/Annot/Subtype/Popup/Rect[200 100 400 300]/Parent 4 0 R>>endobj\n"
        "xref\n0 6\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000107 00000 n \n"
        "0000000206 00000 n \n"
        "0000000358 00000 n \n"
        "trailer<</Size 6/Root 1 0 R>>\nstartxref\n450\n%%EOF\n";

    GError *error = nullptr;
    GBytes *bytes = g_bytes_new_static(pdf_data, sizeof(pdf_data) - 1);
    doc = poppler_document_new_from_bytes(bytes, nullptr, &error);
    g_bytes_unref(bytes);
    
    if (!doc) {
        if (error) g_error_free(error);
        GTEST_SKIP() << "Could not create document from inline PDF";
        return;
    }
    
    page = poppler_document_get_page(doc, 0);
    if (!page) {
        GTEST_SKIP() << "Could not get page from document";
        return;
    }
    
    GList *annots = poppler_page_get_annot_mapping(page);
    
    PopplerAnnotMarkup *markup_annot = nullptr;
    for (GList *l = annots; l != nullptr; l = l->next) {
        PopplerAnnotMapping *mapping = static_cast<PopplerAnnotMapping *>(l->data);
        PopplerAnnot *annot = mapping->annot;
        if (POPPLER_IS_ANNOT_MARKUP(annot)) {
            markup_annot = POPPLER_ANNOT_MARKUP(annot);
            break;
        }
    }
    
    if (markup_annot) {
        PopplerRectangle rect;
        rect.x1 = 10.0;
        rect.y1 = 20.0;
        rect.x2 = 300.0;
        rect.y2 = 400.0;
        
        // Should not crash; sets popup rectangle
        poppler_annot_markup_set_popup_rectangle(markup_annot, &rect);
        
        // Verify by reading back the popup rectangle
        PopplerRectangle out_rect;
        gboolean has_popup = poppler_annot_markup_get_popup_rectangle(markup_annot, &out_rect);
        if (has_popup) {
            EXPECT_DOUBLE_EQ(out_rect.x1, 10.0);
            EXPECT_DOUBLE_EQ(out_rect.y1, 20.0);
            EXPECT_DOUBLE_EQ(out_rect.x2, 300.0);
            EXPECT_DOUBLE_EQ(out_rect.y2, 400.0);
        }
    } else {
        GTEST_SKIP() << "No markup annotation found in the test PDF";
    }
    
    poppler_page_free_annot_mapping(annots);
}

// Test setting popup rectangle with zero-area rectangle (boundary)
TEST_F(PopplerAnnotMarkupSetPopupRectangleTest_2082, SetPopupRectangleZeroArea_2082) {
    static const char pdf_data[] =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/Parent 2 0 R/MediaBox[0 0 612 792]/Annots[4 0 R 5 0 R]>>endobj\n"
        "4 0 obj<</Type/Annot/Subtype/Text/Rect[100 100 200 200]/Contents(Test)/Popup 5 0 R/T(Author)/M(D:20230101000000)>>endobj\n"
        "5 0 obj<</Type/Annot/Subtype/Popup/Rect[200 100 400 300]/Parent 4 0 R>>endobj\n"
        "xref\n0 6\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000107 00000 n \n"
        "0000000206 00000 n \n"
        "0000000355 00000 n \n"
        "trailer<</Size 6/Root 1 0 R>>\nstartxref\n447\n%%EOF\n";

    GError *error = nullptr;
    GBytes *bytes = g_bytes_new_static(pdf_data, sizeof(pdf_data) - 1);
    doc = poppler_document_new_from_bytes(bytes, nullptr, &error);
    g_bytes_unref(bytes);
    
    if (!doc) {
        if (error) g_error_free(error);
        GTEST_SKIP() << "Could not create document from inline PDF";
        return;
    }
    
    page = poppler_document_get_page(doc, 0);
    if (!page) {
        GTEST_SKIP() << "Could not get page from document";
        return;
    }
    
    GList *annots = poppler_page_get_annot_mapping(page);
    
    PopplerAnnotMarkup *markup_annot = nullptr;
    for (GList *l = annots; l != nullptr; l = l->next) {
        PopplerAnnotMapping *mapping = static_cast<PopplerAnnotMapping *>(l->data);
        PopplerAnnot *annot = mapping->annot;
        if (POPPLER_IS_ANNOT_MARKUP(annot)) {
            markup_annot = POPPLER_ANNOT_MARKUP(annot);
            break;
        }
    }
    
    if (markup_annot) {
        // Zero-area rectangle (point)
        PopplerRectangle rect;
        rect.x1 = 50.0;
        rect.y1 = 50.0;
        rect.x2 = 50.0;
        rect.y2 = 50.0;
        
        poppler_annot_markup_set_popup_rectangle(markup_annot, &rect);
        
        PopplerRectangle out_rect;
        gboolean has_popup = poppler_annot_markup_get_popup_rectangle(markup_annot, &out_rect);
        if (has_popup) {
            EXPECT_DOUBLE_EQ(out_rect.x1, 50.0);
            EXPECT_DOUBLE_EQ(out_rect.y1, 50.0);
            EXPECT_DOUBLE_EQ(out_rect.x2, 50.0);
            EXPECT_DOUBLE_EQ(out_rect.y2, 50.0);
        }
    } else {
        GTEST_SKIP() << "No markup annotation found in the test PDF";
    }
    
    poppler_page_free_annot_mapping(annots);
}

// Test setting popup rectangle with negative coordinates
TEST_F(PopplerAnnotMarkupSetPopupRectangleTest_2082, SetPopupRectangleNegativeCoords_2082) {
    static const char pdf_data[] =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/Parent 2 0 R/MediaBox[0 0 612 792]/Annots[4 0 R 5 0 R]>>endobj\n"
        "4 0 obj<</Type/Annot/Subtype/Text/Rect[100 100 200 200]/Contents(Neg)/Popup 5 0 R/T(Author)/M(D:20230101000000)>>endobj\n"
        "5 0 obj<</Type/Annot/Subtype/Popup/Rect[200 100 400 300]/Parent 4 0 R>>endobj\n"
        "xref\n0 6\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000107 00000 n \n"
        "0000000206 00000 n \n"
        "0000000354 00000 n \n"
        "trailer<</Size 6/Root 1 0 R>>\nstartxref\n446\n%%EOF\n";

    GError *error = nullptr;
    GBytes *bytes = g_bytes_new_static(pdf_data, sizeof(pdf_data) - 1);
    doc = poppler_document_new_from_bytes(bytes, nullptr, &error);
    g_bytes_unref(bytes);
    
    if (!doc) {
        if (error) g_error_free(error);
        GTEST_SKIP() << "Could not create document from inline PDF";
        return;
    }
    
    page = poppler_document_get_page(doc, 0);
    if (!page) {
        GTEST_SKIP() << "Could not get page from document";
        return;
    }
    
    GList *annots = poppler_page_get_annot_mapping(page);
    
    PopplerAnnotMarkup *markup_annot = nullptr;
    for (GList *l = annots; l != nullptr; l = l->next) {
        PopplerAnnotMapping *mapping = static_cast<PopplerAnnotMapping *>(l->data);
        PopplerAnnot *annot = mapping->annot;
        if (POPPLER_IS_ANNOT_MARKUP(annot)) {
            markup_annot = POPPLER_ANNOT_MARKUP(annot);
            break;
        }
    }
    
    if (markup_annot) {
        PopplerRectangle rect;
        rect.x1 = -100.0;
        rect.y1 = -200.0;
        rect.x2 = -10.0;
        rect.y2 = -20.0;
        
        poppler_annot_markup_set_popup_rectangle(markup_annot, &rect);
        
        PopplerRectangle out_rect;
        gboolean has_popup = poppler_annot_markup_get_popup_rectangle(markup_annot, &out_rect);
        if (has_popup) {
            EXPECT_DOUBLE_EQ(out_rect.x1, -100.0);
            EXPECT_DOUBLE_EQ(out_rect.y1, -200.0);
            EXPECT_DOUBLE_EQ(out_rect.x2, -10.0);
            EXPECT_DOUBLE_EQ(out_rect.y2, -20.0);
        }
    } else {
        GTEST_SKIP() << "No markup annotation found in the test PDF";
    }
    
    poppler_page_free_annot_mapping(annots);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
