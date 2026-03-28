#include <glib-object.h>
#include <gtest/gtest.h>

// Include poppler glib headers
extern "C" {
#include "poppler-annot.h"
#include "poppler-document.h"
#include "poppler-page.h"
}

class PopplerAnnotCircleSetInteriorColorTest_2116 : public ::testing::Test {
protected:
    void SetUp() override {
        // We need a real PopplerAnnotCircle to test with.
        // Since creating one requires a PDF document context in most cases,
        // we'll try to create a minimal document with an annotation.
        GError *error = nullptr;
        
        // Create a minimal PDF in memory
        const char *minimal_pdf = 
            "%PDF-1.4\n"
            "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
            "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
            "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R/Annots[4 0 R]>>endobj\n"
            "4 0 obj<</Type/Annot/Subtype/Circle/Rect[100 100 200 200]/IC[1.0 0.0 0.0]>>endobj\n"
            "xref\n"
            "0 5\n"
            "0000000000 65535 f \n"
            "0000000009 00000 n \n"
            "0000000058 00000 n \n"
            "0000000115 00000 n \n"
            "0000000206 00000 n \n"
            "trailer<</Size 5/Root 1 0 R>>\n"
            "startxref\n"
            "302\n"
            "%%EOF\n";
        
        gsize len = strlen(minimal_pdf);
        doc = poppler_document_new_from_data((char*)minimal_pdf, (int)len, nullptr, &error);
        
        if (doc == nullptr) {
            if (error) {
                g_error_free(error);
            }
            annot_circle = nullptr;
            page = nullptr;
            return;
        }
        
        page = poppler_document_get_page(doc, 0);
        if (page == nullptr) {
            annot_circle = nullptr;
            return;
        }
        
        GList *annot_mapping_list = poppler_page_get_annot_mapping(page);
        if (annot_mapping_list != nullptr) {
            PopplerAnnotMapping *mapping = (PopplerAnnotMapping *)annot_mapping_list->data;
            if (mapping && mapping->annot && POPPLER_IS_ANNOT_CIRCLE(mapping->annot)) {
                annot_circle = POPPLER_ANNOT_CIRCLE(g_object_ref(mapping->annot));
            } else {
                annot_circle = nullptr;
            }
            poppler_page_free_annot_mapping(annot_mapping_list);
        } else {
            annot_circle = nullptr;
        }
    }
    
    void TearDown() override {
        if (annot_circle) {
            g_object_unref(annot_circle);
        }
        if (page) {
            g_object_unref(page);
        }
        if (doc) {
            g_object_unref(doc);
        }
    }
    
    PopplerDocument *doc = nullptr;
    PopplerPage *page = nullptr;
    PopplerAnnotCircle *annot_circle = nullptr;
};

// Test setting interior color with a valid color
TEST_F(PopplerAnnotCircleSetInteriorColorTest_2116, SetInteriorColorValid_2116) {
    if (!annot_circle) {
        GTEST_SKIP() << "Could not create PopplerAnnotCircle from minimal PDF";
    }
    
    PopplerColor color;
    color.red = 65535;
    color.green = 0;
    color.blue = 0;
    
    // Should not crash or assert
    poppler_annot_circle_set_interior_color(annot_circle, &color);
    
    // Verify by getting the interior color back
    PopplerColor *retrieved_color = poppler_annot_circle_get_interior_color(annot_circle);
    ASSERT_NE(retrieved_color, nullptr);
    EXPECT_EQ(retrieved_color->red, 65535);
    EXPECT_EQ(retrieved_color->green, 0);
    EXPECT_EQ(retrieved_color->blue, 0);
    g_free(retrieved_color);
}

// Test setting interior color with nullptr color (should clear the color)
TEST_F(PopplerAnnotCircleSetInteriorColorTest_2116, SetInteriorColorNull_2116) {
    if (!annot_circle) {
        GTEST_SKIP() << "Could not create PopplerAnnotCircle from minimal PDF";
    }
    
    // Setting NULL color should clear the interior color
    poppler_annot_circle_set_interior_color(annot_circle, nullptr);
    
    PopplerColor *retrieved_color = poppler_annot_circle_get_interior_color(annot_circle);
    // When cleared, should return nullptr
    EXPECT_EQ(retrieved_color, nullptr);
    if (retrieved_color) {
        g_free(retrieved_color);
    }
}

// Test setting interior color with green color
TEST_F(PopplerAnnotCircleSetInteriorColorTest_2116, SetInteriorColorGreen_2116) {
    if (!annot_circle) {
        GTEST_SKIP() << "Could not create PopplerAnnotCircle from minimal PDF";
    }
    
    PopplerColor color;
    color.red = 0;
    color.green = 65535;
    color.blue = 0;
    
    poppler_annot_circle_set_interior_color(annot_circle, &color);
    
    PopplerColor *retrieved_color = poppler_annot_circle_get_interior_color(annot_circle);
    ASSERT_NE(retrieved_color, nullptr);
    EXPECT_EQ(retrieved_color->red, 0);
    EXPECT_EQ(retrieved_color->green, 65535);
    EXPECT_EQ(retrieved_color->blue, 0);
    g_free(retrieved_color);
}

// Test setting interior color with blue color
TEST_F(PopplerAnnotCircleSetInteriorColorTest_2116, SetInteriorColorBlue_2116) {
    if (!annot_circle) {
        GTEST_SKIP() << "Could not create PopplerAnnotCircle from minimal PDF";
    }
    
    PopplerColor color;
    color.red = 0;
    color.green = 0;
    color.blue = 65535;
    
    poppler_annot_circle_set_interior_color(annot_circle, &color);
    
    PopplerColor *retrieved_color = poppler_annot_circle_get_interior_color(annot_circle);
    ASSERT_NE(retrieved_color, nullptr);
    EXPECT_EQ(retrieved_color->red, 0);
    EXPECT_EQ(retrieved_color->green, 0);
    EXPECT_EQ(retrieved_color->blue, 65535);
    g_free(retrieved_color);
}

// Test setting interior color with all zeros (black)
TEST_F(PopplerAnnotCircleSetInteriorColorTest_2116, SetInteriorColorBlack_2116) {
    if (!annot_circle) {
        GTEST_SKIP() << "Could not create PopplerAnnotCircle from minimal PDF";
    }
    
    PopplerColor color;
    color.red = 0;
    color.green = 0;
    color.blue = 0;
    
    poppler_annot_circle_set_interior_color(annot_circle, &color);
    
    PopplerColor *retrieved_color = poppler_annot_circle_get_interior_color(annot_circle);
    ASSERT_NE(retrieved_color, nullptr);
    EXPECT_EQ(retrieved_color->red, 0);
    EXPECT_EQ(retrieved_color->green, 0);
    EXPECT_EQ(retrieved_color->blue, 0);
    g_free(retrieved_color);
}

// Test setting interior color with max values (white)
TEST_F(PopplerAnnotCircleSetInteriorColorTest_2116, SetInteriorColorWhite_2116) {
    if (!annot_circle) {
        GTEST_SKIP() << "Could not create PopplerAnnotCircle from minimal PDF";
    }
    
    PopplerColor color;
    color.red = 65535;
    color.green = 65535;
    color.blue = 65535;
    
    poppler_annot_circle_set_interior_color(annot_circle, &color);
    
    PopplerColor *retrieved_color = poppler_annot_circle_get_interior_color(annot_circle);
    ASSERT_NE(retrieved_color, nullptr);
    EXPECT_EQ(retrieved_color->red, 65535);
    EXPECT_EQ(retrieved_color->green, 65535);
    EXPECT_EQ(retrieved_color->blue, 65535);
    g_free(retrieved_color);
}

// Test overwriting an existing interior color
TEST_F(PopplerAnnotCircleSetInteriorColorTest_2116, OverwriteInteriorColor_2116) {
    if (!annot_circle) {
        GTEST_SKIP() << "Could not create PopplerAnnotCircle from minimal PDF";
    }
    
    PopplerColor color1;
    color1.red = 65535;
    color1.green = 0;
    color1.blue = 0;
    poppler_annot_circle_set_interior_color(annot_circle, &color1);
    
    PopplerColor color2;
    color2.red = 0;
    color2.green = 32768;
    color2.blue = 65535;
    poppler_annot_circle_set_interior_color(annot_circle, &color2);
    
    PopplerColor *retrieved_color = poppler_annot_circle_get_interior_color(annot_circle);
    ASSERT_NE(retrieved_color, nullptr);
    EXPECT_EQ(retrieved_color->red, 0);
    EXPECT_EQ(retrieved_color->green, 32768);
    EXPECT_EQ(retrieved_color->blue, 65535);
    g_free(retrieved_color);
}

// Test that passing a non-PopplerAnnotCircle object triggers g_return_if_fail
// This test verifies the guard clause behavior with an invalid type
TEST_F(PopplerAnnotCircleSetInteriorColorTest_2116, InvalidAnnotTypeHandledGracefully_2116) {
    // Passing NULL as the annot should trigger g_return_if_fail and not crash
    // GLib critical warnings will be emitted but function should return safely
    if (g_test_undefined()) {
        // Expect a critical warning but no crash
        g_test_expect_message("Poppler", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_ANNOT_CIRCLE*");
        PopplerColor color;
        color.red = 100;
        color.green = 200;
        color.blue = 300;
        poppler_annot_circle_set_interior_color(nullptr, &color);
        g_test_assert_expected_messages();
    }
}

// Test setting color then clearing with nullptr
TEST_F(PopplerAnnotCircleSetInteriorColorTest_2116, SetThenClearInteriorColor_2116) {
    if (!annot_circle) {
        GTEST_SKIP() << "Could not create PopplerAnnotCircle from minimal PDF";
    }
    
    PopplerColor color;
    color.red = 12345;
    color.green = 23456;
    color.blue = 34567;
    poppler_annot_circle_set_interior_color(annot_circle, &color);
    
    // Verify it was set
    PopplerColor *retrieved_color = poppler_annot_circle_get_interior_color(annot_circle);
    ASSERT_NE(retrieved_color, nullptr);
    g_free(retrieved_color);
    
    // Now clear
    poppler_annot_circle_set_interior_color(annot_circle, nullptr);
    
    retrieved_color = poppler_annot_circle_get_interior_color(annot_circle);
    EXPECT_EQ(retrieved_color, nullptr);
    if (retrieved_color) {
        g_free(retrieved_color);
    }
}

// Test with mid-range color values
TEST_F(PopplerAnnotCircleSetInteriorColorTest_2116, SetInteriorColorMidRange_2116) {
    if (!annot_circle) {
        GTEST_SKIP() << "Could not create PopplerAnnotCircle from minimal PDF";
    }
    
    PopplerColor color;
    color.red = 32768;
    color.green = 32768;
    color.blue = 32768;
    
    poppler_annot_circle_set_interior_color(annot_circle, &color);
    
    PopplerColor *retrieved_color = poppler_annot_circle_get_interior_color(annot_circle);
    ASSERT_NE(retrieved_color, nullptr);
    EXPECT_EQ(retrieved_color->red, 32768);
    EXPECT_EQ(retrieved_color->green, 32768);
    EXPECT_EQ(retrieved_color->blue, 32768);
    g_free(retrieved_color);
}
