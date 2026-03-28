#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include necessary headers
extern "C" {
#include "poppler-form-field.h"
#include "poppler-action.h"
#include "poppler-document.h"
}

#include "poppler-private.h"
#include "Form.h"
#include "Link.h"

using ::testing::Return;
using ::testing::_;
using ::testing::NiceMock;

// Mock FormWidget to control getActivationAction behavior
class MockFormWidget : public FormWidget {
public:
    MockFormWidget() : FormWidget(nullptr, nullptr, 0, Ref{0, 0}, nullptr) {}
    MOCK_METHOD(LinkAction*, getActivationAction, ());
};

class PopplerFormFieldGetActionTest_2312 : public ::testing::Test {
protected:
    void SetUp() override {
        // Setup is done per-test as needed
    }

    void TearDown() override {
        // Cleanup is done per-test as needed
    }
};

// Test that when field->action is already set, it returns the cached action
TEST_F(PopplerFormFieldGetActionTest_2312, ReturnsCachedAction_WhenActionAlreadySet_2312) {
    _PopplerFormField fieldStruct;
    memset(&fieldStruct, 0, sizeof(fieldStruct));
    
    // Create a dummy PopplerAction to simulate a cached action
    PopplerAction *cachedAction = reinterpret_cast<PopplerAction*>(0xDEADBEEF);
    fieldStruct.action = cachedAction;
    
    // We don't need widget to be valid since the cached action should be returned first
    fieldStruct.widget = nullptr;
    
    PopplerFormField *field = reinterpret_cast<PopplerFormField*>(&fieldStruct);
    
    PopplerAction *result = poppler_form_field_get_action(field);
    EXPECT_EQ(result, cachedAction);
}

// Test that when field->action is null and widget returns null activation action, returns nullptr
TEST_F(PopplerFormFieldGetActionTest_2312, ReturnsNull_WhenNoActionAndWidgetHasNoActivationAction_2312) {
    _PopplerFormField fieldStruct;
    memset(&fieldStruct, 0, sizeof(fieldStruct));
    fieldStruct.action = nullptr;
    
    NiceMock<MockFormWidget> mockWidget;
    EXPECT_CALL(mockWidget, getActivationAction()).WillOnce(Return(nullptr));
    
    fieldStruct.widget = &mockWidget;
    
    PopplerFormField *field = reinterpret_cast<PopplerFormField*>(&fieldStruct);
    
    PopplerAction *result = poppler_form_field_get_action(field);
    EXPECT_EQ(result, nullptr);
}

// Test that calling get_action multiple times returns the same cached pointer
TEST_F(PopplerFormFieldGetActionTest_2312, ReturnsSameCachedActionOnMultipleCalls_2312) {
    _PopplerFormField fieldStruct;
    memset(&fieldStruct, 0, sizeof(fieldStruct));
    
    PopplerAction *cachedAction = reinterpret_cast<PopplerAction*>(0xBEEFCAFE);
    fieldStruct.action = cachedAction;
    fieldStruct.widget = nullptr;
    
    PopplerFormField *field = reinterpret_cast<PopplerFormField*>(&fieldStruct);
    
    PopplerAction *result1 = poppler_form_field_get_action(field);
    PopplerAction *result2 = poppler_form_field_get_action(field);
    
    EXPECT_EQ(result1, result2);
    EXPECT_EQ(result1, cachedAction);
}

// Test that when no cached action exists and widget returns null, nullptr is returned without modifying field->action
TEST_F(PopplerFormFieldGetActionTest_2312, FieldActionRemainsNull_WhenWidgetHasNoActivationAction_2312) {
    _PopplerFormField fieldStruct;
    memset(&fieldStruct, 0, sizeof(fieldStruct));
    fieldStruct.action = nullptr;
    
    NiceMock<MockFormWidget> mockWidget;
    EXPECT_CALL(mockWidget, getActivationAction()).WillOnce(Return(nullptr));
    
    fieldStruct.widget = &mockWidget;
    
    PopplerFormField *field = reinterpret_cast<PopplerFormField*>(&fieldStruct);
    
    poppler_form_field_get_action(field);
    EXPECT_EQ(fieldStruct.action, nullptr);
}

// Test that getActivationAction is not called when action is already cached
TEST_F(PopplerFormFieldGetActionTest_2312, DoesNotCallGetActivationAction_WhenActionCached_2312) {
    _PopplerFormField fieldStruct;
    memset(&fieldStruct, 0, sizeof(fieldStruct));
    
    PopplerAction *cachedAction = reinterpret_cast<PopplerAction*>(0xCAFEBABE);
    fieldStruct.action = cachedAction;
    
    NiceMock<MockFormWidget> mockWidget;
    // getActivationAction should NOT be called
    EXPECT_CALL(mockWidget, getActivationAction()).Times(0);
    
    fieldStruct.widget = &mockWidget;
    
    PopplerFormField *field = reinterpret_cast<PopplerFormField*>(&fieldStruct);
    
    PopplerAction *result = poppler_form_field_get_action(field);
    EXPECT_EQ(result, cachedAction);
}
