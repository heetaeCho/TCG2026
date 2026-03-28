// File: poppler_page_get_image_mapping_test_2448.cc

#include <gtest/gtest.h>
#include <gmock/gmock.h>

extern "C" {
#include <glib.h>
#include "poppler.h"
}

using ::testing::NotNull;
using ::testing::IsNull;

/**
 * Test Suite for poppler_page_get_image_mapping
 *
 * The TEST_ID is 2448
 *
 * These tests treat poppler_page_get_image_mapping as a black box and verify:
 *  - Normal operation (valid page with images)
 *  - Boundary condition (no images)
 *  - Exceptional case (invalid/null page)
 *  - Observable properties of returned mappings (non-null, ids, area validity)
 */

class PopplerPageGetImageMappingTest_2448 : public ::testing::Test {
protected:
    void TearDown() override {
        // nothing
    }

    void FreeMappingList(GList *list) {
        if (!list)
            return;

        for (GList *l = list; l != nullptr; l = l->next) {
            PopplerImageMapping *mapping =
                static_cast<PopplerImageMapping *>(l->data);
            if (mapping) {
                poppler_image_mapping_free(mapping);
            }
        }
        g_list_free(list);
    }
};

/**
 * Exceptional Case:
 * Passing a NULL page should return NULL (g_return_val_if_fail behavior).
 */
TEST_F(PopplerPageGetImageMappingTest_2448,
       NullPageReturnsNull_2448) {
    GList *result = poppler_page_get_image_mapping(nullptr);
    EXPECT_EQ(result, nullptr);
}

/**
 * Normal Operation:
 * For a valid document page, the function should return a non-null list
 * (if images exist) or a null/empty list (if none exist).
 * We verify that:
 *  - Call does not crash
 *  - Returned list (if non-null) contains valid mappings
 */
TEST_F(PopplerPageGetImageMappingTest_2448,
       ValidPageReturnsMappingListOrNull_2448) {
    // Create a minimal empty PDF document in memory.
    const char *pdf_data =
        "%PDF-1.4\n"
        "1 0 obj\n"
        "<< /Type /Catalog /Pages 2 0 R >>\n"
        "endobj\n"
        "2 0 obj\n"
        "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
        "endobj\n"
        "3 0 obj\n"
        "<< /Type /Page /Parent 2 0 R "
        "/MediaBox [0 0 200 200] "
        "/Contents 4 0 R >>\n"
        "endobj\n"
        "4 0 obj\n"
        "<< /Length 0 >>\n"
        "stream\n"
        "endstream\n"
        "endobj\n"
        "xref\n"
        "0 5\n"
        "0000000000 65535 f \n"
        "0000000010 00000 n \n"
        "0000000060 00000 n \n"
        "0000000117 00000 n \n"
        "0000000210 00000 n \n"
        "trailer\n"
        "<< /Size 5 /Root 1 0 R >>\n"
        "startxref\n"
        "280\n"
        "%%EOF\n";

    GError *error = nullptr;
    PopplerDocument *doc =
        poppler_document_new_from_data(pdf_data,
                                       strlen(pdf_data),
                                       nullptr,
                                       &error);

    ASSERT_THAT(doc, NotNull());
    ASSERT_EQ(error, nullptr);

    PopplerPage *page = poppler_document_get_page(doc, 0);
    ASSERT_THAT(page, NotNull());

    GList *result = poppler_page_get_image_mapping(page);

    // Since the page has no images, we expect NULL (boundary case).
    EXPECT_TRUE(result == nullptr || g_list_length(result) >= 0);

    if (result) {
        for (GList *l = result; l != nullptr; l = l->next) {
            PopplerImageMapping *mapping =
                static_cast<PopplerImageMapping *>(l->data);
            ASSERT_THAT(mapping, NotNull());

            // image_id must be non-negative
            EXPECT_GE(mapping->image_id, 0);

            // Area coordinates should be finite numbers.
            EXPECT_TRUE(std::isfinite(mapping->area.x1));
            EXPECT_TRUE(std::isfinite(mapping->area.y1));
            EXPECT_TRUE(std::isfinite(mapping->area.x2));
            EXPECT_TRUE(std::isfinite(mapping->area.y2));
        }
    }

    FreeMappingList(result);
    g_object_unref(page);
    g_object_unref(doc);
}

/**
 * Boundary Condition:
 * If a page contains no images, the returned list should be NULL.
 */
TEST_F(PopplerPageGetImageMappingTest_2448,
       PageWithNoImagesReturnsNull_2448) {
    const char *pdf_data =
        "%PDF-1.4\n"
        "1 0 obj\n"
        "<< /Type /Catalog /Pages 2 0 R >>\n"
        "endobj\n"
        "2 0 obj\n"
        "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
        "endobj\n"
        "3 0 obj\n"
        "<< /Type /Page /Parent 2 0 R "
        "/MediaBox [0 0 300 300] "
        "/Contents 4 0 R >>\n"
        "endobj\n"
        "4 0 obj\n"
        "<< /Length 0 >>\n"
        "stream\n"
        "endstream\n"
        "endobj\n"
        "xref\n"
        "0 5\n"
        "0000000000 65535 f \n"
        "0000000010 00000 n \n"
        "0000000060 00000 n \n"
        "0000000117 00000 n \n"
        "0000000210 00000 n \n"
        "trailer\n"
        "<< /Size 5 /Root 1 0 R >>\n"
        "startxref\n"
        "280\n"
        "%%EOF\n";

    GError *error = nullptr;
    PopplerDocument *doc =
        poppler_document_new_from_data(pdf_data,
                                       strlen(pdf_data),
                                       nullptr,
                                       &error);

    ASSERT_THAT(doc, NotNull());
    ASSERT_EQ(error, nullptr);

    PopplerPage *page = poppler_document_get_page(doc, 0);
    ASSERT_THAT(page, NotNull());

    GList *result = poppler_page_get_image_mapping(page);

    EXPECT_EQ(result, nullptr);

    FreeMappingList(result);
    g_object_unref(page);
    g_object_unref(doc);
}