#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include necessary headers
extern "C" {
#include <glib-object.h>
}

#include "poppler-form-field.h"
#include "poppler-private.h"
#include "Form.h"

// We need to mock FormWidget since we can't easily construct real ones
// However, since we're treating the implementation as a black box and
// poppler_form_field_get_id just calls field->widget->getID(), we need
// to create test fixtures that set up PopplerFormField with a mock widget.

// Mock for FormWidget
class MockFormWidget : public FormWidget {
public:
    // We can't easily call the real constructor, so we use a trick
    // to create a mock that has getID overridden
    MockFormWidget() : FormWidget(nullptr, nullptr, 0, Ref{0, 0}, nullptr) {}
    
    MOCK_METHOD(unsigned, getID, (), (const));
    MOCK_METHOD(FormFieldType, getType, (), ());
};

// Since PopplerFormField is a GObject, we need to properly handle its creation
// For testing purposes, we'll work with the structure directly where possible

class PopplerFormFieldGetIdTest_2309 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that poppler_form_field_get_id returns -1 when passed NULL
TEST_F(PopplerFormFieldGetIdTest_2309, ReturnsNegativeOneForNull_2309)
{
    // Passing NULL should trigger g_return_val_if_fail and return -1
    gint result = poppler_form_field_get_id(nullptr);
    EXPECT_EQ(result, -1);
}

// Test that poppler_form_field_get_id returns the correct ID from the widget
TEST_F(PopplerFormFieldGetIdTest_2309, ReturnsWidgetId_2309)
{
    // Create a PopplerFormField using the GObject system
    PopplerFormField *field = static_cast<PopplerFormField *>(
        g_object_new(POPPLER_TYPE_FORM_FIELD, nullptr));
    
    if (field != nullptr) {
        MockFormWidget mockWidget;
        field->widget = &mockWidget;
        
        EXPECT_CALL(mockWidget, getID())
            .WillOnce(::testing::Return(42u));
        
        gint result = poppler_form_field_get_id(field);
        EXPECT_EQ(result, 42);
        
        // Clean up - set widget to null before unreffing to avoid double free
        field->widget = nullptr;
        g_object_unref(field);
    }
}

// Test with ID value of 0
TEST_F(PopplerFormFieldGetIdTest_2309, ReturnsZeroId_2309)
{
    PopplerFormField *field = static_cast<PopplerFormField *>(
        g_object_new(POPPLER_TYPE_FORM_FIELD, nullptr));
    
    if (field != nullptr) {
        MockFormWidget mockWidget;
        field->widget = &mockWidget;
        
        EXPECT_CALL(mockWidget, getID())
            .WillOnce(::testing::Return(0u));
        
        gint result = poppler_form_field_get_id(field);
        EXPECT_EQ(result, 0);
        
        field->widget = nullptr;
        g_object_unref(field);
    }
}

// Test with a large ID value
TEST_F(PopplerFormFieldGetIdTest_2309, ReturnsLargeId_2309)
{
    PopplerFormField *field = static_cast<PopplerFormField *>(
        g_object_new(POPPLER_TYPE_FORM_FIELD, nullptr));
    
    if (field != nullptr) {
        MockFormWidget mockWidget;
        field->widget = &mockWidget;
        
        unsigned int largeId = 999999;
        EXPECT_CALL(mockWidget, getID())
            .WillOnce(::testing::Return(largeId));
        
        gint result = poppler_form_field_get_id(field);
        EXPECT_EQ(result, static_cast<gint>(largeId));
        
        field->widget = nullptr;
        g_object_unref(field);
    }
}

// Test with maximum unsigned int value to check boundary
TEST_F(PopplerFormFieldGetIdTest_2309, ReturnsMaxUnsignedId_2309)
{
    PopplerFormField *field = static_cast<PopplerFormField *>(
        g_object_new(POPPLER_TYPE_FORM_FIELD, nullptr));
    
    if (field != nullptr) {
        MockFormWidget mockWidget;
        field->widget = &mockWidget;
        
        unsigned int maxId = UINT_MAX;
        EXPECT_CALL(mockWidget, getID())
            .WillOnce(::testing::Return(maxId));
        
        gint result = poppler_form_field_get_id(field);
        // The return is gint (signed), so casting from unsigned max will wrap
        EXPECT_EQ(result, static_cast<gint>(maxId));
        
        field->widget = nullptr;
        g_object_unref(field);
    }
}

// Test calling get_id multiple times returns consistent results
TEST_F(PopplerFormFieldGetIdTest_2309, ConsistentIdOnMultipleCalls_2309)
{
    PopplerFormField *field = static_cast<PopplerFormField *>(
        g_object_new(POPPLER_TYPE_FORM_FIELD, nullptr));
    
    if (field != nullptr) {
        MockFormWidget mockWidget;
        field->widget = &mockWidget;
        
        EXPECT_CALL(mockWidget, getID())
            .WillRepeatedly(::testing::Return(100u));
        
        gint result1 = poppler_form_field_get_id(field);
        gint result2 = poppler_form_field_get_id(field);
        EXPECT_EQ(result1, 100);
        EXPECT_EQ(result2, 100);
        EXPECT_EQ(result1, result2);
        
        field->widget = nullptr;
        g_object_unref(field);
    }
}

// Test with ID value of 1 (smallest positive)
TEST_F(PopplerFormFieldGetIdTest_2309, ReturnsIdOne_2309)
{
    PopplerFormField *field = static_cast<PopplerFormField *>(
        g_object_new(POPPLER_TYPE_FORM_FIELD, nullptr));
    
    if (field != nullptr) {
        MockFormWidget mockWidget;
        field->widget = &mockWidget;
        
        EXPECT_CALL(mockWidget, getID())
            .WillOnce(::testing::Return(1u));
        
        gint result = poppler_form_field_get_id(field);
        EXPECT_EQ(result, 1);
        
        field->widget = nullptr;
        g_object_unref(field);
    }
}
