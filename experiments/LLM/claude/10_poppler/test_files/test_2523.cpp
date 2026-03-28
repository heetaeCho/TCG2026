#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include necessary headers
extern "C" {
#include <glib-object.h>
}

// We need to include the poppler glib headers
#include "poppler-structure-element.h"
#include "poppler-document.h"
#include "poppler-private.h"

// Since we're testing a GObject-based C API as a black box, and we cannot
// easily construct PopplerStructureElement objects without the full poppler
// infrastructure, we test what we can through the public API.

class PopplerStructureElementGetPageTest_2523 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that passing NULL returns -1 (the g_return_val_if_fail guard)
TEST_F(PopplerStructureElementGetPageTest_2523, NullElementReturnsNegativeOne_2523)
{
    // Passing NULL should trigger g_return_val_if_fail and return -1
    // We need to suppress the GLib warning for this test
    g_test_expect_message("Poppler", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_STRUCTURE_ELEMENT*");
    gint result = poppler_structure_element_get_page(nullptr);
    g_test_assert_expected_messages();
    EXPECT_EQ(result, -1);
}

// Test that passing an invalid GObject (not a PopplerStructureElement) returns -1
TEST_F(PopplerStructureElementGetPageTest_2523, InvalidGObjectReturnsNegativeOne_2523)
{
    // Create some random GObject that is NOT a PopplerStructureElement
    // Using a plain GObject instance
    GObject *obj = (GObject *)g_object_new(G_TYPE_OBJECT, nullptr);
    ASSERT_NE(obj, nullptr);

    g_test_expect_message("Poppler", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_STRUCTURE_ELEMENT*");
    gint result = poppler_structure_element_get_page((PopplerStructureElement *)obj);
    g_test_assert_expected_messages();
    EXPECT_EQ(result, -1);

    g_object_unref(obj);
}

// Test with a real PDF document that has structure elements
// This tests normal operation by loading a tagged PDF
class PopplerStructureElementFromDocTest_2523 : public ::testing::Test {
protected:
    PopplerDocument *doc = nullptr;

    void SetUp() override
    {
        // Try to load a test PDF with structure/tags
        // If no test PDF is available, tests will be skipped
        GError *error = nullptr;
        // Attempt to find a tagged PDF for testing
        const char *test_files[] = {
            "file:///tmp/test_tagged.pdf",
            nullptr
        };

        for (int i = 0; test_files[i] != nullptr; i++) {
            doc = poppler_document_new_from_file(test_files[i], nullptr, &error);
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

// If a tagged PDF is available, test that structure elements return valid page indices
TEST_F(PopplerStructureElementFromDocTest_2523, StructureElementPageFromDocument_2523)
{
    if (!doc) {
        GTEST_SKIP() << "No test PDF available for structure element page test";
    }

    PopplerStructureElementIter *iter = poppler_structure_element_iter_new(doc);
    if (!iter) {
        GTEST_SKIP() << "Document has no structure elements";
    }

    // Walk the first structure element and check get_page
    PopplerStructureElement *elem = poppler_structure_element_iter_get_element(iter);
    ASSERT_NE(elem, nullptr);

    gint page = poppler_structure_element_get_page(elem);
    // Page should be >= -1 (could be -1 if no page ref, or >= 0 if valid)
    EXPECT_GE(page, -1);

    // If page is valid, it should be within document page range
    if (page >= 0) {
        int n_pages = poppler_document_get_n_pages(doc);
        EXPECT_LT(page, n_pages);
    }

    g_object_unref(elem);
    poppler_structure_element_iter_free(iter);
}

// Test that get_page returns -1 for grouping elements (which typically don't have a page ref)
TEST_F(PopplerStructureElementFromDocTest_2523, GroupingElementMayReturnNegativeOne_2523)
{
    if (!doc) {
        GTEST_SKIP() << "No test PDF available";
    }

    PopplerStructureElementIter *iter = poppler_structure_element_iter_new(doc);
    if (!iter) {
        GTEST_SKIP() << "Document has no structure elements";
    }

    // The root/document-level structure element is typically grouping
    PopplerStructureElement *elem = poppler_structure_element_iter_get_element(iter);
    ASSERT_NE(elem, nullptr);

    PopplerStructureElementKind kind = poppler_structure_element_get_kind(elem);
    gint page = poppler_structure_element_get_page(elem);

    // For grouping elements, page might be -1
    // We just verify the function doesn't crash and returns a sane value
    EXPECT_GE(page, -1);

    g_object_unref(elem);
    poppler_structure_element_iter_free(iter);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
