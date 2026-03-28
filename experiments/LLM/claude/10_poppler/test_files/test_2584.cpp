#include <glib.h>
#include <glib-object.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

// Include the necessary poppler headers
extern "C" {
#include "poppler-structure-element.h"
#include "poppler-document.h"
}

#include "poppler-private.h"
#include "StructElement.h"

// Since we're testing poppler_structure_element_get_column_count as a black box,
// we need to work with the public GLib API. However, creating proper
// PopplerStructureElement objects requires a valid PDF document with structure elements.
// We'll test what we can through the public interface.

class PopplerStructureElementGetColumnCountTest_2584 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that passing NULL returns 0 (g_return_val_if_fail should catch this)
TEST_F(PopplerStructureElementGetColumnCountTest_2584, NullElementReturnsZero_2584)
{
    // g_return_val_if_fail with NULL should return the default value 0
    // We need to suppress GLib critical warnings for this test
    g_test_expect_message("Glib", G_LOG_LEVEL_CRITICAL, "*");
    guint result = poppler_structure_element_get_column_count(NULL);
    g_test_assert_expected_messages();
    EXPECT_EQ(result, 0u);
}

// Test that passing a non-grouping element returns 0
// The g_return_val_if_fail checks poppler_structure_element_is_grouping
TEST_F(PopplerStructureElementGetColumnCountTest_2584, NonGroupingElementReturnsZero_2584)
{
    // We create a PopplerStructureElement that is not a grouping element.
    // Since we can't easily construct one without a document, we test with NULL
    // which also fails the is_grouping check.
    g_test_expect_message("Glib", G_LOG_LEVEL_CRITICAL, "*");
    guint result = poppler_structure_element_get_column_count(nullptr);
    g_test_assert_expected_messages();
    EXPECT_EQ(result, 0u);
}

// Test with a real PDF document that has tagged structure
class PopplerStructureElementFromDocTest_2584 : public ::testing::Test {
protected:
    PopplerDocument *doc = nullptr;

    void SetUp() override
    {
        // Try to load a tagged PDF for testing
        // This test may be skipped if no suitable PDF is available
        GError *error = nullptr;

        // Try to find a test PDF with structure elements
        const char *test_pdfs[] = {
            "file:///tmp/test_tagged.pdf",
            nullptr
        };

        for (int i = 0; test_pdfs[i] != nullptr; i++) {
            doc = poppler_document_new_from_file(test_pdfs[i], nullptr, &error);
            if (doc != nullptr) {
                break;
            }
            if (error) {
                g_error_free(error);
                error = nullptr;
            }
        }
    }

    void TearDown() override
    {
        if (doc) {
            g_object_unref(doc);
        }
    }
};

// Test that the function returns a valid column count for a valid grouping element
// This test requires a tagged PDF to be available
TEST_F(PopplerStructureElementFromDocTest_2584, ValidGroupingElementReturnsColumnCount_2584)
{
    if (!doc) {
        GTEST_SKIP() << "No test PDF available for structure element testing";
    }

    PopplerStructureElementIter *iter = poppler_structure_element_iter_new(doc);
    if (!iter) {
        GTEST_SKIP() << "Document has no structure elements";
    }

    PopplerStructureElement *element = poppler_structure_element_iter_get_element(iter);
    ASSERT_NE(element, nullptr);

    if (poppler_structure_element_is_grouping(element)) {
        guint count = poppler_structure_element_get_column_count(element);
        // Column count should be at least 1 (default) for a valid grouping element
        EXPECT_GE(count, 1u);
    }

    g_object_unref(element);
    poppler_structure_element_iter_free(iter);
}

// Test the return type is guint (non-negative)
TEST_F(PopplerStructureElementGetColumnCountTest_2584, ReturnTypeIsUnsigned_2584)
{
    // Verify that the return value for invalid input is 0 (unsigned)
    g_test_expect_message("Glib", G_LOG_LEVEL_CRITICAL, "*");
    guint result = poppler_structure_element_get_column_count(nullptr);
    g_test_assert_expected_messages();
    // The result should be exactly 0, not some negative value cast to unsigned
    EXPECT_EQ(result, 0u);
}
