#include <gtest/gtest.h>
#include <glib-object.h>

// Include the header for PopplerAttachment
extern "C" {
#include "poppler-attachment.h"

// Declaration of the function under test
const gchar *poppler_attachment_get_description(PopplerAttachment *attachment);
}

class PopplerAttachmentGetDescriptionTest_2273 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that get_description returns the description field of the attachment
TEST_F(PopplerAttachmentGetDescriptionTest_2273, ReturnsDescriptionWhenSet_2273)
{
    PopplerAttachment attachment = {};
    gchar *desc = g_strdup("Test Description");
    attachment.description = desc;

    const gchar *result = poppler_attachment_get_description(&attachment);

    EXPECT_STREQ(result, "Test Description");
    EXPECT_EQ(result, attachment.description);

    g_free(desc);
}

// Test that get_description returns NULL when description is NULL
TEST_F(PopplerAttachmentGetDescriptionTest_2273, ReturnsNullWhenDescriptionIsNull_2273)
{
    PopplerAttachment attachment = {};
    attachment.description = nullptr;

    const gchar *result = poppler_attachment_get_description(&attachment);

    EXPECT_EQ(result, nullptr);
}

// Test that get_description returns empty string when description is empty
TEST_F(PopplerAttachmentGetDescriptionTest_2273, ReturnsEmptyStringWhenDescriptionIsEmpty_2273)
{
    PopplerAttachment attachment = {};
    gchar *desc = g_strdup("");
    attachment.description = desc;

    const gchar *result = poppler_attachment_get_description(&attachment);

    EXPECT_STREQ(result, "");

    g_free(desc);
}

// Test that get_description returns the exact pointer stored in the description field
TEST_F(PopplerAttachmentGetDescriptionTest_2273, ReturnsSamePointerAsDescriptionField_2273)
{
    PopplerAttachment attachment = {};
    gchar *desc = g_strdup("Pointer identity test");
    attachment.description = desc;

    const gchar *result = poppler_attachment_get_description(&attachment);

    EXPECT_EQ(result, desc);

    g_free(desc);
}

// Test with a description containing special/unicode characters
TEST_F(PopplerAttachmentGetDescriptionTest_2273, ReturnsDescriptionWithSpecialCharacters_2273)
{
    PopplerAttachment attachment = {};
    gchar *desc = g_strdup("Descripción con caractères spéciaux: äöü ñ 中文");
    attachment.description = desc;

    const gchar *result = poppler_attachment_get_description(&attachment);

    EXPECT_STREQ(result, "Descripción con caractères spéciaux: äöü ñ 中文");

    g_free(desc);
}

// Test with a very long description string
TEST_F(PopplerAttachmentGetDescriptionTest_2273, ReturnsLongDescription_2273)
{
    PopplerAttachment attachment = {};
    // Create a long string
    std::string long_desc(10000, 'A');
    gchar *desc = g_strdup(long_desc.c_str());
    attachment.description = desc;

    const gchar *result = poppler_attachment_get_description(&attachment);

    EXPECT_STREQ(result, long_desc.c_str());

    g_free(desc);
}
