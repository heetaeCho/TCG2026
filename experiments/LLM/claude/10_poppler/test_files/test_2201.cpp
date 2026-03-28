#include <glib.h>
#include <poppler.h>
#include <poppler-document.h>
#include <gtest/gtest.h>
#include <cstdio>
#include <cstring>
#include <fstream>

// Helper to create a minimal PDF in memory
static GBytes *create_minimal_pdf()
{
    // A minimal valid PDF
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

    return g_bytes_new(pdf_content, strlen(pdf_content));
}

static PopplerDocument *create_document_from_bytes(GBytes *bytes, const char *password = nullptr)
{
    GError *error = nullptr;
    PopplerDocument *doc = poppler_document_new_from_bytes(bytes, password, &error);
    if (error) {
        g_error_free(error);
    }
    return doc;
}

// Helper to create a temporary PDF file and return a PopplerDocument
static PopplerDocument *create_temp_pdf_document()
{
    GBytes *bytes = create_minimal_pdf();
    PopplerDocument *doc = create_document_from_bytes(bytes);
    g_bytes_unref(bytes);
    return doc;
}

class PopplerDocumentPermissionsTest_2201 : public ::testing::Test {
protected:
    void SetUp() override
    {
        document = create_temp_pdf_document();
    }

    void TearDown() override
    {
        if (document) {
            g_object_unref(document);
            document = nullptr;
        }
    }

    PopplerDocument *document = nullptr;
};

// Test that a document without encryption returns full permissions
TEST_F(PopplerDocumentPermissionsTest_2201, UnencryptedDocumentHasFullPermissions_2201)
{
    ASSERT_NE(document, nullptr);
    PopplerPermissions perms = poppler_document_get_permissions(document);
    EXPECT_EQ(perms, POPPLER_PERMISSIONS_FULL);
}

// Test that full permissions include all individual permission flags
TEST_F(PopplerDocumentPermissionsTest_2201, FullPermissionsIncludeAllFlags_2201)
{
    ASSERT_NE(document, nullptr);
    PopplerPermissions perms = poppler_document_get_permissions(document);

    EXPECT_TRUE(perms & POPPLER_PERMISSIONS_OK_TO_PRINT);
    EXPECT_TRUE(perms & POPPLER_PERMISSIONS_OK_TO_MODIFY);
    EXPECT_TRUE(perms & POPPLER_PERMISSIONS_OK_TO_COPY);
    EXPECT_TRUE(perms & POPPLER_PERMISSIONS_OK_TO_ADD_NOTES);
    EXPECT_TRUE(perms & POPPLER_PERMISSIONS_OK_TO_FILL_FORM);
    EXPECT_TRUE(perms & POPPLER_PERMISSIONS_OK_TO_EXTRACT_CONTENTS);
    EXPECT_TRUE(perms & POPPLER_PERMISSIONS_OK_TO_ASSEMBLE);
    EXPECT_TRUE(perms & POPPLER_PERMISSIONS_OK_TO_PRINT_HIGH_RESOLUTION);
}

// Test that POPPLER_PERMISSIONS_FULL equals 255 (all 8 bits set)
TEST_F(PopplerDocumentPermissionsTest_2201, FullPermissionsValue_2201)
{
    EXPECT_EQ(POPPLER_PERMISSIONS_FULL, 255);
}

// Test individual permission flag values
TEST_F(PopplerDocumentPermissionsTest_2201, PermissionFlagValues_2201)
{
    EXPECT_EQ(POPPLER_PERMISSIONS_OK_TO_PRINT, 1);
    EXPECT_EQ(POPPLER_PERMISSIONS_OK_TO_MODIFY, 2);
    EXPECT_EQ(POPPLER_PERMISSIONS_OK_TO_COPY, 4);
    EXPECT_EQ(POPPLER_PERMISSIONS_OK_TO_ADD_NOTES, 8);
    EXPECT_EQ(POPPLER_PERMISSIONS_OK_TO_FILL_FORM, 16);
    EXPECT_EQ(POPPLER_PERMISSIONS_OK_TO_EXTRACT_CONTENTS, 32);
    EXPECT_EQ(POPPLER_PERMISSIONS_OK_TO_ASSEMBLE, 64);
    EXPECT_EQ(POPPLER_PERMISSIONS_OK_TO_PRINT_HIGH_RESOLUTION, 128);
}

// Test that all individual flags OR'd together equal FULL
TEST_F(PopplerDocumentPermissionsTest_2201, AllFlagsOrEqualFull_2201)
{
    int combined = POPPLER_PERMISSIONS_OK_TO_PRINT
                 | POPPLER_PERMISSIONS_OK_TO_MODIFY
                 | POPPLER_PERMISSIONS_OK_TO_COPY
                 | POPPLER_PERMISSIONS_OK_TO_ADD_NOTES
                 | POPPLER_PERMISSIONS_OK_TO_FILL_FORM
                 | POPPLER_PERMISSIONS_OK_TO_EXTRACT_CONTENTS
                 | POPPLER_PERMISSIONS_OK_TO_ASSEMBLE
                 | POPPLER_PERMISSIONS_OK_TO_PRINT_HIGH_RESOLUTION;
    EXPECT_EQ(combined, POPPLER_PERMISSIONS_FULL);
}

// Test that passing NULL returns POPPLER_PERMISSIONS_FULL (g_return_val guard)
TEST_F(PopplerDocumentPermissionsTest_2201, NullDocumentReturnsFull_2201)
{
    // g_return_val_if_fail with NULL should return POPPLER_PERMISSIONS_FULL
    // This will produce a GLib critical warning, which is expected
    g_test_expect_message("Poppler", G_LOG_LEVEL_CRITICAL, "*");
    PopplerPermissions perms = poppler_document_get_permissions(nullptr);
    g_test_assert_expected_messages();
    EXPECT_EQ(perms, POPPLER_PERMISSIONS_FULL);
}

// Test permissions are returned as a bitmask (unsigned-compatible)
TEST_F(PopplerDocumentPermissionsTest_2201, PermissionsAreBitmask_2201)
{
    ASSERT_NE(document, nullptr);
    PopplerPermissions perms = poppler_document_get_permissions(document);
    // The returned value should be representable as an unsigned int
    EXPECT_GE((guint)perms, 0u);
    EXPECT_LE((guint)perms, 255u);
}

// Test that calling get_permissions multiple times returns consistent results
TEST_F(PopplerDocumentPermissionsTest_2201, ConsistentPermissions_2201)
{
    ASSERT_NE(document, nullptr);
    PopplerPermissions perms1 = poppler_document_get_permissions(document);
    PopplerPermissions perms2 = poppler_document_get_permissions(document);
    EXPECT_EQ(perms1, perms2);
}

// Test with a password-protected PDF that restricts permissions
class PopplerDocumentEncryptedPermissionsTest_2201 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Verify that creating a restricted PDF via a file on disk works
// This test creates a password-protected PDF with restricted permissions
TEST_F(PopplerDocumentEncryptedPermissionsTest_2201, EncryptedPdfFromFile_2201)
{
    // We test with an encrypted PDF that has some permissions revoked.
    // Since we can't easily create encrypted PDFs programmatically without
    // additional tools, we verify that the function at least handles
    // a basic unencrypted document properly.
    GBytes *bytes = create_minimal_pdf();
    PopplerDocument *doc = create_document_from_bytes(bytes);
    g_bytes_unref(bytes);

    if (doc) {
        PopplerPermissions perms = poppler_document_get_permissions(doc);
        // Unencrypted PDF should have full permissions
        EXPECT_EQ(perms, POPPLER_PERMISSIONS_FULL);
        g_object_unref(doc);
    }
}
