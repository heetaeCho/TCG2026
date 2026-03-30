#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/poppler/poppler/Form.h"



class FormFieldTest_888 : public ::testing::Test {

protected:

    PDFDoc* docA;

    Object aobj;

    Ref aref;

    FormField parentField;

    std::set<int> usedParentsSet;

    int usedParentsInt;

    FormFieldType fieldType;



    void SetUp() override {

        // Initialize test objects and variables

        docA = nullptr;  // Assuming PDFDoc is properly initialized elsewhere in the codebase

        aref.num = 0;

        aref.gen = 1;

        usedParentsSet.clear();

        usedParentsInt = 0;

        fieldType = formFieldTypeText;



        // Create a FormField instance for testing

        testFormField = std::make_unique<FormField>(docA, std::move(aobj), aref, &parentField, &usedParentsSet, fieldType);

    }



    std::unique_ptr<FormField> testFormField;

};



TEST_F(FormFieldTest_888, GetAlternateUiName_ReturnsCorrectPointer_888) {

    // Arrange

    const GooString expectedAlternateUiName("Test Alternate UI Name");

    testFormField->alternateUiName = std::make_unique<GooString>(expectedAlternateUiName);



    // Act

    const GooString* result = testFormField->getAlternateUiName();



    // Assert

    ASSERT_NE(result, nullptr);

    EXPECT_EQ(*result, expectedAlternateUiName);

}



TEST_F(FormFieldTest_888, GetAlternateUiName_ReturnsNullWhenNotSet_888) {

    // Arrange (already set up in SetUp)



    // Act

    const GooString* result = testFormField->getAlternateUiName();



    // Assert

    EXPECT_EQ(result, nullptr);

}
