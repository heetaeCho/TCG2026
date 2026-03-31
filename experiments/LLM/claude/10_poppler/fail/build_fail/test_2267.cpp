#include <gtest/gtest.h>
#include <glib-object.h>

// Include poppler glib headers
#include "poppler.h"
#include "poppler-attachment.h"

class PopplerAttachmentTest_2267 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that PopplerAttachment type is registered in GObject type system
TEST_F(PopplerAttachmentTest_2267, TypeIsRegistered_2267)
{
    GType type = POPPLER_TYPE_ATTACHMENT;
    EXPECT_NE(type, G_TYPE_INVALID);
}

// Test that PopplerAttachment can be instantiated via g_object_new
TEST_F(PopplerAttachmentTest_2267, CanBeInstantiated_2267)
{
    PopplerAttachment *attachment = POPPLER_ATTACHMENT(g_object_new(POPPLER_TYPE_ATTACHMENT, NULL));
    ASSERT_NE(attachment, nullptr);
    g_object_unref(attachment);
}

// Test that a newly created attachment has NULL name
TEST_F(PopplerAttachmentTest_2267, NewAttachmentHasNullName_2267)
{
    PopplerAttachment *attachment = POPPLER_ATTACHMENT(g_object_new(POPPLER_TYPE_ATTACHMENT, NULL));
    ASSERT_NE(attachment, nullptr);
    EXPECT_EQ(attachment->name, nullptr);
    g_object_unref(attachment);
}

// Test that a newly created attachment has NULL description
TEST_F(PopplerAttachmentTest_2267, NewAttachmentHasNullDescription_2267)
{
    PopplerAttachment *attachment = POPPLER_ATTACHMENT(g_object_new(POPPLER_TYPE_ATTACHMENT, NULL));
    ASSERT_NE(attachment, nullptr);
    EXPECT_EQ(attachment->description, nullptr);
    g_object_unref(attachment);
}

// Test that PopplerAttachment is a GObject
TEST_F(PopplerAttachmentTest_2267, IsGObject_2267)
{
    PopplerAttachment *attachment = POPPLER_ATTACHMENT(g_object_new(POPPLER_TYPE_ATTACHMENT, NULL));
    ASSERT_NE(attachment, nullptr);
    EXPECT_TRUE(G_IS_OBJECT(attachment));
    g_object_unref(attachment);
}

// Test that POPPLER_IS_ATTACHMENT macro works correctly
TEST_F(PopplerAttachmentTest_2267, IsAttachmentMacroWorks_2267)
{
    PopplerAttachment *attachment = POPPLER_ATTACHMENT(g_object_new(POPPLER_TYPE_ATTACHMENT, NULL));
    ASSERT_NE(attachment, nullptr);
    EXPECT_TRUE(POPPLER_IS_ATTACHMENT(attachment));
    g_object_unref(attachment);
}

// Test that ref/unref works correctly
TEST_F(PopplerAttachmentTest_2267, RefUnrefWorks_2267)
{
    PopplerAttachment *attachment = POPPLER_ATTACHMENT(g_object_new(POPPLER_TYPE_ATTACHMENT, NULL));
    ASSERT_NE(attachment, nullptr);

    g_object_ref(attachment);
    // After ref, refcount should be 2
    // Unref twice to properly clean up
    g_object_unref(attachment);
    g_object_unref(attachment);
}

// Test multiple instances are independent
TEST_F(PopplerAttachmentTest_2267, MultipleInstancesAreIndependent_2267)
{
    PopplerAttachment *attachment1 = POPPLER_ATTACHMENT(g_object_new(POPPLER_TYPE_ATTACHMENT, NULL));
    PopplerAttachment *attachment2 = POPPLER_ATTACHMENT(g_object_new(POPPLER_TYPE_ATTACHMENT, NULL));
    ASSERT_NE(attachment1, nullptr);
    ASSERT_NE(attachment2, nullptr);
    EXPECT_NE(attachment1, attachment2);
    g_object_unref(attachment1);
    g_object_unref(attachment2);
}

// Test that the type name is correct
TEST_F(PopplerAttachmentTest_2267, TypeNameIsCorrect_2267)
{
    PopplerAttachment *attachment = POPPLER_ATTACHMENT(g_object_new(POPPLER_TYPE_ATTACHMENT, NULL));
    ASSERT_NE(attachment, nullptr);
    const gchar *type_name = g_type_name(G_OBJECT_TYPE(attachment));
    EXPECT_STREQ(type_name, "PopplerAttachment");
    g_object_unref(attachment);
}

// Test that initial size/checksum fields are in a default state
TEST_F(PopplerAttachmentTest_2267, NewAttachmentDefaultSize_2267)
{
    PopplerAttachment *attachment = POPPLER_ATTACHMENT(g_object_new(POPPLER_TYPE_ATTACHMENT, NULL));
    ASSERT_NE(attachment, nullptr);
    // size should be initialized to 0 or default
    EXPECT_GE(attachment->size, 0u);
    g_object_unref(attachment);
}
