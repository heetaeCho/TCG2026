#include <glib.h>
#include <glib-object.h>
#include <poppler.h>
#include <cstring>
#include <gtest/gtest.h>

class PopplerDocumentSetAuthorTest_2175 : public ::testing::Test {
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
        g_bytes_unref(bytes);

        GError *error = nullptr;
        document = poppler_document_new_from_stream(stream, len, nullptr, nullptr, &error);
        g_object_unref(stream);

        if (!document && error) {
            g_error_free(error);
        }
    }

    void TearDown() override {
        if (document) {
            g_object_unref(document);
            document = nullptr;
        }
    }
};

TEST_F(PopplerDocumentSetAuthorTest_2175, SetAuthorBasic_2175) {
    ASSERT_NE(document, nullptr);

    const gchar *author = "John Doe";
    poppler_document_set_author(document, author);

    gchar *retrieved = poppler_document_get_author(document);
    ASSERT_NE(retrieved, nullptr);
    EXPECT_STREQ(retrieved, "John Doe");
    g_free(retrieved);
}

TEST_F(PopplerDocumentSetAuthorTest_2175, SetAuthorNull_2175) {
    ASSERT_NE(document, nullptr);

    // First set a valid author
    poppler_document_set_author(document, "Initial Author");

    // Then set to NULL to clear it
    poppler_document_set_author(document, nullptr);

    gchar *retrieved = poppler_document_get_author(document);
    // After setting NULL, author should be cleared
    EXPECT_TRUE(retrieved == nullptr || strlen(retrieved) == 0);
    g_free(retrieved);
}

TEST_F(PopplerDocumentSetAuthorTest_2175, SetAuthorEmptyString_2175) {
    ASSERT_NE(document, nullptr);

    poppler_document_set_author(document, "");

    gchar *retrieved = poppler_document_get_author(document);
    if (retrieved != nullptr) {
        EXPECT_STREQ(retrieved, "");
    }
    g_free(retrieved);
}

TEST_F(PopplerDocumentSetAuthorTest_2175, SetAuthorUTF8_2175) {
    ASSERT_NE(document, nullptr);

    // UTF-8 string with non-ASCII characters
    const gchar *author = "Ñoño García";
    poppler_document_set_author(document, author);

    gchar *retrieved = poppler_document_get_author(document);
    ASSERT_NE(retrieved, nullptr);
    EXPECT_STREQ(retrieved, "Ñoño García");
    g_free(retrieved);
}

TEST_F(PopplerDocumentSetAuthorTest_2175, SetAuthorOverwrite_2175) {
    ASSERT_NE(document, nullptr);

    poppler_document_set_author(document, "First Author");
    gchar *retrieved = poppler_document_get_author(document);
    ASSERT_NE(retrieved, nullptr);
    EXPECT_STREQ(retrieved, "First Author");
    g_free(retrieved);

    poppler_document_set_author(document, "Second Author");
    retrieved = poppler_document_get_author(document);
    ASSERT_NE(retrieved, nullptr);
    EXPECT_STREQ(retrieved, "Second Author");
    g_free(retrieved);
}

TEST_F(PopplerDocumentSetAuthorTest_2175, SetAuthorLongString_2175) {
    ASSERT_NE(document, nullptr);

    // Create a long author string
    std::string long_author(1000, 'A');
    poppler_document_set_author(document, long_author.c_str());

    gchar *retrieved = poppler_document_get_author(document);
    ASSERT_NE(retrieved, nullptr);
    EXPECT_STREQ(retrieved, long_author.c_str());
    g_free(retrieved);
}

TEST_F(PopplerDocumentSetAuthorTest_2175, SetAuthorWithNullDocument_2175) {
    // Should not crash when called with NULL document (g_return_if_fail should guard)
    poppler_document_set_author(nullptr, "Some Author");
    // If we reach here, it didn't crash - that's the expected behavior
}

TEST_F(PopplerDocumentSetAuthorTest_2175, SetAuthorCJKCharacters_2175) {
    ASSERT_NE(document, nullptr);

    const gchar *author = "日本語の著者";
    poppler_document_set_author(document, author);

    gchar *retrieved = poppler_document_get_author(document);
    ASSERT_NE(retrieved, nullptr);
    EXPECT_STREQ(retrieved, "日本語の著者");
    g_free(retrieved);
}

TEST_F(PopplerDocumentSetAuthorTest_2175, SetAuthorWithSpaces_2175) {
    ASSERT_NE(document, nullptr);

    const gchar *author = "  Author With Spaces  ";
    poppler_document_set_author(document, author);

    gchar *retrieved = poppler_document_get_author(document);
    ASSERT_NE(retrieved, nullptr);
    EXPECT_STREQ(retrieved, "  Author With Spaces  ");
    g_free(retrieved);
}

TEST_F(PopplerDocumentSetAuthorTest_2175, SetAuthorMultipleTimes_2175) {
    ASSERT_NE(document, nullptr);

    for (int i = 0; i < 10; i++) {
        std::string author = "Author " + std::to_string(i);
        poppler_document_set_author(document, author.c_str());

        gchar *retrieved = poppler_document_get_author(document);
        ASSERT_NE(retrieved, nullptr);
        EXPECT_STREQ(retrieved, author.c_str());
        g_free(retrieved);
    }
}
