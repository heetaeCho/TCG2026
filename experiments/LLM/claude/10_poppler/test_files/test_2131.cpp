#include <gtest/gtest.h>
#include <glib.h>

// Poppler GLib headers
extern "C" {
#include <poppler.h>
}

#include <cstring>
#include <cmath>

class PopplerAnnotInkTest_2131 : public ::testing::Test {
protected:
    PopplerDocument *doc = nullptr;
    PopplerPage *page = nullptr;

    void SetUp() override {
        GError *error = nullptr;
        // Create a minimal PDF in memory for testing
        const char *pdf_content =
            "%PDF-1.4\n"
            "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
            "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
            "3 0 obj<</Type/Page/Parent 2 0 R/MediaBox[0 0 612 792]>>endobj\n"
            "xref\n0 4\n"
            "0000000000 65535 f \n"
            "0000000009 00000 n \n"
            "0000000058 00000 n \n"
            "0000000115 00000 n \n"
            "trailer<</Size 4/Root 1 0 R>>\n"
            "startxref\n190\n%%EOF\n";

        gsize len = strlen(pdf_content);
        doc = poppler_document_new_from_data((char *)pdf_content, (int)len, nullptr, &error);
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
    }

    PopplerPath *create_path(PopplerPoint *points, int n_points) {
        PopplerPath *path = g_new0(PopplerPath, 1);
        path->points = g_new0(PopplerPoint, n_points);
        memcpy(path->points, points, sizeof(PopplerPoint) * n_points);
        path->n_points = n_points;
        return path;
    }

    void free_path(PopplerPath *path) {
        if (path) {
            g_free(path->points);
            g_free(path);
        }
    }
};

// Test setting ink list with a single path containing a single point
TEST_F(PopplerAnnotInkTest_2131, SinglePathSinglePoint_2131) {
    if (!page) {
        GTEST_SKIP() << "Could not create test document";
    }

    PopplerAnnot *annot = reinterpret_cast<PopplerAnnot *>(
        poppler_annot_ink_new(doc));
    ASSERT_NE(annot, nullptr);

    // Add to page first so crop_box and page are available
    PopplerRectangle rect = {100, 100, 200, 200};
    poppler_page_add_annot(page, annot);

    PopplerPoint points[] = {{150.0, 150.0}};
    PopplerPath *path = create_path(points, 1);
    PopplerPath *ink_list[] = {path};

    poppler_annot_ink_set_ink_list(POPPLER_ANNOT_INK(annot), ink_list, 1);

    // Verify we can retrieve the ink list back
    GList *result = poppler_annot_ink_get_ink_list(POPPLER_ANNOT_INK(annot));
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(g_list_length(result), 1u);

    // Clean up
    g_list_free_full(result, (GDestroyNotify)poppler_path_free);
    free_path(path);
    g_object_unref(annot);
}

// Test setting ink list with multiple paths
TEST_F(PopplerAnnotInkTest_2131, MultiplePathsMultiplePoints_2131) {
    if (!page) {
        GTEST_SKIP() << "Could not create test document";
    }

    PopplerAnnot *annot = reinterpret_cast<PopplerAnnot *>(
        poppler_annot_ink_new(doc));
    ASSERT_NE(annot, nullptr);

    PopplerRectangle rect = {0, 0, 612, 792};
    poppler_page_add_annot(page, annot);

    PopplerPoint points1[] = {{10.0, 20.0}, {30.0, 40.0}, {50.0, 60.0}};
    PopplerPoint points2[] = {{100.0, 200.0}, {300.0, 400.0}};

    PopplerPath *path1 = create_path(points1, 3);
    PopplerPath *path2 = create_path(points2, 2);
    PopplerPath *ink_list[] = {path1, path2};

    poppler_annot_ink_set_ink_list(POPPLER_ANNOT_INK(annot), ink_list, 2);

    GList *result = poppler_annot_ink_get_ink_list(POPPLER_ANNOT_INK(annot));
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(g_list_length(result), 2u);

    g_list_free_full(result, (GDestroyNotify)poppler_path_free);
    free_path(path1);
    free_path(path2);
    g_object_unref(annot);
}

// Test setting ink list with zero paths
TEST_F(PopplerAnnotInkTest_2131, ZeroPaths_2131) {
    if (!page) {
        GTEST_SKIP() << "Could not create test document";
    }

    PopplerAnnot *annot = reinterpret_cast<PopplerAnnot *>(
        poppler_annot_ink_new(doc));
    ASSERT_NE(annot, nullptr);

    poppler_page_add_annot(page, annot);

    poppler_annot_ink_set_ink_list(POPPLER_ANNOT_INK(annot), nullptr, 0);

    GList *result = poppler_annot_ink_get_ink_list(POPPLER_ANNOT_INK(annot));
    // With zero paths, the ink list should be empty
    EXPECT_EQ(g_list_length(result), 0u);

    if (result) {
        g_list_free_full(result, (GDestroyNotify)poppler_path_free);
    }
    g_object_unref(annot);
}

// Test that the rectangle is updated to encompass all points plus border width
TEST_F(PopplerAnnotInkTest_2131, RectangleUpdatedWithBorderWidth_2131) {
    if (!page) {
        GTEST_SKIP() << "Could not create test document";
    }

    PopplerAnnot *annot = reinterpret_cast<PopplerAnnot *>(
        poppler_annot_ink_new(doc));
    ASSERT_NE(annot, nullptr);

    poppler_page_add_annot(page, annot);

    PopplerPoint points[] = {{100.0, 200.0}, {300.0, 400.0}};
    PopplerPath *path = create_path(points, 2);
    PopplerPath *ink_list[] = {path};

    poppler_annot_ink_set_ink_list(POPPLER_ANNOT_INK(annot), ink_list, 1);

    // Verify the annotation rectangle was set
    PopplerRectangle result_rect;
    poppler_annot_get_rectangle(annot, &result_rect);

    // The rectangle should encompass all points (100,200)-(300,400)
    // adjusted by border width
    // We can at least verify the rectangle is non-zero and reasonable
    EXPECT_LE(result_rect.x1, 100.0);
    EXPECT_LE(result_rect.y1, 200.0);
    EXPECT_GE(result_rect.x2, 300.0);
    EXPECT_GE(result_rect.y2, 400.0);

    free_path(path);
    g_object_unref(annot);
}

// Test replacing an existing ink list with a new one
TEST_F(PopplerAnnotInkTest_2131, ReplaceExistingInkList_2131) {
    if (!page) {
        GTEST_SKIP() << "Could not create test document";
    }

    PopplerAnnot *annot = reinterpret_cast<PopplerAnnot *>(
        poppler_annot_ink_new(doc));
    ASSERT_NE(annot, nullptr);

    poppler_page_add_annot(page, annot);

    // Set first ink list with 2 paths
    PopplerPoint points1[] = {{10.0, 20.0}, {30.0, 40.0}};
    PopplerPoint points2[] = {{50.0, 60.0}, {70.0, 80.0}};
    PopplerPath *path1 = create_path(points1, 2);
    PopplerPath *path2 = create_path(points2, 2);
    PopplerPath *ink_list1[] = {path1, path2};

    poppler_annot_ink_set_ink_list(POPPLER_ANNOT_INK(annot), ink_list1, 2);

    GList *result1 = poppler_annot_ink_get_ink_list(POPPLER_ANNOT_INK(annot));
    EXPECT_EQ(g_list_length(result1), 2u);
    g_list_free_full(result1, (GDestroyNotify)poppler_path_free);

    // Replace with a single path
    PopplerPoint points3[] = {{100.0, 100.0}, {200.0, 200.0}, {300.0, 300.0}};
    PopplerPath *path3 = create_path(points3, 3);
    PopplerPath *ink_list2[] = {path3};

    poppler_annot_ink_set_ink_list(POPPLER_ANNOT_INK(annot), ink_list2, 1);

    GList *result2 = poppler_annot_ink_get_ink_list(POPPLER_ANNOT_INK(annot));
    EXPECT_EQ(g_list_length(result2), 1u);

    g_list_free_full(result2, (GDestroyNotify)poppler_path_free);
    free_path(path1);
    free_path(path2);
    free_path(path3);
    g_object_unref(annot);
}

// Test with large coordinate values
TEST_F(PopplerAnnotInkTest_2131, LargeCoordinates_2131) {
    if (!page) {
        GTEST_SKIP() << "Could not create test document";
    }

    PopplerAnnot *annot = reinterpret_cast<PopplerAnnot *>(
        poppler_annot_ink_new(doc));
    ASSERT_NE(annot, nullptr);

    poppler_page_add_annot(page, annot);

    PopplerPoint points[] = {{1e6, 1e6}, {-1e6, -1e6}};
    PopplerPath *path = create_path(points, 2);
    PopplerPath *ink_list[] = {path};

    poppler_annot_ink_set_ink_list(POPPLER_ANNOT_INK(annot), ink_list, 1);

    GList *result = poppler_annot_ink_get_ink_list(POPPLER_ANNOT_INK(annot));
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(g_list_length(result), 1u);

    g_list_free_full(result, (GDestroyNotify)poppler_path_free);
    free_path(path);
    g_object_unref(annot);
}

// Test with negative coordinates
TEST_F(PopplerAnnotInkTest_2131, NegativeCoordinates_2131) {
    if (!page) {
        GTEST_SKIP() << "Could not create test document";
    }

    PopplerAnnot *annot = reinterpret_cast<PopplerAnnot *>(
        poppler_annot_ink_new(doc));
    ASSERT_NE(annot, nullptr);

    poppler_page_add_annot(page, annot);

    PopplerPoint points[] = {{-50.0, -100.0}, {-10.0, -20.0}};
    PopplerPath *path = create_path(points, 2);
    PopplerPath *ink_list[] = {path};

    poppler_annot_ink_set_ink_list(POPPLER_ANNOT_INK(annot), ink_list, 1);

    PopplerRectangle result_rect;
    poppler_annot_get_rectangle(POPPLER_ANNOT(annot), &result_rect);

    // Rectangle should encompass negative coords, adjusted by border
    EXPECT_LE(result_rect.x1, -50.0);
    EXPECT_LE(result_rect.y1, -100.0);
    EXPECT_GE(result_rect.x2, -10.0);
    EXPECT_GE(result_rect.y2, -20.0);

    GList *result = poppler_annot_ink_get_ink_list(POPPLER_ANNOT_INK(annot));
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(g_list_length(result), 1u);

    g_list_free_full(result, (GDestroyNotify)poppler_path_free);
    free_path(path);
    g_object_unref(annot);
}

// Test that point count in returned paths matches what was set
TEST_F(PopplerAnnotInkTest_2131, PointCountPreserved_2131) {
    if (!page) {
        GTEST_SKIP() << "Could not create test document";
    }

    PopplerAnnot *annot = reinterpret_cast<PopplerAnnot *>(
        poppler_annot_ink_new(doc));
    ASSERT_NE(annot, nullptr);

    poppler_page_add_annot(page, annot);

    PopplerPoint points[] = {
        {10.0, 10.0}, {20.0, 20.0}, {30.0, 30.0},
        {40.0, 40.0}, {50.0, 50.0}
    };
    PopplerPath *path = create_path(points, 5);
    PopplerPath *ink_list[] = {path};

    poppler_annot_ink_set_ink_list(POPPLER_ANNOT_INK(annot), ink_list, 1);

    GList *result = poppler_annot_ink_get_ink_list(POPPLER_ANNOT_INK(annot));
    ASSERT_NE(result, nullptr);
    ASSERT_EQ(g_list_length(result), 1u);

    PopplerPath *result_path = static_cast<PopplerPath *>(g_list_nth_data(result, 0));
    ASSERT_NE(result_path, nullptr);
    EXPECT_EQ(result_path->n_points, 5);

    g_list_free_full(result, (GDestroyNotify)poppler_path_free);
    free_path(path);
    g_object_unref(annot);
}
