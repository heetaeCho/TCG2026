#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

// Forward declarations and minimal structures to match the interface
// We need to create testable stubs since the real objects have complex dependencies

#include "poppler/PDFRectangle.h"

// Minimal mock of Page that provides getCropBox
class MockPage {
public:
    PDFRectangle cropBox;
    const PDFRectangle *getCropBox() const { return &cropBox; }
};

// Minimal structure matching _PopplerPage layout - must have a `page` member
// matching what poppler_page_get_crop_box expects
struct MinimalPopplerPage {
    // The actual _PopplerPage has GObject parent and other fields before page
    // We need to match the exact layout. Since we can't easily do that,
    // we'll test through the real API if possible.
    MockPage *page;
};

// Minimal PopplerRectangle matching the expected layout
struct MinimalPopplerRectangle {
    double x1;
    double y1;
    double x2;
    double y2;
};

// Since we cannot easily instantiate real Poppler GLib objects without a full
// PDF document, we test by loading a minimal PDF through the poppler glib API.

#include <poppler.h>

class PopplerPageGetCropBoxTest_2498 : public ::testing::Test {
protected:
    PopplerDocument *doc = nullptr;
    PopplerPage *page = nullptr;

    void SetUp() override {
        // Create a minimal PDF in memory
        // Minimal valid PDF
        const char *pdf_data =
            "%PDF-1.0\n"
            "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
            "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
            "3 0 obj<</Type/Page/Parent 2 0 R/MediaBox[0 0 612 792]/CropBox[10 20 300 400]>>endobj\n"
            "xref\n0 4\n"
            "0000000000 65535 f \n"
            "0000000009 00000 n \n"
            "0000000058 00000 n \n"
            "0000000115 00000 n \n"
            "trailer<</Size 4/Root 1 0 R>>\n"
            "startxref\n216\n%%EOF\n";

        GError *error = nullptr;
        GBytes *bytes = g_bytes_new_static(pdf_data, strlen(pdf_data));
        GInputStream *stream = g_memory_input_stream_new_from_bytes(bytes);
        doc = poppler_document_new_from_stream(stream, g_bytes_get_size(bytes), nullptr, nullptr, &error);
        g_object_unref(stream);
        g_bytes_unref(bytes);

        if (doc) {
            page = poppler_document_get_page(doc, 0);
        }
    }

    void TearDown() override {
        if (page) g_object_unref(page);
        if (doc) g_object_unref(doc);
    }
};

TEST_F(PopplerPageGetCropBoxTest_2498, CropBoxValuesAreCopiedCorrectly_2498) {
    ASSERT_NE(doc, nullptr);
    ASSERT_NE(page, nullptr);

    PopplerRectangle rect = {0, 0, 0, 0};
    poppler_page_get_crop_box(page, &rect);

    EXPECT_DOUBLE_EQ(rect.x1, 10.0);
    EXPECT_DOUBLE_EQ(rect.y1, 20.0);
    EXPECT_DOUBLE_EQ(rect.x2, 300.0);
    EXPECT_DOUBLE_EQ(rect.y2, 400.0);
}

class PopplerPageNoCropBoxTest_2498 : public ::testing::Test {
protected:
    PopplerDocument *doc = nullptr;
    PopplerPage *page = nullptr;

    void SetUp() override {
        // PDF without explicit CropBox - should default to MediaBox
        const char *pdf_data =
            "%PDF-1.0\n"
            "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
            "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
            "3 0 obj<</Type/Page/Parent 2 0 R/MediaBox[0 0 612 792]>>endobj\n"
            "xref\n0 4\n"
            "0000000000 65535 f \n"
            "0000000009 00000 n \n"
            "0000000058 00000 n \n"
            "0000000115 00000 n \n"
            "trailer<</Size 4/Root 1 0 R>>\n"
            "startxref\n195\n%%EOF\n";

        GError *error = nullptr;
        GBytes *bytes = g_bytes_new_static(pdf_data, strlen(pdf_data));
        GInputStream *stream = g_memory_input_stream_new_from_bytes(bytes);
        doc = poppler_document_new_from_stream(stream, g_bytes_get_size(bytes), nullptr, nullptr, &error);
        g_object_unref(stream);
        g_bytes_unref(bytes);

        if (doc) {
            page = poppler_document_get_page(doc, 0);
        }
    }

    void TearDown() override {
        if (page) g_object_unref(page);
        if (doc) g_object_unref(doc);
    }
};

TEST_F(PopplerPageNoCropBoxTest_2498, NoCropBoxDefaultsToMediaBox_2498) {
    ASSERT_NE(doc, nullptr);
    ASSERT_NE(page, nullptr);

    PopplerRectangle rect = {0, 0, 0, 0};
    poppler_page_get_crop_box(page, &rect);

    // When no CropBox is specified, it defaults to MediaBox
    EXPECT_DOUBLE_EQ(rect.x1, 0.0);
    EXPECT_DOUBLE_EQ(rect.y1, 0.0);
    EXPECT_DOUBLE_EQ(rect.x2, 612.0);
    EXPECT_DOUBLE_EQ(rect.y2, 792.0);
}

class PopplerPageCropBoxNegativeCoords_2498 : public ::testing::Test {
protected:
    PopplerDocument *doc = nullptr;
    PopplerPage *page = nullptr;

    void SetUp() override {
        const char *pdf_data =
            "%PDF-1.0\n"
            "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
            "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
            "3 0 obj<</Type/Page/Parent 2 0 R/MediaBox[-100 -200 612 792]/CropBox[-50 -75 500 600]>>endobj\n"
            "xref\n0 4\n"
            "0000000000 65535 f \n"
            "0000000009 00000 n \n"
            "0000000058 00000 n \n"
            "0000000115 00000 n \n"
            "trailer<</Size 4/Root 1 0 R>>\n"
            "startxref\n236\n%%EOF\n";

        GError *error = nullptr;
        GBytes *bytes = g_bytes_new_static(pdf_data, strlen(pdf_data));
        GInputStream *stream = g_memory_input_stream_new_from_bytes(bytes);
        doc = poppler_document_new_from_stream(stream, g_bytes_get_size(bytes), nullptr, nullptr, &error);
        g_object_unref(stream);
        g_bytes_unref(bytes);

        if (doc) {
            page = poppler_document_get_page(doc, 0);
        }
    }

    void TearDown() override {
        if (page) g_object_unref(page);
        if (doc) g_object_unref(doc);
    }
};

TEST_F(PopplerPageCropBoxNegativeCoords_2498, CropBoxWithNegativeCoordinates_2498) {
    ASSERT_NE(doc, nullptr);
    ASSERT_NE(page, nullptr);

    PopplerRectangle rect = {0, 0, 0, 0};
    poppler_page_get_crop_box(page, &rect);

    EXPECT_DOUBLE_EQ(rect.x1, -50.0);
    EXPECT_DOUBLE_EQ(rect.y1, -75.0);
    EXPECT_DOUBLE_EQ(rect.x2, 500.0);
    EXPECT_DOUBLE_EQ(rect.y2, 600.0);
}

class PopplerPageCropBoxZeroSize_2498 : public ::testing::Test {
protected:
    PopplerDocument *doc = nullptr;
    PopplerPage *page = nullptr;

    void SetUp() override {
        const char *pdf_data =
            "%PDF-1.0\n"
            "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
            "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
            "3 0 obj<</Type/Page/Parent 2 0 R/MediaBox[0 0 612 792]/CropBox[100 100 100 100]>>endobj\n"
            "xref\n0 4\n"
            "0000000000 65535 f \n"
            "0000000009 00000 n \n"
            "0000000058 00000 n \n"
            "0000000115 00000 n \n"
            "trailer<</Size 4/Root 1 0 R>>\n"
            "startxref\n222\n%%EOF\n";

        GError *error = nullptr;
        GBytes *bytes = g_bytes_new_static(pdf_data, strlen(pdf_data));
        GInputStream *stream = g_memory_input_stream_new_from_bytes(bytes);
        doc = poppler_document_new_from_stream(stream, g_bytes_get_size(bytes), nullptr, nullptr, &error);
        g_object_unref(stream);
        g_bytes_unref(bytes);

        if (doc) {
            page = poppler_document_get_page(doc, 0);
        }
    }

    void TearDown() override {
        if (page) g_object_unref(page);
        if (doc) g_object_unref(doc);
    }
};

TEST_F(PopplerPageCropBoxZeroSize_2498, CropBoxZeroSizeArea_2498) {
    ASSERT_NE(doc, nullptr);
    ASSERT_NE(page, nullptr);

    PopplerRectangle rect = {0, 0, 0, 0};
    poppler_page_get_crop_box(page, &rect);

    EXPECT_DOUBLE_EQ(rect.x1, 100.0);
    EXPECT_DOUBLE_EQ(rect.y1, 100.0);
    EXPECT_DOUBLE_EQ(rect.x2, 100.0);
    EXPECT_DOUBLE_EQ(rect.y2, 100.0);
}

class PopplerPageCropBoxFloatingPoint_2498 : public ::testing::Test {
protected:
    PopplerDocument *doc = nullptr;
    PopplerPage *page = nullptr;

    void SetUp() override {
        const char *pdf_data =
            "%PDF-1.0\n"
            "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
            "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
            "3 0 obj<</Type/Page/Parent 2 0 R/MediaBox[0 0 612 792]/CropBox[1.5 2.75 300.125 400.875]>>endobj\n"
            "xref\n0 4\n"
            "0000000000 65535 f \n"
            "0000000009 00000 n \n"
            "0000000058 00000 n \n"
            "0000000115 00000 n \n"
            "trailer<</Size 4/Root 1 0 R>>\n"
            "startxref\n232\n%%EOF\n";

        GError *error = nullptr;
        GBytes *bytes = g_bytes_new_static(pdf_data, strlen(pdf_data));
        GInputStream *stream = g_memory_input_stream_new_from_bytes(bytes);
        doc = poppler_document_new_from_stream(stream, g_bytes_get_size(bytes), nullptr, nullptr, &error);
        g_object_unref(stream);
        g_bytes_unref(bytes);

        if (doc) {
            page = poppler_document_get_page(doc, 0);
        }
    }

    void TearDown() override {
        if (page) g_object_unref(page);
        if (doc) g_object_unref(doc);
    }
};

TEST_F(PopplerPageCropBoxFloatingPoint_2498, CropBoxWithFloatingPointValues_2498) {
    ASSERT_NE(doc, nullptr);
    ASSERT_NE(page, nullptr);

    PopplerRectangle rect = {0, 0, 0, 0};
    poppler_page_get_crop_box(page, &rect);

    EXPECT_NEAR(rect.x1, 1.5, 0.001);
    EXPECT_NEAR(rect.y1, 2.75, 0.001);
    EXPECT_NEAR(rect.x2, 300.125, 0.001);
    EXPECT_NEAR(rect.y2, 400.875, 0.001);
}

TEST_F(PopplerPageGetCropBoxTest_2498, RectangleFieldsAreIndependent_2498) {
    ASSERT_NE(doc, nullptr);
    ASSERT_NE(page, nullptr);

    // Verify that calling get_crop_box fills all four fields independently
    PopplerRectangle rect;
    rect.x1 = 999.0;
    rect.y1 = 999.0;
    rect.x2 = 999.0;
    rect.y2 = 999.0;

    poppler_page_get_crop_box(page, &rect);

    // All values should be overwritten
    EXPECT_NE(rect.x1, 999.0);
    EXPECT_NE(rect.y1, 999.0);
    EXPECT_NE(rect.x2, 999.0);
    EXPECT_NE(rect.y2, 999.0);
}

TEST_F(PopplerPageGetCropBoxTest_2498, MultipleCallsReturnSameValues_2498) {
    ASSERT_NE(doc, nullptr);
    ASSERT_NE(page, nullptr);

    PopplerRectangle rect1 = {0, 0, 0, 0};
    PopplerRectangle rect2 = {0, 0, 0, 0};

    poppler_page_get_crop_box(page, &rect1);
    poppler_page_get_crop_box(page, &rect2);

    EXPECT_DOUBLE_EQ(rect1.x1, rect2.x1);
    EXPECT_DOUBLE_EQ(rect1.y1, rect2.y1);
    EXPECT_DOUBLE_EQ(rect1.x2, rect2.x2);
    EXPECT_DOUBLE_EQ(rect1.y2, rect2.y2);
}
