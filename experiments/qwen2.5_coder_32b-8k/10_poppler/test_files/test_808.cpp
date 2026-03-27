#include <gtest/gtest.h>

#include "Annot.h"



class AnnotTextTest_808 : public ::testing::Test {

protected:

    virtual void SetUp() {

        // Setup if necessary

    }



    virtual void TearDown() {

        // Cleanup if necessary

    }

};



TEST_F(AnnotTextTest_808, GetState_ReturnsDefaultState_808) {

    PDFDoc doc(nullptr);

    PDFRectangle rect;

    AnnotText annot(&doc, &rect);



    EXPECT_EQ(annot.getState(), AnnotTextState::stateUnknown); // Assuming default state is unknown

}



TEST_F(AnnotTextTest_808, GetState_ReturnsCorrectState_808) {

    PDFDoc doc(nullptr);

    Object dictObject;

    const Object* obj = nullptr;



    // Assuming we can set the state in some way for testing purposes

    AnnotText annot(&doc, std::move(dictObject), obj);



    // Set up the state if possible, otherwise this is a placeholder test

    EXPECT_EQ(annot.getState(), AnnotTextState::stateOpen); // Example state, replace with actual expected state

}



TEST_F(AnnotTextTest_808, GetIcon_ReturnsEmptyStringByDefault_808) {

    PDFDoc doc(nullptr);

    PDFRectangle rect;

    AnnotText annot(&doc, &rect);



    EXPECT_EQ(annot.getIcon(), "");

}



TEST_F(AnnotTextTest_808, SetIconAndGetIcon_Roundtrip_808) {

    PDFDoc doc(nullptr);

    PDFRectangle rect;

    AnnotText annot(&doc, &rect);



    std::string testIcon = "Comment";

    annot.setIcon(testIcon);

    EXPECT_EQ(annot.getIcon(), testIcon);

}



TEST_F(AnnotTextTest_808, GetOpen_ReturnsFalseByDefault_808) {

    PDFDoc doc(nullptr);

    PDFRectangle rect;

    AnnotText annot(&doc, &rect);



    EXPECT_FALSE(annot.getOpen());

}



TEST_F(AnnotTextTest_808, SetOpenAndGetOpen_RoundtripTrue_808) {

    PDFDoc doc(nullptr);

    PDFRectangle rect;

    AnnotText annot(&doc, &rect);



    annot.setOpen(true);

    EXPECT_TRUE(annot.getOpen());

}



TEST_F(AnnotTextTest_808, SetOpenAndGetOpen_RoundtripFalse_808) {

    PDFDoc doc(nullptr);

    PDFRectangle rect;

    AnnotText annot(&doc, &rect);



    annot.setOpen(false);

    EXPECT_FALSE(annot.getOpen());

}
