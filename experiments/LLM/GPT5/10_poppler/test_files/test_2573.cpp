// poppler-structure-element-get-inline-align-test_2573.cc
#include <gtest/gtest.h>

#include <glib.h>

#include "poppler.h"
#include "poppler-private.h"

// Function under test (declared in poppler headers)
extern "C" PopplerStructureInlineAlign
poppler_structure_element_get_inline_align(PopplerStructureElement *poppler_structure_element);

namespace {

class PopplerStructureElementInlineAlignTest_2573 : public ::testing::Test {
protected:
    static PopplerStructureInlineAlign GetObservedDefault_2573()
    {
        // Per the implementation, the function uses g_return_val_if_fail(...)
        // and returns a "default" enum value when the precondition fails.
        // We treat this as a black box and simply observe what it returns.
        return poppler_structure_element_get_inline_align(nullptr);
    }
};

TEST_F(PopplerStructureElementInlineAlignTest_2573, NullptrReturnsDefaultValue_2573)
{
    const PopplerStructureInlineAlign v1 = poppler_structure_element_get_inline_align(nullptr);
    const PopplerStructureInlineAlign v2 = GetObservedDefault_2573();

    // Observable behavior: returns some deterministic default for invalid input.
    EXPECT_EQ(v1, v2);
}

TEST_F(PopplerStructureElementInlineAlignTest_2573, ElementWithNullElemReturnsSameDefaultAsNullptr_2573)
{
    const PopplerStructureInlineAlign expected_default = GetObservedDefault_2573();

    // Construct a PopplerStructureElement instance with elem == nullptr.
    // This should fail the "is_block" precondition (or otherwise be treated invalid)
    // and therefore return the same default value.
    _PopplerStructureElement raw {};
    raw.elem = nullptr;

    auto *se = reinterpret_cast<PopplerStructureElement *>(&raw);

    const PopplerStructureInlineAlign got = poppler_structure_element_get_inline_align(se);
    EXPECT_EQ(got, expected_default);
}

TEST_F(PopplerStructureElementInlineAlignTest_2573, RepeatedCallsWithInvalidInputsAreStable_2573)
{
    const PopplerStructureInlineAlign expected_default = GetObservedDefault_2573();

    // Repeated nullptr calls should be stable.
    EXPECT_EQ(poppler_structure_element_get_inline_align(nullptr), expected_default);
    EXPECT_EQ(poppler_structure_element_get_inline_align(nullptr), expected_default);

    // Repeated calls on the same "invalid" object should also be stable.
    _PopplerStructureElement raw {};
    raw.elem = nullptr;
    auto *se = reinterpret_cast<PopplerStructureElement *>(&raw);

    EXPECT_EQ(poppler_structure_element_get_inline_align(se), expected_default);
    EXPECT_EQ(poppler_structure_element_get_inline_align(se), expected_default);
}

} // namespace