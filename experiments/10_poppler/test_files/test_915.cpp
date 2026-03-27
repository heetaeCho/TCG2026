#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/Form.h"



class FormFieldChoiceTest_915 : public ::testing::Test {

protected:

    PDFDoc* docA;

    Object aobj;

    Ref ref;

    FormField* parent;

    std::set<int>* usedParents;

    FormFieldChoice* formFieldChoice;



    void SetUp() override {

        // Assuming necessary initialization for PDFDoc, Object, Ref, and FormField

        // These are placeholders as actual initialization depends on the context.

        docA = nullptr; 

        aobj = Object(); 

        ref = Ref();

        parent = nullptr;

        usedParents = new std::set<int>();

        formFieldChoice = new FormFieldChoice(docA, std::move(aobj), ref, parent, usedParents);

    }



    void TearDown() override {

        delete usedParents;

        delete formFieldChoice;

    }

};



TEST_F(FormFieldChoiceTest_915, GetAppearanceSelectedChoice_NormalOperation_915) {

    // Assuming there is a selected choice

    const GooString* result = formFieldChoice->getAppearanceSelectedChoice();

    EXPECT_NE(result, nullptr);

}



TEST_F(FormFieldChoiceTest_915, GetAppearanceSelectedChoice_NoAppearanceSelectedChoice_915) {

    // Simulate no appearance selected choice by setting it to nullptr

    formFieldChoice->appearanceSelectedChoice.reset(nullptr);

    const GooString* result = formFieldChoice->getAppearanceSelectedChoice();

    EXPECT_EQ(result, formFieldChoice->getSelectedChoice());

}



TEST_F(FormFieldChoiceTest_915, GetAppearanceSelectedChoice_BoundaryCondition_915) {

    // Assuming boundary conditions like empty selection

    formFieldChoice->appearanceSelectedChoice.reset(nullptr);

    const GooString* result = formFieldChoice->getAppearanceSelectedChoice();

    EXPECT_EQ(result, formFieldChoice->getSelectedChoice());

}



TEST_F(FormFieldChoiceTest_915, GetAppearanceSelectedChoice_ExceptionalCase_915) {

    // Assuming exceptional case like invalid selection

    formFieldChoice->appearanceSelectedChoice.reset(nullptr);

    const GooString* result = formFieldChoice->getAppearanceSelectedChoice();

    EXPECT_EQ(result, formFieldChoice->getSelectedChoice());

}
