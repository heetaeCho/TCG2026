#include <gtest/gtest.h>

#include "poppler-attachment.h"



class PopplerAttachmentTest_2273 : public ::testing::Test {

protected:

    PopplerAttachment* attachment;



    void SetUp() override {

        attachment = new PopplerAttachment();

        // Setting up a mock description for testing

        attachment->description = new int(42); // Using an integer as per the provided struct definition

    }



    void TearDown() override {

        delete attachment->description;

        delete attachment;

    }

};



TEST_F(PopplerAttachmentTest_2273, GetDescription_ReturnsCorrectValue_2273) {

    EXPECT_EQ(attachment->description, poppler_attachment_get_description(attachment));

}



TEST_F(PopplerAttachmentTest_2273, GetDescription_BoundaryCondition_NULLAttachment_2273) {

    EXPECT_EQ(nullptr, poppler_attachment_get_description(nullptr));

}



// Assuming the description pointer can be null to test another boundary condition

TEST_F(PopplerAttachmentTest_2273, GetDescription_BoundaryCondition_NULLDescription_2273) {

    delete attachment->description;

    attachment->description = nullptr;

    EXPECT_EQ(nullptr, poppler_attachment_get_description(attachment));

}
