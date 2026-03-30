#include <gtest/gtest.h>

#include "Form.h"



using namespace std;



class FormFieldChoiceTest_919 : public ::testing::Test {

protected:

    PDFDoc* mock_doc;

    Object mock_obj;

    Ref mock_ref;

    FormField* mock_parent;

    set<int>* mock_usedParents;

    FormFieldChoice* form_field_choice;



    void SetUp() override {

        mock_doc = nullptr; // Assuming no specific behavior is needed from mock_doc

        mock_obj = Object(); // Default constructed object

        mock_ref = Ref(0, 0); // Default reference

        mock_parent = nullptr; // Assuming no specific behavior is needed from mock_parent

        mock_usedParents = new set<int>(); // Empty set for used parents



        form_field_choice = new FormFieldChoice(mock_doc, std::move(mock_obj), mock_ref, mock_parent, mock_usedParents);

    }



    void TearDown() override {

        delete form_field_choice;

        delete mock_usedParents;

    }

};



TEST_F(FormFieldChoiceTest_919, IsMultiSelect_DefaultValue_False_919) {

    EXPECT_FALSE(form_field_choice->isMultiSelect());

}



// Assuming multiselect can be set through some mechanism not exposed in the interface

// If there's a way to set multiselect, additional tests should be added to verify that behavior



TEST_F(FormFieldChoiceTest_919, IsCombo_DefaultValue_False_919) {

    EXPECT_FALSE(form_field_choice->isCombo());

}



TEST_F(FormFieldChoiceTest_919, HasEdit_DefaultValue_False_919) {

    EXPECT_FALSE(form_field_choice->hasEdit());

}



TEST_F(FormFieldChoiceTest_919, CommitOnSelChange_DefaultValue_False_919) {

    EXPECT_FALSE(form_field_choice->commitOnSelChange());

}



TEST_F(FormFieldChoiceTest_919, IsListBox_DefaultValue_True_919) {

    EXPECT_TRUE(form_field_choice->isListBox());

}



TEST_F(FormFieldChoiceTest_919, GetTopIndex_DefaultValue_Zero_919) {

    EXPECT_EQ(0, form_field_choice->getTopIndex());

}



TEST_F(FormFieldChoiceTest_919, GetNumChoices_DefaultValue_Zero_919) {

    EXPECT_EQ(0, form_field_choice->getNumChoices());

}



TEST_F(FormFieldChoiceTest_919, GetSelectedChoice_NoSelection_ReturnsNull_919) {

    EXPECT_EQ(nullptr, form_field_choice->getSelectedChoice());

}



TEST_F(FormFieldChoiceTest_919, GetEditChoice_NoEdit_ReturnsNull_919) {

    EXPECT_EQ(nullptr, form_field_choice->getEditChoice());

}



TEST_F(FormFieldChoiceTest_919, GetNumSelected_DefaultValue_Zero_919) {

    EXPECT_EQ(0, form_field_choice->getNumSelected());

}



TEST_F(FormFieldChoiceTest_919, NoSpellCheck_DefaultValue_False_919) {

    EXPECT_FALSE(form_field_choice->noSpellCheck());

}



// Additional tests for boundary conditions and exceptional cases would require more information about the class behavior
