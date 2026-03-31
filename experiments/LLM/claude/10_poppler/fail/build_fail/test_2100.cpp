#include <gtest/gtest.h>
#include <poppler.h>
#include <poppler-document.h>
#include <cstring>
#include <cstdio>
#include <glib.h>

extern "C" {
#include "poppler-annot.h"
}

// Helper to create a minimal PDF with a free text annotation in memory
// We use poppler's API to create/manipulate annotations

class PopplerAnnotFreeTextSetFontDescTest_2100 : public ::testing::Test {
protected:
    PopplerDocument *doc = nullptr;
    PopplerPage *page = nullptr;
    PopplerAnnot *annot = nullptr;

    void SetUp() override {
        // Create a simple PDF document for testing
        // We need a document/page to create annotations
        GError *error = nullptr;
        
        // Create a minimal PDF in memory
        const char *pdf_content = 
            "%PDF-1.4\n"
            "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
            "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
            "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R/Resources<<>>>>endobj\n"
            "xref\n0 4\n"
            "0000000000 65535 f \n"
            "0000000009 00000 n \n"
            "0000000058 00000 n \n"
            "0000000115 00000 n \n"
            "trailer<</Size 4/Root 1 0 R>>\nstartxref\n210\n%%EOF\n";
        
        gsize len = strlen(pdf_content);
        doc = poppler_document_new_from_data(const_cast<char*>(pdf_content), len, nullptr, &error);
        if (doc) {
            page = poppler_document_get_page(doc, 0);
        }
    }

    void TearDown() override {
        if (annot) {
            g_object_unref(annot);
            annot = nullptr;
        }
        if (page) {
            g_object_unref(page);
            page = nullptr;
        }
        if (doc) {
            g_object_unref(doc);
            doc = nullptr;
        }
    }

    PopplerAnnotFreeText* createFreeTextAnnot() {
        if (!page) return nullptr;
        
        PopplerRectangle rect;
        rect.x1 = 100;
        rect.y1 = 100;
        rect.x2 = 300;
        rect.y2 = 200;
        
        annot = poppler_annot_free_text_new(doc, &rect);
        if (annot && POPPLER_IS_ANNOT_FREE_TEXT(annot)) {
            return POPPLER_ANNOT_FREE_TEXT(annot);
        }
        return nullptr;
    }
};

TEST_F(PopplerAnnotFreeTextSetFontDescTest_2100, SetFontDescBasic_2100) {
    PopplerAnnotFreeText *ft_annot = createFreeTextAnnot();
    if (!ft_annot) {
        GTEST_SKIP() << "Could not create free text annotation";
    }

    PopplerFontDescription *fd = poppler_font_description_new();
    poppler_font_description_set_family(fd, "Helvetica");
    poppler_font_description_set_size(fd, 14.0);

    poppler_annot_free_text_set_font_desc(ft_annot, fd);

    PopplerFontDescription *result = poppler_annot_free_text_get_font_desc(ft_annot);
    ASSERT_NE(result, nullptr);
    
    const char *family = poppler_font_description_get_family(result);
    EXPECT_STREQ(family, "Helvetica");
    EXPECT_DOUBLE_EQ(poppler_font_description_get_size(result), 14.0);

    poppler_font_description_free(fd);
    poppler_font_description_free(result);
}

TEST_F(PopplerAnnotFreeTextSetFontDescTest_2100, SetFontDescReplacesExisting_2100) {
    PopplerAnnotFreeText *ft_annot = createFreeTextAnnot();
    if (!ft_annot) {
        GTEST_SKIP() << "Could not create free text annotation";
    }

    PopplerFontDescription *fd1 = poppler_font_description_new();
    poppler_font_description_set_family(fd1, "Courier");
    poppler_font_description_set_size(fd1, 10.0);
    poppler_annot_free_text_set_font_desc(ft_annot, fd1);

    PopplerFontDescription *fd2 = poppler_font_description_new();
    poppler_font_description_set_family(fd2, "Times-Roman");
    poppler_font_description_set_size(fd2, 20.0);
    poppler_annot_free_text_set_font_desc(ft_annot, fd2);

    PopplerFontDescription *result = poppler_annot_free_text_get_font_desc(ft_annot);
    ASSERT_NE(result, nullptr);
    
    const char *family = poppler_font_description_get_family(result);
    EXPECT_STREQ(family, "Times-Roman");
    EXPECT_DOUBLE_EQ(poppler_font_description_get_size(result), 20.0);

    poppler_font_description_free(fd1);
    poppler_font_description_free(fd2);
    poppler_font_description_free(result);
}

TEST_F(PopplerAnnotFreeTextSetFontDescTest_2100, SetFontDescCopiesInput_2100) {
    PopplerAnnotFreeText *ft_annot = createFreeTextAnnot();
    if (!ft_annot) {
        GTEST_SKIP() << "Could not create free text annotation";
    }

    PopplerFontDescription *fd = poppler_font_description_new();
    poppler_font_description_set_family(fd, "Helvetica");
    poppler_font_description_set_size(fd, 12.0);

    poppler_annot_free_text_set_font_desc(ft_annot, fd);

    // Modify the original - the annotation's copy should be unaffected
    poppler_font_description_set_family(fd, "Courier");
    poppler_font_description_set_size(fd, 99.0);

    PopplerFontDescription *result = poppler_annot_free_text_get_font_desc(ft_annot);
    ASSERT_NE(result, nullptr);
    
    const char *family = poppler_font_description_get_family(result);
    EXPECT_STREQ(family, "Helvetica");
    EXPECT_DOUBLE_EQ(poppler_font_description_get_size(result), 12.0);

    poppler_font_description_free(fd);
    poppler_font_description_free(result);
}

TEST_F(PopplerAnnotFreeTextSetFontDescTest_2100, SetFontDescMultipleTimes_2100) {
    PopplerAnnotFreeText *ft_annot = createFreeTextAnnot();
    if (!ft_annot) {
        GTEST_SKIP() << "Could not create free text annotation";
    }

    for (int i = 0; i < 10; i++) {
        PopplerFontDescription *fd = poppler_font_description_new();
        char name[64];
        snprintf(name, sizeof(name), "Font%d", i);
        poppler_font_description_set_family(fd, name);
        poppler_font_description_set_size(fd, (double)(i + 1));

        poppler_annot_free_text_set_font_desc(ft_annot, fd);
        poppler_font_description_free(fd);
    }

    PopplerFontDescription *result = poppler_annot_free_text_get_font_desc(ft_annot);
    ASSERT_NE(result, nullptr);
    
    const char *family = poppler_font_description_get_family(result);
    EXPECT_STREQ(family, "Font9");
    EXPECT_DOUBLE_EQ(poppler_font_description_get_size(result), 10.0);

    poppler_font_description_free(result);
}

TEST_F(PopplerAnnotFreeTextSetFontDescTest_2100, SetFontDescWithSmallSize_2100) {
    PopplerAnnotFreeText *ft_annot = createFreeTextAnnot();
    if (!ft_annot) {
        GTEST_SKIP() << "Could not create free text annotation";
    }

    PopplerFontDescription *fd = poppler_font_description_new();
    poppler_font_description_set_family(fd, "Helvetica");
    poppler_font_description_set_size(fd, 0.5);

    poppler_annot_free_text_set_font_desc(ft_annot, fd);

    PopplerFontDescription *result = poppler_annot_free_text_get_font_desc(ft_annot);
    ASSERT_NE(result, nullptr);
    EXPECT_DOUBLE_EQ(poppler_font_description_get_size(result), 0.5);

    poppler_font_description_free(fd);
    poppler_font_description_free(result);
}

TEST_F(PopplerAnnotFreeTextSetFontDescTest_2100, SetFontDescWithLargeSize_2100) {
    PopplerAnnotFreeText *ft_annot = createFreeTextAnnot();
    if (!ft_annot) {
        GTEST_SKIP() << "Could not create free text annotation";
    }

    PopplerFontDescription *fd = poppler_font_description_new();
    poppler_font_description_set_family(fd, "Helvetica");
    poppler_font_description_set_size(fd, 1000.0);

    poppler_annot_free_text_set_font_desc(ft_annot, fd);

    PopplerFontDescription *result = poppler_annot_free_text_get_font_desc(ft_annot);
    ASSERT_NE(result, nullptr);
    EXPECT_DOUBLE_EQ(poppler_font_description_get_size(result), 1000.0);

    poppler_font_description_free(fd);
    poppler_font_description_free(result);
}

TEST_F(PopplerAnnotFreeTextSetFontDescTest_2100, SetFontDescZeroSize_2100) {
    PopplerAnnotFreeText *ft_annot = createFreeTextAnnot();
    if (!ft_annot) {
        GTEST_SKIP() << "Could not create free text annotation";
    }

    PopplerFontDescription *fd = poppler_font_description_new();
    poppler_font_description_set_family(fd, "Helvetica");
    poppler_font_description_set_size(fd, 0.0);

    poppler_annot_free_text_set_font_desc(ft_annot, fd);

    PopplerFontDescription *result = poppler_annot_free_text_get_font_desc(ft_annot);
    ASSERT_NE(result, nullptr);
    EXPECT_DOUBLE_EQ(poppler_font_description_get_size(result), 0.0);

    poppler_font_description_free(fd);
    poppler_font_description_free(result);
}
