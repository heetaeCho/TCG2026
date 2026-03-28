#include <glib.h>
#include <glib-object.h>
#include <gtest/gtest.h>
#include <poppler-document.h>
#include <poppler.h>
#include <cstring>
#include <cstdio>

// Helper to create a minimal valid PDF in memory for testing
static PopplerDocument *create_test_document() {
    // Minimal PDF content
    const char *pdf_content =
        "%PDF-1.0\n"
        "1 0 obj\n"
        "<< /Type /Catalog /Pages 2 0 R >>\n"
        "endobj\n"
        "2 0 obj\n"
        "<< /Type /Pages /Kids [] /Count 0 >>\n"
        "endobj\n"
        "xref\n"
        "0 3\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "trailer\n"
        "<< /Size 3 /Root 1 0 R >>\n"
        "startxref\n"
        "110\n"
        "%%EOF\n";

    gsize length = strlen(pdf_content);
    GError *error = nullptr;

    // Write to a temporary file
    gchar *tmpfile = nullptr;
    gint fd = g_file_open_tmp("test_pdf_XXXXXX.pdf", &tmpfile, &error);
    if (fd == -1 || error) {
        if (error) g_error_free(error);
        return nullptr;
    }

    write(fd, pdf_content, length);
    close(fd);

    gchar *uri = g_filename_to_uri(tmpfile, nullptr, &error);
    if (error) {
        g_error_free(error);
        g_free(tmpfile);
        return nullptr;
    }

    PopplerDocument *doc = poppler_document_new_from_file(uri, nullptr, &error);
    if (error) {
        g_error_free(error);
    }

    g_free(uri);
    g_unlink(tmpfile);
    g_free(tmpfile);

    return doc;
}

class PopplerDocumentSetCreatorTest_2181 : public ::testing::Test {
protected:
    PopplerDocument *doc = nullptr;

    void SetUp() override {
        doc = create_test_document();
        // If we can't create a document, skip but don't fail setup
    }

    void TearDown() override {
        if (doc) {
            g_object_unref(doc);
            doc = nullptr;
        }
    }
};

TEST_F(PopplerDocumentSetCreatorTest_2181, SetCreatorWithValidString_2181) {
    if (!doc) GTEST_SKIP() << "Could not create test document";

    const gchar *creator = "TestCreator";
    poppler_document_set_creator(doc, creator);

    gchar *retrieved = poppler_document_get_creator(doc);
    ASSERT_NE(retrieved, nullptr);
    EXPECT_STREQ(retrieved, "TestCreator");
    g_free(retrieved);
}

TEST_F(PopplerDocumentSetCreatorTest_2181, SetCreatorWithNullClearsCreator_2181) {
    if (!doc) GTEST_SKIP() << "Could not create test document";

    // First set a creator
    poppler_document_set_creator(doc, "SomeCreator");

    // Now set to NULL to clear it
    poppler_document_set_creator(doc, nullptr);

    gchar *retrieved = poppler_document_get_creator(doc);
    // After setting NULL, creator should be empty or NULL
    if (retrieved) {
        EXPECT_STREQ(retrieved, "");
        g_free(retrieved);
    }
}

TEST_F(PopplerDocumentSetCreatorTest_2181, SetCreatorWithEmptyString_2181) {
    if (!doc) GTEST_SKIP() << "Could not create test document";

    poppler_document_set_creator(doc, "");

    gchar *retrieved = poppler_document_get_creator(doc);
    if (retrieved) {
        EXPECT_STREQ(retrieved, "");
        g_free(retrieved);
    }
}

TEST_F(PopplerDocumentSetCreatorTest_2181, SetCreatorWithUTF8String_2181) {
    if (!doc) GTEST_SKIP() << "Could not create test document";

    const gchar *utf8_creator = "Créateur Тест 作者";
    poppler_document_set_creator(doc, utf8_creator);

    gchar *retrieved = poppler_document_get_creator(doc);
    ASSERT_NE(retrieved, nullptr);
    EXPECT_STREQ(retrieved, utf8_creator);
    g_free(retrieved);
}

TEST_F(PopplerDocumentSetCreatorTest_2181, SetCreatorOverwritesPreviousValue_2181) {
    if (!doc) GTEST_SKIP() << "Could not create test document";

    poppler_document_set_creator(doc, "FirstCreator");
    gchar *retrieved1 = poppler_document_get_creator(doc);
    ASSERT_NE(retrieved1, nullptr);
    EXPECT_STREQ(retrieved1, "FirstCreator");
    g_free(retrieved1);

    poppler_document_set_creator(doc, "SecondCreator");
    gchar *retrieved2 = poppler_document_get_creator(doc);
    ASSERT_NE(retrieved2, nullptr);
    EXPECT_STREQ(retrieved2, "SecondCreator");
    g_free(retrieved2);
}

TEST_F(PopplerDocumentSetCreatorTest_2181, SetCreatorWithLongString_2181) {
    if (!doc) GTEST_SKIP() << "Could not create test document";

    // Create a long string
    std::string long_creator(10000, 'A');
    poppler_document_set_creator(doc, long_creator.c_str());

    gchar *retrieved = poppler_document_get_creator(doc);
    ASSERT_NE(retrieved, nullptr);
    EXPECT_STREQ(retrieved, long_creator.c_str());
    g_free(retrieved);
}

TEST_F(PopplerDocumentSetCreatorTest_2181, SetCreatorWithNullDocumentDoesNotCrash_2181) {
    // Passing NULL document should be handled gracefully by g_return_if_fail
    // This should not crash
    poppler_document_set_creator(nullptr, "TestCreator");
    // If we reach here, the guard worked
    SUCCEED();
}

TEST_F(PopplerDocumentSetCreatorTest_2181, SetCreatorWithSpecialCharacters_2181) {
    if (!doc) GTEST_SKIP() << "Could not create test document";

    const gchar *special_creator = "Creator with <special> & \"characters\" © ® ™";
    poppler_document_set_creator(doc, special_creator);

    gchar *retrieved = poppler_document_get_creator(doc);
    ASSERT_NE(retrieved, nullptr);
    EXPECT_STREQ(retrieved, special_creator);
    g_free(retrieved);
}

TEST_F(PopplerDocumentSetCreatorTest_2181, SetCreatorMultipleTimes_2181) {
    if (!doc) GTEST_SKIP() << "Could not create test document";

    for (int i = 0; i < 100; i++) {
        std::string creator = "Creator_" + std::to_string(i);
        poppler_document_set_creator(doc, creator.c_str());
    }

    gchar *retrieved = poppler_document_get_creator(doc);
    ASSERT_NE(retrieved, nullptr);
    EXPECT_STREQ(retrieved, "Creator_99");
    g_free(retrieved);
}

TEST_F(PopplerDocumentSetCreatorTest_2181, SetCreatorWithSingleCharacter_2181) {
    if (!doc) GTEST_SKIP() << "Could not create test document";

    poppler_document_set_creator(doc, "X");

    gchar *retrieved = poppler_document_get_creator(doc);
    ASSERT_NE(retrieved, nullptr);
    EXPECT_STREQ(retrieved, "X");
    g_free(retrieved);
}
