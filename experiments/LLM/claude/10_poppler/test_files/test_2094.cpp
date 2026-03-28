#include <glib.h>
#include <poppler.h>
#include <gtest/gtest.h>
#include <cstring>
#include <cstdio>

class PopplerAnnotTextMarkupTest_2094 : public ::testing::Test {
protected:
    PopplerDocument *doc = nullptr;
    PopplerPage *page = nullptr;
    
    void SetUp() override {
        // Create a minimal PDF in memory
        const char *pdf_content = 
            "%PDF-1.4\n"
            "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
            "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
            "3 0 obj<</Type/Page/Parent 2 0 R/MediaBox[0 0 612 792]/Contents 4 0 R/Resources<<>>>>endobj\n"
            "4 0 obj<</Length 44>>stream\nBT /F1 12 Tf 100 700 Td (Hello World) Tj ET\nendstream\nendobj\n"
            "xref\n0 5\n"
            "0000000000 65535 f \n"
            "0000000009 00000 n \n"
            "0000000058 00000 n \n"
            "0000000115 00000 n \n"
            "0000000232 00000 n \n"
            "trailer<</Size 5/Root 1 0 R>>\nstartxref\n326\n%%EOF\n";
        
        gsize len = strlen(pdf_content);
        GError *error = nullptr;
        
        // Write to temp file
        gchar *tmpfile = nullptr;
        gint fd = g_file_open_tmp("test_XXXXXX.pdf", &tmpfile, &error);
        if (fd >= 0) {
            write(fd, pdf_content, len);
            close(fd);
            
            gchar *uri = g_filename_to_uri(tmpfile, nullptr, &error);
            if (uri) {
                doc = poppler_document_new_from_file(uri, nullptr, &error);
                g_free(uri);
            }
            if (doc) {
                page = poppler_document_get_page(doc, 0);
            }
            g_unlink(tmpfile);
            g_free(tmpfile);
        }
        if (error) {
            g_error_free(error);
        }
    }
    
    void TearDown() override {
        if (page) g_object_unref(page);
        if (doc) g_object_unref(doc);
    }
    
    GArray* create_valid_quadrilaterals(int count = 1) {
        GArray *quads = g_array_new(FALSE, FALSE, sizeof(PopplerQuadrilateral));
        for (int i = 0; i < count; i++) {
            PopplerQuadrilateral quad;
            quad.p1.x = 100.0; quad.p1.y = 700.0;
            quad.p2.x = 200.0; quad.p2.y = 700.0;
            quad.p3.x = 100.0; quad.p3.y = 680.0;
            quad.p4.x = 200.0; quad.p4.y = 680.0;
            g_array_append_val(quads, quad);
        }
        return quads;
    }
};

// Test that passing NULL annotation does not crash (g_return_if_fail guard)
TEST_F(PopplerAnnotTextMarkupTest_2094, NullAnnotDoesNotCrash_2094) {
    GArray *quads = create_valid_quadrilaterals();
    // Should silently return due to g_return_if_fail
    poppler_annot_text_markup_set_quadrilaterals(nullptr, quads);
    g_array_free(quads, TRUE);
}

// Test that passing NULL quadrilaterals does not crash
TEST_F(PopplerAnnotTextMarkupTest_2094, NullQuadrilateralsDoesNotCrash_2094) {
    if (!page) GTEST_SKIP() << "Could not create test PDF";
    
    PopplerRectangle rect = {100, 680, 200, 700};
    GArray *quads = create_valid_quadrilaterals();
    PopplerAnnot *annot = poppler_annot_text_markup_new_highlight(doc, &rect, quads);
    g_array_free(quads, TRUE);
    
    if (!annot) GTEST_SKIP() << "Could not create annotation";
    
    // Should silently return due to g_return_if_fail
    poppler_annot_text_markup_set_quadrilaterals(POPPLER_ANNOT_TEXT_MARKUP(annot), nullptr);
    
    g_object_unref(annot);
}

// Test that passing empty quadrilaterals array does not crash
TEST_F(PopplerAnnotTextMarkupTest_2094, EmptyQuadrilateralsDoesNotCrash_2094) {
    if (!page) GTEST_SKIP() << "Could not create test PDF";
    
    PopplerRectangle rect = {100, 680, 200, 700};
    GArray *quads = create_valid_quadrilaterals();
    PopplerAnnot *annot = poppler_annot_text_markup_new_highlight(doc, &rect, quads);
    g_array_free(quads, TRUE);
    
    if (!annot) GTEST_SKIP() << "Could not create annotation";
    
    GArray *empty_quads = g_array_new(FALSE, FALSE, sizeof(PopplerQuadrilateral));
    // len == 0, should trigger g_return_if_fail
    poppler_annot_text_markup_set_quadrilaterals(POPPLER_ANNOT_TEXT_MARKUP(annot), empty_quads);
    
    g_array_free(empty_quads, TRUE);
    g_object_unref(annot);
}

// Test setting quadrilaterals on a valid highlight annotation
TEST_F(PopplerAnnotTextMarkupTest_2094, SetQuadrilateralsOnHighlight_2094) {
    if (!page) GTEST_SKIP() << "Could not create test PDF";
    
    PopplerRectangle rect = {100, 680, 200, 700};
    GArray *quads = create_valid_quadrilaterals();
    PopplerAnnot *annot = poppler_annot_text_markup_new_highlight(doc, &rect, quads);
    g_array_free(quads, TRUE);
    
    if (!annot) GTEST_SKIP() << "Could not create annotation";
    
    // Create new quadrilaterals and set them
    GArray *new_quads = create_valid_quadrilaterals(2);
    poppler_annot_text_markup_set_quadrilaterals(POPPLER_ANNOT_TEXT_MARKUP(annot), new_quads);
    
    // Verify by getting quadrilaterals back
    GArray *result = poppler_annot_text_markup_get_quadrilaterals(POPPLER_ANNOT_TEXT_MARKUP(annot));
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->len, 2u);
    
    g_array_free(new_quads, TRUE);
    g_array_free(result, TRUE);
    g_object_unref(annot);
}

// Test setting single quadrilateral
TEST_F(PopplerAnnotTextMarkupTest_2094, SetSingleQuadrilateral_2094) {
    if (!page) GTEST_SKIP() << "Could not create test PDF";
    
    PopplerRectangle rect = {100, 680, 200, 700};
    GArray *quads = create_valid_quadrilaterals(3);
    PopplerAnnot *annot = poppler_annot_text_markup_new_highlight(doc, &rect, quads);
    g_array_free(quads, TRUE);
    
    if (!annot) GTEST_SKIP() << "Could not create annotation";
    
    GArray *single_quad = create_valid_quadrilaterals(1);
    poppler_annot_text_markup_set_quadrilaterals(POPPLER_ANNOT_TEXT_MARKUP(annot), single_quad);
    
    GArray *result = poppler_annot_text_markup_get_quadrilaterals(POPPLER_ANNOT_TEXT_MARKUP(annot));
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->len, 1u);
    
    g_array_free(single_quad, TRUE);
    g_array_free(result, TRUE);
    g_object_unref(annot);
}

// Test that quadrilateral coordinates are preserved
TEST_F(PopplerAnnotTextMarkupTest_2094, QuadrilateralCoordinatesPreserved_2094) {
    if (!page) GTEST_SKIP() << "Could not create test PDF";
    
    PopplerRectangle rect = {50, 500, 300, 600};
    GArray *init_quads = create_valid_quadrilaterals();
    PopplerAnnot *annot = poppler_annot_text_markup_new_highlight(doc, &rect, init_quads);
    g_array_free(init_quads, TRUE);
    
    if (!annot) GTEST_SKIP() << "Could not create annotation";
    
    GArray *quads = g_array_new(FALSE, FALSE, sizeof(PopplerQuadrilateral));
    PopplerQuadrilateral quad;
    quad.p1.x = 50.0;  quad.p1.y = 600.0;
    quad.p2.x = 300.0; quad.p2.y = 600.0;
    quad.p3.x = 50.0;  quad.p3.y = 500.0;
    quad.p4.x = 300.0; quad.p4.y = 500.0;
    g_array_append_val(quads, quad);
    
    poppler_annot_text_markup_set_quadrilaterals(POPPLER_ANNOT_TEXT_MARKUP(annot), quads);
    
    GArray *result = poppler_annot_text_markup_get_quadrilaterals(POPPLER_ANNOT_TEXT_MARKUP(annot));
    ASSERT_NE(result, nullptr);
    ASSERT_EQ(result->len, 1u);
    
    PopplerQuadrilateral *res_quad = &g_array_index(result, PopplerQuadrilateral, 0);
    EXPECT_DOUBLE_EQ(res_quad->p1.x, 50.0);
    EXPECT_DOUBLE_EQ(res_quad->p1.y, 600.0);
    EXPECT_DOUBLE_EQ(res_quad->p2.x, 300.0);
    EXPECT_DOUBLE_EQ(res_quad->p2.y, 600.0);
    EXPECT_DOUBLE_EQ(res_quad->p3.x, 50.0);
    EXPECT_DOUBLE_EQ(res_quad->p3.y, 500.0);
    EXPECT_DOUBLE_EQ(res_quad->p4.x, 300.0);
    EXPECT_DOUBLE_EQ(res_quad->p4.y, 500.0);
    
    g_array_free(quads, TRUE);
    g_array_free(result, TRUE);
    g_object_unref(annot);
}

// Test replacing quadrilaterals multiple times
TEST_F(PopplerAnnotTextMarkupTest_2094, ReplaceQuadrilateralsMultipleTimes_2094) {
    if (!page) GTEST_SKIP() << "Could not create test PDF";
    
    PopplerRectangle rect = {100, 680, 200, 700};
    GArray *quads = create_valid_quadrilaterals();
    PopplerAnnot *annot = poppler_annot_text_markup_new_highlight(doc, &rect, quads);
    g_array_free(quads, TRUE);
    
    if (!annot) GTEST_SKIP() << "Could not create annotation";
    
    // Set quadrilaterals multiple times
    for (int i = 1; i <= 5; i++) {
        GArray *new_quads = create_valid_quadrilaterals(i);
        poppler_annot_text_markup_set_quadrilaterals(POPPLER_ANNOT_TEXT_MARKUP(annot), new_quads);
        
        GArray *result = poppler_annot_text_markup_get_quadrilaterals(POPPLER_ANNOT_TEXT_MARKUP(annot));
        ASSERT_NE(result, nullptr);
        EXPECT_EQ(result->len, static_cast<guint>(i));
        
        g_array_free(new_quads, TRUE);
        g_array_free(result, TRUE);
    }
    
    g_object_unref(annot);
}

// Test with many quadrilaterals
TEST_F(PopplerAnnotTextMarkupTest_2094, ManyQuadrilaterals_2094) {
    if (!page) GTEST_SKIP() << "Could not create test PDF";
    
    PopplerRectangle rect = {100, 680, 200, 700};
    GArray *init_quads = create_valid_quadrilaterals();
    PopplerAnnot *annot = poppler_annot_text_markup_new_highlight(doc, &rect, init_quads);
    g_array_free(init_quads, TRUE);
    
    if (!annot) GTEST_SKIP() << "Could not create annotation";
    
    GArray *many_quads = create_valid_quadrilaterals(100);
    poppler_annot_text_markup_set_quadrilaterals(POPPLER_ANNOT_TEXT_MARKUP(annot), many_quads);
    
    GArray *result = poppler_annot_text_markup_get_quadrilaterals(POPPLER_ANNOT_TEXT_MARKUP(annot));
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->len, 100u);
    
    g_array_free(many_quads, TRUE);
    g_array_free(result, TRUE);
    g_object_unref(annot);
}
