#include <gtest/gtest.h>
#include <poppler.h>
#include <glib.h>
#include <cstdio>
#include <cstring>
#include <fstream>

// Helper to create a minimal PDF with no images
static PopplerDocument* create_simple_pdf_document() {
    // Minimal PDF with one page, no images
    const char *pdf_content =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/Parent 2 0 R/MediaBox[0 0 612 792]/Contents 4 0 R/Resources<<>>>>endobj\n"
        "4 0 obj<</Length 0>>stream\n"
        "endstream endobj\n"
        "xref\n"
        "0 5\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "0000000232 00000 n \n"
        "trailer<</Size 5/Root 1 0 R>>\n"
        "startxref\n"
        "291\n"
        "%%EOF\n";

    gsize len = strlen(pdf_content);
    GError *error = nullptr;
    PopplerDocument *doc = poppler_document_new_from_data((char*)pdf_content, (int)len, nullptr, &error);
    if (error) {
        g_error_free(error);
        return nullptr;
    }
    return doc;
}

class PopplerPageImageMappingTest_2448 : public ::testing::Test {
protected:
    void SetUp() override {
        doc_ = nullptr;
        page_ = nullptr;
    }

    void TearDown() override {
        if (page_) {
            g_object_unref(page_);
            page_ = nullptr;
        }
        if (doc_) {
            g_object_unref(doc_);
            doc_ = nullptr;
        }
    }

    PopplerDocument *doc_;
    PopplerPage *page_;
};

// Test that passing NULL page returns NULL
TEST_F(PopplerPageImageMappingTest_2448, NullPageReturnsNull_2448) {
    GList *result = poppler_page_get_image_mapping(nullptr);
    EXPECT_EQ(result, nullptr);
}

// Test that a page with no images returns an empty list (NULL GList)
TEST_F(PopplerPageImageMappingTest_2448, PageWithNoImagesReturnsEmptyList_2448) {
    doc_ = create_simple_pdf_document();
    if (!doc_) {
        GTEST_SKIP() << "Could not create simple PDF document";
    }

    page_ = poppler_document_get_page(doc_, 0);
    ASSERT_NE(page_, nullptr);

    GList *map_list = poppler_page_get_image_mapping(page_);
    // A page with no images should return NULL (empty GList)
    EXPECT_EQ(map_list, nullptr);
}

// Test with a real PDF file that has images (if available)
TEST_F(PopplerPageImageMappingTest_2448, ImageMappingFromFile_2448) {
    // Try to load a test PDF with images from common test locations
    const char *test_files[] = {
        "test_with_images.pdf",
        "/tmp/test_with_images.pdf",
        nullptr
    };

    for (int i = 0; test_files[i] != nullptr; i++) {
        gchar *uri = g_filename_to_uri(test_files[i], nullptr, nullptr);
        if (!uri) continue;
        GError *error = nullptr;
        doc_ = poppler_document_new_from_file(uri, nullptr, &error);
        g_free(uri);
        if (error) {
            g_error_free(error);
            continue;
        }
        if (doc_) break;
    }

    if (!doc_) {
        GTEST_SKIP() << "No test PDF with images available";
    }

    page_ = poppler_document_get_page(doc_, 0);
    ASSERT_NE(page_, nullptr);

    GList *map_list = poppler_page_get_image_mapping(page_);
    if (map_list) {
        // Verify the structure of returned mappings
        for (GList *l = map_list; l != nullptr; l = l->next) {
            PopplerImageMapping *mapping = (PopplerImageMapping *)l->data;
            ASSERT_NE(mapping, nullptr);
            // image_id should be non-negative
            EXPECT_GE(mapping->image_id, 0);
            // Area should have valid coordinates
            EXPECT_LE(mapping->area.x1, mapping->area.x2);
            EXPECT_LE(mapping->area.y1, mapping->area.y2);
        }
        poppler_page_free_image_mapping(map_list);
    }
}

// Test that poppler_image_mapping_new and copy/free work
TEST_F(PopplerPageImageMappingTest_2448, ImageMappingNewAndFree_2448) {
    PopplerImageMapping *mapping = poppler_image_mapping_new();
    ASSERT_NE(mapping, nullptr);
    // Default values should be zero-initialized or valid
    mapping->image_id = 42;
    mapping->area.x1 = 10.0;
    mapping->area.y1 = 20.0;
    mapping->area.x2 = 100.0;
    mapping->area.y2 = 200.0;

    PopplerImageMapping *copy = poppler_image_mapping_copy(mapping);
    ASSERT_NE(copy, nullptr);
    EXPECT_EQ(copy->image_id, 42);
    EXPECT_DOUBLE_EQ(copy->area.x1, 10.0);
    EXPECT_DOUBLE_EQ(copy->area.y1, 20.0);
    EXPECT_DOUBLE_EQ(copy->area.x2, 100.0);
    EXPECT_DOUBLE_EQ(copy->area.y2, 200.0);

    poppler_image_mapping_free(copy);
    poppler_image_mapping_free(mapping);
}

// Test that freeing a NULL mapping doesn't crash
TEST_F(PopplerPageImageMappingTest_2448, FreeNullImageMapping_2448) {
    poppler_image_mapping_free(nullptr);
    // Should not crash
    SUCCEED();
}

// Test that freeing a NULL image mapping list doesn't crash
TEST_F(PopplerPageImageMappingTest_2448, FreeNullImageMappingList_2448) {
    poppler_page_free_image_mapping(nullptr);
    // Should not crash
    SUCCEED();
}

// Test that repeated calls return consistent results
TEST_F(PopplerPageImageMappingTest_2448, RepeatedCallsConsistent_2448) {
    doc_ = create_simple_pdf_document();
    if (!doc_) {
        GTEST_SKIP() << "Could not create simple PDF document";
    }

    page_ = poppler_document_get_page(doc_, 0);
    ASSERT_NE(page_, nullptr);

    GList *map_list1 = poppler_page_get_image_mapping(page_);
    GList *map_list2 = poppler_page_get_image_mapping(page_);

    // Both calls should return the same number of items (0 for no-image page)
    EXPECT_EQ(g_list_length(map_list1), g_list_length(map_list2));

    if (map_list1) poppler_page_free_image_mapping(map_list1);
    if (map_list2) poppler_page_free_image_mapping(map_list2);
}

// Test copying a NULL mapping returns NULL
TEST_F(PopplerPageImageMappingTest_2448, CopyNullImageMapping_2448) {
    PopplerImageMapping *copy = poppler_image_mapping_copy(nullptr);
    EXPECT_EQ(copy, nullptr);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
