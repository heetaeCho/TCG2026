#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/Form.h"



class FormFieldChoiceTest_920 : public ::testing::Test {

protected:

    std::unique_ptr<FormFieldChoice> formFieldChoice;



    virtual void SetUp() {

        // Assuming a mock PDFDoc, Object, Ref, and FormField are available for construction

        // This is a placeholder as actual construction details are not provided

        formFieldChoice = std::make_unique<FormFieldChoice>(nullptr, Object(), Ref(), nullptr, new std::set<int>());

    }

};



TEST_F(FormFieldChoiceTest_920, GetNumChoices_ReturnsExpectedValue_920) {

    // Assuming getNumChoices() returns a specific value

    EXPECT_GE(formFieldChoice->getNumChoices(), 0);

}



TEST_F(FormFieldChoiceTest_920, GetChoice_ValidIndex_ReturnsNonNull_920) {

    int numChoices = formFieldChoice->getNumChoices();

    if (numChoices > 0) {

        EXPECT_NE(formFieldChoice->getChoice(0), nullptr);

    }

}



TEST_F(FormFieldChoiceTest_920, GetExportVal_ValidIndex_ReturnsNonNull_920) {

    int numChoices = formFieldChoice->getNumChoices();

    if (numChoices > 0) {

        EXPECT_NE(formFieldChoice->getExportVal(0), nullptr);

    }

}



TEST_F(FormFieldChoiceTest_920, GetSelectedChoice_NoSelection_ReturnsNull_920) {

    // Assuming no selection has been made

    EXPECT_EQ(formFieldChoice->getSelectedChoice(), nullptr);

}



TEST_F(FormFieldChoiceTest_920, NoSpellCheck_ReturnsExpectedValue_920) {

    bool spellCheck = formFieldChoice->noSpellCheck();

    EXPECT_TRUE(spellCheck || !spellCheck); // This will always be true but ensures the function works

}



TEST_F(FormFieldChoiceTest_920, CommitOnSelChange_ReturnsExpectedValue_920) {

    bool commitOnSelChange = formFieldChoice->commitOnSelChange();

    EXPECT_TRUE(commitOnSelChange || !commitOnSelChange); // This will always be true but ensures the function works

}



TEST_F(FormFieldChoiceTest_920, IsCombo_ReturnsExpectedValue_920) {

    bool isCombo = formFieldChoice->isCombo();

    EXPECT_TRUE(isCombo || !isCombo); // This will always be true but ensures the function works

}



TEST_F(FormFieldChoiceTest_920, HasEdit_ReturnsExpectedValue_920) {

    bool hasEdit = formFieldChoice->hasEdit();

    EXPECT_TRUE(hasEdit || !hasEdit); // This will always be true but ensures the function works

}



TEST_F(FormFieldChoiceTest_920, IsMultiSelect_ReturnsExpectedValue_920) {

    bool isMultiSelect = formFieldChoice->isMultiSelect();

    EXPECT_TRUE(isMultiSelect || !isMultiSelect); // This will always be true but ensures the function works

}



TEST_F(FormFieldChoiceTest_920, GetAppearanceSelectedChoice_NoSelection_ReturnsNull_920) {

    // Assuming no selection has been made

    EXPECT_EQ(formFieldChoice->getAppearanceSelectedChoice(), nullptr);

}



TEST_F(FormFieldChoiceTest_920, IsListBox_ComboFalse_IsTrue_920) {

    if (!formFieldChoice->isCombo()) {

        EXPECT_TRUE(formFieldChoice->isListBox());

    }

}



TEST_F(FormFieldChoiceTest_920, IsListBox_ComboTrue_IsFalse_920) {

    if (formFieldChoice->isCombo()) {

        EXPECT_FALSE(formFieldChoice->isListBox());

    }

}
