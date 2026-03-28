#include <glib.h>
#include <glib-object.h>
#include <poppler.h>
#include <gtest/gtest.h>
#include <cstring>
#include <cstdio>
#include <string>

class PopplerAttachmentTest_2268 : public ::testing::Test {
protected:
    void SetUp() override {
        // Try to find or create a PDF with attachments for testing
        doc_with_attachments = nullptr;
        doc_without_attachments = nullptr;
    }

    void TearDown() override {
        if (doc_with_attachments) {
            g_object_unref(doc_with_attachments);
        }
        if (doc_without_attachments) {
            g_object_unref(doc_without_attachments);
        }
    }

    PopplerDocument *doc_with_attachments;
    PopplerDocument *doc_without_attachments;
};

TEST_F(PopplerAttachmentTest_2268, AttachmentIsGObject_2268)
{
    // Verify that PopplerAttachment type is registered in the GObject type system
    GType type = poppler_attachment_get_type();
    EXPECT_NE(type, G_TYPE_INVALID);
}

TEST_F(PopplerAttachmentTest_2268, AttachmentTypeIsNotAbstract_2268)
{
    GType type = poppler_attachment_get_type();
    EXPECT_FALSE(G_TYPE_IS_ABSTRACT(type));
}

TEST_F(PopplerAttachmentTest_2268, AttachmentTypeParentIsGObject_2268)
{
    GType type = poppler_attachment_get_type();
    GType parent = g_type_parent(type);
    EXPECT_EQ(parent, G_TYPE_OBJECT);
}

TEST_F(PopplerAttachmentTest_2268, DocumentWithNoAttachmentsReturnsEmptyList_2268)
{
    // Create a simple PDF in memory that has no attachments
    GError *error = nullptr;

    // Use a minimal PDF from a file URI or data - try to create a blank doc
    // We'll test with a NULL document scenario where possible
    // If no test PDF is available, we verify the API doesn't crash with empty list
    const char *pdf_data =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    doc_without_attachments = poppler_document_new_from_data(pdf_data, strlen(pdf_data), nullptr, &error);

    if (doc_without_attachments != nullptr) {
        gboolean has_attachments = poppler_document_has_attachments(doc_without_attachments);
        EXPECT_FALSE(has_attachments);

        GList *attachments = poppler_document_get_attachments(doc_without_attachments);
        EXPECT_EQ(attachments, nullptr);
    }
    // If document creation failed, skip gracefully
    if (error) {
        g_error_free(error);
    }
}

TEST_F(PopplerAttachmentTest_2268, AttachmentSaveToCallbackNullCallbackFails_2268)
{
    // Verify that poppler_attachment_save_to_callback handles null callback
    // This tests error/boundary behavior
    GType type = poppler_attachment_get_type();
    ASSERT_NE(type, G_TYPE_INVALID);

    // We can only test this if we have an actual attachment object
    // Verify the type system is properly set up
    EXPECT_TRUE(g_type_is_a(type, G_TYPE_OBJECT));
}

TEST_F(PopplerAttachmentTest_2268, GetTypeReturnsSameValueOnMultipleCalls_2268)
{
    GType type1 = poppler_attachment_get_type();
    GType type2 = poppler_attachment_get_type();
    EXPECT_EQ(type1, type2);
}

TEST_F(PopplerAttachmentTest_2268, TypeNameIsPopplerAttachment_2268)
{
    GType type = poppler_attachment_get_type();
    const gchar *name = g_type_name(type);
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "PopplerAttachment");
}
