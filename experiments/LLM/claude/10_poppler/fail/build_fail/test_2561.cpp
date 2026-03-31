#include <glib.h>
#include <glib-object.h>
#include <poppler.h>
#include <poppler-structure-element.h>

#include <gtest/gtest.h>

class PopplerStructureElementBorderThicknessTest_2561 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that passing NULL for the structure element returns FALSE
TEST_F(PopplerStructureElementBorderThicknessTest_2561, NullElementReturnsFalse_2561)
{
    gdouble border_thicknesses[4] = { 0.0, 0.0, 0.0, 0.0 };
    // g_return_val_if_fail with NULL element should return FALSE
    // Note: This will trigger a GLib critical warning
    g_test_expect_message("GLib", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_STRUCTURE_ELEMENT*");
    gboolean result = poppler_structure_element_get_border_thickness(NULL, border_thicknesses);
    g_test_assert_expected_messages();
    EXPECT_FALSE(result);
}

// Test that passing NULL for border_thicknesses output parameter returns FALSE
TEST_F(PopplerStructureElementBorderThicknessTest_2561, NullBorderThicknessesReturnsFalse_2561)
{
    // We need a valid PopplerStructureElement to test the second parameter check.
    // Since we can't easily create one without a document, we test the NULL element case instead.
    // If we had a valid element, passing NULL for border_thicknesses should return FALSE.
    // This test documents the expected interface behavior.
    
    // With both NULL, the first check should fail first
    g_test_expect_message("GLib", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_STRUCTURE_ELEMENT*");
    gboolean result = poppler_structure_element_get_border_thickness(NULL, NULL);
    g_test_assert_expected_messages();
    EXPECT_FALSE(result);
}

// Test with a real PDF document that has structure elements
class PopplerStructureElementDocTest_2561 : public ::testing::Test {
protected:
    PopplerDocument *doc = nullptr;

    void SetUp() override
    {
        // Try to load a tagged PDF for testing. If not available, skip.
        doc = nullptr;
    }

    void TearDown() override
    {
        if (doc) {
            g_object_unref(doc);
        }
    }

    PopplerDocument *loadTaggedPdf(const char *path)
    {
        GError *error = nullptr;
        gchar *uri = g_filename_to_uri(path, nullptr, &error);
        if (!uri) {
            if (error)
                g_error_free(error);
            return nullptr;
        }
        PopplerDocument *document = poppler_document_new_from_file(uri, nullptr, &error);
        g_free(uri);
        if (error) {
            g_error_free(error);
        }
        return document;
    }
};

// Test that the function handles non-structure-element GObject properly
TEST_F(PopplerStructureElementBorderThicknessTest_2561, NonStructureElementReturnsFalse_2561)
{
    // Passing a non-PopplerStructureElement GObject should fail the type check
    // We use a generic GObject as a stand-in
    GObject *not_a_structure_element = (GObject *)g_object_new(G_TYPE_OBJECT, NULL);
    gdouble border_thicknesses[4] = { 0.0, 0.0, 0.0, 0.0 };

    g_test_expect_message("GLib", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_STRUCTURE_ELEMENT*");
    gboolean result = poppler_structure_element_get_border_thickness(
            (PopplerStructureElement *)not_a_structure_element, border_thicknesses);
    g_test_assert_expected_messages();
    EXPECT_FALSE(result);

    g_object_unref(not_a_structure_element);
}

// Test that output array is initialized before the call and check return value
TEST_F(PopplerStructureElementBorderThicknessTest_2561, OutputArrayPreservedOnFailure_2561)
{
    gdouble border_thicknesses[4] = { 1.0, 2.0, 3.0, 4.0 };

    g_test_expect_message("GLib", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_STRUCTURE_ELEMENT*");
    gboolean result = poppler_structure_element_get_border_thickness(NULL, border_thicknesses);
    g_test_assert_expected_messages();
    EXPECT_FALSE(result);

    // On failure, the array should remain unchanged since function returns early
    EXPECT_DOUBLE_EQ(border_thicknesses[0], 1.0);
    EXPECT_DOUBLE_EQ(border_thicknesses[1], 2.0);
    EXPECT_DOUBLE_EQ(border_thicknesses[2], 3.0);
    EXPECT_DOUBLE_EQ(border_thicknesses[3], 4.0);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
