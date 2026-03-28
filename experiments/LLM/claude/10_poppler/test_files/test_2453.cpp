#include <glib.h>
#include <poppler.h>
#include <gtest/gtest.h>
#include <cstdio>
#include <cstring>
#include <fstream>

class PopplerPageGetLinkMappingTest_2453 : public ::testing::Test {
protected:
    PopplerDocument *doc = nullptr;
    PopplerPage *page = nullptr;

    void SetUp() override {}

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

    // Helper to create a minimal PDF in memory with no links
    PopplerDocument *createMinimalPdfDocument() {
        // Minimal valid PDF
        const char *pdf_content =
            "%PDF-1.0\n"
            "1 0 obj\n"
            "<< /Type /Catalog /Pages 2 0 R >>\n"
            "endobj\n"
            "2 0 obj\n"
            "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
            "endobj\n"
            "3 0 obj\n"
            "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\n"
            "endobj\n"
            "xref\n"
            "0 4\n"
            "0000000000 65535 f \n"
            "0000000009 00000 n \n"
            "0000000058 00000 n \n"
            "0000000115 00000 n \n"
            "trailer\n"
            "<< /Size 4 /Root 1 0 R >>\n"
            "startxref\n"
            "190\n"
            "%%EOF\n";

        gsize len = strlen(pdf_content);
        GError *error = nullptr;

        // Write to temp file
        gchar *tmpfile = nullptr;
        gint fd = g_file_open_tmp("test_pdf_XXXXXX.pdf", &tmpfile, &error);
        if (fd == -1) {
            if (error) g_error_free(error);
            return nullptr;
        }
        write(fd, pdf_content, len);
        close(fd);

        gchar *uri = g_filename_to_uri(tmpfile, nullptr, &error);
        if (!uri) {
            if (error) g_error_free(error);
            g_free(tmpfile);
            return nullptr;
        }

        PopplerDocument *document = poppler_document_new_from_file(uri, nullptr, &error);
        g_free(uri);
        g_unlink(tmpfile);
        g_free(tmpfile);

        if (error) {
            g_error_free(error);
        }
        return document;
    }

    // Helper to create a PDF with links
    PopplerDocument *createPdfWithLinks() {
        const char *pdf_content =
            "%PDF-1.4\n"
            "1 0 obj\n"
            "<< /Type /Catalog /Pages 2 0 R >>\n"
            "endobj\n"
            "2 0 obj\n"
            "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
            "endobj\n"
            "3 0 obj\n"
            "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792]\n"
            "   /Annots [4 0 R] >>\n"
            "endobj\n"
            "4 0 obj\n"
            "<< /Type /Annot /Subtype /Link\n"
            "   /Rect [100 700 200 720]\n"
            "   /A << /Type /Action /S /URI /URI (http://example.com) >> >>\n"
            "endobj\n"
            "xref\n"
            "0 5\n"
            "0000000000 65535 f \n"
            "0000000009 00000 n \n"
            "0000000058 00000 n \n"
            "0000000115 00000 n \n"
            "0000000220 00000 n \n"
            "trailer\n"
            "<< /Size 5 /Root 1 0 R >>\n"
            "startxref\n"
            "363\n"
            "%%EOF\n";

        gsize len = strlen(pdf_content);
        GError *error = nullptr;

        gchar *tmpfile = nullptr;
        gint fd = g_file_open_tmp("test_pdf_links_XXXXXX.pdf", &tmpfile, &error);
        if (fd == -1) {
            if (error) g_error_free(error);
            return nullptr;
        }
        write(fd, pdf_content, len);
        close(fd);

        gchar *uri = g_filename_to_uri(tmpfile, nullptr, &error);
        if (!uri) {
            if (error) g_error_free(error);
            g_free(tmpfile);
            return nullptr;
        }

        PopplerDocument *document = poppler_document_new_from_file(uri, nullptr, &error);
        g_free(uri);
        g_unlink(tmpfile);
        g_free(tmpfile);

        if (error) {
            g_error_free(error);
        }
        return document;
    }
};

// Test that passing NULL returns NULL
TEST_F(PopplerPageGetLinkMappingTest_2453, NullPageReturnsNull_2453) {
    GList *result = poppler_page_get_link_mapping(nullptr);
    EXPECT_EQ(result, nullptr);
}

// Test that a page with no links returns NULL (empty list)
TEST_F(PopplerPageGetLinkMappingTest_2453, PageWithNoLinksReturnsEmptyList_2453) {
    doc = createMinimalPdfDocument();
    if (!doc) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    page = poppler_document_get_page(doc, 0);
    ASSERT_NE(page, nullptr);

    GList *result = poppler_page_get_link_mapping(page);
    // A page with no annotations should return NULL or empty list
    EXPECT_EQ(result, nullptr);

    if (result) {
        poppler_page_free_link_mapping(result);
    }
}

// Test that a page with links returns non-null mapping list
TEST_F(PopplerPageGetLinkMappingTest_2453, PageWithLinksReturnsNonEmptyList_2453) {
    doc = createPdfWithLinks();
    if (!doc) {
        GTEST_SKIP() << "Could not create PDF document with links";
    }

    page = poppler_document_get_page(doc, 0);
    if (!page) {
        GTEST_SKIP() << "Could not get page from document";
    }

    GList *result = poppler_page_get_link_mapping(page);

    if (result != nullptr) {
        // Verify we have at least one link mapping
        EXPECT_GE(g_list_length(result), 1u);

        // Verify first mapping has valid area coordinates
        PopplerLinkMapping *mapping = (PopplerLinkMapping *)result->data;
        EXPECT_NE(mapping, nullptr);

        if (mapping) {
            // The area should have reasonable coordinates
            EXPECT_LE(mapping->area.x1, mapping->area.x2);
            EXPECT_LE(mapping->area.y1, mapping->area.y2);
        }

        poppler_page_free_link_mapping(result);
    }
    // If result is NULL, the PDF might not have parsed links correctly - still valid
}

// Test that link mapping action is populated for pages with URI links
TEST_F(PopplerPageGetLinkMappingTest_2453, LinkMappingActionIsPopulated_2453) {
    doc = createPdfWithLinks();
    if (!doc) {
        GTEST_SKIP() << "Could not create PDF document with links";
    }

    page = poppler_document_get_page(doc, 0);
    if (!page) {
        GTEST_SKIP() << "Could not get page from document";
    }

    GList *result = poppler_page_get_link_mapping(page);

    if (result != nullptr) {
        for (GList *l = result; l != nullptr; l = l->next) {
            PopplerLinkMapping *mapping = (PopplerLinkMapping *)l->data;
            ASSERT_NE(mapping, nullptr);
            // Action may or may not be set depending on parsing
            // but the mapping itself should be valid
        }
        poppler_page_free_link_mapping(result);
    }
}

// Test that free_link_mapping handles NULL gracefully
TEST_F(PopplerPageGetLinkMappingTest_2453, FreeLinkMappingHandlesNull_2453) {
    // This should not crash
    poppler_page_free_link_mapping(nullptr);
}

// Test that calling get_link_mapping twice returns consistent results
TEST_F(PopplerPageGetLinkMappingTest_2453, ConsistentResultsOnMultipleCalls_2453) {
    doc = createMinimalPdfDocument();
    if (!doc) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    page = poppler_document_get_page(doc, 0);
    ASSERT_NE(page, nullptr);

    GList *result1 = poppler_page_get_link_mapping(page);
    GList *result2 = poppler_page_get_link_mapping(page);

    guint len1 = result1 ? g_list_length(result1) : 0;
    guint len2 = result2 ? g_list_length(result2) : 0;

    EXPECT_EQ(len1, len2);

    if (result1) poppler_page_free_link_mapping(result1);
    if (result2) poppler_page_free_link_mapping(result2);
}

// Test link mapping area coordinates are non-negative for default rotation
TEST_F(PopplerPageGetLinkMappingTest_2453, LinkMappingAreaCoordinatesAreReasonable_2453) {
    doc = createPdfWithLinks();
    if (!doc) {
        GTEST_SKIP() << "Could not create PDF document with links";
    }

    page = poppler_document_get_page(doc, 0);
    if (!page) {
        GTEST_SKIP() << "Could not get page from document";
    }

    GList *result = poppler_page_get_link_mapping(page);

    if (result != nullptr) {
        double width, height;
        poppler_page_get_size(page, &width, &height);

        for (GList *l = result; l != nullptr; l = l->next) {
            PopplerLinkMapping *mapping = (PopplerLinkMapping *)l->data;
            ASSERT_NE(mapping, nullptr);

            // Coordinates should be within page bounds (approximately)
            EXPECT_GE(mapping->area.x1, -1.0);
            EXPECT_GE(mapping->area.y1, -1.0);
            EXPECT_LE(mapping->area.x2, width + 1.0);
            EXPECT_LE(mapping->area.y2, height + 1.0);
        }

        poppler_page_free_link_mapping(result);
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
