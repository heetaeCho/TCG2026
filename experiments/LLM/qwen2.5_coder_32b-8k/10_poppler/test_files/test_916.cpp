#include <gtest/gtest.h>

#include "Form.h"



using namespace poppler;



class FormFieldChoiceTest_916 : public ::testing::Test {

protected:

    PDFDoc* docA;

    Object aobj;

    Ref ref;

    FormField* parent;

    std::set<int>* usedParents;

    std::unique_ptr<FormFieldChoice> formFieldChoice;



    void SetUp() override {

        docA = nullptr; // Assuming we cannot initialize this properly in the test context

        parent = nullptr; // Assuming we cannot initialize this properly in the test context

        usedParents = new std::set<int>();

        formFieldChoice.reset(new FormFieldChoice(docA, std::move(aobj), ref, parent, usedParents));

    }



    void TearDown() override {

        delete usedParents;

    }

};



TEST_F(FormFieldChoiceTest_916, IsSelected_ReturnsFalseForUnselectedIndex_916) {

    int index = 0; // Assuming there is at least one choice

    EXPECT_FALSE(formFieldChoice->isSelected(index));

}



TEST_F(FormFieldChoiceTest_916, IsSelected_ReturnsTrueForSelectedIndex_916) {

    int index = 0; // Assuming there is at least one choice

    formFieldChoice->select(index);

    EXPECT_TRUE(formFieldChoice->isSelected(index));

}



TEST_F(FormFieldChoiceTest_916, GetNumChoices_ReturnsZeroWhenNoChoices_916) {

    EXPECT_EQ(0, formFieldChoice->getNumChoices());

}



TEST_F(FormFieldChoiceTest_916, GetNumSelected_ReturnsZeroInitially_916) {

    EXPECT_EQ(0, formFieldChoice->getNumSelected());

}



TEST_F(FormFieldChoiceTest_916, GetNumSelected_ReturnsCorrectCountAfterSelection_916) {

    int index = 0; // Assuming there is at least one choice

    formFieldChoice->select(index);

    EXPECT_EQ(1, formFieldChoice->getNumSelected());

}



TEST_F(FormFieldChoiceTest_916, Toggle_SelectsIndexIfNotAlreadySelected_916) {

    int index = 0; // Assuming there is at least one choice

    formFieldChoice->toggle(index);

    EXPECT_TRUE(formFieldChoice->isSelected(index));

}



TEST_F(FormFieldChoiceTest_916, Toggle_DeselectsIndexIfAlreadySelected_916) {

    int index = 0; // Assuming there is at least one choice

    formFieldChoice->select(index);

    formFieldChoice->toggle(index);

    EXPECT_FALSE(formFieldChoice->isSelected(index));

}



TEST_F(FormFieldChoiceTest_916, DeselectAll_ClearsSelections_916) {

    int index = 0; // Assuming there is at least one choice

    formFieldChoice->select(index);

    formFieldChoice->deselectAll();

    EXPECT_FALSE(formFieldChoice->isSelected(index));

}



TEST_F(FormFieldChoiceTest_916, GetSelectedChoice_ReturnsNullptrWhenNoSelection_916) {

    EXPECT_EQ(nullptr, formFieldChoice->getSelectedChoice());

}



// Assuming the FormFieldChoice can have at least one choice for the following test

TEST_F(FormFieldChoiceTest_916, GetSelectedChoice_ReturnsCorrectChoiceAfterSelection_916) {

    int index = 0; // Assuming there is at least one choice

    formFieldChoice->select(index);

    const GooString* selectedChoice = formFieldChoice->getSelectedChoice();

    EXPECT_NE(nullptr, selectedChoice);

    // We cannot assert the content of the GooString without internal knowledge.

}



TEST_F(FormFieldChoiceTest_916, Reset_DeselectsAllChoices_916) {

    int index = 0; // Assuming there is at least one choice

    formFieldChoice->select(index);

    std::vector<std::string> excludedFields;

    formFieldChoice->reset(excludedFields);

    EXPECT_FALSE(formFieldChoice->isSelected(index));

}
