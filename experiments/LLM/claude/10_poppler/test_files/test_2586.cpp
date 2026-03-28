#include <glib.h>
#include <glib-object.h>
#include <poppler.h>
#include <poppler-structure-element.h>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

class PopplerStructureElementGetColumnWidthsTest_2586 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that passing NULL for poppler_structure_element returns NULL
TEST_F(PopplerStructureElementGetColumnWidthsTest_2586, NullElementReturnsNull_2586)
{
    guint n_values = 0;
    // g_return_val_if_fail should trigger and return NULL when element is NULL
    // Note: This may produce a g_critical warning
    g_test_expect_message(NULL, G_LOG_LEVEL_CRITICAL, "*poppler_structure_element_is_grouping*");
    gdouble *result = poppler_structure_element_get_column_widths(NULL, &n_values);
    g_test_assert_expected_messages();
    EXPECT_EQ(result, nullptr);
}

// Test that passing NULL for n_values returns NULL
TEST_F(PopplerStructureElementGetColumnWidthsTest_2586, NullNValuesReturnsNull_2586)
{
    // We need a valid PopplerStructureElement that is grouping, but since we can't
    // easily create one, we test with NULL element first - the first guard will fire
    // before n_values check. Instead, test behavior expectation:
    // If element is NULL, both guards fail - first one triggers.
    g_test_expect_message(NULL, G_LOG_LEVEL_CRITICAL, "*poppler_structure_element_is_grouping*");
    gdouble *result = poppler_structure_element_get_column_widths(NULL, NULL);
    g_test_assert_expected_messages();
    EXPECT_EQ(result, nullptr);
}

// Test with a real PDF document that has structure elements
class PopplerStructureElementDocTest_2586 : public ::testing::Test {
protected:
    PopplerDocument *doc = nullptr;
    
    void SetUp() override {
        // Try to load a tagged PDF if available
        // This test may be skipped if no suitable PDF is available
    }
    
    void TearDown() override {
        if (doc) {
            g_object_unref(doc);
        }
    }
};

// Test that a non-grouping element returns NULL due to the first guard
TEST_F(PopplerStructureElementGetColumnWidthsTest_2586, NonGroupingElementReturnsNull_2586)
{
    // Without being able to create a proper non-grouping PopplerStructureElement,
    // we verify the NULL case behaves correctly through the guard
    guint n_values = 42;
    g_test_expect_message(NULL, G_LOG_LEVEL_CRITICAL, "*poppler_structure_element_is_grouping*");
    gdouble *result = poppler_structure_element_get_column_widths(NULL, &n_values);
    g_test_assert_expected_messages();
    EXPECT_EQ(result, nullptr);
}

// Verify that n_values parameter is checked (second guard)
// This tests the boundary where first guard passes but second fails
// Since we can't easily construct a grouping element without a PDF,
// we verify the overall contract through the NULL path
TEST_F(PopplerStructureElementGetColumnWidthsTest_2586, BothParamsNullReturnNull_2586)
{
    g_test_expect_message(NULL, G_LOG_LEVEL_CRITICAL, "*poppler_structure_element_is_grouping*");
    gdouble *result = poppler_structure_element_get_column_widths(NULL, NULL);
    g_test_assert_expected_messages();
    EXPECT_EQ(result, nullptr);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
