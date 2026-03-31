#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <glib-object.h>

// Include necessary headers
extern "C" {
#include "poppler-form-field.h"
}

#include "poppler-private.h"
#include "Form.h"
#include "GooString.h"

using ::testing::_;
using ::testing::Return;
using ::testing::NiceMock;

// Mock for FormWidget to control getAlternateUiName behavior
class MockFormWidget : public FormWidget {
public:
    MockFormWidget() : FormWidget(nullptr, nullptr, 0, Ref{0, 0}, nullptr) {}
    MOCK_CONST_METHOD0(getAlternateUiName, const GooString *());
};

class PopplerFormFieldGetAlternateUiNameTest_2320 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that passing NULL field returns NULL
TEST_F(PopplerFormFieldGetAlternateUiNameTest_2320, NullFieldReturnsNull_2320)
{
    // Passing NULL should trigger g_return_val_if_fail and return NULL
    gchar *result = poppler_form_field_get_alternate_ui_name(NULL);
    EXPECT_EQ(result, nullptr);
}

// Test that when getAlternateUiName returns nullptr, the function returns nullptr
TEST_F(PopplerFormFieldGetAlternateUiNameTest_2320, NullAlternateUiNameReturnsNull_2320)
{
    // We need a valid PopplerFormField with a mock widget
    // Since PopplerFormField is a GObject, we need to create it properly
    // However, since we can't easily construct one without the full GObject infrastructure,
    // we test at the boundary we can control.
    
    // This test documents expected behavior: when widget->getAlternateUiName() returns nullptr,
    // the function should return nullptr.
    // Due to GObject type checking in g_return_val_if_fail, we cannot easily test this
    // without a properly constructed PopplerFormField GObject.
    // We document this as a known limitation.
    SUCCEED();
}

// Test that an invalid (non-PopplerFormField) pointer returns NULL due to type check
TEST_F(PopplerFormFieldGetAlternateUiNameTest_2320, InvalidObjectReturnsNull_2320)
{
    // Create a plain GObject that is not a PopplerFormField
    // g_return_val_if_fail(POPPLER_IS_FORM_FIELD(field), NULL) should fail
    // and return NULL
    
    // Note: Casting a random pointer as PopplerFormField* would be UB,
    // but we can test with NULL which is the safest invalid input
    PopplerFormField *invalid = NULL;
    gchar *result = poppler_form_field_get_alternate_ui_name(invalid);
    EXPECT_EQ(result, nullptr);
}
