#include <glib.h>
#include <poppler.h>
#include <gtest/gtest.h>
#include <cstring>
#include <cstdio>

class PopplerPageAddAnnotTest_2461 : public ::testing::Test {
protected:
    PopplerDocument *doc = nullptr;
    PopplerPage *page = nullptr;
    gchar *uri = nullptr;

    void SetUp() override {
        // Create a minimal PDF in memory to work with
        // We need a real PDF document to get a PopplerPage
        const char *pdf_content =
            "%PDF-1.4\n"
            "1 0 obj\n"
            "<< /Type /Catalog /Pages 2 0 R >>\n"
            "endobj\n"
            "2 0 obj\n"
            "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
            "endobj\n"
            "3 0 obj\n"
            "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] /Contents 4 0 R /Resources << >> >>\n"
            "endobj\n"
            "4 0 obj\n"
            "<< /Length 0 >>\n"
            "stream\n"
            "endstream\n"
            "endobj\n"
            "xref\n"
            "0 5\n"
            "0000000000 65535 f \n"
            "0000000009 00000 n \n"
            "0000000058 00000 n \n"
            "0000000115 00000 n \n"
            "0000000240 00000 n \n"
            "trailer\n"
            "<< /Size 5 /Root 1 0 R >>\n"
            "startxref\n"
            "297\n"
            "%%EOF\n";

        // Write to a temp file
        gchar *tmp_path = nullptr;
        GError *error = nullptr;
        gint fd = g_file_open_tmp("poppler_test_XXXXXX.pdf", &tmp_path, &error);
        if (fd >= 0) {
            size_t len = strlen(pdf_content);
            write(fd, pdf_content, len);
            close(fd);

            uri = g_filename_to_uri(tmp_path, nullptr, &error);
            if (uri) {
                doc = poppler_document_new_from_file(uri, nullptr, &error);
            }
            if (error) {
                g_error_free(error);
                error = nullptr;
            }
            g_free(tmp_path);
        }

        if (doc) {
            page = poppler_document_get_page(doc, 0);
        }
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
        if (uri) {
            // Clean up temp file
            gchar *path = g_filename_from_uri(uri, nullptr, nullptr);
            if (path) {
                g_unlink(path);
                g_free(path);
            }
            g_free(uri);
            uri = nullptr;
        }
    }

    PopplerAnnot* createTextAnnot(PopplerRectangle *rect) {
        return poppler_annot_text_new(doc, rect);
    }
};

// Test that adding a valid text annotation to a page does not crash
TEST_F(PopplerPageAddAnnotTest_2461, AddTextAnnotToPage_2461) {
    if (!page || !doc) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PopplerRectangle rect;
    rect.x1 = 100.0;
    rect.y1 = 100.0;
    rect.x2 = 200.0;
    rect.y2 = 200.0;

    PopplerAnnot *annot = createTextAnnot(&rect);
    ASSERT_NE(annot, nullptr);

    // Should not crash
    poppler_page_add_annot(page, annot);

    // Verify the annotation was added by checking the annot mapping list
    GList *annot_mappings = poppler_page_get_annot_mapping(page);
    EXPECT_NE(annot_mappings, nullptr);

    gboolean found = FALSE;
    for (GList *l = annot_mappings; l != nullptr; l = l->next) {
        PopplerAnnotMapping *mapping = (PopplerAnnotMapping *)l->data;
        if (mapping && mapping->annot) {
            PopplerAnnotType type = poppler_annot_get_annot_type(mapping->annot);
            if (type == POPPLER_ANNOT_TEXT) {
                found = TRUE;
                break;
            }
        }
    }
    EXPECT_TRUE(found);

    poppler_page_free_annot_mapping(annot_mappings);
    g_object_unref(annot);
}

// Test adding annotation with zero-sized rectangle
TEST_F(PopplerPageAddAnnotTest_2461, AddAnnotWithZeroRect_2461) {
    if (!page || !doc) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PopplerRectangle rect;
    rect.x1 = 0.0;
    rect.y1 = 0.0;
    rect.x2 = 0.0;
    rect.y2 = 0.0;

    PopplerAnnot *annot = createTextAnnot(&rect);
    ASSERT_NE(annot, nullptr);

    // Should not crash even with zero rect
    poppler_page_add_annot(page, annot);

    g_object_unref(annot);
}

// Test adding annotation at page boundary coordinates
TEST_F(PopplerPageAddAnnotTest_2461, AddAnnotAtPageBoundary_2461) {
    if (!page || !doc) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    double width, height;
    poppler_page_get_size(page, &width, &height);

    PopplerRectangle rect;
    rect.x1 = width - 10.0;
    rect.y1 = height - 10.0;
    rect.x2 = width;
    rect.y2 = height;

    PopplerAnnot *annot = createTextAnnot(&rect);
    ASSERT_NE(annot, nullptr);

    poppler_page_add_annot(page, annot);

    GList *annot_mappings = poppler_page_get_annot_mapping(page);
    EXPECT_NE(annot_mappings, nullptr);

    poppler_page_free_annot_mapping(annot_mappings);
    g_object_unref(annot);
}

// Test adding multiple annotations to the same page
TEST_F(PopplerPageAddAnnotTest_2461, AddMultipleAnnotsToPage_2461) {
    if (!page || !doc) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PopplerRectangle rect1 = { 10.0, 10.0, 50.0, 50.0 };
    PopplerRectangle rect2 = { 100.0, 100.0, 150.0, 150.0 };
    PopplerRectangle rect3 = { 200.0, 200.0, 250.0, 250.0 };

    PopplerAnnot *annot1 = createTextAnnot(&rect1);
    PopplerAnnot *annot2 = createTextAnnot(&rect2);
    PopplerAnnot *annot3 = createTextAnnot(&rect3);

    ASSERT_NE(annot1, nullptr);
    ASSERT_NE(annot2, nullptr);
    ASSERT_NE(annot3, nullptr);

    poppler_page_add_annot(page, annot1);
    poppler_page_add_annot(page, annot2);
    poppler_page_add_annot(page, annot3);

    GList *annot_mappings = poppler_page_get_annot_mapping(page);
    int text_annot_count = 0;
    for (GList *l = annot_mappings; l != nullptr; l = l->next) {
        PopplerAnnotMapping *mapping = (PopplerAnnotMapping *)l->data;
        if (mapping && mapping->annot) {
            if (poppler_annot_get_annot_type(mapping->annot) == POPPLER_ANNOT_TEXT) {
                text_annot_count++;
            }
        }
    }
    EXPECT_GE(text_annot_count, 3);

    poppler_page_free_annot_mapping(annot_mappings);
    g_object_unref(annot1);
    g_object_unref(annot2);
    g_object_unref(annot3);
}

// Test that passing NULL page is handled gracefully (g_return_if_fail)
TEST_F(PopplerPageAddAnnotTest_2461, NullPageDoesNotCrash_2461) {
    if (!doc) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PopplerRectangle rect = { 10.0, 10.0, 50.0, 50.0 };
    PopplerAnnot *annot = createTextAnnot(&rect);
    ASSERT_NE(annot, nullptr);

    // Should return without crashing due to g_return_if_fail
    poppler_page_add_annot(nullptr, annot);

    g_object_unref(annot);
}

// Test that passing NULL annot is handled gracefully (g_return_if_fail)
TEST_F(PopplerPageAddAnnotTest_2461, NullAnnotDoesNotCrash_2461) {
    if (!page) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    // Should return without crashing due to g_return_if_fail
    poppler_page_add_annot(page, nullptr);
}

// Test adding annotation with negative coordinates
TEST_F(PopplerPageAddAnnotTest_2461, AddAnnotWithNegativeCoords_2461) {
    if (!page || !doc) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PopplerRectangle rect;
    rect.x1 = -50.0;
    rect.y1 = -50.0;
    rect.x2 = -10.0;
    rect.y2 = -10.0;

    PopplerAnnot *annot = createTextAnnot(&rect);
    ASSERT_NE(annot, nullptr);

    // Should not crash
    poppler_page_add_annot(page, annot);

    g_object_unref(annot);
}

// Test adding annotation with large coordinates
TEST_F(PopplerPageAddAnnotTest_2461, AddAnnotWithLargeCoords_2461) {
    if (!page || !doc) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PopplerRectangle rect;
    rect.x1 = 10000.0;
    rect.y1 = 10000.0;
    rect.x2 = 20000.0;
    rect.y2 = 20000.0;

    PopplerAnnot *annot = createTextAnnot(&rect);
    ASSERT_NE(annot, nullptr);

    poppler_page_add_annot(page, annot);

    g_object_unref(annot);
}

// Test adding an annotation and verifying it appears in annotation count
TEST_F(PopplerPageAddAnnotTest_2461, AnnotCountIncreasesAfterAdd_2461) {
    if (!page || !doc) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    GList *annot_mappings_before = poppler_page_get_annot_mapping(page);
    int count_before = g_list_length(annot_mappings_before);
    poppler_page_free_annot_mapping(annot_mappings_before);

    PopplerRectangle rect = { 50.0, 50.0, 100.0, 100.0 };
    PopplerAnnot *annot = createTextAnnot(&rect);
    ASSERT_NE(annot, nullptr);

    poppler_page_add_annot(page, annot);

    GList *annot_mappings_after = poppler_page_get_annot_mapping(page);
    int count_after = g_list_length(annot_mappings_after);
    poppler_page_free_annot_mapping(annot_mappings_after);

    EXPECT_EQ(count_after, count_before + 1);

    g_object_unref(annot);
}

// Test adding annotation with swapped coordinates (x1 > x2, y1 > y2)
TEST_F(PopplerPageAddAnnotTest_2461, AddAnnotWithSwappedCoords_2461) {
    if (!page || !doc) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PopplerRectangle rect;
    rect.x1 = 200.0;
    rect.y1 = 200.0;
    rect.x2 = 100.0;
    rect.y2 = 100.0;

    PopplerAnnot *annot = createTextAnnot(&rect);
    ASSERT_NE(annot, nullptr);

    // Should not crash even with inverted coordinates
    poppler_page_add_annot(page, annot);

    g_object_unref(annot);
}

// Test adding annotation at origin (0,0) to small rect
TEST_F(PopplerPageAddAnnotTest_2461, AddAnnotAtOrigin_2461) {
    if (!page || !doc) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PopplerRectangle rect;
    rect.x1 = 0.0;
    rect.y1 = 0.0;
    rect.x2 = 1.0;
    rect.y2 = 1.0;

    PopplerAnnot *annot = createTextAnnot(&rect);
    ASSERT_NE(annot, nullptr);

    poppler_page_add_annot(page, annot);

    GList *annot_mappings = poppler_page_get_annot_mapping(page);
    EXPECT_NE(annot_mappings, nullptr);

    poppler_page_free_annot_mapping(annot_mappings);
    g_object_unref(annot);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
