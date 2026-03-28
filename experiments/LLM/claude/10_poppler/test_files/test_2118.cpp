#include <glib-object.h>
#include <gtest/gtest.h>

// Include poppler glib headers
#include "poppler-annot.h"
#include "poppler-page.h"
#include "poppler-document.h"

class PopplerAnnotSquareSetInteriorColorTest_2118 : public ::testing::Test {
protected:
    PopplerDocument *doc = nullptr;
    PopplerPage *page = nullptr;
    PopplerAnnot *annot = nullptr;

    void SetUp() override {
        // Create a minimal PDF document in memory to work with
        // We need a valid PopplerAnnotSquare object
        GError *error = nullptr;
        
        // Try to create a document from a minimal PDF
        const char *pdf_path = g_getenv("TEST_PDF_PATH");
        if (pdf_path) {
            gchar *uri = g_filename_to_uri(pdf_path, nullptr, &error);
            if (uri) {
                doc = poppler_document_new_from_file(uri, nullptr, &error);
                g_free(uri);
            }
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

    PopplerAnnotSquare *createSquareAnnot() {
        if (!page && doc) {
            page = poppler_document_get_page(doc, 0);
        }
        // Create a square annotation using the poppler API
        PopplerRectangle rect;
        rect.x1 = 10.0;
        rect.y1 = 10.0;
        rect.x2 = 100.0;
        rect.y2 = 100.0;

        PopplerColor color;
        color.red = 65535;
        color.green = 0;
        color.blue = 0;

        PopplerAnnotSquare *square = POPPLER_ANNOT_SQUARE(poppler_annot_square_new(doc, &rect));
        return square;
    }
};

// Test that passing NULL annot doesn't crash (g_return_if_fail should handle it)
TEST_F(PopplerAnnotSquareSetInteriorColorTest_2118, NullAnnotDoesNotCrash_2118) {
    PopplerColor color;
    color.red = 100;
    color.green = 200;
    color.blue = 300;
    
    // Should not crash due to g_return_if_fail
    poppler_annot_square_set_interior_color(nullptr, &color);
}

// Test that passing NULL color is accepted (clearing interior color)
TEST_F(PopplerAnnotSquareSetInteriorColorTest_2118, NullColorClearsInteriorColor_2118) {
    if (!doc) {
        GTEST_SKIP() << "No test PDF available; set TEST_PDF_PATH env var";
    }
    
    PopplerAnnotSquare *square = createSquareAnnot();
    ASSERT_NE(square, nullptr);
    
    // Set a color first
    PopplerColor color;
    color.red = 65535;
    color.green = 0;
    color.blue = 0;
    poppler_annot_square_set_interior_color(square, &color);
    
    // Now set NULL to clear it
    poppler_annot_square_set_interior_color(square, nullptr);
    
    // Verify interior color was cleared
    PopplerColor *retrieved = poppler_annot_square_get_interior_color(square);
    EXPECT_EQ(retrieved, nullptr);
    
    g_object_unref(square);
}

// Test setting a valid interior color
TEST_F(PopplerAnnotSquareSetInteriorColorTest_2118, SetValidInteriorColor_2118) {
    if (!doc) {
        GTEST_SKIP() << "No test PDF available; set TEST_PDF_PATH env var";
    }
    
    PopplerAnnotSquare *square = createSquareAnnot();
    ASSERT_NE(square, nullptr);
    
    PopplerColor color;
    color.red = 65535;
    color.green = 32768;
    color.blue = 0;
    
    poppler_annot_square_set_interior_color(square, &color);
    
    PopplerColor *retrieved = poppler_annot_square_get_interior_color(square);
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->red, 65535);
    EXPECT_EQ(retrieved->green, 32768);
    EXPECT_EQ(retrieved->blue, 0);
    
    g_free(retrieved);
    g_object_unref(square);
}

// Test setting interior color with all zeros (black)
TEST_F(PopplerAnnotSquareSetInteriorColorTest_2118, SetBlackInteriorColor_2118) {
    if (!doc) {
        GTEST_SKIP() << "No test PDF available; set TEST_PDF_PATH env var";
    }
    
    PopplerAnnotSquare *square = createSquareAnnot();
    ASSERT_NE(square, nullptr);
    
    PopplerColor color;
    color.red = 0;
    color.green = 0;
    color.blue = 0;
    
    poppler_annot_square_set_interior_color(square, &color);
    
    PopplerColor *retrieved = poppler_annot_square_get_interior_color(square);
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->red, 0);
    EXPECT_EQ(retrieved->green, 0);
    EXPECT_EQ(retrieved->blue, 0);
    
    g_free(retrieved);
    g_object_unref(square);
}

// Test setting interior color with max values (white)
TEST_F(PopplerAnnotSquareSetInteriorColorTest_2118, SetWhiteInteriorColor_2118) {
    if (!doc) {
        GTEST_SKIP() << "No test PDF available; set TEST_PDF_PATH env var";
    }
    
    PopplerAnnotSquare *square = createSquareAnnot();
    ASSERT_NE(square, nullptr);
    
    PopplerColor color;
    color.red = 65535;
    color.green = 65535;
    color.blue = 65535;
    
    poppler_annot_square_set_interior_color(square, &color);
    
    PopplerColor *retrieved = poppler_annot_square_get_interior_color(square);
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->red, 65535);
    EXPECT_EQ(retrieved->green, 65535);
    EXPECT_EQ(retrieved->blue, 65535);
    
    g_free(retrieved);
    g_object_unref(square);
}

// Test overwriting an existing interior color
TEST_F(PopplerAnnotSquareSetInteriorColorTest_2118, OverwriteInteriorColor_2118) {
    if (!doc) {
        GTEST_SKIP() << "No test PDF available; set TEST_PDF_PATH env var";
    }
    
    PopplerAnnotSquare *square = createSquareAnnot();
    ASSERT_NE(square, nullptr);
    
    PopplerColor color1;
    color1.red = 65535;
    color1.green = 0;
    color1.blue = 0;
    poppler_annot_square_set_interior_color(square, &color1);
    
    PopplerColor color2;
    color2.red = 0;
    color2.green = 65535;
    color2.blue = 0;
    poppler_annot_square_set_interior_color(square, &color2);
    
    PopplerColor *retrieved = poppler_annot_square_get_interior_color(square);
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->red, 0);
    EXPECT_EQ(retrieved->green, 65535);
    EXPECT_EQ(retrieved->blue, 0);
    
    g_free(retrieved);
    g_object_unref(square);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
