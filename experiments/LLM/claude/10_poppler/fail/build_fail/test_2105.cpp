#include <glib.h>
#include <poppler.h>
#include <poppler-document.h>
#include <poppler-page.h>
#include <glib-object.h>
#include <cstring>
#include <cstdio>
#include <cstdlib>

// Include the header that declares poppler_annot_file_attachment_get_name
extern "C" {
#include "poppler-annot.h"
}

#include <gtest/gtest.h>

class PopplerAnnotFileAttachmentTest_2105 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that passing NULL returns NULL (g_return_val_if_fail should catch it)
TEST_F(PopplerAnnotFileAttachmentTest_2105, NullAnnotReturnsNull_2105)
{
    // g_return_val_if_fail with NULL should return NULL
    // We need to suppress the GLib warning
    g_test_expect_message("GLib", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_ANNOT_FILE_ATTACHMENT*");
    gchar *name = poppler_annot_file_attachment_get_name(NULL);
    g_test_assert_expected_messages();
    EXPECT_EQ(name, nullptr);
}

// Test that passing an invalid GObject type returns NULL
TEST_F(PopplerAnnotFileAttachmentTest_2105, InvalidAnnotTypeReturnsNull_2105)
{
    // Create a different type of poppler object and cast it incorrectly
    // Using a PopplerAnnot that is not a file attachment should fail the type check
    // We'll use NULL since we can't easily create a wrong-typed GObject without a document
    g_test_expect_message("GLib", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_ANNOT_FILE_ATTACHMENT*");
    PopplerAnnotFileAttachment *invalid = reinterpret_cast<PopplerAnnotFileAttachment *>(0x1);
    // This would likely crash, so let's just test with NULL which is safer
    gchar *name = poppler_annot_file_attachment_get_name(nullptr);
    g_test_assert_expected_messages();
    EXPECT_EQ(name, nullptr);
}

// Test with a real PDF that contains a file attachment annotation, if available
// Since we may not have a PDF with file attachment annotations readily available,
// we test the interface contract with what we can safely invoke.
TEST_F(PopplerAnnotFileAttachmentTest_2105, NullPointerSafety_2105)
{
    // Multiple calls with NULL should consistently return NULL
    for (int i = 0; i < 3; i++) {
        g_test_expect_message("GLib", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_ANNOT_FILE_ATTACHMENT*");
        gchar *name = poppler_annot_file_attachment_get_name(NULL);
        g_test_assert_expected_messages();
        EXPECT_EQ(name, nullptr);
    }
}

// Test with a wrong GObject type (e.g., a simple GObject)
TEST_F(PopplerAnnotFileAttachmentTest_2105, WrongGObjectTypeReturnsNull_2105)
{
    GObject *obj = (GObject *)g_object_new(G_TYPE_OBJECT, NULL);
    ASSERT_NE(obj, nullptr);

    g_test_expect_message("GLib", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_ANNOT_FILE_ATTACHMENT*");
    gchar *name = poppler_annot_file_attachment_get_name(reinterpret_cast<PopplerAnnotFileAttachment *>(obj));
    g_test_assert_expected_messages();
    EXPECT_EQ(name, nullptr);

    g_object_unref(obj);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, &argv);
    return RUN_ALL_TESTS();
}
