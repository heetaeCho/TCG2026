#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/Annot.h"

#include "TestProjects/poppler/poppler/GooString.h"



class AnnotFileAttachmentTest_855 : public ::testing::Test {

protected:

    GooString* filename;

    AnnotFileAttachment* annotFileAttachment;



    void SetUp() override {

        filename = new GooString("testfile.pdf");

        annotFileAttachment = new AnnotFileAttachment(nullptr, nullptr, filename);

    }



    void TearDown() override {

        delete annotFileAttachment;

        delete filename;

    }

};



TEST_F(AnnotFileAttachmentTest_855, GetName_ReturnsCorrectName_855) {

    EXPECT_STREQ("testfile.pdf", annotFileAttachment->getName()->getCString());

}



TEST_F(AnnotFileAttachmentTest_855, GetName_ReturnsNullWhenFilenameNotSet_855) {

    delete filename;

    filename = nullptr;

    AnnotFileAttachment* annotWithoutName = new AnnotFileAttachment(nullptr, nullptr, filename);

    EXPECT_EQ(nullptr, annotWithoutName->getName());

    delete annotWithoutName;

}
