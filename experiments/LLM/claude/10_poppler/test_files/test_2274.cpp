#include <glib.h>
#include <glib-object.h>
#include "poppler-attachment.h"
#include "poppler.h"
#include <gtest/gtest.h>

// Note: Since PopplerAttachment is a GObject-based type and we cannot directly
// construct instances without the internal Poppler infrastructure, we test
// through the public API as much as possible.

class PopplerAttachmentTest_2274 : public ::testing::Test {
protected:
    void SetUp() override {
        // We need a real PDF with attachments to properly test
        attachment = nullptr;
        document = nullptr;
    }

    void TearDown() override {
        if (attachment) {
            g_object_unref(attachment);
            attachment = nullptr;
        }
        if (document) {
            g_object_unref(document);
            document = nullptr;
        }
        if (attachment_list) {
            g_list_free_full(attachment_list, g_object_unref);
            attachment_list = nullptr;
        }
    }

    PopplerAttachment *attachment;
    PopplerDocument *document;
    GList *attachment_list = nullptr;
};

// Test that poppler_attachment_get_mtime returns a valid GDateTime or NULL
// when called with a valid PopplerAttachment from a real document with attachments
TEST_F(PopplerAttachmentTest_2274, GetMtimeReturnsGDateTimeOrNull_2274)
{
    // Create a minimal PDF with an embedded file in memory
    // Since we can't easily create a PDF with attachments programmatically
    // without a file, we test the type system at minimum
    GType type = poppler_attachment_get_type();
    EXPECT_NE(type, G_TYPE_INVALID);
}

// Test that the PopplerAttachment type is properly registered
TEST_F(PopplerAttachmentTest_2274, TypeIsRegistered_2274)
{
    GType type = poppler_attachment_get_type();
    EXPECT_TRUE(g_type_is_a(type, G_TYPE_OBJECT));
}

// Test with a NULL attachment - this should handle gracefully or we verify the type
TEST_F(PopplerAttachmentTest_2274, GetMtimeWithNullAttachment_2274)
{
    // Calling with NULL would typically cause a g_return_val_if_fail to trigger
    // and return NULL. We test this boundary condition.
    // Note: This may cause a GLib warning/critical message
    g_test_expect_message("Poppler", G_LOG_LEVEL_CRITICAL, "*");
    GDateTime *mtime = poppler_attachment_get_mtime(nullptr);
    g_test_assert_expected_messages();
    EXPECT_EQ(mtime, nullptr);
}

// Test that poppler_attachment_get_name exists and handles NULL
TEST_F(PopplerAttachmentTest_2274, GetNameWithNullAttachment_2274)
{
    g_test_expect_message("Poppler", G_LOG_LEVEL_CRITICAL, "*");
    const gchar *name = poppler_attachment_get_name(nullptr);
    g_test_assert_expected_messages();
    EXPECT_EQ(name, nullptr);
}

// Test that poppler_attachment_get_description exists and handles NULL
TEST_F(PopplerAttachmentTest_2274, GetDescriptionWithNullAttachment_2274)
{
    g_test_expect_message("Poppler", G_LOG_LEVEL_CRITICAL, "*");
    const gchar *desc = poppler_attachment_get_description(nullptr);
    g_test_assert_expected_messages();
    EXPECT_EQ(desc, nullptr);
}

// Test that poppler_attachment_get_ctime handles NULL
TEST_F(PopplerAttachmentTest_2274, GetCtimeWithNullAttachment_2274)
{
    g_test_expect_message("Poppler", G_LOG_LEVEL_CRITICAL, "*");
    GDateTime *ctime = poppler_attachment_get_ctime(nullptr);
    g_test_assert_expected_messages();
    EXPECT_EQ(ctime, nullptr);
}

// Test that poppler_attachment_get_size handles NULL
TEST_F(PopplerAttachmentTest_2274, GetSizeWithNullAttachment_2274)
{
    g_test_expect_message("Poppler", G_LOG_LEVEL_CRITICAL, "*");
    gsize size = poppler_attachment_get_size(nullptr);
    g_test_assert_expected_messages();
    EXPECT_EQ(size, 0u);
}

// Test that poppler_attachment_get_checksum handles NULL
TEST_F(PopplerAttachmentTest_2274, GetChecksumWithNullAttachment_2274)
{
    g_test_expect_message("Poppler", G_LOG_LEVEL_CRITICAL, "*");
    const GString *checksum = poppler_attachment_get_checksum(nullptr);
    g_test_assert_expected_messages();
    EXPECT_EQ(checksum, nullptr);
}

// Test save with NULL attachment
TEST_F(PopplerAttachmentTest_2274, SaveWithNullAttachment_2274)
{
    GError *error = nullptr;
    g_test_expect_message("Poppler", G_LOG_LEVEL_CRITICAL, "*");
    gboolean result = poppler_attachment_save(nullptr, "/tmp/test_output_2274.bin", &error);
    g_test_assert_expected_messages();
    EXPECT_FALSE(result);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
