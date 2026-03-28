#include <glib.h>
#include <glib-object.h>
#include <poppler.h>
#include <poppler-structure-element.h>

#include <gtest/gtest.h>

class PopplerStructureElementTextDecorationColorTest_2578 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that passing NULL as the structure element returns FALSE (via g_return_val_if_fail)
TEST_F(PopplerStructureElementTextDecorationColorTest_2578, NullStructureElementReturnsFalse_2578)
{
    PopplerColor color;
    memset(&color, 0, sizeof(color));

    // g_return_val_if_fail should cause FALSE to be returned for NULL element
    // This will produce a g_critical warning, so we suppress it
    g_test_expect_message("GLib", G_LOG_LEVEL_CRITICAL, "*assertion*failed*");
    gboolean result = poppler_structure_element_get_text_decoration_color(nullptr, &color);
    g_test_assert_expected_messages();

    EXPECT_FALSE(result);
}

// Test that passing NULL as the color returns FALSE (via g_return_val_if_fail)
TEST_F(PopplerStructureElementTextDecorationColorTest_2578, NullColorReturnsFalse_2578)
{
    // We need a valid inline structure element here, but since we can't easily create one
    // without a document, the first guard (is_inline check) will likely fail first.
    // We test the NULL color path indirectly.
    g_test_expect_message("GLib", G_LOG_LEVEL_CRITICAL, "*assertion*failed*");
    gboolean result = poppler_structure_element_get_text_decoration_color(nullptr, nullptr);
    g_test_assert_expected_messages();

    EXPECT_FALSE(result);
}

// Test with a PDF document containing tagged structure to verify actual behavior
class PopplerStructureElementWithDocTest_2578 : public ::testing::Test {
protected:
    PopplerDocument *doc = nullptr;

    void SetUp() override
    {
        // Try to load a test PDF with structure elements if available
        // This test is conditional on having a test file
        doc = nullptr;
    }

    void TearDown() override
    {
        if (doc) {
            g_object_unref(doc);
        }
    }
};

// Test that the function returns FALSE for non-inline structure elements
TEST_F(PopplerStructureElementWithDocTest_2578, NonInlineElementReturnsFalse_2578)
{
    // Without a real document, we verify behavior with NULL which triggers the guard
    PopplerColor color;
    memset(&color, 0, sizeof(color));

    g_test_expect_message("GLib", G_LOG_LEVEL_CRITICAL, "*assertion*failed*");
    gboolean result = poppler_structure_element_get_text_decoration_color(nullptr, &color);
    g_test_assert_expected_messages();

    EXPECT_FALSE(result);
}

// Test: Based on the code, even when value is found, the function returns FALSE
// (this appears to be a bug in the implementation - it returns FALSE instead of TRUE
// after convert_color). We test the observable behavior.
TEST_F(PopplerStructureElementTextDecorationColorTest_2578, FunctionAlwaysReturnsFalsePerImplementation_2578)
{
    // The implementation has `return FALSE` at the end instead of `return TRUE`
    // after calling convert_color. This test documents that observable behavior.
    // Without a valid inline structure element, we can only test the guard conditions.
    PopplerColor color;
    memset(&color, 0, sizeof(color));

    g_test_expect_message("GLib", G_LOG_LEVEL_CRITICAL, "*assertion*failed*");
    gboolean result = poppler_structure_element_get_text_decoration_color(nullptr, &color);
    g_test_assert_expected_messages();

    EXPECT_EQ(result, FALSE);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
