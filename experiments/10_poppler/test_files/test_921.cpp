#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/Form.h"



class FormFieldChoiceTest_921 : public ::testing::Test {

protected:

    PDFDoc* mockDoc;

    Object mockObject;

    Ref mockRef;

    FormField* mockParent;



    void SetUp() override {

        mockDoc = new PDFDoc();

        mockParent = new FormField(mockDoc, std::move(mockObject), mockRef);

    }



    void TearDown() override {

        delete mockParent;

        delete mockDoc;

    }

};



TEST_F(FormFieldChoiceTest_921, CommitOnSelChange_ReturnsTrue_921) {

    FormFieldChoice formFieldChoice(mockDoc, std::move(mockObject), mockRef, mockParent, nullptr);

    EXPECT_TRUE(formFieldChoice.commitOnSelChange());

}



TEST_F(FormFieldChoiceTest_921, CommitOnSelChange_ReturnsFalse_921) {

    FormFieldChoice formFieldChoice(mockDoc, std::move(mockObject), mockRef, mockParent, nullptr);

    // Assuming we can modify the protected member to test different scenarios

    formFieldChoice.doCommitOnSelChange = false;

    EXPECT_FALSE(formFieldChoice.commitOnSelChange());

}



TEST_F(FormFieldChoiceTest_921, GetNumChoices_ReturnsZero_921) {

    FormFieldChoice formFieldChoice(mockDoc, std::move(mockObject), mockRef, mockParent, nullptr);

    EXPECT_EQ(0, formFieldChoice.getNumChoices());

}



TEST_F(FormFieldChoiceTest_921, GetSelectedChoice_ReturnsNullptr_921) {

    FormFieldChoice formFieldChoice(mockDoc, std::move(mockObject), mockRef, mockParent, nullptr);

    EXPECT_EQ(nullptr, formFieldChoice.getSelectedChoice());

}



TEST_F(FormFieldChoiceTest_921, IsCombo_ReturnsFalse_921) {

    FormFieldChoice formFieldChoice(mockDoc, std::move(mockObject), mockRef, mockParent, nullptr);

    EXPECT_FALSE(formFieldChoice.isCombo());

}



TEST_F(FormFieldChoiceTest_921, HasEdit_ReturnsFalse_921) {

    FormFieldChoice formFieldChoice(mockDoc, std::move(mockObject), mockRef, mockParent, nullptr);

    EXPECT_FALSE(formFieldChoice.hasEdit());

}



TEST_F(FormFieldChoiceTest_921, IsMultiSelect_ReturnsFalse_921) {

    FormFieldChoice formFieldChoice(mockDoc, std::move(mockObject), mockRef, mockParent, nullptr);

    EXPECT_FALSE(formFieldChoice.isMultiSelect());

}



TEST_F(FormFieldChoiceTest_921, NoSpellCheck_ReturnsFalse_921) {

    FormFieldChoice formFieldChoice(mockDoc, std::move(mockObject), mockRef, mockParent, nullptr);

    EXPECT_FALSE(formFieldChoice.noSpellCheck());

}



TEST_F(FormFieldChoiceTest_921, IsListBox_ReturnsTrue_921) {

    FormFieldChoice formFieldChoice(mockDoc, std::move(mockObject), mockRef, mockParent, nullptr);

    EXPECT_TRUE(formFieldChoice.isListBox());

}



TEST_F(FormFieldChoiceTest_921, GetTopIndex_ReturnsZero_921) {

    FormFieldChoice formFieldChoice(mockDoc, std::move(mockObject), mockRef, mockParent, nullptr);

    EXPECT_EQ(0, formFieldChoice.getTopIndex());

}
