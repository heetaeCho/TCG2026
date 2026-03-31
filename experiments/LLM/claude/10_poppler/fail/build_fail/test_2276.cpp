#include <gtest/gtest.h>
#include <glib-object.h>

// We need the poppler-glib headers
extern "C" {
#include "poppler-attachment.h"

// Declaration of the function under test
gsize poppler_attachment_get_size(PopplerAttachment *attachment);
}

class PopplerAttachmentTest_2276 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that poppler_attachment_get_size returns the correct size for a normal value
TEST_F(PopplerAttachmentTest_2276, GetSizeReturnsCorrectValue_2276)
{
    PopplerAttachment attachment;
    memset(&attachment, 0, sizeof(attachment));
    attachment.size = 1024;

    gsize result = poppler_attachment_get_size(&attachment);
    EXPECT_EQ(result, 1024u);
}

// Test that poppler_attachment_get_size returns zero when size is zero
TEST_F(PopplerAttachmentTest_2276, GetSizeReturnsZero_2276)
{
    PopplerAttachment attachment;
    memset(&attachment, 0, sizeof(attachment));
    attachment.size = 0;

    gsize result = poppler_attachment_get_size(&attachment);
    EXPECT_EQ(result, 0u);
}

// Test that poppler_attachment_get_size returns correct value for a large size
TEST_F(PopplerAttachmentTest_2276, GetSizeReturnsLargeValue_2276)
{
    PopplerAttachment attachment;
    memset(&attachment, 0, sizeof(attachment));
    attachment.size = (gsize)4294967295ULL; // 2^32 - 1

    gsize result = poppler_attachment_get_size(&attachment);
    EXPECT_EQ(result, (gsize)4294967295ULL);
}

// Test that poppler_attachment_get_size returns correct value for size = 1
TEST_F(PopplerAttachmentTest_2276, GetSizeReturnsOne_2276)
{
    PopplerAttachment attachment;
    memset(&attachment, 0, sizeof(attachment));
    attachment.size = 1;

    gsize result = poppler_attachment_get_size(&attachment);
    EXPECT_EQ(result, 1u);
}

// Test that poppler_attachment_get_size returns max gsize value
TEST_F(PopplerAttachmentTest_2276, GetSizeReturnsMaxGsize_2276)
{
    PopplerAttachment attachment;
    memset(&attachment, 0, sizeof(attachment));
    attachment.size = G_MAXSIZE;

    gsize result = poppler_attachment_get_size(&attachment);
    EXPECT_EQ(result, G_MAXSIZE);
}

// Test with a typical file size value
TEST_F(PopplerAttachmentTest_2276, GetSizeTypicalFileSize_2276)
{
    PopplerAttachment attachment;
    memset(&attachment, 0, sizeof(attachment));
    attachment.size = 65536; // 64KB

    gsize result = poppler_attachment_get_size(&attachment);
    EXPECT_EQ(result, 65536u);
}

// Test that changing the size field is reflected in subsequent calls
TEST_F(PopplerAttachmentTest_2276, GetSizeReflectsChangedValue_2276)
{
    PopplerAttachment attachment;
    memset(&attachment, 0, sizeof(attachment));
    attachment.size = 100;

    EXPECT_EQ(poppler_attachment_get_size(&attachment), 100u);

    attachment.size = 200;
    EXPECT_EQ(poppler_attachment_get_size(&attachment), 200u);
}
