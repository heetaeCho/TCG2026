// poppler_document_set_subject_test_2177.cc

#include <gtest/gtest.h>
#include <gmock/gmock.h>

extern "C" {
#include <glib.h>
#include "poppler.h"
}

// We treat Poppler as a black box and only use the public API.
// We do NOT access internal fields such as document->doc or GooString internals.

class PopplerDocumentSetSubjectTest_2177 : public ::testing::Test {
protected:
    PopplerDocument *document = nullptr;
    GError *error = nullptr;

    void SetUp() override {
        // Create a minimal in-memory PDF document
        const char *minimal_pdf =
            "%PDF-1.4\n"
            "1 0 obj\n"
            "<< /Type /Catalog /Pages 2 0 R >>\n"
            "endobj\n"
            "2 0 obj\n"
            "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
            "endobj\n"
            "3 0 obj\n"
            "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 200 200] >>\n"
            "endobj\n"
            "xref\n"
            "0 4\n"
            "0000000000 65535 f \n"
            "0000000010 00000 n \n"
            "0000000060 00000 n \n"
            "0000000117 00000 n \n"
            "trailer\n"
            "<< /Size 4 /Root 1 0 R >>\n"
            "startxref\n"
            "174\n"
            "%%EOF\n";

        document = poppler_document_new_from_data(
            minimal_pdf,
            strlen(minimal_pdf),
            nullptr,
            &error);

        ASSERT_NE(document, nullptr);
        ASSERT_EQ(error, nullptr);
    }

    void TearDown() override {
        if (document) {
            g_object_unref(document);
            document = nullptr;
        }
        if (error) {
            g_error_free(error);
            error = nullptr;
        }
    }
};

// Normal operation: setting a valid UTF-8 subject should update metadata.
TEST_F(PopplerDocumentSetSubjectTest_2177, SetValidSubjectUpdatesMetadata_2177) {
    const gchar *subject = "Test Subject 2177";

    poppler_document_set_subject(document, subject);

    gchar *retrieved = poppler_document_get_subject(document);
    ASSERT_NE(retrieved, nullptr);
    EXPECT_STREQ(retrieved, subject);

    g_free(retrieved);
}

// Boundary condition: setting subject to nullptr should not crash
// and should result in a null subject when queried.
TEST_F(PopplerDocumentSetSubjectTest_2177, SetNullSubjectClearsOrKeepsConsistentState_2177) {
    poppler_document_set_subject(document, "Initial Subject 2177");

    poppler_document_set_subject(document, nullptr);

    gchar *retrieved = poppler_document_get_subject(document);

    // According to observable behavior, a null subject should result
    // in either nullptr or empty string. We verify it is nullptr.
    EXPECT_EQ(retrieved, nullptr);

    if (retrieved) {
        g_free(retrieved);
    }
}

// Boundary condition: empty string subject should be handled without error.
TEST_F(PopplerDocumentSetSubjectTest_2177, SetEmptyStringSubject_2177) {
    const gchar *subject = "";

    poppler_document_set_subject(document, subject);

    gchar *retrieved = poppler_document_get_subject(document);
    ASSERT_NE(retrieved, nullptr);
    EXPECT_STREQ(retrieved, "");

    g_free(retrieved);
}

// Exceptional case: passing a null document should be safely ignored.
// g_return_if_fail should prevent crash; behavior is observable by no crash.
TEST(PopplerDocumentSetSubjectEdgeTest_2177, NullDocumentDoesNotCrash_2177) {
    // Should not crash even though document is null.
    poppler_document_set_subject(nullptr, "Invalid");

    SUCCEED(); // If we reach here, function handled null safely.
}

// Exceptional case: invalid UTF-8 input should not crash.
// Behavior: if conversion fails, subject should remain unchanged.
TEST_F(PopplerDocumentSetSubjectTest_2177, InvalidUtf8DoesNotModifySubject_2177) {
    const gchar *initial = "Valid Subject 2177";
    poppler_document_set_subject(document, initial);

    // Create invalid UTF-8 sequence
    const gchar invalid_utf8[] = { static_cast<gchar>(0xC3), static_cast<gchar>(0x28), 0 };

    poppler_document_set_subject(document, invalid_utf8);

    gchar *retrieved = poppler_document_get_subject(document);
    ASSERT_NE(retrieved, nullptr);

    // Expect original subject to remain unchanged if conversion failed
    EXPECT_STREQ(retrieved, initial);

    g_free(retrieved);
}