#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Form.h"



class FormFieldChoiceTest_914 : public ::testing::Test {

protected:

    PDFDoc* docA;

    Object aobj;

    Ref ref;

    FormField* parent;

    std::set<int>* usedParents;



    void SetUp() override {

        // Initialize necessary objects for the test

        docA = nullptr;  // Assuming these are not required to be actual instances for this test

        parent = nullptr;

        usedParents = new std::set<int>();

    }



    void TearDown() override {

        delete usedParents;

    }



    FormFieldChoice* createFormFieldChoice(int numChoices) {

        FormFieldChoice* formFieldChoice = new FormFieldChoice(docA, std::move(aobj), ref, parent, usedParents);

        // Manually setting up choices for testing

        formFieldChoice->choices = new ChoiceOpt[numChoices];

        formFieldChoice->numChoices = numChoices;

        for (int i = 0; i < numChoices; ++i) {

            formFieldChoice->choices[i].exportVal.reset(new GooString(std::string("ExportVal") + std::to_string(i)));

            formFieldChoice->choices[i].optionName.reset(new GooString(std::string("OptionName") + std::to_string(i)));

        }

        return formFieldChoice;

    }

};



TEST_F(FormFieldChoiceTest_914, GetExportVal_NormalOperation_914) {

    int numChoices = 3;

    FormFieldChoice* formFieldChoice = createFormFieldChoice(numChoices);



    for (int i = 0; i < numChoices; ++i) {

        EXPECT_EQ(std::string(formFieldChoice->getExportVal(i)->c_str()), "ExportVal" + std::to_string(i));

    }



    delete formFieldChoice;

}



TEST_F(FormFieldChoiceTest_914, GetExportVal_BoundaryCondition_914) {

    int numChoices = 0;

    FormFieldChoice* formFieldChoice = createFormFieldChoice(numChoices);



    EXPECT_EQ(formFieldChoice->getExportVal(0), nullptr);



    delete formFieldChoice;

}



TEST_F(FormFieldChoiceTest_914, GetExportVal_OutOfBounds_914) {

    int numChoices = 2;

    FormFieldChoice* formFieldChoice = createFormFieldChoice(numChoices);



    EXPECT_EQ(formFieldChoice->getExportVal(-1), nullptr);

    EXPECT_EQ(formFieldChoice->getExportVal(2), nullptr); // Out of bounds



    delete formFieldChoice;

}
