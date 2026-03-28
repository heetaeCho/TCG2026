#include <glib.h>
#include <glib-object.h>
#include <poppler-document.h>
#include <poppler.h>
#include <gtest/gtest.h>
#include <cstring>

class PopplerDocumentSetTitleTest_2173 : public ::testing::Test {
protected:
    PopplerDocument *document = nullptr;

    void SetUp() override {
        // Create a minimal valid PDF in memory to get a PopplerDocument
        const char *pdf_content =
            "%PDF-1.0\n"
            "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
            "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
            "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
            "xref\n"
            "0 4\n"
            "0000000000 65535 f \n"
            "0000000009 00000 n \n"
            "0000000058 00000 n \n"
            "0000000115 00000 n \n"
            "trailer<</Size 4/Root 1 0 R>>\n"
            "startxref\n"
            "190\n"
            "%%EOF\n";

        gsize len = strlen(pdf_content);
        GBytes *bytes = g_bytes_new(pdf_content, len);
        GInputStream *stream = g_memory_input_stream_new_from_bytes(bytes);
        GError *error = nullptr;

        document = poppler_document_new_from_stream(stream, len, nullptr, nullptr, &error);
        if (!document) {
            // Try alternative method
            gchar *tmp_path = nullptr;
            gint fd = g_file_open_tmp("test_pdf_XXXXXX.pdf", &tmp_path, &error);
            if (fd >= 0) {
                write(fd, pdf_content, len);
                close(fd);
                gchar *uri = g_filename_to_uri(tmp_path, nullptr, nullptr);
                document = poppler_document_new_from_file(uri, nullptr, &error);
                g_free(uri);
                g_unlink(tmp_path);
                g_free(tmp_path);
            }
            if (error) {
                g_error_free(error);
                error = nullptr;
            }
        }

        g_object_unref(stream);
        g_bytes_unref(bytes);
    }

    void TearDown() override {
        if (document) {
            g_object_unref(document);
            document = nullptr;
        }
    }
};

TEST_F(PopplerDocumentSetTitleTest_2173, SetTitleWithValidString_2173) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }

    const gchar *title = "Test Title";
    poppler_document_set_title(document, title);

    gchar *retrieved_title = poppler_document_get_title(document);
    ASSERT_NE(retrieved_title, nullptr);
    EXPECT_STREQ(retrieved_title, "Test Title");
    g_free(retrieved_title);
}

TEST_F(PopplerDocumentSetTitleTest_2173, SetTitleWithNullClearsTitle_2173) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }

    // First set a title
    poppler_document_set_title(document, "Some Title");

    // Now clear it by passing NULL
    poppler_document_set_title(document, nullptr);

    gchar *retrieved_title = poppler_document_get_title(document);
    // After setting NULL, title should be cleared (NULL or empty)
    if (retrieved_title) {
        EXPECT_STREQ(retrieved_title, "");
        g_free(retrieved_title);
    }
    // NULL is also acceptable
}

TEST_F(PopplerDocumentSetTitleTest_2173, SetTitleWithEmptyString_2173) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }

    poppler_document_set_title(document, "");

    gchar *retrieved_title = poppler_document_get_title(document);
    if (retrieved_title) {
        EXPECT_STREQ(retrieved_title, "");
        g_free(retrieved_title);
    }
}

TEST_F(PopplerDocumentSetTitleTest_2173, SetTitleWithUTF8String_2173) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }

    const gchar *utf8_title = "Título con caractères spéciaux: äöü";
    poppler_document_set_title(document, utf8_title);

    gchar *retrieved_title = poppler_document_get_title(document);
    ASSERT_NE(retrieved_title, nullptr);
    EXPECT_STREQ(retrieved_title, utf8_title);
    g_free(retrieved_title);
}

TEST_F(PopplerDocumentSetTitleTest_2173, SetTitleWithNullDocumentDoesNotCrash_2173) {
    // Passing NULL document should be handled gracefully by g_return_if_fail
    // This test just ensures no crash occurs
    poppler_document_set_title(nullptr, "Test");
}

TEST_F(PopplerDocumentSetTitleTest_2173, SetTitleOverwritesPreviousTitle_2173) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }

    poppler_document_set_title(document, "First Title");
    gchar *first = poppler_document_get_title(document);
    ASSERT_NE(first, nullptr);
    EXPECT_STREQ(first, "First Title");
    g_free(first);

    poppler_document_set_title(document, "Second Title");
    gchar *second = poppler_document_get_title(document);
    ASSERT_NE(second, nullptr);
    EXPECT_STREQ(second, "Second Title");
    g_free(second);
}

TEST_F(PopplerDocumentSetTitleTest_2173, SetTitleWithLongString_2173) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }

    // Create a long title string
    std::string long_title(10000, 'A');
    poppler_document_set_title(document, long_title.c_str());

    gchar *retrieved_title = poppler_document_get_title(document);
    ASSERT_NE(retrieved_title, nullptr);
    EXPECT_EQ(std::string(retrieved_title), long_title);
    g_free(retrieved_title);
}

TEST_F(PopplerDocumentSetTitleTest_2173, SetTitleWithUnicodeChars_2173) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }

    // Chinese characters
    const gchar *unicode_title = "中文标题测试";
    poppler_document_set_title(document, unicode_title);

    gchar *retrieved_title = poppler_document_get_title(document);
    ASSERT_NE(retrieved_title, nullptr);
    EXPECT_STREQ(retrieved_title, unicode_title);
    g_free(retrieved_title);
}

TEST_F(PopplerDocumentSetTitleTest_2173, SetTitleMultipleTimesConsecutively_2173) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }

    for (int i = 0; i < 100; i++) {
        std::string title = "Title " + std::to_string(i);
        poppler_document_set_title(document, title.c_str());
    }

    gchar *retrieved_title = poppler_document_get_title(document);
    ASSERT_NE(retrieved_title, nullptr);
    EXPECT_STREQ(retrieved_title, "Title 99");
    g_free(retrieved_title);
}
