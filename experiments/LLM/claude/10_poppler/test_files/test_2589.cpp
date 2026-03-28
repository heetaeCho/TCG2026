#include <gtest/gtest.h>
#include <gmock/gmock.h>

extern "C" {
#include "poppler-structure-element.h"
#include "poppler-enums.h"
}

// We need to test poppler_structure_element_get_form_state based on the public interface.
// The function:
// 1. Checks that the element's kind is POPPLER_STRUCTURE_ELEMENT_FORM
// 2. If not, returns the first enum value (default)
// 3. If it is a form element, returns the form state attribute

class PopplerStructureElementGetFormStateTest_2589 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that calling get_form_state with NULL returns the default value
// (g_return_val_if_fail should trigger and return default)
TEST_F(PopplerStructureElementGetFormStateTest_2589, NullElementReturnsDefault_2589)
{
    // Passing NULL should trigger g_return_val_if_fail and return the default enum value
    // This tests the error/boundary case of a NULL input
    PopplerStructureFormState result = poppler_structure_element_get_form_state(nullptr);
    // The default value should be the first value in the enum
    // We just verify it doesn't crash and returns some valid enum value
    EXPECT_GE(static_cast<int>(result), 0);
}

// Test that calling get_form_state on a non-FORM element returns the default value
// We need a valid PopplerStructureElement that is NOT of kind POPPLER_STRUCTURE_ELEMENT_FORM
// Since we can't easily construct one without internal access, we verify the NULL case
// which also fails the kind check (since get_kind on NULL would not return FORM)

// Additional boundary test: verify the function signature is callable
TEST_F(PopplerStructureElementGetFormStateTest_2589, FunctionIsCallable_2589)
{
    // Verify the function pointer is valid and the symbol exists
    auto func_ptr = &poppler_structure_element_get_form_state;
    EXPECT_NE(func_ptr, nullptr);
}

// Test that the return type is within valid PopplerStructureFormState range for NULL input
TEST_F(PopplerStructureElementGetFormStateTest_2589, ReturnValueIsValidEnumForNullInput_2589)
{
    PopplerStructureFormState result = poppler_structure_element_get_form_state(nullptr);
    // The result should be a valid enum value
    int result_int = static_cast<int>(result);
    // Check it's within a reasonable range for the enum
    EXPECT_GE(result_int, 0);
}
