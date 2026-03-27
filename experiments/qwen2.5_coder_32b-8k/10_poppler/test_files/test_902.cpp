#include <gtest/gtest.h>

#include "Form.h"



class FormFieldTextTest_902 : public ::testing::Test {

protected:

    PDFDoc* mockDoc;

    Object dictObj;

    Ref ref;

    FormField* parent;

    std::set<int> usedParentsSet;

    int usedParentsInt;



    void SetUp() override {

        mockDoc = nullptr;  // Assuming PDFDoc is not needed for these tests or can be null

        parent = nullptr;   // Assuming parent is not needed for these tests or can be null

    }



    FormFieldText* createFormFieldTextWithContent(const std::string& content) {

        auto uniqueContent = std::make_unique<GooString>(content.c_str());

        FormFieldText* formFieldText = new FormFieldText(mockDoc, std::move(dictObj), ref, parent, &usedParentsSet);

        formFieldText->setContent(std::move(uniqueContent));

        return formFieldText;

    }

};



TEST_F(FormFieldTextTest_902, GetContent_ReturnsCorrectContent_902) {

    auto* formFieldText = createFormFieldTextWithContent("Sample Content");

    EXPECT_STREQ(formFieldText->getContent()->c_str(), "Sample Content");

    delete formFieldText;

}



TEST_F(FormFieldTextTest_902, GetContent_ReturnsNullWhenNoContentSet_902) {

    FormFieldText* formFieldText = new FormFieldText(mockDoc, std::move(dictObj), ref, parent, &usedParentsSet);

    EXPECT_EQ(formFieldText->getContent(), nullptr);

    delete formFieldText;

}



TEST_F(FormFieldTextTest_902, GetContent_BoundaryConditionEmptyString_902) {

    auto* formFieldText = createFormFieldTextWithContent("");

    EXPECT_STREQ(formFieldText->getContent()->c_str(), "");

    delete formFieldText;

}
