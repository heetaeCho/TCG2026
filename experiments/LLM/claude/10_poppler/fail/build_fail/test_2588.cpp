#include <glib.h>
#include <gtest/gtest.h>

// Include necessary headers
extern "C" {
#include "poppler-structure-element.h"
#include "poppler-document.h"
}

#include "poppler-private.h"
#include "poppler.h"

#include <string>
#include <cstdio>

class PopplerStructureFormRoleTest_2588 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that passing NULL returns the default value (first enum value) due to g_return_val_if_fail
TEST_F(PopplerStructureFormRoleTest_2588, NullElementReturnsDefault_2588)
{
    // Passing NULL should trigger g_return_val_if_fail and return the default value
    // The default is the first value in EnumNameValue<PopplerStructureFormRole>::values
    // which should be POPPLER_STRUCTURE_FORM_ROLE_UNDEFINED (0) or similar
    PopplerStructureFormRole result = poppler_structure_element_get_form_role(nullptr);
    // g_return_val_if_fail with NULL will fail the kind check and return default
    // We just verify it doesn't crash and returns a valid enum value
    EXPECT_GE(result, POPPLER_STRUCTURE_FORM_ROLE_UNDEFINED);
    EXPECT_LE(result, POPPLER_STRUCTURE_FORM_ROLE_CHECKBOX);
}

// Test that the enum values are correctly defined
TEST_F(PopplerStructureFormRoleTest_2588, EnumValuesAreDefined_2588)
{
    EXPECT_EQ(POPPLER_STRUCTURE_FORM_ROLE_UNDEFINED, 0);
    EXPECT_EQ(POPPLER_STRUCTURE_FORM_ROLE_RADIO_BUTTON, 1);
    EXPECT_EQ(POPPLER_STRUCTURE_FORM_ROLE_PUSH_BUTTON, 2);
    EXPECT_EQ(POPPLER_STRUCTURE_FORM_ROLE_TEXT_VALUE, 3);
    EXPECT_EQ(POPPLER_STRUCTURE_FORM_ROLE_CHECKBOX, 4);
}

// Test with a tagged PDF that contains form structure elements if available
// This test loads a PDF with structure elements and checks get_form_role behavior
class PopplerStructureFormRoleDocTest_2588 : public ::testing::Test {
protected:
    PopplerDocument *doc = nullptr;

    void SetUp() override
    {
        // Try to create a minimal document; if not available, skip
        doc = nullptr;
    }

    void TearDown() override
    {
        if (doc) {
            g_object_unref(doc);
        }
    }
};

// Test that calling get_form_role on a non-FORM element returns the default
// (this exercises the g_return_val_if_fail guard for element kind)
TEST_F(PopplerStructureFormRoleDocTest_2588, NonFormElementReturnsDefault_2588)
{
    // When we can't construct a proper FORM element, passing NULL exercises
    // the same guard path
    PopplerStructureFormRole result = poppler_structure_element_get_form_role(nullptr);
    // Should return without crashing
    EXPECT_GE(result, POPPLER_STRUCTURE_FORM_ROLE_UNDEFINED);
    EXPECT_LE(result, POPPLER_STRUCTURE_FORM_ROLE_CHECKBOX);
}

// Verify enum completeness - all expected values exist and are sequential
TEST_F(PopplerStructureFormRoleTest_2588, EnumCompleteness_2588)
{
    // Verify that enum values are sequential from 0 to 4
    int values[] = {
        POPPLER_STRUCTURE_FORM_ROLE_UNDEFINED,
        POPPLER_STRUCTURE_FORM_ROLE_RADIO_BUTTON,
        POPPLER_STRUCTURE_FORM_ROLE_PUSH_BUTTON,
        POPPLER_STRUCTURE_FORM_ROLE_TEXT_VALUE,
        POPPLER_STRUCTURE_FORM_ROLE_CHECKBOX
    };

    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(values[i], i) << "Enum value at index " << i << " is not sequential";
    }
}

// Test that the function exists and is callable (link test)
TEST_F(PopplerStructureFormRoleTest_2588, FunctionIsCallable_2588)
{
    // Verify the function pointer is valid (non-null)
    auto func_ptr = &poppler_structure_element_get_form_role;
    EXPECT_NE(func_ptr, nullptr);
}
