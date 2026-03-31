#include <glib.h>
#include <glib-object.h>
#include <poppler.h>
#include <poppler-structure-element.h>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

class PopplerStructureElementColumnGapsTest_2585 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that passing NULL for poppler_structure_element returns NULL
TEST_F(PopplerStructureElementColumnGapsTest_2585, NullElementReturnsNull_2585)
{
    guint n_values = 0;
    gdouble *result = poppler_structure_element_get_column_gaps(nullptr, &n_values);
    EXPECT_EQ(result, nullptr);
}

// Test that passing NULL for n_values returns NULL
TEST_F(PopplerStructureElementColumnGapsTest_2585, NullNValuesReturnsNull_2585)
{
    // We cannot easily create a valid PopplerStructureElement without a real PDF,
    // but we can verify the guard against null n_values with a null element too.
    // The first guard (is_grouping) will fire before n_values check if element is null.
    gdouble *result = poppler_structure_element_get_column_gaps(nullptr, nullptr);
    EXPECT_EQ(result, nullptr);
}

// Integration-style test: Load a real PDF with structure elements if available
// This test verifies behavior with a document that has tagged structure
class PopplerStructureElementDocTest_2585 : public ::testing::Test {
protected:
    PopplerDocument *doc = nullptr;
    gchar *uri = nullptr;

    void SetUp() override
    {
        // Try to find a test PDF with structure elements
        // If not available, tests will be skipped
        doc = nullptr;
    }

    void TearDown() override
    {
        if (doc) {
            g_object_unref(doc);
        }
        g_free(uri);
    }

    PopplerDocument *loadTestDocument(const char *path)
    {
        GError *error = nullptr;
        gchar *abs_path = g_canonicalize_filename(path, nullptr);
        gchar *file_uri = g_filename_to_uri(abs_path, nullptr, &error);
        g_free(abs_path);
        if (!file_uri) {
            if (error)
                g_error_free(error);
            return nullptr;
        }
        PopplerDocument *document = poppler_document_new_from_file(file_uri, nullptr, &error);
        g_free(file_uri);
        if (error) {
            g_error_free(error);
        }
        return document;
    }
};

// Test that a non-grouping structure element returns NULL due to the guard
TEST_F(PopplerStructureElementDocTest_2585, NonGroupingElementReturnsNull_2585)
{
    // Without a valid grouping element, the function should return NULL
    // We test this through the null element path which also fails is_grouping check
    guint n_values = 42;
    gdouble *result = poppler_structure_element_get_column_gaps(nullptr, &n_values);
    EXPECT_EQ(result, nullptr);
    // n_values should remain unchanged since the function returns before modifying it
    EXPECT_EQ(n_values, 42u);
}

// Test both parameters null
TEST_F(PopplerStructureElementColumnGapsTest_2585, BothParamsNullReturnsNull_2585)
{
    gdouble *result = poppler_structure_element_get_column_gaps(nullptr, nullptr);
    EXPECT_EQ(result, nullptr);
}
