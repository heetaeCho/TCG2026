#include <gtest/gtest.h>
#include <poppler.h>
#include <glib.h>
#include <cstring>
#include <cstdio>

class PopplerPageGetSizeTest_2426 : public ::testing::Test {
protected:
    PopplerDocument *doc = nullptr;
    PopplerPage *page = nullptr;

    // Helper to create a minimal PDF with given dimensions and rotation
    PopplerDocument* createPdfWithPageSize(double w, double h, int rotation) {
        // Create a minimal PDF in memory with specified media box and rotation
        char pdf[2048];
        int len = snprintf(pdf, sizeof(pdf),
            "%%PDF-1.4\n"
            "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
            "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
            "3 0 obj<</Type/Page/Parent 2 0 R/MediaBox[0 0 %.1f %.1f]/Rotate %d>>endobj\n"
            "xref\n"
            "0 4\n"
            "0000000000 65535 f \n"
            "0000000009 00000 n \n"
            "0000000058 00000 n \n"
            "0000000115 00000 n \n"
            "trailer<</Size 4/Root 1 0 R>>\n"
            "startxref\n"
            "0\n"
            "%%%%EOF\n",
            w, h, rotation);

        GError *error = nullptr;
        PopplerDocument *document = poppler_document_new_from_data(pdf, len, nullptr, &error);
        if (error) {
            g_error_free(error);
            return nullptr;
        }
        return document;
    }

    void TearDown() override {
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

// Test basic page size retrieval with no rotation
TEST_F(PopplerPageGetSizeTest_2426, BasicPageSizeNoRotation_2426) {
    doc = createPdfWithPageSize(612.0, 792.0, 0);
    ASSERT_NE(doc, nullptr);
    page = poppler_document_get_page(doc, 0);
    ASSERT_NE(page, nullptr);

    double width = 0, height = 0;
    poppler_page_get_size(page, &width, &height);
    EXPECT_DOUBLE_EQ(width, 612.0);
    EXPECT_DOUBLE_EQ(height, 792.0);
}

// Test page size with 90 degree rotation - width and height should be swapped
TEST_F(PopplerPageGetSizeTest_2426, PageSizeRotation90_2426) {
    doc = createPdfWithPageSize(612.0, 792.0, 90);
    ASSERT_NE(doc, nullptr);
    page = poppler_document_get_page(doc, 0);
    ASSERT_NE(page, nullptr);

    double width = 0, height = 0;
    poppler_page_get_size(page, &width, &height);
    EXPECT_DOUBLE_EQ(width, 792.0);
    EXPECT_DOUBLE_EQ(height, 612.0);
}

// Test page size with 180 degree rotation - no swap
TEST_F(PopplerPageGetSizeTest_2426, PageSizeRotation180_2426) {
    doc = createPdfWithPageSize(612.0, 792.0, 180);
    ASSERT_NE(doc, nullptr);
    page = poppler_document_get_page(doc, 0);
    ASSERT_NE(page, nullptr);

    double width = 0, height = 0;
    poppler_page_get_size(page, &width, &height);
    EXPECT_DOUBLE_EQ(width, 612.0);
    EXPECT_DOUBLE_EQ(height, 792.0);
}

// Test page size with 270 degree rotation - width and height should be swapped
TEST_F(PopplerPageGetSizeTest_2426, PageSizeRotation270_2426) {
    doc = createPdfWithPageSize(612.0, 792.0, 270);
    ASSERT_NE(doc, nullptr);
    page = poppler_document_get_page(doc, 0);
    ASSERT_NE(page, nullptr);

    double width = 0, height = 0;
    poppler_page_get_size(page, &width, &height);
    EXPECT_DOUBLE_EQ(width, 792.0);
    EXPECT_DOUBLE_EQ(height, 612.0);
}

// Test passing nullptr for width
TEST_F(PopplerPageGetSizeTest_2426, NullWidthPointer_2426) {
    doc = createPdfWithPageSize(612.0, 792.0, 0);
    ASSERT_NE(doc, nullptr);
    page = poppler_document_get_page(doc, 0);
    ASSERT_NE(page, nullptr);

    double height = 0;
    poppler_page_get_size(page, nullptr, &height);
    EXPECT_DOUBLE_EQ(height, 792.0);
}

// Test passing nullptr for height
TEST_F(PopplerPageGetSizeTest_2426, NullHeightPointer_2426) {
    doc = createPdfWithPageSize(612.0, 792.0, 0);
    ASSERT_NE(doc, nullptr);
    page = poppler_document_get_page(doc, 0);
    ASSERT_NE(page, nullptr);

    double width = 0;
    poppler_page_get_size(page, &width, nullptr);
    EXPECT_DOUBLE_EQ(width, 612.0);
}

// Test passing nullptr for both width and height - should not crash
TEST_F(PopplerPageGetSizeTest_2426, BothPointersNull_2426) {
    doc = createPdfWithPageSize(612.0, 792.0, 0);
    ASSERT_NE(doc, nullptr);
    page = poppler_document_get_page(doc, 0);
    ASSERT_NE(page, nullptr);

    EXPECT_NO_FATAL_FAILURE(poppler_page_get_size(page, nullptr, nullptr));
}

// Test with square page dimensions - rotation should not matter
TEST_F(PopplerPageGetSizeTest_2426, SquarePageNoRotation_2426) {
    doc = createPdfWithPageSize(500.0, 500.0, 0);
    ASSERT_NE(doc, nullptr);
    page = poppler_document_get_page(doc, 0);
    ASSERT_NE(page, nullptr);

    double width = 0, height = 0;
    poppler_page_get_size(page, &width, &height);
    EXPECT_DOUBLE_EQ(width, 500.0);
    EXPECT_DOUBLE_EQ(height, 500.0);
}

// Test with square page dimensions and 90 rotation
TEST_F(PopplerPageGetSizeTest_2426, SquarePageRotation90_2426) {
    doc = createPdfWithPageSize(500.0, 500.0, 90);
    ASSERT_NE(doc, nullptr);
    page = poppler_document_get_page(doc, 0);
    ASSERT_NE(page, nullptr);

    double width = 0, height = 0;
    poppler_page_get_size(page, &width, &height);
    EXPECT_DOUBLE_EQ(width, 500.0);
    EXPECT_DOUBLE_EQ(height, 500.0);
}

// Test with a very small page
TEST_F(PopplerPageGetSizeTest_2426, SmallPageSize_2426) {
    doc = createPdfWithPageSize(1.0, 1.0, 0);
    ASSERT_NE(doc, nullptr);
    page = poppler_document_get_page(doc, 0);
    ASSERT_NE(page, nullptr);

    double width = 0, height = 0;
    poppler_page_get_size(page, &width, &height);
    EXPECT_DOUBLE_EQ(width, 1.0);
    EXPECT_DOUBLE_EQ(height, 1.0);
}

// Test with a large page
TEST_F(PopplerPageGetSizeTest_2426, LargePageSize_2426) {
    doc = createPdfWithPageSize(14400.0, 14400.0, 0);
    ASSERT_NE(doc, nullptr);
    page = poppler_document_get_page(doc, 0);
    ASSERT_NE(page, nullptr);

    double width = 0, height = 0;
    poppler_page_get_size(page, &width, &height);
    EXPECT_DOUBLE_EQ(width, 14400.0);
    EXPECT_DOUBLE_EQ(height, 14400.0);
}

// Test that passing NULL page doesn't crash (g_return_if_fail should handle it)
TEST_F(PopplerPageGetSizeTest_2426, NullPageDoesNotCrash_2426) {
    double width = -1, height = -1;
    // g_return_if_fail should silently return without modifying width/height
    poppler_page_get_size(nullptr, &width, &height);
    EXPECT_DOUBLE_EQ(width, -1);
    EXPECT_DOUBLE_EQ(height, -1);
}

// Test landscape-oriented page
TEST_F(PopplerPageGetSizeTest_2426, LandscapePage_2426) {
    doc = createPdfWithPageSize(792.0, 612.0, 0);
    ASSERT_NE(doc, nullptr);
    page = poppler_document_get_page(doc, 0);
    ASSERT_NE(page, nullptr);

    double width = 0, height = 0;
    poppler_page_get_size(page, &width, &height);
    EXPECT_DOUBLE_EQ(width, 792.0);
    EXPECT_DOUBLE_EQ(height, 612.0);
}

// Test landscape page with 90 degree rotation
TEST_F(PopplerPageGetSizeTest_2426, LandscapePageRotation90_2426) {
    doc = createPdfWithPageSize(792.0, 612.0, 90);
    ASSERT_NE(doc, nullptr);
    page = poppler_document_get_page(doc, 0);
    ASSERT_NE(page, nullptr);

    double width = 0, height = 0;
    poppler_page_get_size(page, &width, &height);
    // Rotated 90 degrees: width gets crop height, height gets crop width
    EXPECT_DOUBLE_EQ(width, 612.0);
    EXPECT_DOUBLE_EQ(height, 792.0);
}
