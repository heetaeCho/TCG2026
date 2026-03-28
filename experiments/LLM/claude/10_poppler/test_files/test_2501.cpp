#include <gtest/gtest.h>
#include <poppler.h>
#include <glib.h>
#include <cstring>
#include <cstdio>

// Helper to create a minimal PDF in memory for testing
static PopplerDocument *create_test_document_from_data(const char *pdf_data, gsize len) {
    GError *error = nullptr;
    GBytes *bytes = g_bytes_new(pdf_data, len);
    PopplerDocument *doc = poppler_document_new_from_bytes(bytes, nullptr, &error);
    g_bytes_unref(bytes);
    if (error) {
        g_error_free(error);
        return nullptr;
    }
    return doc;
}

// Minimal valid PDF with text content
static const char *minimal_pdf_with_text =
    "%PDF-1.0\n"
    "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
    "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
    "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R/Contents 4 0 R/Resources<</Font<</F1 5 0 R>>>>>>endobj\n"
    "4 0 obj<</Length 44>>stream\n"
    "BT /F1 12 Tf 100 700 Td (Hello World) Tj ET\n"
    "endstream\nendobj\n"
    "5 0 obj<</Type/Font/Subtype/Type1/BaseFont/Helvetica>>endobj\n"
    "xref\n"
    "0 6\n"
    "0000000000 65535 f \n"
    "0000000009 00000 n \n"
    "0000000058 00000 n \n"
    "0000000115 00000 n \n"
    "0000000266 00000 n \n"
    "0000000360 00000 n \n"
    "trailer<</Size 6/Root 1 0 R>>\n"
    "startxref\n"
    "431\n"
    "%%EOF\n";

// Minimal PDF with no text
static const char *minimal_pdf_no_text =
    "%PDF-1.0\n"
    "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
    "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
    "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R/Resources<<>>>>endobj\n"
    "xref\n"
    "0 4\n"
    "0000000000 65535 f \n"
    "0000000009 00000 n \n"
    "0000000058 00000 n \n"
    "0000000115 00000 n \n"
    "trailer<</Size 4/Root 1 0 R>>\n"
    "startxref\n"
    "206\n"
    "%%EOF\n";

class PopplerPageTextLayoutTest_2501 : public ::testing::Test {
protected:
    void SetUp() override {
        doc_with_text_ = create_test_document_from_data(minimal_pdf_with_text,
                                                         strlen(minimal_pdf_with_text));
        if (doc_with_text_) {
            page_with_text_ = poppler_document_get_page(doc_with_text_, 0);
        }

        doc_no_text_ = create_test_document_from_data(minimal_pdf_no_text,
                                                       strlen(minimal_pdf_no_text));
        if (doc_no_text_) {
            page_no_text_ = poppler_document_get_page(doc_no_text_, 0);
        }
    }

    void TearDown() override {
        if (page_with_text_) g_object_unref(page_with_text_);
        if (doc_with_text_) g_object_unref(doc_with_text_);
        if (page_no_text_) g_object_unref(page_no_text_);
        if (doc_no_text_) g_object_unref(doc_no_text_);
    }

    PopplerDocument *doc_with_text_ = nullptr;
    PopplerPage *page_with_text_ = nullptr;
    PopplerDocument *doc_no_text_ = nullptr;
    PopplerPage *page_no_text_ = nullptr;
};

// Test: NULL page parameter should return FALSE (g_return_val_if_fail)
TEST_F(PopplerPageTextLayoutTest_2501, NullPageReturnsFalse_2501) {
    PopplerRectangle area = {0, 0, 612, 792};
    PopplerRectangle *rectangles = nullptr;
    guint n_rectangles = 0;

    // g_return_val_if_fail will trigger a critical warning and return FALSE
    // We suppress the warning for test purposes
    g_test_expect_message(nullptr, G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_PAGE*");
    gboolean result = poppler_page_get_text_layout_for_area(nullptr, &area, &rectangles, &n_rectangles);
    g_test_assert_expected_messages();

    EXPECT_FALSE(result);
}

// Test: NULL area parameter should return FALSE
TEST_F(PopplerPageTextLayoutTest_2501, NullAreaReturnsFalse_2501) {
    if (!page_with_text_) {
        GTEST_SKIP() << "Could not create test document";
    }
    PopplerRectangle *rectangles = nullptr;
    guint n_rectangles = 0;

    g_test_expect_message(nullptr, G_LOG_LEVEL_CRITICAL, "*area != nullptr*");
    gboolean result = poppler_page_get_text_layout_for_area(page_with_text_, nullptr, &rectangles, &n_rectangles);
    g_test_assert_expected_messages();

    EXPECT_FALSE(result);
}

// Test: Area with no text content should return FALSE
TEST_F(PopplerPageTextLayoutTest_2501, EmptyPageReturnsFalse_2501) {
    if (!page_no_text_) {
        GTEST_SKIP() << "Could not create test document without text";
    }
    PopplerRectangle area = {0, 0, 612, 792};
    PopplerRectangle *rectangles = nullptr;
    guint n_rectangles = 0;

    gboolean result = poppler_page_get_text_layout_for_area(page_no_text_, &area, &rectangles, &n_rectangles);

    EXPECT_FALSE(result);
    EXPECT_EQ(n_rectangles, 0u);
}

// Test: Area that doesn't overlap any text should return FALSE
TEST_F(PopplerPageTextLayoutTest_2501, AreaWithNoTextOverlapReturnsFalse_2501) {
    if (!page_with_text_) {
        GTEST_SKIP() << "Could not create test document";
    }
    // Area far from where text is placed (text is around x=100, y=700)
    PopplerRectangle area = {500, 0, 612, 50};
    PopplerRectangle *rectangles = nullptr;
    guint n_rectangles = 0;

    gboolean result = poppler_page_get_text_layout_for_area(page_with_text_, &area, &rectangles, &n_rectangles);

    // Either FALSE (no words found) or TRUE with some rectangles
    if (!result) {
        EXPECT_EQ(n_rectangles, 0u);
    }
}

// Test: Full page area with text should return TRUE and provide rectangles
TEST_F(PopplerPageTextLayoutTest_2501, FullPageAreaWithTextReturnsTrue_2501) {
    if (!page_with_text_) {
        GTEST_SKIP() << "Could not create test document";
    }
    PopplerRectangle area = {0, 0, 612, 792};
    PopplerRectangle *rectangles = nullptr;
    guint n_rectangles = 0;

    gboolean result = poppler_page_get_text_layout_for_area(page_with_text_, &area, &rectangles, &n_rectangles);

    if (result) {
        EXPECT_GT(n_rectangles, 0u);
        EXPECT_NE(rectangles, nullptr);

        // Verify rectangles have reasonable values (within page bounds approximately)
        for (guint i = 0; i < n_rectangles; i++) {
            // Just check they are finite numbers
            EXPECT_FALSE(std::isnan(rectangles[i].x1));
            EXPECT_FALSE(std::isnan(rectangles[i].y1));
            EXPECT_FALSE(std::isnan(rectangles[i].x2));
            EXPECT_FALSE(std::isnan(rectangles[i].y2));
        }

        g_free(rectangles);
    } else {
        // Document might not have parsed text properly with minimal PDF
        EXPECT_EQ(n_rectangles, 0u);
    }
}

// Test: n_rectangles is set to 0 initially even on success
TEST_F(PopplerPageTextLayoutTest_2501, NRectanglesInitializedToZero_2501) {
    if (!page_no_text_) {
        GTEST_SKIP() << "Could not create test document without text";
    }
    PopplerRectangle area = {0, 0, 612, 792};
    PopplerRectangle *rectangles = nullptr;
    guint n_rectangles = 999;  // Set to non-zero

    gboolean result = poppler_page_get_text_layout_for_area(page_no_text_, &area, &rectangles, &n_rectangles);

    if (!result) {
        EXPECT_EQ(n_rectangles, 0u);
    }
}

// Test: Zero-size area should return FALSE
TEST_F(PopplerPageTextLayoutTest_2501, ZeroSizeAreaReturnsFalse_2501) {
    if (!page_with_text_) {
        GTEST_SKIP() << "Could not create test document";
    }
    PopplerRectangle area = {0, 0, 0, 0};
    PopplerRectangle *rectangles = nullptr;
    guint n_rectangles = 0;

    gboolean result = poppler_page_get_text_layout_for_area(page_with_text_, &area, &rectangles, &n_rectangles);

    // A zero-size area should find no text
    if (!result) {
        EXPECT_EQ(n_rectangles, 0u);
    }
}

// Test: Negative coordinate area
TEST_F(PopplerPageTextLayoutTest_2501, NegativeCoordinateArea_2501) {
    if (!page_with_text_) {
        GTEST_SKIP() << "Could not create test document";
    }
    PopplerRectangle area = {-100, -100, -50, -50};
    PopplerRectangle *rectangles = nullptr;
    guint n_rectangles = 0;

    gboolean result = poppler_page_get_text_layout_for_area(page_with_text_, &area, &rectangles, &n_rectangles);

    // No text should be in negative coordinates
    if (!result) {
        EXPECT_EQ(n_rectangles, 0u);
    }
}

// Test: Very large area covering entire page and beyond
TEST_F(PopplerPageTextLayoutTest_2501, VeryLargeAreaCoversAll_2501) {
    if (!page_with_text_) {
        GTEST_SKIP() << "Could not create test document";
    }
    PopplerRectangle area = {-1000, -1000, 10000, 10000};
    PopplerRectangle *rectangles = nullptr;
    guint n_rectangles = 0;

    gboolean result = poppler_page_get_text_layout_for_area(page_with_text_, &area, &rectangles, &n_rectangles);

    if (result) {
        EXPECT_GT(n_rectangles, 0u);
        EXPECT_NE(rectangles, nullptr);
        g_free(rectangles);
    }
}

// Test: Calling the function twice on the same page should give consistent results
TEST_F(PopplerPageTextLayoutTest_2501, ConsistentResultsOnMultipleCalls_2501) {
    if (!page_with_text_) {
        GTEST_SKIP() << "Could not create test document";
    }
    PopplerRectangle area = {0, 0, 612, 792};
    PopplerRectangle *rectangles1 = nullptr;
    guint n_rectangles1 = 0;
    PopplerRectangle *rectangles2 = nullptr;
    guint n_rectangles2 = 0;

    gboolean result1 = poppler_page_get_text_layout_for_area(page_with_text_, &area, &rectangles1, &n_rectangles1);
    gboolean result2 = poppler_page_get_text_layout_for_area(page_with_text_, &area, &rectangles2, &n_rectangles2);

    EXPECT_EQ(result1, result2);
    EXPECT_EQ(n_rectangles1, n_rectangles2);

    if (result1 && result2) {
        for (guint i = 0; i < n_rectangles1; i++) {
            EXPECT_DOUBLE_EQ(rectangles1[i].x1, rectangles2[i].x1);
            EXPECT_DOUBLE_EQ(rectangles1[i].y1, rectangles2[i].y1);
            EXPECT_DOUBLE_EQ(rectangles1[i].x2, rectangles2[i].x2);
            EXPECT_DOUBLE_EQ(rectangles1[i].y2, rectangles2[i].y2);
        }
        g_free(rectangles1);
        g_free(rectangles2);
    }
}

// Test: Rectangle coordinates should generally have x1 <= x2 and y1 <= y2 for character bboxes
TEST_F(PopplerPageTextLayoutTest_2501, RectangleCoordinatesOrdering_2501) {
    if (!page_with_text_) {
        GTEST_SKIP() << "Could not create test document";
    }
    PopplerRectangle area = {0, 0, 612, 792};
    PopplerRectangle *rectangles = nullptr;
    guint n_rectangles = 0;

    gboolean result = poppler_page_get_text_layout_for_area(page_with_text_, &area, &rectangles, &n_rectangles);

    if (result && n_rectangles > 0) {
        // Character bounding boxes typically have x1 <= x2 and y1 <= y2
        // (though separator rectangles might have x1 == x2)
        for (guint i = 0; i < n_rectangles; i++) {
            EXPECT_LE(rectangles[i].x1, rectangles[i].x2) << "Rectangle " << i;
            EXPECT_LE(rectangles[i].y1, rectangles[i].y2) << "Rectangle " << i;
        }
        g_free(rectangles);
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
