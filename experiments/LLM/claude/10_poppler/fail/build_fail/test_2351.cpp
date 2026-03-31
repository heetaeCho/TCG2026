#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <glib.h>
#include <memory>
#include <string>

// Include necessary headers
#include "poppler-form-field.h"
#include "poppler-private.h"
#include "Form.h"
#include "GooString.h"

using ::testing::_;
using ::testing::Return;
using ::testing::Invoke;

// Mock FormWidgetChoice to capture setEditChoice calls
class MockFormWidgetChoice : public FormWidgetChoice {
public:
    MockFormWidgetChoice() : FormWidgetChoice(nullptr, nullptr, 0, Ref{0, 0}, nullptr) {}
    
    MOCK_METHOD(void, setEditChoice, (std::unique_ptr<GooString>), (override));
    
    FormFieldType getType() override { return formChoice; }
};

// Mock FormWidget for non-choice type testing
class MockFormWidgetText : public FormWidget {
public:
    MockFormWidgetText() : FormWidget(nullptr, nullptr, 0, Ref{0, 0}, nullptr) {}
    
    FormFieldType getType() override { return formText; }
};

class PopplerFormFieldChoiceSetTextTest_2351 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that setting text on a choice field with valid UTF-8 text works
TEST_F(PopplerFormFieldChoiceSetTextTest_2351, SetTextWithValidUTF8_2351)
{
    MockFormWidgetChoice mockWidget;
    
    _PopplerFormField field;
    field.widget = &mockWidget;
    field.field_modified_action = nullptr;
    field.format_field_action = nullptr;
    field.validate_field_action = nullptr;
    field.calculate_field_action = nullptr;
    
    std::string capturedText;
    EXPECT_CALL(mockWidget, setEditChoice(_))
        .WillOnce(Invoke([&capturedText](std::unique_ptr<GooString> gooStr) {
            if (gooStr) {
                capturedText = std::string(gooStr->c_str(), gooStr->getLength());
            }
        }));
    
    poppler_form_field_choice_set_text(reinterpret_cast<PopplerFormField *>(&field), "Hello");
    
    // The text should have been converted to UTF-16BE, so it should not be empty
    EXPECT_FALSE(capturedText.empty());
}

// Test that setting text with nullptr results in an empty GooString
TEST_F(PopplerFormFieldChoiceSetTextTest_2351, SetTextWithNull_2351)
{
    MockFormWidgetChoice mockWidget;
    
    _PopplerFormField field;
    field.widget = &mockWidget;
    field.field_modified_action = nullptr;
    field.format_field_action = nullptr;
    field.validate_field_action = nullptr;
    field.calculate_field_action = nullptr;
    
    bool gooStringWasEmpty = false;
    EXPECT_CALL(mockWidget, setEditChoice(_))
        .WillOnce(Invoke([&gooStringWasEmpty](std::unique_ptr<GooString> gooStr) {
            if (gooStr && gooStr->getLength() == 0) {
                gooStringWasEmpty = true;
            }
        }));
    
    poppler_form_field_choice_set_text(reinterpret_cast<PopplerFormField *>(&field), nullptr);
    
    EXPECT_TRUE(gooStringWasEmpty);
}

// Test that setting empty string text works
TEST_F(PopplerFormFieldChoiceSetTextTest_2351, SetTextWithEmptyString_2351)
{
    MockFormWidgetChoice mockWidget;
    
    _PopplerFormField field;
    field.widget = &mockWidget;
    field.field_modified_action = nullptr;
    field.format_field_action = nullptr;
    field.validate_field_action = nullptr;
    field.calculate_field_action = nullptr;
    
    size_t capturedLength = 999;
    EXPECT_CALL(mockWidget, setEditChoice(_))
        .WillOnce(Invoke([&capturedLength](std::unique_ptr<GooString> gooStr) {
            if (gooStr) {
                capturedLength = gooStr->getLength();
            }
        }));
    
    poppler_form_field_choice_set_text(reinterpret_cast<PopplerFormField *>(&field), "");
    
    // Empty UTF-8 string converted to UTF-16BE should produce empty or BOM-only output
    // The exact length depends on g_convert behavior with empty strings
    EXPECT_LE(capturedLength, 2u); // Could be 0 or 2 (BOM)
}

// Test that setting text with Unicode characters works
TEST_F(PopplerFormFieldChoiceSetTextTest_2351, SetTextWithUnicodeCharacters_2351)
{
    MockFormWidgetChoice mockWidget;
    
    _PopplerFormField field;
    field.widget = &mockWidget;
    field.field_modified_action = nullptr;
    field.format_field_action = nullptr;
    field.validate_field_action = nullptr;
    field.calculate_field_action = nullptr;
    
    size_t capturedLength = 0;
    EXPECT_CALL(mockWidget, setEditChoice(_))
        .WillOnce(Invoke([&capturedLength](std::unique_ptr<GooString> gooStr) {
            if (gooStr) {
                capturedLength = gooStr->getLength();
            }
        }));
    
    // UTF-8 encoded string with non-ASCII characters (e.g., "é" is 2 bytes in UTF-8, 2 bytes in UTF-16BE)
    poppler_form_field_choice_set_text(reinterpret_cast<PopplerFormField *>(&field), "café");
    
    // "café" has 4 characters, each 2 bytes in UTF-16BE = 8 bytes
    EXPECT_GT(capturedLength, 0u);
}

// Test that calling with a non-choice widget type triggers g_return_if_fail
// (The function should return early without calling setEditChoice)
TEST_F(PopplerFormFieldChoiceSetTextTest_2351, NonChoiceFieldTypeReturnsEarly_2351)
{
    MockFormWidgetText mockWidget;
    
    _PopplerFormField field;
    field.widget = &mockWidget;
    field.field_modified_action = nullptr;
    field.format_field_action = nullptr;
    field.validate_field_action = nullptr;
    field.calculate_field_action = nullptr;
    
    // This should not crash - the g_return_if_fail should prevent further execution
    // We can't easily verify the g_return_if_fail fires, but we can verify no crash
    // and that no setEditChoice is called (since it's not a FormWidgetChoice)
    poppler_form_field_choice_set_text(reinterpret_cast<PopplerFormField *>(&field), "test");
    
    // If we got here without crash, the test passes
    SUCCEED();
}

// Test with a long text string
TEST_F(PopplerFormFieldChoiceSetTextTest_2351, SetTextWithLongString_2351)
{
    MockFormWidgetChoice mockWidget;
    
    _PopplerFormField field;
    field.widget = &mockWidget;
    field.field_modified_action = nullptr;
    field.format_field_action = nullptr;
    field.validate_field_action = nullptr;
    field.calculate_field_action = nullptr;
    
    size_t capturedLength = 0;
    EXPECT_CALL(mockWidget, setEditChoice(_))
        .WillOnce(Invoke([&capturedLength](std::unique_ptr<GooString> gooStr) {
            if (gooStr) {
                capturedLength = gooStr->getLength();
            }
        }));
    
    // Create a long ASCII string (1000 characters)
    std::string longText(1000, 'A');
    poppler_form_field_choice_set_text(reinterpret_cast<PopplerFormField *>(&field), longText.c_str());
    
    // 1000 ASCII characters in UTF-16BE = 2000 bytes
    EXPECT_EQ(capturedLength, 2000u);
}

// Test setEditChoice is called exactly once
TEST_F(PopplerFormFieldChoiceSetTextTest_2351, SetEditChoiceCalledOnce_2351)
{
    MockFormWidgetChoice mockWidget;
    
    _PopplerFormField field;
    field.widget = &mockWidget;
    field.field_modified_action = nullptr;
    field.format_field_action = nullptr;
    field.validate_field_action = nullptr;
    field.calculate_field_action = nullptr;
    
    EXPECT_CALL(mockWidget, setEditChoice(_)).Times(1);
    
    poppler_form_field_choice_set_text(reinterpret_cast<PopplerFormField *>(&field), "test");
}

// Test with single character
TEST_F(PopplerFormFieldChoiceSetTextTest_2351, SetTextWithSingleCharacter_2351)
{
    MockFormWidgetChoice mockWidget;
    
    _PopplerFormField field;
    field.widget = &mockWidget;
    field.field_modified_action = nullptr;
    field.format_field_action = nullptr;
    field.validate_field_action = nullptr;
    field.calculate_field_action = nullptr;
    
    size_t capturedLength = 0;
    EXPECT_CALL(mockWidget, setEditChoice(_))
        .WillOnce(Invoke([&capturedLength](std::unique_ptr<GooString> gooStr) {
            if (gooStr) {
                capturedLength = gooStr->getLength();
            }
        }));
    
    poppler_form_field_choice_set_text(reinterpret_cast<PopplerFormField *>(&field), "A");
    
    // Single ASCII character in UTF-16BE = 2 bytes
    EXPECT_EQ(capturedLength, 2u);
}

// Test with multi-byte UTF-8 characters (CJK character)
TEST_F(PopplerFormFieldChoiceSetTextTest_2351, SetTextWithCJKCharacters_2351)
{
    MockFormWidgetChoice mockWidget;
    
    _PopplerFormField field;
    field.widget = &mockWidget;
    field.field_modified_action = nullptr;
    field.format_field_action = nullptr;
    field.validate_field_action = nullptr;
    field.calculate_field_action = nullptr;
    
    size_t capturedLength = 0;
    EXPECT_CALL(mockWidget, setEditChoice(_))
        .WillOnce(Invoke([&capturedLength](std::unique_ptr<GooString> gooStr) {
            if (gooStr) {
                capturedLength = gooStr->getLength();
            }
        }));
    
    // "日本" - two CJK characters, each 3 bytes in UTF-8, each 2 bytes in UTF-16BE
    poppler_form_field_choice_set_text(reinterpret_cast<PopplerFormField *>(&field), "日本");
    
    // Two BMP characters in UTF-16BE = 4 bytes
    EXPECT_EQ(capturedLength, 4u);
}
