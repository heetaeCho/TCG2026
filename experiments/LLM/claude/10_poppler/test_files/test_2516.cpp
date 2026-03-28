#include <glib-object.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include necessary headers
extern "C" {
#include "poppler-structure-element.h"
#include "poppler-document.h"
}

#include "poppler-private.h"
#include "StructElement.h"

// We need to work with the GObject-based API, so we need the type system initialized
class PopplerStructureElementTest_2516 : public ::testing::Test {
protected:
    static void SetUpTestSuite()
    {
        // Initialize the GObject type system
#if !GLIB_CHECK_VERSION(2, 36, 0)
        g_type_init();
#endif
    }

    void SetUp() override
    {
        // We need a valid PopplerDocument and StructElement to test with
        // Since we can't easily create these without a real PDF, we'll
        // test what we can through the public API
    }

    void TearDown() override { }
};

// Test that the structure element type is properly registered
TEST_F(PopplerStructureElementTest_2516, TypeRegistration_2516)
{
    GType type = POPPLER_TYPE_STRUCTURE_ELEMENT;
    EXPECT_NE(type, G_TYPE_INVALID);
}

// Test that the type name is correct
TEST_F(PopplerStructureElementTest_2516, TypeName_2516)
{
    GType type = POPPLER_TYPE_STRUCTURE_ELEMENT;
    const gchar *name = g_type_name(type);
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "PopplerStructureElement");
}

// Test that POPPLER_IS_STRUCTURE_ELEMENT works on NULL
TEST_F(PopplerStructureElementTest_2516, IsStructureElementNull_2516)
{
    EXPECT_FALSE(POPPLER_IS_STRUCTURE_ELEMENT(nullptr));
}

// Test that POPPLER_IS_STRUCTURE_ELEMENT works on a non-structure-element object
TEST_F(PopplerStructureElementTest_2516, IsStructureElementWrongType_2516)
{
    // Create a simple GObject that is not a PopplerStructureElement
    GObject *obj = (GObject *)g_object_new(G_TYPE_OBJECT, nullptr);
    ASSERT_NE(obj, nullptr);
    EXPECT_FALSE(POPPLER_IS_STRUCTURE_ELEMENT(obj));
    g_object_unref(obj);
}

// Test that the GType hierarchy is correct (should derive from GObject)
TEST_F(PopplerStructureElementTest_2516, TypeHierarchy_2516)
{
    GType type = POPPLER_TYPE_STRUCTURE_ELEMENT;
    EXPECT_TRUE(g_type_is_a(type, G_TYPE_OBJECT));
}

// Test poppler_structure_element_get_kind with a real PDF document
// This requires loading a tagged PDF - we test the enum type exists
TEST_F(PopplerStructureElementTest_2516, StructureElementKindEnumExists_2516)
{
    // Verify that the enum values are defined
    EXPECT_EQ(POPPLER_STRUCTURE_ELEMENT_CONTENT, 0);
    // Just verify the enum type exists and has expected values
    EXPECT_GE(POPPLER_STRUCTURE_ELEMENT_DOCUMENT, 0);
}

// Test that poppler_structure_element_get_type returns a valid GType
TEST_F(PopplerStructureElementTest_2516, GetTypeFunction_2516)
{
    GType type = poppler_structure_element_get_type();
    EXPECT_NE(type, G_TYPE_INVALID);
    EXPECT_EQ(type, POPPLER_TYPE_STRUCTURE_ELEMENT);
}

// Integration test: Load a tagged PDF and verify structure elements
// This test will be skipped if no test PDF is available
class PopplerStructureElementIntegrationTest_2516 : public ::testing::Test {
protected:
    PopplerDocument *doc = nullptr;
    gchar *uri = nullptr;

    void SetUp() override
    {
#if !GLIB_CHECK_VERSION(2, 36, 0)
        g_type_init();
#endif
        // Try to find a test PDF with structure elements
        // This is best-effort; test will be skipped if unavailable
        const char *test_files[] = { "test-tagged.pdf", "../test/tagged.pdf", nullptr };

        for (int i = 0; test_files[i] != nullptr; i++) {
            if (g_file_test(test_files[i], G_FILE_TEST_EXISTS)) {
                gchar *abs_path = g_canonicalize_filename(test_files[i], nullptr);
                uri = g_strdup_printf("file://%s", abs_path);
                g_free(abs_path);

                GError *error = nullptr;
                doc = poppler_document_new_from_file(uri, nullptr, &error);
                if (error) {
                    g_error_free(error);
                    g_free(uri);
                    uri = nullptr;
                    doc = nullptr;
                }
                break;
            }
        }
    }

    void TearDown() override
    {
        if (doc) {
            g_object_unref(doc);
        }
        g_free(uri);
    }
};

// Test structure tree root retrieval (may be NULL for untagged PDFs)
TEST_F(PopplerStructureElementIntegrationTest_2516, GetStructureTreeIfAvailable_2516)
{
    if (!doc) {
        GTEST_SKIP() << "No test PDF available for integration testing";
    }

    // If the document is loaded, we can at least verify the document is valid
    EXPECT_TRUE(POPPLER_IS_DOCUMENT(doc));
}
