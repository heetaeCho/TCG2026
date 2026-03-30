#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/Form.h"

#include <memory>

#include <optional>



using namespace poppler;



class FormFieldTextTest_910 : public ::testing::Test {

protected:

    PDFDoc* doc;

    Object dictObj;

    Ref ref;

    FormField* parent;

    std::set<int> usedParentsSet;

    int usedParentsInt;

    std::unique_ptr<FormFieldText> formFieldText;



    void SetUp() override {

        doc = nullptr; // Assuming setup for these is done elsewhere in actual tests

        dictObj = Object(); // Assuming setup for these is done elsewhere in actual tests

        ref = Ref(0, 0); // Assuming setup for these is done elsewhere in actual tests

        parent = nullptr; // Assuming setup for these is done elsewhere in actual tests

        usedParentsSet = std::set<int>();

        usedParentsInt = 0;

        formFieldText = std::make_unique<FormFieldText>(doc, std::move(dictObj), ref, parent, &usedParentsSet);

    }

};



TEST_F(FormFieldTextTest_910, IsRichText_DefaultValue_False_910) {

    EXPECT_FALSE(formFieldText->isRichText());

}



// Since the richText flag is protected and not modifiable through public interface,

// we can only test its default value. Additional tests would require setting this

// value which is not possible without internal access or a setter method.



TEST_F(FormFieldTextTest_910, GetContent_DefaultValue_Nullptr_910) {

    EXPECT_EQ(formFieldText->getContent(), nullptr);

}



TEST_F(FormFieldTextTest_910, GetAppearanceContent_DefaultValue_Nullptr_910) {

    EXPECT_EQ(formFieldText->getAppearanceContent(), nullptr);

}



TEST_F(FormFieldTextTest_910, IsMultiline_DefaultValue_False_910) {

    EXPECT_FALSE(formFieldText->isMultiline());

}



TEST_F(FormFieldTextTest_910, IsPassword_DefaultValue_False_910) {

    EXPECT_FALSE(formFieldText->isPassword());

}



TEST_F(FormFieldTextTest_910, IsFileSelect_DefaultValue_False_910) {

    EXPECT_FALSE(formFieldText->isFileSelect());

}



TEST_F(FormFieldTextTest_910, NoSpellCheck_DefaultValue_False_910) {

    EXPECT_FALSE(formFieldText->noSpellCheck());

}



TEST_F(FormFieldTextTest_910, NoScroll_DefaultValue_False_910) {

    EXPECT_FALSE(formFieldText->noScroll());

}



TEST_F(FormFieldTextTest_910, IsComb_DefaultValue_False_910) {

    EXPECT_FALSE(formFieldText->isComb());

}



TEST_F(FormFieldTextTest_910, GetMaxLen_DefaultValue_Zero_910) {

    EXPECT_EQ(formFieldText->getMaxLen(), 0);

}
