#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/Form.h"



class FormFieldTextTest : public ::testing::Test {

protected:

    PDFDoc* doc;

    Object dictObj;

    Ref ref;

    FormField* parent;

    std::set<int>* usedParents;



    void SetUp() override {

        // Initialize the necessary objects for constructing a FormFieldText instance

        doc = new PDFDoc();

        dictObj.initNull();

        ref.num = 0;

        ref.gen = 0;

        parent = nullptr;

        usedParents = new std::set<int>();

    }



    void TearDown() override {

        // Clean up the allocated objects

        delete doc;

        delete usedParents;

    }

};



TEST_F(FormFieldTextTest_905, IsPassword_ReturnsTrue_WhenPasswordIsSet_905) {

    FormFieldText formFieldText(doc, std::move(dictObj), ref, parent, *usedParents);

    formFieldText.password = true; // Directly setting for testing purposes



    EXPECT_TRUE(formFieldText.isPassword());

}



TEST_F(FormFieldTextTest_905, IsPassword_ReturnsFalse_WhenPasswordIsNotSet_905) {

    FormFieldText formFieldText(doc, std::move(dictObj), ref, parent, *usedParents);

    formFieldText.password = false; // Directly setting for testing purposes



    EXPECT_FALSE(formFieldText.isPassword());

}



TEST_F(FormFieldTextTest_905, IsMultiline_ReturnsFalse_ByDefault_905) {

    FormFieldText formFieldText(doc, std::move(dictObj), ref, parent, *usedParents);



    EXPECT_FALSE(formFieldText.isMultiline());

}



TEST_F(FormFieldTextTest_905, IsFileSelect_ReturnsFalse_ByDefault_905) {

    FormFieldText formFieldText(doc, std::move(dictObj), ref, parent, *usedParents);



    EXPECT_FALSE(formFieldText.isFileSelect());

}



TEST_F(FormFieldTextTest_905, NoSpellCheck_ReturnsFalse_ByDefault_905) {

    FormFieldText formFieldText(doc, std::move(dictObj), ref, parent, *usedParents);



    EXPECT_FALSE(formFieldText.noSpellCheck());

}



TEST_F(FormFieldTextTest_905, NoScroll_ReturnsFalse_ByDefault_905) {

    FormFieldText formFieldText(doc, std::move(dictObj), ref, parent, *usedParents);



    EXPECT_FALSE(formFieldText.noScroll());

}



TEST_F(FormFieldTextTest_905, IsComb_ReturnsFalse_ByDefault_905) {

    FormFieldText formFieldText(doc, std::move(dictObj), ref, parent, *usedParents);



    EXPECT_FALSE(formFieldText.isComb());

}



TEST_F(FormFieldTextTest_905, IsRichText_ReturnsFalse_ByDefault_905) {

    FormFieldText formFieldText(doc, std::move(dictObj), ref, parent, *usedParents);



    EXPECT_FALSE(formFieldText.isRichText());

}
