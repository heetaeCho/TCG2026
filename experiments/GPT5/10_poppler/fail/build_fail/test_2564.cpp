// poppler-structure-element-get-space-after-test.cc
#include <gtest/gtest.h>

#include <cmath>   // std::isnan
#include <cstddef> // nullptr

// Prefer including the public Poppler GLib header if available.
#if __has_include(<poppler.h>)
#include <poppler.h>
#elif __has_include("poppler.h")
#include "poppler.h"
#endif

// We only use the provided internal struct definition to create a minimal,
// non-block/invalid element instance without touching any private state.
#if __has_include("poppler-private.h")
#include "poppler-private.h"
#endif

extern "C" {
gdouble poppler_structure_element_get_space_after(PopplerStructureElement *poppler_structure_element);
}

class PopplerStructureElementGetSpaceAfterTest_2564 : public ::testing::Test {};

TEST_F(PopplerStructureElementGetSpaceAfterTest_2564, NullPointerReturnsNaN_2564)
{
    // Error/exceptional case: API should refuse invalid element and return NAN.
    const gdouble v = poppler_structure_element_get_space_after(nullptr);
    EXPECT_TRUE(std::isnan(static_cast<double>(v)));
}

TEST_F(PopplerStructureElementGetSpaceAfterTest_2564, DummyElementWithNullElemReturnsNaN_2564)
{
    // Boundary/error case: a structurally present PopplerStructureElement whose backing
    // StructElement is null should not be considered a valid block element.
    PopplerStructureElement dummy{};
    dummy.elem = nullptr;

    const gdouble v = poppler_structure_element_get_space_after(&dummy);
    EXPECT_TRUE(std::isnan(static_cast<double>(v)));
}

TEST_F(PopplerStructureElementGetSpaceAfterTest_2564, RepeatedCallsOnInvalidElementRemainNaN_2564)
{
    PopplerStructureElement dummy{};
    dummy.elem = nullptr;

    const gdouble v1 = poppler_structure_element_get_space_after(&dummy);
    const gdouble v2 = poppler_structure_element_get_space_after(&dummy);

    EXPECT_TRUE(std::isnan(static_cast<double>(v1)));
    EXPECT_TRUE(std::isnan(static_cast<double>(v2)));
}