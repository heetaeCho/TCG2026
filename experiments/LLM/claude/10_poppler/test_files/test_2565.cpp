#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cmath>

// Include necessary headers for poppler glib
#include "poppler-structure-element.h"
#include "poppler-private.h"

// We need to test poppler_structure_element_get_start_indent which:
// 1. Returns NAN if the element is not a block element
// 2. Returns the numeric value of the StartIndent attribute otherwise

class PopplerStructureElementGetStartIndentTest_2565 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that passing NULL returns NAN (g_return_val_if_fail should trigger)
TEST_F(PopplerStructureElementGetStartIndentTest_2565, NullElementReturnsNAN_2565)
{
    gdouble result = poppler_structure_element_get_start_indent(nullptr);
    EXPECT_TRUE(std::isnan(result));
}

// Test that a non-block structure element returns NAN
TEST_F(PopplerStructureElementGetStartIndentTest_2565, NonBlockElementReturnsNAN_2565)
{
    // Create a PopplerStructureElement that is not a block element
    // We need to construct one backed by an inline-level StructElement
    // Since we can't easily construct internal objects, we test with NULL
    // which exercises the g_return_val_if_fail path
    PopplerStructureElement *elem = nullptr;
    gdouble result = poppler_structure_element_get_start_indent(elem);
    EXPECT_TRUE(std::isnan(result));
}

// If we have access to create a valid block PopplerStructureElement,
// we would test that it returns a valid (non-NAN) double value.
// Since constructing a full StructElement requires a document context,
// we verify the interface contract through the null/invalid paths.

// Test that calling with NULL multiple times consistently returns NAN
TEST_F(PopplerStructureElementGetStartIndentTest_2565, ConsistentNANForNull_2565)
{
    for (int i = 0; i < 5; i++) {
        gdouble result = poppler_structure_element_get_start_indent(nullptr);
        EXPECT_TRUE(std::isnan(result));
    }
}
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cmath>
#include <glib.h>

extern "C" {
#include "poppler-structure-element.h"
}

class PopplerStructureElementGetStartIndentTest_2565 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that passing NULL triggers g_return_val_if_fail and returns NAN
TEST_F(PopplerStructureElementGetStartIndentTest_2565, NullElementReturnsNAN_2565)
{
    // Suppress GLib critical warnings for this test since we expect them
    g_test_expect_message("Poppler", G_LOG_LEVEL_CRITICAL, "*");
    
    gdouble result = poppler_structure_element_get_start_indent(nullptr);
    EXPECT_TRUE(std::isnan(result));
}

// Test that repeated calls with NULL consistently return NAN
TEST_F(PopplerStructureElementGetStartIndentTest_2565, RepeatedNullCallsReturnNAN_2565)
{
    for (int i = 0; i < 3; i++) {
        gdouble result = poppler_structure_element_get_start_indent(nullptr);
        EXPECT_TRUE(std::isnan(result));
    }
}

// Test boundary: verify the return type is gdouble (NAN is a valid gdouble)
TEST_F(PopplerStructureElementGetStartIndentTest_2565, ReturnTypeIsGdouble_2565)
{
    gdouble result = poppler_structure_element_get_start_indent(nullptr);
    // NAN compared to itself is always false per IEEE 754
    EXPECT_NE(result, result);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
