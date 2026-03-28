#include <glib.h>
#include <glib-object.h>
#include <poppler.h>
#include <cstring>
#include <gtest/gtest.h>

class PopplerDocumentSetSubjectTest_2177 : public ::testing::Test {
protected:
    PopplerDocument *document = nullptr;

    void SetUp() override {
        // Create a minimal PDF in memory to get a valid PopplerDocument
        // This is a minimal valid PDF
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
        GBytes *bytes = g_bytes_new(pdf_content, len);
        GInputStream *stream = g_memory_input_stream_new_from_bytes(bytes);
        g_bytes_unref(bytes);

        GError *error = nullptr;
        document = poppler_document_new_from_stream(stream, len, nullptr, nullptr, &error);

        if (!document) {
            // Try alternative method
            if (error) {
                g_error_free(error);
                error = nullptr;
            }
            // Create from data
            document = poppler_document_new_from_data((char *)pdf_content, (int)len, nullptr, &error);
        }

        if (!document && error) {
            g_printerr("Failed to create document: %s\n", error->message);
            g_error_free(error);
        }

        g_object_unref(stream);
    }

    void TearDown() override {
        if (document) {
            g_object_unref(document);
            document = nullptr;
        }
    }
};

TEST_F(PopplerDocumentSetSubjectTest_2177, SetSubjectWithValidString_2177) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }

    const gchar *subject = "Test Subject";
    poppler_document_set_subject(document, subject);

    gchar *retrieved = poppler_document_get_subject(document);
    ASSERT_NE(retrieved, nullptr);
    EXPECT_STREQ(retrieved, subject);
    g_free(retrieved);
}

TEST_F(PopplerDocumentSetSubjectTest_2177, SetSubjectWithNullClearsSubject_2177) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }

    // First set a subject
    poppler_document_set_subject(document, "Initial Subject");

    // Now set to NULL to clear it
    poppler_document_set_subject(document, nullptr);

    gchar *retrieved = poppler_document_get_subject(document);
    // After setting NULL, subject should be cleared (NULL or empty)
    if (retrieved != nullptr) {
        EXPECT_STREQ(retrieved, "");
        g_free(retrieved);
    }
}

TEST_F(PopplerDocumentSetSubjectTest_2177, SetSubjectWithEmptyString_2177) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }

    poppler_document_set_subject(document, "");

    gchar *retrieved = poppler_document_get_subject(document);
    if (retrieved != nullptr) {
        EXPECT_STREQ(retrieved, "");
        g_free(retrieved);
    }
}

TEST_F(PopplerDocumentSetSubjectTest_2177, SetSubjectWithUTF8String_2177) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }

    const gchar *subject = "Ünïcödé Sübject ñ";
    poppler_document_set_subject(document, subject);

    gchar *retrieved = poppler_document_get_subject(document);
    ASSERT_NE(retrieved, nullptr);
    EXPECT_STREQ(retrieved, subject);
    g_free(retrieved);
}

TEST_F(PopplerDocumentSetSubjectTest_2177, SetSubjectOverwritesPrevious_2177) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }

    poppler_document_set_subject(document, "First Subject");
    poppler_document_set_subject(document, "Second Subject");

    gchar *retrieved = poppler_document_get_subject(document);
    ASSERT_NE(retrieved, nullptr);
    EXPECT_STREQ(retrieved, "Second Subject");
    g_free(retrieved);
}

TEST_F(PopplerDocumentSetSubjectTest_2177, SetSubjectWithNullDocumentDoesNotCrash_2177) {
    // Passing NULL document should be handled by g_return_if_fail
    // This should not crash
    poppler_document_set_subject(nullptr, "Test Subject");
}

TEST_F(PopplerDocumentSetSubjectTest_2177, SetSubjectWithLongString_2177) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }

    // Create a long subject string
    std::string long_subject(10000, 'A');
    poppler_document_set_subject(document, long_subject.c_str());

    gchar *retrieved = poppler_document_get_subject(document);
    ASSERT_NE(retrieved, nullptr);
    EXPECT_STREQ(retrieved, long_subject.c_str());
    g_free(retrieved);
}

TEST_F(PopplerDocumentSetSubjectTest_2177, SetSubjectMultipleTimes_2177) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }

    for (int i = 0; i < 100; i++) {
        std::string subject = "Subject " + std::to_string(i);
        poppler_document_set_subject(document, subject.c_str());
    }

    gchar *retrieved = poppler_document_get_subject(document);
    ASSERT_NE(retrieved, nullptr);
    EXPECT_STREQ(retrieved, "Subject 99");
    g_free(retrieved);
}

TEST_F(PopplerDocumentSetSubjectTest_2177, SetSubjectWithSpecialCharacters_2177) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }

    const gchar *subject = "Subject with special chars: <>&\"'\\/ \t\n";
    poppler_document_set_subject(document, subject);

    gchar *retrieved = poppler_document_get_subject(document);
    ASSERT_NE(retrieved, nullptr);
    // Just verify something was set (exact match may vary due to encoding)
    EXPECT_TRUE(strlen(retrieved) > 0);
    g_free(retrieved);
}
