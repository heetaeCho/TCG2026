#include <gtest/gtest.h>
#include <poppler.h>
#include <poppler-document.h>
#include <cstring>
#include <cstdio>
#include <fstream>

// Helper to create a minimal valid PDF in memory for testing
static PopplerDocument* create_test_document() {
    // Create a minimal PDF file in a temp location
    const char* pdf_content = 
        "%PDF-1.4\n"
        "1 0 obj << /Type /Catalog /Pages 2 0 R >> endobj\n"
        "2 0 obj << /Type /Pages /Kids [3 0 R] /Count 1 >> endobj\n"
        "3 0 obj << /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >> endobj\n"
        "xref\n"
        "0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer << /Size 4 /Root 1 0 R >>\n"
        "startxref\n"
        "190\n"
        "%%EOF\n";

    char tmpname[] = "/tmp/poppler_test_XXXXXX.pdf";
    int fd = mkstemps(tmpname, 4);
    if (fd < 0) return nullptr;
    write(fd, pdf_content, strlen(pdf_content));
    close(fd);

    GError *error = nullptr;
    gchar *uri = g_filename_to_uri(tmpname, nullptr, &error);
    if (!uri) {
        unlink(tmpname);
        return nullptr;
    }
    
    PopplerDocument *doc = poppler_document_new_from_file(uri, nullptr, &error);
    g_free(uri);
    unlink(tmpname);
    
    if (error) {
        g_error_free(error);
        return nullptr;
    }
    return doc;
}

class PopplerAnnotFreeTextTest_2099 : public ::testing::Test {
protected:
    void SetUp() override {
        doc = create_test_document();
        // doc may be null if PDF creation fails; tests will skip
    }

    void TearDown() override {
        if (doc) {
            g_object_unref(doc);
        }
    }

    PopplerDocument *doc = nullptr;
};

TEST_F(PopplerAnnotFreeTextTest_2099, CreateFreeTextAnnotation_2099) {
    if (!doc) GTEST_SKIP() << "Could not create test document";
    
    PopplerPage *page = poppler_document_get_page(doc, 0);
    ASSERT_NE(page, nullptr);
    
    PopplerRectangle rect;
    rect.x1 = 100;
    rect.y1 = 100;
    rect.x2 = 300;
    rect.y2 = 200;
    
    PopplerAnnot *annot = poppler_annot_free_text_new(doc, &rect);
    ASSERT_NE(annot, nullptr);
    EXPECT_EQ(poppler_annot_get_annot_type(annot), POPPLER_ANNOT_FREE_TEXT);
    
    g_object_unref(annot);
    g_object_unref(page);
}

TEST_F(PopplerAnnotFreeTextTest_2099, SetAndGetFontDescription_2099) {
    if (!doc) GTEST_SKIP() << "Could not create test document";
    
    PopplerRectangle rect = {100, 100, 300, 200};
    PopplerAnnot *annot = poppler_annot_free_text_new(doc, &rect);
    ASSERT_NE(annot, nullptr);
    
    PopplerFontDescription *desc = poppler_font_description_new();
    ASSERT_NE(desc, nullptr);
    poppler_font_description_set_family_name(desc, "Helvetica");
    poppler_font_description_set_size(desc, 14.0);
    
    poppler_annot_free_text_set_font_description(POPPLER_ANNOT_FREE_TEXT(annot), desc);
    
    PopplerFontDescription *retrieved = poppler_annot_free_text_get_font_description(POPPLER_ANNOT_FREE_TEXT(annot));
    ASSERT_NE(retrieved, nullptr);
    EXPECT_DOUBLE_EQ(retrieved->size_pt, 14.0);
    EXPECT_STREQ(retrieved->font_name, "Helvetica");
    
    poppler_font_description_free(desc);
    poppler_font_description_free(retrieved);
    g_object_unref(annot);
}

TEST_F(PopplerAnnotFreeTextTest_2099, SetFontColor_2099) {
    if (!doc) GTEST_SKIP() << "Could not create test document";
    
    PopplerRectangle rect = {100, 100, 300, 200};
    PopplerAnnot *annot = poppler_annot_free_text_new(doc, &rect);
    ASSERT_NE(annot, nullptr);
    
    PopplerColor color;
    color.red = 65535;
    color.green = 0;
    color.blue = 0;
    
    poppler_annot_free_text_set_font_color(POPPLER_ANNOT_FREE_TEXT(annot), &color);
    
    PopplerColor *retrieved = poppler_annot_free_text_get_font_color(POPPLER_ANNOT_FREE_TEXT(annot));
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->red, 65535);
    EXPECT_EQ(retrieved->green, 0);
    EXPECT_EQ(retrieved->blue, 0);
    
    g_free(retrieved);
    g_object_unref(annot);
}

TEST_F(PopplerAnnotFreeTextTest_2099, SetNullFontDescription_2099) {
    if (!doc) GTEST_SKIP() << "Could not create test document";
    
    PopplerRectangle rect = {100, 100, 300, 200};
    PopplerAnnot *annot = poppler_annot_free_text_new(doc, &rect);
    ASSERT_NE(annot, nullptr);
    
    // Setting NULL font description should use defaults (Sans, 11pt)
    poppler_annot_free_text_set_font_description(POPPLER_ANNOT_FREE_TEXT(annot), nullptr);
    
    PopplerFontDescription *retrieved = poppler_annot_free_text_get_font_description(POPPLER_ANNOT_FREE_TEXT(annot));
    // When no font description is set, expect default or null
    if (retrieved) {
        poppler_font_description_free(retrieved);
    }
    
    g_object_unref(annot);
}

TEST_F(PopplerAnnotFreeTextTest_2099, SetFontDescriptionWithDifferentSizes_2099) {
    if (!doc) GTEST_SKIP() << "Could not create test document";
    
    PopplerRectangle rect = {100, 100, 300, 200};
    PopplerAnnot *annot = poppler_annot_free_text_new(doc, &rect);
    ASSERT_NE(annot, nullptr);
    
    PopplerFontDescription *desc = poppler_font_description_new();
    ASSERT_NE(desc, nullptr);
    
    // Test with a very small size
    poppler_font_description_set_family_name(desc, "Sans");
    poppler_font_description_set_size(desc, 1.0);
    poppler_annot_free_text_set_font_description(POPPLER_ANNOT_FREE_TEXT(annot), desc);
    
    PopplerFontDescription *retrieved = poppler_annot_free_text_get_font_description(POPPLER_ANNOT_FREE_TEXT(annot));
    ASSERT_NE(retrieved, nullptr);
    EXPECT_DOUBLE_EQ(retrieved->size_pt, 1.0);
    poppler_font_description_free(retrieved);
    
    // Test with a large size
    poppler_font_description_set_size(desc, 72.0);
    poppler_annot_free_text_set_font_description(POPPLER_ANNOT_FREE_TEXT(annot), desc);
    
    retrieved = poppler_annot_free_text_get_font_description(POPPLER_ANNOT_FREE_TEXT(annot));
    ASSERT_NE(retrieved, nullptr);
    EXPECT_DOUBLE_EQ(retrieved->size_pt, 72.0);
    poppler_font_description_free(retrieved);
    
    poppler_font_description_free(desc);
    g_object_unref(annot);
}

TEST_F(PopplerAnnotFreeTextTest_2099, SetContentsWithFontDescription_2099) {
    if (!doc) GTEST_SKIP() << "Could not create test document";
    
    PopplerRectangle rect = {100, 100, 300, 200};
    PopplerAnnot *annot = poppler_annot_free_text_new(doc, &rect);
    ASSERT_NE(annot, nullptr);
    
    poppler_annot_set_contents(annot, "Test Content");
    
    PopplerFontDescription *desc = poppler_font_description_new();
    poppler_font_description_set_family_name(desc, "Serif");
    poppler_font_description_set_size(desc, 12.0);
    poppler_annot_free_text_set_font_description(POPPLER_ANNOT_FREE_TEXT(annot), desc);
    
    gchar *contents = poppler_annot_get_contents(annot);
    ASSERT_NE(contents, nullptr);
    EXPECT_STREQ(contents, "Test Content");
    g_free(contents);
    
    poppler_font_description_free(desc);
    g_object_unref(annot);
}

TEST_F(PopplerAnnotFreeTextTest_2099, SetFontColorBlack_2099) {
    if (!doc) GTEST_SKIP() << "Could not create test document";
    
    PopplerRectangle rect = {100, 100, 300, 200};
    PopplerAnnot *annot = poppler_annot_free_text_new(doc, &rect);
    ASSERT_NE(annot, nullptr);
    
    PopplerColor color;
    color.red = 0;
    color.green = 0;
    color.blue = 0;
    
    poppler_annot_free_text_set_font_color(POPPLER_ANNOT_FREE_TEXT(annot), &color);
    
    PopplerColor *retrieved = poppler_annot_free_text_get_font_color(POPPLER_ANNOT_FREE_TEXT(annot));
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->red, 0);
    EXPECT_EQ(retrieved->green, 0);
    EXPECT_EQ(retrieved->blue, 0);
    
    g_free(retrieved);
    g_object_unref(annot);
}

TEST_F(PopplerAnnotFreeTextTest_2099, SetFontColorWhite_2099) {
    if (!doc) GTEST_SKIP() << "Could not create test document";
    
    PopplerRectangle rect = {100, 100, 300, 200};
    PopplerAnnot *annot = poppler_annot_free_text_new(doc, &rect);
    ASSERT_NE(annot, nullptr);
    
    PopplerColor color;
    color.red = 65535;
    color.green = 65535;
    color.blue = 65535;
    
    poppler_annot_free_text_set_font_color(POPPLER_ANNOT_FREE_TEXT(annot), &color);
    
    PopplerColor *retrieved = poppler_annot_free_text_get_font_color(POPPLER_ANNOT_FREE_TEXT(annot));
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->red, 65535);
    EXPECT_EQ(retrieved->green, 65535);
    EXPECT_EQ(retrieved->blue, 65535);
    
    g_free(retrieved);
    g_object_unref(annot);
}

TEST_F(PopplerAnnotFreeTextTest_2099, MultipleFontDescriptionUpdates_2099) {
    if (!doc) GTEST_SKIP() << "Could not create test document";
    
    PopplerRectangle rect = {100, 100, 300, 200};
    PopplerAnnot *annot = poppler_annot_free_text_new(doc, &rect);
    ASSERT_NE(annot, nullptr);
    
    // First update
    PopplerFontDescription *desc1 = poppler_font_description_new();
    poppler_font_description_set_family_name(desc1, "Courier");
    poppler_font_description_set_size(desc1, 10.0);
    poppler_annot_free_text_set_font_description(POPPLER_ANNOT_FREE_TEXT(annot), desc1);
    
    PopplerFontDescription *retrieved1 = poppler_annot_free_text_get_font_description(POPPLER_ANNOT_FREE_TEXT(annot));
    ASSERT_NE(retrieved1, nullptr);
    EXPECT_STREQ(retrieved1->font_name, "Courier");
    EXPECT_DOUBLE_EQ(retrieved1->size_pt, 10.0);
    poppler_font_description_free(retrieved1);
    
    // Second update - should override first
    PopplerFontDescription *desc2 = poppler_font_description_new();
    poppler_font_description_set_family_name(desc2, "Times");
    poppler_font_description_set_size(desc2, 20.0);
    poppler_annot_free_text_set_font_description(POPPLER_ANNOT_FREE_TEXT(annot), desc2);
    
    PopplerFontDescription *retrieved2 = poppler_annot_free_text_get_font_description(POPPLER_ANNOT_FREE_TEXT(annot));
    ASSERT_NE(retrieved2, nullptr);
    EXPECT_STREQ(retrieved2->font_name, "Times");
    EXPECT_DOUBLE_EQ(retrieved2->size_pt, 20.0);
    poppler_font_description_free(retrieved2);
    
    poppler_font_description_free(desc1);
    poppler_font_description_free(desc2);
    g_object_unref(annot);
}

TEST_F(PopplerAnnotFreeTextTest_2099, GetQuadding_2099) {
    if (!doc) GTEST_SKIP() << "Could not create test document";
    
    PopplerRectangle rect = {100, 100, 300, 200};
    PopplerAnnot *annot = poppler_annot_free_text_new(doc, &rect);
    ASSERT_NE(annot, nullptr);
    
    PopplerAnnotFreeTextQuadding quadding = poppler_annot_free_text_get_quadding(POPPLER_ANNOT_FREE_TEXT(annot));
    // Default quadding should be a valid enum value
    EXPECT_GE(quadding, POPPLER_ANNOT_FREE_TEXT_QUADDING_LEFT_JUSTIFIED);
    
    g_object_unref(annot);
}

TEST_F(PopplerAnnotFreeTextTest_2099, AnnotType_2099) {
    if (!doc) GTEST_SKIP() << "Could not create test document";
    
    PopplerRectangle rect = {0, 0, 100, 100};
    PopplerAnnot *annot = poppler_annot_free_text_new(doc, &rect);
    ASSERT_NE(annot, nullptr);
    
    EXPECT_EQ(poppler_annot_get_annot_type(annot), POPPLER_ANNOT_FREE_TEXT);
    
    g_object_unref(annot);
}
