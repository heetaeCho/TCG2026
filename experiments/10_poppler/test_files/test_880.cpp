#include <gtest/gtest.h>

#include "Form.h"

#include <gmock/gmock.h>



using namespace ::testing;



class MockPDFDoc : public PDFDoc {

public:

    MOCK_METHOD(void, someMethod, (), (const));

};



class MockObject : public Object {

public:

    MOCK_METHOD(void, someMethod, (), (const));

};



class FormFieldTest_880 : public ::testing::Test {

protected:

    Ref ref;

    MockPDFDoc mockDocA;

    MockObject mockObj;

    std::set<int> usedParentsSet;

    int* usedParentsPtr = new int[1]{0};

    FormFieldType fieldType = formButton;



    void SetUp() override {

        ref.num = 1;

        ref.gen = 2;

    }



    void TearDown() override {

        delete[] usedParentsPtr;

    }

};



TEST_F(FormFieldTest_880, ConstructorWithSetUsedParents_880) {

    FormField formField(&mockDocA, std::move(mockObj), ref, nullptr, &usedParentsSet, fieldType);

}



TEST_F(FormFieldTest_880, ConstructorWithIntPtrUsedParents_880) {

    FormField formField(&mockDocA, std::move(mockObj), ref, nullptr, usedParentsPtr, fieldType);

}



TEST_F(FormFieldTest_880, GetRefReturnsCorrectValue_880) {

    FormField formField(&mockDocA, std::move(mockObj), ref, nullptr, &usedParentsSet, fieldType);

    EXPECT_EQ(formField.getRef(), ref);

}



TEST_F(FormFieldTest_880, SetReadOnlyAndGetReadOnlyWorkAsExpected_880) {

    FormField formField(&mockDocA, std::move(mockObj), ref, nullptr, &usedParentsSet, fieldType);

    formField.setReadOnly(true);

    EXPECT_TRUE(formField.isReadOnly());



    formField.setReadOnly(false);

    EXPECT_FALSE(formField.isReadOnly());

}



TEST_F(FormFieldTest_880, SetDefaultAppearanceAndGetDefaultAppearanceWorkAsExpected_880) {

    FormField formField(&mockDocA, std::move(mockObj), ref, nullptr, &usedParentsSet, fieldType);

    std::string appearance = "/Helv 12 Tf";

    formField.setDefaultAppearance(appearance);

    EXPECT_EQ(formField.getDefaultAppearance()->getCString(), appearance.c_str());

}



TEST_F(FormFieldTest_880, SetPartialNameAndGetPartialNameWorkAsExpected_880) {

    FormField formField(&mockDocA, std::move(mockObj), ref, nullptr, &usedParentsSet, fieldType);

    GooString partialName("partial_name");

    formField.setPartialName(partialName);

    EXPECT_EQ(formField.getPartialName()->getCString(), "partial_name");

}



TEST_F(FormFieldTest_880, GetFullyQualifiedNameReturnsNullByDefault_880) {

    FormField formField(&mockDocA, std::move(mockObj), ref, nullptr, &usedParentsSet, fieldType);

    EXPECT_EQ(formField.getFullyQualifiedName(), nullptr);

}



TEST_F(FormFieldTest_880, FindWidgetByRefReturnsNullForNonExistentWidget_880) {

    FormField formField(&mockDocA, std::move(mockObj), ref, nullptr, &usedParentsSet, fieldType);

    Ref nonExistentRef{3, 4};

    EXPECT_EQ(formField.findWidgetByRef(nonExistentRef), nullptr);

}



TEST_F(FormFieldTest_880, FindFieldByRefReturnsNullForNonExistentField_880) {

    FormField formField(&mockDocA, std::move(mockObj), ref, nullptr, &usedParentsSet, fieldType);

    Ref nonExistentRef{3, 4};

    EXPECT_EQ(formField.findFieldByRef(nonExistentRef), nullptr);

}



TEST_F(FormFieldTest_880, FindFieldByFullyQualifiedNameReturnsNullForNonExistentField_880) {

    FormField formField(&mockDocA, std::move(mockObj), ref, nullptr, &usedParentsSet, fieldType);

    EXPECT_EQ(formField.findFieldByFullyQualifiedName("non_existent_field"), nullptr);

}



TEST_F(FormFieldTest_880, ResetWithExcludedFieldsDoesNotThrow_880) {

    FormField formField(&mockDocA, std::move(mockObj), ref, nullptr, &usedParentsSet, fieldType);

    std::vector<std::string> excludedFields = {"field1", "field2"};

    EXPECT_NO_THROW(formField.reset(excludedFields));

}



TEST_F(FormFieldTest_880, ResetChildrenWithExcludedFieldsDoesNotThrow_880) {

    FormField formField(&mockDocA, std::move(mockObj), ref, nullptr, &usedParentsSet, fieldType);

    std::vector<std::string> excludedFields = {"field1", "field2"};

    EXPECT_NO_THROW(formField.resetChildren(excludedFields));

}



TEST_F(FormFieldTest_880, ResetWithIntExcludedFieldsDoesNotThrow_880) {

    FormField formField(&mockDocA, std::move(mockObj), ref, nullptr, &usedParentsSet, fieldType);

    int excludedFields = 123;

    EXPECT_NO_THROW(formField.reset(excludedFields));

}



TEST_F(FormFieldTest_880, ResetChildrenWithIntExcludedFieldsDoesNotThrow_880) {

    FormField formField(&mockDocA, std::move(mockObj), ref, nullptr, &usedParentsSet, fieldType);

    int excludedFields = 123;

    EXPECT_NO_THROW(formField.resetChildren(excludedFields));

}



TEST_F(FormFieldTest_880, GetNumWidgetsReturnsZeroByDefault_880) {

    FormField formField(&mockDocA, std::move(mockObj), ref, nullptr, &usedParentsSet, fieldType);

    EXPECT_EQ(formField.getNumWidgets(), 0);

}



TEST_F(FormFieldTest_880, GetWidgetReturnsNullForInvalidIndex_880) {

    FormField formField(&mockDocA, std::move(mockObj), ref, nullptr, &usedParentsSet, fieldType);

    EXPECT_EQ(formField.getWidget(0), nullptr);

}



TEST_F(FormFieldTest_880, GetNumChildrenReturnsZeroByDefault_880) {

    FormField formField(&mockDocA, std::move(mockObj), ref, nullptr, &usedParentsSet, fieldType);

    EXPECT_EQ(formField.getNumChildren(), 0);

}



TEST_F(FormFieldTest_880, GetChildrenReturnsNullForInvalidIndex_880) {

    FormField formField(&mockDocA, std::move(mockObj), ref, nullptr, &usedParentsSet, fieldType);

    EXPECT_EQ(formField.getChildren(0), nullptr);

}



TEST_F(FormFieldTest_880, GetNoExportReturnsFalseByDefault_880) {

    FormField formField(&mockDocA, std::move(mockObj), ref, nullptr, &usedParentsSet, fieldType);

    EXPECT_FALSE(formField.getNoExport());

}
