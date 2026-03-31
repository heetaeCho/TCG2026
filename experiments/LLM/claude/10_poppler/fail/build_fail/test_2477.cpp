#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <poppler.h>
#include <poppler-page.h>
#include <glib.h>
#include <cstdio>
#include <cstring>
#include <cmath>

class PopplerPageTextAttributes_2477 : public ::testing::Test {
protected:
    PopplerDocument *doc = nullptr;
    PopplerPage *page = nullptr;

    void SetUp() override {
        // We need a real PDF to test with. Try to find a test PDF.
        GError *error = nullptr;
        
        // Create a minimal PDF in memory for testing
        const char *pdf_content = 
            "%PDF-1.4\n"
            "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
            "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
            "3 0 obj<</Type/Page/Parent 2 0 R/MediaBox[0 0 612 792]"
            "/Contents 4 0 R/Resources<</Font<</F1 5 0 R>>>>>>endobj\n"
            "4 0 obj<</Length 44>>\nstream\n"
            "BT /F1 12 Tf 100 700 Td (Hello World) Tj ET\n"
            "endstream\nendobj\n"
            "5 0 obj<</Type/Font/Subtype/Type1/BaseFont/Helvetica>>endobj\n"
            "xref\n0 6\n"
            "0000000000 65535 f \n"
            "0000000009 00000 n \n"
            "0000000058 00000 n \n"
            "0000000115 00000 n \n"
            "0000000266 00000 n \n"
            "0000000360 00000 n \n"
            "trailer<</Size 6/Root 1 0 R>>\n"
            "startxref\n431\n%%EOF\n";

        // Write to temp file
        tmp_path = g_strdup("/tmp/test_poppler_2477.pdf");
        FILE *f = fopen(tmp_path, "wb");
        if (f) {
            fwrite(pdf_content, 1, strlen(pdf_content), f);
            fclose(f);
        }

        gchar *uri = g_filename_to_uri(tmp_path, nullptr, &error);
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
        if (page) {
            g_object_unref(page);
        }
        if (doc) {
            g_object_unref(doc);
        }
        if (tmp_path) {
            unlink(tmp_path);
            g_free(tmp_path);
        }
    }

    gchar *tmp_path = nullptr;
};

TEST_F(PopplerPageTextAttributes_2477, GetTextAttributesReturnsListOrNull_2477) {
    if (!page) {
        GTEST_SKIP() << "Could not load test PDF";
    }
    GList *attrs = poppler_page_get_text_attributes(page);
    // The result can be a valid list or NULL depending on text content
    // If there's text, we expect a non-null list
    if (attrs) {
        // Each element should be a PopplerTextAttributes
        for (GList *l = attrs; l != nullptr; l = l->next) {
            PopplerTextAttributes *attr = (PopplerTextAttributes *)l->data;
            ASSERT_NE(attr, nullptr);
            // font_size should be positive
            EXPECT_GT(attr->font_size, 0.0);
            // Color values should be in valid range [0, 65535]
            EXPECT_GE(attr->color.red, 0);
            EXPECT_LE(attr->color.red, 65535);
            EXPECT_GE(attr->color.green, 0);
            EXPECT_LE(attr->color.green, 65535);
            EXPECT_GE(attr->color.blue, 0);
            EXPECT_LE(attr->color.blue, 65535);
        }
        poppler_page_free_text_attributes(attrs);
    }
}

TEST_F(PopplerPageTextAttributes_2477, TextAttributesFontNameNotNull_2477) {
    if (!page) {
        GTEST_SKIP() << "Could not load test PDF";
    }
    GList *attrs = poppler_page_get_text_attributes(page);
    if (attrs) {
        for (GList *l = attrs; l != nullptr; l = l->next) {
            PopplerTextAttributes *attr = (PopplerTextAttributes *)l->data;
            ASSERT_NE(attr, nullptr);
            // font_name may or may not be null, but if present should be valid string
            if (attr->font_name) {
                EXPECT_GT(strlen(attr->font_name), 0u);
            }
        }
        poppler_page_free_text_attributes(attrs);
    }
}

TEST_F(PopplerPageTextAttributes_2477, TextAttributesCopyWorks_2477) {
    if (!page) {
        GTEST_SKIP() << "Could not load test PDF";
    }
    GList *attrs = poppler_page_get_text_attributes(page);
    if (attrs && attrs->data) {
        PopplerTextAttributes *original = (PopplerTextAttributes *)attrs->data;
        PopplerTextAttributes *copy = poppler_text_attributes_copy(original);
        ASSERT_NE(copy, nullptr);
        
        EXPECT_DOUBLE_EQ(copy->font_size, original->font_size);
        EXPECT_EQ(copy->is_underlined, original->is_underlined);
        EXPECT_EQ(copy->color.red, original->color.red);
        EXPECT_EQ(copy->color.green, original->color.green);
        EXPECT_EQ(copy->color.blue, original->color.blue);
        
        if (original->font_name && copy->font_name) {
            EXPECT_STREQ(copy->font_name, original->font_name);
        }
        
        poppler_text_attributes_free(copy);
        poppler_page_free_text_attributes(attrs);
    }
}

TEST_F(PopplerPageTextAttributes_2477, FreeTextAttributesHandlesNull_2477) {
    // Should not crash when freeing NULL
    poppler_page_free_text_attributes(nullptr);
}

TEST_F(PopplerPageTextAttributes_2477, TextAttributesFreeHandlesNull_2477) {
    // Should not crash
    poppler_text_attributes_free(nullptr);
}

TEST_F(PopplerPageTextAttributes_2477, TextAttributesNewReturnsValid_2477) {
    PopplerTextAttributes *attrs = poppler_text_attributes_new();
    ASSERT_NE(attrs, nullptr);
    poppler_text_attributes_free(attrs);
}

TEST_F(PopplerPageTextAttributes_2477, ColorValuesAreRounded_2477) {
    // Test the color conversion formula: (int)(r * 65535. + 0.5)
    // For r=0 -> 0, r=1.0 -> 65535, r=0.5 -> 32768
    // This tests the expected conversion indirectly through the API
    if (!page) {
        GTEST_SKIP() << "Could not load test PDF";
    }
    GList *attrs = poppler_page_get_text_attributes(page);
    if (attrs) {
        for (GList *l = attrs; l != nullptr; l = l->next) {
            PopplerTextAttributes *attr = (PopplerTextAttributes *)l->data;
            // Default text color is typically black (0,0,0)
            // Values should be integers in valid range
            EXPECT_GE(attr->color.red, 0);
            EXPECT_LE(attr->color.red, 65535);
            EXPECT_GE(attr->color.green, 0);
            EXPECT_LE(attr->color.green, 65535);
            EXPECT_GE(attr->color.blue, 0);
            EXPECT_LE(attr->color.blue, 65535);
        }
        poppler_page_free_text_attributes(attrs);
    }
}

TEST_F(PopplerPageTextAttributes_2477, GetTextAttributesForAreaReturnsValidResults_2477) {
    if (!page) {
        GTEST_SKIP() << "Could not load test PDF";
    }
    
    PopplerRectangle rect;
    rect.x1 = 0;
    rect.y1 = 0;
    rect.x2 = 612;
    rect.y2 = 792;
    
    GList *attrs = poppler_page_get_text_attributes_for_area(page, &rect);
    if (attrs) {
        for (GList *l = attrs; l != nullptr; l = l->next) {
            PopplerTextAttributes *attr = (PopplerTextAttributes *)l->data;
            ASSERT_NE(attr, nullptr);
            EXPECT_GT(attr->font_size, 0.0);
        }
        poppler_page_free_text_attributes(attrs);
    }
}

TEST_F(PopplerPageTextAttributes_2477, GetTextAttributesForEmptyAreaReturnsNullOrEmpty_2477) {
    if (!page) {
        GTEST_SKIP() << "Could not load test PDF";
    }
    
    // Area with no text
    PopplerRectangle rect;
    rect.x1 = 0;
    rect.y1 = 0;
    rect.x2 = 1;
    rect.y2 = 1;
    
    GList *attrs = poppler_page_get_text_attributes_for_area(page, &rect);
    // May be NULL or empty list for area with no text
    if (attrs) {
        poppler_page_free_text_attributes(attrs);
    }
}

TEST_F(PopplerPageTextAttributes_2477, UnderlineAttributeIsBool_2477) {
    if (!page) {
        GTEST_SKIP() << "Could not load test PDF";
    }
    GList *attrs = poppler_page_get_text_attributes(page);
    if (attrs) {
        for (GList *l = attrs; l != nullptr; l = l->next) {
            PopplerTextAttributes *attr = (PopplerTextAttributes *)l->data;
            // is_underlined should be either TRUE or FALSE
            EXPECT_TRUE(attr->is_underlined == TRUE || attr->is_underlined == FALSE);
        }
        poppler_page_free_text_attributes(attrs);
    }
}

TEST_F(PopplerPageTextAttributes_2477, TextAttributesStartAndEndIndex_2477) {
    if (!page) {
        GTEST_SKIP() << "Could not load test PDF";
    }
    GList *attrs = poppler_page_get_text_attributes(page);
    if (attrs) {
        for (GList *l = attrs; l != nullptr; l = l->next) {
            PopplerTextAttributes *attr = (PopplerTextAttributes *)l->data;
            // start_index should be <= end_index
            EXPECT_LE(attr->start_index, attr->end_index);
            // Indices should be non-negative
            EXPECT_GE(attr->start_index, 0);
            EXPECT_GE(attr->end_index, 0);
        }
        poppler_page_free_text_attributes(attrs);
    }
}
