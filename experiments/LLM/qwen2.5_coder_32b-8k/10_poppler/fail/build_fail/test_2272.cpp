#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-attachment.h"



// Mocking GDateTime for testing purposes

class MockGDateTime {

public:

    MOCK_METHOD0(g_date_time_ref, GDateTime*());

    MOCK_METHOD0(g_date_time_unref, void());

};



// Test fixture for PopplerAttachment tests

class PopplerAttachmentTest_2272 : public ::testing::Test {

protected:

    PopplerAttachment* attachment;



    void SetUp() override {

        attachment = new PopplerAttachment();

        attachment->ctime = GDateTime(); // Assuming default constructor sets a valid GDateTime object

    }



    void TearDown() override {

        delete attachment;

    }

};



// Test for normal operation of poppler_attachment_get_ctime

TEST_F(PopplerAttachmentTest_2272, GetCtime_ReturnsValidGDateTime_2272) {

    GDateTime* ctime = poppler_attachment_get_ctime(attachment);

    EXPECT_NE(ctime, nullptr);

}



// Test for boundary condition where ctime is not set

TEST_F(PopplerAttachmentTest_2272, GetCtime_ReturnsNullWhenCtimeNotSet_2272) {

    attachment->ctime = nullptr;

    GDateTime* ctime = poppler_attachment_get_ctime(attachment);

    EXPECT_EQ(ctime, nullptr);

}



// Test for exceptional case where attachment is null

TEST_F(PopplerAttachmentTest_2272, GetCtime_ReturnsNullWhenAttachmentIsNull_2272) {

    GDateTime* ctime = poppler_attachment_get_ctime(nullptr);

    EXPECT_EQ(ctime, nullptr);

}
