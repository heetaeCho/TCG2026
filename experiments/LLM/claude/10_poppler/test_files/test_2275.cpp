#include <gtest/gtest.h>
#include <glib-object.h>

// Include the poppler attachment header
extern "C" {
#include "poppler-attachment.h"

// Declaration of the function under test
const gchar *poppler_attachment_get_name(PopplerAttachment *attachment);
}

class PopplerAttachmentTest_2275 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that get_name returns the name field of the attachment
TEST_F(PopplerAttachmentTest_2275, GetNameReturnsCorrectName_2275) {
    PopplerAttachment attachment;
    memset(&attachment, 0, sizeof(attachment));
    
    const gchar *test_name = "test_document.pdf";
    attachment.name = const_cast<gchar *>(test_name);
    
    const gchar *result = poppler_attachment_get_name(&attachment);
    EXPECT_STREQ(result, test_name);
}

// Test that get_name returns NULL when name is NULL
TEST_F(PopplerAttachmentTest_2275, GetNameReturnsNullWhenNameIsNull_2275) {
    PopplerAttachment attachment;
    memset(&attachment, 0, sizeof(attachment));
    
    attachment.name = nullptr;
    
    const gchar *result = poppler_attachment_get_name(&attachment);
    EXPECT_EQ(result, nullptr);
}

// Test that get_name returns empty string when name is empty
TEST_F(PopplerAttachmentTest_2275, GetNameReturnsEmptyStringWhenNameIsEmpty_2275) {
    PopplerAttachment attachment;
    memset(&attachment, 0, sizeof(attachment));
    
    const gchar *empty_name = "";
    attachment.name = const_cast<gchar *>(empty_name);
    
    const gchar *result = poppler_attachment_get_name(&attachment);
    EXPECT_STREQ(result, "");
}

// Test that get_name returns a name with special characters
TEST_F(PopplerAttachmentTest_2275, GetNameReturnsNameWithSpecialChars_2275) {
    PopplerAttachment attachment;
    memset(&attachment, 0, sizeof(attachment));
    
    const gchar *special_name = "file with spaces & (special) chars!.pdf";
    attachment.name = const_cast<gchar *>(special_name);
    
    const gchar *result = poppler_attachment_get_name(&attachment);
    EXPECT_STREQ(result, special_name);
}

// Test that get_name returns the exact pointer (not a copy)
TEST_F(PopplerAttachmentTest_2275, GetNameReturnsSamePointer_2275) {
    PopplerAttachment attachment;
    memset(&attachment, 0, sizeof(attachment));
    
    const gchar *test_name = "pointer_test.pdf";
    attachment.name = const_cast<gchar *>(test_name);
    
    const gchar *result = poppler_attachment_get_name(&attachment);
    EXPECT_EQ(result, test_name);
}

// Test with a long file name
TEST_F(PopplerAttachmentTest_2275, GetNameReturnsLongName_2275) {
    PopplerAttachment attachment;
    memset(&attachment, 0, sizeof(attachment));
    
    std::string long_name(1024, 'a');
    long_name += ".pdf";
    attachment.name = const_cast<gchar *>(long_name.c_str());
    
    const gchar *result = poppler_attachment_get_name(&attachment);
    EXPECT_STREQ(result, long_name.c_str());
}

// Test with Unicode characters in the name
TEST_F(PopplerAttachmentTest_2275, GetNameReturnsUnicodeName_2275) {
    PopplerAttachment attachment;
    memset(&attachment, 0, sizeof(attachment));
    
    const gchar *unicode_name = "文档附件.pdf";
    attachment.name = const_cast<gchar *>(unicode_name);
    
    const gchar *result = poppler_attachment_get_name(&attachment);
    EXPECT_STREQ(result, unicode_name);
}

// Test calling get_name multiple times returns consistent result
TEST_F(PopplerAttachmentTest_2275, GetNameIsConsistentAcrossMultipleCalls_2275) {
    PopplerAttachment attachment;
    memset(&attachment, 0, sizeof(attachment));
    
    const gchar *test_name = "consistent_test.pdf";
    attachment.name = const_cast<gchar *>(test_name);
    
    const gchar *result1 = poppler_attachment_get_name(&attachment);
    const gchar *result2 = poppler_attachment_get_name(&attachment);
    EXPECT_EQ(result1, result2);
    EXPECT_STREQ(result1, result2);
}
