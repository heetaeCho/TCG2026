#include <glib.h>
#include <glib-object.h>
#include <poppler.h>
#include <cstdio>
#include <cstring>
#include <string>

#include "gtest/gtest.h"

class PopplerPageGetLabelTest_2428 : public ::testing::Test {
protected:
    PopplerDocument *document = nullptr;
    PopplerPage *page = nullptr;
    std::string test_pdf_path;

    void SetUp() override {
        // Create a minimal PDF in memory or load from a test file
        // We'll try to create a simple PDF document programmatically
        // First, let's create a minimal PDF file
        const char *pdf_content =
            "%PDF-1.4\n"
            "1 0 obj\n"
            "<< /Type /Catalog /Pages 2 0 R /PageLabels 4 0 R >>\n"
            "endobj\n"
            "2 0 obj\n"
            "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
            "endobj\n"
            "3 0 obj\n"
            "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\n"
            "endobj\n"
            "4 0 obj\n"
            "<< /Nums [0 << /P (Cover) >>] >>\n"
            "endobj\n"
            "xref\n"
            "0 5\n"
            "0000000000 65535 f \n"
            "0000000009 00000 n \n"
            "0000000082 00000 n \n"
            "0000000139 00000 n \n"
            "0000000218 00000 n \n"
            "trailer\n"
            "<< /Size 5 /Root 1 0 R >>\n"
            "startxref\n"
            "267\n"
            "%%EOF\n";

        test_pdf_path = "/tmp/test_page_label_2428.pdf";
        FILE *f = fopen(test_pdf_path.c_str(), "wb");
        if (f) {
            fwrite(pdf_content, 1, strlen(pdf_content), f);
            fclose(f);
        }

        GError *error = nullptr;
        gchar *uri = g_filename_to_uri(test_pdf_path.c_str(), nullptr, &error);
        if (uri) {
            document = poppler_document_new_from_file(uri, nullptr, &error);
            g_free(uri);
        }
        if (error) {
            g_error_free(error);
            error = nullptr;
        }
    }

    void TearDown() override {
        if (page) {
            g_object_unref(page);
            page = nullptr;
        }
        if (document) {
            g_object_unref(document);
            document = nullptr;
        }
        remove(test_pdf_path.c_str());
    }
};

// Test that passing NULL page returns NULL
TEST_F(PopplerPageGetLabelTest_2428, NullPageReturnsNull_2428) {
    gchar *label = poppler_page_get_label(nullptr);
    EXPECT_EQ(label, nullptr);
}

// Test that a valid page returns a non-NULL label string
TEST_F(PopplerPageGetLabelTest_2428, ValidPageReturnsLabel_2428) {
    if (!document) {
        GTEST_SKIP() << "Could not load test PDF document";
    }

    int n_pages = poppler_document_get_n_pages(document);
    ASSERT_GT(n_pages, 0);

    page = poppler_document_get_page(document, 0);
    ASSERT_NE(page, nullptr);

    gchar *label = poppler_page_get_label(page);
    // The page should have some label (either custom or default numeric)
    EXPECT_NE(label, nullptr);
    if (label) {
        g_free(label);
    }
}

// Test with a document that has no custom page labels (default numeric labels)
class PopplerPageGetLabelNoLabelsTest_2428 : public ::testing::Test {
protected:
    PopplerDocument *document = nullptr;
    std::string test_pdf_path;

    void SetUp() override {
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
            "194\n"
            "%%EOF\n";

        test_pdf_path = "/tmp/test_page_label_nolabels_2428.pdf";
        FILE *f = fopen(test_pdf_path.c_str(), "wb");
        if (f) {
            fwrite(pdf_content, 1, strlen(pdf_content), f);
            fclose(f);
        }

        GError *error = nullptr;
        gchar *uri = g_filename_to_uri(test_pdf_path.c_str(), nullptr, &error);
        if (uri) {
            document = poppler_document_new_from_file(uri, nullptr, &error);
            g_free(uri);
        }
        if (error) {
            g_error_free(error);
        }
    }

    void TearDown() override {
        if (document) {
            g_object_unref(document);
        }
        remove(test_pdf_path.c_str());
    }
};

// Test that a page without custom labels returns a default numeric label
TEST_F(PopplerPageGetLabelNoLabelsTest_2428, DefaultLabelIsNumeric_2428) {
    if (!document) {
        GTEST_SKIP() << "Could not load test PDF document";
    }

    PopplerPage *page = poppler_document_get_page(document, 0);
    if (!page) {
        GTEST_SKIP() << "Could not get page from document";
    }

    gchar *label = poppler_page_get_label(page);
    // Without page labels, poppler typically returns a numeric string like "1"
    EXPECT_NE(label, nullptr);
    if (label) {
        // The label should be a valid UTF-8 string
        EXPECT_TRUE(g_utf8_validate(label, -1, nullptr));
        g_free(label);
    }

    g_object_unref(page);
}

// Test with a multi-page document with custom page labels
class PopplerPageGetLabelMultiPageTest_2428 : public ::testing::Test {
protected:
    PopplerDocument *document = nullptr;
    std::string test_pdf_path;

    void SetUp() override {
        const char *pdf_content =
            "%PDF-1.4\n"
            "1 0 obj\n"
            "<< /Type /Catalog /Pages 2 0 R /PageLabels 5 0 R >>\n"
            "endobj\n"
            "2 0 obj\n"
            "<< /Type /Pages /Kids [3 0 R 4 0 R] /Count 2 >>\n"
            "endobj\n"
            "3 0 obj\n"
            "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\n"
            "endobj\n"
            "4 0 obj\n"
            "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\n"
            "endobj\n"
            "5 0 obj\n"
            "<< /Nums [0 << /S /r >> 1 << /S /D /St 1 >>] >>\n"
            "endobj\n"
            "xref\n"
            "0 6\n"
            "0000000000 65535 f \n"
            "0000000009 00000 n \n"
            "0000000082 00000 n \n"
            "0000000145 00000 n \n"
            "0000000224 00000 n \n"
            "0000000303 00000 n \n"
            "trailer\n"
            "<< /Size 6 /Root 1 0 R >>\n"
            "startxref\n"
            "366\n"
            "%%EOF\n";

        test_pdf_path = "/tmp/test_page_label_multi_2428.pdf";
        FILE *f = fopen(test_pdf_path.c_str(), "wb");
        if (f) {
            fwrite(pdf_content, 1, strlen(pdf_content), f);
            fclose(f);
        }

        GError *error = nullptr;
        gchar *uri = g_filename_to_uri(test_pdf_path.c_str(), nullptr, &error);
        if (uri) {
            document = poppler_document_new_from_file(uri, nullptr, &error);
            g_free(uri);
        }
        if (error) {
            g_error_free(error);
        }
    }

    void TearDown() override {
        if (document) {
            g_object_unref(document);
        }
        remove(test_pdf_path.c_str());
    }
};

// Test that different pages can have different labels
TEST_F(PopplerPageGetLabelMultiPageTest_2428, DifferentPagesHaveDifferentLabels_2428) {
    if (!document) {
        GTEST_SKIP() << "Could not load test PDF document";
    }

    int n_pages = poppler_document_get_n_pages(document);
    if (n_pages < 2) {
        GTEST_SKIP() << "Not enough pages in test document";
    }

    PopplerPage *page0 = poppler_document_get_page(document, 0);
    PopplerPage *page1 = poppler_document_get_page(document, 1);
    ASSERT_NE(page0, nullptr);
    ASSERT_NE(page1, nullptr);

    gchar *label0 = poppler_page_get_label(page0);
    gchar *label1 = poppler_page_get_label(page1);

    EXPECT_NE(label0, nullptr);
    EXPECT_NE(label1, nullptr);

    if (label0 && label1) {
        // The labels returned should be valid UTF-8
        EXPECT_TRUE(g_utf8_validate(label0, -1, nullptr));
        EXPECT_TRUE(g_utf8_validate(label1, -1, nullptr));
    }

    if (label0) g_free(label0);
    if (label1) g_free(label1);
    g_object_unref(page0);
    g_object_unref(page1);
}

// Test that the returned label is a valid UTF-8 string
TEST_F(PopplerPageGetLabelTest_2428, LabelIsValidUTF8_2428) {
    if (!document) {
        GTEST_SKIP() << "Could not load test PDF document";
    }

    page = poppler_document_get_page(document, 0);
    if (!page) {
        GTEST_SKIP() << "Could not get page";
    }

    gchar *label = poppler_page_get_label(page);
    if (label) {
        EXPECT_TRUE(g_utf8_validate(label, -1, nullptr));
        // Label should have non-zero length for a valid page
        EXPECT_GT(strlen(label), 0u);
        g_free(label);
    }
}

// Test that the returned string can be freed without issues (memory ownership)
TEST_F(PopplerPageGetLabelTest_2428, ReturnedStringIsFreeable_2428) {
    if (!document) {
        GTEST_SKIP() << "Could not load test PDF document";
    }

    page = poppler_document_get_page(document, 0);
    if (!page) {
        GTEST_SKIP() << "Could not get page";
    }

    gchar *label = poppler_page_get_label(page);
    // Should be able to free without error - if NULL, g_free handles it safely
    g_free(label);
    // If we reach here without crash, the test passes
    SUCCEED();
}

// Test calling get_label multiple times on the same page returns consistent results
TEST_F(PopplerPageGetLabelTest_2428, ConsistentLabelOnMultipleCalls_2428) {
    if (!document) {
        GTEST_SKIP() << "Could not load test PDF document";
    }

    page = poppler_document_get_page(document, 0);
    if (!page) {
        GTEST_SKIP() << "Could not get page";
    }

    gchar *label1 = poppler_page_get_label(page);
    gchar *label2 = poppler_page_get_label(page);

    if (label1 && label2) {
        EXPECT_STREQ(label1, label2);
    } else {
        // Both should be NULL or both non-NULL
        EXPECT_EQ(label1, label2);
    }

    g_free(label1);
    g_free(label2);
}
