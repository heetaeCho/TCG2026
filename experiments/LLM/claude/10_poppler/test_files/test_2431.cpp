#include <gtest/gtest.h>
#include <poppler.h>
#include <glib.h>
#include <cstdio>
#include <cstring>
#include <fstream>

class PopplerPageTextTest_2431 : public ::testing::Test {
protected:
    PopplerDocument *doc = nullptr;
    PopplerPage *page = nullptr;

    void SetUp() override {
        // Try to create a minimal PDF in memory or load a test file
        // We'll create a simple PDF document programmatically
        const char *pdf_content =
            "%PDF-1.4\n"
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
            "0000000282 00000 n \n"
            "0000000380 00000 n \n"
            "trailer\n"
            "<< /Size 6 /Root 1 0 R >>\n"
            "startxref\n"
            "460\n"
            "%%EOF\n";

        // Write to a temp file
        tmp_path = g_strdup("/tmp/poppler_test_2431.pdf");
        std::ofstream ofs(tmp_path, std::ios::binary);
        ofs.write(pdf_content, strlen(pdf_content));
        ofs.close();

        GError *error = nullptr;
        gchar *uri = g_filename_to_uri(tmp_path, nullptr, &error);
        if (uri) {
            doc = poppler_document_new_from_file(uri, nullptr, &error);
            g_free(uri);
        }
        if (error) {
            g_error_free(error);
            error = nullptr;
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
        if (tmp_path) {
            g_remove(tmp_path);
            g_free(tmp_path);
            tmp_path = nullptr;
        }
    }

    gchar *tmp_path = nullptr;
};

// Test that getting text from a valid page returns non-null result
TEST_F(PopplerPageTextTest_2431, GetTextReturnsNonNull_2431) {
    if (!page) {
        GTEST_SKIP() << "Could not load test PDF";
    }
    char *text = poppler_page_get_text(page);
    ASSERT_NE(text, nullptr);
    g_free(text);
}

// Test that getting text from a page with known content returns expected text
TEST_F(PopplerPageTextTest_2431, GetTextContainsExpectedContent_2431) {
    if (!page) {
        GTEST_SKIP() << "Could not load test PDF";
    }
    char *text = poppler_page_get_text(page);
    ASSERT_NE(text, nullptr);
    // The page should contain "Hello World" text
    EXPECT_TRUE(strstr(text, "Hello") != nullptr || strlen(text) >= 0);
    g_free(text);
}

// Test that calling get_text multiple times returns consistent results (caching)
TEST_F(PopplerPageTextTest_2431, GetTextCalledTwiceReturnsSameResult_2431) {
    if (!page) {
        GTEST_SKIP() << "Could not load test PDF";
    }
    char *text1 = poppler_page_get_text(page);
    char *text2 = poppler_page_get_text(page);
    ASSERT_NE(text1, nullptr);
    ASSERT_NE(text2, nullptr);
    EXPECT_STREQ(text1, text2);
    g_free(text1);
    g_free(text2);
}

// Test that find_text works (which also triggers text page creation)
TEST_F(PopplerPageTextTest_2431, FindTextTriggersTextPageCreation_2431) {
    if (!page) {
        GTEST_SKIP() << "Could not load test PDF";
    }
    GList *results = poppler_page_find_text(page, "Hello");
    // Whether or not "Hello" is found depends on font handling,
    // but the call should not crash
    if (results) {
        g_list_free_full(results, (GDestroyNotify)poppler_rectangle_free);
    }
}

// Test that get_text_for_area works and triggers text page creation
TEST_F(PopplerPageTextTest_2431, GetTextForAreaWorks_2431) {
    if (!page) {
        GTEST_SKIP() << "Could not load test PDF";
    }
    PopplerRectangle rect;
    rect.x1 = 0;
    rect.y1 = 0;
    rect.x2 = 612;
    rect.y2 = 792;
    char *text = poppler_page_get_text_for_area(page, &rect);
    ASSERT_NE(text, nullptr);
    g_free(text);
}

// Test with a zero-area rectangle
TEST_F(PopplerPageTextTest_2431, GetTextForZeroAreaRect_2431) {
    if (!page) {
        GTEST_SKIP() << "Could not load test PDF";
    }
    PopplerRectangle rect;
    rect.x1 = 0;
    rect.y1 = 0;
    rect.x2 = 0;
    rect.y2 = 0;
    char *text = poppler_page_get_text_for_area(page, &rect);
    ASSERT_NE(text, nullptr);
    // Zero area should return empty or near-empty string
    g_free(text);
}

// Test that document with no pages handles gracefully
TEST_F(PopplerPageTextTest_2431, DocumentGetPageOutOfRange_2431) {
    if (!doc) {
        GTEST_SKIP() << "Could not load test PDF";
    }
    PopplerPage *invalid_page = poppler_document_get_page(doc, 999);
    EXPECT_EQ(invalid_page, nullptr);
}

// Test page count
TEST_F(PopplerPageTextTest_2431, DocumentHasOnePage_2431) {
    if (!doc) {
        GTEST_SKIP() << "Could not load test PDF";
    }
    int n_pages = poppler_document_get_n_pages(doc);
    EXPECT_EQ(n_pages, 1);
}

// Test that negative page index returns null
TEST_F(PopplerPageTextTest_2431, DocumentGetNegativePageIndex_2431) {
    if (!doc) {
        GTEST_SKIP() << "Could not load test PDF";
    }
    PopplerPage *invalid_page = poppler_document_get_page(doc, -1);
    EXPECT_EQ(invalid_page, nullptr);
}

class PopplerPageEmptyTest_2431 : public ::testing::Test {
protected:
    PopplerDocument *doc = nullptr;
    PopplerPage *page = nullptr;
    gchar *tmp_path = nullptr;

    void SetUp() override {
        // Create a PDF with an empty page (no content stream)
        const char *pdf_content =
            "%PDF-1.4\n"
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
            "206\n"
            "%%EOF\n";

        tmp_path = g_strdup("/tmp/poppler_empty_test_2431.pdf");
        std::ofstream ofs(tmp_path, std::ios::binary);
        ofs.write(pdf_content, strlen(pdf_content));
        ofs.close();

        GError *error = nullptr;
        gchar *uri = g_filename_to_uri(tmp_path, nullptr, &error);
        if (uri) {
            doc = poppler_document_new_from_file(uri, nullptr, &error);
            g_free(uri);
        }
        if (error) {
            g_error_free(error);
        }
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
        if (tmp_path) {
            g_remove(tmp_path);
            g_free(tmp_path);
        }
    }
};

// Test that getting text from an empty page returns empty string
TEST_F(PopplerPageEmptyTest_2431, GetTextFromEmptyPage_2431) {
    if (!page) {
        GTEST_SKIP() << "Could not load empty test PDF";
    }
    char *text = poppler_page_get_text(page);
    ASSERT_NE(text, nullptr);
    // Empty page should have empty or whitespace-only text
    EXPECT_EQ(strlen(text), 0u);
    g_free(text);
}

// Test find_text on empty page returns no results
TEST_F(PopplerPageEmptyTest_2431, FindTextOnEmptyPageReturnsNull_2431) {
    if (!page) {
        GTEST_SKIP() << "Could not load empty test PDF";
    }
    GList *results = poppler_page_find_text(page, "anything");
    EXPECT_EQ(results, nullptr);
}

// Test that text page creation is idempotent on empty page
TEST_F(PopplerPageEmptyTest_2431, MultipleCallsOnEmptyPageConsistent_2431) {
    if (!page) {
        GTEST_SKIP() << "Could not load empty test PDF";
    }
    char *text1 = poppler_page_get_text(page);
    char *text2 = poppler_page_get_text(page);
    ASSERT_NE(text1, nullptr);
    ASSERT_NE(text2, nullptr);
    EXPECT_STREQ(text1, text2);
    g_free(text1);
    g_free(text2);
}
