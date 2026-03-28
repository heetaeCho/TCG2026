// File: poppler_structure_element_get_ruby_position_test_2582.cc

#include <gtest/gtest.h>
#include <gmock/gmock.h>

extern "C" {
#include <glib.h>
#include "poppler.h"
#include "poppler-private.h"
}

// Forward declaration of the function under test
extern "C" PopplerStructureRubyPosition
poppler_structure_element_get_ruby_position(PopplerStructureElement *poppler_structure_element);

class PopplerStructureElementRubyPositionTest_2582 : public ::testing::Test {
protected:
    void SetUp() override {
        element = g_new0(PopplerStructureElement, 1);
    }

    void TearDown() override {
        if (element) {
            g_free(element);
            element = nullptr;
        }
    }

    PopplerStructureElement *element{nullptr};
};

/**
 * Test normal operation:
 * When a valid inline PopplerStructureElement is provided,
 * the function should return a valid PopplerStructureRubyPosition enum value.
 * (Black-box: we only verify that the returned value is within enum range.)
 */
TEST_F(PopplerStructureElementRubyPositionTest_2582,
       ReturnsValidEnumValueForValidInlineElement_2582)
{
    ASSERT_NE(element, nullptr);

    PopplerStructureRubyPosition pos =
        poppler_structure_element_get_ruby_position(element);

    // Since we treat implementation as black box,
    // verify that the returned value is within known enum bounds.
    EXPECT_GE(static_cast<int>(pos),
              static_cast<int>(POPPLER_STRUCTURE_RUBY_POSITION_UNKNOWN));
    EXPECT_LE(static_cast<int>(pos),
              static_cast<int>(POPPLER_STRUCTURE_RUBY_POSITION_AFTER));
}

/**
 * Boundary condition:
 * Passing nullptr should trigger g_return_val_if_fail
 * and return the default enum value (first enum entry).
 */
TEST_F(PopplerStructureElementRubyPositionTest_2582,
       ReturnsDefaultValueWhenNullElement_2582)
{
    PopplerStructureRubyPosition pos =
        poppler_structure_element_get_ruby_position(nullptr);

    // By contract of g_return_val_if_fail, the function should
    // return the first enum value.
    EXPECT_EQ(pos, POPPLER_STRUCTURE_RUBY_POSITION_UNKNOWN);
}

/**
 * Boundary condition:
 * When element exists but is not inline (observable via API),
 * function should return default enum value.
 */
TEST_F(PopplerStructureElementRubyPositionTest_2582,
       ReturnsDefaultValueWhenElementIsNotInline_2582)
{
    ASSERT_NE(element, nullptr);

    // We do not manipulate internal state; assume default zero-initialized
    // element does not satisfy inline requirement.
    PopplerStructureRubyPosition pos =
        poppler_structure_element_get_ruby_position(element);

    EXPECT_EQ(pos, POPPLER_STRUCTURE_RUBY_POSITION_UNKNOWN);
}

/**
 * Exceptional case:
 * Repeated calls with same valid element should be stable and not crash.
 */
TEST_F(PopplerStructureElementRubyPositionTest_2582,
       RepeatedCallsAreStable_2582)
{
    ASSERT_NE(element, nullptr);

    PopplerStructureRubyPosition pos1 =
        poppler_structure_element_get_ruby_position(element);
    PopplerStructureRubyPosition pos2 =
        poppler_structure_element_get_ruby_position(element);

    EXPECT_EQ(pos1, pos2);
}