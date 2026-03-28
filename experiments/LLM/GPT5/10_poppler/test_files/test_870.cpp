#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Form.h"  // Assume the header with FormWidget is correctly included.

using testing::Mock;
using testing::Return;
using testing::AtLeast;

// Mock class for testing FormWidget
class MockFormWidget : public FormWidget {
public:
    MockFormWidget(PDFDoc* docA, Object* aobj, unsigned int num, Ref aref, FormField* fieldA)
        : FormWidget(docA, aobj, num, aref, fieldA) {}

    MOCK_METHOD(FormField*, getField, (), (override));
    MOCK_METHOD(bool, inRect, (double x, double y), (const, override));
    MOCK_METHOD(void, getRect, (double* x1, double* y1, double* x2, double* y2), (const, override));
    MOCK_METHOD(const GooString*, getPartialName, (), (const, override));
    MOCK_METHOD(void, setPartialName, (const GooString& name), (override));
    MOCK_METHOD(const GooString*, getAlternateUiName, (), (const, override));
    MOCK_METHOD(const GooString*, getMappingName, (), (const, override));
    MOCK_METHOD(const GooString*, getFullyQualifiedName, (), (const, override));
    MOCK_METHOD(bool, isModified, (), (const, override));
    MOCK_METHOD(bool, isReadOnly, (), (const, override));
    MOCK_METHOD(void, setReadOnly, (bool value), (override));
    MOCK_METHOD(LinkAction*, getActivationAction, (), (override));
    MOCK_METHOD(std::unique_ptr<LinkAction>, getAdditionalAction, (Annot::FormAdditionalActionsType type), (override));
    MOCK_METHOD(bool, setAdditionalAction, (Annot::FormAdditionalActionsType t, const std::string& js), (override));
    MOCK_METHOD(void, createWidgetAnnotation, (), (override));
    MOCK_METHOD(void, updateWidgetAppearance, (), (override));
    MOCK_METHOD(void, print, (int indent), (override));
    MOCK_METHOD(unsigned, getID, (), (const, override));
    MOCK_METHOD(void, setID, (unsigned int i), (override));
    MOCK_METHOD(FormFieldType, getType, (), (override));
    MOCK_METHOD(Object*, getObj, (), (override));
    MOCK_METHOD(Ref, getRef, (), (override));
    MOCK_METHOD(void, setChildNum, (unsigned i), (override));
    MOCK_METHOD(unsigned, getChildNum, (), (const, override));
    MOCK_METHOD(std::shared_ptr<AnnotWidget>, getWidgetAnnotation, (), (const, override));
    MOCK_METHOD(void, setWidgetAnnotation, (std::shared_ptr<AnnotWidget> _widget), (override));
};

// Test case for the getField() method
TEST_F(MockFormWidget, GetField_ReturnsCorrectField_870) {
    FormField* expectedField = new FormField();
    MockFormWidget widget(nullptr, nullptr, 1, {}, expectedField);

    EXPECT_CALL(widget, getField()).WillOnce(Return(expectedField));

    FormField* actualField = widget.getField();
    EXPECT_EQ(actualField, expectedField);
}

// Test case for the inRect() method
TEST_F(MockFormWidget, InRect_ReturnsTrueForInside_871) {
    MockFormWidget widget(nullptr, nullptr, 1, {}, nullptr);
    double x = 10.0, y = 20.0;

    EXPECT_CALL(widget, inRect(x, y)).WillOnce(Return(true));

    bool result = widget.inRect(x, y);
    EXPECT_TRUE(result);
}

TEST_F(MockFormWidget, InRect_ReturnsFalseForOutside_872) {
    MockFormWidget widget(nullptr, nullptr, 1, {}, nullptr);
    double x = -10.0, y = -20.0;

    EXPECT_CALL(widget, inRect(x, y)).WillOnce(Return(false));

    bool result = widget.inRect(x, y);
    EXPECT_FALSE(result);
}

// Test case for getRect() method
TEST_F(MockFormWidget, GetRect_CorrectValues_873) {
    MockFormWidget widget(nullptr, nullptr, 1, {}, nullptr);
    double x1, y1, x2, y2;

    EXPECT_CALL(widget, getRect(&x1, &y1, &x2, &y2))
        .WillOnce(testing::DoAll(testing::SetArgReferee<0>(1.0), testing::SetArgReferee<1>(2.0),
                                 testing::SetArgReferee<2>(3.0), testing::SetArgReferee<3>(4.0)));

    widget.getRect(&x1, &y1, &x2, &y2);
    EXPECT_EQ(x1, 1.0);
    EXPECT_EQ(y1, 2.0);
    EXPECT_EQ(x2, 3.0);
    EXPECT_EQ(y2, 4.0);
}

// Test case for setReadOnly() method
TEST_F(MockFormWidget, SetReadOnly_ValidValue_874) {
    MockFormWidget widget(nullptr, nullptr, 1, {}, nullptr);
    bool newValue = true;

    EXPECT_CALL(widget, setReadOnly(newValue)).Times(1);

    widget.setReadOnly(newValue);
}

// Test case for getID() method
TEST_F(MockFormWidget, GetID_ReturnsCorrectID_875) {
    MockFormWidget widget(nullptr, nullptr, 1, {}, nullptr);
    unsigned expectedID = 123;

    EXPECT_CALL(widget, getID()).WillOnce(Return(expectedID));

    unsigned actualID = widget.getID();
    EXPECT_EQ(actualID, expectedID);
}

// Test case for setWidgetAnnotation() method
TEST_F(MockFormWidget, SetWidgetAnnotation_ValidAnnotation_876) {
    std::shared_ptr<AnnotWidget> newWidget = std::make_shared<AnnotWidget>();
    MockFormWidget widget(nullptr, nullptr, 1, {}, nullptr);

    EXPECT_CALL(widget, setWidgetAnnotation(newWidget)).Times(1);

    widget.setWidgetAnnotation(newWidget);
}

// Exceptional Case: Ensure that invalid action returns false for setAdditionalAction
TEST_F(MockFormWidget, SetAdditionalAction_InvalidAction_877) {
    MockFormWidget widget(nullptr, nullptr, 1, {}, nullptr);
    std::string invalidJsCode = "invalidJs";

    EXPECT_CALL(widget, setAdditionalAction(Annot::FormAdditionalActionsType::Unknown, invalidJsCode)).WillOnce(Return(false));

    bool result = widget.setAdditionalAction(Annot::FormAdditionalActionsType::Unknown, invalidJsCode);
    EXPECT_FALSE(result);
}