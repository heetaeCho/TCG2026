#include <glib.h>
#include <glib-object.h>
#include <gtest/gtest.h>

// Include poppler glib headers
#include "poppler.h"
#include "poppler-attachment.h"

class PopplerAttachmentTest_2269 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that a PopplerAttachment object can be created and is of the correct type
TEST_F(PopplerAttachmentTest_2269, ObjectTypeIsCorrect_2269)
{
    GType type = poppler_attachment_get_type();
    EXPECT_NE(type, G_TYPE_INVALID);
}

// Test that PopplerAttachment is a GObject subclass
TEST_F(PopplerAttachmentTest_2269, IsGObjectSubclass_2269)
{
    GType type = poppler_attachment_get_type();
    EXPECT_TRUE(g_type_is_a(type, G_TYPE_OBJECT));
}

// Test that creating and unreffing an attachment doesn't crash (finalize path)
// We need a real PDF with attachments to properly test this through the public API.
// We'll test via a document with embedded files if possible.
TEST_F(PopplerAttachmentTest_2269, AttachmentFromDocumentWithEmbeddedFiles_2269)
{
    // Create a minimal PDF in memory that has no attachments
    // and verify has_attachments returns FALSE
    const char *pdf_content = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                               "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                               "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                               "xref\n0 4\n0000000000 65535 f \n"
                               "0000000009 00000 n \n0000000058 00000 n \n"
                               "0000000115 00000 n \ntrailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    GError *error = nullptr;
    GBytes *bytes = g_bytes_new_static(pdf_content, strlen(pdf_content));
    GInputStream *stream = g_memory_input_stream_new_from_bytes(bytes);

    // Try loading from bytes - poppler_document_new_from_stream or similar
    // Use poppler_document_new_from_data for simplicity
    PopplerDocument *doc = poppler_document_new_from_bytes(bytes, nullptr, &error);

    if (doc != nullptr) {
        gboolean has = poppler_document_has_attachments(doc);
        // Our minimal PDF should not have attachments
        EXPECT_FALSE(has);

        GList *attachments = poppler_document_get_attachments(doc);
        EXPECT_EQ(attachments, nullptr);

        if (attachments) {
            g_list_free_full(attachments, g_object_unref);
        }

        g_object_unref(doc);
    } else {
        // If doc creation fails, just clean up - not a failure of attachment code
        if (error) {
            g_error_free(error);
        }
    }

    g_object_unref(stream);
    g_bytes_unref(bytes);
}

// Test that poppler_attachment_get_type returns a consistent value
TEST_F(PopplerAttachmentTest_2269, GetTypeConsistent_2269)
{
    GType type1 = poppler_attachment_get_type();
    GType type2 = poppler_attachment_get_type();
    EXPECT_EQ(type1, type2);
}

// Test save callback - we need an actual attachment to test save.
// Since we can't easily create one without a real PDF, we test the type system aspects.
TEST_F(PopplerAttachmentTest_2269, TypeNameIsCorrect_2269)
{
    GType type = poppler_attachment_get_type();
    const gchar *name = g_type_name(type);
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "PopplerAttachment");
}

// Test that PopplerAttachment can be instantiated (though fields will be null/default)
// and that finalize handles null fields gracefully
TEST_F(PopplerAttachmentTest_2269, FinalizeHandlesNullFields_2269)
{
    // g_object_new will create an attachment with null fields
    // Unreffing should call finalize which should handle nulls gracefully
    PopplerAttachment *attachment = (PopplerAttachment *)g_object_new(POPPLER_TYPE_ATTACHMENT, nullptr);
    ASSERT_NE(attachment, nullptr);

    // The name, description, checksum should be null initially
    EXPECT_EQ(attachment->name, nullptr);
    EXPECT_EQ(attachment->description, nullptr);
    EXPECT_EQ(attachment->checksum, nullptr);

    // Unreffing should not crash even with null fields
    g_object_unref(attachment);
}

// Test that finalize properly frees name field
TEST_F(PopplerAttachmentTest_2269, FinalizeFreesName_2269)
{
    PopplerAttachment *attachment = (PopplerAttachment *)g_object_new(POPPLER_TYPE_ATTACHMENT, nullptr);
    ASSERT_NE(attachment, nullptr);

    // Set name to a dynamically allocated string
    attachment->name = g_strdup("test_attachment.pdf");
    EXPECT_STREQ(attachment->name, "test_attachment.pdf");

    // Unreffing should free name without issues
    g_object_unref(attachment);
}

// Test that finalize properly frees description field
TEST_F(PopplerAttachmentTest_2269, FinalizeFreesDescription_2269)
{
    PopplerAttachment *attachment = (PopplerAttachment *)g_object_new(POPPLER_TYPE_ATTACHMENT, nullptr);
    ASSERT_NE(attachment, nullptr);

    attachment->description = g_strdup("A test description");
    EXPECT_STREQ(attachment->description, "A test description");

    g_object_unref(attachment);
}

// Test that finalize properly frees checksum GString
TEST_F(PopplerAttachmentTest_2269, FinalizeFreesChecksum_2269)
{
    PopplerAttachment *attachment = (PopplerAttachment *)g_object_new(POPPLER_TYPE_ATTACHMENT, nullptr);
    ASSERT_NE(attachment, nullptr);

    attachment->checksum = g_string_new("abc123checksum");
    EXPECT_STREQ(attachment->checksum->str, "abc123checksum");

    g_object_unref(attachment);
}

// Test finalize with all fields set
TEST_F(PopplerAttachmentTest_2269, FinalizeWithAllFieldsSet_2269)
{
    PopplerAttachment *attachment = (PopplerAttachment *)g_object_new(POPPLER_TYPE_ATTACHMENT, nullptr);
    ASSERT_NE(attachment, nullptr);

    attachment->name = g_strdup("file.txt");
    attachment->description = g_strdup("description");
    attachment->checksum = g_string_new("checksum_value");

    // Should cleanly finalize without memory issues
    g_object_unref(attachment);
}

// Test with empty strings
TEST_F(PopplerAttachmentTest_2269, FinalizeWithEmptyStrings_2269)
{
    PopplerAttachment *attachment = (PopplerAttachment *)g_object_new(POPPLER_TYPE_ATTACHMENT, nullptr);
    ASSERT_NE(attachment, nullptr);

    attachment->name = g_strdup("");
    attachment->description = g_strdup("");
    attachment->checksum = g_string_new("");

    g_object_unref(attachment);
}

// Test multiple create/destroy cycles
TEST_F(PopplerAttachmentTest_2269, MultipleCreateDestroyCycles_2269)
{
    for (int i = 0; i < 100; i++) {
        PopplerAttachment *attachment = (PopplerAttachment *)g_object_new(POPPLER_TYPE_ATTACHMENT, nullptr);
        ASSERT_NE(attachment, nullptr);
        attachment->name = g_strdup("cycle_test");
        g_object_unref(attachment);
    }
}

// Test ref/unref behavior
TEST_F(PopplerAttachmentTest_2269, RefUnrefBehavior_2269)
{
    PopplerAttachment *attachment = (PopplerAttachment *)g_object_new(POPPLER_TYPE_ATTACHMENT, nullptr);
    ASSERT_NE(attachment, nullptr);

    attachment->name = g_strdup("ref_test");

    // Add a reference
    g_object_ref(attachment);

    // First unref should not finalize
    g_object_unref(attachment);

    // Name should still be accessible
    EXPECT_STREQ(attachment->name, "ref_test");

    // Second unref should finalize
    g_object_unref(attachment);
}
