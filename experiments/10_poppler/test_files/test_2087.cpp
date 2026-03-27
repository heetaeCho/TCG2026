#include <gtest/gtest.h>

#include "poppler-annot.h"



// Assuming we have a way to create and manage PopplerAnnotMarkup instances for testing purposes.

class PopplerAnnotMarkupTest_2087 : public ::testing::Test {

protected:

    // Mock or setup any necessary collaborators if needed

    void SetUp() override {

        // Setup code, if any

    }



    void TearDown() override {

        // Teardown code, if any

    }

};



TEST_F(PopplerAnnotMarkupTest_2087, GetReplyTo_ReturnsR_2087) {

    // Arrange

    PopplerAnnotMarkup* poppler_annot = createPopplerAnnotMarkupWithReplyType(AnnotMarkup::replyTypeR);



    // Act

    PopplerAnnotMarkupReplyType result = poppler_annot_markup_get_reply_to(poppler_annot);



    // Assert

    EXPECT_EQ(result, POPPLER_ANNOT_MARKUP_REPLY_TYPE_R);



    // Cleanup

    destroyPopplerAnnotMarkup(poppler_annot);

}



TEST_F(PopplerAnnotMarkupTest_2087, GetReplyTo_ReturnsGroup_2087) {

    // Arrange

    PopplerAnnotMarkup* poppler_annot = createPopplerAnnotMarkupWithReplyType(AnnotMarkup::replyTypeGroup);



    // Act

    PopplerAnnotMarkupReplyType result = poppler_annot_markup_get_reply_to(poppler_annot);



    // Assert

    EXPECT_EQ(result, POPPLER_ANNOT_MARKUP_REPLY_TYPE_GROUP);



    // Cleanup

    destroyPopplerAnnotMarkup(poppler_annot);

}



TEST_F(PopplerAnnotMarkupTest_2087, GetReplyTo_UnsupportedType_WarningAndReturnsR_2087) {

    // Arrange

    PopplerAnnotMarkup* poppler_annot = createPopplerAnnotMarkupWithUnsupportedReplyType();



    // Act & Assert

    EXPECT_EQ(poppler_annot_markup_get_reply_to(poppler_annot), POPPLER_ANNOT_MARKUP_REPLY_TYPE_R);



    // Cleanup

    destroyPopplerAnnotMarkup(poppler_annot);

}



TEST_F(PopplerAnnotMarkupTest_2087, GetReplyTo_NullPointer_ReturnsR_2087) {

    // Arrange

    PopplerAnnotMarkup* poppler_annot = nullptr;



    // Act & Assert

    EXPECT_EQ(poppler_annot_markup_get_reply_to(poppler_annot), POPPLER_ANNOT_MARKUP_REPLY_TYPE_R);

}
