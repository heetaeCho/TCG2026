#include <glib-object.h>
#include <gtest/gtest.h>

// Include poppler glib headers
extern "C" {
#include "poppler-annot.h"
#include "poppler-document.h"
#include "poppler-page.h"
}

class PopplerAnnotFreeTextSetFontColorTest_2102 : public ::testing::Test {
protected:
    PopplerAnnotFreeText *annot = nullptr;
    PopplerDocument *doc = nullptr;
    PopplerPage *page = nullptr;

    void SetUp() override {
        // We need a valid PopplerAnnotFreeText object to test with.
        // Create one via the poppler API if possible.
        // Since we need a real annotation, we'll try to create a minimal PDF document
        // and add a free text annotation to it.
        
        GError *error = nullptr;
        // Try to load a minimal PDF from memory or create annotation directly
        // Using poppler_annot_free_text_new to create the annotation
        
        // Create a minimal PDF in memory
        const char *pdf_content = 
            "%PDF-1.4\n"
            "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
            "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
            "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
            "xref\n0 4\n"
            "0000000000 65535 f \n"
            "0000000009 00000 n \n"
            "0000000058 00000 n \n"
            "0000000115 00000 n \n"
            "trailer<</Size 4/Root 1 0 R>>\n"
            "startxref\n190\n%%EOF\n";
        
        doc = poppler_document_new_from_data((char*)pdf_content, strlen(pdf_content), NULL, &error);
        if (doc) {
            page = poppler_document_get_page(doc, 0);
        }
        
        if (page) {
            PopplerRectangle rect = {100, 100, 300, 200};
            annot = (PopplerAnnotFreeText *)poppler_annot_free_text_new(doc, &rect);
        }
    }

    void TearDown() override {
        if (annot)
            g_object_unref(annot);
        if (page)
            g_object_unref(page);
        if (doc)
            g_object_unref(doc);
    }
};

TEST_F(PopplerAnnotFreeTextSetFontColorTest_2102, SetBasicRedColor_2102) {
    if (!annot) GTEST_SKIP() << "Could not create annotation";
    
    PopplerColor color;
    color.red = 65535;
    color.green = 0;
    color.blue = 0;
    
    poppler_annot_free_text_set_font_color(annot, &color);
    
    // Retrieve the font color to verify it was set
    PopplerColor *retrieved = poppler_annot_free_text_get_font_color(annot);
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->red, 65535);
    EXPECT_EQ(retrieved->green, 0);
    EXPECT_EQ(retrieved->blue, 0);
    g_free(retrieved);
}

TEST_F(PopplerAnnotFreeTextSetFontColorTest_2102, SetBasicGreenColor_2102) {
    if (!annot) GTEST_SKIP() << "Could not create annotation";
    
    PopplerColor color;
    color.red = 0;
    color.green = 65535;
    color.blue = 0;
    
    poppler_annot_free_text_set_font_color(annot, &color);
    
    PopplerColor *retrieved = poppler_annot_free_text_get_font_color(annot);
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->red, 0);
    EXPECT_EQ(retrieved->green, 65535);
    EXPECT_EQ(retrieved->blue, 0);
    g_free(retrieved);
}

TEST_F(PopplerAnnotFreeTextSetFontColorTest_2102, SetBasicBlueColor_2102) {
    if (!annot) GTEST_SKIP() << "Could not create annotation";
    
    PopplerColor color;
    color.red = 0;
    color.green = 0;
    color.blue = 65535;
    
    poppler_annot_free_text_set_font_color(annot, &color);
    
    PopplerColor *retrieved = poppler_annot_free_text_get_font_color(annot);
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->red, 0);
    EXPECT_EQ(retrieved->green, 0);
    EXPECT_EQ(retrieved->blue, 65535);
    g_free(retrieved);
}

TEST_F(PopplerAnnotFreeTextSetFontColorTest_2102, SetBlackColor_2102) {
    if (!annot) GTEST_SKIP() << "Could not create annotation";
    
    PopplerColor color;
    color.red = 0;
    color.green = 0;
    color.blue = 0;
    
    poppler_annot_free_text_set_font_color(annot, &color);
    
    PopplerColor *retrieved = poppler_annot_free_text_get_font_color(annot);
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->red, 0);
    EXPECT_EQ(retrieved->green, 0);
    EXPECT_EQ(retrieved->blue, 0);
    g_free(retrieved);
}

TEST_F(PopplerAnnotFreeTextSetFontColorTest_2102, SetWhiteColor_2102) {
    if (!annot) GTEST_SKIP() << "Could not create annotation";
    
    PopplerColor color;
    color.red = 65535;
    color.green = 65535;
    color.blue = 65535;
    
    poppler_annot_free_text_set_font_color(annot, &color);
    
    PopplerColor *retrieved = poppler_annot_free_text_get_font_color(annot);
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->red, 65535);
    EXPECT_EQ(retrieved->green, 65535);
    EXPECT_EQ(retrieved->blue, 65535);
    g_free(retrieved);
}

TEST_F(PopplerAnnotFreeTextSetFontColorTest_2102, SetColorTwiceOverwrites_2102) {
    if (!annot) GTEST_SKIP() << "Could not create annotation";
    
    PopplerColor color1;
    color1.red = 65535;
    color1.green = 0;
    color1.blue = 0;
    
    poppler_annot_free_text_set_font_color(annot, &color1);
    
    PopplerColor color2;
    color2.red = 0;
    color2.green = 0;
    color2.blue = 65535;
    
    poppler_annot_free_text_set_font_color(annot, &color2);
    
    PopplerColor *retrieved = poppler_annot_free_text_get_font_color(annot);
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->red, 0);
    EXPECT_EQ(retrieved->green, 0);
    EXPECT_EQ(retrieved->blue, 65535);
    g_free(retrieved);
}

TEST_F(PopplerAnnotFreeTextSetFontColorTest_2102, SetMidRangeColor_2102) {
    if (!annot) GTEST_SKIP() << "Could not create annotation";
    
    PopplerColor color;
    color.red = 32768;
    color.green = 16384;
    color.blue = 49152;
    
    poppler_annot_free_text_set_font_color(annot, &color);
    
    PopplerColor *retrieved = poppler_annot_free_text_get_font_color(annot);
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->red, 32768);
    EXPECT_EQ(retrieved->green, 16384);
    EXPECT_EQ(retrieved->blue, 49152);
    g_free(retrieved);
}

TEST_F(PopplerAnnotFreeTextSetFontColorTest_2102, SetColorDoesNotAffectOriginalStruct_2102) {
    if (!annot) GTEST_SKIP() << "Could not create annotation";
    
    PopplerColor color;
    color.red = 12345;
    color.green = 23456;
    color.blue = 34567;
    
    poppler_annot_free_text_set_font_color(annot, &color);
    
    // Modify the original color struct after setting
    color.red = 0;
    color.green = 0;
    color.blue = 0;
    
    // The annotation should still have the original values (copy semantics)
    PopplerColor *retrieved = poppler_annot_free_text_get_font_color(annot);
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->red, 12345);
    EXPECT_EQ(retrieved->green, 23456);
    EXPECT_EQ(retrieved->blue, 34567);
    g_free(retrieved);
}

TEST_F(PopplerAnnotFreeTextSetFontColorTest_2102, SetMaxValueColor_2102) {
    if (!annot) GTEST_SKIP() << "Could not create annotation";
    
    PopplerColor color;
    color.red = 65535;
    color.green = 65535;
    color.blue = 65535;
    
    poppler_annot_free_text_set_font_color(annot, &color);
    
    PopplerColor *retrieved = poppler_annot_free_text_get_font_color(annot);
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->red, 65535);
    EXPECT_EQ(retrieved->green, 65535);
    EXPECT_EQ(retrieved->blue, 65535);
    g_free(retrieved);
}

TEST_F(PopplerAnnotFreeTextSetFontColorTest_2102, SetColorValueOne_2102) {
    if (!annot) GTEST_SKIP() << "Could not create annotation";
    
    PopplerColor color;
    color.red = 1;
    color.green = 1;
    color.blue = 1;
    
    poppler_annot_free_text_set_font_color(annot, &color);
    
    PopplerColor *retrieved = poppler_annot_free_text_get_font_color(annot);
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->red, 1);
    EXPECT_EQ(retrieved->green, 1);
    EXPECT_EQ(retrieved->blue, 1);
    g_free(retrieved);
}
