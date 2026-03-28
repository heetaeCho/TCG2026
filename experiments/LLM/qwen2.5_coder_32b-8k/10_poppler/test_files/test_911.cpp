#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/Form.h"



class FormFieldTextTest_911 : public ::testing::Test {

protected:

    PDFDoc* docA;

    Object dictObj;

    Ref ref;

    FormField* parent;

    std::set<int> usedParentsSet;

    int usedParentsInt;



    void SetUp() override {

        // Initialize necessary objects for the test

        docA = nullptr;  // Assuming PDFDoc constructor is not needed here

        parent = nullptr;  // Assuming FormField constructor is not needed here

        usedParentsSet.clear();

        usedParentsInt = 0;

    }



    FormFieldText* createFormFieldText() {

        return new FormFieldText(docA, std::move(dictObj), ref, parent, &usedParentsSet);

    }

};



TEST_F(FormFieldTextTest_911, GetMaxLen_DefaultValue_911) {

    FormFieldText formFieldText = *createFormFieldText();

    EXPECT_EQ(formFieldText.getMaxLen(), 0); // Assuming default maxLen is 0

}



TEST_F(FormFieldTextTest_911, IsMultiline_DefaultValue_911) {

    FormFieldText formFieldText = *createFormFieldText();

    EXPECT_FALSE(formFieldText.isMultiline());

}



TEST_F(FormFieldTextTest_911, IsPassword_DefaultValue_911) {

    FormFieldText formFieldText = *createFormFieldText();

    EXPECT_FALSE(formFieldText.isPassword());

}



TEST_F(FormFieldTextTest_911, IsFileSelect_DefaultValue_911) {

    FormFieldText formFieldText = *createFormFieldText();

    EXPECT_FALSE(formFieldText.isFileSelect());

}



TEST_F(FormFieldTextTest_911, NoSpellCheck_DefaultValue_911) {

    FormFieldText formFieldText = *createFormFieldText();

    EXPECT_FALSE(formFieldText.noSpellCheck());

}



TEST_F(FormFieldTextTest_911, NoScroll_DefaultValue_911) {

    FormFieldText formFieldText = *createFormFieldText();

    EXPECT_FALSE(formFieldText.noScroll());

}



TEST_F(FormFieldTextTest_911, IsComb_DefaultValue_911) {

    FormFieldText formFieldText = *createFormFieldText();

    EXPECT_FALSE(formFieldText.isComb());

}



TEST_F(FormFieldTextTest_911, IsRichText_DefaultValue_911) {

    FormFieldText formFieldText = *createFormFieldText();

    EXPECT_FALSE(formFieldText.isRichText());

}



TEST_F(FormFieldTextTest_911, TokenizeDA_EmptyString_ReturnsNullopt_911) {

    std::string daString = "";

    std::vector<std::string> daToks;

    const char* searchTok = "someToken";

    auto result = FormFieldText::tokenizeDA(daString, &daToks, searchTok);

    EXPECT_FALSE(result.has_value());

}



TEST_F(FormFieldTextTest_911, TokenizeDA_ValidString_ReturnsIndex_911) {

    std::string daString = "someToken otherToken";

    std::vector<std::string> daToks;

    const char* searchTok = "someToken";

    auto result = FormFieldText::tokenizeDA(daString, &daToks, searchTok);

    EXPECT_TRUE(result.has_value());

    EXPECT_EQ(*result, 0); // Assuming the first token is at index 0

}



TEST_F(FormFieldTextTest_911, TokenizeDA_TokenNotFound_ReturnsNullopt_911) {

    std::string daString = "otherToken someOtherToken";

    std::vector<std::string> daToks;

    const char* searchTok = "someToken";

    auto result = FormFieldText::tokenizeDA(daString, &daToks, searchTok);

    EXPECT_FALSE(result.has_value());

}
