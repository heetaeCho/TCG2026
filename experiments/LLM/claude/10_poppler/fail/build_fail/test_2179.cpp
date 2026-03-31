#include <glib.h>
#include <glib-object.h>
#include <gtest/gtest.h>
#include <poppler-document.h>
#include <poppler.h>
#include <cstring>
#include <cstdio>

class PopplerDocumentSetKeywordsTest_2179 : public ::testing::Test {
protected:
    PopplerDocument *document = nullptr;

    void SetUp() override {
        // Create a minimal valid PDF in memory to get a PopplerDocument
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
            "190\n"
            "%%EOF\n";

        // Write to a temporary file
        tmp_file = g_strdup("/tmp/test_poppler_keywords_2179.pdf");
        FILE *f = fopen(tmp_file, "wb");
        if (f) {
            fwrite(pdf_content, 1, strlen(pdf_content), f);
            fclose(f);
        }

        GError *error = nullptr;
        gchar *uri = g_filename_to_uri(tmp_file, nullptr, &error);
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
            document = nullptr;
        }
        if (tmp_file) {
            g_remove(tmp_file);
            g_free(tmp_file);
            tmp_file = nullptr;
        }
    }

    gchar *tmp_file = nullptr;
};

// Test setting keywords with a normal ASCII string
TEST_F(PopplerDocumentSetKeywordsTest_2179, SetNormalKeywords_2179) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }

    const gchar *keywords = "test, keywords, poppler";
    poppler_document_set_keywords(document, keywords);

    gchar *retrieved = poppler_document_get_keywords(document);
    ASSERT_NE(retrieved, nullptr);
    EXPECT_STREQ(retrieved, keywords);
    g_free(retrieved);
}

// Test setting keywords to NULL (clearing keywords)
TEST_F(PopplerDocumentSetKeywordsTest_2179, SetNullKeywords_2179) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }

    // First set some keywords
    poppler_document_set_keywords(document, "initial keywords");

    // Now set to NULL to clear
    poppler_document_set_keywords(document, nullptr);

    gchar *retrieved = poppler_document_get_keywords(document);
    // After setting NULL, keywords should be cleared (NULL or empty)
    if (retrieved) {
        EXPECT_STREQ(retrieved, "");
        g_free(retrieved);
    }
    // If NULL is returned, that's also acceptable (keywords cleared)
}

// Test setting keywords with an empty string
TEST_F(PopplerDocumentSetKeywordsTest_2179, SetEmptyKeywords_2179) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }

    poppler_document_set_keywords(document, "");

    gchar *retrieved = poppler_document_get_keywords(document);
    if (retrieved) {
        EXPECT_STREQ(retrieved, "");
        g_free(retrieved);
    }
}

// Test setting keywords with UTF-8 content
TEST_F(PopplerDocumentSetKeywordsTest_2179, SetUTF8Keywords_2179) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }

    const gchar *utf8_keywords = "ключевые, слова, テスト";
    poppler_document_set_keywords(document, utf8_keywords);

    gchar *retrieved = poppler_document_get_keywords(document);
    ASSERT_NE(retrieved, nullptr);
    EXPECT_STREQ(retrieved, utf8_keywords);
    g_free(retrieved);
}

// Test setting keywords multiple times (overwriting)
TEST_F(PopplerDocumentSetKeywordsTest_2179, SetKeywordsMultipleTimes_2179) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }

    poppler_document_set_keywords(document, "first set of keywords");
    poppler_document_set_keywords(document, "second set of keywords");

    gchar *retrieved = poppler_document_get_keywords(document);
    ASSERT_NE(retrieved, nullptr);
    EXPECT_STREQ(retrieved, "second set of keywords");
    g_free(retrieved);
}

// Test that passing a non-document (NULL) does not crash (g_return_if_fail should handle it)
TEST_F(PopplerDocumentSetKeywordsTest_2179, SetKeywordsOnNullDocument_2179) {
    // This should not crash due to g_return_if_fail
    // We suppress the GLib critical warning for this test
    g_test_expect_message("GLib-GObject", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_DOCUMENT*");
    poppler_document_set_keywords(nullptr, "some keywords");
    g_test_assert_expected_messages();
}

// Test setting keywords with a long string
TEST_F(PopplerDocumentSetKeywordsTest_2179, SetLongKeywords_2179) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }

    // Create a long keywords string
    std::string long_keywords(10000, 'a');
    for (size_t i = 100; i < long_keywords.size(); i += 100) {
        long_keywords[i] = ',';
    }

    poppler_document_set_keywords(document, long_keywords.c_str());

    gchar *retrieved = poppler_document_get_keywords(document);
    ASSERT_NE(retrieved, nullptr);
    EXPECT_STREQ(retrieved, long_keywords.c_str());
    g_free(retrieved);
}

// Test setting keywords with special characters
TEST_F(PopplerDocumentSetKeywordsTest_2179, SetKeywordsWithSpecialChars_2179) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }

    const gchar *special_keywords = "key1; key2 & key3 <tag> \"quoted\"";
    poppler_document_set_keywords(document, special_keywords);

    gchar *retrieved = poppler_document_get_keywords(document);
    ASSERT_NE(retrieved, nullptr);
    EXPECT_STREQ(retrieved, special_keywords);
    g_free(retrieved);
}

// Test set then clear then set again
TEST_F(PopplerDocumentSetKeywordsTest_2179, SetClearSetKeywords_2179) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }

    poppler_document_set_keywords(document, "initial");
    poppler_document_set_keywords(document, nullptr);
    poppler_document_set_keywords(document, "final keywords");

    gchar *retrieved = poppler_document_get_keywords(document);
    ASSERT_NE(retrieved, nullptr);
    EXPECT_STREQ(retrieved, "final keywords");
    g_free(retrieved);
}
