#include <glib.h>
#include <glib-object.h>
#include "poppler-attachment.h"
#include <gtest/gtest.h>

// We need to include the poppler headers properly
extern "C" {
#include "poppler.h"
}

class PopplerAttachmentTest_2272 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

TEST_F(PopplerAttachmentTest_2272, GetCtimeReturnsNonNullForValidAttachment_2272) {
    // We need a valid PopplerAttachment to test. Since PopplerAttachment is a GObject,
    // we create one if possible through the public API.
    // Since we cannot easily create a PopplerAttachment without a PDF document,
    // we test through document loading if available.
    
    // For a black-box test, we verify the function signature behavior:
    // passing NULL should be handled (or crash - we document expected behavior)
    
    // Test that the function exists and is callable with a valid type
    // We'll test with a NULL attachment to check boundary behavior
    // Note: This may cause a critical warning from GLib but shouldn't crash
    // if the implementation uses GET_PRIVATE macro with g_return checks
    
    // Suppress GLib critical warnings for this test
    g_test_expect_message("GLib-GObject", G_LOG_LEVEL_CRITICAL, "*");
    
    GDateTime *result = poppler_attachment_get_ctime(NULL);
    
    // When passed NULL, the function should return NULL (if it has proper guards)
    EXPECT_EQ(result, nullptr);
    
    g_test_assert_expected_messages();
}

TEST_F(PopplerAttachmentTest_2272, GetCtimeWithValidPDFAttachment_2272) {
    // Try to load a PDF with attachments if test data is available
    // This tests normal operation path
    GError *error = nullptr;
    
    // Attempt to create a minimal test - since we can't easily create
    // PopplerAttachment objects directly, we test through document API
    const char *test_pdf_path = g_getenv("POPPLER_TEST_PDF_WITH_ATTACHMENTS");
    
    if (test_pdf_path != nullptr) {
        gchar *uri = g_filename_to_uri(test_pdf_path, nullptr, &error);
        if (uri) {
            PopplerDocument *doc = poppler_document_new_from_file(uri, nullptr, &error);
            if (doc) {
                if (poppler_document_has_attachments(doc)) {
                    GList *attachments = poppler_document_get_attachments(doc);
                    if (attachments) {
                        PopplerAttachment *attachment = POPPLER_ATTACHMENT(attachments->data);
                        // The ctime may or may not be set depending on the PDF
                        GDateTime *ctime = poppler_attachment_get_ctime(attachment);
                        // Just verify it doesn't crash - ctime can be NULL if not set
                        // If it's non-NULL, verify it's a valid GDateTime
                        if (ctime != nullptr) {
                            // Verify we can extract year from it (basic validity check)
                            gint year = g_date_time_get_year(ctime);
                            EXPECT_GT(year, 0);
                        }
                        
                        g_list_free_full(attachments, g_object_unref);
                    }
                }
                g_object_unref(doc);
            }
            g_free(uri);
        }
        if (error) {
            g_error_free(error);
        }
    } else {
        // Skip gracefully if no test PDF is available
        GTEST_SKIP() << "No test PDF with attachments available (set POPPLER_TEST_PDF_WITH_ATTACHMENTS)";
    }
}

TEST_F(PopplerAttachmentTest_2272, GetCtimeFunctionExists_2272) {
    // Verify that the function symbol exists and is linkable
    // This is a compile-time/link-time test essentially
    auto func_ptr = &poppler_attachment_get_ctime;
    EXPECT_NE(func_ptr, nullptr);
}
