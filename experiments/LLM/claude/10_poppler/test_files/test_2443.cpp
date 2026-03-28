#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <glib-object.h>

// Include necessary headers
extern "C" {
#include "poppler.h"
#include "poppler-page.h"
}

#include "poppler-private.h"

// Helper to create a PopplerDocument from a PDF file for testing
class PopplerPageGetSelectedTextTest_2443 : public ::testing::Test {
protected:
    PopplerDocument *doc = nullptr;
    PopplerPage *page = nullptr;

    void SetUp() override {
        // Try to load a simple test PDF. We'll create one in memory if possible,
        // or use a known test file path.
        GError *error = nullptr;
        
        // Try to find a test PDF - use a simple one-page PDF
        // We'll generate a minimal PDF in memory
        const char *minimal_pdf =
            "%PDF-1.0\n"
            "1 0 obj\n"
            "<< /Type /Catalog /Pages 2 0 R >>\n"
            "endobj\n"
            "2 0 obj\n"
            "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
            "endobj\n"
            "3 0 obj\n"
            "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] "
            "/Contents 4 0 R /Resources << /Font << /F1 5 0 R >> >> >>\n"
            "endobj\n"
            "4 0 obj\n"
            "<< /Length 44 >>\n"
            "stream\n"
            "BT /F1 12 Tf 100 700 Td (Hello World) Tj ET\n"
            "endstream\n"
            "endobj\n"
            "5 0 obj\n"
            "<< /Type /Font /Subtype /Type1 /BaseFont /Helvetica >>\n"
            "endobj\n"
            "xref\n"
            "0 6\n"
            "0000000000 65535 f \n"
            "0000000009 00000 n \n"
            "0000000058 00000 n \n"
            "0000000115 00000 n \n"
            "0000000266 00000 n \n"
            "0000000360 00000 n \n"
            "trailer\n"
            "<< /Size 6 /Root 1 0 R >>\n"
            "startxref\n"
            "441\n"
            "%%EOF\n";

        gsize len = strlen(minimal_pdf);
        GBytes *bytes = g_bytes_new(minimal_pdf, len);
        GInputStream *stream = g_memory_input_stream_new_from_bytes(bytes);
        
        doc = poppler_document_new_from_stream(stream, len, nullptr, nullptr, &error);
        
        if (doc == nullptr && error != nullptr) {
            g_error_free(error);
            error = nullptr;
            // Try alternative approach - create from data
            doc = poppler_document_new_from_data((char*)minimal_pdf, len, nullptr, &error);
        }

        if (doc != nullptr) {
            page = poppler_document_get_page(doc, 0);
        }

        g_object_unref(stream);
        g_bytes_unref(bytes);
    }

    void TearDown() override {
        if (page) {
            g_object_unref(page);
        }
        if (doc) {
            g_object_unref(doc);
        }
    }
};

// Test that passing NULL page returns NULL (g_return_val_if_fail check)
TEST_F(PopplerPageGetSelectedTextTest_2443, NullPageReturnsNull_2443) {
    PopplerRectangle rect;
    rect.x1 = 0;
    rect.y1 = 0;
    rect.x2 = 100;
    rect.y2 = 100;
    
    // Passing NULL as page should trigger g_return_val_if_fail and return NULL
    char *result = poppler_page_get_selected_text(nullptr, POPPLER_SELECTION_GLYPH, &rect);
    EXPECT_EQ(result, nullptr);
}

// Test that passing NULL selection returns NULL
TEST_F(PopplerPageGetSelectedTextTest_2443, NullSelectionReturnsNull_2443) {
    if (page == nullptr) {
        GTEST_SKIP() << "Could not create test page";
    }
    
    char *result = poppler_page_get_selected_text(page, POPPLER_SELECTION_GLYPH, nullptr);
    EXPECT_EQ(result, nullptr);
}

// Test with POPPLER_SELECTION_GLYPH style - normal operation
TEST_F(PopplerPageGetSelectedTextTest_2443, GlyphSelectionStyleReturnsString_2443) {
    if (page == nullptr) {
        GTEST_SKIP() << "Could not create test page";
    }
    
    PopplerRectangle rect;
    rect.x1 = 0;
    rect.y1 = 0;
    rect.x2 = 612;
    rect.y2 = 792;
    
    char *result = poppler_page_get_selected_text(page, POPPLER_SELECTION_GLYPH, &rect);
    EXPECT_NE(result, nullptr);
    if (result) {
        g_free(result);
    }
}

// Test with POPPLER_SELECTION_WORD style
TEST_F(PopplerPageGetSelectedTextTest_2443, WordSelectionStyleReturnsString_2443) {
    if (page == nullptr) {
        GTEST_SKIP() << "Could not create test page";
    }
    
    PopplerRectangle rect;
    rect.x1 = 0;
    rect.y1 = 0;
    rect.x2 = 612;
    rect.y2 = 792;
    
    char *result = poppler_page_get_selected_text(page, POPPLER_SELECTION_WORD, &rect);
    EXPECT_NE(result, nullptr);
    if (result) {
        g_free(result);
    }
}

// Test with POPPLER_SELECTION_LINE style
TEST_F(PopplerPageGetSelectedTextTest_2443, LineSelectionStyleReturnsString_2443) {
    if (page == nullptr) {
        GTEST_SKIP() << "Could not create test page";
    }
    
    PopplerRectangle rect;
    rect.x1 = 0;
    rect.y1 = 0;
    rect.x2 = 612;
    rect.y2 = 792;
    
    char *result = poppler_page_get_selected_text(page, POPPLER_SELECTION_LINE, &rect);
    EXPECT_NE(result, nullptr);
    if (result) {
        g_free(result);
    }
}

// Test with zero-area selection rectangle
TEST_F(PopplerPageGetSelectedTextTest_2443, ZeroAreaSelectionReturnsEmptyOrNull_2443) {
    if (page == nullptr) {
        GTEST_SKIP() << "Could not create test page";
    }
    
    PopplerRectangle rect;
    rect.x1 = 0;
    rect.y1 = 0;
    rect.x2 = 0;
    rect.y2 = 0;
    
    char *result = poppler_page_get_selected_text(page, POPPLER_SELECTION_GLYPH, &rect);
    // With a zero-area rectangle, we expect either NULL or an empty string
    EXPECT_NE(result, nullptr);
    if (result) {
        // Zero area selection likely yields empty text
        EXPECT_STREQ(result, "");
        g_free(result);
    }
}

// Test with selection rectangle outside page bounds
TEST_F(PopplerPageGetSelectedTextTest_2443, OutOfBoundsSelectionReturnsEmptyString_2443) {
    if (page == nullptr) {
        GTEST_SKIP() << "Could not create test page";
    }
    
    PopplerRectangle rect;
    rect.x1 = 10000;
    rect.y1 = 10000;
    rect.x2 = 20000;
    rect.y2 = 20000;
    
    char *result = poppler_page_get_selected_text(page, POPPLER_SELECTION_GLYPH, &rect);
    EXPECT_NE(result, nullptr);
    if (result) {
        // Selection outside page should return empty string
        EXPECT_STREQ(result, "");
        g_free(result);
    }
}

// Test with negative coordinates in selection
TEST_F(PopplerPageGetSelectedTextTest_2443, NegativeCoordinatesSelection_2443) {
    if (page == nullptr) {
        GTEST_SKIP() << "Could not create test page";
    }
    
    PopplerRectangle rect;
    rect.x1 = -100;
    rect.y1 = -100;
    rect.x2 = -50;
    rect.y2 = -50;
    
    char *result = poppler_page_get_selected_text(page, POPPLER_SELECTION_GLYPH, &rect);
    EXPECT_NE(result, nullptr);
    if (result) {
        g_free(result);
    }
}

// Test that result is a valid freeable string (not corrupted memory)
TEST_F(PopplerPageGetSelectedTextTest_2443, ResultIsFreeable_2443) {
    if (page == nullptr) {
        GTEST_SKIP() << "Could not create test page";
    }
    
    PopplerRectangle rect;
    rect.x1 = 90;
    rect.y1 = 80;
    rect.x2 = 300;
    rect.y2 = 720;
    
    char *result = poppler_page_get_selected_text(page, POPPLER_SELECTION_GLYPH, &rect);
    ASSERT_NE(result, nullptr);
    // Verify it's a valid C string (can compute strlen without crashing)
    size_t len = strlen(result);
    EXPECT_GE(len, 0u);
    g_free(result);
}

// Test with inverted rectangle (x1 > x2, y1 > y2)
TEST_F(PopplerPageGetSelectedTextTest_2443, InvertedRectangleSelection_2443) {
    if (page == nullptr) {
        GTEST_SKIP() << "Could not create test page";
    }
    
    PopplerRectangle rect;
    rect.x1 = 612;
    rect.y1 = 792;
    rect.x2 = 0;
    rect.y2 = 0;
    
    char *result = poppler_page_get_selected_text(page, POPPLER_SELECTION_GLYPH, &rect);
    // Should still return a valid (possibly empty) string
    EXPECT_NE(result, nullptr);
    if (result) {
        g_free(result);
    }
}

// Test that different selection styles can produce different results on same area
TEST_F(PopplerPageGetSelectedTextTest_2443, DifferentStylesSameArea_2443) {
    if (page == nullptr) {
        GTEST_SKIP() << "Could not create test page";
    }
    
    PopplerRectangle rect;
    rect.x1 = 0;
    rect.y1 = 0;
    rect.x2 = 612;
    rect.y2 = 792;
    
    char *result_glyph = poppler_page_get_selected_text(page, POPPLER_SELECTION_GLYPH, &rect);
    char *result_word = poppler_page_get_selected_text(page, POPPLER_SELECTION_WORD, &rect);
    char *result_line = poppler_page_get_selected_text(page, POPPLER_SELECTION_LINE, &rect);
    
    // All should return non-null
    EXPECT_NE(result_glyph, nullptr);
    EXPECT_NE(result_word, nullptr);
    EXPECT_NE(result_line, nullptr);
    
    if (result_glyph) g_free(result_glyph);
    if (result_word) g_free(result_word);
    if (result_line) g_free(result_line);
}

// Test selecting a small area around known text position
TEST_F(PopplerPageGetSelectedTextTest_2443, SmallSelectionArea_2443) {
    if (page == nullptr) {
        GTEST_SKIP() << "Could not create test page";
    }
    
    // The text "Hello World" should be around coordinates (100, 700) based on our PDF
    PopplerRectangle rect;
    rect.x1 = 95;
    rect.y1 = 85;  // Adjusted for coordinate system (y might be flipped)
    rect.x2 = 200;
    rect.y2 = 100;
    
    char *result = poppler_page_get_selected_text(page, POPPLER_SELECTION_GLYPH, &rect);
    EXPECT_NE(result, nullptr);
    if (result) {
        g_free(result);
    }
}

// Test calling the function multiple times on the same page (consistency)
TEST_F(PopplerPageGetSelectedTextTest_2443, MultipleCalls_2443) {
    if (page == nullptr) {
        GTEST_SKIP() << "Could not create test page";
    }
    
    PopplerRectangle rect;
    rect.x1 = 0;
    rect.y1 = 0;
    rect.x2 = 612;
    rect.y2 = 792;
    
    char *result1 = poppler_page_get_selected_text(page, POPPLER_SELECTION_GLYPH, &rect);
    char *result2 = poppler_page_get_selected_text(page, POPPLER_SELECTION_GLYPH, &rect);
    
    ASSERT_NE(result1, nullptr);
    ASSERT_NE(result2, nullptr);
    
    // Same selection should yield same text
    EXPECT_STREQ(result1, result2);
    
    g_free(result1);
    g_free(result2);
}

// Test with point selection (x1==x2 and y1==y2 but non-zero)
TEST_F(PopplerPageGetSelectedTextTest_2443, PointSelection_2443) {
    if (page == nullptr) {
        GTEST_SKIP() << "Could not create test page";
    }
    
    PopplerRectangle rect;
    rect.x1 = 100;
    rect.y1 = 100;
    rect.x2 = 100;
    rect.y2 = 100;
    
    char *result = poppler_page_get_selected_text(page, POPPLER_SELECTION_GLYPH, &rect);
    EXPECT_NE(result, nullptr);
    if (result) {
        g_free(result);
    }
}
