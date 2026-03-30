#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/poppler/poppler/Form.h"



using namespace testing;



class FormFieldButtonTest : public ::testing::Test {

protected:

    PDFDoc* mockDoc;

    Object dict;

    Ref ref;

    FormField* mockParent;

    std::set<int>* usedParentsSet;

    int* usedParentsArray;



    void SetUp() override {

        mockDoc = new PDFDoc();

        ref.num = 0;

        ref.gen = 0;

        mockParent = nullptr;

        usedParentsSet = new std::set<int>();

        usedParentsArray = new int[1];

    }



    void TearDown() override {

        delete mockDoc;

        delete usedParentsSet;

        delete[] usedParentsArray;

    }

};



TEST_F(FormFieldButtonTest_901, GetNumSiblings_ReturnsZeroInitially_901) {

    FormFieldButton button(mockDoc, std::move(dict), ref, mockParent, usedParentsSet);

    EXPECT_EQ(button.getNumSiblings(), 0);

}



TEST_F(FormFieldButtonTest_901, SetSibling_IncreasesSiblingCount_901) {

    FormFieldButton* sibling = new FormFieldButton(mockDoc, std::move(dict), ref, mockParent, usedParentsArray);

    FormFieldButton button(mockDoc, std::move(dict), ref, mockParent, usedParentsSet);



    button.setSibling(0, sibling);

    EXPECT_EQ(button.getNumSiblings(), 1);



    delete sibling;

}



TEST_F(FormFieldButtonTest_901, GetSibling_ReturnsCorrectSibling_901) {

    FormFieldButton* sibling = new FormFieldButton(mockDoc, std::move(dict), ref, mockParent, usedParentsArray);

    FormFieldButton button(mockDoc, std::move(dict), ref, mockParent, usedParentsSet);



    button.setSibling(0, sibling);

    EXPECT_EQ(button.getSibling(0), sibling);



    delete sibling;

}



TEST_F(FormFieldButtonTest_901, SetNumSiblings_SetsCorrectCount_901) {

    FormFieldButton button(mockDoc, std::move(dict), ref, mockParent, usedParentsSet);



    button.setNumSiblings(5);

    EXPECT_EQ(button.getNumSiblings(), 5);

}



TEST_F(FormFieldButtonTest_901, SetSibling_OutOfBounds_DoesNotCrash_901) {

    FormFieldButton* sibling = new FormFieldButton(mockDoc, std::move(dict), ref, mockParent, usedParentsArray);

    FormFieldButton button(mockDoc, std::move(dict), ref, mockParent, usedParentsSet);



    EXPECT_NO_THROW(button.setSibling(100, sibling));



    delete sibling;

}



TEST_F(FormFieldButtonTest_901, GetSibling_OutOfBounds_ReturnsNullptr_901) {

    FormFieldButton button(mockDoc, std::move(dict), ref, mockParent, usedParentsSet);



    EXPECT_EQ(button.getSibling(100), nullptr);

}
