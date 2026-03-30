#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/Form.h"

#include <memory>

#include <string>



class FormFieldTextTest_907 : public ::testing::Test {

protected:

    std::unique_ptr<FormFieldText> formFieldText;



    void SetUp() override {

        // Assuming a way to create an instance of FormFieldText

        PDFDoc* docA = nullptr;

        Object dictObj; // This should be properly initialized in real use case

        Ref ref;

        FormField* parent = nullptr;

        std::set<int> usedParents;



        formFieldText = std::make_unique<FormFieldText>(docA, std::move(dictObj), ref, parent, &usedParents);

    }

};



TEST_F(FormFieldTextTest_907, NoSpellCheckReturnsFalseByDefault_907) {

    EXPECT_FALSE(formFieldText->noSpellCheck());

}



// Assuming there's a way to set doNotSpellCheck to true

// This test case is hypothetical as the current interface does not provide a setter for doNotSpellCheck

// TEST_F(FormFieldTextTest_907, NoSpellCheckReturnsTrueWhenSet_907) {

//     formFieldText->setDoNotSpellCheck(true); // Hypothetical function

//     EXPECT_TRUE(formFieldText->noSpellCheck());

// }



TEST_F(FormFieldTextTest_907, GetContentReturnsNullPointerInitially_907) {

    EXPECT_EQ(nullptr, formFieldText->getContent());

}



TEST_F(FormFieldTextTest_907, SetContentUpdatesContentPointer_907) {

    auto content = std::make_unique<GooString>("Sample Content");

    formFieldText->setContent(std::move(content));

    EXPECT_NE(nullptr, formFieldText->getContent());

}



TEST_F(FormFieldTextTest_907, GetAppearanceContentReturnsNullPointerInitially_907) {

    EXPECT_EQ(nullptr, formFieldText->getAppearanceContent());

}



TEST_F(FormFieldTextTest_907, SetAppearanceContentUpdatesAppearanceContentPointer_907) {

    auto appearanceContent = std::make_unique<GooString>("Sample Appearance Content");

    formFieldText->setAppearanceContent(std::move(appearanceContent));

    EXPECT_NE(nullptr, formFieldText->getAppearanceContent());

}



TEST_F(FormFieldTextTest_907, IsMultilineReturnsFalseByDefault_907) {

    EXPECT_FALSE(formFieldText->isMultiline());

}



TEST_F(FormFieldTextTest_907, IsPasswordReturnsFalseByDefault_907) {

    EXPECT_FALSE(formFieldText->isPassword());

}



TEST_F(FormFieldTextTest_907, IsFileSelectReturnsFalseByDefault_907) {

    EXPECT_FALSE(formFieldText->isFileSelect());

}



TEST_F(FormFieldTextTest_907, NoScrollReturnsFalseByDefault_907) {

    EXPECT_FALSE(formFieldText->noScroll());

}



TEST_F(FormFieldTextTest_907, IsCombReturnsFalseByDefault_907) {

    EXPECT_FALSE(formFieldText->isComb());

}



TEST_F(FormFieldTextTest_907, IsRichTextReturnsFalseByDefault_907) {

    EXPECT_FALSE(formFieldText->isRichText());

}



// Assuming getMaxLen has a default value or can be set externally

// This test case is hypothetical as the current interface does not provide a setter for maxLen

// TEST_F(FormFieldTextTest_907, GetMaxLenReturnsDefaultValue_907) {

//     EXPECT_EQ(expectedDefaultMaxLen, formFieldText->getMaxLen());

// }
