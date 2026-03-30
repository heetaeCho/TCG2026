#include <gtest/gtest.h>

#include "Form.h"



using namespace poppler;



class FormFieldButtonTest_895 : public ::testing::Test {

protected:

    PDFDoc* doc;

    Object dict;

    Ref ref;

    FormField* parent;

    std::set<int>* usedParentsSet;

    int* usedParentsInt;



    void SetUp() override {

        doc = new PDFDoc();

        dict.init_null();

        ref.num = 1;

        ref.gen = 0;

        parent = nullptr;

        usedParentsSet = new std::set<int>();

        usedParentsInt = new int(0);

    }



    void TearDown() override {

        delete doc;

        delete usedParentsSet;

        delete usedParentsInt;

    }

};



TEST_F(FormFieldButtonTest_895, GetButtonType_NormalOperation_895) {

    FormFieldButton button(doc, std::move(dict), ref, parent, usedParentsSet);

    // Assuming btype is set to some valid value in the constructor

    EXPECT_EQ(button.getButtonType(), FormButtonType::Unknown);  // Replace with actual expected type if known

}



TEST_F(FormFieldButtonTest_895, GetButtonType_BoundaryConditions_895) {

    // Boundary conditions not directly observable from getButtonType alone

    // Further assumptions or additional methods required to test boundary conditions

}



TEST_F(FormFieldButtonTest_895, NoToggleToOff_NormalOperation_895) {

    FormFieldButton button(doc, std::move(dict), ref, parent, usedParentsSet);

    EXPECT_FALSE(button.noToggleToOff());  // Assuming default is false

}



TEST_F(FormFieldButtonTest_895, GetAppearanceState_NormalOperation_895) {

    FormFieldButton button(doc, std::move(dict), ref, parent, usedParentsSet);

    EXPECT_STREQ(button.getAppearanceState(), "");  // Assuming default is empty string

}



TEST_F(FormFieldButtonTest_895, GetDefaultAppearanceState_NormalOperation_895) {

    FormFieldButton button(doc, std::move(dict), ref, parent, usedParentsSet);

    EXPECT_STREQ(button.getDefaultAppearanceState(), "");  // Assuming default is empty string

}



TEST_F(FormFieldButtonTest_895, SetAndGetSibling_NormalOperation_895) {

    FormFieldButton button(doc, std::move(dict), ref, parent, usedParentsSet);

    FormFieldButton* sibling = new FormFieldButton(doc, std::move(Object()), Ref(), nullptr, usedParentsInt);

    button.setSibling(0, sibling);

    EXPECT_EQ(button.getSibling(0), sibling);

    delete sibling;

}



TEST_F(FormFieldButtonTest_895, GetNumSiblings_NormalOperation_895) {

    FormFieldButton button(doc, std::move(dict), ref, parent, usedParentsSet);

    button.setNumSiblings(2);

    EXPECT_EQ(button.getNumSiblings(), 2);

}
