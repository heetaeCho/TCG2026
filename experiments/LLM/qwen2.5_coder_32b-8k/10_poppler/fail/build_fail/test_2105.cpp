#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-annot.h"



// Mocking external dependencies if needed.

class MockAnnotFileAttachment : public AnnotFileAttachment {

public:

    MOCK_METHOD(const GooString*, getName, (), (const override));

};



class PopplerAnnotFileAttachmentTest_2105 : public ::testing::Test {

protected:

    MockAnnotFileAttachment mockAnnot;

    _PopplerAnnotFileAttachment popplerAnnotFileAttachment;

    PopplerAnnot popplerAnnot;



    void SetUp() override {

        // Set up the necessary relationships

        popplerAnnot.annot.reset(&mockAnnot);

        popplerAnnotFileAttachment.poppler_annot = &popplerAnnot;

    }

};



TEST_F(PopplerAnnotFileAttachmentTest_2105, GetName_ReturnsValidString_2105) {

    const char* expectedName = "attachment.pdf";

    GooString gooString(expectedName);



    EXPECT_CALL(mockAnnot, getName()).WillOnce(::testing::Return(&gooString));



    gchar* result = poppler_annot_file_attachment_get_name(reinterpret_cast<PopplerAnnotFileAttachment*>(&popplerAnnotFileAttachment));

    ASSERT_STREQ(result, expectedName);

    g_free(result); // Free the allocated string

}



TEST_F(PopplerAnnotFileAttachmentTest_2105, GetName_ReturnsNull_2105) {

    EXPECT_CALL(mockAnnot, getName()).WillOnce(::testing::Return(nullptr));



    gchar* result = poppler_annot_file_attachment_get_name(reinterpret_cast<PopplerAnnotFileAttachment*>(&popplerAnnotFileAttachment));

    ASSERT_EQ(result, nullptr);

}



TEST_F(PopplerAnnotFileAttachmentTest_2105, InvalidObject_ReturnsNull_2105) {

    PopplerAnnotFileAttachment invalidAnnot;

    gchar* result = poppler_annot_file_attachment_get_name(&invalidAnnot);



    ASSERT_EQ(result, nullptr);

}
