#include <gtest/gtest.h>
#include <poppler.h>
#include <poppler-document.h>
#include <poppler-page.h>
#include <cstring>
#include <cstdio>
#include <glib.h>

extern "C" {
#include "poppler-annot.h"
}

class PopplerAnnotMarkupOpacityTest_2084 : public ::testing::Test {
protected:
    PopplerDocument *doc = nullptr;
    PopplerPage *page = nullptr;
    PopplerAnnotMarkup *markup_annot = nullptr;
    PopplerAnnot *annot_base = nullptr;

    void SetUp() override {
        // Try to create a simple PDF document for testing
        // We need a real document to create annotations
        GError *error = nullptr;
        
        // Create a minimal PDF in memory
        const char *pdf_data =
            "%PDF-1.4\n"
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

        gsize len = strlen(pdf_data);
        doc = poppler_document_new_from_data((char*)pdf_data, (int)len, nullptr, &error);
        
        if (doc) {
            page = poppler_document_get_page(doc, 0);
        }
    }

    PopplerAnnot* createTextAnnot() {
        if (!page) return nullptr;
        
        PopplerRectangle rect;
        rect.x1 = 10;
        rect.y1 = 10;
        rect.x2 = 100;
        rect.y2 = 100;
        
        // PopplerAnnotText is a markup annotation
        PopplerAnnot *annot = poppler_annot_text_new(doc, &rect);
        return annot;
    }

    void TearDown() override {
        if (annot_base) {
            g_object_unref(annot_base);
            annot_base = nullptr;
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
};

// Test setting opacity to a normal value
TEST_F(PopplerAnnotMarkupOpacityTest_2084, SetOpacityNormalValue_2084) {
    annot_base = createTextAnnot();
    if (!annot_base) {
        GTEST_SKIP() << "Could not create annotation";
    }
    
    ASSERT_TRUE(POPPLER_IS_ANNOT_MARKUP(annot_base));
    PopplerAnnotMarkup *markup = POPPLER_ANNOT_MARKUP(annot_base);
    
    poppler_annot_markup_set_opacity(markup, 0.5);
    gdouble result = poppler_annot_markup_get_opacity(markup);
    EXPECT_DOUBLE_EQ(result, 0.5);
}

// Test setting opacity to 1.0 (fully opaque)
TEST_F(PopplerAnnotMarkupOpacityTest_2084, SetOpacityFullyOpaque_2084) {
    annot_base = createTextAnnot();
    if (!annot_base) {
        GTEST_SKIP() << "Could not create annotation";
    }
    
    ASSERT_TRUE(POPPLER_IS_ANNOT_MARKUP(annot_base));
    PopplerAnnotMarkup *markup = POPPLER_ANNOT_MARKUP(annot_base);
    
    poppler_annot_markup_set_opacity(markup, 1.0);
    gdouble result = poppler_annot_markup_get_opacity(markup);
    EXPECT_DOUBLE_EQ(result, 1.0);
}

// Test setting opacity to 0.0 (fully transparent)
TEST_F(PopplerAnnotMarkupOpacityTest_2084, SetOpacityFullyTransparent_2084) {
    annot_base = createTextAnnot();
    if (!annot_base) {
        GTEST_SKIP() << "Could not create annotation";
    }
    
    ASSERT_TRUE(POPPLER_IS_ANNOT_MARKUP(annot_base));
    PopplerAnnotMarkup *markup = POPPLER_ANNOT_MARKUP(annot_base);
    
    poppler_annot_markup_set_opacity(markup, 0.0);
    gdouble result = poppler_annot_markup_get_opacity(markup);
    EXPECT_DOUBLE_EQ(result, 0.0);
}

// Test setting opacity to a small positive value
TEST_F(PopplerAnnotMarkupOpacityTest_2084, SetOpacitySmallValue_2084) {
    annot_base = createTextAnnot();
    if (!annot_base) {
        GTEST_SKIP() << "Could not create annotation";
    }
    
    ASSERT_TRUE(POPPLER_IS_ANNOT_MARKUP(annot_base));
    PopplerAnnotMarkup *markup = POPPLER_ANNOT_MARKUP(annot_base);
    
    poppler_annot_markup_set_opacity(markup, 0.01);
    gdouble result = poppler_annot_markup_get_opacity(markup);
    EXPECT_DOUBLE_EQ(result, 0.01);
}

// Test setting opacity multiple times (last value should persist)
TEST_F(PopplerAnnotMarkupOpacityTest_2084, SetOpacityMultipleTimes_2084) {
    annot_base = createTextAnnot();
    if (!annot_base) {
        GTEST_SKIP() << "Could not create annotation";
    }
    
    ASSERT_TRUE(POPPLER_IS_ANNOT_MARKUP(annot_base));
    PopplerAnnotMarkup *markup = POPPLER_ANNOT_MARKUP(annot_base);
    
    poppler_annot_markup_set_opacity(markup, 0.2);
    poppler_annot_markup_set_opacity(markup, 0.7);
    poppler_annot_markup_set_opacity(markup, 0.9);
    
    gdouble result = poppler_annot_markup_get_opacity(markup);
    EXPECT_DOUBLE_EQ(result, 0.9);
}

// Test setting opacity to boundary value just below 1.0
TEST_F(PopplerAnnotMarkupOpacityTest_2084, SetOpacityNearOne_2084) {
    annot_base = createTextAnnot();
    if (!annot_base) {
        GTEST_SKIP() << "Could not create annotation";
    }
    
    ASSERT_TRUE(POPPLER_IS_ANNOT_MARKUP(annot_base));
    PopplerAnnotMarkup *markup = POPPLER_ANNOT_MARKUP(annot_base);
    
    poppler_annot_markup_set_opacity(markup, 0.999);
    gdouble result = poppler_annot_markup_get_opacity(markup);
    EXPECT_DOUBLE_EQ(result, 0.999);
}

// Test passing NULL as the annotation (should not crash due to g_return_if_fail)
TEST_F(PopplerAnnotMarkupOpacityTest_2084, SetOpacityNullAnnot_2084) {
    // g_return_if_fail should handle NULL gracefully without crashing
    poppler_annot_markup_set_opacity(nullptr, 0.5);
    // If we reach here, the function handled NULL correctly
    SUCCEED();
}

// Test setting opacity to 0.25
TEST_F(PopplerAnnotMarkupOpacityTest_2084, SetOpacityQuarter_2084) {
    annot_base = createTextAnnot();
    if (!annot_base) {
        GTEST_SKIP() << "Could not create annotation";
    }
    
    ASSERT_TRUE(POPPLER_IS_ANNOT_MARKUP(annot_base));
    PopplerAnnotMarkup *markup = POPPLER_ANNOT_MARKUP(annot_base);
    
    poppler_annot_markup_set_opacity(markup, 0.25);
    gdouble result = poppler_annot_markup_get_opacity(markup);
    EXPECT_DOUBLE_EQ(result, 0.25);
}

// Test setting opacity to 0.75
TEST_F(PopplerAnnotMarkupOpacityTest_2084, SetOpacityThreeQuarters_2084) {
    annot_base = createTextAnnot();
    if (!annot_base) {
        GTEST_SKIP() << "Could not create annotation";
    }
    
    ASSERT_TRUE(POPPLER_IS_ANNOT_MARKUP(annot_base));
    PopplerAnnotMarkup *markup = POPPLER_ANNOT_MARKUP(annot_base);
    
    poppler_annot_markup_set_opacity(markup, 0.75);
    gdouble result = poppler_annot_markup_get_opacity(markup);
    EXPECT_DOUBLE_EQ(result, 0.75);
}

// Test that setting and getting opacity are consistent for various values
TEST_F(PopplerAnnotMarkupOpacityTest_2084, SetOpacityConsistency_2084) {
    annot_base = createTextAnnot();
    if (!annot_base) {
        GTEST_SKIP() << "Could not create annotation";
    }
    
    ASSERT_TRUE(POPPLER_IS_ANNOT_MARKUP(annot_base));
    PopplerAnnotMarkup *markup = POPPLER_ANNOT_MARKUP(annot_base);
    
    double values[] = {0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0};
    for (double val : values) {
        poppler_annot_markup_set_opacity(markup, val);
        gdouble result = poppler_annot_markup_get_opacity(markup);
        EXPECT_DOUBLE_EQ(result, val) << "Failed for opacity value: " << val;
    }
}
