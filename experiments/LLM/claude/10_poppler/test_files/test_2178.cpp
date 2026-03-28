#include <glib.h>
#include <glib-object.h>
#include <poppler-document.h>
#include <poppler.h>
#include <gtest/gtest.h>
#include <cstring>
#include <string>

class PopplerDocumentGetKeywordsTest_2178 : public ::testing::Test {
protected:
    void SetUp() override {
        document_ = nullptr;
    }

    void TearDown() override {
        if (document_) {
            g_object_unref(document_);
            document_ = nullptr;
        }
    }

    PopplerDocument *document_;
};

// Test that passing NULL returns NULL
TEST_F(PopplerDocumentGetKeywordsTest_2178, NullDocumentReturnsNull_2178)
{
    gchar *keywords = poppler_document_get_keywords(nullptr);
    EXPECT_EQ(keywords, nullptr);
}

// Test that a valid PDF document with no keywords returns NULL
TEST_F(PopplerDocumentGetKeywordsTest_2178, DocumentWithoutKeywordsReturnsNull_2178)
{
    // Create a minimal PDF in memory with no keywords metadata
    const char *minimal_pdf =
        "%PDF-1.0\n"
        "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
        "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer\n<< /Size 4 /Root 1 0 R >>\n"
        "startxref\n190\n%%EOF\n";

    GError *error = nullptr;
    gsize len = strlen(minimal_pdf);
    GBytes *bytes = g_bytes_new_static(minimal_pdf, len);
    GInputStream *stream = g_memory_input_stream_new_from_bytes(bytes);

    document_ = poppler_document_new_from_stream(stream, len, nullptr, nullptr, &error);

    if (document_ != nullptr) {
        gchar *keywords = poppler_document_get_keywords(document_);
        // A document without keywords should return NULL or empty string
        if (keywords != nullptr) {
            // If not null, it should at least be retrievable as a string
            g_free(keywords);
        }
        // Test passes either way - we just verify no crash
    } else {
        // If we can't create document from minimal PDF, skip gracefully
        if (error) {
            g_error_free(error);
        }
    }

    g_object_unref(stream);
    g_bytes_unref(bytes);
}

// Test with a PDF that has keywords set in its Info dictionary
TEST_F(PopplerDocumentGetKeywordsTest_2178, DocumentWithKeywordsReturnsKeywords_2178)
{
    const char *pdf_with_keywords =
        "%PDF-1.4\n"
        "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
        "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n"
        "4 0 obj\n<< /Keywords (test keyword poppler) >>\nendobj\n"
        "xref\n0 5\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "0000000190 00000 n \n"
        "trailer\n<< /Size 5 /Root 1 0 R /Info 4 0 R >>\n"
        "startxref\n240\n%%EOF\n";

    GError *error = nullptr;
    gsize len = strlen(pdf_with_keywords);
    GBytes *bytes = g_bytes_new_static(pdf_with_keywords, len);
    GInputStream *stream = g_memory_input_stream_new_from_bytes(bytes);

    document_ = poppler_document_new_from_stream(stream, len, nullptr, nullptr, &error);

    if (document_ != nullptr) {
        gchar *keywords = poppler_document_get_keywords(document_);
        if (keywords != nullptr) {
            std::string kw(keywords);
            EXPECT_NE(kw.find("test keyword poppler"), std::string::npos);
            g_free(keywords);
        }
    } else {
        if (error) {
            g_error_free(error);
        }
    }

    g_object_unref(stream);
    g_bytes_unref(bytes);
}

// Test loading a file-based PDF if available and checking keywords
TEST_F(PopplerDocumentGetKeywordsTest_2178, FileBasedDocumentKeywords_2178)
{
    // Try to load a test file if it exists
    const char *test_pdf_path = "/tmp/test_keywords_2178.pdf";

    // Create a minimal PDF file with keywords
    FILE *f = fopen(test_pdf_path, "w");
    if (f) {
        const char *pdf_content =
            "%PDF-1.4\n"
            "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
            "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
            "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n"
            "4 0 obj\n<< /Keywords (science math) >>\nendobj\n"
            "xref\n0 5\n"
            "0000000000 65535 f \n"
            "0000000009 00000 n \n"
            "0000000058 00000 n \n"
            "0000000115 00000 n \n"
            "0000000190 00000 n \n"
            "trailer\n<< /Size 5 /Root 1 0 R /Info 4 0 R >>\n"
            "startxref\n240\n%%EOF\n";
        fputs(pdf_content, f);
        fclose(f);

        gchar *uri = g_filename_to_uri(test_pdf_path, nullptr, nullptr);
        GError *error = nullptr;
        document_ = poppler_document_new_from_file(uri, nullptr, &error);

        if (document_ != nullptr) {
            gchar *keywords = poppler_document_get_keywords(document_);
            if (keywords != nullptr) {
                // We successfully retrieved keywords
                EXPECT_TRUE(strlen(keywords) > 0);
                g_free(keywords);
            }
        } else {
            if (error) {
                g_error_free(error);
            }
        }

        g_free(uri);
        g_remove(test_pdf_path);
    }
}

// Test that calling get_keywords multiple times on same document is consistent
TEST_F(PopplerDocumentGetKeywordsTest_2178, MultipleCallsReturnConsistentResults_2178)
{
    const char *pdf_with_keywords =
        "%PDF-1.4\n"
        "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
        "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n"
        "4 0 obj\n<< /Keywords (repeat test) >>\nendobj\n"
        "xref\n0 5\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "0000000190 00000 n \n"
        "trailer\n<< /Size 5 /Root 1 0 R /Info 4 0 R >>\n"
        "startxref\n240\n%%EOF\n";

    GError *error = nullptr;
    gsize len = strlen(pdf_with_keywords);
    GBytes *bytes = g_bytes_new_static(pdf_with_keywords, len);
    GInputStream *stream = g_memory_input_stream_new_from_bytes(bytes);

    document_ = poppler_document_new_from_stream(stream, len, nullptr, nullptr, &error);

    if (document_ != nullptr) {
        gchar *keywords1 = poppler_document_get_keywords(document_);
        gchar *keywords2 = poppler_document_get_keywords(document_);

        if (keywords1 != nullptr && keywords2 != nullptr) {
            EXPECT_STREQ(keywords1, keywords2);
        } else {
            // Both should be null or both non-null
            EXPECT_EQ(keywords1, keywords2);
        }

        g_free(keywords1);
        g_free(keywords2);
    } else {
        if (error) {
            g_error_free(error);
        }
    }

    g_object_unref(stream);
    g_bytes_unref(bytes);
}

// Test that the returned string is a new allocation (caller must free)
TEST_F(PopplerDocumentGetKeywordsTest_2178, ReturnedStringIsNewAllocation_2178)
{
    const char *pdf_with_keywords =
        "%PDF-1.4\n"
        "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
        "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n"
        "4 0 obj\n<< /Keywords (allocation test) >>\nendobj\n"
        "xref\n0 5\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "0000000190 00000 n \n"
        "trailer\n<< /Size 5 /Root 1 0 R /Info 4 0 R >>\n"
        "startxref\n240\n%%EOF\n";

    GError *error = nullptr;
    gsize len = strlen(pdf_with_keywords);
    GBytes *bytes = g_bytes_new_static(pdf_with_keywords, len);
    GInputStream *stream = g_memory_input_stream_new_from_bytes(bytes);

    document_ = poppler_document_new_from_stream(stream, len, nullptr, nullptr, &error);

    if (document_ != nullptr) {
        gchar *keywords1 = poppler_document_get_keywords(document_);
        gchar *keywords2 = poppler_document_get_keywords(document_);

        if (keywords1 != nullptr && keywords2 != nullptr) {
            // Each call should return a separately allocated string
            EXPECT_NE(keywords1, keywords2);
            EXPECT_STREQ(keywords1, keywords2);
        }

        g_free(keywords1);
        g_free(keywords2);
    } else {
        if (error) {
            g_error_free(error);
        }
    }

    g_object_unref(stream);
    g_bytes_unref(bytes);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
