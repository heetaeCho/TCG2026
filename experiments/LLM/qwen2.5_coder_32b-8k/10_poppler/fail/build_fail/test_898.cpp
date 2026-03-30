#include <gtest/gtest.h>

#include "Form.h"



class FormFieldButtonTest_898 : public ::testing::Test {

protected:

    PDFDoc* doc;

    Ref ref;

    FormField* parent;

    std::set<int>* usedParents;



    void SetUp() override {

        doc = nullptr; // Assuming we do not need a real PDFDoc object for these tests

        ref.num = 0;

        ref.gen = 0;

        parent = nullptr;

        usedParents = new std::set<int>();

    }



    void TearDown() override {

        delete usedParents;

    }

};



TEST_F(FormFieldButtonTest_898, DefaultAppearanceStateReturnsNullWhenNotName_898) {

    FormFieldButton formFieldButton(doc, Object(Object::objNone), ref, parent, usedParents);

    EXPECT_EQ(formFieldButton.getDefaultAppearanceState(), nullptr);

}



TEST_F(FormFieldButtonTest_898, DefaultAppearanceStateReturnsCorrectName_898) {

    std::string name = "testState";

    FormFieldButton formFieldButton(doc, Object(Object::objName, name), ref, parent, usedParents);

    EXPECT_STREQ(formFieldButton.getDefaultAppearanceState(), name.c_str());

}



TEST_F(FormFieldButtonTest_898, DefaultAppearanceStateBoundaryEmptyString_898) {

    std::string emptyName = "";

    FormFieldButton formFieldButton(doc, Object(Object::objName, emptyName), ref, parent, usedParents);

    EXPECT_STREQ(formFieldButton.getDefaultAppearanceState(), "");

}



TEST_F(FormFieldButtonTest_898, DefaultAppearanceStateBoundaryLargeString_898) {

    std::string largeName(1024, 'a');

    FormFieldButton formFieldButton(doc, Object(Object::objName, largeName), ref, parent, usedParents);

    EXPECT_STREQ(formFieldButton.getDefaultAppearanceState(), largeName.c_str());

}
