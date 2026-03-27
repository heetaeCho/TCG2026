#include <gtest/gtest.h>

#include "poppler-attachment.h"



// Mocking external collaborators if needed (not required in this case)



class PopplerAttachmentTest : public ::testing::Test {

protected:

    PopplerAttachment *attachment;



    void SetUp() override {

        attachment = new PopplerAttachment();

        // Initialize with default values

        attachment->size = 0;

    }



    void TearDown() override {

        delete attachment;

    }

};



TEST_F(PopplerAttachmentTest_2276, GetSize_ReturnsZeroForDefault_2276) {

    EXPECT_EQ(poppler_attachment_get_size(attachment), 0);

}



TEST_F(PopplerAttachmentTest_2276, GetSize_ReturnsCorrectValue_2276) {

    attachment->size = 1024;

    EXPECT_EQ(poppler_attachment_get_size(attachment), 1024);

}



TEST_F(PopplerAttachmentTest_2276, GetSize_BoundaryCondition_MaxSize_2276) {

    attachment->size = G_MAXSIZE;

    EXPECT_EQ(poppler_attachment_get_size(attachment), G_MAXSIZE);

}



TEST_F(PopplerAttachmentTest_2276, GetSize_BoundaryCondition_ZeroSize_2276) {

    attachment->size = 0;

    EXPECT_EQ(poppler_attachment_get_size(attachment), 0);

}
