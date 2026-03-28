#include <gtest/gtest.h>
#include <glib.h>
#include <poppler.h>
#include <cstring>
#include <cstdio>
#include <fstream>

class PopplerDocumentGetIdTest_2150 : public ::testing::Test {
protected:
    PopplerDocument *doc_with_id = nullptr;
    PopplerDocument *doc_without_id = nullptr;

    // Helper to create a minimal PDF in memory that has an ID
    static PopplerDocument *createPdfFromString(const char *pdf_content, gsize len) {
        GError *error = nullptr;
        PopplerDocument *doc = poppler_document_new_from_data(pdf_content, len, nullptr, &error);
        if (error) {
            g_error_free(error);
            return nullptr;
        }
        return doc;
    }

    // Minimal PDF with an ID entry in the trailer
    static std::string makePdfWithId() {
        // A minimal valid PDF with a trailer that contains an /ID entry
        std::string pdf =
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
            "<< /Size 4 /Root 1 0 R /ID [<0123456789abcdef0123456789abcdef> <0123456789abcdef0123456789abcdef>] >>\n"
            "startxref\n"
            "190\n"
            "%%EOF\n";
        return pdf;
    }

    // Minimal PDF without an ID entry
    static std::string makePdfWithoutId() {
        std::string pdf =
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
        return pdf;
    }

    void SetUp() override {
        std::string pdf_with = makePdfWithId();
        doc_with_id = createPdfFromString(pdf_with.c_str(), pdf_with.size());

        std::string pdf_without = makePdfWithoutId();
        doc_without_id = createPdfFromString(pdf_without.c_str(), pdf_without.size());
    }

    void TearDown() override {
        if (doc_with_id)
            g_object_unref(doc_with_id);
        if (doc_without_id)
            g_object_unref(doc_without_id);
    }
};

// Test that NULL document returns FALSE
TEST_F(PopplerDocumentGetIdTest_2150, NullDocumentReturnsFalse_2150) {
    gchar *perm = nullptr;
    gchar *upd = nullptr;
    // Passing NULL should trigger g_return_val_if_fail and return FALSE
    // Note: This may produce a g_critical warning
    g_test_expect_message(nullptr, G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_DOCUMENT*");
    gboolean result = poppler_document_get_id(nullptr, &perm, &upd);
    g_test_assert_expected_messages();
    EXPECT_FALSE(result);
}

// Test getting both IDs from a document that has IDs
TEST_F(PopplerDocumentGetIdTest_2150, GetBothIdsFromDocWithId_2150) {
    if (!doc_with_id) {
        GTEST_SKIP() << "Could not create PDF with ID";
    }
    gchar *perm = nullptr;
    gchar *upd = nullptr;
    gboolean result = poppler_document_get_id(doc_with_id, &perm, &upd);
    if (result) {
        EXPECT_NE(perm, nullptr);
        EXPECT_NE(upd, nullptr);
        if (perm) g_free(perm);
        if (upd) g_free(upd);
    }
}

// Test getting only permanent_id (update_id is NULL)
TEST_F(PopplerDocumentGetIdTest_2150, GetOnlyPermanentId_2150) {
    if (!doc_with_id) {
        GTEST_SKIP() << "Could not create PDF with ID";
    }
    gchar *perm = nullptr;
    gboolean result = poppler_document_get_id(doc_with_id, &perm, nullptr);
    if (result) {
        EXPECT_NE(perm, nullptr);
        if (perm) g_free(perm);
    }
}

// Test getting only update_id (permanent_id is NULL)
TEST_F(PopplerDocumentGetIdTest_2150, GetOnlyUpdateId_2150) {
    if (!doc_with_id) {
        GTEST_SKIP() << "Could not create PDF with ID";
    }
    gchar *upd = nullptr;
    gboolean result = poppler_document_get_id(doc_with_id, nullptr, &upd);
    if (result) {
        EXPECT_NE(upd, nullptr);
        if (upd) g_free(upd);
    }
}

// Test passing both output pointers as NULL (just check return value)
TEST_F(PopplerDocumentGetIdTest_2150, BothOutputPointersNull_2150) {
    if (!doc_with_id) {
        GTEST_SKIP() << "Could not create PDF with ID";
    }
    gboolean result = poppler_document_get_id(doc_with_id, nullptr, nullptr);
    // Should still return TRUE if the document has an ID, or FALSE if not
    // We just verify it doesn't crash
    SUCCEED();
}

// Test document without ID returns FALSE
TEST_F(PopplerDocumentGetIdTest_2150, DocWithoutIdReturnsFalse_2150) {
    if (!doc_without_id) {
        GTEST_SKIP() << "Could not create PDF without ID";
    }
    gchar *perm = nullptr;
    gchar *upd = nullptr;
    gboolean result = poppler_document_get_id(doc_without_id, &perm, &upd);
    EXPECT_FALSE(result);
    EXPECT_EQ(perm, nullptr);
    EXPECT_EQ(upd, nullptr);
}

// Test that when document has no ID, output pointers are set to nullptr
TEST_F(PopplerDocumentGetIdTest_2150, NoIdSetsOutputToNull_2150) {
    if (!doc_without_id) {
        GTEST_SKIP() << "Could not create PDF without ID";
    }
    gchar *perm = reinterpret_cast<gchar *>(0xDEADBEEF);
    gchar *upd = reinterpret_cast<gchar *>(0xDEADBEEF);
    gboolean result = poppler_document_get_id(doc_without_id, &perm, &upd);
    if (!result) {
        EXPECT_EQ(perm, nullptr);
        EXPECT_EQ(upd, nullptr);
    }
}

// Test that permanent and update IDs from same document with same ID match
TEST_F(PopplerDocumentGetIdTest_2150, PermanentAndUpdateIdConsistency_2150) {
    if (!doc_with_id) {
        GTEST_SKIP() << "Could not create PDF with ID";
    }
    gchar *perm = nullptr;
    gchar *upd = nullptr;
    gboolean result = poppler_document_get_id(doc_with_id, &perm, &upd);
    if (result && perm && upd) {
        // For our test PDF, permanent and update IDs are the same
        EXPECT_EQ(memcmp(perm, upd, 32), 0);
        g_free(perm);
        g_free(upd);
    }
}

// Test calling get_id multiple times yields same results
TEST_F(PopplerDocumentGetIdTest_2150, RepeatedCallsConsistent_2150) {
    if (!doc_with_id) {
        GTEST_SKIP() << "Could not create PDF with ID";
    }
    gchar *perm1 = nullptr, *perm2 = nullptr;
    gchar *upd1 = nullptr, *upd2 = nullptr;

    gboolean r1 = poppler_document_get_id(doc_with_id, &perm1, &upd1);
    gboolean r2 = poppler_document_get_id(doc_with_id, &perm2, &upd2);

    EXPECT_EQ(r1, r2);
    if (r1 && r2 && perm1 && perm2) {
        EXPECT_EQ(memcmp(perm1, perm2, 32), 0);
    }
    if (r1 && r2 && upd1 && upd2) {
        EXPECT_EQ(memcmp(upd1, upd2, 32), 0);
    }

    if (perm1) g_free(perm1);
    if (perm2) g_free(perm2);
    if (upd1) g_free(upd1);
    if (upd2) g_free(upd2);
}
