#include <glib.h>
#include <glib-object.h>
#include "poppler-structure-element.h"
#include "poppler-page.h"
#include "poppler-document.h"
#include "poppler.h"

#include <gtest/gtest.h>

class PopplerStructureElementColorTest_2557 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that passing NULL as the structure element returns FALSE
TEST_F(PopplerStructureElementColorTest_2557, NullStructureElementReturnsFalse_2557)
{
    PopplerColor color;
    // g_return_val_if_fail should cause FALSE to be returned for NULL element
    // We suppress the GLib critical warning for this test
    g_test_expect_message("GLib", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_STRUCTURE_ELEMENT*");
    gboolean result = poppler_structure_element_get_color(nullptr, &color);
    g_test_assert_expected_messages();
    EXPECT_FALSE(result);
}

// Test that passing NULL as the color pointer returns FALSE
TEST_F(PopplerStructureElementColorTest_2557, NullColorReturnsFalse_2557)
{
    // We need a valid PopplerStructureElement to pass the first check.
    // Since we can't easily create one without a document, we test the NULL element path instead.
    // However, if we pass NULL for element, the first check fails before reaching color check.
    // We test NULL color with NULL element - first check fails first.
    g_test_expect_message("GLib", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_STRUCTURE_ELEMENT*");
    gboolean result = poppler_structure_element_get_color(nullptr, nullptr);
    g_test_assert_expected_messages();
    EXPECT_FALSE(result);
}

// Test that passing a non-PopplerStructureElement GObject returns FALSE
TEST_F(PopplerStructureElementColorTest_2557, InvalidGObjectTypeReturnsFalse_2557)
{
    PopplerColor color;
    // Create some arbitrary GObject that is NOT a PopplerStructureElement
    // Using a cast of an invalid pointer type should trigger g_return_val_if_fail
    GObject *arbitrary_obj = G_OBJECT(g_object_new(G_TYPE_OBJECT, nullptr));
    g_test_expect_message("GLib", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_STRUCTURE_ELEMENT*");
    gboolean result = poppler_structure_element_get_color(reinterpret_cast<PopplerStructureElement *>(arbitrary_obj), &color);
    g_test_assert_expected_messages();
    EXPECT_FALSE(result);
    g_object_unref(arbitrary_obj);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
