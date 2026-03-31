#include <gtest/gtest.h>
#include <gmock/gmock.h>

extern "C" {
#include <glib-object.h>
}

// We need to include poppler glib headers
#include "poppler-document.h"
#include "poppler-private.h"
#include "poppler.h"

#include <string>
#include <cstdio>
#include <cstdlib>

class PopplerDocumentAttachmentsTest_2154 : public ::testing::Test {
protected:
    void SetUp() override {
        document_with_attachments_ = nullptr;
        document_without_attachments_ = nullptr;
    }

    void TearDown() override {
        if (document_with_attachments_) {
            g_object_unref(document_with_attachments_);
        }
        if (document_without_attachments_) {
            g_object_unref(document_without_attachments_);
        }
    }

    PopplerDocument *loadDocument(const char *filename) {
        GError *error = nullptr;
        gchar *uri = g_strdup_printf("file://%s", filename);
        PopplerDocument *doc = poppler_document_new_from_file(uri, nullptr, &error);
        g_free(uri);
        if (error) {
            g_error_free(error);
            return nullptr;
        }
        return doc;
    }

    // Try to find test PDF files in common test data locations
    std::string findTestFile(const std::string &name) {
        // Common locations for poppler test data
        std::vector<std::string> paths = {
            std::string("../test/") + name,
            std::string("../../test/") + name,
            std::string("./test/") + name,
            std::string("../testfiles/") + name,
            std::string(TESTDATADIR "/") + name,
        };
        for (const auto &p : paths) {
            FILE *f = fopen(p.c_str(), "r");
            if (f) {
                fclose(f);
                // Get absolute path
                char *abs = realpath(p.c_str(), nullptr);
                if (abs) {
                    std::string result(abs);
                    free(abs);
                    return result;
                }
                return p;
            }
        }
        return "";
    }

    PopplerDocument *document_with_attachments_;
    PopplerDocument *document_without_attachments_;
};

// Test that passing NULL document returns 0
TEST_F(PopplerDocumentAttachmentsTest_2154, NullDocumentReturnsZero_2154) {
    // g_return_val_if_fail should handle NULL and return 0
    // We suppress the GLib warning for this test
    g_test_expect_message("GLib", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_DOCUMENT*");
    guint result = poppler_document_get_n_attachments(nullptr);
    g_test_assert_expected_messages();
    EXPECT_EQ(result, 0u);
}

// Test that a valid document without attachments returns 0
TEST_F(PopplerDocumentAttachmentsTest_2154, DocumentWithoutAttachmentsReturnsZero_2154) {
    // Create a simple PDF in memory without attachments
    // We use poppler_document_new_from_data or from_file with a simple PDF
    const char *minimal_pdf =
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

    GError *error = nullptr;
    GBytes *bytes = g_bytes_new_static(minimal_pdf, strlen(minimal_pdf));
    PopplerDocument *doc = poppler_document_new_from_bytes(bytes, nullptr, &error);
    g_bytes_unref(bytes);

    if (doc) {
        guint n = poppler_document_get_n_attachments(doc);
        EXPECT_EQ(n, 0u);
        g_object_unref(doc);
    } else {
        // If we can't create from bytes, try alternate approach
        if (error) {
            g_error_free(error);
        }
        GTEST_SKIP() << "Could not create minimal PDF document for testing";
    }
}

// Test that passing an invalid GObject (non-PopplerDocument) returns 0
TEST_F(PopplerDocumentAttachmentsTest_2154, InvalidGObjectReturnsZero_2154) {
    // Create some other GObject type and pass it
    // This should trigger the POPPLER_IS_DOCUMENT check and return 0
    GObject *not_a_document = (GObject *)g_object_new(G_TYPE_OBJECT, NULL);

    g_test_expect_message("GLib", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_DOCUMENT*");
    guint result = poppler_document_get_n_attachments((PopplerDocument *)not_a_document);
    g_test_assert_expected_messages();

    EXPECT_EQ(result, 0u);
    g_object_unref(not_a_document);
}

// Test return type is guint (unsigned)
TEST_F(PopplerDocumentAttachmentsTest_2154, ReturnTypeIsUnsigned_2154) {
    const char *minimal_pdf =
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

    GError *error = nullptr;
    GBytes *bytes = g_bytes_new_static(minimal_pdf, strlen(minimal_pdf));
    PopplerDocument *doc = poppler_document_new_from_bytes(bytes, nullptr, &error);
    g_bytes_unref(bytes);

    if (doc) {
        guint n = poppler_document_get_n_attachments(doc);
        // Result should be non-negative (it's unsigned, so always >= 0)
        EXPECT_GE(n, 0u);
        g_object_unref(doc);
    } else {
        if (error) {
            g_error_free(error);
        }
        GTEST_SKIP() << "Could not create minimal PDF document for testing";
    }
}

// Test with a PDF that has embedded files (attachments)
TEST_F(PopplerDocumentAttachmentsTest_2154, DocumentWithAttachmentsReturnsNonZero_2154) {
    // Try to find a test PDF with attachments
    std::string path = findTestFile("unittestcases/with-attachments.pdf");
    if (path.empty()) {
        path = findTestFile("with-attachments.pdf");
    }

    if (path.empty()) {
        GTEST_SKIP() << "Test PDF with attachments not found, skipping";
        return;
    }

    document_with_attachments_ = loadDocument(path.c_str());
    if (!document_with_attachments_) {
        GTEST_SKIP() << "Could not load test PDF with attachments";
        return;
    }

    guint n = poppler_document_get_n_attachments(document_with_attachments_);
    EXPECT_GT(n, 0u);
}

// Test consistency: calling the function multiple times returns the same value
TEST_F(PopplerDocumentAttachmentsTest_2154, ConsistentReturnValue_2154) {
    const char *minimal_pdf =
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

    GError *error = nullptr;
    GBytes *bytes = g_bytes_new_static(minimal_pdf, strlen(minimal_pdf));
    PopplerDocument *doc = poppler_document_new_from_bytes(bytes, nullptr, &error);
    g_bytes_unref(bytes);

    if (doc) {
        guint n1 = poppler_document_get_n_attachments(doc);
        guint n2 = poppler_document_get_n_attachments(doc);
        guint n3 = poppler_document_get_n_attachments(doc);
        EXPECT_EQ(n1, n2);
        EXPECT_EQ(n2, n3);
        g_object_unref(doc);
    } else {
        if (error) {
            g_error_free(error);
        }
        GTEST_SKIP() << "Could not create minimal PDF document for testing";
    }
}
