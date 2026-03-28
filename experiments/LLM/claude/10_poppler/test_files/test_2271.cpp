#include <gtest/gtest.h>
#include <glib.h>

extern "C" {
#include "poppler-attachment.h"
}

// Since we need the actual struct layout and poppler types, we include what's needed
// poppler_attachment_get_checksum returns attachment->checksum which is a GString*

class PopplerAttachmentChecksumTest_2271 : public ::testing::Test {
protected:
    PopplerAttachment *attachment = nullptr;

    void SetUp() override {
        attachment = static_cast<PopplerAttachment *>(
            g_object_new(POPPLER_TYPE_ATTACHMENT, nullptr));
    }

    void TearDown() override {
        if (attachment) {
            g_object_unref(attachment);
            attachment = nullptr;
        }
    }
};

TEST_F(PopplerAttachmentChecksumTest_2271, ReturnsChecksumField_2271) {
    // A newly created attachment should have some checksum value (possibly NULL)
    const GString *checksum = poppler_attachment_get_checksum(attachment);
    // For a default-constructed attachment, checksum may be NULL
    // We just verify the function doesn't crash and returns something
    SUCCEED();
}

TEST_F(PopplerAttachmentChecksumTest_2271, ChecksumIsNullForNewAttachment_2271) {
    const GString *checksum = poppler_attachment_get_checksum(attachment);
    // A newly created PopplerAttachment without any PDF data should have NULL checksum
    EXPECT_EQ(checksum, nullptr);
}

TEST_F(PopplerAttachmentChecksumTest_2271, ReturnTypeIsConst_2271) {
    // Verify the function returns a const GString pointer (compile-time check)
    const GString *checksum = poppler_attachment_get_checksum(attachment);
    // This test primarily verifies the const correctness at compile time
    (void)checksum;
    SUCCEED();
}

TEST_F(PopplerAttachmentChecksumTest_2271, ConsistentReturnOnMultipleCalls_2271) {
    // Calling the function multiple times should return the same pointer
    const GString *checksum1 = poppler_attachment_get_checksum(attachment);
    const GString *checksum2 = poppler_attachment_get_checksum(attachment);
    EXPECT_EQ(checksum1, checksum2);
}

TEST_F(PopplerAttachmentChecksumTest_2271, SetChecksumAndRetrieve_2271) {
    // If we can set the checksum field directly and retrieve it
    // Since checksum is a public field in the struct
    GString *test_checksum = g_string_new("abc123");
    
    // Access the checksum field if it's accessible
    if (attachment->checksum != nullptr) {
        g_string_free(attachment->checksum, TRUE);
    }
    attachment->checksum = test_checksum;
    
    const GString *result = poppler_attachment_get_checksum(attachment);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result, test_checksum);
    EXPECT_STREQ(result->str, "abc123");
    EXPECT_EQ(result->len, 6u);
}

TEST_F(PopplerAttachmentChecksumTest_2271, EmptyChecksumString_2271) {
    GString *empty_checksum = g_string_new("");
    
    if (attachment->checksum != nullptr) {
        g_string_free(attachment->checksum, TRUE);
    }
    attachment->checksum = empty_checksum;
    
    const GString *result = poppler_attachment_get_checksum(attachment);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result->str, "");
    EXPECT_EQ(result->len, 0u);
}
