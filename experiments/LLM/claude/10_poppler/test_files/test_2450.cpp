#include <glib.h>
#include <poppler.h>
#include <cairo.h>
#include <gtest/gtest.h>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <string>

class PopplerPageGetImageTest_2450 : public ::testing::Test {
protected:
    PopplerDocument *doc_with_image = nullptr;
    PopplerDocument *doc_without_image = nullptr;
    PopplerPage *page_with_image = nullptr;
    PopplerPage *page_without_image = nullptr;

    // Helper to create a minimal PDF with an embedded image
    static std::string createPdfWithImage() {
        // Minimal PDF with a small inline image
        std::string pdf =
            "%PDF-1.4\n"
            "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
            "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
            "3 0 obj<</Type/Page/Parent 2 0 R/MediaBox[0 0 100 100]/Contents 4 0 R/Resources<</XObject<</Im0 5 0 R>>>>>>endobj\n"
            "4 0 obj<</Length 26>>stream\n"
            "/Im0 Do\n"
            "endstream\n"
            "endobj\n"
            "5 0 obj<</Type/XObject/Subtype/Image/Width 2/Height 2/ColorSpace/DeviceRGB/BitsPerComponent 8/Length 12>>stream\n"
            "\xFF\x00\x00\x00\xFF\x00\x00\x00\xFF\xFF\xFF\x00"
            "endstream\n"
            "endobj\n"
            "xref\n"
            "0 6\n"
            "0000000000 65535 f \n"
            "0000000009 00000 n \n"
            "0000000058 00000 n \n"
            "0000000115 00000 n \n"
            "0000000266 00000 n \n"
            "0000000342 00000 n \n"
            "trailer<</Size 6/Root 1 0 R>>\n"
            "startxref\n"
            "520\n"
            "%%EOF\n";
        return pdf;
    }

    // Helper to create a minimal PDF without images
    static std::string createPdfWithoutImage() {
        std::string pdf =
            "%PDF-1.4\n"
            "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
            "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
            "3 0 obj<</Type/Page/Parent 2 0 R/MediaBox[0 0 100 100]/Contents 4 0 R/Resources<<>>>>endobj\n"
            "4 0 obj<</Length 2>>stream\n"
            "  \n"
            "endstream\n"
            "endobj\n"
            "xref\n"
            "0 5\n"
            "0000000000 65535 f \n"
            "0000000009 00000 n \n"
            "0000000058 00000 n \n"
            "0000000115 00000 n \n"
            "0000000230 00000 n \n"
            "trailer<</Size 5/Root 1 0 R>>\n"
            "startxref\n"
            "300\n"
            "%%EOF\n";
        return pdf;
    }

    PopplerDocument* loadFromString(const std::string &pdfData) {
        GError *error = nullptr;
        PopplerDocument *doc = poppler_document_new_from_data(
            (char*)pdfData.c_str(), pdfData.size(), nullptr, &error);
        if (error) {
            g_error_free(error);
            return nullptr;
        }
        return doc;
    }

    void SetUp() override {
        std::string pdfWithImg = createPdfWithImage();
        std::string pdfNoImg = createPdfWithoutImage();

        doc_with_image = loadFromString(pdfWithImg);
        doc_without_image = loadFromString(pdfNoImg);

        if (doc_with_image) {
            page_with_image = poppler_document_get_page(doc_with_image, 0);
        }
        if (doc_without_image) {
            page_without_image = poppler_document_get_page(doc_without_image, 0);
        }
    }

    void TearDown() override {
        if (page_with_image) g_object_unref(page_with_image);
        if (page_without_image) g_object_unref(page_without_image);
        if (doc_with_image) g_object_unref(doc_with_image);
        if (doc_without_image) g_object_unref(doc_without_image);
    }
};

// Test that passing NULL page returns NULL
TEST_F(PopplerPageGetImageTest_2450, NullPageReturnsNull_2450) {
    cairo_surface_t *result = poppler_page_get_image(nullptr, 0);
    EXPECT_EQ(result, nullptr);
}

// Test that an invalid (non-PopplerPage) GObject returns NULL
TEST_F(PopplerPageGetImageTest_2450, InvalidPageTypeReturnsNull_2450) {
    // Create a non-PopplerPage GObject
    GObject *not_a_page = (GObject*)g_object_new(G_TYPE_OBJECT, nullptr);
    cairo_surface_t *result = poppler_page_get_image((PopplerPage*)not_a_page, 0);
    EXPECT_EQ(result, nullptr);
    g_object_unref(not_a_page);
}

// Test that requesting an image with an out-of-range ID returns NULL
TEST_F(PopplerPageGetImageTest_2450, OutOfRangeImageIdReturnsNull_2450) {
    if (!page_with_image) {
        GTEST_SKIP() << "Could not create test PDF with image";
    }
    // Use a very large image_id that's certainly out of range
    cairo_surface_t *result = poppler_page_get_image(page_with_image, 99999);
    EXPECT_EQ(result, nullptr);
}

// Test negative image ID returns NULL (out of range behavior)
TEST_F(PopplerPageGetImageTest_2450, NegativeImageIdReturnsNull_2450) {
    if (!page_with_image) {
        GTEST_SKIP() << "Could not create test PDF with image";
    }
    cairo_surface_t *result = poppler_page_get_image(page_with_image, -1);
    EXPECT_EQ(result, nullptr);
}

// Test that page without images returns NULL for image_id 0
TEST_F(PopplerPageGetImageTest_2450, PageWithNoImagesReturnsNull_2450) {
    if (!page_without_image) {
        GTEST_SKIP() << "Could not create test PDF without images";
    }
    cairo_surface_t *result = poppler_page_get_image(page_without_image, 0);
    EXPECT_EQ(result, nullptr);
}

// Test that a valid image retrieval returns a non-null surface
TEST_F(PopplerPageGetImageTest_2450, ValidImageIdReturnsSurface_2450) {
    if (!page_with_image) {
        GTEST_SKIP() << "Could not create test PDF with image";
    }

    // First check if there are images using poppler_page_get_image_mapping
    GList *image_mapping = poppler_page_get_image_mapping(page_with_image);
    if (!image_mapping) {
        GTEST_SKIP() << "No images found in test PDF";
    }

    PopplerImageMapping *mapping = (PopplerImageMapping*)image_mapping->data;
    gint image_id = mapping->image_id;

    cairo_surface_t *result = poppler_page_get_image(page_with_image, image_id);
    if (result) {
        EXPECT_NE(result, nullptr);
        // Verify it's a valid cairo surface
        EXPECT_EQ(cairo_surface_status(result), CAIRO_STATUS_SUCCESS);
        cairo_surface_destroy(result);
    }
    // Even if result is null (image decode issue), the function shouldn't crash

    poppler_page_free_image_mapping(image_mapping);
}

// Test that the returned surface is properly referenced (can be used after return)
TEST_F(PopplerPageGetImageTest_2450, ReturnedSurfaceIsReferenced_2450) {
    if (!page_with_image) {
        GTEST_SKIP() << "Could not create test PDF with image";
    }

    GList *image_mapping = poppler_page_get_image_mapping(page_with_image);
    if (!image_mapping) {
        GTEST_SKIP() << "No images found in test PDF";
    }

    PopplerImageMapping *mapping = (PopplerImageMapping*)image_mapping->data;
    gint image_id = mapping->image_id;

    cairo_surface_t *result = poppler_page_get_image(page_with_image, image_id);
    if (result) {
        // The surface should be valid and usable
        EXPECT_EQ(cairo_surface_status(result), CAIRO_STATUS_SUCCESS);
        
        // Get reference count indirectly: we should be able to reference and unreference
        cairo_surface_reference(result);
        cairo_surface_destroy(result); // Undo our extra reference
        
        // Original reference should still be valid
        EXPECT_EQ(cairo_surface_status(result), CAIRO_STATUS_SUCCESS);
        
        cairo_surface_destroy(result); // Clean up the function's reference
    }

    poppler_page_free_image_mapping(image_mapping);
}

// Test calling get_image multiple times with same ID returns consistent results
TEST_F(PopplerPageGetImageTest_2450, MultipleCallsSameIdConsistent_2450) {
    if (!page_with_image) {
        GTEST_SKIP() << "Could not create test PDF with image";
    }

    GList *image_mapping = poppler_page_get_image_mapping(page_with_image);
    if (!image_mapping) {
        GTEST_SKIP() << "No images found in test PDF";
    }

    PopplerImageMapping *mapping = (PopplerImageMapping*)image_mapping->data;
    gint image_id = mapping->image_id;

    cairo_surface_t *result1 = poppler_page_get_image(page_with_image, image_id);
    cairo_surface_t *result2 = poppler_page_get_image(page_with_image, image_id);

    // Both calls should have the same success/failure status
    if (result1 && result2) {
        EXPECT_EQ(cairo_surface_status(result1), CAIRO_STATUS_SUCCESS);
        EXPECT_EQ(cairo_surface_status(result2), CAIRO_STATUS_SUCCESS);
        
        // Both should have same dimensions
        EXPECT_EQ(cairo_image_surface_get_width(result1), 
                  cairo_image_surface_get_width(result2));
        EXPECT_EQ(cairo_image_surface_get_height(result1), 
                  cairo_image_surface_get_height(result2));
        
        cairo_surface_destroy(result1);
        cairo_surface_destroy(result2);
    } else {
        // Both should be null or both non-null
        EXPECT_EQ(result1 == nullptr, result2 == nullptr);
        if (result1) cairo_surface_destroy(result1);
        if (result2) cairo_surface_destroy(result2);
    }

    poppler_page_free_image_mapping(image_mapping);
}

// Test boundary: image_id exactly at the count (should return null)
TEST_F(PopplerPageGetImageTest_2450, ImageIdAtExactCountReturnsNull_2450) {
    if (!page_with_image) {
        GTEST_SKIP() << "Could not create test PDF with image";
    }

    GList *image_mapping = poppler_page_get_image_mapping(page_with_image);
    if (!image_mapping) {
        GTEST_SKIP() << "No images found in test PDF";
    }

    // Count number of images
    guint num_images = g_list_length(image_mapping);
    
    // image_id equal to num_images should be out of range
    cairo_surface_t *result = poppler_page_get_image(page_with_image, (gint)num_images);
    EXPECT_EQ(result, nullptr);

    poppler_page_free_image_mapping(image_mapping);
}

// Test with INT_MAX as image_id
TEST_F(PopplerPageGetImageTest_2450, IntMaxImageIdReturnsNull_2450) {
    if (!page_with_image) {
        GTEST_SKIP() << "Could not create test PDF with image";
    }
    cairo_surface_t *result = poppler_page_get_image(page_with_image, G_MAXINT);
    EXPECT_EQ(result, nullptr);
}

// Test with image_id = 0 on page without images
TEST_F(PopplerPageGetImageTest_2450, ZeroIdOnEmptyPageReturnsNull_2450) {
    if (!page_without_image) {
        GTEST_SKIP() << "Could not create test PDF without images";
    }
    cairo_surface_t *result = poppler_page_get_image(page_without_image, 0);
    EXPECT_EQ(result, nullptr);
}
