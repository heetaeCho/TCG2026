#include <gtest/gtest.h>

#include "poppler-attachment.h"



// Mocking external collaborators if needed

class MockPopplerAttachment : public PopplerAttachment {

public:

    MOCK_CONST_METHOD0(get_checksum, const GString*());

};



TEST_F(PopplerAttachmentTest_2271, GetChecksum_ReturnsNonEmptyString_2271) {

    PopplerAttachment attachment;

    attachment.checksum = new GString("somechecksum");

    EXPECT_STREQ("somechecksum", poppler_attachment_get_checksum(&attachment));

    delete attachment.checksum;

}



TEST_F(PopplerAttachmentTest_2271, GetChecksum_ReturnsEmptyString_2271) {

    PopplerAttachment attachment;

    attachment.checksum = new GString("");

    EXPECT_STREQ("", poppler_attachment_get_checksum(&attachment));

    delete attachment.checksum;

}



TEST_F(PopplerAttachmentTest_2271, GetChecksum_ReturnsNull_2271) {

    PopplerAttachment attachment;

    attachment.checksum = nullptr;

    EXPECT_EQ(nullptr, poppler_attachment_get_checksum(&attachment));

}
