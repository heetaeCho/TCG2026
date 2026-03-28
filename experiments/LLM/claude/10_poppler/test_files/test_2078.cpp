#include <gtest/gtest.h>
#include <poppler.h>
#include <poppler-document.h>
#include <poppler-page.h>
#include <cstdio>
#include <cstring>

// We need a real PDF document to create annotations
// We'll use poppler's GLib API to create test fixtures

class PopplerAnnotMarkupSetPopupTest_2078 : public ::testing::Test {
protected:
    PopplerDocument *doc = nullptr;
    PopplerPage *page = nullptr;
    
    void SetUp() override {
        GError *error = nullptr;
        // Try to create a minimal PDF in memory or load a test file
        // Create a minimal PDF buffer
        const char *minimal_pdf = 
            "%PDF-1.0\n"
            "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
            "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
            "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
            "xref\n"
            "0 4\n"
            "0000000000 65535 f \n"
            "0000000009 00000 n \n"
            "0000000058 00000 n \n"
            "0000000115 00000 n \n"
            "trailer<</Size 4/Root 1 0 R>>\n"
            "startxref\n"
            "190\n"
            "%%EOF\n";
        
        // Write to a temp file
        const char *tmpfile = "/tmp/test_poppler_annot_2078.pdf";
        FILE *f = fopen(tmpfile, "wb");
        if (f) {
            fwrite(minimal_pdf, 1, strlen(minimal_pdf), f);
            fclose(f);
        }
        
        gchar *uri = g_filename_to_uri(tmpfile, nullptr, &error);
        if (uri) {
            doc = poppler_document_new_from_file(uri, nullptr, &error);
            g_free(uri);
        }
        if (error) {
            g_error_free(error);
            error = nullptr;
        }
        
        if (doc) {
            page = poppler_document_get_page(doc, 0);
        }
    }
    
    void TearDown() override {
        if (page) g_object_unref(page);
        if (doc) g_object_unref(doc);
        unlink("/tmp/test_poppler_annot_2078.pdf");
    }
};

// Test that set_popup works on a valid text annotation (which is a markup annotation)
TEST_F(PopplerAnnotMarkupSetPopupTest_2078, SetPopupOnTextAnnot_2078) {
    if (!page) GTEST_SKIP() << "Could not create test document";
    
    PopplerRectangle rect;
    rect.x1 = 100.0;
    rect.y1 = 100.0;
    rect.x2 = 200.0;
    rect.y2 = 200.0;
    
    // Create a text annotation (which is a markup annotation)
    PopplerAnnot *annot = poppler_annot_text_new(doc, &rect);
    ASSERT_NE(annot, nullptr);
    ASSERT_TRUE(POPPLER_IS_ANNOT_MARKUP(annot));
    
    PopplerAnnotMarkup *markup = POPPLER_ANNOT_MARKUP(annot);
    
    PopplerRectangle popup_rect;
    popup_rect.x1 = 150.0;
    popup_rect.y1 = 150.0;
    popup_rect.x2 = 350.0;
    popup_rect.y2 = 250.0;
    
    // Should not crash and should set the popup
    poppler_annot_markup_set_popup(markup, &popup_rect);
    
    // Verify popup is set by checking has_popup
    gboolean has_popup = poppler_annot_markup_has_popup(markup);
    EXPECT_TRUE(has_popup);
    
    // Verify we can retrieve the popup rect and it matches what we set
    PopplerRectangle retrieved_rect;
    gboolean got_rect = poppler_annot_markup_get_popup_rectangle(markup, &retrieved_rect);
    EXPECT_TRUE(got_rect);
    if (got_rect) {
        EXPECT_DOUBLE_EQ(retrieved_rect.x1, 150.0);
        EXPECT_DOUBLE_EQ(retrieved_rect.y1, 150.0);
        EXPECT_DOUBLE_EQ(retrieved_rect.x2, 350.0);
        EXPECT_DOUBLE_EQ(retrieved_rect.y2, 250.0);
    }
    
    g_object_unref(annot);
}

// Test setting popup with zero-area rectangle (boundary condition)
TEST_F(PopplerAnnotMarkupSetPopupTest_2078, SetPopupWithZeroAreaRect_2078) {
    if (!page) GTEST_SKIP() << "Could not create test document";
    
    PopplerRectangle rect;
    rect.x1 = 100.0;
    rect.y1 = 100.0;
    rect.x2 = 200.0;
    rect.y2 = 200.0;
    
    PopplerAnnot *annot = poppler_annot_text_new(doc, &rect);
    ASSERT_NE(annot, nullptr);
    
    PopplerAnnotMarkup *markup = POPPLER_ANNOT_MARKUP(annot);
    
    PopplerRectangle popup_rect;
    popup_rect.x1 = 0.0;
    popup_rect.y1 = 0.0;
    popup_rect.x2 = 0.0;
    popup_rect.y2 = 0.0;
    
    // Should not crash even with zero-area rect
    poppler_annot_markup_set_popup(markup, &popup_rect);
    
    gboolean has_popup = poppler_annot_markup_has_popup(markup);
    EXPECT_TRUE(has_popup);
    
    g_object_unref(annot);
}

// Test setting popup with negative coordinates (boundary condition)
TEST_F(PopplerAnnotMarkupSetPopupTest_2078, SetPopupWithNegativeCoords_2078) {
    if (!page) GTEST_SKIP() << "Could not create test document";
    
    PopplerRectangle rect;
    rect.x1 = 100.0;
    rect.y1 = 100.0;
    rect.x2 = 200.0;
    rect.y2 = 200.0;
    
    PopplerAnnot *annot = poppler_annot_text_new(doc, &rect);
    ASSERT_NE(annot, nullptr);
    
    PopplerAnnotMarkup *markup = POPPLER_ANNOT_MARKUP(annot);
    
    PopplerRectangle popup_rect;
    popup_rect.x1 = -50.0;
    popup_rect.y1 = -50.0;
    popup_rect.x2 = 100.0;
    popup_rect.y2 = 100.0;
    
    poppler_annot_markup_set_popup(markup, &popup_rect);
    
    gboolean has_popup = poppler_annot_markup_has_popup(markup);
    EXPECT_TRUE(has_popup);
    
    PopplerRectangle retrieved_rect;
    gboolean got_rect = poppler_annot_markup_get_popup_rectangle(markup, &retrieved_rect);
    EXPECT_TRUE(got_rect);
    if (got_rect) {
        EXPECT_DOUBLE_EQ(retrieved_rect.x1, -50.0);
        EXPECT_DOUBLE_EQ(retrieved_rect.y1, -50.0);
        EXPECT_DOUBLE_EQ(retrieved_rect.x2, 100.0);
        EXPECT_DOUBLE_EQ(retrieved_rect.y2, 100.0);
    }
    
    g_object_unref(annot);
}

// Test setting popup with very large coordinates (boundary condition)
TEST_F(PopplerAnnotMarkupSetPopupTest_2078, SetPopupWithLargeCoords_2078) {
    if (!page) GTEST_SKIP() << "Could not create test document";
    
    PopplerRectangle rect;
    rect.x1 = 100.0;
    rect.y1 = 100.0;
    rect.x2 = 200.0;
    rect.y2 = 200.0;
    
    PopplerAnnot *annot = poppler_annot_text_new(doc, &rect);
    ASSERT_NE(annot, nullptr);
    
    PopplerAnnotMarkup *markup = POPPLER_ANNOT_MARKUP(annot);
    
    PopplerRectangle popup_rect;
    popup_rect.x1 = 0.0;
    popup_rect.y1 = 0.0;
    popup_rect.x2 = 1e6;
    popup_rect.y2 = 1e6;
    
    poppler_annot_markup_set_popup(markup, &popup_rect);
    
    gboolean has_popup = poppler_annot_markup_has_popup(markup);
    EXPECT_TRUE(has_popup);
    
    g_object_unref(annot);
}

// Test overwriting popup by calling set_popup twice
TEST_F(PopplerAnnotMarkupSetPopupTest_2078, SetPopupTwiceOverwrites_2078) {
    if (!page) GTEST_SKIP() << "Could not create test document";
    
    PopplerRectangle rect;
    rect.x1 = 100.0;
    rect.y1 = 100.0;
    rect.x2 = 200.0;
    rect.y2 = 200.0;
    
    PopplerAnnot *annot = poppler_annot_text_new(doc, &rect);
    ASSERT_NE(annot, nullptr);
    
    PopplerAnnotMarkup *markup = POPPLER_ANNOT_MARKUP(annot);
    
    PopplerRectangle popup_rect1;
    popup_rect1.x1 = 10.0;
    popup_rect1.y1 = 10.0;
    popup_rect1.x2 = 100.0;
    popup_rect1.y2 = 100.0;
    
    poppler_annot_markup_set_popup(markup, &popup_rect1);
    
    PopplerRectangle popup_rect2;
    popup_rect2.x1 = 200.0;
    popup_rect2.y1 = 200.0;
    popup_rect2.x2 = 400.0;
    popup_rect2.y2 = 400.0;
    
    // Setting popup again should overwrite
    poppler_annot_markup_set_popup(markup, &popup_rect2);
    
    gboolean has_popup = poppler_annot_markup_has_popup(markup);
    EXPECT_TRUE(has_popup);
    
    PopplerRectangle retrieved_rect;
    gboolean got_rect = poppler_annot_markup_get_popup_rectangle(markup, &retrieved_rect);
    EXPECT_TRUE(got_rect);
    if (got_rect) {
        EXPECT_DOUBLE_EQ(retrieved_rect.x1, 200.0);
        EXPECT_DOUBLE_EQ(retrieved_rect.y1, 200.0);
        EXPECT_DOUBLE_EQ(retrieved_rect.x2, 400.0);
        EXPECT_DOUBLE_EQ(retrieved_rect.y2, 400.0);
    }
    
    g_object_unref(annot);
}

// Test that passing NULL for poppler_annot triggers g_return_if_fail (no crash)
TEST_F(PopplerAnnotMarkupSetPopupTest_2078, NullAnnotDoesNotCrash_2078) {
    PopplerRectangle popup_rect;
    popup_rect.x1 = 10.0;
    popup_rect.y1 = 10.0;
    popup_rect.x2 = 100.0;
    popup_rect.y2 = 100.0;
    
    // g_return_if_fail should just return without crashing
    poppler_annot_markup_set_popup(nullptr, &popup_rect);
    // If we reach here, the test passes (no crash/abort)
    SUCCEED();
}

// Test with inverted rectangle coordinates (x1 > x2, y1 > y2)
TEST_F(PopplerAnnotMarkupSetPopupTest_2078, SetPopupWithInvertedCoords_2078) {
    if (!page) GTEST_SKIP() << "Could not create test document";
    
    PopplerRectangle rect;
    rect.x1 = 100.0;
    rect.y1 = 100.0;
    rect.x2 = 200.0;
    rect.y2 = 200.0;
    
    PopplerAnnot *annot = poppler_annot_text_new(doc, &rect);
    ASSERT_NE(annot, nullptr);
    
    PopplerAnnotMarkup *markup = POPPLER_ANNOT_MARKUP(annot);
    
    // Inverted coordinates
    PopplerRectangle popup_rect;
    popup_rect.x1 = 300.0;
    popup_rect.y1 = 300.0;
    popup_rect.x2 = 100.0;
    popup_rect.y2 = 100.0;
    
    // Should not crash
    poppler_annot_markup_set_popup(markup, &popup_rect);
    
    gboolean has_popup = poppler_annot_markup_has_popup(markup);
    EXPECT_TRUE(has_popup);
    
    g_object_unref(annot);
}
