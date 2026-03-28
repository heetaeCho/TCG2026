#include <glib.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Forward declarations and includes needed
#include "poppler-structure-element.h"
#include "poppler-document.h"

// We need access to the iter structure internals for setup
// These are from the glib binding layer

extern "C" {
PopplerStructureElementIter *poppler_structure_element_iter_get_child(PopplerStructureElementIter *parent);
void poppler_structure_element_iter_free(PopplerStructureElementIter *iter);
gboolean poppler_structure_element_iter_next(PopplerStructureElementIter *iter);
PopplerStructureElement *poppler_structure_element_iter_get_element(PopplerStructureElementIter *iter);
PopplerStructureElementIter *poppler_structure_element_iter_new(PopplerDocument *poppler_document);
PopplerStructureElementIter *poppler_structure_element_iter_copy(PopplerStructureElementIter *iter);
}

class PopplerStructureElementIterGetChildTest_2540 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that passing NULL returns NULL
TEST_F(PopplerStructureElementIterGetChildTest_2540, NullParentReturnsNull_2540)
{
    PopplerStructureElementIter *result = poppler_structure_element_iter_get_child(nullptr);
    EXPECT_EQ(result, nullptr);
}

// Test with a real PDF document that has structure elements
// Since we can't easily construct mock StructElement/StructTreeRoot objects,
// we test the null guard which is the primary boundary condition testable
// without a full PDF document setup.

class PopplerStructureElementIterNullGuardTest_2540 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(PopplerStructureElementIterNullGuardTest_2540, GetChildWithNullIterReturnsNull_2540)
{
    // g_return_val_if_fail should cause NULL return for NULL input
    PopplerStructureElementIter *child = poppler_structure_element_iter_get_child(NULL);
    ASSERT_EQ(child, nullptr);
}

// If we can load a PDF with known structure, test deeper behavior
class PopplerStructureElementIterDocumentTest_2540 : public ::testing::Test {
protected:
    PopplerDocument *doc = nullptr;

    void SetUp() override
    {
        GError *error = nullptr;
        // Try to load a test PDF with structure tags
        gchar *uri = g_filename_to_uri(TESTDATADIR "/unittestcases/WithStructure.pdf", nullptr, &error);
        if (uri) {
            doc = poppler_document_new_from_file(uri, nullptr, &error);
            g_free(uri);
        }
        if (error) {
            g_error_free(error);
        }
    }

    void TearDown() override
    {
        if (doc) {
            g_object_unref(doc);
        }
    }
};

TEST_F(PopplerStructureElementIterDocumentTest_2540, GetChildFromRootIterReturnsValidOrNull_2540)
{
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PopplerStructureElementIter *iter = poppler_structure_element_iter_new(doc);
    if (!iter) {
        GTEST_SKIP() << "No structure elements in test PDF";
    }

    // Get child of root - may or may not have children
    PopplerStructureElementIter *child = poppler_structure_element_iter_get_child(iter);
    // Result is either a valid iter or NULL - both are acceptable
    // If non-null, we should be able to free it
    if (child) {
        poppler_structure_element_iter_free(child);
    }

    poppler_structure_element_iter_free(iter);
}
