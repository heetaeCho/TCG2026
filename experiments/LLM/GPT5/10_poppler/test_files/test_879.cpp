#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Form.h"

// Test case for normal operation
TEST_F(FormFieldTest_879, GetObj_ReturnsObject_879) {
    FormField formField(nullptr, Object(), Ref(), nullptr, nullptr, FormFieldType::eTextField);
    Object* obj = formField.getObj();
    ASSERT_NE(obj, nullptr);  // Ensure the returned object is not null
}

// Test case for checking getRef behavior
TEST_F(FormFieldTest_880, GetRef_ReturnsCorrectRef_880) {
    Ref ref;
    FormField formField(nullptr, Object(), ref, nullptr, nullptr, FormFieldType::eTextField);
    Ref resultRef = formField.getRef();
    ASSERT_EQ(resultRef, ref);  // Ensure the reference matches the provided one
}

// Test case for checking setReadOnly behavior
TEST_F(FormFieldTest_881, SetReadOnly_ChangesValue_881) {
    FormField formField(nullptr, Object(), Ref(), nullptr, nullptr, FormFieldType::eTextField);
    formField.setReadOnly(true);
    ASSERT_TRUE(formField.isReadOnly());  // Verify that the field is set to readonly

    formField.setReadOnly(false);
    ASSERT_FALSE(formField.isReadOnly());  // Verify that the field is no longer readonly
}

// Test case for checking getFullyQualifiedName behavior
TEST_F(FormFieldTest_882, GetFullyQualifiedName_ReturnsCorrectName_882) {
    GooString gooName("TestName");
    FormField formField(nullptr, Object(), Ref(), nullptr, nullptr, FormFieldType::eTextField);
    formField.setPartialName(gooName);

    const GooString* name = formField.getFullyQualifiedName();
    ASSERT_EQ(*name, gooName);  // Verify that the returned name is correct
}

// Test case for exceptional case handling: Invalid widget access
TEST_F(FormFieldTest_883, GetWidget_OutOfBounds_883) {
    FormField formField(nullptr, Object(), Ref(), nullptr, nullptr, FormFieldType::eTextField);
    ASSERT_EQ(formField.getWidget(0), nullptr);  // Trying to access a widget when none exists
}

// Test case for boundary condition: getNumWidgets when there are no widgets
TEST_F(FormFieldTest_884, GetNumWidgets_ZeroWidgets_884) {
    FormField formField(nullptr, Object(), Ref(), nullptr, nullptr, FormFieldType::eTextField);
    ASSERT_EQ(formField.getNumWidgets(), 0);  // Verify the number of widgets is 0
}

// Test case for boundary condition: getNumChildren when there are no children
TEST_F(FormFieldTest_885, GetNumChildren_ZeroChildren_885) {
    FormField formField(nullptr, Object(), Ref(), nullptr, nullptr, FormFieldType::eTextField);
    ASSERT_EQ(formField.getNumChildren(), 0);  // Verify the number of children is 0
}

// Test case for checking if field is stand-alone
TEST_F(FormFieldTest_886, SetStandAlone_SetsCorrectly_886) {
    FormField formField(nullptr, Object(), Ref(), nullptr, nullptr, FormFieldType::eTextField);
    formField.setStandAlone(true);
    ASSERT_TRUE(formField.isStandAlone());  // Verify that the field is stand-alone

    formField.setStandAlone(false);
    ASSERT_FALSE(formField.isStandAlone());  // Verify that the field is no longer stand-alone
}

// Test case for error handling: isAmongExcludedFields with invalid field
TEST_F(FormFieldTest_887, IsAmongExcludedFields_ReturnsFalse_887) {
    FormField formField(nullptr, Object(), Ref(), nullptr, nullptr, FormFieldType::eTextField);
    std::vector<std::string> excludedFields{"invalidField"};
    ASSERT_FALSE(formField.isAmongExcludedFields(excludedFields));  // Ensure that the invalid field is not excluded
}

// Test case for checking the behavior of hasTextQuadding
TEST_F(FormFieldTest_888, HasTextQuadding_ReturnsFalse_888) {
    FormField formField(nullptr, Object(), Ref(), nullptr, nullptr, FormFieldType::eTextField);
    ASSERT_FALSE(formField.hasTextQuadding());  // Verify that hasTextQuadding returns false for the default case
}

// Test case for error handling: findFieldByRef with invalid reference
TEST_F(FormFieldTest_889, FindFieldByRef_ReturnsNull_889) {
    FormField formField(nullptr, Object(), Ref(), nullptr, nullptr, FormFieldType::eTextField);
    Ref invalidRef;
    ASSERT_EQ(formField.findFieldByRef(invalidRef), nullptr);  // Verify that the field returns null for invalid reference
}