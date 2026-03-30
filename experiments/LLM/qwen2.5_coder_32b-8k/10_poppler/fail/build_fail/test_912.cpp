#include <gtest/gtest.h>

#include "Form.h"



class FormFieldChoiceTest : public ::testing::Test {

protected:

    PDFDoc doc;

    Object obj;

    Ref ref;

    std::set<int> usedParentsSet;

    int usedParentsArray[1];

    FormFieldChoice* formFieldChoice;



    void SetUp() override {

        formFieldChoice = new FormFieldChoice(&doc, std::move(obj), ref, nullptr, &usedParentsSet);

    }



    void TearDown() override {

        delete formFieldChoice;

    }

};



TEST_F(FormFieldChoiceTest_912, GetNumChoices_ReturnsZeroByDefault_912) {

    EXPECT_EQ(formFieldChoice->getNumChoices(), 0);

}



TEST_F(FormFieldChoiceTest_912, GetSelectedChoice_ReturnsNullptrWhenNoSelection_912) {

    EXPECT_EQ(formFieldChoice->getSelectedChoice(), nullptr);

}



TEST_F(FormFieldChoiceTest_912, GetEditChoice_ReturnsNullptrByDefault_912) {

    EXPECT_EQ(formFieldChoice->getEditChoice(), nullptr);

}



TEST_F(FormFieldChoiceTest_912, GetNumSelected_ReturnsZeroByDefault_912) {

    EXPECT_EQ(formFieldChoice->getNumSelected(), 0);

}



TEST_F(FormFieldChoiceTest_912, IsCombo_ReturnsFalseByDefault_912) {

    EXPECT_FALSE(formFieldChoice->isCombo());

}



TEST_F(FormFieldChoiceTest_912, HasEdit_ReturnsFalseByDefault_912) {

    EXPECT_FALSE(formFieldChoice->hasEdit());

}



TEST_F(FormFieldChoiceTest_912, IsMultiSelect_ReturnsFalseByDefault_912) {

    EXPECT_FALSE(formFieldChoice->isMultiSelect());

}



TEST_F(FormFieldChoiceTest_912, NoSpellCheck_ReturnsFalseByDefault_912) {

    EXPECT_FALSE(formFieldChoice->noSpellCheck());

}



TEST_F(FormFieldChoiceTest_912, CommitOnSelChange_ReturnsFalseByDefault_912) {

    EXPECT_FALSE(formFieldChoice->commitOnSelChange());

}



TEST_F(FormFieldChoiceTest_912, IsListBox_ReturnsTrueWhenNotCombo_912) {

    EXPECT_TRUE(formFieldChoice->isListBox());

}



TEST_F(FormFieldChoiceTest_912, GetTopIndex_ReturnsZeroByDefault_912) {

    EXPECT_EQ(formFieldChoice->getTopIndex(), 0);

}



TEST_F(FormFieldChoiceTest_912, GetAppearanceSelectedChoice_ReturnsNullptrByDefault_912) {

    EXPECT_EQ(formFieldChoice->getAppearanceSelectedChoice(), nullptr);

}
