#include <gtest/gtest.h>

#include "poppler-attachment.h"

#include "poppler-attachment.cc"



// Mock structure to facilitate testing

struct PopplerAttachmentMock : public _PopplerAttachment {

    PopplerAttachmentMock(const char* name) {

        this->name = const_cast<char*>(name);

    }

};



class PopplerAttachmentTest_2275 : public ::testing::Test {

protected:

    void SetUp() override {

        testAttachment = new PopplerAttachmentMock("test_attachment");

    }



    void TearDown() override {

        delete testAttachment;

    }



    PopplerAttachment* testAttachment;

};



TEST_F(PopplerAttachmentTest_2275, GetName_ReturnsCorrectName_2275) {

    const gchar* result = poppler_attachment_get_name(testAttachment);

    EXPECT_STREQ(result, "test_attachment");

}



TEST_F(PopplerAttachmentTest_2275, GetName_NullPointer_ReturnsNull_2275) {

    const gchar* result = poppler_attachment_get_name(nullptr);

    EXPECT_EQ(result, nullptr);

}



TEST_F(PopplerAttachmentTest_2275, GetName_EmptyString_ReturnsEmptyString_2275) {

    PopplerAttachmentMock emptyAttachment("");

    const gchar* result = poppler_attachment_get_name(&emptyAttachment);

    EXPECT_STREQ(result, "");

}
