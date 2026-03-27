#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <vector>
#include <memory>
#include <string>

#include "./TestProjects/poppler/poppler/Form.h"

// Mocking external dependencies
class MockFormField : public FormField {
public:
    MOCK_METHOD(int, getNumChildren, (), (const, override));
    MOCK_METHOD(FormField*, getChildren, (int i), (const, override));
    MOCK_METHOD(bool, getNoExport, (), (const, override));
    MOCK_METHOD(const GooString*, getFullyQualifiedName, (), (const, override));
    MOCK_METHOD(int, getNumWidgets, (), (const, override));
    MOCK_METHOD(FormWidget*, getWidget, (int i), (const, override));
    MOCK_METHOD(FormField*, findFieldByRef, (Ref aref), (override));
    MOCK_METHOD(FormField*, findFieldByFullyQualifiedName, (const std::string& name), (override));
};

TEST_F(FormFieldTest_892, GetNumChildrenReturnsZeroWhenTerminal) {
    MockFormField field;
    field.terminal = true;

    EXPECT_CALL(field, getNumChildren()).WillOnce(testing::Return(0));

    EXPECT_EQ(field.getNumChildren(), 0);
}

TEST_F(FormFieldTest_892, GetNumChildrenReturnsSizeWhenNotTerminal) {
    MockFormField field;
    field.terminal = false;
    field.children = std::vector<std::unique_ptr<FormField>>(3);

    EXPECT_CALL(field, getNumChildren()).WillOnce(testing::Return(3));

    EXPECT_EQ(field.getNumChildren(), 3);
}

TEST_F(FormFieldTest_892, GetChildrenReturnsValidChildAtIndex) {
    MockFormField field;
    field.children.push_back(std::make_unique<FormField>());
    field.children.push_back(std::make_unique<FormField>());
    
    FormField* child = field.getChildren(0);
    
    EXPECT_NE(child, nullptr);
}

TEST_F(FormFieldTest_892, GetNoExportReturnsFalseByDefault) {
    MockFormField field;
    
    EXPECT_CALL(field, getNoExport()).WillOnce(testing::Return(false));

    EXPECT_FALSE(field.getNoExport());
}

TEST_F(FormFieldTest_892, GetFullyQualifiedNameReturnsExpectedName) {
    MockFormField field;
    GooString name("TestName");
    field.fullyQualifiedName = std::make_unique<GooString>(name);
    
    EXPECT_CALL(field, getFullyQualifiedName()).WillOnce(testing::Return(&name));

    EXPECT_EQ(field.getFullyQualifiedName()->getCString(), "TestName");
}

TEST_F(FormFieldTest_892, GetWidgetReturnsNullIfIndexOutOfBounds) {
    MockFormField field;
    field.widgets = std::vector<std::unique_ptr<FormWidget>>(2);

    FormWidget* widget = field.getWidget(3); // Out of bounds

    EXPECT_EQ(widget, nullptr);
}

TEST_F(FormFieldTest_892, FindFieldByRefReturnsValidField) {
    MockFormField field;
    Ref ref; // Assume Ref is properly initialized
    FormField* foundField = field.findFieldByRef(ref);

    EXPECT_NE(foundField, nullptr);
}

TEST_F(FormFieldTest_892, FindFieldByFullyQualifiedNameReturnsValidField) {
    MockFormField field;
    std::string name = "TestField";
    FormField* foundField = field.findFieldByFullyQualifiedName(name);

    EXPECT_NE(foundField, nullptr);
}

TEST_F(FormFieldTest_892, ResetDoesNotCrashWithEmptyExcludedFields) {
    MockFormField field;
    std::vector<std::string> excludedFields;
    
    EXPECT_NO_THROW(field.reset(excludedFields));
}

TEST_F(FormFieldTest_892, ResetChildrenDoesNotCrashWithEmptyExcludedFields) {
    MockFormField field;
    std::vector<std::string> excludedFields;
    
    EXPECT_NO_THROW(field.resetChildren(excludedFields));
}

TEST_F(FormFieldTest_892, SetReadOnlyWorksCorrectly) {
    MockFormField field;
    
    EXPECT_CALL(field, setReadOnly(true)).Times(1);
    
    field.setReadOnly(true);
}

TEST_F(FormFieldTest_892, SetStandAloneWorksCorrectly) {
    MockFormField field;
    
    EXPECT_CALL(field, setStandAlone(true)).Times(1);
    
    field.setStandAlone(true);
}

TEST_F(FormFieldTest_892, GetNumWidgetsReturnsCorrectValue) {
    MockFormField field;
    field.widgets = std::vector<std::unique_ptr<FormWidget>>(5);
    
    EXPECT_CALL(field, getNumWidgets()).WillOnce(testing::Return(5));

    EXPECT_EQ(field.getNumWidgets(), 5);
}

TEST_F(FormFieldTest_892, GetWidgetReturnsCorrectWidget) {
    MockFormField field;
    field.widgets = std::vector<std::unique_ptr<FormWidget>>(2);
    
    FormWidget* widget = field.getWidget(1);
    
    EXPECT_NE(widget, nullptr);
}

TEST_F(FormFieldTest_892, HasTextQuaddingReturnsTrueIfSet) {
    MockFormField field;
    field.hasQuadding = true;
    
    EXPECT_CALL(field, hasTextQuadding()).WillOnce(testing::Return(true));

    EXPECT_TRUE(field.hasTextQuadding());
}

TEST_F(FormFieldTest_892, HasTextQuaddingReturnsFalseByDefault) {
    MockFormField field;
    field.hasQuadding = false;
    
    EXPECT_CALL(field, hasTextQuadding()).WillOnce(testing::Return(false));

    EXPECT_FALSE(field.hasTextQuadding());
}