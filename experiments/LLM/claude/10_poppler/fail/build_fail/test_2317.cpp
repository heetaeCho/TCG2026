#include <glib.h>
#include <glib-object.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <string>
#include <memory>

// Include necessary poppler headers
#include "poppler-form-field.h"
#include "poppler-private.h"
#include "Form.h"
#include "GooString.h"

using ::testing::_;
using ::testing::Return;
using ::testing::NiceMock;

// Mock FormWidget to control getPartialName() behavior
class MockFormWidget : public FormWidget {
public:
    // We need a constructor that doesn't require real PDFDoc
    MockFormWidget() : FormWidget(nullptr, nullptr, 0, Ref{0, 0}, nullptr) {}
    
    MOCK_CONST_METHOD0(getPartialName, const GooString*());
};

class PopplerFormFieldGetPartialNameTest_2317 : public ::testing::Test {
protected:
    void SetUp() override {
        // We'll set up per-test as needed
    }

    void TearDown() override {
    }
};

// Test that passing NULL field returns NULL
TEST_F(PopplerFormFieldGetPartialNameTest_2317, NullFieldReturnsNull_2317) {
    gchar *result = poppler_form_field_get_partial_name(NULL);
    EXPECT_EQ(result, nullptr);
}

// Test that when getPartialName() returns nullptr, the function returns nullptr
TEST_F(PopplerFormFieldGetPartialNameTest_2317, NullPartialNameReturnsNull_2317) {
    // Create a PopplerFormField with a mock widget
    PopplerFormField *field = static_cast<PopplerFormField*>(
        g_object_new(POPPLER_TYPE_FORM_FIELD, NULL));
    
    auto mockWidget = std::make_unique<NiceMock<MockFormWidget>>();
    ON_CALL(*mockWidget, getPartialName()).WillByDefault(Return(nullptr));
    
    field->widget = mockWidget.get();
    
    gchar *result = poppler_form_field_get_partial_name(field);
    EXPECT_EQ(result, nullptr);
    
    field->widget = nullptr;
    g_object_unref(field);
}

// Test that when getPartialName() returns a valid GooString, the result is a valid UTF-8 string
TEST_F(PopplerFormFieldGetPartialNameTest_2317, ValidPartialNameReturnsUtf8String_2317) {
    PopplerFormField *field = static_cast<PopplerFormField*>(
        g_object_new(POPPLER_TYPE_FORM_FIELD, NULL));
    
    auto mockWidget = std::make_unique<NiceMock<MockFormWidget>>();
    GooString partialName("TestFieldName");
    ON_CALL(*mockWidget, getPartialName()).WillByDefault(Return(&partialName));
    
    field->widget = mockWidget.get();
    
    gchar *result = poppler_form_field_get_partial_name(field);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "TestFieldName");
    
    g_free(result);
    field->widget = nullptr;
    g_object_unref(field);
}

// Test with an empty GooString partial name
TEST_F(PopplerFormFieldGetPartialNameTest_2317, EmptyPartialNameReturnsEmptyString_2317) {
    PopplerFormField *field = static_cast<PopplerFormField*>(
        g_object_new(POPPLER_TYPE_FORM_FIELD, NULL));
    
    auto mockWidget = std::make_unique<NiceMock<MockFormWidget>>();
    GooString emptyName("");
    ON_CALL(*mockWidget, getPartialName()).WillByDefault(Return(&emptyName));
    
    field->widget = mockWidget.get();
    
    gchar *result = poppler_form_field_get_partial_name(field);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "");
    
    g_free(result);
    field->widget = nullptr;
    g_object_unref(field);
}

// Test with a partial name containing special characters
TEST_F(PopplerFormFieldGetPartialNameTest_2317, SpecialCharactersPartialName_2317) {
    PopplerFormField *field = static_cast<PopplerFormField*>(
        g_object_new(POPPLER_TYPE_FORM_FIELD, NULL));
    
    auto mockWidget = std::make_unique<NiceMock<MockFormWidget>>();
    GooString specialName("Field_123-abc.xyz");
    ON_CALL(*mockWidget, getPartialName()).WillByDefault(Return(&specialName));
    
    field->widget = mockWidget.get();
    
    gchar *result = poppler_form_field_get_partial_name(field);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "Field_123-abc.xyz");
    
    g_free(result);
    field->widget = nullptr;
    g_object_unref(field);
}

// Test with a long partial name
TEST_F(PopplerFormFieldGetPartialNameTest_2317, LongPartialName_2317) {
    PopplerFormField *field = static_cast<PopplerFormField*>(
        g_object_new(POPPLER_TYPE_FORM_FIELD, NULL));
    
    auto mockWidget = std::make_unique<NiceMock<MockFormWidget>>();
    std::string longStr(1000, 'A');
    GooString longName(longStr.c_str());
    ON_CALL(*mockWidget, getPartialName()).WillByDefault(Return(&longName));
    
    field->widget = mockWidget.get();
    
    gchar *result = poppler_form_field_get_partial_name(field);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(strlen(result), 1000u);
    
    g_free(result);
    field->widget = nullptr;
    g_object_unref(field);
}

// Test that the returned string is a newly allocated copy (caller owns it)
TEST_F(PopplerFormFieldGetPartialNameTest_2317, ReturnedStringIsNewlyAllocated_2317) {
    PopplerFormField *field = static_cast<PopplerFormField*>(
        g_object_new(POPPLER_TYPE_FORM_FIELD, NULL));
    
    auto mockWidget = std::make_unique<NiceMock<MockFormWidget>>();
    GooString partialName("DuplicateTest");
    ON_CALL(*mockWidget, getPartialName()).WillByDefault(Return(&partialName));
    
    field->widget = mockWidget.get();
    
    gchar *result1 = poppler_form_field_get_partial_name(field);
    gchar *result2 = poppler_form_field_get_partial_name(field);
    
    ASSERT_NE(result1, nullptr);
    ASSERT_NE(result2, nullptr);
    // Both should have the same content
    EXPECT_STREQ(result1, result2);
    // But should be different allocations
    EXPECT_NE(result1, result2);
    
    g_free(result1);
    g_free(result2);
    field->widget = nullptr;
    g_object_unref(field);
}
